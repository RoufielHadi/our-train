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

// *** PROTOTYPE FUNGSI DASHBOARD ADMIN ***

// *** TAMPILAN DASHBOARD ***
void ShowAdminDashboard(const char* email);
/* Tujuan : Menampilkan dashboard untuk admin */
/* IS      : email terdefinisi */
/* FS      : Dashboard admin ditampilkan */

// *** MENU ADMIN ***
void ShowUserManagementMenu(const char* email);
/* Tujuan : Menampilkan menu manajemen user */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen user ditampilkan */

void ShowTrainManagementMenu(const char* email);
/* Tujuan : Menampilkan menu manajemen kereta */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen kereta ditampilkan */

void ShowScheduleManagementMenu(const char* email);
/* Tujuan : Menampilkan menu manajemen jadwal */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen jadwal ditampilkan */

void ShowRouteManagementMenu(const char* email);
/* Tujuan : Menampilkan menu manajemen rute */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen rute ditampilkan */

// *** FUNGSI UTAMA ***
void RunAdminDashboard(const char* email);
/* Tujuan : Menjalankan dashboard admin */
/* IS      : email terdefinisi */
/* FS      : Dashboard admin berjalan dan menampilkan menu-menu admin */

#endif /* DASHBOARD_ADMIN_H */ 