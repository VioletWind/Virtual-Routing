#include "socket.h"
#include <stdlib.h>
#include <stdio.h>
#include <afxsock.h>
#include "stdafx.h"
#include <string>
#include <string.h>
using namespace std;
#define BUFFERSIZE 2048
int socketBind(int port)
{
	//create socket
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
	{
		perror("creat error\n");
		return -1;
	}

	//printf("create socket, fd: %d\n", fd);

	//build connection
	struct sockaddr_in siMe;
	memset((char *)&siMe, 0, sizeof(siMe));

	siMe.sin_family = AF_INET;
	siMe.sin_port = htons(port);
	//siMe.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", (void*)(&siMe.sin_addr.s_addr));
	int r = bind(fd, (struct sockaddr*)&siMe, sizeof(siMe));
	if (r == -1)
	{
		//perror("bind error\n");
		closesocket(fd);
		//int err = WSAGetLastError();
		//return err;
		return -1;
	}
	//printf("bind successfully!\n");
	return fd;

}

int socketSend(int fd, int port, std::string IP, std::string content)
{
	char *buf = new char[BUFFERSIZE];
	memset(buf, '\0', BUFFERSIZE);
	strcpy_s(buf, content.size() + 10, content.c_str());

	//build connection
	struct sockaddr_in siTo;
	memset((char *)&siTo, 0, sizeof(siTo));

	siTo.sin_family = AF_INET;
	siTo.sin_port = htons(port);
	//siTo.sin_addr.s_addr = inet_addr(IP.c_str());
	inet_pton(AF_INET, "127.0.0.1", (void*)(&siTo.sin_addr.s_addr));

	//printf("socketSend %s\n", buf);

	//send content
	int r = sendto(fd, buf, BUFFERSIZE - 1, 0, (struct sockaddr*)&siTo, sizeof(siTo));
	if (r == -1)
	{
		//perror("send error\n");
		//int err = WSAGetLastError();
		//return err;
		return -1;
	}
	return 0;
}

int socketReceive(int fd, std::string &content, std::string &IP)
{
	char *buf = new char[BUFFERSIZE];
	memset(buf, '\0', BUFFERSIZE);
	string tcontent;
	//build connection
	struct sockaddr_in siFrom;
	memset((char *)&siFrom, 0, sizeof(siFrom));

	//receive content
	socklen_t len = sizeof(siFrom);
	int r = recvfrom(fd, buf, BUFFERSIZE - 1, 0, (struct sockaddr *)&siFrom, &len);

	if (r > 0)
	{
		int port = ntohs(siFrom.sin_port);
		char IPBuf[BUFFERSIZE];
		inet_ntop(AF_INET, (void*)(&siFrom.sin_addr.s_addr), IPBuf, BUFFERSIZE);
		//read buffer
		string tIP(IPBuf);
		IP = tIP;
		tcontent = std::string(buf);
		content = tcontent;
		return port;
	}
	//perror("receive error\n");
	//int err = WSAGetLastError();
	//return err;
	return -1;

}
