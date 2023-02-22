/* fpont 12/99 */
/* pont.net    */
/* udpServer.c */

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
#define NUM_TESTE 620000

int main(int argc, char *argv[]) {
  
  int sd, rc, n, cliLen;
  struct sockaddr_in cliAddr, servAddr;
  int msg;
  long i=0;
  long vetor_grande[NUM_TESTE];



  sd=socket(AF_INET, SOCK_DGRAM, 0);

  if(sd<0) {
    printf("%s: cannot open socket \n",argv[0]);
    exit(1);
  }

  /* bind local server port */
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
  if(rc<0) {
    printf("%s: cannot bind port number %d \n", 
	   argv[0], LOCAL_SERVER_PORT);
    exit(1);
  }

  printf("%s: waiting for data on port UDP %u\n", 
	   argv[0],LOCAL_SERVER_PORT);

  /* server infinite loop */
  while(msg != -1) {
   //if (setsockopt (sd, SOL_SOCKET, SO_RCVTIMEO, &tv,
     //        sizeof tv) < 0)
      //break;

    /* receive message */
    cliLen = sizeof(cliAddr);
    n = recvfrom(sd, &msg, sizeof(int)+1, 0, 
		 (struct sockaddr *) &cliAddr, &cliLen);

    if(n<0) {
      printf("%s: cannot receive data \n",argv[0]);
      continue;
    }

    vetor_grande[i] = msg;  

    i++;

  }

  double div = ((i / (double) NUM_TESTE) -1) * -100;

  printf("[INFO] O cliente enviou %d mensagens! \n", NUM_TESTE);
  printf("[INFO] O servidor recebeu %d mensagens! \n", i);
  printf("[INFO] Foram perdidas %d mensagens!!! \n", (NUM_TESTE - i));
  printf("[INFO] Foram perdidas %.2f%s mensagens!!! \n", div, "%");

  return 0;
}
