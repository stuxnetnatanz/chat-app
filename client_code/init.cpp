#include "client.h"

void Connect(int &sockFD, sockaddr_in &servAddr) {

    if(connect(sockFD, (sockaddr*)&servAddr, sizeof(servAddr)) < 0)
        print_error("Connect Error");
}

void connect_to_server(int &sockFD, sockaddr_in &servAddr, int argc, const char * argv[]) {

    char serverIP[17];
    int port;
    Socket(sockFD);

    bzero(&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;

    if(argc < 2) {
        cout << "Enter Port: ";
        cin >> port;
    }
    else
        port = atoi(argv[1]);

    if(argc < 3) {
        cout << "Enter ip: ";
        cin >> serverIP;
    }
    else
        strcpy(serverIP,argv[2]);

    int x = inet_pton(AF_INET, serverIP, &(servAddr.sin_addr));
    if(!x)
        print_error("Invalid IP address");
    if(x == -1)
        print_error("inet_pton Error");

    servAddr.sin_port = htons(port);

    Connect(sockFD, servAddr);
    cout << setw(atoi(getenv("COLUMNS"))/2 - 4) << green << bold << "CONNECTED" << regular << setw(0) << endl;
}
