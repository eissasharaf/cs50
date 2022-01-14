SELECT DISTINCT(name) FROM directors JOIN
people ON people.id = directors.person_id,
ratings ON ratings.movie_id = directors.movie_id WHERE
ratings.rating >= 9.0 ;
