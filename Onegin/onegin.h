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
    const char* str_beg;
    const char* str_end; 
};

size_t FileSize(const char* file_name);
char* CreateBuffer(FILE *file, int file_size);
int CountStrings(char* Buffer, int file_size);
String* CreateStringsBuffer(char* Buffer, int amount_of_strings, int size);
int Strcmp(const char* str1, const char* str2);
bool CheckSym(char sym);
void SwapStrPtr(String** str1, String** str2);
void Qsort(String** string_ptrs, int left, int right, int (*comp)(const char *, const char *));
void FileWrite(String** StringsPtrs, const int amount_of_strings, const char* output_file_name);



#endif //_ONEGIN_H_