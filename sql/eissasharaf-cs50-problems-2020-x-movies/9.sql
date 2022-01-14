SELECT DISTINCT(name) FROM stars JOIN
people ON people.id = stars.person_id,
movies ON movies.id = stars.movie_id WHERE
movies.year = 2004 ORDER BY
people.birth;