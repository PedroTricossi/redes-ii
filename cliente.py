import socket


msgFromClient       = "Hello UDP Server"

bytesToSend         = str.encode(msgFromClient)

serverAddressPort   = ("200.17.202.34", 20001)

bufferSize          = 1024


# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Send to server using created UDP socket
for i in range(800000):
    # print(i)
    UDPClientSocket.sendto(i.to_bytes(10, 'big'), serverAddressPort)

for i in range(1000):
    i = 800007
    UDPClientSocket.sendto(i.to_bytes(10, 'big'), serverAddressPort)
