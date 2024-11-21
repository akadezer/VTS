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
int writer = 1;
int mutex = 0;
int reader;
void P(int semaphore_num)
{

    struct sembuf semaphore;
    semaphore.sem_num = semaphore_num;
    semaphore.sem_op = -1; // P-Operation
    semaphore.sem_flg = ~(IPC_NOWAIT | SEM_UNDO);

    if (semop(sem_id, &semaphore, 1))
    { // 1 ist Groesse Array
        perror("Error in semop P()");
        exit(1);
    }
}
void V(int semaphore_num)
{

    struct sembuf semaphore;
    semaphore.sem_num = semaphore_num;
    semaphore.sem_op = 1; // V-Operation
    semaphore.sem_flg = ~(IPC_NOWAIT | SEM_UNDO);

    if (semop(sem_id, &semaphore, 1))
    { // 1 ist Groesse Array
        perror("Error in semop P()");
        exit(1);
    }
}
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
}
int main()
{
    sem_t sem_key;
    if ((sem_key = ftok("/Users/aleksandarmaksimovic/Projects/vts/blatt3", '1')) < 0)
    {
        perror("Fehler bei ftok()");
        exit(1);
    }
    if ((sem_id = semget(sem_key, 2, IPC_CREAT | 0666)) < 0)
    {
        perror("Error in semget");
        exit(1);
    }

    init_sem();

    // initialise writer processes
    for (int i = 0; i < NUM_OF_WRITER; i++)
    {
        switch (fork())
        {
        case 0:
            P(writer);
            write();
            V(writer);
            exit(0);

        case -1:
            perror("Error on fork");
            exit(1);
        default:
        }
    }

    // initialize reader processes
    for (int i = 0; i < NUM_OF_READER; i++)
    {
        /* code */

        switch (fork())
        {
        case 0:
            P(mutex);
            reader++;
            if (1 == reader)
                P(writer);
            V(mutex);
            read();
            P(mutex);
            reader--;
            if (0 == reader)
                V(writer);
            V(mutex);
            exit(0);

        case -1:
            perror("Error on fork");
            exit(1);
        default:
        }
    }
}