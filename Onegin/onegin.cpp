#include "onegin.h"


//---------------------------------------------------------------------
//! Function for defining the size of the file
//! @param [in]  file_name   name of the file 
//! 
//! @return size of the file
//----------------------------------------------------------------------
size_t FileSize(const char* file_name)
{ 
  assert (file_name);

  struct stat buff = {};
  stat (file_name, &buff);

  return buff.st_size;
}

//---------------------------------------------------------------------
//! Fuinctuon for creating a buffer with text from file
//! @param [in]  file        file 
//! @param [in]  file_size   size of the file 
//! 
//! @return buffer with text
//----------------------------------------------------------------------

unsigned char *CreateBuffer(FILE *file, int file_size)
{
    assert(file);

    unsigned char *buffer = (unsigned char *)calloc (file_size + 1, sizeof(char));
    assert(buffer);
    size_t result = fread(buffer, sizeof(char), file_size, file);
    assert(result);

    return buffer;
}


//---------------------------------------------------------------------
//! Fuinctuon for separating strings
//! @param [in]  Buffer            buffer with text from file
//! @param [in]  size              size of the buffer
//! @param [out] amount_of_strings amount of strings in buffer 
//! 
//! @return buffer of strings
//----------------------------------------------------------------------
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
            string_ptrs[counter].length = new_size;

           *amount_of_strings = ++counter;
           return string_ptrs;
        }

        if((capacity - counter) < DELTA)
        {
            capacity *= 2;
            string_ptrs = (String*) realloc(string_ptrs, sizeof(String) * capacity);

        }
    
    }

    if (capacity != counter)
        string_ptrs = (String*) realloc(string_ptrs, sizeof(String) * counter);


    *amount_of_strings = ++counter;
    return string_ptrs;
}


//---------------------------------------------------------------------
//! Fuinctuon for comparing strings from the beginning
//! @param [in]  str1  pointer to the first string
//! @param [in]  str2  pointer to the second string
//----------------------------------------------------------------------
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


//---------------------------------------------------------------------
//! Fuinctuon for comparing strings from the end
//! @param [in]  str1  pointer to the first string
//! @param [in]  str2  pointer to the second string
//----------------------------------------------------------------------
 int StrcmpEnd(const void* str1, const void* str2)
{
    assert(str1);
    assert(str2);

    const unsigned char* string1_beg = ((String*) str1)->str_beg;
    const unsigned char* string2_beg = ((String*) str2)->str_beg;
    const unsigned char* string1_end = ((String*) str1)->str_beg + (((String*) str1)->length - 1);
    const unsigned char* string2_end = ((String*) str2)->str_beg + (((String*) str2)->length - 1);


    while (true)
    {
        while(!isalpha (*string1_end) && (string1_end != string1_beg))
            --string1_end;
        while(!isalpha (*string2_end) && (string2_end != string2_beg))
            --string2_end;

        if (toupper (*string1_end) != toupper (*string2_end)|| string1_beg == string1_end || string2_beg == string2_end)
            break;

        --string1_end;
        --string2_end;

    }

    return toupper(*string1_end) - toupper(*string2_end); 
}

//---------------------------------------------------------------------
//! My qsort fuinctuon
//
//----------------------------------------------------------------------
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

//---------------------------------------------------------------------
//! Fuinctuon for swapping strings
//! @param [in]  str1  pointer to the first string
//! @param [in]  str2  pointer to the second string
//----------------------------------------------------------------------
void SwapStrs(String* str1, String* str2) {

    assert(str1);
    assert(str2);

    String temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}


//---------------------------------------------------------------------
//! Fuinctuon for sorting strings and creating files with sorted text
//! @param [in] Strings             buffer of strings
//! @param [in] amount_of_strings   amount of strings
//! @param [in] output_filename_beg name of the file with beginning sorting
//! @param [in] output_filename_end name of the file with ending sorting
//----------------------------------------------------------------------
void FileWrite(String* Strings, const int amount_of_strings, const char* output_filename_beg, const char* output_filename_end)
{
    assert(Strings);
    assert(amount_of_strings);
    assert(output_filename_beg);
    assert(output_filename_end);

    FILE* output_beg = fopen(output_filename_beg, "w+");

    qsort(Strings, amount_of_strings, sizeof (String), StrcmpBegin);
    //Qsort(Strings, 0, amount_of_strings - 1, StrcmpBegin);
    
    fprintf(output_beg, "Beginning sort\n\n");
    PrintStrings(output_beg, Strings, output_filename_beg, amount_of_strings);
    fclose(output_beg);

    FILE* output_end = fopen(output_filename_end, "w+");

    qsort(Strings, amount_of_strings, sizeof (String), StrcmpEnd);
    //Qsort(Strings, 0, amount_of_strings - 1, StrcmpEnd);

    fprintf(output_end, "Endinging sort\n\n");
    PrintStrings(output_end, Strings, output_filename_end, amount_of_strings);
    fclose(output_end);
}

//---------------------------------------------------------------------
//! Fuinctuon for writing sorted strings to file 
//! @param [in] output              file for sorted text
//! @param [in] amount_of_strings   amount of strings
//! @param [in] output_filename_beg name of the file
//----------------------------------------------------------------------
void PrintStrings(FILE* output, String* Strings, const char* output_file_name, const int amount_of_strings)
{
    for (int i = 0; i < amount_of_strings; i++)
    {
        unsigned char* begin = Strings[i].str_beg;
        if(*begin == '\0' || isspace(*begin))
            continue;
        fprintf(output, "%s\n", begin);
    }
}