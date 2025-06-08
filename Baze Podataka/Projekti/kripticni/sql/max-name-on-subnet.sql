SELECT MAX(korisnicko_ime) as "Najduze Ime", javna_addr, addr_mreze, serveri.naziv
FROM korisnici JOIN PODMREZE USING(javna_addr, addr_mreze)
               JOIN MREZE USING(javna_addr)
               JOIN SERVERI USING(javna_addr)
GROUP BY serveri.naziv, javna_addr, addr_mreze
HAVING MAX(LENGTH(korisnicko_ime)) > 5;
