#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
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
   //초성 인지 혹은 종성인지 확인을 해야겠지....
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
               third_select = 200;////////ㄱ->ㅈ->ㅊ의 경우 없는 받침이지!
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
               third_select = 200;////////ㄱ->ㅈ->ㅊ의 경우 없는 받침이지!
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
               third_select = 200;////////ㄱ->ㅈ->ㅊ의 경우 없는 받침이지!
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
               third_select = 200;////////ㄱ->ㅈ->ㅊ의 경우 없는 받침이지!
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
         /////////받침이 이상할경우.. 깁->깊->기ㅃ?... 새로운 초성으로 가야겠지
         if (check != 1)
         {
            for (j = 0; j < 19; j++)
            {
               in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
               if (wcHead[j] == consonant[i][k_flag])
               {
                  exception1 = 1;
                  firstPosition = j;// 새로운 초성위치
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
               exception2 = 1;/////ㄴㅅ없지만 ㄶ는받침에 해당하자나 .... 한번더 기다려야겠지
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
         if (exception2 == 1) //많
         {
            in[_where] = 0;
            _where--;
            firstPosition = cpyfirstPosition;
         }
         in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28) + lastPosition;
      }
   }
   else if (consCheck == 3)//ㄵ-->ㄴ, ㅊ
   {
      in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28) + cpylastPosition;
      _where++;
      for (j = 0; j < 19; j++)
      {
         if (wcHead[j] == consonant[i][k_flag])
         {
            firstPosition = j; //////초성위치 결정 
            break;
         }
      }
      in[_where] = wcHead[j];
      vowelCheck = 0;
      third_select = 0;
   }
   //system("cls");
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
   for (j = 0; j < 21; j++)
   {
      if (wcMid[j] == vowel[save - 1][vowel_sum])
      {
         if (vowelCheck == 0) //첫번째 모음 관리
         {
            middlePosition = j;
            in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
            break;
         }
         else if (vowelCheck == 1) //받침으로 처리한 자음과 모음관리
         {
            if (exception1 == 0)
            {
               in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
               middlePosition = j;
               if (first_select == 0)
                  _where++;
               else if (first_select == 1)
               {
                  if (whatVowel == 10)// 오요우유..... 
                     _where++;
                  in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
               }
               for (k = 0; k < 19; k++)
               {
                  if (wcHead[k] == wcTail[lastPosition])
                  {
                     firstPosition = k;
                     in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
                     lastPosition = 0;
                     vowelCheck = 0;
                     break;
                  }
               }
               break;
            }
            else if (exception1 == 1)
            {
               middlePosition = j;
               in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
               vowelCheck = 0;
            }
         }
         else if (vowelCheck == 2) ////앉+ㅏ -->안자
         {
            in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28) + cpylastPosition;
            _where++;
            middlePosition = j;
            for (k = 0; k < 19; k++)
            {
               if (wcHead[k] == wcTail[lastPosition2])
               {
                  firstPosition = k;
                  in[_where] = 44032 + (firstPosition * 588) + (middlePosition * 28);
                  vowelCheck = 0;
                  break;
               }
            }

         }
      }
   }
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   return vowel_sum;
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
   setlocale(LC_ALL, "korean");
   wchar_t ch;
   while(1)
   {
	
   }
}
