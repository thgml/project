#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

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

int main()
{
	changeToKorean();
	return 0;
}