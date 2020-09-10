SELECT title FROM movies WHERE movies.id IN
(SELECT stars.movie_id FROM stars WHERE person_id =136 INTERSECT SELECT stars.movie_id FROM stars WHERE person_id =307)