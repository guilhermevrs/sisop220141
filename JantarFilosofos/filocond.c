#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define LEFT (number+Nphils-1)%Nphils
#define RIGHT (number+1)%Nphils


pthread_cond_t LR_eating;
//Mutex para sentar na mesa
pthread_mutex_t table_mutex;
//Mutex para imprimir estado
sem_t printStat;
//String que guarda estado atual da mesa
char phil_stats[];
//Numero de filosofos na mesa
int Nphils;

void changePrintStates(char state, int idPhil){
    sem_wait(&printStat);
    phil_stats[idPhil] = state;
    int i;
    for (i = 0; i < Nphils; ++i) {
        printf("%c", phil_stats[i]);
    }
    printf("\n");
    fflush(stdout);
    sem_post(&printStat);
}

void* philosopher(void* arg){

    int number = *(int*)(arg);
    srand(time(NULL));

    while(1){
        //Filosofo comeca pensando.
        //.. e dorme por um tempo aleatorio
        int rnd = rand() % 10 + 1;
        sleep(rnd);
        //Filosofo fica com fome...        
        changePrintStates('H', number);
        //..entao se senta na mesa (nunca mais de um filosofo senta na mesa ao mesmo tempo)
        pthread_mutex_lock(&table_mutex);

        //Se os vizinhos estao comendo entao bloqueio e libero a mesa
        while(phil_stats[LEFT] == 69 || phil_stats[RIGHT] == 69){
            pthread_cond_wait(&LR_eating, &table_mutex);
        }

        //phil_staanots[number] = 'E';
        changePrintStates('E', number);
        //Libera a mesa para os outros
        pthread_cond_signal(&LR_eating);
        pthread_mutex_unlock(&table_mutex);
        rnd = rand() % 10 + 1;
        sleep(rnd);
        //phil_stats[number] = 'T';
        changePrintStates('T', number);
    }
}

int main(int argc, char **argv){

    // Validacao de parametros
    if(argc < 2){
        printf("Numero de filosofos nao especificado.");
        return 0;
    }
    Nphils = atoi(argv[1]);
    if(Nphils < 1){
        printf("Numero de filosofos precisar ser maior/igual a 1.");
        return 0;
    }

    // Array que armazena o estado de cada filosofo
    *phil_stats = malloc(sizeof(char)*Nphils);
    memset(phil_stats, 84, sizeof(char)*Nphils);


    // Criacao dos filosofos e mutexes
    pthread_t phils[Nphils];
    pthread_mutex_init(&table_mutex, NULL);
    sem_init(&printStat, 0, 1);

    changePrintStates('T', 0);

    int i;

    for(i = 0; i < Nphils; ++i){
        pthread_create(&phils[i], NULL, philosopher, (void*)(&i));
        usleep(100);
    }

    for (i = 0; i < Nphils; ++i){
        pthread_join(phils[i], NULL);
    }

    return 0;
}
