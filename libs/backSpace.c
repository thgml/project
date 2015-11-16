#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int whenSpace = 0;
int _where = 0;
int in[10];

void gotoxy(int x, int y)
{
	printf("%d;%d", y + 1, x + 1);
	printf("\n");
}

void space()
{
	int j = 0;

	//display

	in[_where] = ' ';

	// console check
	whenSpace = 1;

	for (j = 0; j <= _where; j++)
		printf("%s", in[j]);
}

void backspace()
{
	int j = 0;

	if (whenSpace == 1)
	{
		_where -= 2;
		whenSpace = 0;
	}
	else
		_where -= 1;

	// console check

	//display fuction

	if (_where <= 0)
	{
		_where = 0;
		//erase
	}

	in[_where] = 0;
	for (j = 0; j < _where; j++)
		printf("%s", in[j]);
}

int main()
{
	gotoxy(10,10);

	return 1;
}