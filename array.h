/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boolean.h"

// Konstanta untuk ukuran maksimum kursi kereta
#define MAX_KOLOM 5 // Maksimum kolom (kursi ke samping)
#define MAX_BARIS 20 // Maksimum baris (kursi ke belakang)
#define MAX_GERBONG 10 // Maksimum jumlah gerbong per kereta
#define MAX_KERETA 50 // Maksimum jumlah kereta yang dapat disimpan

// Definisi jenis-jenis kereta
typedef enum {
    EKONOMI,
    EKONOMI_PREMIUM,
    BISNIS,
    EKSEKUTIF,
    LUXURY,
    PRIORITY,
    SLEEPER,
    COMPARTMENT
} JenisKereta;

// Konfigurasi ukuran kursi untuk setiap jenis kereta
typedef struct {
    int kolom;
    int baris;
} KonfigurasiKursi;

// Struktur data untuk menyimpan informasi kursi kereta
typedef struct {
    int nomor_gerbong;
    boolean status_kursi[MAX_KOLOM][MAX_BARIS]; // TRUE jika kursi terisi, FALSE jika kosong
} FormatKursi;

// Struktur data untuk menyimpan informasi kereta dan kursinya
typedef struct KursiKereta {
    char id_kereta[10];
    JenisKereta jenis;
    FormatKursi data_kursi[MAX_GERBONG];
    int jumlah_gerbong;
    struct KursiKereta* next; // Untuk implementasi linked list jika diperlukan
} KursiKereta;

// Definisi array untuk menyimpan data kereta
typedef struct {
    KursiKereta data[MAX_KERETA];
    int jumlah_kereta;
} ArrayKereta;

// *** PROTOTYPE FUNGSI ***

// KONSTRUKTOR
void InisialisasiArrayKereta(ArrayKereta *arr);
// Tujuan  : Menginisialisasi array kereta agar siap digunakan
// IS      : Array belum terisi
// FS      : Array memiliki jumlah_kereta = 0, siap digunakan

// OPERASI DASAR
void TambahKereta(ArrayKereta *arr, char *id_kereta, JenisKereta jenis, int jumlah_gerbong);
// Tujuan  : Menambahkan kereta baru dengan konfigurasi sesuai jenisnya
// IS      : Array mungkin kosong atau berisi beberapa kereta
// FS      : Kereta baru ditambahkan ke dalam array jika belum penuh

void HapusKereta(ArrayKereta *arr, int index);
// Tujuan  : Menghapus kereta dari array berdasarkan indeks
// IS      : Array tidak kosong
// FS      : Kereta di indeks tertentu dihapus, elemen setelahnya digeser ke kiri

int CariKeretaById(ArrayKereta *arr, char *id_kereta);
// Tujuan  : Mencari kereta dalam array berdasarkan ID
// IS      : Array tidak kosong
// FS      : Mengembalikan indeks kereta jika ditemukan, -1 jika tidak

void TampilkanDaftarKereta(ArrayKereta arr);
// Tujuan  : Menampilkan daftar kereta beserta jenis dan jumlah gerbongnya
// IS      : Array mungkin kosong atau berisi beberapa kereta
// FS      : Seluruh data kereta ditampilkan ke layar

// OPERASI KURSI
void InisialisasiKursiKereta(KursiKereta *kereta);
// Tujuan  : Menginisialisasi seluruh kursi kereta sebagai kosong
// IS      : Kereta sudah memiliki jenis dan jumlah gerbong yang valid
// FS      : Seluruh kursi dalam kereta ditandai sebagai kosong (FALSE)

boolean ReservasiKursi(KursiKereta *kereta, int gerbong, int baris, int kolom);
// Tujuan  : Mereservasi kursi pada gerbong, baris, dan kolom tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika kursi berhasil direservasi, FALSE jika gagal

boolean BatalkanReservasi(KursiKereta *kereta, int gerbong, int baris, int kolom);
// Tujuan  : Membatalkan reservasi kursi pada gerbong, baris, dan kolom tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika pembatalan berhasil, FALSE jika gagal

boolean CekStatusKursi(KursiKereta kereta, int gerbong, int baris, int kolom);
// Tujuan  : Mengecek status kursi (terisi atau kosong)
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan status kursi (TRUE jika terisi, FALSE jika kosong)

void TampilkanKursiGerbong(KursiKereta kereta, int gerbong);
// Tujuan  : Menampilkan visualisasi kursi untuk gerbong tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Tampilan visual kursi ditampilkan ke layar

// UTILITAS
KonfigurasiKursi GetKonfigurasiKursiByJenis(JenisKereta jenis);
// Tujuan  : Mendapatkan konfigurasi kursi berdasarkan jenis kereta
// IS      : Jenis kereta valid
// FS      : Mengembalikan struktur KonfigurasiKursi dengan kolom dan baris sesuai jenis

const char* GetNamaJenisKereta(JenisKereta jenis);
// Tujuan  : Mendapatkan nama jenis kereta dalam bentuk string
// IS      : Jenis kereta valid
// FS      : Mengembalikan string yang berisi nama jenis kereta

int HitungJumlahKursiKereta(KursiKereta kereta);
// Tujuan  : Menghitung total jumlah kursi dalam kereta
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan jumlah total kursi

int HitungJumlahKursiTerisi(KursiKereta kereta);
// Tujuan  : Menghitung jumlah kursi yang sudah terisi
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan jumlah kursi yang terisi

float HitungPersentaseKursiTerisi(KursiKereta kereta);
// Tujuan  : Menghitung persentase kursi yang sudah terisi
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan persentase kursi terisi (0-100)

#endif /* ARRAY_H */

