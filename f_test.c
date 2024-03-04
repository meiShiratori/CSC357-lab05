#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>

void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl))
    {
        perror("getrlimit");
        exit(-1);
    }
    else
    {
        // printf("Current max processes limit: %lu\n", (unsigned long)rl.rlim_cur);
        // printf("Max processes limit (hard limit): %lu\n", (unsigned long)rl.rlim_max);
    }
    rl.rlim_cur = max_procs;
    if (setrlimit(RLIMIT_NPROC, &rl))
    {
        perror("setrlimit");
        exit(-1);
    }
}



int main(int argc, char *argv[])
{
    //limit_fork(300);
    if (argc < 2)
    {
        perror("Error: enter a value N");
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    pid_t process_id = fork();
    if (process_id < 0)
    {
        perror("Error: fork failed");
        exit(EXIT_FAILURE);
    }
    else if (process_id == 0)
    {
        for (int i = 1; i <= N; i++)
        {
            if (i % 2 != 0)
            {
                printf("%d\n", i);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        wait(NULL);
        for (int i = 1; i <= N; i++)
        {
            if (i % 2 == 0)
            {
                printf("\t%d\n", i);
            }
        }
    }
    return 0;
}
