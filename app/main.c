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
wchar_t consonant[10][3] = { { L'ㅇ', L'ㅁ' }, { L'ㅂ', L'ㅍ', L'ㅃ' }, { L'ㅅ', L'ㅎ', L'ㅆ' }, { L'ㅈ', L'ㅊ', L'ㅉ' },
{ L'ㄱ', L'ㅋ', L'ㄲ' }, { L'ㄴ', L'ㄹ' }, { L'ㄷ', L'ㅌ', L'ㄸ' },
{ L'ㅣ' }, { L'*' }, { L'ㅡ' } };
wchar_t vowel[5][7] = { { L'ㅣ', L' ', L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ' }
, { L'ㅡ', L'ㅢ', L'ㅜ', L'ㅟ', L'ㅠ', L'ㅝ', L'ㅞ' }
, { L'ㅓ', L'ㅔ' }
, { L' ', L'ㅕ', L'ㅖ', L'ㅛ' }
, { L'ㅗ', L'ㅚ', L' ', L'ㅘ', L'ㅙ' } };
wchar_t doubleSupport1[] = { L'ㅈ', L'ㅎ' };//ㄴ받침
wchar_t doubleSupport2[] = { L'ㄱ', L'ㅁ', L'ㅂ', L'ㅅ', L'ㅌ', L'ㅍ', L'ㅎ' }; //ㄹ
wchar_t doubleSupport3[] = { L'ㅅ' };//ㄱ,ㅂ 받침
//초성
static const wchar_t wcHead[] = { L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ',
L'ㄸ', L'ㄹ', L'ㅁ', L'ㅂ',
L'ㅃ', L'ㅅ', L'ㅆ', L'ㅇ',
L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ',
L'ㅌ', L'ㅍ', L'ㅎ' };
//중성
static const wchar_t wcMid[] = { L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ',
L'ㅓ', L'ㅔ', L'ㅕ', L'ㅖ',
L'ㅗ', L'ㅘ', L'ㅙ', L'ㅚ',
L'ㅛ', L'ㅜ', L'ㅝ', L'ㅞ',
L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ', L'ㅣ' };
//종성
static const wchar_t wcTail[] = { L' ', L'ㄱ', L'ㄲ', L'ㄳ',
L'ㄴ', L'ㄵ', L'ㄶ', L'ㄷ',
L'ㄹ', L'ㄺ', L'ㄻ', L'ㄼ',
L'ㄽ', L'ㄾ', L'ㄿ', L'ㅀ',
L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ',
L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ',
L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ' };
int firstPosition = 0, cpyfirstPosition = 0;
int middlePosition;
int lastPosition = 0, lastPosition2 = -100, cpylastPosition = 0;//복사본
int doubleCons = 0;
int _where = 0;
int flag = 1;
int eras = 0; //영어 backspace
int consCheck = 0; //초성인지 , 종성인지 확인해야지
int vowelCheck = 0; ///첫번째 모은인지 두번째 모음인지...
int first_select = 0, second_select = 0, third_select = 0; // 자음이 결정 되어있는지  ///자리때문에 전역으로
int exception1 = 0, exception2 = 0;// 기삐 두번쨰 모음 예외
int whatVowel = -100;/////////8번먼저 눌렸을때
int save = -100, whenSpace = 0, whenBackspace = 0, whenChange = 0; //임시저장
int k_flag = 0;
int capsLock = 0;

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
         if (flag == 1)
         {
            for (z = 0; z <= 2; z += 1)
               printf("%s", unicode_to_utf8(consonant[cnt][z]));
         }
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
   if (flag == 1)
      printf("%s%s", unicode_to_utf8(consonant[0][0]), unicode_to_utf8(consonant[0][1]));
   else if (flag == 2 && capsLock == 0)
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
   system("clear");
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
   system("clear");
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
void change()
{
   int j = 0;
   if (flag == 2 || flag == 3)
   {
      if (now == 1)
         _where--;
   }
   system("clear");
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   if (flag == 1)
      flag = 2;
   else if (flag == 2)
      flag = 3;
   else if (flag == 3)
      flag = 1;
   system("clear");
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
void changeToNum(wchar_t a)
{
   wchar_t ch;
   in[_where] = a;
   if (in[_where] == '0')
      space();
   else
   {
      while (1)
      {
         ch = getche();
         if (ch == '+')
         {
            change();
            return;
         }
         if (ch == '.') //space
         {
            _where++;
            space();
            if (eras != 0)
               eras = 0;
            now = 0;
            continue;
         }
         if (ch == '-') //지우기
         {
            if (eras == 0)
            {
               _where++;
               eras = 100;
            }
            backspace();
            now = 1;
            continue;
         }
         else
         {
            _where++;
            in[_where] = ch;
            if (eras != 0)
               eras = 0;
            now = 0;
         }
      }
   }
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
   system("clear");
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
   system("clear");
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
   system("clear");
   display();
   for (j = 0; j <= _where; j++)
      printf("%s", unicode_to_utf8(in[j]));
   return vowel_sum;
}
void changeToKorean(wchar_t a)
{
   wchar_t ch;
   int cons_flag = 0;
   int vowel_sum = 0;
   int i = 0;
   int j = 0;
   in[_where] = a;
   if (in[_where] == '.')
      space();
   else
   {
      cons_flag = consonantPrint(a - '0');
      consCheck = 0;
      while (1)
      {
         ch = getche();
         if (ch == '+')
         {
            change();
            return;
         }
         if (ch == '-')
         {
            if (eras == 0)
            {
               _where++;
               eras = 100;
            }
            backspace();
            now = 1;
            continue;
         }
         if (ch == '.')
         {
            _where++;
            space();
            if (eras != 0)
               eras = 0;
            now = 0;
            _where++;
            continue;
         }
         else if (ch == '7' || ch == '8' || ch == '9')
         {
            if (whatVowel == -100)
            {
               if (ch == '7' || ch == '9')
                  whatVowel = 0;
               else if (ch == '8')//처음에 .... 맨처음에 8 들어왔을때
               {
                  whatVowel = 100;
                  system("clear");
                  display();
                  for (j = 0; j <= _where; j++)
                     printf("%s", unicode_to_utf8(in[j]));
                  printf("%s", unicode_to_utf8(consonant[8][0]));
                  continue;
               }
            }
            else if (whatVowel == 100)
            {
               if (ch == '8')
                  whatVowel = 10;
               else
                  whatVowel = 2;
            }
            if (vowelCheck == 0) //입력한 자음이 안바뀌고 바로 모음 온 상태
            {
               if (whenSpace == 1)
               {
                  vowel_sum = 0;
                  lastPosition2 = 100;
                  whenSpace = 10;
               }
               if (whenBackspace == 1)
               {
                  vowel_sum = 0;
                  lastPosition2 = 100;
                  whenBackspace = 0;
               }
               if (whenChange == 1)
               {
                  vowel_sum = 0;
                  lastPosition2 = 100;
                  whenChange = 0;
               }
               consCheck = 1;
               lastPosition = 0;
               k_flag = 0;
            }
            else if (vowelCheck == 1)
            {
               if (exception2 == 1)
               {
                  vowelCheck = 2;
                  third_select = 0;
                  exception2 = 0;
               }
               consCheck = 1;
            }
            if (third_select == 1)
            {
               if (vowelCheck != 0)
               {
                  vowelCheck = 2;
                  third_select = 0;
               }
            }
            if (first_select == 0)
            {
               i = ch - '0' - 6;
               vowelPrint(i, 0, vowel_sum);
               first_select = 1;
            }
            else
               vowel_sum = vowelPrint(i, ch - '0' - 6, vowel_sum);
            a = 0;
            continue;
         }
         else
         {
            if (consCheck == 0) //처음에 입력한 자음이 바뀔때 ㅂ->ㅍ ->ㅃ
            {
               vowelCheck = 0;
               first_select = 0;
            }
            else if (consCheck == 1) //자+모 완성된거야 따라서 받침생성이지
            {
               vowelCheck = 1;
               vowel_sum = 0;
               first_select = 0;
            }
            if (ch == a) ///똑같은거 눌렸을때 ㄱ->ㅋ ->ㄲ
            {
               if (exception2 == 1)
                  lastPosition2 = 0;
               if (third_select == 1)
                  consCheck = 3;
               if (exception1 == 1)
                  exception1 = 0;
               a = ch;
               cons_flag = consonantPrint(a - '0');
               first_select = 0; //새로운 자음
               whatVowel = -100;
               save = -100;
            }
            else  /////ㄱ -> ㅈ -> ㅇ
            {
               if (exception2 == 1)
                  exception2 = 0;
               if (consCheck == 1)
                  k_flag = 0;
               if (lastPosition != 0)
                  lastPosition2 = 0;
               if (exception1 == 1)
                  exception1 = 0;
               a = ch;
               cons_flag = 0;
               cons_flag = consonantPrint(a - '0');
               first_select = 0; //새로운 자음
               whatVowel = -100;
               save = -100;
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
int main(void)
{
   setlocale(LC_ALL, "korean");
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
      if (flag == 1) //한글
      {
         changeToKorean(ch);
      }
      else if (flag == 2) //영어
         changeToEnglish(ch);
      else if (flag == 3) //숫자
         changeToNum(ch);
      _where++;
   }
} 
