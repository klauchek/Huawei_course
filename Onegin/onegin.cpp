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

    return buffer;
}

//------------------------------------------------
int CountStrings(char* Buffer, int size)
{
    assert(Buffer);
    assert(size);

    int buf_counter = 0; //считает считанные символы
    int str_amount = 0; //считает строки
    while(buf_counter < size)
    {
        if (Buffer[buf_counter] == '\n')
        {
            ++str_amount;
            while(isspace(Buffer[buf_counter]) || (Buffer[buf_counter] == '\0'))
            {
                Buffer[buf_counter] = '\0';
                ++buf_counter;

                if(buf_counter == size)  
                    break;
            }
        }
        else
            buf_counter++;
    }

    return str_amount;
}

//---------------------------
String* CreateStringsBuffer(char* Buffer, int amount_of_strings, int size)
{
    assert(Buffer);
    assert(size);
    assert(amount_of_strings);

    String* strings = (String *)calloc (amount_of_strings, sizeof (String));

    int str_counter = 0;
    int buf_counter = 0;

    while (buf_counter < size)
    {
     
        if (Buffer[buf_counter] == '\0')
        {
            //проверяем конец строки
            int end = buf_counter - 1;
            if(!CheckSym(Buffer[end])) 
            {
                while(isspace(Buffer[end]))
                    --end;
                //просто сдвигаем конец обратно
            }
            //это конец строки, все ок
            strings[str_counter].str_end = &(Buffer[end]);
            ++str_counter;

            while(Buffer[buf_counter] == '\0') //пошли дальше считать
                        ++buf_counter;
        }
        else
        {
            if((buf_counter == 0)  || (Buffer[buf_counter - 1] == '\0'))
                strings[str_counter].str_beg = &(Buffer[buf_counter]);
            
            ++buf_counter;
        }  
    }

    return strings;
}


//----------------------------------------------------------

String** CreateStringsPtrsBuffer(String* Strings, int amount_of_strings)
{
    assert(amount_of_strings);
    assert(Strings);

    String** Strings_ptrs = (String **) calloc (amount_of_strings, sizeof (String *));

        //СВЯЗАТЬ ЭЛЕМЕНТЫ МАСССИВА СТРОК С ЭЛЕМЕНТАМИ МАССИВА УКАЗАТЕЛЕЙ
    for (int i = 0; i < amount_of_strings; i++)
        (Strings_ptrs)[i] = &(Strings)[i];

    return Strings_ptrs;
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
int Strcmp(const char* string1, const char* string2)
{
    assert(string1);
    assert(string2);

    while (*string1 != '\0' && *string2 != '\0')
    {
        if (toupper (*string1) == toupper (*string2))//при совпадении продвигаемся далее
        {
            ++string1;
            ++string2;
        }
        else //символы не совпали, но символ - не буква
        {
            if (!isalpha (*string1))
                ++string1;
            if (!isalpha (*string2))
                ++string2;
        }
    }

	
	return toupper(*string1) - toupper(*string2);
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

void Qsort(String** string_ptrs, int low, int high, int (*comp)(const char *, const char *))
{ 
    assert(string_ptrs);
    assert(comp);

    int left = low;
    int right = high;

    if (left >= right) 
        return; /* в массиве менее двух элементов */

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


//----------------------------------------------------------------
void FileWrite(String** Strings_ptrs, const int amount_of_strings, const char* output_file_name)
{
    assert(Strings_ptrs);
    assert(amount_of_strings);
    assert(output_file_name);

    FILE* output = fopen(output_file_name, "wb");

    Qsort(Strings_ptrs, 0, amount_of_strings - 1, Strcmp);

    fprintf(output, "Beginning sort\n\n");
    for (int i = 0; i < amount_of_strings; ++i)
        fprintf (output, "%s\n", Strings_ptrs[i]->str_beg);

    fclose(output);
}