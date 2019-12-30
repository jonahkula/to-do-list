#include <stdio.h>

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type
typedef struct ListObj *List;

// Constructors-Deconstructors
List newList(void);      // creates and returns a new empty list
void freeList(List *pL); // frees all heap memory associated with *pL, and sets *pL to NULL

// Access functions
int length(List L);         // returns the number of elements in L
int index1(List L);          // returns index of cursor element if defined, -1 otherwise
char *front(List L);        // returns front element of L. Pre: length() > 0
char *back(List L);         // returns back element of L. Pre: length() > 0
char *get(List L);          // returns cursor element of L. Pre: length() > 0, index() >= 0
int equals(List A, List B); // returns true (1) iff Lists A and B are in same state, and returns false
                            // (0) if otherwise

// Manipulation procedures
void clear(List L);                    // resets L to its original empty state
void moveFront(List L);                // if L is non-empty, sets cursor under the front element,
                                       // otherwise does nothing
void moveBack(List L);                 // if L is non-empty, sets cursor under the back element,
                                       // otherwise does nothing
void movePrev(List L);                 // if cursor is defined and not at front, move cursor one step
                                       // toward the front of L; if cursor is defined and at front, cursor
                                       // becomes undefined; if cursor is undefined do nothing
void moveNext(List L);                 // If cursor is defined and not at back, move cursor one step toward
                                       // the back of L; if cursor is defined and at back, cursor becomes
                                       // undefined; if cursor is undefined do nothing
void prepend(List L, char *data);      // insert new element into L. If L is non-empty, insertion takes place
                                       // before front element
void append(List L, char *data);       // insert new element into L. If L is non-empty, insertion takes place
                                       // after back element
void insertBefore(List L, char *data); // insert new element before cursor. Pre: length() > 0, index() >= 0
void insertAfter(List L, char *data);  // insert new element before cursor. Pre: length() > 0, index() >= 0
void deleteFront(List L);              // delete the front element. Pre: length() > 0
void deleteBack(List L);               // delete the back element. Pre: length() > 0
void delete (List L);                  // delete cursor element, making cursor undefined.
                                       // Pre: length() > 0, index() >= 0
void set(List L, char *data);          // overwrites the cursor element with x. Pre: length()>0, index()>=0

// Other operations
void printList(FILE *out, List L); // prints to the file pointed to by out, a string representation of L
                                   // consisting of a space separated sequence of integers, with front on left
List copyList(List L);             // returns a new List representing the same integer sequence as L. The cursor
                                   // in the new list is undefined, regardless of the state of the cursor in L.
                                   // The state of L is unchanged.

#endif
