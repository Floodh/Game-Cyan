
#include "P2P.hpp"

using namespace std;

int pkgNumber = 0;

int* generatePkg()
{

    Message m{NULL};
    sendMessageQue.Consume(m);
    if (sendMessageQue.Size() == 0)
        sendMessageQue.Produce(Message{m.message});

    int* pkg = new int[PKGSIZE];

    pkg[0] = CLIENTNUMBER;
    pkg[1] = pkgNumber++;

    if (m.message != NULL)
        for (int i = 2; i < PKGSIZE / 8; i++)
            pkg[i] = m.message[i];

    cout << "pkg number = " << pkgNumber << endl;

    return pkg;
    
}


int clientThread()
{
    system("title UDP Client");

    // initialise winsock
    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    // create socket
    sockaddr_in server;
    int client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
        return 2;
    }

    // setup address structure
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);

    // start communication
    while (true)
    {
        char message[BUFLEN];

        Sleep(100);
        printf("Sending message: ");

        //cin.getline(message, BUFLEN);

        // send the message
        if (sendto(client_socket, (const char*)generatePkg(), PKGSIZE, 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }

        // receive a reply and print it
        // clear the answer by filling null, it might have previously received data
        char answer[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int slen = sizeof(sockaddr_in);
        int answer_length;
        if (answer_length = recvfrom(client_socket, answer, PKGSIZE, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }


        eventQueue.Produce(Message{answer});

    }

    closesocket(client_socket);
    WSACleanup();
}