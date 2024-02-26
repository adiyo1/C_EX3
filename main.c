#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"
#include "StrList.h"


int main() {
int choice;
int index;
char str[SizeMaxWord];
//StrList *ptr1= StrList_alloc();
StrList *ptr2= StrList_alloc();
//StrList *ptr3= StrList_alloc();

while (1) {
    
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        
        //printf("How many words do you want to add? ");
        scanf("%d", &index);
        
        for (int i = 0; i < index; i++) {
          scanf("%s", str);
          StrList_insertLast(ptr2, str);
        }
        
        break;

      case 2:
        //printf("Enter index: ");
        scanf("%d", &index);
        //printf("Enter string: ");
        scanf("%s", str);
        StrList_insertAt(ptr2, str, index);
        //StrList_print(ptr2);
        break;
      case 3:
        StrList_print(ptr2);
        break;
      case 4:
        //printf("List size: %ld\n", StrList_size(ptr2));
        printf("%li\n", StrList_size(ptr2));
        break;
      case 5:
        //printf("Enter index: ");
        scanf("%d", &index);
        //printf("The string at index %d is: ", index); 
        StrList_printAt(ptr2, index);
        break;
      case 6:
        //printf("Number of characters: %d\n", StrList_printLen(ptr2));
        printf("%d\n", StrList_printLen(ptr2));
        break;
      case 7:
        //printf("Enter string: ");
        scanf("%s", str);
        //printf("Number of occurrences: %d\n", StrList_count(ptr2, str));
        printf("%d\n", StrList_count(ptr2, str));
        break;
      case 8:
        //printf("Enter string: ");
        scanf("%s", str);
        StrList_remove(ptr2, str);
        break;
      case 9:
        //printf("Enter index: ");
        scanf("%d", &index);
        StrList_removeAt(ptr2, index);
        break;
      case 10:
        StrList_reverse(ptr2);
        break;
      case 11:
        StrList_free(ptr2);
        break;
      case 12:
        StrList_sort(ptr2);
        break;
      case 13:
        if (StrList_isSorted(ptr2)) {
          printf("true\n");
        } else {
          printf("false\n");
        }
        break;
      // case 14:
      //   StrList_firstData(ptr2);
      //   break;
      // case 15:
      //   StrList_isEqual(ptr2, ptr1);
      //   break;
      // case 16:
      //   ptr3= StrList_clone(ptr2);
      //   printf("%d",StrList_isEqual(ptr2, ptr3));
      //   break;
      case 0:
        exit(0);
        // printf("the program is over");
    }
  }

StrList_free(ptr2);
return 0;
}