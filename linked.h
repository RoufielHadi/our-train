/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef LINKED_H
#define LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "time.h" // Include the time.h file for Waktu ADT

// Struktur data Stasiun Transit
typedef struct StasiunTransit {
    char nama_stasiun[30];
    WaktuSingkat waktu_transit; // Menggunakan WaktuSingkat untuk stasiun transit
    struct StasiunTransit* next; // untuk stasiun selanjutnya 
} StasiunTransit;  // LINKED LIST

// Struktur data Jadwal Kereta
typedef struct {
    StasiunTransit* head;  // menunjuk ke node pertama stasiun transit
} JadwalKereta;

// Struktur data informasi kereta
typedef struct {
    char id_Kereta[10];
    char nama_kereta[50];
    char jenis_layanan[50];
    float harga_tiket;
    char jumlah_gerbong[2];
    JadwalKereta jadwal;  // hubungan langsung dengan daftar stasiun transit
} InformasiKereta;

typedef struct DataInformasiKereta {
    InformasiKereta kereta_info;
    struct DataInformasiKereta* next;
} DataInformasiKereta;  // LINKED LIST

// Struktur untuk user
typedef struct {
    char email[100];
    char nama[50];
    char alamat[50];
    char nomor_telepon[13]; 
    char password[64];
    int is_admin;  // Tipe pengguna: 1=admin, 2=kasir, 3=mesin, 4=user biasa
} User;

typedef struct DataUser {
    User user_info;
    struct DataUser* next; 
} DataUser;  //LINKED LIST

// Struktur Payment
typedef struct {
    char email[100];
    char no_rekening[16];
    int saldo; 
    char pin[64]; 
} Payment; 

typedef struct PaymentUser {
    Payment payment_info; 
    struct PaymentUser* next;
} PaymentUser;  //LINKED LIST

// Struck untuk mendefinisikan list
typedef struct {
    DataUser* First;
} ListUser;

typedef struct {
    PaymentUser* First;
} ListPayment;

typedef struct {
    DataInformasiKereta* First;
} ListKereta;

typedef struct {
    StasiunTransit* First;
} ListStasiun;

// =====================================================
// ===================== KONSTRUKTOR ===================
// =====================================================
void CreateListUser(ListUser *L);
// Tujuan : Membuat list user kosong
// IS     : L sembarang
// FS     : Terbentuk list user kosong (First = NULL)

void CreateListPayment(ListPayment *L);
// Tujuan : Membuat list payment kosong
// IS     : L sembarang
// FS     : Terbentuk list payment kosong (First = NULL)

void CreateListKereta(ListKereta *L);
// Tujuan : Membuat list kereta kosong
// IS     : L sembarang
// FS     : Terbentuk list kereta kosong (First = NULL)

void CreateListStasiun(ListStasiun *L);
// Tujuan : Membuat list stasiun kosong
// IS     : L sembarang
// FS     : Terbentuk list stasiun kosong (First = NULL)

void CreateJadwalKereta(JadwalKereta *J);
// Tujuan : Membuat jadwal kereta kosong
// IS     : J sembarang
// FS     : Terbentuk jadwal kereta kosong (head = NULL)

void DeleteListUser(ListUser *L);
// Tujuan : Menghapus semua elemen dalam list user
// IS     : L mungkin kosong atau berisi elemen
// FS     : Semua elemen dalam list user dihapus dan didealokasi

void DeleteListPayment(ListPayment *L);
// Tujuan : Menghapus semua elemen dalam list payment
// IS     : L mungkin kosong atau berisi elemen
// FS     : Semua elemen dalam list payment dihapus dan didealokasi

void DeleteListKereta(ListKereta *L);
// Tujuan : Menghapus semua elemen dalam list kereta
// IS     : L mungkin kosong atau berisi elemen
// FS     : Semua elemen dalam list kereta dihapus dan didealokasi

void DeleteListStasiun(ListStasiun *L);
// Tujuan : Menghapus semua elemen dalam list stasiun
// IS     : L mungkin kosong atau berisi elemen
// FS     : Semua elemen dalam list stasiun dihapus dan didealokasi

// =====================================================
// ===================== VALIDATOR =====================
// =====================================================
boolean isEmptyUser(ListUser L);
// Tujuan : Mengecek apakah list user kosong
// Mengembalikan TRUE jika list user kosong, FALSE jika tidak

boolean isEmptyPayment(ListPayment L);
// Tujuan : Mengecek apakah list payment kosong
// Mengembalikan TRUE jika list payment kosong, FALSE jika tidak

boolean isEmptyKereta(ListKereta L);
// Tujuan : Mengecek apakah list kereta kosong
// Mengembalikan TRUE jika list kereta kosong, FALSE jika tidak

