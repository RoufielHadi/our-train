/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_REKENING_SAYA_H
#define DASHBOARD_REKENING_SAYA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "clear.h"
#include "linked.h"
#include "implementasi_akun_user.h"
#include "dashboard_authentication.h"

// *** TAMPILAN DASHBOARD REKENING SAYA ***
void ShowUserBankDashboard(const char* email);
/* Tujuan : Menampilkan dashboard rekening saya untuk user */
/* IS      : email terdefinisi */
/* FS      : Dashboard rekening saya ditampilkan */

// *** MENU REKENING SAYA ***
void ShowBankAccountInfo(const char* email);
/* Tujuan : Menampilkan informasi rekening user */
/* IS      : email terdefinisi */
/* FS      : Informasi rekening user ditampilkan */

boolean ChangeBankPIN(const char* email);
/* Tujuan : Mengubah PIN rekening user */
/* IS      : email terdefinisi */
/* FS      : PIN rekening user diubah, mengembalikan TRUE jika berhasil */

boolean TopUpBalance(const char* email);
/* Tujuan : Menambah saldo rekening user */
/* IS      : email terdefinisi */
/* FS      : Saldo rekening user bertambah, mengembalikan TRUE jika berhasil */

// *** FUNGSI UTAMA ***
void RunUserBankDashboard(const char* email);
/* Tujuan : Menjalankan dashboard rekening saya */
/* IS      : email terdefinisi */
/* FS      : Dashboard rekening saya berjalan dan menampilkan menu-menu rekening */

#endif /* DASHBOARD_REKENING_SAYA_H */ 