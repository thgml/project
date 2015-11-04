void changeToNum(char a)
{
   char ch;
   in[_where] = a;

   if (in[_where] == '0')
      printf(" ");
   else
   {
      while (1)
      {
         ch = getche();
          _where++;
          in[_where] = ch;
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
}