boolean isEmptyStasiun(ListStasiun L);
// Tujuan : Mengecek apakah list stasiun kosong
// Mengembalikan TRUE jika list stasiun kosong, FALSE jika tidak

boolean isEmptyJadwal(JadwalKereta J);
// Tujuan : Mengecek apakah jadwal kereta kosong
// Mengembalikan TRUE jika jadwal kereta kosong, FALSE jika tidak

// =====================================================
// ================== OPERASI DASAR ====================
// =====================================================
DataUser* CreateDataUser(User userData);
// Tujuan : Membuat node baru dengan data user
// IS     : userData terdefinisi
// FS     : Mengembalikan address node baru, atau NULL jika gagal

PaymentUser* CreateDataPayment(Payment paymentData);
// Tujuan : Membuat node baru dengan data payment
// IS     : paymentData terdefinisi
// FS     : Mengembalikan address node baru, atau NULL jika gagal

DataInformasiKereta* CreateDataKereta(InformasiKereta keretaData);
// Tujuan : Membuat node baru dengan data kereta
// IS     : keretaData terdefinisi
// FS     : Mengembalikan address node baru, atau NULL jika gagal

StasiunTransit* CreateStasiunTransit(char* nama_stasiun, WaktuSingkat waktu_transit);
// Tujuan : Membuat node baru dengan data stasiun transit
// IS     : nama_stasiun dan waktu_transit terdefinisi
// FS     : Mengembalikan address node baru, atau NULL jika gagal

void InsertFirstUser(ListUser *L, DataUser *P);
// Tujuan : Menambahkan elemen P sebagai elemen pertama dalam list user
// IS     : L mungkin kosong
// FS     : P menjadi elemen pertama dalam list user

void InsertFirstPayment(ListPayment *L, PaymentUser *P);
// Tujuan : Menambahkan elemen P sebagai elemen pertama dalam list payment
// IS     : L mungkin kosong
// FS     : P menjadi elemen pertama dalam list payment

void InsertFirstKereta(ListKereta *L, DataInformasiKereta *P);
// Tujuan : Menambahkan elemen P sebagai elemen pertama dalam list kereta
// IS     : L mungkin kosong
// FS     : P menjadi elemen pertama dalam list kereta

void InsertFirstStasiun(ListStasiun *L, StasiunTransit *P);
// Tujuan : Menambahkan elemen P sebagai elemen pertama dalam list stasiun
// IS     : L mungkin kosong
// FS     : P menjadi elemen pertama dalam list stasiun

void InsertFirstJadwal(JadwalKereta *J, StasiunTransit *P);
// Tujuan : Menambahkan elemen P sebagai elemen pertama dalam jadwal kereta
// IS     : J mungkin kosong
// FS     : P menjadi elemen pertama dalam jadwal kereta

void InsertLastUser(ListUser *L, DataUser *P);
// Tujuan : Menambahkan elemen P sebagai elemen terakhir dalam list user
// IS     : L mungkin kosong
// FS     : P menjadi elemen terakhir dalam list user

void InsertLastPayment(ListPayment *L, PaymentUser *P);
// Tujuan : Menambahkan elemen P sebagai elemen terakhir dalam list payment
// IS     : L mungkin kosong
// FS     : P menjadi elemen terakhir dalam list payment

void InsertLastKereta(ListKereta *L, DataInformasiKereta *P);
// Tujuan : Menambahkan elemen P sebagai elemen terakhir dalam list kereta
// IS     : L mungkin kosong
// FS     : P menjadi elemen terakhir dalam list kereta

void InsertLastStasiun(ListStasiun *L, StasiunTransit *P);
// Tujuan : Menambahkan elemen P sebagai elemen terakhir dalam list stasiun
// IS     : L mungkin kosong
// FS     : P menjadi elemen terakhir dalam list stasiun

void InsertLastJadwal(JadwalKereta *J, StasiunTransit *P);
// Tujuan : Menambahkan elemen P sebagai elemen terakhir dalam jadwal kereta
// IS     : J mungkin kosong
// FS     : P menjadi elemen terakhir dalam jadwal kereta

void InsertAfterUser(DataUser *pBef, DataUser *PNew);
// Tujuan : Menyisipkan elemen PNew setelah elemen pBef dalam list user
// IS     : pBef tidak NULL
// FS     : PNew menjadi elemen setelah pBef dalam list user

void InsertAfterPayment(PaymentUser *pBef, PaymentUser *PNew);
// Tujuan : Menyisipkan elemen PNew setelah elemen pBef dalam list payment
// IS     : pBef tidak NULL
// FS     : PNew menjadi elemen setelah pBef dalam list payment

