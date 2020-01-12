#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

void getInput(FILE *out, List toDoList);
void listOptions(FILE *out, List toDoList, int choice);
void finishProgram(FILE *out, List toDoList);

int main(int argc, char *argv[])
{
    FILE *out;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <output file>\n", argv[0]);
        exit(1);
    }
    out = fopen(argv[1], "w");
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    List toDoList = newList();
    printList(stdout, toDoList);
    printf("\n");
    getInput(out, toDoList);
    return 0;
}

void getInput(FILE *out, List toDoList)
{
    int choice;
    printf("(1) - add\n(2) - delete\n(3) - edit\n(4) - sort\n(5) - print\n(6) - clear\n(7) - finish\n\nInput: ");
    if (scanf("%d", &choice) != 1)
    {
        printf("\nError: input is not an integer\n");
        freeList(&toDoList);
        fclose(out);
        exit(1);
    }
    printf("\n");
    listOptions(out, toDoList, choice);
}

void listOptions(FILE *out, List toDoList, int choice)
{
    char str[1000];
    int userInput;
    switch (choice)
    {
    case 1:
        // add
        printf("Enter an item to add: ");
        scanf(" %[^\n]", str);
        strncat(str, "\n", 1);
        append(toDoList, str);
        printf("\n");
        printList(stdout, toDoList);
        printf("\n");
        getInput(out, toDoList);
        break;
    case 2:
        // delete
        printf("Enter item number to delete: ");
        if (scanf("%d", &userInput) != 1)
        {
            printf("\nError: input is not an integer\n");
            freeList(&toDoList);
            fclose(out);
            exit(1);
        }
        printf("\n");
        if (find(toDoList, userInput) == 0)
        {
            printf("Error: item number does not exist\n\n");
            getInput(out, toDoList);
        }
        delete (toDoList);
        printList(stdout, toDoList);
        printf("\n");
        getInput(out, toDoList);
        break;
    case 3:
        // edit
        printf("Enter item number to edit: ");
        if (scanf("%d", &userInput) != 1)
        {
            printf("\nError: input is not an integer\n");
            freeList(&toDoList);
            fclose(out);
            exit(1);
        }
        printf("\n");
        if (find(toDoList, userInput) == 0)
        {
            printf("Error: item number does not exist\n\n");
            getInput(out, toDoList);
        }
        printf("Enter new item: ");
        scanf(" %[^\n]", str);
        strncat(str, "\n", 1);
        edit(toDoList, str);
        printf("\n");
        printList(stdout, toDoList);
        printf("\n");
        getInput(out, toDoList);
        break;
    case 4:
        // sort
        sortList(toDoList);
        printList(stdout, toDoList);
        printf("\n");
        getInput(out, toDoList);
        break;
    case 5:
        // print
        printList(stdout, toDoList);
        printf("\n");
        getInput(out, toDoList);
        break;
    case 6:
        // clear
        clear(toDoList);
        printList(stdout, toDoList);
        printf("\n");
        getInput(out, toDoList);
        break;
    case 7:
        // finish
        finishProgram(out, toDoList);
    default:
        printf("Error: invalid input, must be 1-7\n\n");
        getInput(out, toDoList);
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
