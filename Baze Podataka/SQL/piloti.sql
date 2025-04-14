CREATE TABLE piloti(
    id_pil NUMBER(3) PRIMARY KEY,
    ime_pil VARCHAR2(30) NOT NULL,
    god_let NUMBER(2),
    god_star NUMBER(2)
);
CREATE TABLE putnici(
    id_pu NUMBER(3) PRIMARY KEY,
    ime_pu VARCHAR(30) NOT NULL
);
CREATE TABLE letovi(
    id_le NUMBER(3),
    id_pu NUMBER(3) NOT NULL REFERENCES putnici(id_pu),
    d_let DATE,
    id_pil NUMBER(3) NOT NULL REFERENCES piloti(id_pil),
    pol_a VARCHAR(20),
    odr_a VARCHAR(20),
    PRIMARY KEY(id_pil,id_pu)
);

INSERT INTO piloti(id_pil, ime_pil, god_let, god_star)
VALUES(11,'Petar Peric',10,35);

INSERT INTO piloti(id_pil, ime_pil, god_let, god_star)
VALUES(12,'Marko Makic',9,33);

INSERT INTO putnici(id_pu, ime_pu)
VALUES(15, 'Jovan Jovic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(16, 'Petar Mitic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(17, 'Vesna Jovic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(18, 'Dragan Savic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(19, 'Milica Stevic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(105, 'Jelena Misic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(106, 'Mara Vasic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(107, 'Desa Stosic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(108, 'Mila Ristic');

INSERT INTO putnici(id_pu, ime_pu)
VALUES(109, 'Vera Tonic');
