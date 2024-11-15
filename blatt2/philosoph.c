#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <time.h>

int lb = 0;
int ub = 5;

int main()
{

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
                    essen = true;
                }

                while (essen == true)
                {
                    sleep(1);
                    printf("Philosoph %d ist am essen \n", i);
                    int r2 = (rand() % (ub - lb) + lb);
                    if (r2 == i)
                    {
                        essen = false;
                    }
                }

                sleep(1);
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