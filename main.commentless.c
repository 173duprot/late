#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <termios.h>
#include <sys/poll.h>

#define STDIN_FILENO    0       
#define STDOUT_FILENO   1       
#define STDERR_FILENO   2       

#define	READ_ONLY	0	

void echo_off()
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main(int argc, char *argv[])
{
	struct pollfd pfds[2];

	char buffer[1024];

	int buffer_size;
	int fd_stdin = STDIN_FILENO;
	int fd_file = open(argv[1], READ_ONLY);

	echo_off();
	
	while (1)
	{
		pfds[0].fd = fd_stdin;
		pfds[0].events = POLLIN;
		pfds[1].fd = fd_file;
		pfds[1].events = POLLIN;
			
		poll(pfds, 2, -1); 		

		if (pfds[0].revents & POLLIN)
		{
		
			buffer_size = read(fd_stdin, buffer, sizeof(buffer));
			buffer[buffer_size] = '\0';
			puts(buffer);
			buffer[0] = '\0';
		}

		if (pfds[1].revents & POLLIN)
		{
			buffer_size = read(fd_file, buffer, 1024);
			buffer[buffer_size] = '\0';
			puts(buffer);
			buffer[0] = '\0';
			
		}
	}
}
