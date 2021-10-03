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

enum Alloc
{
    MORE = 1,
    LESS = 0,
    DELTA = 50,
    START_SIZE = 512
};

size_t FileSize(const char* file_name);
unsigned char* CreateBuffer(FILE *file, int file_size);
String* SeparateStrings(unsigned char* Buffer, size_t size, int* amount_of_strings);
int Strcmp(const unsigned char* str1, const unsigned char* str2);

bool CheckSym(char sym);
void SwapStrPtr(String** str1, String** str2);
void Qsort(String** string_ptrs, int left, int right, int (*comp)(const char *, const char *));
void FileWrite(String* Strings, const int amount_of_strings, const char* output_file_name);

inline bool need_allocate(size_t size, size_t capacity, enum Alloc flag);

void str_array_realloc(String* str_array, size_t* str_arr_size, enum Alloc flag);



#endif //_ONEGIN_H_