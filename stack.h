/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef STACK_H
#define STACK_H

#include "boolean.h"
#include "linked.h"
#include "time.h"

#define FILE_RIWAYAT "riwayat_pemesanan.txt"

// Struktur data untuk user dalam riwayat tiket
typedef struct {
    char nama[100];
    char email[100];
    char nomor_telepon[20];
} UserRiwayat;

// Struktur data untuk kereta dalam riwayat tiket
typedef struct {
    char kode_kereta[20];
    char nama_kereta[100];
    char stasiun_asal[100];
    char stasiun_tujuan[100];
    char jam_berangkat[10];
    char jam_tiba[10];
    char tanggal_berangkat[20];
    char kelas[50];
    int harga;
} KeretaRiwayat;

// Definisi struktur data RiwayatTiket
typedef struct {
    UserRiwayat riwayat_user;
    KeretaRiwayat riwayat_kereta; 
    int riwayat_nomor_gerbong;
    int riwayat_nomor_kursi; 
    Waktu riwayat_waktu_pemesanan; 
} RiwayatTiket;

// Definisi struktur node DataRiwayat
typedef struct DataRiwayat {
    RiwayatTiket info;
    struct DataRiwayat* next;
} DataRiwayat;

// Definisi alias untuk pointer DataRiwayat
typedef DataRiwayat* addressRiwayat;

// Definisi struktur Stack untuk Riwayat Pembelian
typedef struct {
    addressRiwayat top;
} StackRiwayat;

boolean isEmptyStackRiwayat(StackRiwayat S);
/* Tujuan : Memeriksa apakah stack riwayat kosong */
/* IS      : Stack terdefinisi */
/* FS      : Mengembalikan TRUE jika stack kosong, FALSE jika tidak */

void CreateStackRiwayat(StackRiwayat *S);
/* Tujuan : Membuat stack riwayat kosong */
/* IS      : Stack belum terdefinisi */
/* FS      : Stack terdefinisi dan kosong (S.top = NULL) */

void PushRiwayat(StackRiwayat *S, RiwayatTiket tiket);
/* Tujuan : Menambahkan elemen ke stack riwayat (push) */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Elemen tiket ditambahkan sebagai elemen paling atas stack */

boolean PopRiwayat(StackRiwayat *S, RiwayatTiket *tiket);
/* Tujuan : Menghapus elemen dari stack riwayat (pop) */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Jika stack tidak kosong, elemen paling atas stack dihapus dan nilainya disimpan di tiket, 
             mengembalikan TRUE. Jika stack kosong, mengembalikan FALSE */

boolean TopRiwayat(StackRiwayat S, RiwayatTiket *tiket);
/* Tujuan : Mengembalikan elemen di puncak stack riwayat tanpa menghapusnya */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Jika stack tidak kosong, nilai elemen paling atas disimpan di tiket, mengembalikan TRUE.
             Jika stack kosong, mengembalikan FALSE */

int NbElmtStackRiwayat(StackRiwayat S);
/* Tujuan : Menghitung jumlah elemen dalam stack riwayat */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Mengembalikan jumlah elemen dalam stack */

void TampilStackRiwayat(StackRiwayat S);
/* Tujuan : Menampilkan isi stack riwayat */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Informasi setiap elemen stack ditampilkan ke layar */

void DeAlokasiStackRiwayat(StackRiwayat *S);
/* Tujuan : Menghapus semua elemen stack dari memori */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Stack kosong, semua elemen telah dihapus dari memori */

void SaveRiwayatToFile(StackRiwayat S, const char *filename);
/* Tujuan : Menyimpan stack riwayat ke dalam file */
/* IS      : Stack terdefinisi, mungkin kosong */
/* FS      : Informasi riwayat tiket tersimpan dalam file */

void LoadRiwayatFromFile(StackRiwayat *S, const char *filename);
/* Tujuan : Membaca stack riwayat dari file */
/* IS      : Stack terdefinisi */
/* FS      : Stack berisi riwayat tiket yang dibaca dari file */

#endif

