#include "StrList.h"
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>

typedef struct _node {
    char* _data;
    struct _node * _next;
} Node;


typedef struct _StrList {
    Node* _head;
    size_t _size;
} StrList;



Node* Node_alloc(char* data,Node* next) {
	Node* p= (Node*)malloc(sizeof(Node));
	p->_data= data;
	p->_next= next;
	return p;
}

void Node_free(Node* node) {
    if (node == NULL) return;
    free(node->_data); // Deallocate memory for the string
    free(node); // Deallocate memory for the node itself
}

StrList* StrList_alloc()
{
    StrList* p = (StrList*)malloc(sizeof(StrList));
    p->_head = NULL;
    p->_size = 0;
    return p; 
}

void StrList_free(StrList* StrList)
{
    StrList->_size=0;
  if (StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->_next;
		Node_free(p2);
	}    
	//free(StrList); 
}

void StrList_insertLast(StrList* StrList, const char* data)
{
  if (StrList == NULL) return;
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    
    newNode->_data = strdup(data); 
    newNode->_next = NULL; // new node will be the last node

    if (StrList->_head == NULL) {
        // if the list is empty, new node becomes the head
        StrList->_head = newNode;
    } else {
        // traverse the list to find the last node
        Node* current = StrList->_head;
        while (current->_next != NULL) {
            current = current->_next;
        }
        // attach the new node to the last node
        current->_next = newNode;
    }
    
    ++(StrList->_size);
}

void StrList_print(const StrList* StrList)
{
    if(StrList_size(StrList)==0)
    {
        printf("\n");
        return;
    }
    
    else{
        const Node* p = StrList->_head;
        while (p)
        {
            printf("%s", p->_data);
            if (p->_next != NULL) // check if there's a next node
                printf(" ");     // print a space only if it's not the last node
            p = p->_next;
        }
        printf("\n");
    }
}

void StrList_insertAt(StrList* StrList, const char* data, int index)
{
    if (StrList == NULL) return;

    if (index < 0 || index > StrList->_size) {
        // invalid index
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // memory allocation failed
        return;
    }
    
    newNode->_data = strdup(data);
    newNode->_next = NULL;

    if (index == 0) {
        // inserting at the beginning
        newNode->_next = StrList->_head;
        StrList->_head = newNode;
    } else {
        // inserting in the middle or at the end
        Node* current = StrList->_head;
        for (int i = 0; i < index - 1; i++) {
            current = current->_next;
        }
        newNode->_next = current->_next;
        current->_next = newNode;
    }

    ++(StrList->_size);
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList)
{
    const Node* p= StrList->_head;
    if(p==NULL)
    {
        return NULL;
    }
    return p->_data;

}

size_t StrList_size(const StrList* StrList)
{
  return StrList->_size;
}

void StrList_printAt(const StrList* Strlist,int index)
{
    const Node* p= Strlist->_head;
    for (int i = 0; i < index; i++)
    {
        if (p == NULL) {
            printf("Index out of bounds\n");
            return;
        }
        p = p->_next;
    }
    if (p != NULL) {
        printf("%s\n", p->_data);
    } else {
        printf("Index out of bounds\n");
    }
}

int StrList_printLen(const StrList* Strlist)
{
    int totalChars=0;
    const Node* p= Strlist->_head;
    while(p!= NULL) 
    {
        int len = strlen(p->_data);

        totalChars += len;
        
        p = p->_next;
        
    }
    return totalChars;

}
int StrList_count(StrList* StrList, const char* data)
{
    int count = 0;
    const Node* p = StrList->_head;

    while (p != NULL) {
        if (strcmp(p->_data, data) == 0) {
            count++;
        }
        p = p->_next;
    }

    return count;

}
/*
	Given a string and a list, remove all the appearences of this string in the list.
*/

void StrList_remove(StrList* StrList, const char* data)
{
     Node** h = &(StrList->_head);

    while (*h != NULL) {
        if (strcmp((*h)->_data, data) == 0) {
            Node* temp = *h;
            *h = (*h)->_next;
            free(temp->_data); 
            free(temp); 
            StrList->_size--; 
        } else {
            h = &((*h)->_next);
        }
    }
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index)
{   
    if (StrList->_head == NULL || index < 0 || index >= StrList->_size) {
        // If the list is empty or the index is out of bounds, return
        return;
    }

    Node** h = &(StrList->_head);

    for (int i = 0; i < index; i++) {
        h = &((*h)->_next);
    }

    Node* temp = *h;
    *h = (*h)->_next;
    free(temp->_data); 
    free(temp); 
    StrList->_size--; 
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
    const Node* p1 = StrList1->_head;
    const Node* p2 = StrList2->_head;

    if (StrList_size(StrList1) != StrList_size(StrList2) || (p1 == NULL && p2 != NULL) || (p2 == NULL && p1 != NULL))
    {
        return 0;
    }

    while (p1 != NULL && p2 != NULL)
    {
        if (strcmp(p1->_data, p2->_data) != 0)
        {
            return 0; 
        }
        p1 = p1->_next;
        p2 = p2->_next;
    }

    return 1;
}



StrList* StrList_clone(const StrList* srclist)
{
    
    StrList *ret= StrList_alloc();
	const Node* old= srclist->_head;
	Node* *copy= &(ret->_head);
	ret->_size= srclist->_size;
	while(old) {
		*copy= Node_alloc(old->_data,NULL);
		old= old->_next;
		copy= &((*copy)->_next);
	}
	return ret;
}

/*
 * Reverces the given StrList. 
 */
void StrList_reverse( StrList* StrList)
{
    Node* prev = NULL;
    Node* current = StrList->_head;
    Node* next = NULL;

    // Traverse the list and reverse the links
    while (current != NULL) {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }

    // Update the head of the list
    StrList->_head = prev;
}


/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort(StrList* StrList)
{
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;
  
    /* Checking for empty list */
    if (StrList->_head == NULL)
        return;
  
    do {
        swapped = 0;
        ptr1 = StrList->_head;
  
        while (ptr1->_next != lptr) {
            if (strcmp(ptr1->_data, ptr1->_next->_data) > 0) {
                char* temp = ptr1->_data;
                ptr1->_data = ptr1->_next->_data;
                ptr1->_next->_data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->_next;
        }
        lptr = ptr1;
    } while (swapped);
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList)
{
    if (StrList->_head == NULL || StrList->_head->_next == NULL)
        return 1;

    Node* current = StrList->_head;

    while (current->_next != NULL) {
        if (strcmp(current->_data, current->_next->_data) > 0) {
            return 0;
        }
        current = current->_next;
    }

    return 1;
}