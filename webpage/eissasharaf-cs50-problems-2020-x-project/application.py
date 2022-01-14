from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)
db = SQL("sqlite:///users.db")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/resturants")
def resturants():
    return render_template("Resturants.html")

@app.route("/homemade")
def homemade():
    return render_template("homemade.html")

@app.route("/aboutus", methods=["GET", "POST"])
def aboutus():
    if request.method == "POST":
        if not request.form.get('name') or not request.form.get('mail'):
            return "<h1>INVALID<h/1>"
        db.execute("INSERT INTO new (name, mail) VALUES(:name, :mail);", name = request.form.get('name'), mail = request.form.get('mail'))
        return redirect("/")
    else:
        return render_template("aboutus.html")
