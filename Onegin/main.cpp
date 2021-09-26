#include "onegin.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    //массив структур где строки и их длины

    const char* file_name = "/home/mash/Code/Huawei_course/Onegin/yevgeniy_onegin.txt";
    FILE* input = fopen(file_name, "rb");

    size_t file_size = FileSize(file_name);
    printf("filesize %ld\n", file_size);
    char* Buffer = CreateBuffer(input, file_size);

    int amount_of_strings = CountStrings(Buffer, file_size);
    printf("srt amount: %d\n", amount_of_strings);

    //СТРОКА ЭТО СТРУКТУРА
    String* Strings = CreateStringsBuffer(Buffer, amount_of_strings, file_size); //массив строк
    String** Strings_ptrs = CreateStringsPtrsBuffer(Strings, amount_of_strings); //массив указателей на строки
    


    return 0;
}
  
