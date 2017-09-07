#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024

void Error_Handling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET clnt_sock, serv_sock;
	SOCKADDR_IN clnt_addr, serv_addr;
	int sock_len;
	int length;

	char message[BUF_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_Handling("WSAStartup() error!");

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == INVALID_SOCKET)
		Error_Handling("socket() error!");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == -1)
		Error_Handling("bind() error!");

	if (listen(serv_sock, 5) == -1)
		Error_Handling("listen() error!");

	for (int i = 0; i <= 5; i++)
	{
		sock_len = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &sock_len);
		if (clnt_sock == -1)
			Error_Handling("accept() error!");

		printf("clnt_sock:%d\n", clnt_sock);

		while (length = recv(clnt_sock, message, BUF_SIZE, 0))
			send(clnt_sock, message, length, 0);

		closesocket(clnt_sock);
	}
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