#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

void change()
{
	int j = 0;
	int _where;
	char in[1000];
	
	if(1) // flag condition
	{
		if(1) // current
			_where--;
	}

	// display

	for(j=0; j<=_where; j++)
		printf("%s", unicode_to_utf8(in[j]));

	
	// display
	for(j=0; j<=_where; j++)
		printf("%s", unicode_to_utf8(in[j]));	

}

int main()
{
	change();	

	return 0;
}
