/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_ADMIN_H
#define DASHBOARD_ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "clear.h"
#include "hash_password.h"

// *** PROTOTYPE FUNGSI DASHBOARD ADMIN ***

// *** TAMPILAN DASHBOARD ***
void TampilkanDashboardAdmin(const char* email);
/* Tujuan : Menampilkan dashboard untuk admin */
/* IS      : email terdefinisi */
/* FS      : Dashboard admin ditampilkan */

// *** MENU ADMIN ***
void TampilkanMenuManajemenUser(const char* email);
/* Tujuan : Menampilkan menu manajemen user */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen user ditampilkan */

void TampilkanMenuManajemenKereta(const char* email);
/* Tujuan : Menampilkan menu manajemen kereta */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen kereta ditampilkan */

void TampilkanMenuManajemenJadwal(const char* email);
/* Tujuan : Menampilkan menu manajemen jadwal */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen jadwal ditampilkan */

void TampilkanMenuManajemenRute(const char* email);
/* Tujuan : Menampilkan menu manajemen rute */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen rute ditampilkan */

void TampilkanMenuRekapitulasiKeuntungan(const char* email);
/* Tujuan : Menampilkan menu rekapitulasi keuntungan */
/* IS      : email terdefinisi */
/* FS      : Menu rekapitulasi keuntungan ditampilkan */

// *** FUNGSI BARU UNTUK MANAJEMEN USER ***
void TampilkanMenuManajemenAkunUser(const char* email);
/* Tujuan : Menampilkan menu manajemen akun user */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen akun user ditampilkan */

void TampilkanMenuManajemenAkunKasir(const char* email, HashPassword* morseTree);
/* Tujuan : Menampilkan menu manajemen akun kasir */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Menu manajemen akun kasir ditampilkan */

void TampilkanMenuManajemenAkunMesin(const char* email, HashPassword* morseTree);
/* Tujuan : Menampilkan menu manajemen akun mesin */
/* IS      : email terdefinisi, morseTree terdefinisi */
/* FS      : Menu manajemen akun mesin ditampilkan */

// Tambahkan prototype untuk menu gabungan kereta dan jadwal
void TampilkanMenuManajemenKeretaDanJadwal(const char* email);
/* Tujuan : Menampilkan menu manajemen kereta dan jadwal */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen kereta dan jadwal ditampilkan */

// Prototipe fungsi pendukung untuk kereta dan jadwal
void LihatInformasiKereta(const char* email);
/* Tujuan : Menampilkan informasi kereta dari file informasi_umum.txt */
/* IS      : email terdefinisi */
/* FS      : Daftar kereta ditampilkan */

void LihatInformasiJadwal(const char* email);
/* Tujuan : Menampilkan informasi jadwal dari file jadwal_kereta.txt */
/* IS      : email terdefinisi */
/* FS      : Daftar jadwal ditampilkan */

void TambahKeretaDanJadwal(const char* email);
/* Tujuan : Menambahkan data kereta lalu jadwal */
/* IS      : email terdefinisi */
/* FS      : Data kereta dan jadwal disimpan ke file */

void EditKeretaAtauJadwal(const char* email);
/* Tujuan : Menampilkan menu edit kereta atau jadwal */
/* IS      : email terdefinisi */
/* FS      : Data kereta atau jadwal diperbarui */

void HapusKeretaAtauJadwal(const char* email);
/* Tujuan : Menampilkan menu hapus kereta atau jadwal */
/* IS      : email terdefinisi */
/* FS      : Data kereta atau jadwal dihapus */

// *** FUNGSI UTAMA ***
void JalankanDashboardAdmin(const char* email);
/* Tujuan : Menjalankan dashboard admin */
/* IS      : email terdefinisi */
/* FS      : Dashboard admin berjalan dan menampilkan menu-menu admin */

#endif /* DASHBOARD_ADMIN_H */ 