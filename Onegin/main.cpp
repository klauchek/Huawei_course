#include "onegin.h"

int main()
{
    int amount_of_strings = 0;
    const char* file_name = "/home/mash/Code/Huawei_course/Onegin/hamlet.txt";
    FILE* input = fopen(file_name, "rb");

    size_t file_size = FileSize(file_name);
    printf("filesize %ld\n", file_size);

    unsigned char* Buffer = CreateBuffer(input, file_size);
    String* strings = SeparateStrings(Buffer, file_size, &amount_of_strings);
    printf("str amount: %d\n", amount_of_strings);

    FileWrite(strings, amount_of_strings, "hamlet_sorted_beg.txt", "hamlet_sorted_end.txt");

    free (strings);
    free (Buffer);

    fclose (input);
    return 0;
}
  
