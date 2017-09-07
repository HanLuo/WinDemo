#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024

void Error_Handling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET clnt_sock;
	SOCKADDR_IN clnt_addr;

	char message[BUF_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_Handling("WSAStartup() error!");

	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (clnt_sock == INVALID_SOCKET)
		Error_Handling("socket() error!");

	memset(&clnt_addr, 0, sizeof(clnt_addr));
	clnt_addr.sin_family = AF_INET;
	clnt_addr.sin_addr.s_addr = inet_addr(argv[1]);
	clnt_addr.sin_port = htons(atoi(argv[2]));


}

void Error_Handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}