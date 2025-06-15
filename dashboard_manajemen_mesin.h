/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef DASHBOARD_MANAJEMEN_MESIN_H
#define DASHBOARD_MANAJEMEN_MESIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "databases.h"
#include "implementasi_akun_user.h"
#include "hash_password.h"

// Fungsi untuk menampilkan dashboard manajemen mesin
void TampilkanDashboardManajemenMesin(const char* email);
/* Tujuan : Menampilkan dashboard manajemen akun mesin */
/* IS      : email terdefinisi */
/* FS      : Dashboard manajemen akun mesin ditampilkan */

// Fungsi untuk menampilkan form tambah mesin
void TampilkanFormTambahMesin(const char* email, HashPassword* morseTree);
/* Tujuan : Menampilkan form untuk menambah akun mesin */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Form tambah akun mesin ditampilkan */

// Fungsi untuk menampilkan form edit mesin
void TampilkanFormEditMesin(const char* email, HashPassword* morseTree);
/* Tujuan : Menampilkan form untuk mengedit akun mesin */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Form edit akun mesin ditampilkan */

// Fungsi untuk mengedit akun mesin
void EditMesinAccount(const char* mesinEmail, HashPassword* morseTree);
/* Tujuan : Mengedit data akun mesin */
/* IS      : mesinEmail dan morseTree terdefinisi */
/* FS      : Data akun mesin diperbarui */

// Fungsi untuk menampilkan form hapus mesin
void TampilkanFormHapusMesin(const char* email);
/* Tujuan : Menampilkan form untuk menghapus akun mesin */
/* IS      : email terdefinisi */
/* FS      : Form hapus akun mesin ditampilkan */

// Fungsi utama untuk manajemen mesin
void JalankanDashboardManajemenMesin(const char* email, HashPassword* morseTree);
/* Tujuan : Menjalankan menu manajemen akun mesin secara berulang */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Menu manajemen akun mesin aktif hingga user memilih kembali */

#endif /* DASHBOARD_MANAJEMEN_MESIN_H */ 
