/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef IMPLEMENTASI_AKUN_USER_H
#define IMPLEMENTASI_AKUN_USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "linked.h"
#include "databases.h"

// Forward declaration
typedef struct HashPassword HashPassword;

// Tipe pengguna:
// 1 = Admin
// 2 = Kasir
// 3 = Mesin
// 4 = User biasa

// Fungsi untuk membuat akun baru
User BuatAkun(char* email, char* nama, char* alamat, char* nomor_telepon, char* password, int tipe_pengguna, HashPassword *morseTree);
/* Tujuan : Membuat User dengan data yang diberikan dan hash password */
/* IS      : semua parameter terdefinisi */
/* FS      : User baru dikembalikan dengan password ter-hash */

// Fungsi untuk menambahkan akun baru ke dalam list
boolean TambahAkun(ListUser *L, User user_baru);
/* Tujuan : Menambahkan User ke dalam linked list ListUser */
/* IS      : L pointer terdefinisi, user_baru berisi data */
/* FS      : Node baru ditambahkan di akhir list, TRUE jika berhasil */

// Fungsi untuk login
boolean Login(ListUser L, char* email, char* password, User* user_aktif, HashPassword *morseTree);
/* Tujuan : Memverifikasi kredensial dan mengatur user aktif */
/* IS      : L, email, password dan user_aktif pointer terdefinisi */
/* FS      : user_aktif diisi jika login berhasil, return TRUE/FALSE */

// Fungsi untuk mencari akun berdasarkan email
boolean CariAkun(ListUser L, char* email, User* hasil);
/* Tujuan : Mencari akun dalam ListUser berdasarkan email */
/* IS      : L dan email terdefinisi, hasil pointer valid */
/* FS      : hasil diisi jika ditemukan, return TRUE/FALSE */

// Fungsi untuk memperbarui informasi akun
boolean UpdateAkun(ListUser *L, char* email, User user_baru);
/* Tujuan : Mengubah data user kecuali email dan password */
/* IS      : L pointer terdefinisi, email dan user_baru terdefinisi */
/* FS      : Data pada node diperbarui, return TRUE jika berhasil */

// Fungsi untuk menghapus akun
boolean HapusAkun(ListUser *L, char* email);
/* Tujuan : Menghapus node User dari ListUser berdasarkan email */
/* IS      : L pointer terdefinisi, email terdefinisi */
/* FS      : Node dihapus, return TRUE jika berhasil */

// Fungsi untuk menghapus akun dari file (alias untuk HapusAkunUser)
boolean HapusAkunDariFile(char* email);

// Fungsi untuk menulis akun ke file
boolean TulisAkunUser(Record* record);

// Fungsi untuk menampilkan informasi akun
void TampilkanAkun(User user);

// Fungsi untuk menampilkan semua akun (hanya admin)
void TampilkanSemuaAkun(ListUser L);

// Fungsi untuk mengubah password
boolean UbahPassword(ListUser *L, char* email, char* password_lama, char* password_baru, HashPassword *morseTree);

// Fungsi untuk mengubah tipe pengguna (hanya admin)
boolean UbahTipePengguna(ListUser *L, char* email, int tipe_pengguna_baru);

// Fungsi untuk validasi email
boolean ValidasiEmail(char* email);

// Fungsi untuk validasi nomor telepon
boolean ValidasiNomorTelepon(char* nomor_telepon);

// Fungsi untuk validasi saldo
boolean ValidasiSaldo(const char* saldo_str);

// Fungsi untuk memformat nama ke Title Case
void FormatNama(char* nama);

// Fungsi untuk membuat akun kasir
User BuatAkunKasir(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree);

// Fungsi untuk menambahkan akun kasir
boolean TambahAkunKasir(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree);

// Fungsi untuk menampilkan semua akun kasir
void TampilkanSemuaAkunKasir(ListUser L);

// Fungsi untuk menghapus akun kasir berdasarkan email
boolean HapusAkunKasir(char* email);

// Fungsi untuk mengedit akun kasir berdasarkan email
boolean EditAkunKasir(char* email, char* nama, char* alamat, char* nomor_telepon, HashPassword *morseTree);

// Fungsi untuk membuat akun mesin
User BuatAkunMesin(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree);

// Fungsi untuk menambahkan akun mesin
boolean TambahAkunMesin(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree);

// Fungsi untuk menampilkan semua akun mesin
void TampilkanSemuaAkunMesin(ListUser L);

// Fungsi untuk menghapus akun mesin berdasarkan email
boolean HapusAkunMesin(char* email);

// Fungsi untuk mengedit akun mesin berdasarkan email
boolean EditAkunMesin(char* email, char* nama, char* alamat, char* nomor_telepon, HashPassword *morseTree);

#endif /* IMPLEMENTASI_AKUN_USER_H */ 