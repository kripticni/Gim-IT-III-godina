SELECT korisnicko_ime
FROM korisnici
WHERE javna_addr = (SELECT javna_addr
                    FROM serveri
                    WHERE naziv='MojServer');
--koji su korisnici na mom serveru
