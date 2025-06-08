--prvi red
INSERT INTO mreze (javna_addr) VALUES (1234567890);

INSERT INTO podmreze (javna_addr, addr_mreze, broadcast_addr, gateway_addr)
VALUES (1234567890, 100, 1234567999, 1234567891);

INSERT INTO korisnici_podaci (korisnicko_ime, email, broj_telefona, profilna, ime, prezime, datum_rodjenja, pol)
VALUES ('korisnik1', 'korisnik@example.com', '0641234567', HEXTORAW('89504E470D0A1A0A0000000D49484452'), 'Marko', 'Markovic', TO_DATE('1990-05-15', 'YYYY-MM-DD'), 'm');

INSERT INTO korisnici_verifikacije (korisnicko_ime, hash_sifre, hash_profila, pgp_javni_kljuc)
VALUES ('korisnik1', 'abc123hashsifre', 'def456hashprofila', HEXTORAW('1234567890ABCDEF'));

INSERT INTO korisnici (korisnicko_ime, javna_addr, addr_mreze, privatna_addr, port)
VALUES ('korisnik1', 1234567890, 100, 19216811, 5000);

INSERT INTO serveri (javna_addr, naziv, port)
VALUES (1234567890, 'MojServer', 8080);

-- ostala 4 reda
INSERT INTO mreze (javna_addr) VALUES (1234567891);
INSERT INTO mreze (javna_addr) VALUES (1234567892);
INSERT INTO mreze (javna_addr) VALUES (1234567893);
INSERT INTO mreze (javna_addr) VALUES (1234567894);

INSERT INTO podmreze (javna_addr, addr_mreze, broadcast_addr, gateway_addr)
VALUES (1234567891, 101, 1234567999, 1234567892);

INSERT INTO podmreze (javna_addr, addr_mreze, broadcast_addr, gateway_addr)
VALUES (1234567892, 102, 1234567998, 1234567893);

INSERT INTO podmreze (javna_addr, addr_mreze, broadcast_addr, gateway_addr)
VALUES (1234567893, 103, 1234567997, 1234567894);

INSERT INTO podmreze (javna_addr, addr_mreze, broadcast_addr, gateway_addr)
VALUES (1234567894, 104, 1234567996, 1234567895);

INSERT INTO korisnici_podaci (korisnicko_ime, email, broj_telefona, profilna, ime, prezime, datum_rodjenja, pol)
VALUES ('korisnik2', 'korisnik2@example.com', '0641234568', HEXTORAW('89504E470D0A1A0A0000000D49484453'), 'Ana', 'Petrovic', TO_DATE('1992-07-21', 'YYYY-MM-DD'), 'z');

INSERT INTO korisnici_podaci (korisnicko_ime, email, broj_telefona, profilna, ime, prezime, datum_rodjenja, pol)
VALUES ('korisnik3', 'korisnik3@example.com', '0641234569', HEXTORAW('89504E470D0A1A0A0000000D49484454'), 'Ivan', 'Jovanovic', TO_DATE('1988-12-10', 'YYYY-MM-DD'), 'm');

INSERT INTO korisnici_podaci (korisnicko_ime, email, broj_telefona, profilna, ime, prezime, datum_rodjenja, pol)
VALUES ('korisnik4', 'korisnik4@example.com', '0641234570', HEXTORAW('89504E470D0A1A0A0000000D49484455'), 'Jelena', 'Nikolic', TO_DATE('1995-03-30', 'YYYY-MM-DD'), 'z');

INSERT INTO korisnici_podaci (korisnicko_ime, email, broj_telefona, profilna, ime, prezime, datum_rodjenja, pol)
VALUES ('korisnik5', 'korisnik5@example.com', '0641234571', HEXTORAW('89504E470D0A1A0A0000000D49484456'), 'Marko', 'Ilic', TO_DATE('1991-11-05', 'YYYY-MM-DD'), 'm');

INSERT INTO korisnici_verifikacije (korisnicko_ime, hash_sifre, hash_profila, pgp_javni_kljuc)
VALUES ('korisnik2', 'abc124hashsifre', 'def457hashprofila', HEXTORAW('1234567890ABCDE0'));

INSERT INTO korisnici_verifikacije (korisnicko_ime, hash_sifre, hash_profila, pgp_javni_kljuc)
VALUES ('korisnik3', 'abc125hashsifre', 'def458hashprofila', HEXTORAW('1234567890ABCDE1'));

INSERT INTO korisnici_verifikacije (korisnicko_ime, hash_sifre, hash_profila, pgp_javni_kljuc)
VALUES ('korisnik4', 'abc126hashsifre', 'def459hashprofila', HEXTORAW('1234567890ABCDE2'));

INSERT INTO korisnici_verifikacije (korisnicko_ime, hash_sifre, hash_profila, pgp_javni_kljuc)
VALUES ('korisnik5', 'abc127hashsifre', 'def460hashprofila', HEXTORAW('1234567890ABCDE3'));

INSERT INTO korisnici (korisnicko_ime, javna_addr, addr_mreze, privatna_addr, port)
VALUES ('korisnik2', 1234567891, 101, 19216812, 5001);

INSERT INTO korisnici (korisnicko_ime, javna_addr, addr_mreze, privatna_addr, port)
VALUES ('korisnik3', 1234567892, 102, 19216813, 5002);

INSERT INTO korisnici (korisnicko_ime, javna_addr, addr_mreze, privatna_addr, port)
VALUES ('korisnik4', 1234567893, 103, 19216814, 5003);

INSERT INTO korisnici (korisnicko_ime, javna_addr, addr_mreze, privatna_addr, port)
VALUES ('korisnik5', 1234567894, 104, 19216815, 5004);

INSERT INTO serveri (javna_addr, naziv, port)
VALUES (1234567891, 'Server2', 8081);

INSERT INTO serveri (javna_addr, naziv, port)
VALUES (1234567892, 'Server3', 8082);

INSERT INTO serveri (javna_addr, naziv, port)
VALUES (1234567893, 'Server4', 8083);

INSERT INTO serveri (javna_addr, naziv, port)
VALUES (1234567894, 'Server5', 8084);
