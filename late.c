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
#include <string.h>

void follow(char filename[]) {
	char letter;
	FILE *fptr;

	fptr = fopen(filename, "a+");
	
	while(1) {

		letter = fgetc(fptr);

		if(strcmp(line, next_line) != 0) {
			putchar("f");
			fptr++
		}	
		
	}

	fclose(fptr);
}

int main(int argc, char* argv[]) {

	/* write(); */	
	follow(argv[0]);

	return 0;
}


