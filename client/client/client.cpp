#include<WinSock2.h>
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<string>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
	//初始化
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	//建立套接字结构
	cout << "This is Client !" << endl;
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == -1)
	{
		cout << "socket error !" << endl;
		return 0;
	}

	//连接connect
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(sclient,(struct sockaddr*)&serAddr,sizeof(serAddr))<0)
	{
		cout << "Connect error !" << endl;
		return 0;
	}
	std::cout << "...connect" << std::endl;
	char buf[255];
	char Data[255];
	while (true)
	{
		cin >> buf;
		send(sclient, buf, strlen(buf), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)flags一般设0
		if (strcmp(buf, "end") == 0) {
			cout << "...disconnect" << endl;
			break;
		}
		memset(Data, 0, sizeof(Data));
		recv(sclient, Data, sizeof(Data), 0);
		cout << Data << endl;
	}

}