
////////////////////////////////////////////////////////////////////////////////////////////////

INSERT INTO roles_privileges (roles_id, privileges_id)
SELECT DISTINCT roles_id, 20
FROM roles_privileges
WHERE privileges_id IN (13, 15) ;

////////////////////////////////////////////////////////////////////////////////////////////////

. . .
