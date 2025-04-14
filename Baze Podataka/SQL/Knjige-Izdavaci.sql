-- AUTORI(id_aut, ime, pre)
-- IZDAVACI(id_izd, naz, grad, adr, sajt)
-- KNJIGE(id_knj, naz, id_izd)
-- AUTORI_KNJIGE(id_aut, id_knj)

--napisati upiti kojim se prikazuje autor knjiga i nazivi njenog izdavaca
SELECT knjige.naz AS 'naziv knjiga', izdavaci.naz AS "naziv izdavaca"
FROM IZDAVACI JOIN KNJIGE ON (knjige.id_izd = izdavaci.id_izd)

--...nastavak samo ako je naziv izdavaca "cet" i sortirati po nazivu knjiga
SELECT knjige.naz AS 'naziv knjiga', izdavaci.naz AS "naziv izdavaca"
FROM IZDAVACI JOIN KNJIGE ON (knjige.id_izd = izdavaci.id_izd)
WHERE izdavaci.naz = 'cet'
ORDER BY knjige.naz

--napisati upit kojim se prikazuju nazivi knjiga ciji je jedan od autora
--djurisic

