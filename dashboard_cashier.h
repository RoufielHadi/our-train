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

// *** PROTOTYPE FUNGSI DASHBOARD CASHIER ***

// *** TAMPILAN DASHBOARD ***
void ShowCashierDashboard(const char* email);
/* Tujuan : Menampilkan dashboard untuk kasir */
/* IS      : email terdefinisi */
/* FS      : Dashboard kasir ditampilkan */

// *** MENU KASIR ***
void ShowTicketSalesMenu(const char* email);
/* Tujuan : Menampilkan menu penjualan tiket */
/* IS      : email terdefinisi */
/* FS      : Menu penjualan tiket ditampilkan */

void ShowTicketVerificationMenu(const char* email);
/* Tujuan : Menampilkan menu verifikasi tiket */
/* IS      : email terdefinisi */
/* FS      : Menu verifikasi tiket ditampilkan */

void ShowSalesReportMenu(const char* email);
/* Tujuan : Menampilkan menu laporan penjualan */
/* IS      : email terdefinisi */
/* FS      : Menu laporan penjualan ditampilkan */

// *** FUNGSI UTAMA ***
void RunCashierDashboard(const char* email);
/* Tujuan : Menjalankan dashboard kasir */
/* IS      : email terdefinisi */
/* FS      : Dashboard kasir berjalan dan menampilkan menu-menu kasir */

#endif /* DASHBOARD_CASHIER_H */ 