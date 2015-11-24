#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

wchar_t in[1000];
int now = 0;

wchar_t consonant[10][3] = { { L'ㅇ', L'ㅁ' }, { L'ㅂ', L'ㅍ', L'ㅃ' }, { L'ㅅ', L'ㅎ', L'ㅆ' }, { L'ㅈ', L'ㅊ', L'ㅉ' },
{ L'ㄱ', L'ㅋ', L'ㄲ' }, { L'ㄴ', L'ㄹ' }, { L'ㄷ', L'ㅌ', L'ㄸ' },
{ L'ㅣ' }, { L'*' }, { L'ㅡ' } };
wchar_t vowel[5][7] = { { L'ㅣ', L' ', L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ' }
, { L'ㅡ', L'ㅢ', L'ㅜ', L'ㅟ', L'ㅠ', L'ㅝ', L'ㅞ' }
, { L'ㅓ', L'ㅔ' }
, { L' ', L'ㅕ', L'ㅖ', L'ㅛ' }
, { L'ㅗ', L'ㅚ', L' ', L'ㅘ', L'ㅙ' } };

int consCheck = 0;
int firstPosition = 0;
void gotoxy(int x, int y)
{
   printf("\033[%d;%dH", y + 1, x + 1);
}
int consonantPrint(int i)
{
   int check = 0;
   int quit = 0;
   int j = 0;
   if (k_flag == 1)
   {
      if (consonant[i][1] == ' ')
         k_flag = 0;
   }
   if (k_flag == 2)
   {
      if (consonant[i][2] == ' ')
         k_flag = 0;
   }
   if (k_flag == 3)
      k_flag = 0;
   if (consCheck == 0) //////얘는 초성이야
   {
   	 for (j = 0; j < 19; j++)
     	{
       		 if (wcHead[j] == consonant[i][k_flag])
       		 {
          		firstPosition = j; //////초성위치 결정 
           		break;
        	 }
     	 }
         in[_where] = wcHead[j];
  }
  else if (consCheck == 1)//얘는 종성
   {
      if (lastPosition2 == 0)
      {
         for (j = 0; j < 28; j++)
         {
            if (wcTail[j] == consonant[i][k_flag])
            {
               lastPosition2 = j;
               cpylastPosition = lastPosition;
               break;
            }
         }
	 if (lastPosition == 1) //ㄱ
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;// 
            if (wcTail[lastPosition2] == doubleSupport3[0])
            {
               lastPosition = 3;
               third_select = 1;
               quit = 1;
            }
            if (quit != 1)
               quit = 2;
         }
	else if (lastPosition == 4) //ㄴ
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;/
            for (j = 0; j < 2; j++)
            {
               if (wcTail[lastPosition2] == doubleSupport1[j])
               {
                  lastPosition = lastPosition + j + 1;
                  quit = 1;
                  third_select = 1;
                  break;
               }
            }
            if (quit != 1)
               quit = 2;
         }
	else if (lastPosition == 8) //ㄹ
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;///
            for (j = 0; j < 7; j++)
            {
               if (wcTail[lastPosition2] == doubleSupport2[j])
               {
                  lastPosition = lastPosition + j + 1;
                  quit = 1;
                  third_select = 1;
                  break;
               }
            }
            if (quit != 1)
               quit = 2;
         }
         else if (lastPosition == 17) //ㅂ
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;///
            if (wcTail[lastPosition2] == doubleSupport3[0])
            {
               lastPosition = 18;
               third_select = 1;
               quit = 1;
            }
            if (quit != 1)
               quit = 2;
         }
         else
            quit = 2;
         }
	if (quit == 0)
      {
         for (j = 0; j < 28; j++)
         {
            if (wcTail[j] == consonant[i][k_flag])
            {
               check = 1;
               lastPosition = j;
               in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28) + lastPosition;
               break;
            }
         }
       }
	 else if (quit == 2)
      {
         if (third_select == 100)
         {
            if (lastPosition == 7 || lastPosition == 16 || lastPosition == 19 || lastPosition == 21 || lastPosition == 22 ||
               lastPosition == 23 || lastPosition == 24 || lastPosition == 25 || lastPosition == 26 || lastPosition == 27)
               consCheck = 0;
            else
            {
               exception2 = 1;////
               cpyfirstPosition = firstPosition;
            }
         }
         else if (third_select == 200)
            _where--;
         else if (third_select == 1)
            third_select = 0;
         vowelCheck = 0;
         _where++;
         for (j = 0; j < 18; j++)
         {
            if (wcHead[j] == consonant[i][k_flag])
            {
               firstPosition = j;
               in[_where] = wcHead[j];
               if (third_select != 100)
                  consCheck = 0;
               break;
            }
         }
      }
   }
}
int main (void)
{
	return 0;
}
