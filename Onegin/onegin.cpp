#include "onegin.h"




/*void ReadFromFile(const char **string_ptrs, const char *file_name)
{
    FILE* input = fopen(file_name, "rb");
    char str[1000] = 
    while()
    {
        fgets();
        Index[i] = strdup(str);
        i++
    }

    fclose(input);
    
} 
*/


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
    assert(file != NULL);

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
    //будем считывать строку(детектить символы \n и заменять на \0 пока не дойдет до буквы)
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
    assert(amount_of_strings);

    String* strings = (String *)calloc (amount_of_strings, sizeof (String));

// НЕ ИСПОЛЬЗУЕМ СТРОКОВЫЕ ФУНКЦИИ, ПОЭТОМУ \0 МОЖЕТ БЫТЬ ВАЩЕ ЛЕВЫМ СИМВОЛОМ
//НУЖНА ПРОВЕРКА НА ТО, ЧТО ОН ИМЕННО КОНЕЦ СТРОКИ, Т.Е. ПЕРЕД НИМ    Б У К В Ы, А ПОСЛЕ НЕГО КАКОЙ-ТО СИМВОЛ (ОБЯЩАТЕЛЬНО НЕ \0!!!!!! А КАКОЙ-ТО ДРУГОЙ )
    int str_counter = 0;
    int buf_counter = 0;

    while (buf_counter < size)
    {
     
        if (Buffer[buf_counter] == '\0')
        {
            //проверяем конец строки
            int end = buf_counter - 1;
            if(!check_sym(Buffer[end])) //это НЕ конец строки, там какие-то пробельчики или табуляция
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

        //if (str_counter % 13 == 0)
        //printf("%d\n", str_counter);
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

    String** Strings_ptrs = (String **) calloc (amount_of_strings, sizeof (String *));

        //СВЯЗАТЬ ЭЛЕМЕНТЫ МАСССИВА СТРОК С ЭЛЕМЕНТАМИ МАССИВА УКАЗАТЕЛЕЙ
    for (int i = 0; i < amount_of_strings; i++)
        (Strings_ptrs)[i] = &(Strings)[i];

    return Strings_ptrs;
} 


bool check_sym(char sym)
{
    if((isalnum(sym) || ispunct(sym)) && (sym != '\0'))
        return true;
    return false;
}


//обработка ошибок
//compare strings
