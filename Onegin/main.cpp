#include "onegin.h"

int main()
{
    // setlocale(LC_ALL, "Russian");

    const char* file_name = "SlavaPiska.txt";
    FILE* input = fopen(file_name, "rb");

    size_t file_size = FileSize(file_name);
    printf("filesize %ld\n", file_size);
    char* Buffer = CreateBuffer(input, file_size);

   // int amount_of_strings = (Buffer, file_size);
   // printf("srt amount: %d\n", amount_of_strings);

    
    FileWrite(Strings_ptrs, amount_of_strings, "onegin_sorted.txt");

    free (Strings);
    free (Buffer);


    return 0;
}
  
