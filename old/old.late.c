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
#include <unistd.h> /* sleep () */
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Will follow the live output of the file */
void follow(char filename[]) {

	char letter;

	char input_char;
	char input_buffer[1000];

	FILE *fptr;


	/* Open file */
	fptr = fopen(filename, "a+");

	/* Loop forever */
	while (1)
	{
		/* set letter as the next char in the document */
		letter = fgetc(fptr);

		/* Print contents from file until EOF*/
		while (letter != EOF)
		{
			putchar (letter);
			letter = fgetc(fptr);
		}

		/* moves cursor back to the last non-EOF char */
		ungetc(letter, fptr);

		/* Save cursor position */
		printf("\033[s");
		

		/* Take input */
		input_char = getch();


		/* if the user hits enter */
		if (input_char == 10)
		{
			/* append input buffer to the end of file */
			fprintf(fptr, "\n%s", input_buffer);
			/* clear input buffer */
			input_buffer[0] = '\0';
		}
		else
		{
			/* append input to buffer */
			strncat(input_buffer, &input_char, 1);
		}
		
		/* move cursor, clear
		   move cursor, clear */
		printf("\033[E \033[K \
			\033[E \033[K");
		/* print buffer */
		printf("> %c", input_buffer);
		
		/* move cursor back to the saved position */
		printf("\033[u");
		

		/* sleep and redo */
		sleep(0.01);
	}
	fclose(fptr);
}

int main(int argc, char* argv[])
{
	follow(argv[1]);
	
	return 0;
}
