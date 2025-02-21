/**
@file input.c
@author Neha Ramesh (nramesh3)
This programs helps with reading in lines from a file
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**
 Function that reads a line from the file
 @param fp for the file we are reading from
 @return a string
 */
char *readLine (FILE *fp)
{
// 	printf ("In Input.c - readLine\n");

   int i = 0;
   int size = 0;
   char val;
   int cnt = 0;
   int repos;
   int capacity = 10;
   char *str = (char *) malloc(capacity + 1);
   while (fscanf (fp, "%c", &val) == 1) {
      if (val == EOF || val == '\n') {
         break;
      }
      str[i++] = val;
      cnt++;
      if (cnt > capacity) {
         capacity = capacity * 2;
         str = (char *)realloc (str, (capacity * 1 + 1) );
      }
   }
   str[i++] = '\0';
   return str;
}