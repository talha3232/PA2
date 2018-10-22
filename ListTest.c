//-----------------------------------------------------------------------------
// ListTest.c
// A test client for Queue ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include"List.h"

int main(int argc, char* argv[]){

   List A = newList();
   printf("Length of A is: %d \n", length(A));

   prepend(A, 5);
   printf("Front element is: %d \n", front(A));

   prepend(A, 4);
   printf("Length of A is: %d \n", length(A));
   printf("Front element is: %d \n", front(A));

   printf("listEmpty() result: %d \n", isEmpty(A));

   // cursor checks
   moveFront(A);
   printf("Cursor element should be 4: %d \n", get(A));
   moveNext(A);
   printf("Cursor element should be 5: %d \n", get(A));

   append(A,6);
   moveBack(A);
   printf("Cursor element should be 6: %d \n", get(A));
   printf("Length of A should be 3: %d \n", length(A));

   moveBack(A);
   insertBefore(A,3);
   moveBack(A);
   printf("Cursor element should be 6: %d \n", get(A));
   printf("Length of A should be 4: %d \n", length(A));

   movePrev(A);
   printf("Cursor element should be 3: %d \n", get(A));

   moveFront(A);
   insertAfter(A,2);
   moveNext(A);
   printf("Cursor element should be 2: %d \n", get(A));

   printList(stdout,A);

   List B = newList();
   B = copyList(A);
   printList(stdout,B);
   freeList(&B);

   moveBack(A);
   printf("Cursor element should be 6: %d \n", get(A));
   deleteBack(A);
   moveBack(A);
   printf("Cursor element should be 3: %d \n", get(A));

   moveFront(A);
   printf("Cursor element should be 4: %d \n", get(A));
   deleteFront(A);
   moveFront(A);
   printf("Cursor element should be 2: %d \n", get(A));

   moveNext(A);
   printf("Cursor element should be 5: %d \n", get(A));
   delete(A);
   moveFront(A);
   moveNext(A);
   printf("Cursor element should be 3: %d \n", get(A));

   return(0);
}
