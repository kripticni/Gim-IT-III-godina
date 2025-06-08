CREATE TABLE mreze(
    javna_addr INT PRIMARY KEY CHECK(javna_addr BETWEEN 0 AND 4294967295)
);


CREATE TABLE serveri(
    javna_addr INT PRIMARY KEY CHECK(javna_addr BETWEEN 0 AND 4294967295),
    naziv VARCHAR(50) UNIQUE NOT NULL CHECK(LENGTH(naziv) BETWEEN 3 AND 50),
    port INT NOT NULL CHECK(port BETWEEN 0 AND 65535),
    FOREIGN KEY(javna_addr) REFERENCES mreze(javna_addr)
);

CREATE TABLE podmreze(
    javna_addr INT CHECK(javna_addr BETWEEN 0 AND 4294967295),
    addr_mreze INT CHECK(addr_mreze BETWEEN 0 AND 4294967295),
    broadcast_addr INT NOT NULL CHECK(broadcast_addr BETWEEN 0 AND 4294967295),
    gateway_addr INT NOT NULL CHECK(gateway_addr BETWEEN 0 AND 4294967295),
    FOREIGN KEY(javna_addr) REFERENCES mreze(javna_addr),
    PRIMARY KEY(javna_addr, addr_mreze)
);

CREATE TABLE korisnici(
    korisnicko_ime VARCHAR(20) PRIMARY KEY CHECK(LENGTH(korisnicko_ime) BETWEEN 3 AND 20),
    javna_addr INT NOT NULL CHECK(javna_addr BETWEEN 0 AND 4294967295),
    addr_mreze INT NOT NULL CHECK(addr_mreze BETWEEN 0 AND 4294967295),
    privatna_addr INT NOT NULL CHECK(privatna_addr BETWEEN 0 AND 4294967295),
    port INT NOT NULL CHECK(port BETWEEN 0 AND 65535),
    FOREIGN KEY(javna_addr, addr_mreze) REFERENCES podmreze(javna_addr, addr_mreze),
    FOREIGN KEY(korisnicko_ime) REFERENCES korisnici_podaci(korisnicko_ime)
);

CREATE TABLE korisnici_podaci(
    korisnicko_ime VARCHAR(20) PRIMARY KEY CHECK(LENGTH(korisnicko_ime) BETWEEN 3 AND 20),
    email VARCHAR(50) NOT NULL CHECK(email LIKE '%@%' AND LENGTH(email) BETWEEN 3 AND 50),
    broj_telefona VARCHAR(15) NOT NULL,
    profilna BLOB NOT NULL,
    -- hteo bih proveru za broj telefona i profilnu (manje od 2mb)
    -- ali ne postoji nacin koji radi i za sqlite i za oracle apex
    ime VARCHAR(50) NOT NULL CHECK(LENGTH(ime) BETWEEN 1 and 50),
    prezime VARCHAR(50) NOT NULL CHECK(LENGTH(prezime) BETWEEN 1 and 50),
    datum_rodjenja DATE NOT NULL,
    pol VARCHAR(1) NOT NULL CHECK(pol = 'm' OR pol = 'z' OR pol = 'n')
);

CREATE TABLE korisnici_verifikacije(
    korisnicko_ime VARCHAR(20) PRIMARY KEY CHECK(LENGTH(korisnicko_ime) BETWEEN 3 AND 20),
    hash_sifre VARCHAR(512) NOT NULL,
    hash_profila VARCHAR(512) NOT NULL,
    pgp_javni_kljuc BLOB NOT NULL,
    -- hteo bih i ovde proveru ali ponovo je postoji nacin
    FOREIGN KEY(korisnicko_ime) REFERENCES korisnici_podaci(korisnicko_ime)
);
