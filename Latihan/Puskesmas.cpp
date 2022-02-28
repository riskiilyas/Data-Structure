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

static string LIST_PRIORITAS[] = {
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
    int size;
    int capacity;

    Kamar(int capacity) {
        front = NULL;
        capacity = capacity;
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
    int size {0};

    Puskesmas(int kamar_capacity) {
        kamar = new Kamar(kamar_capacity);
    }

    void addPasien(string nama_pasien, int prioritas) {
        PasienNode *newNode = new PasienNode;
        newNode->nama_pasien = nama_pasien;
        newNode->prioritas = prioritas;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (isEmpty()) {
            front = newNode;
        } else {
            if (!(kamar->isFull())){
                kamar->enqueue(nama_pasien, prioritas);
            } else {
                PasienNode *curr = front;
                while (curr->next != NULL || curr->prioritas < prioritas) {
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
                size++;
            }
        }
    }

    void nextKamar() {
        if (isEmpty()) return;
        PasienNode *curr = front;
        kamar->dequeue();
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
    return 0;
}