#include <stdio.h>

void backspace()
{
	int whenSpace = 0;
	int _where = 0;
	int in[10];

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
