#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define OPSZ 4

void Error_Handling(char *message);
int calculate(int opnum, int opnds[], char oprator);


int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET serv_sock, clnt_sock;
	SOCKADDR_IN serv_addr, clnt_addr;
	int clntAdrSize;
	int result, opndCnt;
	int recvCnt, recvLen;

	char opinfo[BUF_SIZE];

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

	while (1)
	{
		fputs("accetp data", stdout);
		clntAdrSize = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &clntAdrSize);
		printf("clnt_sock: %d", clnt_sock);
		if (clnt_sock == -1)
			Error_Handling("accept() error!");

		opndCnt = 0;
		recv(clnt_sock, (char*)&opndCnt, 1, 0);

		recvLen = 0;
		while ((opndCnt*OPSZ + 1) > recvLen)
		{
			recvCnt = recv(clnt_sock, &opinfo[recvLen], BUF_SIZE - 1, 0);
			recvLen += recvCnt;
		}
		result = calculate(opndCnt, (int*)opinfo, opinfo[recvLen - 1]);
		send(clnt_sock, (char*)&result, sizeof(result), 0);
		closesocket(clnt_sock);
	}
	closesocket(serv_sock);
	WSACleanup();
	return 0;
}

int calculate(int opnum, int opnds[], char oprator)
{
	int result = 0, i = 0;
	switch (oprator)
	{
	case '+':
		for (i = 0; i < opnum; i++)
			result = opnds[i];
		break;
	}
	
	return result;

}

void Error_Handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}