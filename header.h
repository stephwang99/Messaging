#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
//#define MY_PORT 60002
//char SERVER_IP [] = "127.0.0.1";
//unsigned char key = 101;
//unsigned char counter = 87;

//void setupClient();
//void setupServer();
//void encrypting(char[]);
int quit (char[]);
void received(char[]);
int sending (char[]);
