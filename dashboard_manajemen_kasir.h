/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/
#ifndef DASHBOARD_MANAJEMEN_KASIR_H
#define DASHBOARD_MANAJEMEN_KASIR_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "databases.h"
#include "implementasi_akun_user.h"
#include "hash_password.h"

// Fungsi untuk menampilkan dashboard manajemen kasir
void TampilkanDashboardManajemenKasir(const char* email);
/* Tujuan : Menampilkan dashboard manajemen akun kasir */
/* IS      : email terdefinisi */
/* FS      : Dashboard manajemen akun kasir ditampilkan */

// Fungsi untuk menampilkan form tambah kasir
void TampilkanFormTambahKasir(const char* email, HashPassword* morseTree);
/* Tujuan : Menampilkan form untuk menambah akun kasir */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Form tambah akun kasir ditampilkan */

// Fungsi untuk menampilkan form edit kasir
void TampilkanFormEditKasir(const char* email, HashPassword* morseTree);
/* Tujuan : Menampilkan form untuk mengedit akun kasir */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Form edit akun kasir ditampilkan */

// Fungsi untuk mengedit akun kasir
void EditKasirAccount(const char* kasirEmail, HashPassword* morseTree);
/* Tujuan : Mengedit data akun kasir */
/* IS      : kasirEmail dan morseTree terdefinisi */
/* FS      : Data akun kasir diperbarui */

// Fungsi untuk menampilkan form hapus kasir
void TampilkanFormHapusKasir(const char* email);
/* Tujuan : Menampilkan form untuk menghapus akun kasir */
/* IS      : email terdefinisi */
/* FS      : Form hapus akun kasir ditampilkan */

// Fungsi utama untuk manajemen kasir
void JalankanDashboardManajemenKasir(const char* email, HashPassword* morseTree);
/* Tujuan : Menjalankan menu manajemen akun kasir secara berulang */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Menu manajemen akun kasir aktif hingga user memilih kembali */

#endif /* DASHBOARD_MANAJEMEN_KASIR_H */ 
