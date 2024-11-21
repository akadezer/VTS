#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#define NUM_OF_WRITER 2
#define NUM_OF_READER 5
#define MUTEX 1
int sem_id;
pid_t writer[NUM_OF_WRITER];
pid_t reader[NUM_OF_READER];

void write()
{
    sleep(1);
    printf("Schreiber überarbeitet Datei. \n");
    sleep(1);
}

void read()
{
    sleep(1);
    printf("Leser liest gerade die Datei \n");
    sleep(1);
}
void init_sem()
{

    if (semctl(sem_id, 0, SETVAL, 1) < 0)
    {
        perror("Error in semctl");
        exit(1);
    }
    if (semctl(sem_id, 1, SETVAL, 1) < 0)
    {
        perror("Error in semctl");
        exit(1);
    }
    if (semctl(sem_id, 2, GETVAL, 1) < 0)
    {
        perror("Error in semctl");
        exit(1);
    }
}
int main()
{
    sem_t sem_key;
    if ((sem_key = ftok("/Users/aleksandarmaksimovic/Projects/vts/blatt3", '1')) < 0)
    {
        perror("Fehler bei ftok()");
        exit(1);
    }
    if ((sem_id = semget(sem_key, 3, IPC_CREAT | 0666)) < 0)
    {
        perror("Error in semget");
        exit(1);
    }

    init_sem();

    // initialise writer processes
    for (int i = 0; i < NUM_OF_WRITER; i++)
    {
        if ((writer[i] = fork()) < 0)
        {
            perror("Fehler bei fork() fuer writer");
            exit(1);
        }
    }

    // initialize reader processes
    for (int i = 0; i < NUM_OF_READER; i++)
    {

        if ((reader[i] = fork()) < 0)
        {
            perror("Fehler bei fork() fuer reader");
            exit(1);
        }
    }
}