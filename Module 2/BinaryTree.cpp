#include<iostream>

using namespace std;

// Node
struct BinaryTree{
    struct Node{
        char label;
        Node *left {NULL}, 
            *right {NULL}, 
            *parent {NULL};  
    };

    Node *root {NULL};

    BinaryTree(char label) {
        root = (Node*) malloc(sizeof(Node));
        root->label = label;
        cout << root->label << endl;
    }

    bool isEmpty() {
        return root == NULL;
    }

    Node* insertLeft(char label) {
        Node* newNode = new Node;
        if (isEmpty()){
               root = (Node*) malloc(sizeof(Node));
               root->label = label;
               newNode = root;
        } else {
            Node* temp = root;
            while (){
            }
            
        }
    }

};

int main() {
    BinaryTree tree('A');
}
