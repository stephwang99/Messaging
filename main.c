#include "header.h"
#define MY_PORT 60002

unsigned char key = 101;
unsigned counter = 87;
char SERVER_IP [] = "";
void encrypting(char*, int);
void setupServer();
void setupClient();

int main(int argc, char *argv[]){
  if(argc < 2){
    setupServer();
  }else{
    strcpy(SERVER_IP, argv[1]);
    setupClient();
  }
  return 0;
}
//Function:     setupClient()
//Purpose:      It sets up the socket for the client side, allows sending and receiving message.
//Parameter:    None
//Return:       None
void setupClient(){
    int mySocket;
    struct sockaddr_in  addr;
    int i, bytesRcv;
    char buffer[100];
    mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mySocket < 0) {
        printf("eek! couldn't open socket\n");
        exit(-1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr.sin_port = htons((unsigned short) MY_PORT);
    printf("Connecting to server...\n");
    i = connect(mySocket,(struct sockaddr *) &addr,sizeof(addr));
    if (i<0) {
        printf("client could not connect!\n");
        exit(-1);
    }
    printf("... connected\n");
    while (1) {
        int x = sending(buffer);
        encrypting(buffer, strlen(buffer));
        send(mySocket, buffer, strlen(buffer), 0);
        if(x)
            break;
        printf("\n... waiting to receive ...\n");
        bytesRcv = recv(mySocket, buffer, sizeof(buffer), 0);
        buffer[bytesRcv] = 0;
        received(buffer);
        //decrypting
        encrypting(buffer, bytesRcv);
        received(buffer);
        if(quit(buffer))
            break;
  } 
  close(mySocket);
}

//Function:     setupServer()
//Purpose:      It sets up the server side which also acts like a client, allowing sending and receiving messages.
//Parameters:   None
//Return:       None
void setupServer(){
    int myListenSocket, clientSocket;
    struct sockaddr_in myAddr, clientAddr;
    int i, addrSize, bytesRcv;
    char buffer[100];
    myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(myListenSocket < 0){
        printf("eek! couldn't open socket\n");
        exit(-1);
    }
    memset(&myAddr, 0, sizeof(myAddr));
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myAddr.sin_port = htons((unsigned short)MY_PORT);

    i = bind(myListenSocket, (struct sockaddr*) &myAddr, sizeof(myAddr));
    if(i < 0){
        printf("eek! couldn't bind socket\n");
        exit(-1);
    }
    i = listen(myListenSocket, 5);
    if(i < 0){
        printf("eek! couldn't listen\n");
        exit(-1);
    }
    printf("Waiting for connection request...\n");
    addrSize = sizeof(clientAddr);
    clientSocket = accept(myListenSocket,(struct sockaddr*)&clientAddr, &addrSize);
    if(clientSocket < 0){
        printf("eek! couldn't accept the connection\n");
        exit(-1);
    }
    printf("... connection accepted\n");
    printf("... waiting to receive ...\n");
    while(1){
        bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesRcv] = 0;
        received(buffer);
        //decrypting
        encrypting(buffer, bytesRcv);
        received(buffer);
        if(quit(buffer))
            break;
        int y = sending(buffer);
        encrypting(buffer, strlen(buffer));
        send(clientSocket, buffer, strlen(buffer),0);
        if(y)
            break;
        printf("\n... waiting to receive ...\n\n");
    }
    close(myListenSocket);
    close(clientSocket);
}
//Function:     encrypting()
//Purpose:      Uses the encrypt function to encrypt the message (also decrypt)
//Parameters:  
//      in-out: the message that needs to be encrypted/decrypted
//      return: none
void encrypting(char *buffer, int bytesRcv){
    unsigned char c;
    for(int i = 0; i < bytesRcv; i++){
        c = encrypt(counter, key);
        buffer[i] ^= c;
        counter++;
       // printf("the string is %s\n", buffer);
    }
}
