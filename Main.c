#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main(int argc, char *argv[])
{
    // FILE *in, *out;
    int userInput;
    printf("(1) - start list from scratch\n(2) - start from text file\n\nInput: ");
    scanf("%d", &userInput);
    printf("%d",userInput);
    // if (argc != 3)
    // {
    //     fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
    //     exit(1);
    // }
    // in = fopen(argv[1], "r");
    // out = fopen(argv[2], "w");
    // if (in == NULL)
    // {
    //     printf("Unable to open file %s for reading\n", argv[1]);
    //     exit(1);
    // }
    // if (out == NULL)
    // {
    //     printf("Unable to open file %s for writing\n", argv[2]);
    //     exit(1);
    // }
    // fclose(in);
    // fclose(out);
    return 0;
}
