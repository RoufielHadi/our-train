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
#include "tree_biner.h"

// Tipe pengguna:
// 1 = Admin
// 2 = Kasir
// 3 = Mesin
// 4 = User biasa

// Fungsi untuk membuat akun baru
User BuatAkun(char* email, char* nama, char* alamat, char* nomor_telepon, char* password, int tipe_pengguna, HashPassword *morseTree);

// Fungsi untuk menambahkan akun baru ke dalam list
boolean TambahAkun(ListUser *L, User user_baru);

// Fungsi untuk login
boolean Login(ListUser L, char* email, char* password, User* user_aktif, HashPassword *morseTree);

// Fungsi untuk mencari akun berdasarkan email
boolean CariAkun(ListUser L, char* email, User* hasil);

// Fungsi untuk memperbarui informasi akun
boolean UpdateAkun(ListUser *L, char* email, User user_baru);

// Fungsi untuk menghapus akun
boolean HapusAkun(ListUser *L, char* email);

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

#endif /* IMPLEMENTASI_AKUN_USER_H */ 