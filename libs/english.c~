#include <stdio.h>
#include <termios.h>
#include <unistd.h>

char in[1000];
char englishSmall[10][4] = { {}, { 'p', 'q', 'r', 's' }, { 't', 'u', 'v' }, { 'w', 'x', 'y', 'z' },
{ 'g', 'h', 'i' }, { 'j', 'k', 'l' }, { 'm', 'n', 'o' },
{ '.', '?', '!' }, { 'a', 'b', 'c' }, { 'd', 'e', 'f' } };
char englishLarge[10][4] = { {}, { 'P', 'Q', 'R', 'S' }, { 'T', 'U', 'V' }, { 'W', 'X', 'Y', 'Z' },
{ 'G', 'H', 'I' }, { 'J', 'K', 'L' }, { 'M', 'N', 'O' },
{ '.', '?', '!' }, { 'A', 'B', 'C' }, { 'D', 'E', 'F' } };

int _where =0;
int capsLock = 0;
int englishArayPrint(int i, int e_flag, int capsLock)
{
   int j = 0;
   if (e_flag == 3)
   {
      if (englishSmall[i][3] == ' ')
         e_flag = 0;
   }
   if (e_flag == 4)
      e_flag = 0;

   for (j = 0; j <= _where; j++)
      printf("%c", in[j]);
   e_flag++;

   return e_flag;
}
void changeToEnglish(char a)
{
	char ch;
	int e_flag = 0;	
	in[_where] = a;
	
	while(1)
	{
		ch = getche();
		if (ch == a) //같은건가
         	{
            		e_flag = englishArayPrint(a - '0', e_flag, capsLock);
        	 }
         	else  //같지 않아
         	{
        	    if (in[_where] == '0')  
            	    {
               		a = ch;
               		e_flag = 0;
               		in[_where] = ch;
               		e_flag = englishArayPrint(ch - '0', e_flag, capsLock);
 		    }
  
  	            else
                    {
               		a = ch;
               		e_flag = 0;
   		       in[_where] = ch;
        	       e_flag = englishArayPrint(ch - '0', e_flag, capsLock);
           	     }
                  }
	}
}


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
int main (void)
{
	char ch;
	while(1)
	{
		ch = getche();
		changeToEnglish(ch);
	}
}
