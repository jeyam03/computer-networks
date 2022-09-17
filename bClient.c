#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    exit(1);
  }
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  while(1){
	// Agent ID
	  bzero(buffer, 1024);
	  recv(sock, buffer, sizeof(buffer), 0);
	  printf("Server: %s\n", buffer);
	// Give Agent ID
	  bzero(buffer, 1024);
	  char name[20];
	  scanf("%s", name);
	  strcpy(buffer, name);
	  printf("\nClient: %s\n", buffer);
	  send(sock, buffer, strlen(buffer), 0);
	// How many tickets?
	  bzero(buffer, 1024);
	  recv(sock, buffer, sizeof(buffer), 0);
	  printf("\nServer: %s\n", buffer);
	// Give number of tickets
	  int numOfTickets;
	  scanf("%d", &numOfTickets);
	  printf("\nClient: %s\n", buffer);
	  send(sock, &numOfTickets, sizeof(int), 0);
	// Price of one tickets
	  bzero(buffer, 1024);
	  recv(sock, buffer, sizeof(buffer), 0);
	  printf("\nServer: %s\n", buffer);
	  break;
  }

  close(sock);
  printf("Disconnected from the server.\n");

  return 0;

}