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

int length(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return (L->length);
}

int index1(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    return (L->cursorIndex);
}

char *front(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    return (L->front->data);
}

char *back(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    return (L->back->data);
}

char *get(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    return (L->cursor->data);
}

int equals(List A, List B)
{
    int eq = 0;
    Node N = NULL;
    Node M = NULL;
    if (A == NULL || B == NULL)
    {
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }
    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (eq && N != NULL)
    {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

void clear(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    while (length(L) != 0)
        deleteFront(L);
}

void moveFront(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0)
        return;
    L->cursor = L->front;
    L->cursorIndex = 0;
}

void moveBack(List L)
{
    if (L == NULL)
    {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0)
        return;
    L->cursor = L->back;
    L->cursorIndex = L->length - 1;
}

void movePrev(List L)
{
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
    Node N = newNode(data);
    if (L == NULL)
    {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
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
    Node N = newNode(data);
    if (L == NULL)
    {
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
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
    Node N = newNode(data);
    if (L == NULL)
    {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
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
    Node N = newNode(data);
    if (L == NULL)
    {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
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
    if (L == NULL)
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
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
    if (L == NULL)
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
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
    if (L == NULL)
    {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
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

void set(List L, char *data)
{
    L->cursor->data = data;
}

void printList(FILE *out, List L)
{
    Node N = NULL;
    if (L == NULL)
    {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }
    N = L->front;
    while (N != NULL)
    {
        fprintf(out, "%s ", N->data);
        N = N->next;
    }
}

List copyList(List L)
{
    List NewList = newList();
    Node N = L->front;
    while (N != NULL)
    {
        append(NewList, N->data);
        N = N->next;
    }
    return NewList;
}
