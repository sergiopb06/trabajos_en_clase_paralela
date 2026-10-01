#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_SIZE 100

struct Node{
    int data;
    struct Node *next;
};

void push(struct Node** tail, int new_data){
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*tail);
    (*tail) = new_node;

}

void splitList(struct Node* source, struct Node** frontRef, struct Node** backRef){
    struct Node* fast;
    struct Node* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL){
        fast = fast->next;

        if (fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}


struct Node* merge(struct Node* a, struct Node* b){
    struct Node* result = NULL;

    //Base cases 
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);


    if (a->data <= b->data){
        result = a;
        result->next = SortedMerge(a->next, b);
    }

    else{
        result = b;
        result->next = SortedMerge(a, b->next);
    }

    return (result);
}


void mergeSort(struct Node** headRef){
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;


    if ((head == NULL) || (head->next == NULL)){
        return;
    }


    splitList(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);


    *headRef = merge(a, b);
}


int main(){
    srand(time(NULL));
    struct Node *head = NULL; // First 
    struct Node *tail = NULL; // Last 
    
    head = (struct Node *)malloc(sizeof(struct Node));
    tail = (struct Node *)malloc(sizeof(struct Node));
    
    for(int i = 0; i < LIST_SIZE; i++){
        int num = rand() % 20;
        struct Node *new_node = NULL;
        push(&new_node, i);
    }

    struct Node *temp = head;
    while (temp != NULL){
        printf("%d", temp->data);
        temp = temp->next;
    }
    
}