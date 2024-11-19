#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
int sem_id;
#define SEM_NUM 5

int lb = 0;
int ub = 5;

void P(int left_sem, int right_sem)
{
    struct sembuf semaphore[SEM_NUM];
    semaphore[left_sem].sem_num = 0;
    semaphore[left_sem].sem_op = -1; // P
    semaphore[left_sem].sem_flg = ~(IPC_NOWAIT | SEM_UNDO);

    semaphore[right_sem].sem_num = 0;
    semaphore[right_sem].sem_op = -1; // P
    semaphore[right_sem].sem_flg = ~(IPC_NOWAIT | SEM_UNDO);

    if (semop(sem_id, &semaphore[left_sem], SEM_NUM))
    { // 1 ist Groesse Array
        perror("Error in semop P()");
        exit(1);
    }
    if (semop(sem_id, &semaphore[left_sem], SEM_NUM))
    { // 1 ist Groesse Array
        perror("Error in semop P()");
        exit(1);
    }
}

void V(int left_sem, int right_sem)
{
    struct sembuf semaphore[SEM_NUM];
    semaphore[left_sem].sem_num = 0;
    semaphore[left_sem].sem_op = 1; // V
    semaphore[left_sem].sem_flg = ~(IPC_NOWAIT | SEM_UNDO);

    semaphore[right_sem].sem_num = 0;
    semaphore[right_sem].sem_op = 1; // V
    semaphore[right_sem].sem_flg = ~(IPC_NOWAIT | SEM_UNDO);
    if (semop(sem_id, &semaphore[left_sem], SEM_NUM))
    { // 1 ist Groesse Array
        perror("Error in semop V()");
        exit(1);
    }
    if (semop(sem_id, &semaphore[right_sem], SEM_NUM))
    { // 1 ist Groesse Array
        perror("Error in semop V()");
        exit(1);
    }
}

void init_sem()
{
    for (int i = 0; i < 5; i++)
    {
        if (semctl(sem_id, i, SETVAL, 1) < 0)
        {
            perror("Error in semctl");
            exit(1);
        }
    }
}

int main()
{
    key_t sem_key[5];

    for (int i = 0; i < 5; i++)
    {
        if ((sem_key[i] = ftok("/Users/aleksandarmaksimovic/Projects/vts/blatt2/", '1')) < 0)
        {
            perror("Fehler bei ftok");
            exit(1);
        }

        if ((sem_id = semget(sem_key[i], 5, IPC_CREAT | 0666)) < 0)
        {
            perror("Error in semget");
            exit(1);
        }
    }
    init_sem();
    for (int i = 0; i < 5; i++)
    {

        switch (fork())
        {
        case 0:
            printf("%d", i);
            for (int j = 0; j < 5; j++)
            {
                bool essen = false;
                srand(time(NULL));
                int r = (rand() % (ub - lb) + lb);
                if (r == i)
                {
                    P(i, (i % 5));
                    essen = true;
                }

                while (essen == true)
                {
                    sleep(5);
                    printf("Philosoph %d ist am essen \n", i);
                    int r2 = (rand() % (ub - lb) + lb);
                    if (r2 == i)
                    {
                        essen = false;
                        V(i, (i % 5));
                    }
                }

                sleep(5);
                printf("Philosoph %d ist am denken \n", i);
            }

            exit(0);

        case -1:
            perror("fork failed");
            exit(1);

        default:;
        }
    }
}