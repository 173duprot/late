#include <stdio.h>
#include <fcntl.h> /* open() */
#include <unistd.h> 

#include <termios.h>
#include <sys/poll.h>

#define STDIN_FILENO    0       /* Standard input.  */
#define STDOUT_FILENO   1       /* Standard output.  */
#define STDERR_FILENO   2       /* Standard error output.  */

#define	READ_ONLY	0	/* Custom thing for the open() function */

/* tc- means terminal control, it will turn off terminal echoing */
/* relies on termios.h */
void echo_off()
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);

	/* ICANON turns off line by line input */
	/* ECHO turns off echoing what you type */
	t.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main(int argc, char *argv[])
{
	/*VAR buffer -- buffer for reading from files/stdin*/
		/* These VARS are used to temporarily, and by multiple things */
		/* read, print, then close for the next use of it */
	char buffer[1024];
	int buffer_size;
	
	/*  A file descriptor is a number that uniquely identifies an open file */
	/* They are found in /proc/<PID>/fd/[ 0 | 1 | 2 | 3 ...] */

	/*VAR fd_ -- file descriptor - 0,1,2 reserved for stdin, stdout, stderr */
	int fd_stdin = STDIN_FILENO;
	int fd_file = open(argv[1], READ_ONLY);
	
	struct pollfd pfds[2];

	echo_off();
	
	while (1)
	{
	/* Wait for I/O event, either stdin or file change */

		/* poll() every itteration needs to be re-initilized */
			/* POLLIN checks weather theres data to be read */
		pfds[0].fd = fd_stdin;
		pfds[0].events = POLLIN;

		pfds[1].fd = fd_file;
		pfds[1].events = POLLIN;

		/*FN poll() - wait for some event on a file descriptor */
			/* -1 means wait forever */
		poll(pfds, 2, -1); 		

	/* If STDIN has new stuff to read */
		if (pfds[0].revents & POLLIN)
		{
		/* Read input */
			/* read(); returns its length */
				/* read takes raw ascii input thats *not* \0 terminated */
			buffer_size = read(fd_stdin, buffer, sizeof(buffer));
			
			/* go to the end of the buffer and \0 terminate it */
			buffer[buffer_size] = '\0';

		/* Print input */
			puts(buffer);
			/* Null terminate the buffer at the beggining, deleting the string */
			buffer[0] = '\0';
		}
	
	/* If the file has new stuff to read */
		if (pfds[1].revents & POLLIN)
		{
		/* Read file */
			/* read(); returns its length */
				/* read takes raw ascii input thats *not* \0 terminated */
			buffer_size = read(fd_file, buffer, 1024);
			
			/* go to the end of the buffer and \0 terminate it */
			buffer[buffer_size] = '\0';
		
		/* Print file */
			puts(buffer);
			/* Null terminate the buffer at the beggining, deleting the string */
			buffer[0] = '\0';
			
		}
	}
}
