#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void Error_Handling(char *message);

int main(int argc, char *argv[])
{
	SOCKET clnt_sock, serv_sock;
	SOCKADDR_IN clnt_addr, serv_addr;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == INVALID_SOCKET)
		Error_Handling("socket() error!");


}

void Error_Handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}