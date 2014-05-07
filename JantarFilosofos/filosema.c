#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define LEFT (number+Nphils-1)%Nphils
#define RIGHT (number+1)%Nphils

//Um mutex para cada filosofo
sem_t *phil_mutex;
//Mutex para sentar na mesa
sem_t table_mutex;
//Mutex para imprimir estado
sem_t printStat;
//String que guarda estado atual da mesa
char phil_stats[];
//Numero de filosofos na mesa
int Nphils;

void printStates(){
    sem_wait(&printStat);
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
        int rnd = rand() % 10 + 1;
        sleep(rnd);
        //Filosofo fica com fome...
        phil_stats[number] = 'H';
        printStates();
        sem_wait(&table_mutex);
        //Se os vizinhos nao estao comendo entao posso comer
        if(phil_stats[LEFT] != 69 && phil_stats[RIGHT] != 69){
            phil_stats[number] = 'E';
            printStates();
            //Libera a mesa para os outros
            sem_post(&table_mutex);
            rnd = rand() % 10 + 1;
            sleep(rnd);
            phil_stats[number] = 'T';
            printStates();
        }
        else{
            //Saindo da mesa
            sem_post(&table_mutex);
        }
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
    //phil_mutex = malloc(sizeof(sem_t)*Nphils);
    sem_init(&table_mutex, 0, 1);
    sem_init(&printStat, 0, 1);

    printStates();

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
