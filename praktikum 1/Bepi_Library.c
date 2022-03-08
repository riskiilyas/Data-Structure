#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/* Struktur Node */

typedef struct dnode_t {
    char *title;
    float price;
    struct dnode_t      \
        *next,
        *prev;
} DListNode;

/* Struktur ADT Deque */
/* Implementasi didasarkan pada Doubly-Linked List */

typedef struct deque_t {
    DListNode           \
        *_head, 
        *_tail;
    unsigned _size;
} Deque;

/* DAFTAR FUNGSI YANG TERSEDIA */

DListNode* __dlist_createNode(char* title, float price);
void deq_init(Deque *deque);
bool deq_isEmpty(Deque *deque);
void deq_pushBack(Deque *deque, char* title, float price);
void deq_popFront(Deque *deque);
void deq_popBack(Deque *deque);

/* Definisi Fungsi */

DListNode* __dlist_createNode(char* title, float price)
{
    DListNode *newNode = \
        (DListNode*) malloc (sizeof(DListNode));
    
    if (!newNode) return NULL;
    newNode->title = title;
    newNode->price = price;
    newNode->next = NULL;
    newNode->prev = NULL;

    return (DListNode*) newNode;
}

void deq_init(Deque *deque)
{
    deque->_head = deque->_tail = NULL;
    deque->_size = (unsigned) 0;
}

bool deq_isEmpty(Deque *deque) {
    return (deque->_head == NULL && \
            deque->_tail == NULL);
}

void deq_pushBack(Deque *deque, char* title, float price)
{
    DListNode *newNode = __dlist_createNode(title, price);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        deque->_tail->next = newNode;
        newNode->prev = deque->_tail;
        deque->_tail = newNode;
    }
}

void deq_pushFront(Deque *deque, char* title, float price)
{
    DListNode *newNode = __dlist_createNode(title, price);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }

        newNode->next = deque->_head;
        deque->_head->prev = newNode;
        deque->_head = newNode;
    }
}

void deq_popFront(Deque *deque)
{
    if (!deq_isEmpty(deque)) {
        DListNode *temp = deque->_head;
        if (deque->_head == deque->_tail) {
            deque->_head = NULL;
            deque->_tail = NULL;
            print_book(&temp);
            free(temp);
        }
        else {
            deque->_head = deque->_head->next;
            deque->_head->prev = NULL;
            print_book(&temp);
            free(temp);
        }
        deque->_size--;
    }
}

void print_book(DListNode *book) {
    printf("Title\t\t: %s\n", book->title);
    printf("Rent Price\t: $%f/day\n", book->price);
}

void findByTitle(Deque *deque, char *title){
    DListNode *temp = deque->_head;
    int span = strlen(title);
    while(temp!=NULL){
        int flag = 0;
        for(int i=0; i<span; i++){
            if(title[i].tolower()!=(temp->title)[i].tolower()) break;
            if(i==span-1) flag =1;
        }
        if(flag){
            print_book(&temp);
            return;
        }
        temp = temp->next;
    }
    printf("No book with that title was found.\n");
}

void findByLocation(Deque *deque, int loc){
    DListNode *temp = deque->_head;
    int now = 0;
    while(temp!=NULL){
        if(loc==now) {
            print_book(&temp);
            return;
        }
        temp = temp->next;
        now++;
    }
    printf("Failed to retrieve book.\n");
}

void deq_popBack(Deque *deque)
{
    if (!deq_isEmpty(deque)) {
        DListNode *temp;
        if (deque->_head == deque->_tail) {
            temp = deque->_head;
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else {
            temp = deque->_tail;
            deque->_tail = deque->_tail->prev;
            deque->_tail->next = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

int main(int argc, char const *argv[])
{
    Deque mydeq;
    deq_init(&mydeq);

    char inp[500];
    while(fgets(inp, 500, stdin) != NULL) {
        
    }

    printf("Bepi has %d book(s).", mydeq._size);
    return 0;
}