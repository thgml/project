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
   if (consCheck == 0) //
   {
      for (j = 0; j < 19; j++)
      {
         if (wcHead[j] == consonant[i][k_flag])
         {
            firstPosition = j; // 
            break;
         }
      }
      in[_where] = wcHead[j];
   }
   else if (consCheck == 1)/
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
         if (lastPosition == 1) //
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
         else if (lastPosition == 4) //
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;//
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
         else if (lastPosition == 8) //
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;//
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
         else if (lastPosition == 17) //
         {
            if (third_select != 100)
               third_select = 100;
            else if (third_select == 100)
               third_select = 200;/////
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
         //////
         if (check != 1)
         {
            for (j = 0; j < 19; j++)
            {
               in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
               if (wcHead[j] == consonant[i][k_flag])
               {
                  exception1 = 1;
                  firstPosition = j;/
                  break;
               }
            }
            _where++;
            in[_where] = consonant[i][k_flag];
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
               exception2 = 1;///
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
      else
      {
         if (exception2 == 1) /
         {
            in[_where] = 0;
            _where--;
            firstPosition = cpyfirstPosition;
         }
         in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28) + lastPosition;
      }
   }
   else if (consCheck == 3)/
   {
      in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28) + cpylastPosition;
      _where++;
      for (j = 0; j < 19; j++)
      {
         if (wcHead[j] == consonant[i][k_flag])
         {
            firstPosition = j; ///
            break;
         }
      }
      in[_where] = wcHead[j];
      vowelCheck = 0;
      third_select = 0;
   }
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   k_flag++;
   return k_flag;
}
int vowelPrint(int i, int now, int vowel_sum)
{
   int j = 0;
   int k = 0;
   vowel_sum = vowel_sum + now;
   if (save == -100)
   {
      if (whatVowel == 2 || whatVowel == 10)
      {
         if (i == 1)
            i = 3;
         else if (i == 2)
            i = 4;
         else if (i == 3)
            i = 5;
      }
      else
      {
         if (i == 1)
            i = 1;
         else if (i == 3)
            i = 2;
      }
      save = i;
   }
}
void changeToKorean(wchar_t a)
{
	wchar_t ch;
	int cons_flag =0;
	int vowel_sum =0;
	int i =0;
	int j =0;
	in[_where] = a;
	if(in[_where] == '.')
		space();
	else
	{
		while(1)
		{
			ch = getche();
			if(ch =='+')
			{
				change();
				return ;
			}
			if(ch == '-')
			{
				if(eras == 0)
				{
					_where ++;
					eras = 100;
				}
				backspace();
				now =1;
				continue;
			}
			if(ch == '.')
			{
				_where++;
				space();
				if(eras !=0)
					eras =0;
				now =0;
				_where ++;
				continue;
			}
			else if(ch == '7' || ch =='8' || ch =='9')
			{
				if(whatVowel == -100)
				{
					if(ch =='7' || ch =='9')
						whatVowel =0;
					else if(ch == '8')//
					{
						whatVowel = 100;
						display();
						for(j =0 ;j<=_where;j++)
							printf("%s",unicode_to_utf8(in[j]);
						printf("%s",unicode_to_utf8(consonant[8][0]));
						continue;
					}
				}
				else if(whatVowel == 100)
				{
					if(ch =='8')
						whatVowel =10;
					else
						whatVowel =2;
				}
			}
		}
	}
}
int main (void)
{
	return 0;
}
