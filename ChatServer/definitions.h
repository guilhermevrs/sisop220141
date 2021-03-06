#define PORT 8888
#define BUFSIZE 1024

#define TRUE 1
#define FALSE 0

#define WELCOME_MESSAGE "Bem-vindo ao chat!"
#define REJECT_MESSAGE "Desculpa, mas estamos lotados"
#define CONFIRM_MESSAGE "Operacao feita com sucesso"

#define TYPE_GREETING 0
#define TYPE_MESSAGE 1
#define TYPE_CONFIRM 2
#define TYPE_ERROR 3

#define IS_MESSAGE 0
#define IS_CHANGENICK 1
#define IS_CREATEROOM 2
#define IS_JOINROOM 3
#define IS_LEAVEROOM 4

#define CMD_QUIT "\\quit"
#define CMD_QUIT_END "\\quit\n"
#define CMD_CHANGE_NICK "\\nick"
#define CMD_CHANGE_NICK_END "\\nick\n"
#define CMD_CREATE_ROOM "\\create"
#define CMD_CREATE_ROOM_END "\\create\n"
#define CMD_JOIN_ROOM "\\join"
#define CMD_JOIN_ROOM_END "\\join\n"
#define CMD_LEAVE_ROOM "\\leave"
#define CMD_LEAVE_ROOM_END "\\leave\n"


typedef struct Data_str
{
    int type;
    int id;
    char message[BUFSIZE];
    char nickname[40];
} Data;