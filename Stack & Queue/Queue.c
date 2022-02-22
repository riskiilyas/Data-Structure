#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct queueNode_t {
    int data;
    struct queueNode_t *next;
} QueueNode;

typedef struct queue_t {
    QueueNode   *_front, 
                *_rear;
    unsigned _size;
} Queue;

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_pushBack(Queue *queue, int value)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
        newNode->next = NULL;
      
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pushFront(Queue *queue, int value) {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
        newNode->next = NULL;

        if (queue_isEmpty(queue)) {
            queue->_front = queue->_rear = newNode;
        } else {
            newNode->next = queue->_front;
            queue->_front = newNode;
        }
        
    }
    print_queue(&queue);
}

void queue_popFront(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
      
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    } 
    print_queue(queue);
}

void queue_popBack(Queue *queue) {
    // if (!queue_isEmpty(queue)){
    //     QueueNode *temp = queue->_rear;
    //     queue->_rear = 
    // }
}

int queue_front(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->_front->data);
    }
    return 0;
}

int queue_back(Queue *queue) {
    if (!queue_isEmpty(queue)){
        return (queue->_rear->data);
    }
    return 0;
}

void queue_init(Queue* queue) {
    queue->_front = NULL;
    queue->_rear = NULL;
    queue->_size = 0;
}

void print_queue(Queue *queue) {
    QueueNode *temp = queue->_front;
    while (temp->next != NULL){
        printf("%d, ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue queue;
    queue_init(&queue);
    queue_pushFront(&queue, 25);
    queue_pushFront(&queue, 42);
}