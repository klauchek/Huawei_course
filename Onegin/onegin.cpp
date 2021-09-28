#include "onegin.h"


//------------------------------------------------
//определить размер файла
size_t FileSize(const char* file_name)
{ 
  assert (file_name);

  struct stat buff;
  stat (file_name, &buff);

  return buff.st_size;
}
//----------------------------------------


//-----------------------------------------------
//считать полностью весь текст в буфер

char *CreateBuffer(FILE *file, int file_size)
{
    assert(file);

    char *buffer = (char *)calloc (file_size, sizeof(char));
    fread(buffer, sizeof(char), file_size, file);

    for (int i = 0; i < file_size; i++) {

        printf ("%c", buffer[i]);

    }

    printf ("\n");

    return buffer;
}

//---------------------------
int SeparateStrings(char* Buffer, String** strings, int size)
{
    assert(Buffer);
    assert(size);

    int str_arr_size = 128; //START SIZE?
    String* strings = (String *)calloc (str_arr_size, sizeof (String));

    char* cur_last = (char *)memchr(Buffer, '\n', size);
    char* cur_start = Buffer;

    int counter = 0;

    //отдельно проверка первой строки и сосчитать или не сосчитать ее 
    if (isspace(*cur_start))
    {
        if (cur_start == cur_last)
            cur_last = (char *)memchr(cur_start, '\n', size - *cur_start);

        while (isspace(*cur_start))
            ++cur_start;
    }
    strings[counter]->str_beg = cur_start;
    strings[counter]->str_end = cur_last;
    ++counter;

    //fist was valid
    while (cur_last != NULL)
    {
        cur_start = cur_last + 1;
        while (isspace(*cur_start))
        {
            if(*cur_start == size)
                break;

            if (*cur_start == '\n')
                continue;
            else
                ++cur_start;
        }

        cur_last = (char *)memchr(cur_start, '\n', size - *cur_start);
        strings[counter]->str_beg = cur_start;
        strings[counter]->str_end = cur_last;
        ++counter;

        //выделить память реаллоком если нужно
    }

    //очистка реаллоком лишней выделенной памяти
    return counter;
}



//------------------------------------------------------------

bool CheckSym(char sym)
{
    if((isalnum(sym) || ispunct(sym)) && (sym != '\0'))
        return true;
    return false;
}

//-----------------------------------------------------------
//сравниваются строки из Strings
// int Strcmp(const void* str1, const void* str2)
// {
//     assert(str1);
//     assert(str2);

//     const char* string1 = ((String**) str1)[0]->str_beg;
//     const char* string2 = ((String**) str2)[0]->str_beg;

//     while (*string1 != '\0' && *string2 != '\0')
//     {
//         if (toupper (*string1) == toupper (*string2))
//         {
//             ++string1;
//             ++string2;
//         }
//         else 
//         {
//             if (!isalpha (*string1))
//                 ++string1;
//             if (!isalpha (*string2))
//                 ++string2;
//         }
//     }

	
// 	return toupper(*string1) - toupper(*string2);
// }

int Strcmp (const void *first, const void *second )
{
  assert (first);
  assert (second);

  const char* str1 = ((String**) str1)[0]->str_beg;
  const char* str2 = ((String**) str2)[0]->str_beg;

  size_t char_count_1 = 0;
  size_t char_count_2 = 0;

  while (*str1 != '\0' && *str2 != '\0')
  {
    while (ispunct (str1[0]) || isdigit (str1[0]) || isspace (str1[0]))
      str1++;

    while (ispunct (str2[0]) || isdigit (str2[0]) || isspace (str2[0]))
      str2++;

    while (tolower(str1[0]) == tolower(str2[0]) )
    {
      str1++;
      str2++;
    }
    break;
  }

  return (tolower(str1[0]) - tolower(str2[0]));
}


//-----------------------------------------------

void SwapStrPtr(String** str1, String** str2)
{
    assert(str1);
    assert(str2);

    String* temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

/*
void Qsort(String** string_ptrs, int low, int high, int (*comp)(const char *, const char *))
{ 
    assert(string_ptrs);
    assert(comp);

    int left = low;
    int right = high;

    if (left >= right) 
        return; //в массиве менее двух элементов 

    const char* mid = string_ptrs[(right + left)/2]->str_beg;

    while(left <= right)
    {
        while ((*comp)(string_ptrs[left]->str_beg, mid))
            ++left;
        while ((*comp)(mid, string_ptrs[right]->str_beg))
            --right;
        if (left <= right)
            SwapStrPtr(&string_ptrs[left++], &string_ptrs[right--]);
    }

        if (low < right)
            Qsort(string_ptrs, low, right, Strcmp);

        if (left < high)
            Qsort(string_ptrs, left, high, Strcmp);
} 
*/

//----------------------------------------------------------------
void FileWrite(String** Strings, const int amount_of_strings, const char* output_file_name)
{
    assert(Strings_ptrs);
    assert(amount_of_strings);
    assert(output_file_name);

    FILE* output = fopen(output_file_name, "wb");

    qsort(Strings_ptrs, 0, amount_of_strings - 1, Strcmp);

    for (int i = 0; i < amount_of_strings; i++) {

        printf ("%s\n", Strings_ptrs[i]->str_beg);
    }
    fprintf(output, "Beginning sort\n\n");
    for (int i = 0; i < amount_of_strings; ++i)
        fprintf (output, "%s\n", Strings_ptrs[i]->str_beg);

    fclose(output);
}









