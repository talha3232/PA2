//-----------------------------------------------------------------------------
// Talha Baqar
// Queue.c now List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
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
   N->cursor = NULL;
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

// newQueue()
// Returns reference to new empty Queue object.
List newList(void){
   List Q;
   Q = malloc(sizeof(ListObj));
   Q->front = Q->back = Q->cursor = NULL;
   Q->length = Q-> index = 0;
   return(Q);
}


// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while( !isEmpty(*pL) ) {
         //FIXME
         Dequeue(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1
int index(List L){
   if(cursor != NULL){
      return index;
   }
   else{
      return -1;
   }
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(Q)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns value at the back of L.
// Pre: length()>0
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back>data);
}

// get()
// Returns cursor element
// Pre: length()>0, index()>=0
int get(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   if(cursor == NULL){
      printf("List Error: cursor not pointing to anything\n");
      exit(1);
   }
   return cursor->data;
}

// equals()
// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B){
   newList X = A;
   newList Y = B;
   newNode node1 = X->front;
   newNode node2 = Y->front;

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

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List Q){
   if( Q==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(Q->length==0);
}


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data element at the end of Q
void Enqueue(Queue Q, int data)
{
   Node N = newNode(data);

   if( Q==NULL ){
      printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ) {
      Q->front = Q->back = N;
   }else{
      Q->back->next = N;
      Q->back = N;
   }
   Q->length++;
}

// Dequeue()
// Deletes element at front of Q
// Pre: !isEmpty(Q)
void Dequeue(Queue Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling Dequeue on an empty Queue\n");
      exit(1);
   }
   N = Q->front;
   if( getLength(Q)>1 ) {
      Q->front = Q->front->next;
   }else{
      Q->front = Q->back = NULL;
   }
   Q->length--;
   freeNode(&N);
}


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints data elements in Q on a single line to stdout.
void printQueue(Queue Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(1);
   }

   for(N = Q->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(Queue A, Queue B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("Queue Error: calling equals() on NULL Queue reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}
