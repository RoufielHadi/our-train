/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_CASHIER_H
#define DASHBOARD_CASHIER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "clear.h"

// Helper function to extract station name from cashier email
void ExtractStationNameFromEmail(const char* email, char* station);
/* Tujuan : Mengekstrak nama stasiun dari email kasir */
/* IS      : email terdefinisi (contoh: cashier.bandung@ourtrain.id) */
/* FS      : station diisi dengan nama stasiun (contoh: Bandung) */

// *** TAMPILAN DASHBOARD ***
void ShowCashierDashboard(const char* email);
/* Tujuan : Menampilkan dashboard untuk kasir */
/* IS      : email terdefinisi */
/* FS      : Dashboard kasir ditampilkan */

// *** MENU KASIR ***
void ShowCallNextQueueMenu(const char* email);
/* Tujuan : Memanggil nomor antrian berikutnya */
/* IS      : email terdefinisi */
/* FS      : Nomor antrian berikutnya dipanggil */

void ShowSkipQueueMenu(const char* email);
/* Tujuan : Melewati nomor antrian saat ini */
/* IS      : email terdefinisi */
/* FS      : Nomor antrian saat ini dilewati */

void ShowQueueStatusMenu(const char* email);
/* Tujuan : Menampilkan status antrian */
/* IS      : email terdefinisi */
/* FS      : Status antrian ditampilkan */

// *** FUNGSI UTAMA ***
void RunCashierDashboard(const char* email);
/* Tujuan : Menjalankan dashboard kasir */
/* IS      : email terdefinisi */
/* FS      : Dashboard kasir berjalan dan menampilkan menu-menu kasir */

#endif /* DASHBOARD_CASHIER_H */ 