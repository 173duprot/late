#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getch();

int main(int argc, char **argv) {
   int ch;
   printf("Press x to exit.\n\n");
   for (;;) {
      ch = getch();
      printf("ch = %c (%d)\n", ch, ch);
      if(ch == 'x')
         break;
   }
   return 0;
}

int getch() {
   struct termios oldtc;
   struct termios newtc;
   int ch;
   tcgetattr(STDIN_FILENO, &oldtc);
   newtc = oldtc;
   newtc.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
   ch=getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
   return ch;
}