void InsertAfterKereta(DataInformasiKereta *pBef, DataInformasiKereta *PNew);
// Tujuan : Menyisipkan elemen PNew setelah elemen pBef dalam list kereta
// IS     : pBef tidak NULL
// FS     : PNew menjadi elemen setelah pBef dalam list kereta

void InsertAfterStasiun(StasiunTransit *pBef, StasiunTransit *PNew);
// Tujuan : Menyisipkan elemen PNew setelah elemen pBef dalam list stasiun
// IS     : pBef tidak NULL
// FS     : PNew menjadi elemen setelah pBef dalam list stasiun

void DeleteFirstUser(ListUser *L);
// Tujuan : Menghapus elemen pertama dari list user
// IS     : List tidak kosong
// FS     : Elemen pertama dalam list user dihapus dan didealokasi

void DeleteFirstPayment(ListPayment *L);
// Tujuan : Menghapus elemen pertama dari list payment
// IS     : List tidak kosong
// FS     : Elemen pertama dalam list payment dihapus dan didealokasi

void DeleteFirstKereta(ListKereta *L);
// Tujuan : Menghapus elemen pertama dari list kereta
// IS     : List tidak kosong
// FS     : Elemen pertama dalam list kereta dihapus dan didealokasi

void DeleteFirstStasiun(ListStasiun *L);
// Tujuan : Menghapus elemen pertama dari list stasiun
// IS     : List tidak kosong
// FS     : Elemen pertama dalam list stasiun dihapus dan didealokasi

void DeleteFirstJadwal(JadwalKereta *J);
// Tujuan : Menghapus elemen pertama dari jadwal kereta
// IS     : Jadwal tidak kosong
// FS     : Elemen pertama dalam jadwal kereta dihapus dan didealokasi

void DeleteLastUser(ListUser *L);
// Tujuan : Menghapus elemen terakhir dari list user
// IS     : List tidak kosong
// FS     : Elemen terakhir dalam list user dihapus dan didealokasi

void DeleteLastPayment(ListPayment *L);
// Tujuan : Menghapus elemen terakhir dari list payment
// IS     : List tidak kosong
// FS     : Elemen terakhir dalam list payment dihapus dan didealokasi

void DeleteLastKereta(ListKereta *L);
// Tujuan : Menghapus elemen terakhir dari list kereta
// IS     : List tidak kosong
// FS     : Elemen terakhir dalam list kereta dihapus dan didealokasi

void DeleteLastStasiun(ListStasiun *L);
// Tujuan : Menghapus elemen terakhir dari list stasiun
// IS     : List tidak kosong
// FS     : Elemen terakhir dalam list stasiun dihapus dan didealokasi

void DeleteLastJadwal(JadwalKereta *J);
// Tujuan : Menghapus elemen terakhir dari jadwal kereta
// IS     : Jadwal tidak kosong
// FS     : Elemen terakhir dalam jadwal kereta dihapus dan didealokasi

void DeleteAfterUser(DataUser *pBef);
// Tujuan : Menghapus elemen setelah pBef dalam list user
// IS     : pBef tidak NULL dan memiliki elemen setelahnya
// FS     : Elemen setelah pBef dalam list user dihapus dan didealokasi

void DeleteAfterPayment(PaymentUser *pBef);
// Tujuan : Menghapus elemen setelah pBef dalam list payment
// IS     : pBef tidak NULL dan memiliki elemen setelahnya
// FS     : Elemen setelah pBef dalam list payment dihapus dan didealokasi

void DeleteAfterKereta(DataInformasiKereta *pBef);
// Tujuan : Menghapus elemen setelah pBef dalam list kereta
// IS     : pBef tidak NULL dan memiliki elemen setelahnya
// FS     : Elemen setelah pBef dalam list kereta dihapus dan didealokasi

void DeleteAfterStasiun(StasiunTransit *pBef);
// Tujuan : Menghapus elemen setelah pBef dalam list stasiun
// IS     : pBef tidak NULL dan memiliki elemen setelahnya
// FS     : Elemen setelah pBef dalam list stasiun dihapus dan didealokasi

void DeAlokasiUser(DataUser **P);
// Tujuan : Mengembalikan memori dari suatu node user ke sistem
// IS     : P terdefinisi
// FS     : Memori yang ditempati oleh P dikembalikan ke sistem

void DeAlokasiPayment(PaymentUser **P);
// Tujuan : Mengembalikan memori dari suatu node payment ke sistem
// IS     : P terdefinisi
// FS     : Memori yang ditempati oleh P dikembalikan ke sistem

