#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        perror("Error: enter a value N");
        exit(EXIT_FAILURE);
    }

    pid_t pid1, pid2;

    pid1 = fork();
    if(pid1 < 0)
    {
        perror("Error: fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid1 == 0)
    {

        if(execl("./odds", "odds", argv[1], (char *)NULL) == -1)
        {
            perror("Error: exec failed");
            exit(EXIT_FAILURE);
        }
    }

    pid2 = fork();
    if(pid2 < 0)
    {
        perror("Error: fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid2 == 0)
    {

        if(execl("./evens", "evens", argv[1], (char *)NULL) == -1)
        {
            perror("Error: exec failed");
            exit(EXIT_FAILURE);
        }
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
