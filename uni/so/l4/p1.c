#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t pid = fork();

    if(pid == 0)
    {
        char* arg[] = {"ls", NULL};
        execve("/bin/ls", arg, NULL); //will kill the child, no need to return
    }
    else
    {
        printf("Parent: %d, Child: %d\n", getpid(), pid);
        wait(NULL);
    }

    return 0;
}