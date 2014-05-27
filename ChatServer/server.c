#include "server.h"

//set of socket descriptors
fd_set readfds;

int sendDataObject(int type, int id, char message[], char* nickname, int socket){
    Data dt;
    unsigned char buffer[2048];

    dt.type = type;
    dt.id = id;
    strcpy(dt.message, message);

    if(nickname == NULL)
        dt.nickname[0] = '\0';
    else
        strcpy(dt.nickname, nickname);

    memcpy(&buffer, &dt, sizeof(dt));
    if(socket != 0){
        if( send(socket, buffer, sizeof(buffer), 0) != sizeof(buffer) )
        {
            perror("send DataObject");
        }
    }
}

int checkType(char* buffer){
    int isCommand = IS_MESSAGE;
    char copyBuffer[BUFSIZE];
    char * tok;

    strcpy(copyBuffer, buffer);

    tok = strtok(copyBuffer, " ");
    if(strcmp(tok , CMD_CHANGE_NICK) == 0 || strcmp(tok , CMD_CHANGE_NICK_END) == 0){
        isCommand = IS_CHANGENICK;
    }
    else if(strcmp(tok , CMD_CREATE_ROOM) == 0 || strcmp(tok , CMD_CREATE_ROOM_END) == 0){
        isCommand = IS_CREATEROOM;
    }
    else if(strcmp(tok , CMD_JOIN_ROOM) == 0 || strcmp(tok , CMD_JOIN_ROOM_END) == 0){
        isCommand = IS_JOINROOM;
    }
    else if(strcmp(tok , CMD_LEAVE_ROOM) == 0 || strcmp(tok , CMD_LEAVE_ROOM) == 0){
        isCommand = IS_LEAVEROOM;
    }
    return isCommand;
}

void changeNick(char* buffer, User *usr){
    char *tok;
    tok = strtok(buffer, " ");
    tok = strtok(NULL, " ");
    if(tok != NULL){
        strcpy(usr->nickname, tok);
        usr->nickname[40] = '\0';
        sendDataObject(TYPE_CONFIRM, 0, CONFIRM_MESSAGE, NULL, usr->socket);
    }
    else{
        sendDataObject(TYPE_ERROR, 0, "Erro ao utilizar o comando \\nick. Usage: \\nick new_nick", NULL, usr->socket);
    }
}

void multicastReceived(char buffer[], int sender, User clients[], int maxClients){
    int i;
    User usr;
    Data dt;
    for (i = 0; i < maxClients; ++i)
    {
        if(sender != i){
            usr = clients[i];
            if(usr.room == NULL)
                sendDataObject(TYPE_MESSAGE, sender, buffer, clients[sender].nickname, usr.socket);
        }
    }
}

void roomMessageReceived(char buffer[], int sender, User clients[], int maxClients){
    int i;
    User usr;
    Room *rm;
    Data dt;

    rm = clients[sender].room;

    for (i = 0; i < maxClients; ++i)
    {
        if(sender != i){
            usr = clients[i];
            if(usr.room == rm)
                sendDataObject(TYPE_MESSAGE, sender, buffer, clients[sender].nickname, usr.socket);
        }
    }
}

void joinRoom(char *buffer, User *usr, Room *rooms){
    int i, exists;
    char *tok;
    tok = strtok(buffer, " ");
    tok = strtok(NULL, " ");
    if(tok != NULL){
        exists = 0;
        for(i = 0; i< MAX_ROOMS; i++, rooms++){
            if(rooms->active){
                if(strcmp(rooms->name, tok) == 0){
                    exists = 1;
                    usr->room = rooms;
                    break;
                }
            }
        }
        if(exists){
                sendDataObject(TYPE_CONFIRM, 0, CONFIRM_MESSAGE, NULL, usr->socket);
        }
        else{
            sendDataObject(TYPE_ERROR, 0, "Erro ao utilizar o comando \\join. Room nao existe", NULL, usr->socket);
        }
    }
    else{
        sendDataObject(TYPE_ERROR, 0, "Erro ao utilizar o comando \\join. Usage: \\join room_name", NULL, usr->socket);
    }
}

