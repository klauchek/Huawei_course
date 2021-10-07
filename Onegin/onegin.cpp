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

    unsigned char *buffer = (unsigned char *)calloc (file_size + 1, sizeof(char));
    fread(buffer, sizeof(char), file_size, file);
    return buffer;
}

//---------------------------
String* SeparateStrings(unsigned char* Buffer, size_t size, int* amount_of_strings)
{
    assert(Buffer);
    assert(size);

    size_t capacity = START_SIZE;
    
    String* string_ptrs = (String *)calloc (capacity, sizeof (String));
    assert(string_ptrs);
    
    unsigned char* cur_start = Buffer;        
    
    unsigned char* cur_last = (unsigned char *)memchr(cur_start, '\n', size);

    size_t new_size = size;
    size_t counter = 0;
    
    while (*cur_last != '\0')
    {
        string_ptrs[counter].str_beg = cur_start;

        string_ptrs[counter].str_beg[cur_last - cur_start] = '\0';
        string_ptrs[counter].length = cur_last - cur_start + 1;
        new_size = new_size - (cur_last - cur_start + 1);
        ++counter;

        cur_start = cur_last + 1;

        cur_last = (unsigned char *)memchr(cur_start, '\n', new_size);

        if (cur_last == NULL) 
        {
            string_ptrs[counter].str_beg = cur_start;
            string_ptrs[counter].str_beg[new_size] = '\0';
           *amount_of_strings = ++counter;
           return string_ptrs;
        }

        if((capacity - counter) < DELTA)
        {
            capacity *= 2;
            string_ptrs = (String*)realloc(string_ptrs, sizeof(String) * capacity);
        }
    
    }

    if (capacity != counter)
        string_ptrs = (String*) realloc(string_ptrs, sizeof(String) * counter);

    *amount_of_strings = ++counter;
    return string_ptrs;
}


//-----------------------------------------------------------
//сравниваются строки из Strings
 int StrcmpBegin(const void* str1, const void* str2)
 {
     assert(str1);
     assert(str2);

     const unsigned char* string1 = ((String*) str1)->str_beg;
     const unsigned char* string2 = ((String*) str2)->str_beg;
    
    

    while ((*string1 != '\0') && (*string2 != '\0'))
    {
        while(!isalpha (*string1) && (*string1) != '\0')
            ++string1;
        while(!isalpha (*string2) && (*string2) != '\0')
            ++string2;


        if (toupper (*string1) != toupper (*string2))
            break;

        ++string1;
        ++string2;

     }

 	return toupper(*string1) - toupper(*string2);
}

 int StrcmpEnd(const void* str1, const void* str2)
{
    assert(str1);
    assert(str2);

    const unsigned char* string1 = ((String*) str1)->str_beg + (((String*) str1)->length - 1);
    const unsigned char* string2 = ((String*) str2)->str_beg + (((String*) str2)->length - 1);
    const unsigned char* string1_end = ((String*) str1)->str_beg + (((String*) str1)->length - 1);
    const unsigned char* string2_end = ((String*) str2)->str_beg + (((String*) str2)->length - 1);


    while (true)
    {
        while(!isalpha (*string1) && (string1_end - string1 != ((String*) str1)->length - 1))
            --string1;
        while(!isalpha (*string2) && (string2_end - string2 != ((String*) str2)->length - 1))
            --string2;

        if (toupper (*string1) != toupper (*string2) || string1 == ((String*)str1)->str_beg || string2 == ((String*)str2)->str_beg)
            break;

        --string1;
        --string2;

    }

    return toupper(*string1) - toupper(*string2);
}


//-----------------------------------------------

void Qsort(String* strings, int low, int high, int (*comp)(const void* str1, const void* str2)) {

    assert(strings);

    if (low >= high)
        return;

    int pivot = low;
    int begin = low;
    int end = high;

    while (begin < end)
    {
        while (comp(strings + begin, strings + pivot) <= 0 && (begin <= high))
            ++begin;
        while (comp(strings + end, strings + pivot) > 0 && (end >= low))
            --end;

        if (begin < end)
            SwapStrs(strings + begin, strings + end);
    }

    SwapStrs(strings + end, strings + pivot);
    

    if (end > low)
        Qsort(strings, low, end - 1, comp);

    Qsort(strings, end + 1, high, comp);
}

//--------------------------------------------------
void SwapStrs(String* str1, String* str2) {

    assert(str1);
    assert(str2);

    String temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}


//----------------------------------------------------------------
void FileWrite(String* Strings, const int amount_of_strings, const char* output_file_name)
{
    assert(Strings);
    assert(amount_of_strings);
    assert(output_file_name);

    FILE* output = fopen(output_file_name, "w+");

    //qsort(Strings, amount_of_strings, sizeof (String), StrcmpBegin);
    Qsort(Strings, 0, amount_of_strings - 1, StrcmpBegin);
    
    fprintf(output, "Beginning sort\n\n");
    for (int i = 0; i < amount_of_strings; i++)
    {
        unsigned char* begin = Strings[i].str_beg;
        if(isspace(*begin))
            continue;
        
        fprintf(output, "%.*s\n", (int)Strings[i].length, begin);
    }


    fclose(output);
}








