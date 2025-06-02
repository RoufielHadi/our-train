/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"

/* Struktur data AntreanOffline untuk pembelian tiket secara offline */
typedef struct AntreanOffline {
    int nomor_antrean;
    struct AntreanOffline* next;
} AntreanOffline;

/* Definisi pointer ke AntreanOffline */
typedef AntreanOffline* addressAntrean;

/* Definisi struktur Queue untuk antrian */
typedef struct {
    addressAntrean First;  // penunjuk ke elemen pertama
    addressAntrean Last;   // penunjuk ke elemen terakhir
} Queue;

/* *** Konstruktor & Destructor *** */
boolean isEmptyQueue(Queue Q);
/* Tujuan : Memeriksa apakah queue kosong */
/* IS      : Queue terdefinisi */
/* FS      : Mengembalikan TRUE jika queue kosong, FALSE jika tidak */

void CreateQueue(Queue *Q);
/* Tujuan : Membuat queue kosong */
/* IS      : Q belum terdefinisi */
/* FS      : Q terdefinisi dengan First dan Last = NULL */

addressAntrean CreateNodeAntrean(int nomorAntrean);
/* Tujuan : Membuat node antrean baru */
/* IS      : Nomor antrean terdefinisi */
/* FS      : Mengembalikan pointer ke node antrean baru */

void DeAlokasiAntrean(addressAntrean *p);
/* Tujuan : Menghapus node antrean dari memori (dealokasi) */
/* IS      : p terdefinisi */
/* FS      : p dikembalikan ke sistem (dealokasi) */

/* *** Operasi Enqueue & Dequeue *** */
void Enqueue(Queue *Q, int nomorAntrean);
/* Tujuan : Menambahkan elemen baru ke belakang queue */
/* IS      : Queue mungkin kosong */
/* FS      : Elemen baru ditambahkan di belakang queue */

boolean Dequeue(Queue *Q, int *nomorAntrean);
/* Tujuan : Menghapus elemen dari depan queue dan menyimpannya ke nomorAntrean */
/* IS      : Queue mungkin kosong */
/* FS      : Jika queue tidak kosong, elemen depan dihapus, nilai disimpan dalam nomorAntrean, 
             dan mengembalikan TRUE. Jika queue kosong, mengembalikan FALSE */

/* *** Operasi Tambahan *** */
int NbElmtQueue(Queue Q);
/* Tujuan : Mengembalikan jumlah elemen dalam queue */
/* IS      : Queue terdefinisi */
/* FS      : Mengembalikan jumlah elemen dalam queue */

void TampilQueue(Queue Q);
/* Tujuan : Menampilkan isi queue dari depan ke belakang */
/* IS      : Queue terdefinisi */
/* FS      : Semua elemen queue ditampilkan ke layar */

int Front(Queue Q);
/* Tujuan : Mengembalikan nilai elemen terdepan tanpa menghapusnya */
/* IS      : Queue tidak kosong */
/* FS      : Mengembalikan nilai nomor_antrean elemen terdepan */

int Rear(Queue Q);
/* Tujuan : Mengembalikan nilai elemen terakhir dalam queue tanpa menghapusnya */
/* IS      : Queue tidak kosong */
/* FS      : Mengembalikan nilai nomor_antrean elemen terakhir dalam queue */

#endif

