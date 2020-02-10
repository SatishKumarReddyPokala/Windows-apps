#include<iostream>
#include<WS2tcpip.h>
#include<string>

#define SUCCESS 0

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{

	//initialize winsock
	WSAData wsadata;	//winsock structure to initialize
	WORD ver = MAKEWORD(2, 2);

	int Winsock = WSAStartup(ver, &wsadata);
	if (Winsock != SUCCESS)
	{
		cout << "Failed to initialize occured\n";
		return 1;
	}

	//create socket

	SOCKET Ssocket = socket(AF_INET, SOCK_STREAM, 0);
	if (Ssocket == INVALID_SOCKET)
	{
		cout << "failed to create socket\n";
		return 1;
	}

	//bind socket with IP and  port
	sockaddr_in soaddr;
	soaddr.sin_family = AF_INET;
	soaddr.sin_port = htons(48000);//host to network short
	soaddr.sin_addr.S_un.S_addr = INADDR_ANY;	//bind to any address
	if (bind(Ssocket, (sockaddr *)&soaddr, sizeof(soaddr)) != SUCCESS)
	{
		cout << "failed to bind socket\n";
		return 1;
	}

	//listening socket
	if(listen(Ssocket, SOMAXCONN) != SUCCESS)	//backlog : The maximum length of the queue of pending connections
	{
		cout << "failed to listen socket\n";
		return 1;
	}

	//Wait for connection
	sockaddr_in client;
	int Csize = sizeof(client);

	SOCKET Csocket = accept(Ssocket, (sockaddr *)&client, &Csize);
	if (Csocket == INVALID_SOCKET)
	{
		cout << "failed to create socket\n";
		return 1;
	}
	char cname[NI_MAXHOST];
	memset(cname, 0, NI_MAXHOST);
	inet_ntop(AF_INET, &client.sin_addr, cname, NI_MAXHOST);

	cout << cname << "connected port number is" << ntohs(client.sin_port)<<endl;

	//close listing socket
	closesocket(Ssocket);

	//while loop accept message and eco back to client
	char data[5000];
	while (1)
	{
		memset(data, 0, 5000);
		int recevcount = recv(Csocket, data, 5000, 0);
		if (recevcount == SOCKET_ERROR)
		{
			cout << "failed to receive data\n";
			break;
		}
		if (recevcount == 0)
		{
			cout << "disconnected" << endl;
			break;
		}
		cout <<"CLIENT : "<< string(data, 0, recevcount)<<endl;
		string InpuT;
		cout << ">";
		getline(cin, InpuT);
		send(Csocket, InpuT.c_str(), InpuT.size() + 1, 0);

	}

	//close socket
	closesocket(Csocket);

	//shutdown winsock
	WSACleanup();

	system("pause");

	return 0;
}