#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main(int argc, char *argv[])
{
    // open files
    FILE *in, *out;
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    // get user input to start off with a file or from scratch
    // add exception handling later
    int userInput;
    printf("(1) - start list from scratch\n(2) - start from text file\n\nInput: ");
    scanf("%d", &userInput);
    printf("\n");
    if (userInput == 1)
    {
        // TBD
    }
    else if (userInput == 2)
    {
        // TBD
    }
    else
    {
        // TBD
    }
    fclose(in);
    fclose(out);
    return 0;
}
