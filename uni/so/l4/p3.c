#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    //compile p2.c first and pass the binary pwd to arglist, change name below if your binary isn't named coll

    for(int i = 2; i < argc; ++i)
    {
        pid_t pid = fork();
        if(pid == 0)
        {
            char* arg[] = {"coll", argv[i], NULL};
            execve(argv[1], arg, NULL);
        }
        else
            wait(NULL);
    }
    return 0;
}