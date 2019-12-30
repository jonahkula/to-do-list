#include <stdio.h>

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj *List;
List newList(void);                    // creates and returns a new empty list
void freeList(List *pL);               // frees all heap memory associated with *pL, and sets *pL to NULL
int length(List L);                    // returns the number of elements in L
int cursorIndex(List L);               // returns index of cursor element if defined and -1 otherwise
char *front(List L);                   // returns front element of L
char *back(List L);                    // returns back element of L
char *get(List L);                     // returns cursor element of L
int equals(List A, List B);            // returns (1) if A and B are equal and (0) otherwise
void clear(List L);                    // resets L to empty state
void moveFront(List L);                // set cursor to front element
void moveBack(List L);                 // set cursor to back element
void movePrev(List L);                 // move cursor one step toward front of L
void moveNext(List L);                 // move cursor one step toward back of L
void prepend(List L, char *data);      // insert new element at the front of L
void append(List L, char *data);       // insert new element at the end of L
void insertBefore(List L, char *data); // insert new element before cursor
void insertAfter(List L, char *data);  // insert new element after cursor
void deleteFront(List L);              // delete the front element
void deleteBack(List L);               // delete the back element
void delete (List L);                  // delete cursor element, making cursor undefined
void edit(List L, char *data);         // overwrites the cursor element with new data
void sortList(List L);                 // sorts list in alphabetical order
void printList(FILE *out, List L);     // prints the most current state of List to out
List copyList(List L);                 // returns a new List representing the same sequence as L and cursor undefined

#endif