void createRoom(char *buffer, User *usr, Room *rooms){
    int i, alreadyExists;
    char *tok;
    Room *emptyRoom = NULL;
    tok = strtok(buffer, " ");
    tok = strtok(NULL, " ");
    if(tok != NULL){
        alreadyExists = 0;

        for(i = 0; i< MAX_ROOMS; i++, rooms++){
            if(emptyRoom == NULL && !rooms->active)
                emptyRoom = rooms;
            if(strcmp(rooms->name, tok) == 0){
                alreadyExists = 1;
                sendDataObject(TYPE_ERROR, 0, "Erro ao utilizar o comando \\create. Nome de sala ja existe", NULL, usr->socket);
                break;
            }
        }

        if(!alreadyExists){
            if(emptyRoom != NULL){
                emptyRoom->active = 1;
                strcpy(emptyRoom->name, tok);
                usr->room = emptyRoom;
                sendDataObject(TYPE_CONFIRM, 0, CONFIRM_MESSAGE, NULL, usr->socket);
            }
            else{
                sendDataObject(TYPE_ERROR, 0, "Erro ao utilizar o comando \\create. Nao cabem mais salas", NULL, usr->socket);
            }
        }
    }
    else{
        sendDataObject(TYPE_ERROR, 0, "Erro ao utilizar o comando \\create. Usage: \\create room_name", NULL, usr->socket);
    }
}

int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    User tmpUser;
    Room rooms[MAX_ROOMS];

    unsigned char buffer[2048];  //data buffer of 1K

    if(argc < 2)
    {
        printf("ERRO: Precisa ser executado como ./server NumberOfClients");
        exit(EXIT_FAILURE);
    }

    int max_clients = atoi(argv[1]);
    User connectedUsers[max_clients];

    //initialise all sockets to 0 so not checked
    for (i = 0; i < max_clients; i++){
        connectedUsers[i].socket = 0;
        connectedUsers[i].room = NULL;
    }

    //clear all rooms
    for (i=0; i < MAX_ROOMS; i++)
        rooms[i].active = 0;

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            tmpUser = connectedUsers[i];
            //socket descriptor
            sd = tmpUser.socket;

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New trying connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( connectedUsers[i].socket == 0 )
                {
                    sprintf(connectedUsers[i].nickname, "Client%d", i);
                    connectedUsers[i].socket = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);

                    sendDataObject(TYPE_GREETING, i, WELCOME_MESSAGE, NULL, new_socket);

                    break;
                }
                else if(i == max_clients - 1){
                    sendDataObject(TYPE_GREETING, -1, REJECT_MESSAGE, NULL, new_socket);
                }
            }
        }

        //else its some IO operation on some other socket :)
        for (i = 0; i < max_clients; i++)
        {
            if (FD_ISSET( connectedUsers[i].socket , &readfds))
            {
                //Check if it was for closing , and also read the incoming message
                if ((valread = read( connectedUsers[i].socket , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(connectedUsers[i].socket , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    FD_CLR(connectedUsers[i].socket, &readfds);

                    //Close the socket and mark as 0 in list for reuse
                    close( connectedUsers[i].socket );
                    connectedUsers[i].socket = 0;
                }
                else
                {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[valread-1] = '\0';
                    printf("Received from client %i: %s", i, buffer);

                    switch(checkType(buffer)){
                        case IS_MESSAGE:
                            if(connectedUsers[i].room == NULL)
                                multicastReceived(buffer, i, connectedUsers, max_clients);
                            else
                                roomMessageReceived(buffer, i, connectedUsers, max_clients);
                        break;
                        case IS_CHANGENICK:
                            changeNick(buffer, &(connectedUsers[i]));
                        break;
                        case IS_CREATEROOM:
                            createRoom(buffer, &(connectedUsers[i]), rooms);
                        break;
                        case IS_JOINROOM:
                            joinRoom(buffer, &(connectedUsers[i]), rooms);
                        break;
                        case IS_LEAVEROOM:
                            connectedUsers[i].room = NULL;
                            sendDataObject(TYPE_CONFIRM, 0, CONFIRM_MESSAGE, NULL, connectedUsers[i].socket);
                        break;
                        default:
                        break;
                    }

                }
            }
        }
    }

    return 0;
}