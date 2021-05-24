#include <stdio.h>
#include <fcntl.h>		/* open() */
#include <unistd.h>		/* read(), write() etc... */

#include <termios.h>		/* Terminal control */
#include <sys/poll.h>		/* Watch file descriptors FD  for changes */
#include <sys/inotify.h>	/* Watch files for changes as a FD steam */

#define STDIN_FILENO    0       /* Standard input.  */
#define STDOUT_FILENO   1       /* Standard output.  */
#define STDERR_FILENO   2       /* Standard error output.  */

#define	READ		0	/* Custom thing for the open() function */
#define WRITE		1	/* Custom thing for the open() function */

/* tc- means terminal control, it will turn off terminal echoing */
/* relies on termios.h */
void echo_off()
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);

	/* ICANON turns off line by line input, only 1 char at a time is taken */
	/* ECHO turns off echoing what you type */
	t.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main(int argc, char *argv[])
{
	/* Init for poll */
	struct pollfd pfds[2];

	/*VAR buffer -- buffer for reading from files/stdin*/
		/* This VAR is used to temporarily, and by multiple things */
		/* read, print, then close for the next use of it */
	char buffer;
	int buffer_size;
	
	/*  A file descriptor is a number that uniquely identifies an open file */
	/* They are found in /proc/<PID>/fd/[ 0 | 1 | 2 | 3 ...] */

	/*VAR fd_ -- file descriptor - 0,1,2 reserved for stdin, stdout, stderr */
	int fd_stdin = STDIN_FILENO;
	int fd_stdout = STDOUT_FILENO;
	
	/* init for inotify */
	int fd_file = inotify_init(); 
	inotify_add_watch(fd_file, argv[1], IN_MODIFY);
	
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

	/* If STDIN has new character to read */
		if (pfds[0].revents & POLLIN)
		{
		/* Read char from input */
			/* Buffer is a char, the size is 1 */
			read(fd_stdin, &buffer, 1);
			
		/* Print input */
			write(fd_stdout, &buffer, 1);
		}
	
	/* If the file has new stuff to read */
		if (pfds[1].revents & POLLIN)
		{
			/* Go through ever letter in the file */
		/*	while ( (buffer_size = read(fd_file, &buffer, 1)) > 0)
				{
					/* Read char from file */
		/*			read(fd_file, &buffer, 1);
				
					/* Print file */
		/*			write(fd_stdout, &buffer, 1);
				} */
		
		/* Read char from file */
		read(fd_file, &buffer, 1);
		
		/* Print file */
		write(fd_stdout, &buffer, 1);
		}
	}
}
