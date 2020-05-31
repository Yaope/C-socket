// server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include<string.h>
#include<WinSock2.h>
#include <iostream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include <sys/types.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
     /*加载winsock文件*/
//WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息

    //初始化WSA  
    WORD sockVersion = MAKEWORD(2, 0); //使用WINSOCK2版本
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)//第一个参数是WINSOCK 版本号,第二个参数是指向WSADATA的指针.
    {
        return 0;                               //该函数返回一个INT型值,通过检查这个值来确定初始化是否成功   
    }


    std::cout << "This is  server !" << std::endl;
    int slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//0：自动选择类型对应的默认协议
    if (slisten == -1)
    {
        std::cout << "socket error !";
        return 0;
    }

    //绑定ip地址和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;//参见in_addr结构
    //INADDR_ANY:转换过来就是0.0.0.0，泛指本机的意思，也就是表示本机的所有IP
    //当PC有多块网卡时，可以使用这个，只需管理一个套接字，便可以监听所有网卡端口号数据
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        std::cout<<"bind error !"<<std::endl;
    }

    //开始监听
    if (listen(slisten, 5) == SOCKET_ERROR)//slisten:要监听的socket描述字，5：相应的socket可以排队的最大连接数
    {
        std::cout << "listen error !";
        return 0;
    }

    SOCKET sClient;
    sockaddr_in clientAddr;
    int clientAddrlen = sizeof(clientAddr);
    while (true)
    {
        std::cout << "...listening" << std::endl;
        sClient = accept(slisten, (SOCKADDR*)&clientAddr, &clientAddrlen);
        if (sClient == INVALID_SOCKET)
        {
            std::cout << "accept error !";
            continue;
        }
        inet_ntoa(clientAddr.sin_addr);
        std::cout << "...connect" <<ntohs(clientAddr.sin_port)<< std::endl;

        //接收数据
        char buf[255];
        while (true)
        {
            memset(buf, 0, 255);//清空脏数据
            int len = recv(sClient, buf, 255, 0);
            buf[len] = '\0';
            if (strcmp(buf, "end" )==0)
            {
                std::cout << "...disconnect" << ntohs(clientAddr.sin_port) << std::endl;
                break;
            }
            std::cout << buf << std::endl;  
            
            //发送数据
            
            send(sClient, buf, strlen(buf), 0);
            
            
            /*char Data[255];*/
            /*std::cin >> Data;
            send(sClient, Data, strlen(Data), 0);*/
        }
        closesocket(sClient);
    }
    closesocket(slisten);
    WSACleanup();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
