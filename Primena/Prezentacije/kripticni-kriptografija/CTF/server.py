import socket

HOST = ""
PORT = 50007
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    print("Host: ", socket.gethostbyname(""))
    print("On port: ", PORT)
    s.listen(1)
    conn, addr = s.accept()
    with conn:
        print("Connected by", addr)
        conn.sendall("Posalji sha256 hash od originalnog fajla\n".encode())

        while True:
            data = conn.recv(1024)
            if data.decode().startswith(
                "354bb4917d965e7c573c3ee659da2ae6f10cbbd864a1178afc183588d5db6f39"
            ):
                conn.sendall(
                    "GimCTF{usp3s4n_uv0d_u_kr1pt0gr4f1ju_2025_kripticni}".encode()
                )
            if not data:
                break
s.close()
exit()
