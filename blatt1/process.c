#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int sem_id;

void init_sem()
{
    if (semctl(sem_id, 0, SETVAL, 1) < 0)
    {
        perror("Error in semctl");
        exit(1);
    }
}

void P()
{
    struct sembuf P = {0, -1, SEM_UNDO};

    if (semop(sem_id, &P, 1) == -1)
    { // 1 ist Groesse Array
        perror("Error in semop P()");
        exit(1);
    }
}

void V()
{
    struct sembuf V = {0, 1, SEM_UNDO};
    if (semop(sem_id, &V, 1))
    { // 1 ist Groesse Array
        perror("Error in semop V()");
        exit(1);
    }
}

int main()
{
    key_t sem_key;

    if ((sem_key = ftok("/Users/aleksandarmaksimovic/Projects/vts/blatt1/", '1')) < 0)
    {
        perror("Fehler bei ftok");
        exit(1);
    }
    if ((sem_id = semget(sem_key, 1, IPC_CREAT | 0666)) < 0)
    {
        perror("Error in semget");
        exit(1);
    }
    init_sem();

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case 0:
            printf("Process %d mit PID %d \n", i, getpid());
            P();
            printf("Process %d betritt den kritischen Bereich \n", i);
            sleep(1);
            printf("Process %d verlässt den kritischen Bereich \n", i);
            sleep(1);
            V();
            printf("Process %d betritt den nicht kritischen Bereich \n", i);
            sleep(1);
            printf("Process %d verlässt den nicht kritischen Bereich \n", i);

            exit(0);
        case -1:

            perror("Fork failed");
            exit(1);
            ;
        default:;
        }
    }
}
