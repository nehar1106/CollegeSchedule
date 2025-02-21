/**
@file input.h
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
char *readLine(FILE *fp);