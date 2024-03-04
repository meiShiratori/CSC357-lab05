#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        perror("Error: enter a program and a file name");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd < 0)
    {
        perror("Error: opening file");
        exit(EXIT_FAILURE);
    }

    if(dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("Error: duplicating file descriptor");
        exit(EXIT_FAILURE);
    }

    close(fd);

    if(execvp(argv[1], &argv[1]) < 0)
    {
        perror("Error: executing program");
        exit(EXIT_FAILURE);
    }

    return 0;
}
