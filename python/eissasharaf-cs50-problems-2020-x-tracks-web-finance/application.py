import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    share = list()
    total = list()
    rate = list()
    symbol = db.execute("SELECT DISTINCT symbol FROM track WHERE id = :id_;", id_ = int(session["user_id"]))
    for row in range(len(symbol)):
        rate.append(lookup(symbol[row]['symbol']))
        share.append(db.execute("SELECT shares FROM track WHERE symbol = :symbol AND id = :id_", symbol = symbol[row]['symbol'], id_ = int(session["user_id"])))
        i = 0
    for row in range(len(share)):
        total.append(0)
        for element in share[row]:
            total[row - i] += element['shares']
        if total[row - i] == 0:
            total.remove(total[row - i])
            symbol.remove(symbol[row - i])
            rate.remove(rate[row - i])
            i += 1
    cash = db.execute("SELECT cash FROM users WHERE id = :id_", id_ = int(session["user_id"]))
    i = len(symbol)
    alll = cash[0]['cash'] + sum((rate[j]['price'] * total[j]) for j in range(len(rate)))
    return render_template("index.html", symbol = symbol, cash = cash, total = total, rate = rate, i = i, alll = alll)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get('symbol') or not request.form.get('shares'):
            return apology("please enter a symbol and/or rate", 400)
        symbol = request.form.get('symbol')
        shares = int(request.form.get('shares'))
        if shares <= 0:
            return apology("please enter a positive number")
        rate = lookup(symbol)
        if not rate:
            return apology("INVALID SYMBOL", 400)
        price = db.execute("SELECT cash FROM users WHERE  id = :id_;", id_ = session["user_id"])
        own = int(price[0]['cash'])
        if own > shares * int(rate['price']):
            own -= shares * int(rate['price'])
            print(own, session["user_id"])
            db.execute("UPDATE users SET cash = :cash WHERE id = :id_", cash = own, id_ = int(session["user_id"]))
            db.execute("INSERT INTO track (id, symbol, shares, price) VALUES (:id_, :symbol, :shares, :price)", id_ = session["user_id"], symbol = symbol,
                        shares = shares, price = rate['price'])
            return redirect("/")
        else:
            return apology("CAN'T AFFORD", 400)
    else:
        return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    hist = db.execute("SELECT * FROM track WHERE id =:id_", id_ = session["user_id"])
    return render_template("history.html", hist = hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        rate = lookup(request.form.get('symbol'))
        if not rate:
            return apology("INVALID SYMBOL", 400)
        return render_template("quoted.html", name = rate['name'], cost = rate['price'], symbol = rate['symbol'])
    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get('username')
        password = request.form.get('password')
        confirm = request.form.get('confirmation')
        #CHECK valid name & pssword & password confirmation
        if not name:
            return apology("must provide username", 403)
        elif not password:
            return apology("must provide password", 403)
        elif not confirm:
            return apology("must confirm password", 403)

        if password != confirm:
            return apology("please make sure to write password correctly", 403)
        else:
            #register the user into database
            count = db.execute("SELECT COUNT(*) AS 'countt' FROM users WHERE username = :name;", name = name);
            if  int(count[0]['countt']) != 0:
                return apology("This username isn't available. Please try another.", 403)
            else:
                db.execute("INSERT INTO users (username, hash) VALUES(:name, :password);", name = name, password = generate_password_hash(password))
                return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    own = db.execute("SELECT symbol, shares FROM track WHERE id = :id_", id_ = session["user_id"])
    mine = list()
    for dic in own:
        mine.append(list(dic.values()))
    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("please enter symbol and/or share", 403)
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("please enter a positive number")
        total = 0
        for row in mine:
            if row[0] == symbol:
                total += row[1]
        if total < shares:
            return apology("There isn't enough shares", 403)
        rate = lookup(symbol)
        db.execute("INSERT INTO track (id, symbol, shares, price) VALUES (:id_, :symbol, :shares, :price);", id_ = session["user_id"], symbol = symbol,
                    shares = -shares, price = rate['price'])
        own = db.execute("SELECT cash FROM users WHERE id = :id_", id_ = int(session["user_id"]))
        own[0]['cash'] += shares * rate['price']
        db.execute("UPDATE users SET cash = :cash WHERE id = :id_", cash = own[0]['cash'], id_ = int(session["user_id"]))
        return redirect("/")
    else:
        symbol = db.execute("SELECT DISTINCT symbol FROM track WHERE id =:id_", id_ = session["user_id"])
        for row in symbol:
            count = db.execute("SELECT shares FROM track WHERE id =:id_ AND symbol = :symbol", id_ = session["user_id"], symbol = row['symbol'])
            total = 0
            total += sum(count[k]['shares'] for k in range(len(count)))
            if total == 0:
                symbol.remove(row)
        return render_template("sell.html", symbol = symbol)
    #return apology("TODO")

@app.route("/change", methods=["GET", "POST"])
@login_required
def newpassword():
    if request.method == "POST":
        if not request.form.get('old') or not request.form.get('password') or not request.form.get('confirmation'):
            return apology("please enter a valid passwords", 403)
        rows = db.execute("SELECT * FROM users WHERE id = :id_",
                          id_ = session["user_id"])
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("old")):
            return apology("invalid username and/or password", 403)
        if request.form.get("password") !=  request.form.get("confirmation"):
            return apology("your new password didn't match with confirmation password", 403)
        db.execute("UPDATE users SET hash = :hash_ WHERE id = :id_", hash_ = generate_password_hash(request.form.get("password")), id_ = session["user_id"])
        return redirect("/")
    else:
        return render_template("password.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
