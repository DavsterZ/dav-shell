#include "utils.h"

/*
 * RETURN
 *    0 -> If the strings are equals
 *    < 0 -> If str1 < str2
 *    > 0 -> If str1 > str2
 */
int utils_strcmp(const char* str1, const char* str2)
{
   while(*str1 && (*str1 == *str2))
  {
    str1++;
    str2++;
  }

  return *(unsigned char*)str1 - *(unsigned char*)str2;
}

