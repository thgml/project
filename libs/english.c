#include <stdio.h>

char in[1000];
char englishSmall[10][4] = { {}, { 'p', 'q', 'r', 's' }, { 't', 'u', 'v' }, { 'w', 'x', 'y', 'z' },
{ 'g', 'h', 'i' }, { 'j', 'k', 'l' }, { 'm', 'n', 'o' },
{ '.', '?', '!' }, { 'a', 'b', 'c' }, { 'd', 'e', 'f' } };
char englishLarge[10][4] = { {}, { 'P', 'Q', 'R', 'S' }, { 'T', 'U', 'V' }, { 'W', 'X', 'Y', 'Z' },
{ 'G', 'H', 'I' }, { 'J', 'K', 'L' }, { 'M', 'N', 'O' },
{ '.', '?', '!' }, { 'A', 'B', 'C' }, { 'D', 'E', 'F' } };

int _where =0;
int main (void)
{
	char ch;
	while(1)
	{
		ch = getche();
		changeToNum(ch);
	}
}
