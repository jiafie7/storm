import socket
import struct


def send_data(client, data):
    cmd = 1
    data_len = len(data)
    data = struct.pack(f"HH{data_len}s", cmd, data_len, data.encode("utf-8"))
    client.send(data)
    info = client.recv(1024).decode()
    print(info)


if __name__ == "__main__":

    host = "127.0.0.1"
    port = 7777

    client = socket.socket()  # create socket
    client.connect((host, port))  # connect to server
    send_data(client, "hello")
    client.close()
