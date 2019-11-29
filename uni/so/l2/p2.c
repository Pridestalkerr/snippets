#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char buffer[4096];

    int file_in = open(argv[1], O_RDONLY, S_IRUSR);
    int file_out = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
    int count = 0;    

    while((count = read(file_in, buffer, 4096)) > 0)
    {
        printf("%d\n", count);
        int written_count = write(file_out, buffer, count);

        if(count != written_count)
            printf("%s", "Error writing data.");
    }

    close(file_in);
    close(file_out);

    return 0;
}