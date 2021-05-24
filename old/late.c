/* late.c -- live appending text editor

	The person who associated a work with this deed has dedicated the work to
	the public domain by waiving all of his or her rights to the work worldwide
	under copyright law, including all related and neighboring rights, to the
	extent allowed by law. Do whatever you want. You can copy, modify, distribute
	and perform this work, even for commercial purposes, all without asking
	permission.

	This software is provided `as is`, and in fact, if you copy this code consider
	yourself liable for running as if you wrote it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #include <unistd.h> /* sleep (), STDIN_FILENO allowing me to watch stdin */
/* #include <sys/poll.h> /* watch stdin with poll */

/* Will follow the live output of the file */
void follow(char filename[]) {

	char input_char;
	char input_buffer[1000];

	/* get the pid of the program so we can play with stdin and out */
	pid_t pid = getpid();
	
	/* Open file */
	FILE *fptr;
	fptr = fopen(filename, "a+");
	pid_t tgetpid(void);

	/* Loop forever */
	while (1)
	{
		/* set input_char as the next char in the document */
		input_char = fgetc(fptr);

		/* Print contents from file until EOF*/
		while (input_char != EOF)
		{
			putchar (input_char);
			input_char = fgetc(fptr);
		}

		/* moves cursor back to the last non-EOF char */
		ungetc(input_char, fptr);

		/* sleep and redo */
		sleep(0.01);
	}
	/* fclose(fptr); will never close so whats the point */
}

int main(int argc, char* argv[])
{
	follow(argv[1]);
	return 0;
}
