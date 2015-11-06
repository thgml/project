#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

char in[100];

int getche(void)
{
   struct termios oldattr, newattr;
   int ch;
   tcgetattr(STDIN_FILENO, &oldattr);
   newattr = oldattr;
   newattr.c_lflag &= ~(ICANON);
   tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
   ch = getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
   return ch;
}

void changeToNum(char a)
{
   char ch;
   int _where;
   in[_where] = a;

   if (in[_where] == '0')
      printf("space\n");
   else
   {
      while (1)
      {
         ch = getche();
	 if(ch == '+')
	 {
		printf("change\n");
		return;
	 }
	 if(ch == '-')
	 {
		printf("delete\n");
	 }
	 else
	 {
         	_where++;
         	in[_where] = ch;
	 }
      }
   }
}

int main()
{
	char ch;
	while(1)
	{
		
		ch = getche();
		changeToNum(ch);
		
		
	}
}
