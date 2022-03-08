/**
 */

#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

string LIST_PRIORITAS[] = {
    "pusingkebanyakantugas",
    "diare",
    "maag",
    "flu"
};

struct Kamar {
    struct KamarNode {
        string nama_pasien;
        int prioritas;
        struct KamarNode *next;
    };

    KamarNode *front;
    int size = 0;
    int capacity;

    Kamar(int capacity) {
        front = NULL;
        this->capacity = capacity;
    }

    bool isEmpty() {
        return front == NULL;
    }

    bool isFull() {
        return size == capacity;
    }

    void enqueue(string x, int priority) {
        KamarNode *newNode = new KamarNode;
        newNode->nama_pasien = x;
        newNode->prioritas = priority;
        newNode->next = NULL;

        if (isEmpty()) {
            front = newNode;
        } else {
            KamarNode *curr = front;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        size++;
    }

    void dequeue() {
        if (isEmpty()) return;
        else {
            KamarNode *temp = front;
            front = temp->next;
            size--;
            cout << "Pasien atas nama " << temp->nama_pasien << " sudah selesai konsultasi mengenai " << LIST_PRIORITAS[temp->prioritas] << "." <<endl;
            free(temp);
        }
    }
};

struct Puskesmas {
    struct PasienNode {
        char* nama_pasien;
        int prioritas;
        PasienNode *next, *prev;
    };

    PasienNode *front {NULL};
    Kamar *kamar;
    int size = 0;

    Puskesmas(int kamar_capacity) {
        kamar = new Kamar(kamar_capacity);
    }

    void addPasien(char* nama_pasien, int prioritas) {
        PasienNode *newNode = new PasienNode;
        newNode->nama_pasien = nama_pasien;
        newNode->prioritas = prioritas;
        newNode->prev = NULL;
        newNode->next = NULL;
        cout << "Pasien atas nama " << nama_pasien << " terdaftar ke database." << endl;

        if (isEmpty()) {
            if(!(kamar->isFull())){
                kamar->enqueue(nama_pasien, prioritas);
                cout << "Pasien atas nama "<< nama_pasien << " Langsung masuk." << endl;
            } else {
                front = newNode;
                cout << "Pasien atas nama " << nama_pasien << " mengantri." << endl;
                size++;
            }
        } else {
            PasienNode *curr = front;
            if (prioritas < front->prioritas || (prioritas==front->prioritas && strcmp(nama_pasien, front->nama_pasien)<0)){
                newNode->next = front;
                front->prev=newNode;
                front = newNode;
            } else {
                while (curr->next!=NULL && curr->next->prioritas<prioritas){
                    curr=curr->next;
                    newNode->prev=curr;
                    newNode->next=curr->next;
                    curr->next->prev=newNode;
                    curr->next=newNode;
                }
            }
            
            cout << "Pasien atas nama " << nama_pasien << " mengantri." << endl;
            size++;
            if (kamar->isFull()) return;
            kamar->enqueue(front->nama_pasien, front->prioritas);
            cout << "Pasien atas nama "<< nama_pasien << " Langsung masuk." << endl;
            PasienNode *temp = front;
            temp->next->prev = NULL;
            front = temp->next;
            free(temp);
            size--;
        }
    }

    void nextKamar() {
        kamar->dequeue();
        if (!isEmpty()) return;
        PasienNode *curr = front;
        kamar->enqueue(curr->nama_pasien, curr->prioritas);
        curr->next->prev = NULL;
        front = curr->next;
        curr->next = NULL;
        cout << "Pasien atas nama " << curr->nama_pasien << " masuk dari antrian." << endl;
        free(curr);
        size--;
    }

    bool isEmpty() {
        return front == NULL;
    }
};


int main(int argc, char const *argv[])
{
    int n;
    int data[4] {0};
    scanf("%d", &n);
    Puskesmas puskesmas(n);
    while (scanf("%d", &n)!=EOF) {
        if(n==1) {
            char nama_pasien[20];
            char prioritas[30];
            scanf("%s", nama_pasien);
            scanf("%s", prioritas);
            switch (prioritas[0]) {
                case 'p':
                    puskesmas.addPasien(nama_pasien, 0);
                    data[0]++;
                    break;
                case 'd':
                    puskesmas.addPasien(nama_pasien, 1);
                    data[1]++;
                    break;
                case 'm':
                    puskesmas.addPasien(nama_pasien, 2);
                    data[2]++;
                    break;
                case 'f':
                    puskesmas.addPasien(nama_pasien, 3);
                    data[3]++;
                    break;
                default:
                    break;
            }
        } else {
            puskesmas.nextKamar();
        }
    }
    while (!(puskesmas.kamar->isEmpty())) {
        puskesmas.kamar->dequeue();
    }
    cout << "Data pasien harin ini:" << endl;
    cout << "flu: " << data[3] << endl;
    cout << "diare: " << data[2] << endl;
    cout << "maag: " << data[1] << endl;
    cout << "pusingkebanyakantugas: " << data[0] << endl; 
    return 0;
}