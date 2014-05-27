/*
SERVER
*/
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "definitions.h"

#define MAX_ROOMS 10

typedef struct Room_struct{
    char name[41];
    int active;
} Room;

typedef struct Users_struct{
    char nickname[41];
    int socket;
    Room *room;
} User;