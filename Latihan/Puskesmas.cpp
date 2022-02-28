/**
 * Implementasi ADT PriorityQueue menggunakan Linked List
 * [default: minimum priority]
 * 
 * Dibuat dan ditulis oleh Bayu Laksana
 * Dimodifikasi oleh Riski Ilyas
 * Implementasi untuk bahasa C
 * 
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
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
        string nama_pasien;
        int prioritas;
        PasienNode *next, *prev;
    };

    PasienNode *front {nullptr};
    Kamar *kamar;
    int size = 0;

    Puskesmas(int kamar_capacity) {
        kamar = new Kamar(kamar_capacity);
    }

    void addPasien(string nama_pasien, int prioritas) {
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
            }
        } else {
            if (!(kamar->isFull())){
                kamar->enqueue(nama_pasien, prioritas);
                cout << "Pasien atas nama "<< nama_pasien << " Langsung masuk." << endl;
            } else {
                PasienNode *curr = front;
                while (curr->next != NULL && curr->prioritas < prioritas) {
                    curr = curr->next;
                }
                if (curr->next == NULL && curr->prioritas < prioritas) {
                    curr->next = newNode;
                    newNode->prev = curr;
                }else if (curr == front) {
                    newNode->next = front;
                    front->prev = newNode;
                    front = newNode;
                } else {
                    newNode->next = curr;
                    newNode->prev = curr->prev;
                    curr->prev->next = newNode;
                    curr->prev = newNode;
                }
                curr->next = newNode;
                cout << "Pasien atas nama " << nama_pasien << " mengantri." << endl;
                size++;
            }
        }
    }

    void nextKamar() {
        kamar->dequeue();
        if (isEmpty()) return;
        PasienNode *curr = front;
        kamar->enqueue(curr->nama_pasien, curr->prioritas);
        curr->next->prev = curr->prev;
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
    cout << "flu: " << data[0] << endl;
    cout << "diare: " << data[1] << endl;
    cout << "maag: " << data[2] << endl;
    cout << "pusingkebanyakantugas: " << data[3] << endl; 
    return 0;
}