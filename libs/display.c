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

void display(int *flag, int *capsLock)
{
	int y, x, z, cnt = 6;
	for (y = 2; y <= 8; y += 3)
	{
		for (x = 3; x <= 15; x += 6)
		{
			gotoxy(x, y);
			printf("%d", ++cnt);
			gotoxy(x + 1, y + 1);
			if (flag == 1)
			{
				for (z = 0; z <= 2; z += 1)
					printf("str");
			}
			if (flag == 2 && capsLock == 0)
			{
				for (z = 0; z <= 3; z += 1)
					printf("str");

			}
			if (flag == 2 && capsLock == 1)
			{
				for (z = 0; z <= 3; z += 1)
					printf("str");
			}
			if (cnt == 9)
				cnt = 3;
			else if (cnt == 6)
				cnt = 0;
		}
	}
	gotoxy(3, 11);
	printf("0");
	gotoxy(4, 12);
	if (flag == 1)
		printf("str str");
	else if (flag == 2 && capsLock == 0)
		printf("Large");
	else if (flag == 2 && capsLock == 1)
		printf("Small");
	gotoxy(15, 11);
	printf(".");
	gotoxy(16, 12);
	if (flag == 1 || flag == 2 || flag == 3)
		printf("SP");
	gotoxy(1, 15);
}

void space() //space(j, _where, consCheck, vowelCheck, whenSpace, save)
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
