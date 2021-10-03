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

unsigned char *CreateBuffer(FILE *file, int file_size)
{
    assert(file);

    unsigned char *buffer = (unsigned char *)calloc (file_size, sizeof(char));
    fread(buffer, sizeof(char), file_size, file);
    return buffer;
}

//---------------------------
String* SeparateStrings(unsigned char* Buffer, size_t size, int* amount_of_strings)
{
    assert(Buffer);
    assert(size);

    size_t capacity = 512;//START SIZE?
    
    String* string_ptrs = (String *)calloc (capacity, sizeof (String));
    assert(string_ptrs);
    
    unsigned char* cur_start = Buffer;        
    unsigned char* cur_last = (unsigned char *)memchr(cur_start, '\n', size);


    printf("cur_start_prev: %c\n", *(cur_start - 1));
    printf("cur_start: %c\n", *cur_start);
    printf("cur_last_prev: %c\n", *(cur_last - 1));
    printf("cur_last: %c\n", *cur_last);

    unsigned char* prev_last = nullptr;
    size_t new_size = size;
    size_t counter = 0;

    while (cur_last != NULL)
    {
        if (cur_last - 1 == prev_last && *prev_last == '\n')
            while (!isalpha(*cur_last))
                ++cur_last;

        string_ptrs[counter].str_beg = cur_start;
        string_ptrs[counter].length = cur_last - cur_start + 1;

        new_size = new_size - (cur_last - cur_start + 1);
        ++counter;
    
        cur_start = cur_last + 1;
        prev_last = cur_last;
        cur_last = (unsigned char *)memchr(cur_start, '\n', new_size);

        if (need_allocate(counter, capacity, MORE))   
            str_array_realloc(string_ptrs, &capacity, MORE); 
    }
    

        printf("cur_start_prev: %c\n", *(cur_start - 1));
        printf("cur_start: %c\n", *cur_start);
        printf("cur_last_prev: %c\n", *(cur_last - 1));
        printf("cur_last: %c\n", *cur_last);
        printf("\n");


    if (need_allocate(counter, capacity, LESS))   
        str_array_realloc(string_ptrs, &counter, LESS); 

    *amount_of_strings = ++counter;
    return string_ptrs;
}




inline bool need_allocate(size_t size, size_t capacity, enum Alloc flag) {
    if (flag)
        return (size != capacity);      /* if size != capacity => return false => allocate is need */
    return (capacity - size) < DELTA;
}


//----------------------------------------------------------------------------

void str_array_realloc(String* str_array, size_t* str_arr_size, enum Alloc flag) {

    assert(str_array);
    assert(str_arr_size);

    if (flag)
        *str_arr_size *= 2; 

    String* new_str_arr = (String*) realloc(str_array, sizeof(String) * (*str_arr_size));
    assert(new_str_arr);

    str_array = new_str_arr;
}



       /* 
       кусок для проверки первой строки

       if (cur_start == cur_last)
        {
            cur_last = (unsigned char *)memchr(cur_start, '\n', size - (cur_start - Buffer));
            while(isspace(*cur_start))
                ++cur_start;
            ++counter;
        }
*/


//-----------------------------------------------------------
//сравниваются строки из Strings
 int Strcmp(const void* str1, const void* str2)
 {
     assert(str1);
     assert(str2);

     const unsigned char* string1 = ((String*) str1)[0].str_beg;
     const unsigned char* string2 = ((String*) str2)[0].str_beg;
    
    

    while ((*string1 != '\n') && (*string2 != '\n'))
    {
        while(!isalpha (*string1) && (*string1 != '\n'))
            ++string1;
        while(!isalpha (*string2) && (*string2 != '\n'))
            ++string2;


        if (toupper (*string1) != toupper (*string2))
            break;

        ++string1;
        ++string2;

     }

 	return toupper(*string1) - toupper(*string2);
}

/*
int Strcmp (const void *first, const void *second )
{
  assert (first);
  assert (second);

  const unsigned char* str1 = ((String*) str1)[0].str_beg;
  const unsigned char* str2 = ((String*) str2)[0].str_beg;

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
*/


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
void FileWrite(String* Strings, const int amount_of_strings, const char* output_file_name)
{
    assert(Strings);
    assert(amount_of_strings);
    assert(output_file_name);

    FILE* output = fopen(output_file_name, "w+");
    printf ("%.*s\n", Strings[0].length, Strings[0].str_beg);
    printf ("%.*s\n", Strings[1].length, Strings[1].str_beg);
    printf ("%.*s\n", Strings[2].length, Strings[2].str_beg);
    printf ("%.*s\n", Strings[3].length, Strings[3].str_beg);
    printf ("%.*s\n", Strings[4].length, Strings[4].str_beg);



    printf("hui\n");
    qsort(Strings, 0, amount_of_strings - 1, Strcmp);
    printf("hui2\n");
    
    
    /*for (int i = 0; i < amount_of_strings; i++)
    {
        unsigned char* begin = Strings[i].str_beg;
        if(isspace(*begin))
            continue;

        fprintf (output, "%.*s\n", Strings[i].length, begin);
    }
    */
    printf ("%.*s\n", Strings[0].length, Strings[0].str_beg);
    printf ("%.*s\n", Strings[1].length, Strings[1].str_beg);
    printf ("%.*s\n", Strings[2].length, Strings[2].str_beg);
    printf ("%.*s\n", Strings[3].length, Strings[3].str_beg);
    printf ("%.*s\n", Strings[4].length, Strings[4].str_beg);

    //fprintf(output, "Beginning sort\n\n");
    printf ("str amount: %d\n", amount_of_strings);  


    printf ("%.*s\n", Strings[0].length, Strings[0].str_beg);
    printf ("%.*s\n", Strings[1].length, Strings[1].str_beg);
    printf ("%.*s\n", Strings[2].length, Strings[2].str_beg);
    printf ("%.*s\n", Strings[3].length, Strings[3].str_beg);
    printf ("%.*s\n", Strings[4].length, Strings[4].str_beg);


    fclose(output);
}








