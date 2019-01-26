#include <stdio.h>
#include <string.h>
//#include "header.h"

//Function:     quit()
//Purpose:      Checks for user input and see if the user wants to quit the chat.
//Parameter:
//      in:     The string the user inputted to check if it's "quit"
//      return: none
int quit(char str[]){
    if(strcmp(str,"quit") == 0)
        return 1;
    return 0;
}
//Function:     received()
//Purpose:      Outputs what has been received in a specific format
//Parameter:
//      in:     The string that is being received
//      return: none
void received(char buffer[]){
    printf("received-> %s\n", buffer);
}
//Function:     sending()
//Purpose:      Prompts the user for a message to send
//Parameter:    
//      in-out: The message that will be sent to the other user
//      return: boolean of whether to quit or not to quit
int sending (char buffer[]){
    char inStr[100];
    while(1){
        printf("Your msg-> ");
        fgets(inStr, sizeof(inStr),stdin);
        inStr[strlen(inStr)-1] = 0;
        strcpy(buffer, inStr);
        if(strlen(inStr) > 0)
            break;
    }
    return quit(inStr);
}
