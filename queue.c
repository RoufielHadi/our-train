/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/* *** Konstruktor & Destructor *** */
void CreateQueue(Queue *Q) {
    Q->First = NULL;
    Q->Last = NULL;
}

boolean isEmptyQueue(Queue Q) {
    return (Q.First == NULL && Q.Last == NULL);
}

addressAntrean CreateNodeAntrean(int nomorAntrean) {
    addressAntrean P = (addressAntrean)malloc(sizeof(AntreanOffline));
    if (P != NULL) {
        P->nomor_antrean = nomorAntrean;
        P->next = NULL;
    }
    return P;
}

void DeAlokasiAntrean(addressAntrean *p) {
    free(*p);
    *p = NULL;
}

/* *** Operasi Enqueue & Dequeue *** */
void Enqueue(Queue *Q, int nomorAntrean) {
    addressAntrean P = CreateNodeAntrean(nomorAntrean);
    if (P != NULL) {
        if (isEmptyQueue(*Q)) {
            Q->First = P;
        } else {
            Q->Last->next = P;
        }
        Q->Last = P;
    }
}

boolean Dequeue(Queue *Q, int *nomorAntrean) {
    if (isEmptyQueue(*Q)) {
        return FALSE;
    }
    
    addressAntrean P = Q->First;
    *nomorAntrean = P->nomor_antrean;
    
    if (Q->First == Q->Last) {
        Q->First = NULL;
        Q->Last = NULL;
    } else {
        Q->First = P->next;
    }
    
    P->next = NULL;
    DeAlokasiAntrean(&P);
    
    return TRUE;
}

/* *** Operasi Tambahan *** */
int NbElmtQueue(Queue Q) {
    int count = 0;
    addressAntrean P = Q.First;
    
    while (P != NULL) {
        count++;
        P = P->next;
    }
    
    return count;
}

void TampilQueue(Queue Q) {
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong\n");
        return;
    }
    
    printf("Isi antrian: ");
    addressAntrean P = Q.First;
    while (P != NULL) {
        printf("%d", P->nomor_antrean);
        P = P->next;
        if (P != NULL) {
            printf(" -> ");
        }
    }
    printf(" -> NULL\n");
}

int Front(Queue Q) {
    if (!isEmptyQueue(Q)) {
        return Q.First->nomor_antrean;
    }
    return -1; // Nilai error jika queue kosong
}

int Rear(Queue Q) {
    if (!isEmptyQueue(Q)) {
        return Q.Last->nomor_antrean;
    }
    return -1; // Nilai error jika queue kosong
}

