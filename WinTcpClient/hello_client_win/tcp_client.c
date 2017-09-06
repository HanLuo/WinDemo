#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void Error_Handling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;

	SOCKET clnt_sock;
	SOCKADDR_IN serv_addr;

	char message[30];

	int count = 0, index = 0, length = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_Handling("WSAStartup error!");

	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (clnt_sock == INVALID_SOCKET)
		Error_Handling("socket() error!");

	memset(&serv_addr, 0, sizeof(serv_addr));// Ìî³äsin_zero
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(clnt_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == -1)
		Error_Handling("connect() error!");

	while (length = recv(clnt_sock, &message[index++], 1, 0))
	{
		if (length == -1)
			Error_Handling("recv() error!");
		count += length;
	}

	printf("Function Call : %d\n", count);
	printf("Message length: %d\n", count);

	closesocket(clnt_sock);
	WSACleanup();

	return 0;
}

void Error_Handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}