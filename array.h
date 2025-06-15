/*
Author: Devi Maulani
NIM: 241524007
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
#define MAX_SEGMEN 10 // Maksimum jumlah segmen perjalanan
#define MAX_NAMA_SEGMEN 50 // Panjang maksimum nama segmen

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

// Struktur untuk menyimpan informasi segmen
typedef struct {
    char nama[MAX_NAMA_SEGMEN]; // Contoh: "Padalarang-Cimahi"
} InfoSegmen;

// Struktur data untuk menyimpan informasi kursi kereta
typedef struct {
    int nomor_gerbong;
    boolean status_kursi[MAX_KOLOM][MAX_BARIS][MAX_SEGMEN]; // TRUE jika kursi terisi pada segmen tertentu
} FormatKursi;

// Struktur data untuk menyimpan informasi kereta dan kursinya
typedef struct KursiKereta {
    char id_kereta[10]; // ID kereta untuk referensi ke informasi umum
    FormatKursi data_kursi[MAX_GERBONG];
    int jumlah_gerbong;
    InfoSegmen segmen[MAX_SEGMEN]; // Informasi segmen-segmen perjalanan
    int jumlah_segmen; // Jumlah segmen perjalanan
    char tanggal[11]; // Format YYYY-MM-DD
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
void TambahKereta(ArrayKereta *arr, char *id_kereta, int jumlah_gerbong, char *tanggal, InfoSegmen *segmen_list, int jumlah_segmen);
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
void InisialisasiKursiKereta(KursiKereta *kereta, JenisKereta jenis);
// Tujuan  : Menginisialisasi seluruh kursi kereta sebagai kosong
// IS      : Kereta sudah memiliki jumlah gerbong yang valid
// FS      : Seluruh kursi dalam kereta ditandai sebagai kosong (FALSE)

boolean ReservasiKursi(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_idx);
// Tujuan  : Mereservasi kursi pada gerbong, baris, kolom, dan segmen tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika kursi berhasil direservasi, FALSE jika gagal

boolean ReservasiKursiMultiSegmen(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_awal, int segmen_akhir);
// Tujuan  : Mereservasi kursi untuk beberapa segmen sekaligus
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika kursi berhasil direservasi, FALSE jika gagal

boolean BatalkanReservasi(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_idx);
// Tujuan  : Membatalkan reservasi kursi pada gerbong, baris, kolom, dan segmen tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika pembatalan berhasil, FALSE jika gagal

boolean BatalkanReservasiMultiSegmen(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_awal, int segmen_akhir);
// Tujuan  : Membatalkan reservasi kursi untuk beberapa segmen sekaligus
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika pembatalan berhasil, FALSE jika gagal

boolean CekStatusKursi(KursiKereta kereta, int gerbong, int baris, int kolom, int segmen_idx);
// Tujuan  : Mengecek status kursi (terisi atau kosong) pada segmen tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan status kursi (TRUE jika terisi, FALSE jika kosong)

void TampilkanKursiGerbong(KursiKereta kereta, int gerbong, int segmen_idx, JenisKereta jenis);
// Tujuan  : Menampilkan visualisasi kursi untuk gerbong tertentu pada segmen tertentu
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

JenisKereta GetJenisKeretaFromString(const char* jenis_str);
// Tujuan  : Mengkonversi string jenis kereta ke enum JenisKereta
// IS      : jenis_str adalah string yang valid
// FS      : Mengembalikan enum JenisKereta yang sesuai dengan string

int HitungJumlahKursiKereta(KursiKereta kereta, JenisKereta jenis);
// Tujuan  : Menghitung total jumlah kursi dalam kereta
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan jumlah total kursi

int HitungJumlahKursiTerisiSegmen(KursiKereta kereta, int segmen_idx);
// Tujuan  : Menghitung jumlah kursi yang sudah terisi pada segmen tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan jumlah kursi yang terisi pada segmen tersebut

float HitungPersentaseKursiTerisiSegmen(KursiKereta kereta, int segmen_idx, JenisKereta jenis);
// Tujuan  : Menghitung persentase kursi yang sudah terisi pada segmen tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan persentase kursi terisi (0-100) pada segmen tersebut

int CariIndexSegmen(KursiKereta kereta, const char *nama_segmen);
// Tujuan  : Mencari index segmen berdasarkan namanya
// IS      : Kereta sudah memiliki data segmen
// FS      : Mengembalikan index segmen jika ditemukan, -1 jika tidak

#endif /* ARRAY_H */

