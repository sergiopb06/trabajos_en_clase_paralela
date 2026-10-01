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