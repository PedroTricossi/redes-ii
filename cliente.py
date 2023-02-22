'''
    Canhao UDP
    trabalho feito para a disciplina de redes II
    Alunos: Pedro Tricossi e Carlos Cichon
'''
import socket

serverAddressPort   = ("200.17.202.34", 20001)

# Cria socket UDP
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Envia 800000 mensagens para o servidor
for i in range(800000):
    # print(i)
    UDPClientSocket.sendto(i.to_bytes(10, 'big'), serverAddressPort)

# Envia mensagem de termino
for i in range(1000):
    i = 800007
    UDPClientSocket.sendto(i.to_bytes(10, 'big'), serverAddressPort)