void DeAlokasiKereta(DataInformasiKereta **P);
// Tujuan : Mengembalikan memori dari suatu node kereta ke sistem
// IS     : P terdefinisi
// FS     : Memori yang ditempati oleh P dikembalikan ke sistem

void DeAlokasiStasiun(StasiunTransit **P);
// Tujuan : Mengembalikan memori dari suatu node stasiun ke sistem
// IS     : P terdefinisi
// FS     : Memori yang ditempati oleh P dikembalikan ke sistem

// =====================================================
// ================= OPERASI TAMBAHAN =================
// =====================================================

int NbElmtUser(ListUser L);
// Tujuan : Menghitung jumlah elemen dalam list user
// Mengembalikan jumlah elemen dalam list user (0 jika kosong)

int NbElmtPayment(ListPayment L);
// Tujuan : Menghitung jumlah elemen dalam list payment
// Mengembalikan jumlah elemen dalam list payment (0 jika kosong)

int NbElmtKereta(ListKereta L);
// Tujuan : Menghitung jumlah elemen dalam list kereta
// Mengembalikan jumlah elemen dalam list kereta (0 jika kosong)

int NbElmtStasiun(ListStasiun L);
// Tujuan : Menghitung jumlah elemen dalam list stasiun
// Mengembalikan jumlah elemen dalam list stasiun (0 jika kosong)

int NbElmtJadwal(JadwalKereta J);
// Tujuan : Menghitung jumlah elemen dalam jadwal kereta
// Mengembalikan jumlah elemen dalam jadwal kereta (0 jika kosong)

DataUser* SearchUserByEmail(ListUser L, char *email);
// Tujuan : Mencari elemen user berdasarkan email
// Mengembalikan DataUser* jika ditemukan, NULL jika tidak

PaymentUser* SearchPaymentByEmail(ListPayment L, char *email);
// Tujuan : Mencari elemen payment berdasarkan email
// Mengembalikan PaymentUser* jika ditemukan, NULL jika tidak

DataInformasiKereta* SearchKeretaById(ListKereta L, char *id_Kereta);
// Tujuan : Mencari elemen kereta berdasarkan ID kereta
// Mengembalikan DataInformasiKereta* jika ditemukan, NULL jika tidak

StasiunTransit* SearchStasiunByNama(ListStasiun L, char *nama_stasiun);
// Tujuan : Mencari elemen stasiun berdasarkan nama stasiun
// Mengembalikan StasiunTransit* jika ditemukan, NULL jika tidak

void PrintUser(ListUser L);
// Tujuan : Menampilkan semua elemen dalam list user
// IS     : List mungkin kosong atau berisi elemen
// FS     : Data dalam list user ditampilkan di layar

void PrintPayment(ListPayment L);
// Tujuan : Menampilkan semua elemen dalam list payment
// IS     : List mungkin kosong atau berisi elemen
// FS     : Data dalam list payment ditampilkan di layar

void PrintKereta(ListKereta L);
// Tujuan : Menampilkan semua elemen dalam list kereta
// IS     : List mungkin kosong atau berisi elemen
// FS     : Data dalam list kereta ditampilkan di layar

void PrintStasiun(ListStasiun L);
// Tujuan : Menampilkan semua elemen dalam list stasiun
// IS     : List mungkin kosong atau berisi elemen
// FS     : Data dalam list stasiun ditampilkan di layar

void PrintJadwal(JadwalKereta J);
// Tujuan : Menampilkan semua elemen dalam jadwal kereta
// IS     : Jadwal mungkin kosong atau berisi elemen
// FS     : Data dalam jadwal kereta ditampilkan di layar

ListUser BalikListUser(ListUser L);
// Tujuan : Membalik urutan elemen dalam list user
// IS     : List mungkin kosong atau berisi elemen
// FS     : Elemen dalam list user dibalik

ListPayment BalikListPayment(ListPayment L);
// Tujuan : Membalik urutan elemen dalam list payment
// IS     : List mungkin kosong atau berisi elemen
// FS     : Elemen dalam list payment dibalik

ListKereta BalikListKereta(ListKereta L);
// Tujuan : Membalik urutan elemen dalam list kereta
// IS     : List mungkin kosong atau berisi elemen
// FS     : Elemen dalam list kereta dibalik

ListStasiun BalikListStasiun(ListStasiun L);
// Tujuan : Membalik urutan elemen dalam list stasiun
// IS     : List mungkin kosong atau berisi elemen
// FS     : Elemen dalam list stasiun dibalik

JadwalKereta BalikJadwalKereta(JadwalKereta J);
// Tujuan : Membalik urutan elemen dalam jadwal kereta
// IS     : Jadwal mungkin kosong atau berisi elemen
// FS     : Elemen dalam jadwal kereta dibalik

#endif
