#include <stdio.h>

void gotoxy(int x, int y)
{
	printf("%d;%d", y + 1, x + 1);
	printf("\n");
}

int main()
{
	gotoxy(10,10);

	return 1;
}
