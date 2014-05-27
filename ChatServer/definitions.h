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

#define CMD_QUIT "\\quit"
#define CMD_QUIT_END "\\quit\n"
#define CMD_CHANGE_NICK "\\nick"
#define CMD_CHANGE_NICK_END "\\nick\n"

typedef struct Data_str
{
    int type;
    int id;
    char message[BUFSIZE];
    char nickname[40];
} Data;