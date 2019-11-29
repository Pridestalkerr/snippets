#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    pid_t pid = fork();
    if(pid == 0)
    {
        int n = (int) strtol(argv[1], (char**) NULL, 10);
        while(n != 1)
        {
            printf("%d ", n);
            if(n % 2)
                n = 3*n + 1;
            else
                n = n / 2;
        }
        printf("1\n");

        return 0;
    }
    else
        wait(NULL);

    return 0;
}