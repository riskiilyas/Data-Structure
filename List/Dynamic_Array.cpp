#include<iostream>

typedef struct Dynamic_Array {
    int *arr;
    int size;
    int capacity;

    bool isEmpty() {
        return this->size == 0;
    }

    bool isFull() {
        return this->size == this->capacity;
    }

    void push_back(int value) {
        
    }

} Dynamic_Array; 



int main() {

}