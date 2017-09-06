#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void Error_Handling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;

	SOCKET serv_sock;
	SOCKET clnt_sock;

	SOCKADDR_IN serv_addr;
	SOCKADDR_IN clnt_addr;

	char message[] = "Hello World!";
	
	int clnt_size;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_Handling("WSAStartup() error!");

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == INVALID_SOCKET)
		Error_Handling("socket() error!");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Error_Handling("bind() error!");

	if (listen(serv_sock, 5) == SOCKET_ERROR)
		Error_Handling("listen() error!");

	clnt_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &clnt_size);
	if (clnt_sock == INVALID_SOCKET)
		Error_Handling("accept() error!");

	send(clnt_sock, message, sizeof(message), 0);

	closesocket(clnt_sock);
	closesocket(serv_sock);
	WSACleanup();
	return 0;

}

void Error_Handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}