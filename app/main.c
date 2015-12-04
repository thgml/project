#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

int englishArayPrint(int i, int e_flag, int capsLock)
{
   int j = 0;
   if (e_flag == 3)
   {
      if (englishSmall[i][3] == ' ')
         e_flag = 0;
   }
   if (e_flag == 4)
      e_flag = 0;
   if (capsLock == 0)
      in[_where] = englishSmall[i][e_flag];  //소문자
   else if (capsLock == 1)
      in[_where] = englishLarge[i][e_flag];  //대문자
   //system("cls");
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   e_flag++;

   return e_flag;
}

void changeToEnglish(wchar_t a)
{
   wchar_t ch;
   int e_flag = 0;
   in[_where] = a;
   if (in[_where] == 0)
      space();
   else
   {
      if (in[_where] == '0') //처음에 캡스락 켰냐 안켰냐
         capsLock = 1;
      else
         e_flag = englishArayPrint(a - '0', e_flag, capsLock);
      while (1)
      {
         ch = getche();
         if (ch == '+')
         {
            change();
            return;
         }
         if (ch == '.')
         {
            _where++;
            space();
            a = ch;
            if (eras != 0)
               eras = 0;
            now = 0;
            continue;
         }
         if (ch == '0')
         {
            if (capsLock == 0)
               capsLock = 1;
            else
               capsLock = 0;
            if (eras != 0)
               eras = 0;
            _where++;
            in[_where] = ch;
            e_flag = 0;
            continue;
         }
         if (ch == '-')
         {
            if (eras == 0)
            {
               _where++;
               eras = 100;
            }
            e_flag = 0;
            backspace();
            now = 1;
            continue;
         }
         if (ch == a) //같은건가
         {
            e_flag = englishArayPrint(a - '0', e_flag, capsLock);
            if (eras != 0)
               eras = 0;
            now = 0;
         }
         else  //같지 않아
         {
            if (in[_where] == '0')  // 바로 전에 capsLock눌렀나
            {
               a = ch;
               e_flag = 0;
               in[_where] = ch;
               e_flag = englishArayPrint(ch - '0', e_flag, capsLock);
               if (eras != 0)
                  eras = 0;
               now = 0;
            }
            else
            {
               a = ch;
               e_flag = 0;
               if (now == 0)
                  _where++;
               in[_where] = ch;
               e_flag = englishArayPrint(ch - '0', e_flag, capsLock);
               if (eras != 0)
                  eras = 0;
               now = 0;
            }
         }

      }

   }
}
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

int main (void)
{
   setlocale(LC_ALL, "korean");
   wchar_t ch;
   while(1)
   {
	
   }
}
