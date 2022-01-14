SELECT title FROM stars JOIN
movies ON stars.movie_id = movies.id,
people ON people.id = stars.person_id,
ratings ON ratings.movie_id = stars.movie_id WHERE
 people.name = "Chadwick Boseman" ORDER BY
 ratings.rating DESC LIMIT 5;