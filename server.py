import socket

localIP     = "200.17.202.34"
localPort   = 20001
bufferSize  = 1024
contador = 0
true_m = 0

msgFromServer       = "Hello UDP Client"

bytesToSend         = str.encode(msgFromServer)

# Create a datagram socket

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Bind to address and ip

UDPServerSocket.bind((localIP, localPort))

print("UDP server up and listening")

 

# Listen for incoming datagrams

while(true_m != 800007):

    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)


    message = bytesAddressPair[0]

    
    address = bytesAddressPair[1]
    
    true_m = int.from_bytes(message, "big")
    contador+=1

    clientMsg = "Message from Client:{}".format(true_m)
    clientIP  = "Client IP Address:{}".format(address)
    
    print(clientMsg)
    print(clientIP)

perdas  = 800000 - contador
print(f'a perda foi de: {perdas} mensagens')