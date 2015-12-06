#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <termios.h>

char in[100];
int eras = 1;

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

void change()
{
	int j = 0;
	if (flag == 2 || flag == 3)
	{
		if (now == 1)
		_where--;
	}

	//display
	for (j = 0; j <= _where; j++)
		printf("%s", unicode_to_utf8(in[j]));
	if (flag == 1)
		flag = 2;
	else if (flag == 2)
		flag = 3;
	else if (flag == 3)
		flag = 1;

	//display
	for (j = 0; j <= _where; j++)
		printf("%s", unicode_to_utf8(in[j]));

	return;
}

void changeToKorean(char a)
{
	char ch;
	int cons_flag = 0;
	int vowel_sum = 0;
	int i = 0;
	int j = 0;
	int _where = 0;  //////////////
	char in[_where] = a;


	if (in[_where] == '.')
		//space
	else
	{
		//cons_flag = consonant
		while (1)
		{
			ch = getche();
			if (ch == '+')
			{
				//change
				return;
			}
			if (ch == '-')
			{
				backspace();
				continue;
			}
			if (ch == '.')
			{
				space();
				continue;
			}
         else if (ch == '7' || ch == '8' || ch == '9')
         {
		//
         }
      }
   }
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
	 if(ch == '.')
	 {
		_where++;
		printf("space");
		if(eras != 0)
		{
			eras = 0;
			continue;
		}
	 }
	 if(ch == '-')
	 {
		if(eras == 0)
		{
			_where++;
			eras = 100;
		}	
		printf("delete\n");
		continue;
	 }
	 else
	 {
         	_where++;
         	in[_where] = ch;
		if(eras != 0)
		{	
			eras = 0;
		}
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
	return 0;
}
