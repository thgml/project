#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

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

int main()
{
	change();
	change();	
	return 0;
}
