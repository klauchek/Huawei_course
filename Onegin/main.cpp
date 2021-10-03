#include "onegin.h"

int main()
{
    //setlocale(LC_ALL, "Russian");

    int amount_of_strings = 0;
    const char* file_name = "/home/mash/Code/Huawei_course/Onegin/SlavaPiska.txt";
    FILE* input = fopen(file_name, "rb");

    size_t file_size = FileSize(file_name);
    printf("filesize %ld\n", file_size);
    unsigned char* Buffer = CreateBuffer(input, file_size);

    // for (int i = 0; i < file_size; ++i) {

    //     printf ("%c", Buffer[i]);
    // }

    String* strings = SeparateStrings(Buffer, file_size, &amount_of_strings);
    // for (int i = 0; i < amount_of_strings; ++i) {

    //     int c = 'A';
    //     int counter = 0;
    //     while (c != '\0') {
    //         c = strings[i].str_beg[counter];
    //         counter++;
    //         printf ("%c", c);
    //     }
    // }
    printf("str amount: %d\n", amount_of_strings);

 
    FileWrite(strings, amount_of_strings, "onegin_sorted.txt");

    free (strings);
    free (Buffer);

    fclose (input);
    return 0;
}
  
