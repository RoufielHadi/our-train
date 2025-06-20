/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef DASHBOARD_MANAJEMEN_KERETA_H
#define DASHBOARD_MANAJEMEN_KERETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "clear.h"
#include "array.h"
#include "implementasi_informasi_kereta.h"
#include "databases.h"
#include "dashboard_manajemen_jadwal.h"
#include "implementasi_jadwal_kereta.h"

// Konstanta untuk jenis layanan
#define STR_EKONOMI "Ekonomi"
#define STR_BISNIS "Bisnis"
#define STR_EKSEKUTIF "Eksekutif"
#define STR_LUXURY "Luxury"

// Fungsi validasi menggunakan implementasi dari implementasi_informasi_kereta.h
/* Fungsi ValidasiIDKereta sudah diimplementasikan di implementasi_informasi_kereta.h */
/* Fungsi ValidasiJenisLayanan sudah diimplementasikan di implementasi_informasi_kereta.h */

void DashboardTampilkanDaftarKereta();
/* Tujuan : Menampilkan daftar kereta yang tersedia di sistem */
/* IS      : tidak ada */
/* FS      : Daftar kereta ditampilkan di layar */

void DashboardTambahKereta();
/* Tujuan : Menampilkan form untuk menambah kereta baru */
/* IS      : tidak ada */
/* FS      : Form input kereta baru ditampilkan */

void DashboardEditKereta();
/* Tujuan : Menampilkan form untuk mengedit data kereta */
/* IS      : tidak ada */
/* FS      : Form edit data kereta ditampilkan */

void DashboardHapusKereta();
/* Tujuan : Menampilkan konfirmasi dan menghapus kereta terpilih */
/* IS      : tidak ada */
/* FS      : Kereta terhapus dari database jika dikonfirmasi */

void TampilkanDaftarKeretaUI(void);
/* Tujuan : Menampilkan daftar kereta (wrapper) */
/* IS      : tidak ada */
/* FS      : Panggilan ke DashboardTampilkanDaftarKereta dilaksanakan */

void TampilkanFormTambahKereta();
/* Tujuan : Menampilkan form tambah kereta (wrapper) */
/* IS      : tidak ada */
/* FS      : Panggilan ke DashboardTambahKereta dilaksanakan */

void TampilkanFormEditKereta();
/* Tujuan : Menampilkan form edit kereta (wrapper) */
/* IS      : tidak ada */
/* FS      : Panggilan ke DashboardEditKereta dilaksanakan */

void TampilkanFormHapusKereta();
/* Tujuan : Menampilkan form hapus kereta (wrapper) */
/* IS      : tidak ada */
/* FS      : Panggilan ke DashboardHapusKereta dilaksanakan */

void MenuManajemenKereta(const char* email);
/* Tujuan : Menjalankan menu manajemen kereta */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen kereta ditampilkan berulang */

#endif
