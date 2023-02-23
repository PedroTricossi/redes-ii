'''
    Canhao UDP
    trabalho feito para a disciplina de redes II
    Alunos: Pedro Tricossi e Carlos Cichon
'''
import socket

localIP     = "200.17.202.34"
localPort   = 20001
bufferSize  = 1024
contador = 0
true_m = 0
MENSAGENS_ENVIADAS = 62000

# Cria socket datagram (mais facil que em C :))

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Faz o bind com IP

UDPServerSocket.bind((localIP, localPort))

print("UDP server up and listening")

 
# Escuta as mensagens do cliente :o

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

perdas  = MENSAGENS_ENVIADAS - contador
print(f'Foram enviadas {MENSAGENS_ENVIADAS} mensagens - Foram perdidas {perdas}')
print(f'Apenas {(1 - (perdas / MENSAGENS_ENVIADAS)) * 100}% das mensagens chegaram')