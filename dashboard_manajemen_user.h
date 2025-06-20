/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef DASHBOARD_MANAJEMEN_USER_H
#define DASHBOARD_MANAJEMEN_USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "boolean.h"
#include "databases.h"

// Forward declaration
typedef struct HashPassword HashPassword;

#include "implementasi_akun_user.h"
#include "hash_password.h"
#include "clear.h"

// Deklarasi variabel global eksternal
extern HashPassword* morseTree;

// Fungsi untuk mendekode hash morse menjadi plaintext
char* DecodeMorseHash(const char* hash);
/* Tujuan : Mengubah hash morse menjadi plaintext yang dapat dibaca */
/* IS      : hash terdefinisi */
/* FS      : Mengembalikan string plaintext hasil dekode */

// Fungsi untuk menampilkan dashboard manajemen user
void ShowUserManagementDashboard(const char* email);
/* Tujuan : Menampilkan dashboard manajemen akun user */
/* IS      : email terdefinisi */
/* FS      : Dashboard manajemen akun user ditampilkan */

// Fungsi untuk menampilkan daftar akun user
void ShowUserAccounts(const char* email);
/* Tujuan : Menampilkan seluruh akun user biasa */
/* IS      : email terdefinisi */
/* FS      : Jika ada akun user, menampilkan daftar; jika tidak, menampilkan pesan tidak ada data */

// Fungsi untuk menampilkan detail akun user
void ShowUserAccountDetail(const char* email, const char* userEmail);
/* Tujuan : Menampilkan detail informasi akun user dan rekening */
/* IS      : email terdefinisi, userEmail terdefinisi */
/* FS      : Detail informasi akun user dan rekening ditampilkan */

// Fungsi untuk melihat informasi user yang terdaftar
void ViewUserInformation(const char* email);
/* Tujuan : Menampilkan daftar email user dan memilih untuk melihat detail */
/* IS      : email terdefinisi */
/* FS      : Email user ditampilkan dan detail informasi ditampilkan jika dipilih */

// Fungsi untuk menghapus akun user
void DeleteUserAccount(const char* email);
/* Tujuan : Menghapus akun user terpilih berdasarkan email */
/* IS      : email terdefinisi */
/* FS      : Akun user dengan email yang dipilih dihapus dari database */

// Fungsi untuk menambahkan akun kasir dan mesin secara berpasangan
void TambahAkunKasirDanMesin(const char* email, HashPassword* morseTree);

// Fungsi baru untuk menghapus user berdasarkan pilihan indeks
void DeleteUserByIndex(const char* email);
/* Tujuan : Menampilkan daftar email user dan menghapus yang dipilih */
/* IS      : email terdefinisi */
/* FS      : User yang dipilih dihapus setelah konfirmasi */

// Fungsi untuk melihat informasi akun kasir
void ViewKasirAccounts(const char* email);

// Fungsi untuk melihat informasi akun mesin
void ViewMesinAccounts(const char* email);

// Fungsi untuk melihat informasi akun admin
void ViewAdminAccounts(const char* email);

// Tambahkan stub untuk edit akun kasir dan mesin
void TampilkanFormEditKasir(const char* email, HashPassword* morseTree);
void TampilkanFormEditMesin(const char* email, HashPassword* morseTree);

// Tambahkan stub untuk delete akun kasir dan mesin
void TampilkanFormHapusKasir(const char* email);
void TampilkanFormHapusMesin(const char* email);

// Fungsi utama untuk manajemen user
void RunUserManagementDashboard(const char* email);
/* Tujuan : Menjalankan menu manajemen akun user secara berulang */
/* IS      : email terdefinisi */
/* FS      : Menampilkan menu sampai user memilih kembali */

#endif /* DASHBOARD_MANAJEMEN_USER_H */
