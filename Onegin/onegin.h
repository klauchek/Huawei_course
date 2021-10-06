#ifndef _ONEGIN_H_
#define _ONEGIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <locale.h>
#include <sys/stat.h>


struct String
{
    unsigned char* str_beg;
    int length; 
};

const long int START_SIZE = 512;
const int DELTA = 100;

size_t FileSize(const char* file_name);
unsigned char* CreateBuffer(FILE *file, int file_size);
String* SeparateStrings(unsigned char* Buffer, size_t size, int* amount_of_strings);
int StrcmpBegin(const void* str1, const void* str2);
int StrcmpEnd(const void* str1, const void* str2);
void SwapStrPtr(String** str1, String** str2);
void Qsort(String** string_ptrs, int left, int right, int (*comp)(const char *, const char *));
void FileWrite(String* Strings, const int amount_of_strings, const char* output_file_name);



#endif //_ONEGIN_H_