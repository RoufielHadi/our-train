/*
Author: Devi Maulani 
NIM: 241524007 
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef IMPLEMENTASI_TIKET_SAYA_H
#define IMPLEMENTASI_TIKET_SAYA_H

#include "boolean.h"
#include "linked.h"
#include "stack.h"
#include "implementasi_akun_user.h"

// Struktur data untuk menyimpan tiket user yang sedang login
typedef struct {
    StackRiwayat tiket_user;
} TiketSaya;

// Fungsi untuk menginisialisasi TiketSaya
void CreateTiketSaya(TiketSaya *T);
// Tujuan : Membuat struktur TiketSaya kosong
// IS     : T sembarang
// FS     : T terdefinisi dengan stack kosong

// Fungsi untuk mengambil semua tiket user yang sedang login
void AmbilTiketSaya(const char *filename, User user_aktif, TiketSaya *hasil);
// Tujuan : Mengambil semua tiket milik user dari file riwayat pemesanan
// IS     : filename dan user_aktif terdefinisi, hasil sembarang
// FS     : hasil berisi semua tiket milik user_aktif

// Fungsi untuk menampilkan semua tiket user yang sedang login
void TampilkanTiketSaya(TiketSaya T, User user_aktif);
// Tujuan : Menampilkan semua tiket milik user yang sedang login
// IS     : T dan user_aktif terdefinisi
// FS     : Informasi tiket ditampilkan ke layar

// Fungsi untuk menampilkan detail tiket berdasarkan indeks
boolean TampilkanDetailTiketSaya(TiketSaya T, User user_aktif, int indeks);
// Tujuan : Menampilkan detail tiket pada indeks tertentu
// IS     : T, user_aktif, dan indeks terdefinisi
// FS     : Detail tiket ditampilkan ke layar, mengembalikan TRUE jika berhasil

// Fungsi untuk dealokasi memori TiketSaya
void DealokasiTiketSaya(TiketSaya *T);
// Tujuan : Menghapus semua elemen dalam TiketSaya
// IS     : T terdefinisi
// FS     : Semua elemen dalam T dihapus

// Fungsi untuk menampilkan semua tiket pengguna
void LihatSemuaTiket(User user_aktif);
// Tujuan : Menampilkan semua tiket milik user yang sedang login
// IS     : user_aktif terdefinisi
// FS     : Informasi tiket ditampilkan ke layar

// Fungsi untuk melihat detail tiket berdasarkan indeks
void LihatDetailTiketByIndex(User user_aktif);
// Tujuan : Meminta indeks dan menampilkan detail tiket pada indeks tersebut
// IS     : user_aktif terdefinisi
// FS     : Detail tiket ditampilkan ke layar

#endif