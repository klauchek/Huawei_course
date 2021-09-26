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

//void ReadFromFile();
size_t FileSize(const char* file_name);
char* CreateBuffer(FILE *file, int file_size);
int CountStrings(char* Buffer, int file_size);
String* CreateStringsBuffer(char* Buffer, int amount_of_strings, int size);
String** CreateStringsPtrsBuffer(String* Strings, int amount_of_strings);
bool check_sym(char sym);



#endif //_ONEGIN_H_