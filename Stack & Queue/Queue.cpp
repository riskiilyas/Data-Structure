#include<iostream>

using namespace std;

// IMPLEMENTED USING DYNAMIC ARRAY
struct darray {
    int* arr;
    int size;
    int capacity;
};

// IMPLEMENTED USING LINKED LIST
struct node {
    int value;
    node* next;
};

struct QueueL {
    private:
        node *front, *back;
        int size;

    public:
        void push(int newVal) {
            if (this->isEmpty()) {
                
            }
            
        }

        void pop() {

        }

        bool isEmpty() {
            return this->front == NULL && this->back == NULL;
        }
};

int main() {

}