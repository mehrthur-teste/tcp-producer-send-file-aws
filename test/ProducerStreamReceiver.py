import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 9001

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"Consumer listening on {UDP_IP}:{UDP_PORT}")

while True:
    data, addr = sock.recvfrom(4096)
    message = data.decode()
    print(f"Received: {message}")

    if ':' in message:
        seq_num = message.split(':', 1)[0]
        ack = f"ACK:{seq_num}".encode()
        sock.sendto(ack, addr)
        print(f"Sent ACK:{seq_num}")