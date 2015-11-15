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
       }
   }
}
int main (void)
{
	return 0;
}
