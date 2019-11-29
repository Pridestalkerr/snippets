#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *copy = (char*) malloc(strlen(argv[1]));
    
    syscall(332, argv[1], copy, strlen(argv[1]));

    printf("Copied string: %s\n", copy);

    free(copy);

    return 0;
}