/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_MACHINE_H
#define DASHBOARD_MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "clear.h"

// *** PROTOTYPE FUNGSI DASHBOARD MACHINE ***

// *** TAMPILAN DASHBOARD ***
void ShowMachineDashboard(const char* email);
/* Tujuan : Menampilkan dashboard untuk mesin */
/* IS      : email terdefinisi */
/* FS      : Dashboard mesin ditampilkan */

// *** MENU MESIN ***
void ShowTicketPrintingMenu(const char* email);
/* Tujuan : Menampilkan menu cetak tiket */
/* IS      : email terdefinisi */
/* FS      : Menu cetak tiket ditampilkan */

void ShowTicketScanningMenu(const char* email);
/* Tujuan : Menampilkan menu pemindaian tiket */
/* IS      : email terdefinisi */
/* FS      : Menu pemindaian tiket ditampilkan */

void ShowMachineStatusMenu(const char* email);
/* Tujuan : Menampilkan menu status mesin */
/* IS      : email terdefinisi */
/* FS      : Menu status mesin ditampilkan */

// *** FUNGSI UTAMA ***
void RunMachineDashboard(const char* email);
/* Tujuan : Menjalankan dashboard mesin */
/* IS      : email terdefinisi */
/* FS      : Dashboard mesin berjalan dan menampilkan menu-menu mesin */

#endif /* DASHBOARD_MACHINE_H */ 