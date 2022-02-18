#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct staque {
    int *arr;
    int size;
    int capacity;
} staque;

void push_front(staque *q, int x) {
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->arr = (int *)realloc(q->arr, q->capacity * sizeof(int));
    }
    for (int i = q->size; i > 0; i--) {
        q->arr[i] = q->arr[i - 1];
    }
    q->arr[0] = x;
    q->size++;
}

void push_back(staque *q, int x) {
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->arr = (int *)realloc(q->arr, q->capacity * sizeof(int));
    }
    q->arr[q->size] = x;
    q->size++;
}

int pop_front(staque *q) {
    int x = q->arr[0];
    for (int i = 0; i < q->size - 1; i++) {
        q->arr[i] = q->arr[i + 1];
    }
    q->size--;
    return x;
}

int pop_back(staque *q) {
    int x = q->arr[q->size - 1];
    q->size--;
    return x;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    staque q;
    q.arr = (int *)malloc(n * sizeof(int));
    q.size = 0;
    q.capacity = n;
    for (int i = 0; i < n; i++) {
        char inp[10];
        scanf("%s", inp);
        if (strcmp(inp, "push_front") == 0) {
            int x;
            scanf("%d", &x);
            push_front(&q, x);
        } else if (strcmp(inp, "push_back") == 0) {
            int x;
            scanf("%d", &x);
            push_back(&q, x);
        } else if (strcmp(inp, "pop_front") == 0) {
            printf("%d\n", pop_front(&q));
        } else if (strcmp(inp, "pop_back") == 0) {
            printf("%d\n", pop_back(&q));
        }
    }
    return 0;
}

