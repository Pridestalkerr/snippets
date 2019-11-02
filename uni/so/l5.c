#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) //4 elements max
{
	char *shm_name = "lkjjipo0112c";
	int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	ftruncate(shm_fd, 4096*4);
	int *data = (int*) mmap(NULL, 4096*4, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	int itr;
	for(itr = 1; itr < argc; ++itr)
	{
		int val = atol(argv[itr]);
		pid_t pid = fork();
		if(pid == 0)
		{
			char *shm_name = "lkjjipo0112c";
			int shm_fd = shm_open(shm_name, O_RDWR, S_IRUSR | S_IWUSR);
			int *data_int = (int*) mmap(NULL, 1024*4, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 1024*4*(itr - 1));
			//printf("%d\n", data_int[0]); race?
			int i = 0;
			int n = data_int[i];
			while(n != 1)
			{
				if(n % 2)
					n = 3*n + 1;
				else
					n = n / 2;
				i++;
				data_int[i] = n;
			}
			munmap(data_int, 1024); //unmap the address
			return 0;
		}
		else
		{
			//write(shm_fd, &val, sizeof(int));
			data[256*4*(itr - 1)] = val;
		}
	}
	wait(NULL);
	wait(NULL);
	wait(NULL); //wait for every child
	for(itr = 0; itr < 1024*4; ++itr)
		printf("%d ", data[itr]);
	shm_unlink(shm_name);
	return 0;
}	