#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

int scan_dir(char *folder, char *filename, int socket_fd)
{
	DIR *dirp = opendir(folder);

	struct dirent *current_file;

	while((current_file = readdir(dirp)) != NULL)
	{
		if(strcmp(current_file->d_name, ".") != 0 && strcmp(current_file->d_name, "..") != 0)
		{
			char new_path[1024];
			strcpy(new_path, folder);
			strcat(new_path, current_file->d_name);

			struct stat file_stat;
			stat(new_path, &file_stat);
			
			//directory
			if(S_ISDIR(file_stat.st_mode))
			{
				//printf("%s\n", current_file->d_name);
				strcat(new_path, "/");
				if(scan_dir(new_path, filename, socket_fd))
				{
					closedir(dirp);
					return 1;
				}
			}

			//regular file
			//printf("%s\n", current_file->d_name);
			if(strcmp(current_file->d_name, filename) == 0)
			{
				//stat on current file
				printf("%s\n", new_path);
				printf("%u\n", file_stat.st_size);

				closedir(dirp);
				return 1;
			}
		}
	}
	closedir(dirp);
	return 0;
}

void socket_child(int socket_fd)
{
	char filename[100];
	read(socket_fd, &filename, 100);

	//printf("%s\n", filename);

	if(scan_dir("./", filename, socket_fd) == 0)
		printf("File not found.\n");

	close(socket_fd);
}

void socket_parent(int socket_fd, char *filename)
{
	write(socket_fd, filename, strlen(filename) + 1);

	close(socket_fd);

	wait(NULL);
}

int main(int argc, char **argv)
{
	char input[100];
	char name[100];
	int access = 0;
	while(1)
	{
		if(access)
			printf("[%s> ", name);
		else
			printf("> ");

		//login:name
		//find:file
		//stat:file
		//quit

		scanf("%s", input);

		if(access)
		{
			//find, stat
			//if login => "already logged"

			if(strncmp(input, "login:", 6) == 0)
			{
				printf("Already logged.\n");
			}
			else if(strncmp(input, "find:", 5) == 0)
			{
				//find
				int socket_fd[2];
				socketpair(AF_UNIX, SOCK_STREAM, 0, socket_fd);

				pid_t process_id = fork();

				if(process_id == 0)
				{
					close(socket_fd[0]);
					socket_child(socket_fd[1]);
					return 0;
				}
				else
				{
					close(socket_fd[1]);

					char *filename_pt = strchr(input, ':');
					filename_pt++;

					socket_parent(socket_fd[0], filename_pt);
				}
			}
			else if(strncmp(input, "stat:", 5) == 0)
			{
				//stat
				char *fifo_name = "/tmp/stat_fifo";
				mkfifo(fifo_name, 0666); //read, write

				pid_t process_id = fork();

				if(process_id == 0)
				{
					int fifo_fd = open(fifo_name, O_RDONLY);

					char filename[100];

					read(fifo_fd, filename, 100);

					//printf("%s\n", filename);

					struct stat file_stat;

					stat(filename, &file_stat);

					//format this as you please
					printf("%u\n", file_stat.st_size);

					close(fifo_fd);

					return 0;
				}
				else
				{
					char *filename_pt = strchr(input, ':');
					filename_pt++;

					int fifo_fd = open(fifo_name, O_WRONLY);

					write(fifo_fd, filename_pt, strlen(filename_pt)+1);
					close(fifo_fd);

					unlink(fifo_name);

					wait(NULL);
				}
			}
			else
				printf("Unrecognized command. (try find: / stat:)\n");
		}
		else
		{
			//login
			if(strncmp(input, "login:", 6) == 0)
			{
				//split name from input
				char *name_pt = strchr(input, ':');
				name_pt++;

				int pipe_fd[2];
				pipe(pipe_fd);

				//fork for login
				pid_t process_id = fork();

				if(process_id == 0)
				{
					//child will return access
					close(pipe_fd[0]); //close read;

					FILE *users = fopen("users.cfg", "r");

					char line[100];
					while(fgets(line, 50, users) != NULL)
					{
						line[strlen(line) - 1] = 0;
						if(strcmp(line, name_pt) == 0)
						{
							//printf("%s", line);
							write(pipe_fd[1], (int[]){1}, sizeof(int));	//access = 1;
							//strcpy(name, name_pt);
							//printf("Welcome %s\n", name);
							close(pipe_fd[1]);
							return 0;
						}
					}
					//printf("Invalid user.\n");
					write(pipe_fd[1], (int[]){0}, sizeof(int));
					close(pipe_fd[1]);
					return 0;
				}
				else
				{
					//parent will check if child returned access
					close(pipe_fd[1]); //close write

					read(pipe_fd[0], &access, sizeof(int));

					close(pipe_fd[0]);

					wait(NULL);

					if(access)
					{
						strcpy(name, name_pt);
						printf("Welcome %s\n", name);
					}
					else
					{
						printf("Invalid user.\n");
					}
				}
			}
			else
				printf("Unrecognized command. (are you logged in?)\n");
		}
	}

	return 0;
}