#define PORT 8888
#define BUFSIZE 1024

#define TRUE 1
#define FALSE 0

#define WELCOME_MESSAGE "Bem-vindo ao chat!"
#define REJECT_MESSAGE "Desculpa, mas estamos lotados"

#define TYPE_GREETING 0
#define TYPE_MESSAGE 1

typedef struct Data_str
{
    int type;
    int id;
    char message[BUFSIZE];
} Data;