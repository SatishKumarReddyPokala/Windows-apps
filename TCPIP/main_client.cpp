#include<iostream>
#include<string>
#include<WS2tcpip.h>

#define SUCCESS 0

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	string ipAddr = "192.168.42.102";	//server IP
	int portnum = 48000;			//server listening port

	//initialize winsock
	WSAData wsadata;
	WORD ver = MAKEWORD(2, 2);

	int Winsock = WSAStartup(ver, &wsadata);
	if (Winsock != SUCCESS)
	{
		cout << "Failed to initialize occured\n";
		return 1;
	}

	//create socket
	SOCKET Csocket = socket(AF_INET, SOCK_STREAM, 0);
	if (Csocket == INVALID_SOCKET)
	{
		cout << "failed to create socket\n";
		return 1;
	}

	//Fill in a hint structure
	sockaddr_in soaddr;
	soaddr.sin_family = AF_INET;
	soaddr.sin_port = htons(48000);			//host to network short
	inet_pton(AF_INET, ipAddr.c_str(), &soaddr.sin_addr);

	//connect to server
	if (connect(Csocket, (sockaddr *)&soaddr, sizeof(soaddr)) == SOCKET_ERROR)
	{
		cout << "failed to connect socket\n";
		closesocket(Csocket);
		return 1;
	}

	//loop for send and receive data
	char recedata[5000];
	string InpuT;

	do
	{
		//prompt to enter text
		cout << ">";
		getline(cin, InpuT);

		//send the text
		if (send(Csocket, InpuT.c_str(), InpuT.size() + 1, 0) == SOCKET_ERROR)
		{
			memset(recedata, 0, 5000);
		}
		int recvcount = recv(Csocket, recedata, 5000, 0);
		if (recvcount > 0)
		{
			cout << "SERVER : " << string(recedata, 0, recvcount) << endl;
		}
	} while (InpuT.size() > 0);

	//close socket
	closesocket(Csocket);
	WSACleanup();

	system("pause");
}
