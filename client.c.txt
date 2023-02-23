/* Canhao UDP
   trabalho feito para a disciplina de redes II
   Alunos: Pedro Tricossi e Carlos Cichon
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */ 
#include <stdlib.h>

#define REMOTE_SERVER_PORT 5678 // porta para comunicacao
#define MAX_MSG 100
#define NUM_TESTE 620000 // numero de mensagens disparadas


int main(int argc, char *argv[]) {
  // testa a criacao do arquivo de log
  FILE *log = fopen("log_client", "w");
  if(!log) {
    printf("It was not possible to open client log file.\n");
    exit(1);
  }
  
  int sd, rc; // descritor do socket
  struct sockaddr_in cliAddr, remoteServAddr; //enderecos do cliente e servidor
  struct hostent *h; // dns
  int j=-1;
  long i=0;
  
  // pega os argumentos da linha de comando
  if(argc!=2) {
    printf("usage : %s <server> \n", argv[0]);
    exit(1);
  }

  // Ip do server e consulta a tabela de nomes
  h = gethostbyname(argv[1]);
  if(h==NULL) {
    fprintf(log, "%s: unknown host '%s' \n", argv[0], argv[1]);
    exit(1);
  }

  // Tabela de nomes funcionou
  fprintf(log, "%s: sending data to '%s' (IP : %s) \n", argv[0], h->h_name,

	inet_ntoa(*(struct in_addr *)h->h_addr_list[0]));

  //familia do endereco
  remoteServAddr.sin_family = h->h_addrtype;

  // copia o endereco do servidor que esta no dns para o endereco do servidor
  memcpy((char *) &remoteServAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);

  // conversao de little-endian em big-endian
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

  // Cria socket
  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) {
    fprintf(log, "%s: cannot open socket \n",argv[0]);
    exit(1);
  }
  
  // faz o bind
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);
  
  rc = bind(sd, (struct sockaddr *) &cliAddr, sizeof(cliAddr));

  // bind nao funcionou
  if(rc<0) {
    fprintf(log, "%s: cannot bind port\n", argv[0]);
    exit(1);
  }

  fprintf(log, "%s: binded successfully\n", argv[0]);



  // Envia os dados
  for(i=0;i<NUM_TESTE;i++) {
    rc = sendto(sd, &i, sizeof(int)+1, 0, (struct sockaddr *) &remoteServAddr, sizeof(remoteServAddr));
    fprintf(log, "%s: sent %ld to server\n", argv[0], i);

    if(rc<0) {
      fprintf(log, "%s: cannot send data %ld \n",argv[0],i-1);
      close(sd);
      exit(1);
    }
  }

  // Envia Fim de comunicacao
  for(int i=0;i<420;i++){    
    fprintf(log, "%s: sent end of comunication \n", argv[0]);
    rc = sendto(sd, &j, sizeof(int)+1, 0, (struct sockaddr *) &remoteServAddr, sizeof(remoteServAddr));
  }
  
  return 1;

}
