#include <unistd.h>

int main(int argc, char **argv)
{
    write(1, "Hello World!", 12);

    return 0;
}