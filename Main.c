#include <stdlib.h>
#include <stdio.h>
#include "List.h"

void startProgram(FILE *in, FILE *out);
void readFile(FILE *in, FILE *out);
void listOptions(FILE *out, List toDoList);
void finishProgram(FILE *out, List toDoList);

int main(int argc, char *argv[])
{
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
    startProgram(in, out);
    return 0;
}

void startProgram(FILE *in, FILE *out)
{
    int userInput;
    printf("(1) - start list from scratch\n(2) - start from text file\n\nInput: ");
    if (scanf("%d", &userInput) != 1)
    {
        printf("\nError: input is not an integer\n");
        fclose(in);
        fclose(out);
        exit(1);
    }
    printf("\n");
    if (userInput == 1)
    {
        fclose(in);
        List toDoList = newList();
        printList(stdout, toDoList);
        printf("\n");
        listOptions(out, toDoList);
    }
    else if (userInput == 2)
    {
        readFile(in, out);
    }
    else
    {
        printf("Error: invalid input, must be 1 or 2\n\n");
        startProgram(in, out);
    }
}

void readFile(FILE *in, FILE *out)
{
    List toDoList = newList();
    char str[1000];
    rewind(in);
    while (fgets(str, sizeof str, in) != NULL)
        append(toDoList, str);
    fclose(in);
    printList(stdout, toDoList);
    printf("\n");
    listOptions(out, toDoList);
}

void listOptions(FILE *out, List toDoList)
{
    int userInput;
    printf("(1) - add\n(2) - delete\n(3) - edit\n(4) - sort\n(5) - print\n(6) - clear\n(7) - finish\n\nInput: ");
    if (scanf("%d", &userInput) != 1)
    {
        printf("\nError: input is not an integer\n");
        fclose(out);
        exit(1);
    }
    printf("\n");
    switch (userInput)
    {
    case 1:
        // add
        listOptions(out, toDoList);
        break;
    case 2:
        // delete
        listOptions(out, toDoList);
        break;
    case 3:
        // edit
        listOptions(out, toDoList);
        break;
    case 4:
        sortList(toDoList);
        printList(stdout, toDoList);
        printf("\n");
        listOptions(out, toDoList);
        break;
    case 5:
        printList(stdout, toDoList);
        printf("\n");
        listOptions(out, toDoList);
        break;
    case 6:
        clear(toDoList);
        printList(stdout, toDoList);
        printf("\n");
        listOptions(out, toDoList);
        break;
    case 7:
        finishProgram(out, toDoList);
    default:
        printf("Error: invalid input, must be 1-7\n\n");
        listOptions(out, toDoList);
    }
}

void finishProgram(FILE *out, List toDoList)
{
    printf("Program finished, final list written to text file and below:\n\n");
    printList(stdout, toDoList);
    printList(out, toDoList);
    fclose(out);
    freeList(&toDoList);
    exit(0);
}

/*
fix reading bug, overwriting everytime you append
write add, delete, and edit in listOptions()
test code and fix bugs
*/
