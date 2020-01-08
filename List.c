#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "string.h"

struct NodeObj
{
    char *data;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

typedef struct NodeObj *Node;

struct ListObj
{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;

Node newNode(char *data)
{
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = N->prev = NULL;
    return N;
}

void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void)
{
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return L;
}

void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (length(*pL) != 0)
            deleteFront(*pL);
        free(*pL);
        *pL = NULL;
    }
}

void testNull(List L)
{
    if (L == NULL)
    {
        printf("Error: calling function on a NULL List reference\n");
        exit(1);
    }
}

void testEmpty(List L)
{
    if (L->length == 0)
    {
        printf("Error: List is empty\n");
        exit(1);
    }
}

void testCursor(List L)
{
    if (L->cursorIndex == -1)
    {
        printf("Error: cursor is NULL\n");
        exit(1);
    }
}

int length(List L)
{
    testNull(L);
    return (L->length);
}

int cursorIndex(List L)
{
    testNull(L);
    return (L->cursorIndex);
}

char *front(List L)
{
    testNull(L);
    testEmpty(L);
    return (L->front->data);
}

char *back(List L)
{
    testNull(L);
    testEmpty(L);
    return (L->back->data);
}

char *get(List L)
{
    testNull(L);
    testEmpty(L);
    return (L->cursor->data);
}

int equals(List A, List B)
{
    testNull(A);
    testNull(B);
    int eq = (A->length == B->length);
    Node N = A->front;
    Node M = B->front;
    while (eq && N != NULL)
    {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

int find(List L, int userInput)
{
    if (userInput <= 0 || userInput > L->length)
        return 0;
    int count = 1;
    Node N = L->front;
    while (N != NULL && count != userInput)
    {
        count++;
        N = N->next;
    }
    L->cursor = N;
    L->cursorIndex = count - 1;
    return 1;
}

void clear(List L)
{
    testNull(L);
    while (length(L) != 0)
        deleteFront(L);
}

void moveFront(List L)
{
    testNull(L);
    testEmpty(L);
    if (L->length == 0)
        return;
    L->cursor = L->front;
    L->cursorIndex = 0;
}

void moveBack(List L)
{
    testNull(L);
    testEmpty(L);
    if (L->length == 0)
        return;
    L->cursor = L->back;
    L->cursorIndex = L->length - 1;
}

void movePrev(List L)
{
    testNull(L);
    testEmpty(L);
    if (L->cursor == NULL)
        return;
    if (L->cursor == L->front)
    {
        L->cursor = NULL;
        L->cursorIndex = -1;
        return;
    }
    else
    {
        L->cursor = L->cursor->prev;
        L->cursorIndex--;
    }
}

void moveNext(List L)
{
    testNull(L);
    testEmpty(L);
    if (L->cursor == NULL)
        return;
    if (L->cursor == L->back)
    {
        L->cursor = NULL;
        L->cursorIndex = -1;
        return;
    }
    L->cursor = L->cursor->next;
    L->cursorIndex++;
}

void prepend(List L, char *data)
{
    testNull(L);
    Node N = newNode(data);
    if (L->front == NULL)
    {
        L->front = L->back = N;
        L->cursor = L->front;
        L->length++;
        return;
    }
    L->front->prev = N;
    N->next = L->front;
    L->front = N;
    L->cursorIndex++;
    L->length++;
}

void append(List L, char *data)
{
    testNull(L);
    Node N = newNode(data);
    if (L->length == 0)
        L->front = L->back = N;
    else
    {
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
        N->next = NULL;
    }
    L->length++;
}

void insertBefore(List L, char *data)
{
    testNull(L);
    testCursor(L);
    Node N = newNode(data);
    if (L->length == 0)
        L->front = L->back = N;
    if (L->cursor == L->front)
    {
        freeNode(&N);
        prepend(L, data);
        return;
    }
    N->next = L->cursor;
    N->prev = L->cursor->prev;
    L->cursor->prev->next = N;
    L->cursor->prev = N;
    L->length++;
    L->cursorIndex++;
}

void insertAfter(List L, char *data)
{
    testNull(L);
    testCursor(L);
    Node N = newNode(data);
    if (L->length == 0)
        L->front = L->back = N;
    if (L->cursor == L->back)
    {
        freeNode(&N);
        append(L, data);
        return;
    }
    L->cursor->next->prev = N;
    N->next = L->cursor->next;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length++;
}

void deleteFront(List L)
{
    testNull(L);
    if (L->length == 1)
    {
        freeNode(&L->front);
        L->front = L->back = NULL;
        L->cursorIndex = -1;
        L->cursor = NULL;
    }
    else
    {
        Node N = L->front;
        if (L->cursor == N)
        {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
        L->front = L->front->next;
        L->front->prev = NULL;
        freeNode(&N);
        if (L->cursorIndex != -1)
            L->cursorIndex--;
    }
    L->length--;
}

void deleteBack(List L)
{
    testNull(L);
    if (L->length == 1)
    {
        freeNode(&L->back);
        L->back = L->front = NULL;
        L->cursorIndex = -1;
        L->cursor = NULL;
    }
    else
    {
        Node N = L->back;
        if (L->cursor == N)
        {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
        L->back = L->back->prev;
        L->back->next = NULL;
        freeNode(&N);
        if (L->cursorIndex == L->length - 1)
            L->cursorIndex = -1;
    }
    L->length--;
}

void delete (List L)
{
    testNull(L);
    testCursor(L);
    if (L->cursor == L->back)
        deleteBack(L);
    else if (L->cursor == L->front)
        deleteFront(L);
    else
    {
        Node N = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->length--;
        freeNode(&N);
    }
    L->cursorIndex = -1;
}

void edit(List L, char *data)
{
    testNull(L);
    testEmpty(L);
    testCursor(L);
    L->cursor->data = data;
}

void sortList(List L)
{
    testNull(L);
    if (L->length == 0)
        return;
    char *temp = "";
    Node N = L->front;
    Node M = NULL;
    while (N != NULL)
    {
        M = N->next;
        while (M != NULL)
        {
            if (strcmp(N->data, M->data) > 0)
            {
                strcpy(temp, N->data);
                strcpy(N->data, M->data);
                strcpy(M->data, temp);
            }
            M = M->next;
        }
        N = N->next;
    }
}

void printList(FILE *out, List L)
{
    testNull(L);
    if (L->length == 0)
        fprintf(out, "To do list is empty\n");
    else
    {
        Node N = L->front;
        int count = 1;
        while (N != NULL)
        {
            fprintf(out, "%d. %s", count, N->data);
            count++;
            N = N->next;
        }
    }
}

List copyList(List L)
{
    testNull(L);
    testEmpty(L);
    List copyL = newList();
    Node N = L->front;
    while (N != NULL)
    {
        append(copyL, N->data);
        N = N->next;
    }
    return copyL;
}
