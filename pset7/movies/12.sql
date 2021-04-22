SELECT movies.title from movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Helena Bonham Carter"
AND movies.title IN(SELECT movies.title from movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Johnny Depp");