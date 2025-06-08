SELECT SUBSTR(korisnicko_ime, 1, 2) || 
       SUBSTR(korisnici_podaci.email, 1, 2) ||
       SUBSTR(korisnici_podaci.ime, 1, 2) ||
       SUBSTR(korisnici_podaci.prezime, 1, 2) ||
       SUBSTR(serveri.naziv, 1, 2) as "Identifikator"
FROM korisnici JOIN korisnici_podaci USING (korisnicko_ime)
               JOIN podmreze USING (javna_addr)
               JOIN mreze USING (javna_addr)
               JOIN serveri USING (javna_addr)
