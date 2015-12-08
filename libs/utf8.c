#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

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
