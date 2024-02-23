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


// Node* Node_alloc(char* data,Node* next) {
// 	Node* p= (Node*)malloc(sizeof(Node));
// 	p->_data= strdup(data);
// 	p->_next= next;
// 	return p;
// }

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
        // Memory allocation failed
        return;
    }
    
    newNode->_data = strdup(data); // Allocate memory for data and copy it
    newNode->_next = NULL; // New node will be the last node

    if (StrList->_head == NULL) {
        // If the list is empty, new node becomes the head
        StrList->_head = newNode;
    } else {
        // Traverse the list to find the last node
        Node* current = StrList->_head;
        while (current->_next != NULL) {
            current = current->_next;
        }
        // Attach the new node to the last node
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
        const Node* p= StrList->_head;
        while(p) {
            printf("%s ", p->_data);
            //printf("(%.2s)->",p->_data);
            p= p->_next;
        }
        
        printf("\n");
        //printf("|| size:%zu\n",StrList->_size);
    }
}

void StrList_insertAt(StrList* StrList, const char* data, int index)
{
    if (StrList == NULL) return;

    if (index < 0 || index > StrList->_size) {
        // Invalid index
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // Memory allocation failed
        return;
    }
    
    newNode->_data = strdup(data); // Allocate memory for data and copy it
    newNode->_next = NULL;

    if (index == 0) {
        // Inserting at the beginning
        newNode->_next = StrList->_head;
        StrList->_head = newNode;
    } else {
        // Inserting in the middle or at the end
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
        // Get the length of the string in the current node
        int len = strlen(p->_data);

        // Add the length to the total count
        totalChars += len;
        
        // Move to the next node
        p = p->_next;
        
    }
    return totalChars;

}
int StrList_count(StrList* StrList, const char* data)
{
    int count = 0;
    const Node* p = StrList->_head;

    // Iterate through the list
    while (p != NULL) {
        // Compare the data in the current node with the target data
        if (strcmp(p->_data, data) == 0) {
            // If they match, increment the count
            count++;
        }
        // Move to the next node
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
            free(temp->_data); // Free memory allocated for the string
            free(temp); // Free memory allocated for the node
            StrList->_size--; // Decrease the size of the list
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
    free(temp->_data); // Free memory allocated for the string
    free(temp); // Free memory allocated for the node
    StrList->_size--; // Decrease the size of the list
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
    const Node* p1 = StrList1->_head;
    const Node* p2 = StrList2->_head;

    // Check if the lists have different sizes or if one of them is empty
    if (StrList_size(StrList1) != StrList_size(StrList2) || (p1 == NULL && p2 != NULL) || (p2 == NULL && p1 != NULL))
    {
        return 0;
    }

    // Traverse both lists and compare each node's data
    while (p1 != NULL && p2 != NULL)
    {
        // Compare the data stored in the nodes
        if (strcmp(p1->_data, p2->_data) != 0)
        {
            return 0; // If data is not equal, return 0
        }
        p1 = p1->_next;
        p2 = p2->_next;
    }

    // If both lists have been traversed completely and no mismatch found, they are equal
    return 1;
}


// Node* Node_alloc(char* data,Node* next) {
// 	Node* p= (Node*)malloc(sizeof(Node));
// 	p->_data= strdup(data);
// 	p->_next= next;
// 	return p;
// }
/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */

// StrList* StrList_clone(const StrList* srclist)
// {
//     if (srclist == NULL)
//         return NULL;

//     StrList* cloneList = StrList_alloc(); // Allocate memory for the cloned list

//     // Iterate over each node in the original list
//     Node* current = srclist->_head;
//     Node** cloneNext = &(cloneList->_head);
//     while (current != NULL) {
//         // Duplicate the string in the current node
//         char* newData = strdup(current->_data);
//         if (newData == NULL) {
//             // Memory allocation failed, clean up and return NULL
//             StrList_free(cloneList);
//             return NULL;
//         }

//         // Create a new node with the duplicated string
//         Node* newNode = Node_alloc(newData, NULL);
//         if (newNode == NULL) {
//             // Memory allocation failed, clean up and return NULL
//             free(newData); // Free the duplicated string
//             StrList_free(cloneList);
//             return NULL;
//         }

//         // Link the new node to the cloned list
//         *cloneNext = newNode;
//         cloneNext = &(newNode->_next);

//         // Move to the next node in the original list
//         current = current->_next;
//     }

//     // Update the size of the cloned list
//     cloneList->_size = srclist->_size;

//     return cloneList;
// }

StrList *StrList_clone(const StrList *StrList)
{
    struct _StrList *clone =NULL;
    if(StrList)
    {
        clone = StrList_alloc();
        Node *corrent = StrList -> _head;
        while(corrent)
        {
            StrList_insertLast(clone, corrent-> _data);
            corrent= corrent->_next;
        }
    }
    return clone;
}
// StrList* StrList_clone(const StrList* srclist)
// {
    
//     StrList *ret= StrList_alloc();
// 	const Node* old= srclist->_head;
// 	Node* *copy= &(ret->_head);
// 	ret->_size= srclist->_size;
// 	while(old) {
// 		*copy= Node_alloc(old->_data,NULL);
// 		old= old->_next;
// 		copy= &((*copy)->_next);
// 	}
// 	return ret;
// }

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
    // If the list is empty or has only one element, it is considered sorted
    if (StrList->_head == NULL || StrList->_head->_next == NULL)
        return 1;

    Node* current = StrList->_head;

    // Traverse the list and compare each node's data with the next node's data
    while (current->_next != NULL) {
        // Compare the current node's data with the next node's data
        if (strcmp(current->_data, current->_next->_data) > 0) {
            // If the current node's data is greater than the next node's data,
            // the list is not sorted
            return 0;
        }
        // Move to the next node
        current = current->_next;
    }

    // If the loop completes without encountering unsorted data, the list is sorted
    return 1;
}