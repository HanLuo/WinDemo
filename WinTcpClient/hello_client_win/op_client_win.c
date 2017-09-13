#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void Error_Handling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET clnt_sock;
	SOCKADDR_IN serv_addr;
	int opndCnt, i, result;

	char opmsg[BUF_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_Handling("WSAStartup() error!");

	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (clnt_sock == INVALID_SOCKET)
		Error_Handling("socket() error!");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	if (connect(clnt_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Error_Handling("connect() error!");

	fputs("operand count: ", stdout);
	scanf("%d", &opndCnt);
	opmsg[0] = (char)opndCnt;

	for (i = 0; i < opndCnt; i++)
	{
		printf("Operand: %d", i + 1);
		scanf("%d", (int*)&opmsg[i*OPSZ + 1]);
	}
	fgetc(stdin);
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opndCnt*OPSZ + 1]);
	send(clnt_sock, opmsg, opndCnt*OPSZ + 2, 0);
	recv(clnt_sock, &result, RLT_SIZE, 0);

	printf("Operation result: %d\n", result);
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