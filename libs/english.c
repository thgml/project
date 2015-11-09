#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>


wchar_t in[1000];
int now = 0; // 방금 전에 지웠는가 안지웠는가
wchar_t englishSmall[10][4] = { {}, { 'p', 'q', 'r', 's' }, { 't', 'u', 'v' }, { 'w', 'x', 'y', 'z' },
{ 'g', 'h', 'i' }, { 'j', 'k', 'l' }, { 'm', 'n', 'o' },
{ '.', '?', '!' }, { 'a', 'b', 'c' }, { 'd', 'e', 'f' } };
wchar_t englishLarge[10][4] = { {}, { 'P', 'Q', 'R', 'S' }, { 'T', 'U', 'V' }, { 'W', 'X', 'Y', 'Z' },
{ 'G', 'H', 'I' }, { 'J', 'K', 'L' }, { 'M', 'N', 'O' },
{ '.', '?', '!' }, { 'A', 'B', 'C' }, { 'D', 'E', 'F' } };
int firstPosition = 0, cpyfirstPosition = 0;
int middlePosition;
int lastPosition = 0, lastPosition2 = -100, cpylastPosition = 0;//복사본
int doubleCons = 0;
int _where = 0;
int flag = 2;
int eras = 0; //영어 backspace
int consCheck = 0; //초성인지 , 종성인지 확인해야지
int vowelCheck = 0; ///첫번째 모은인지 두번째 모음인지...
int first_select = 0, second_select = 0, third_select = 0; // 자음이 결정 되어있는지  ///자리때문에 전역으로
int exception1 = 0, exception2 = 0;// 기삐 두번쨰 모음 예외
int whatVowel = -100;/////////8번먼저 눌렸을때
int save = -100, whenSpace = 0, whenBackspace = 0, whenChange = 0; //임시저장
int k_flag = 0;
int capsLock = 0;
const char* unicode_to_utf8(wchar_t c)
{
   static unsigned char b_static[5];
   unsigned char* b = b_static;

   if (c<(1 << 7))// 7 bit Unicode encoded as plain ascii
   {
      *b++ = (unsigned char)(c);
   }
   else if (c<(1 << 11))// 11 bit Unicode encoded in 2 UTF-8 bytes
   {
      *b++ = (unsigned char)((c >> 6) | 0xC0);
      *b++ = (unsigned char)((c & 0x3F) | 0x80);
   }
   else if (c<(1 << 16))// 16 bit Unicode encoded in 3 UTF-8 bytes
   {
      *b++ = (unsigned char)(((c >> 12)) | 0xE0);
      *b++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
      *b++ = (unsigned char)((c & 0x3F) | 0x80);
   }

   else if (c<(1 << 21))// 21 bit Unicode encoded in 4 UTF-8 bytes
   {
      *b++ = (unsigned char)(((c >> 18)) | 0xF0);
      *b++ = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
      *b++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
      *b++ = (unsigned char)((c & 0x3F) | 0x80);
   }
   *b = '\0';
   return b_static;
}
void gotoxy(int x, int y)
{
   printf("\033[%d;%dH", y + 1, x + 1);
}
void display()
{
   int y, x, z, cnt = 6;
   for (y = 2; y <= 8; y += 3)
   {
      for (x = 3; x <= 15; x += 6)
      {
         gotoxy(x, y);
         printf("%d", ++cnt);
         gotoxy(x + 1, y + 1);
         if (flag == 2 && capsLock == 0)
         {
            for (z = 0; z <= 3; z += 1)
               printf("%s", unicode_to_utf8(englishSmall[cnt][z]));

         }
         if (flag == 2 && capsLock == 1)
         {
            for (z = 0; z <= 3; z += 1)
               printf("%s", unicode_to_utf8(englishLarge[cnt][z]));
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
   if (flag == 2 && capsLock == 0)
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
void change()
{
   int j = 0;
   if (flag == 2 || flag == 3)
   {
      if (now == 1)
         _where--;
   }
   //system("cls");
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   if (flag == 1)
      flag = 2;
   else if (flag == 2)
      flag = 3;
   else if (flag == 3)
      flag = 1;
   //system("cls");
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   whenChange = 1;
   consCheck = 0;
   vowelCheck = 0;
   save = -100;
   k_flag = 0;
   now = 0;
   return;
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
   consCheck = 0;
   vowelCheck = 0;
   save = -100;
   whenBackspace = 1;
   k_flag = 0;
   //system("cls");
   display();
   if (_where <= 0)
   {
      _where = 0;
      eras = 0;
   }
   in[_where] = 0;
   for (j = 0; j < _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
}
void space()
{
   int j = 0;
   //system("cls");
   display();
   in[_where] = ' ';
   consCheck = 0;
   vowelCheck = 0;
   whenSpace = 1;
   save = -100;
   k_flag = 0;
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
}
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
   wchar_t ch;
   display();
   while (1)
   {
      ch = getche();
      if (ch == '-')
      {
         backspace();
         continue;
      }
      if (ch == '+')
      {
         change();
         continue;
      }
      if (flag == 2) //영어
         changeToEnglish(ch);
      _where++;
   }
}
