//-----------------------------------------------------------------------------
// Talha Baqar
// Queue.c now List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

//freeList()
void freeList(List* pL){
   while(isEmpty(*pL) == 0){
      deleteFront(*pL);
   }
   free(*pL);
   *pL = NULL;
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   return(L->length);
}

// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1
int index(List L){
   if(L->cursor != NULL){
      return L->index;
   }
   else{
      return -1;
   }
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(Q)
int front(List L){
   return(L->front->data);
}

// back()
// Returns value at the back of L.
// Pre: length()>0
int back(List L){
   return(L->back->data);
}

// get()
// Returns cursor element
// Pre: length()>0, index()>=0
int get(List L){
   return L->cursor->data;
}

// equals()
// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B){
   List X = newList();
   List Y = newList();
   X = A;
   Y = B;
   Node node1 = newNode(1);
   node1 = X->front;
   Node node2 = newNode(1);
   node2 = Y->front;

   while(node1 != NULL && node2 != NULL){
      if(node1->data == node2->data){
         node1 = node1->next;
         node2 = node2->next;
      }
      else{ // if data are not equal, return false
         return 0;
      }
   }
   if(node1 == NULL && node2 == NULL){
      return 1; //both lists are empty, or data is all equal, return true
   }
   else{
      return 0; // one node is null and other is not, return false
   }
}

//isEmpty()
//Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   return(L->length==0);
}


// Manipulation procedures ----------------------------------------------------
/*
// clear()
// Resets this List to its original empty state.
void clear(List L){
   freeList(L);
}
*/

// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   if(isEmpty(L)==0){
      L->cursor = L->front;
      L->index = 0;
   }
}

// void moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
   if(isEmpty(L)==0){
      L->cursor = L->back;
      L->index = length(L)-1;
   }
}

// void movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing
void movePrev(List L){
   if(L->cursor != NULL && L->cursor != L->front){
      L->cursor = L->cursor->prev;
      L->index--;
   }
   else if(L->cursor != NULL && L->cursor == L->front){
      L->cursor = NULL;
      L->index = -1;
   }
   // cursor undefined do nothing

}

// void moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if(L->cursor != NULL && L->cursor != L->back){
      L->cursor = L->cursor->next;
      L->index++;
   }
   else if(L->cursor != NULL && L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   // cursor undefined do nothing
}

// void prepend(//void insertBefore(int data) // Insert new element before cursor.
// Pre: length()>0, index()>=0int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
   Node temp = newNode(data);
   if(isEmpty(L) == 0){ // List is NOT empty
      temp->next = L->front;
      L->front->prev = temp;
      L->front = temp;
      L->index++;
   }
   else{ // empty list
      L->front = L->back = temp;
   }
   L->length++;
}

// void append(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
   Node temp = newNode(data);
   switch(L->length){
      case 0: // empty list
         L->front = L->back = temp;
         break;
      case 1: // list with 1 element
         L->front->next = temp;
         temp->prev = L->front;
         L->back = temp;
      default: // list with > 1 elements
         L->back->next = temp;
         temp->prev = L->back;
         L->back = temp;
         break;
   }
   L->length++;
}

// void insertBefore(int data)
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
   if(isEmpty(L) == 1 || L->index < 0){
      printf("insertBefore called on empty list or undefined index");
      return;
   }
   else if(L->cursor == L->front){ // cursor at front
      prepend(L,data);
   }
   else if(L->length > 0 && L->index >= 0){
      Node temp = newNode(data);
      Node prevNode = L->cursor->prev;

      L->cursor->prev = temp;
      temp->next = L->cursor;
      temp->prev = prevNode;
      L->length++;
      L->index++;

      if(prevNode != NULL){
         prevNode->next = temp;
      }
   }
}

// void insertAfter(int data)
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
   if(isEmpty(L) == 1 || L->index < 0){
      printf("insertAfter called on empty list or undefined index");
      return;
   }
   else if(L->cursor == L->back){ // cursor at front
      append(L,data);
   }
   else if(L->length > 0 && L->index >= 0){
      Node temp = newNode(data);
      Node nextNode = L->cursor->next;

      L->cursor->next = temp;
      temp->prev = L->cursor;
      temp->next = nextNode;
      L->length++;

      if(nextNode != NULL){
         nextNode->prev = temp;
      }
   }
}

// void deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L){
   if(L->cursor == L-> front){ // reset cursor if at front
      L->cursor = NULL;
      L->index = -1;
   }
   else{
      L->index--;
   }
   // taken from Queue.c in prof examples
   if(L->length >= 1){
      Node N = L->front;
      if( L->length>1 ) {
         L->front = L->front->next;
         L->front->prev = NULL;
      }else{
         L->front = L->back = NULL;
      }
      L->length--;
      freeNode(&N);
   }
}

//void deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L){
   if(L->cursor == L->back){ // reset cursor if at back
      L->cursor = NULL;
      L->index = -1;
   }

   if(L->length >= 1){
      Node N = L->back;
      if( L->length>1 ) {
         L->back = L->back->prev;
         L->back->next = NULL;
      }else{
         L->front = L->back = NULL;
      }
      L->length--;
      freeNode(&N);
   }
}

// void delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   if(L->cursor == L->front){
      deleteFront(L);
   }
   else if(L->cursor == L->back){
      deleteBack(L);
   }
   else if(L->cursor != NULL && L->length > 1){
      Node temp = L->cursor;
      Node prevNode = L->cursor->prev;
      Node nextNode = L->cursor->next;

      prevNode->next = nextNode;
      nextNode->prev = prevNode;

      freeNode(&temp);
      L->length--;
      L->cursor = NULL;
      L->index = -1;
   }
}

// Other Functions -------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List\n");
      return;
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out,"%d ", N->data);
   }
   fprintf(out,"\n");
}

// List copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
   Node N = L->front;
   List B = newList();

   while(N != NULL){
      append(B, N->data);
      N = N->next;
   }
   return B;
}





