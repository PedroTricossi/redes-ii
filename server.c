/*
  Canhao UDP
   trabalho feito para a disciplina de redes II
   Alunos: Pedro Tricossi e Carlos Cichon
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <stdlib.h>

#define LOCAL_SERVER_PORT 5678
#define MAX_MSG 100
#define NUM_TESTE 620001 // 62000 msgs + 1 de fim

int main(int argc, char *argv[]) {
  // testa a criacao do arquivo de log
  FILE *log = fopen("log_server", "w");
  if(!log) {
    printf("It was not possible to open server log file.\n");
    exit(1);
  }
  
  int sd, rc, n, cliLen;
  struct sockaddr_in cliAddr, servAddr;
  int msg;
  long i=0;
  long vetor_grande[NUM_TESTE];

  // Cria socket
  sd=socket(AF_INET, SOCK_DGRAM, 0);

  // testa criacao do socket
  if(sd<0) {
    fprintf(log, "%s: cannot open socket.\n",argv[0]);
    exit(1);
  }

  fprintf(log, "%s: socket openned successfully.\n",argv[0]);

  // Faz bind
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));

  // bind nao funcionou
  if(rc<0) {
    fprintf(log, "%s: cannot bind port number %d \n", 
	  argv[0], LOCAL_SERVER_PORT);
    exit(1);
  }

  // bind funcionou
  fprintf(log, "%s: port number %d binded successfully\n", 
  argv[0], LOCAL_SERVER_PORT);


  fprintf(log, "%s: waiting for data on port UDP %u\n", 
	   argv[0],LOCAL_SERVER_PORT);

  // Servidor escuta as mensagens do cliente, enquanto não receber a msg -1
  while(msg != -1) {
    cliLen = sizeof(cliAddr);
    n = recvfrom(sd, &msg, sizeof(int)+1, 0, 
		(struct sockaddr *) &cliAddr, &cliLen);

    // nao recebeu os dados
    if(n<0) {
      fprintf(log, "%s: cannot receive data \n",argv[0]);
      continue;
    }

    //recebeu
    fprintf(log, "%s: %d received \n",argv[0], msg);

    vetor_grande[i] = msg;
    // incrementa a quantidade de mensagens recebidas
    i++;
  }

  // mostra os dados da análise
  double div = ((i / (double) NUM_TESTE) -1) * -100;

  printf("[INFO] O cliente enviou %d mensagens! \n", NUM_TESTE);
  printf("[INFO] O servidor recebeu %ld mensagens! \n", i);
  printf("[INFO] Foram perdidas %ld mensagens!!! \n", (NUM_TESTE - i));
  printf("[INFO] Foram perdidas %.2f%s mensagens!!! \n", div, "%");

  return 0;
}
