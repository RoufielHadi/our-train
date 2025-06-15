/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_USER_H
#define DASHBOARD_USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "clear.h"
#include "linked.h" // This already contains the User struct definition

// External declaration for logoutFlag
extern boolean logoutFlag;

// *** PROTOTYPE FUNGSI DASHBOARD USER ***

// *** TAMPILAN DASHBOARD ***
void ShowUserDashboard(const char* email);
/* Tujuan : Menampilkan dashboard untuk user */
/* IS      : email terdefinisi */
/* FS      : Dashboard user ditampilkan */

// *** MENU USER ***
void ShowUserProfileMenu(const char* email);
/* Tujuan : Menampilkan menu profil user */
/* IS      : email terdefinisi */
/* FS      : Menu profil user ditampilkan */

void ShowUserTicketMenu(const char* email);
/* Tujuan : Menampilkan menu tiket user */
/* IS      : email terdefinisi */
/* FS      : Menu tiket user ditampilkan */

void ShowUserHistoryMenu(const char* email);
/* Tujuan : Menampilkan menu riwayat pembelian user */
/* IS      : email terdefinisi */
/* FS      : Menu riwayat pembelian user ditampilkan */

void ShowUserPaymentMenu(const char* email);
/* Tujuan : Menampilkan menu pembayaran user */
/* IS      : email terdefinisi */
/* FS      : Menu pembayaran user ditampilkan */

void ShowTicketPurchaseMenu(const char* email);
/* Tujuan : Menampilkan menu pembelian tiket */
/* IS      : email terdefinisi */
/* FS      : Menu pembelian tiket ditampilkan */

void ShowTrainScheduleMenu(const char* email);
/* Tujuan : Menampilkan menu jadwal kereta */
/* IS      : email terdefinisi */
/* FS      : Menu jadwal kereta ditampilkan */

// *** FUNGSI UTAMA ***
void RunUserDashboard(const char* email);
/* Tujuan : Menjalankan dashboard user */
/* IS      : email terdefinisi */
/* FS      : Dashboard user berjalan dan menampilkan menu-menu user */

#endif /* DASHBOARD_USER_H */ 