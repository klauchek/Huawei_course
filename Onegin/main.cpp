#include "onegin.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    const char* file_name = "/home/mash/Code/Huawei_course/Onegin/yevgeniy_onegin.txt";
    FILE* input = fopen(file_name, "rb");

    size_t file_size = FileSize(file_name);
    printf("filesize %ld\n", file_size);
    char* Buffer = CreateBuffer(input, file_size);

    int amount_of_strings = CountStrings(Buffer, file_size);
    printf("srt amount: %d\n", amount_of_strings);


    String* Strings = CreateStringsBuffer(Buffer, amount_of_strings, file_size); //массив строк
    String** Strings_ptrs = CreateStringsPtrsBuffer(Strings, amount_of_strings); //массив указателей на строки

    
    FileWrite(Strings_ptrs, amount_of_strings, "onegin_sorted.txt");

    free (Strings_ptrs);
    free (Strings);
    free (Buffer);


    return 0;
}
  
