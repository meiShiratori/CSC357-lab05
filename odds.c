#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        perror("Error: enter a value N");
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    for(int i = 1; i <= N; i++)
    {
        if(i % 2 != 0)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}
