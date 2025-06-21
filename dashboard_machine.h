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

// Helper function to extract station name from machine email
void ExtractStationFromEmail(const char* email, char* station);
/* Tujuan : Mengekstrak nama stasiun dari email mesin */
/* IS      : email terdefinisi (contoh: machine.bandung@ourtrain.id) */
/* FS      : station diisi dengan nama stasiun (contoh: Bandung) */

// *** TAMPILAN DASHBOARD ***
void ShowMachineDashboard(const char* email);
/* Tujuan : Menampilkan dashboard untuk mesin */
/* IS      : email terdefinisi */
/* FS      : Dashboard mesin ditampilkan */

// *** MENU MESIN ***
void TakeQueueNumber(const char* email);
/* Tujuan : Mengambil nomor antrian baru */
/* IS      : email terdefinisi */
/* FS      : Nomor antrian baru diambil dan disimpan */

void ShowTicketScanningMenu(const char* email);
/* Tujuan : Menampilkan menu pemindaian tiket */
/* IS      : email terdefinisi */
/* FS      : Menu pemindaian tiket ditampilkan dan tiket dalam 24 jam ditampilkan */

void ShowTrainsForTodayMenu(const char* email);
/* Tujuan : Menampilkan jadwal kereta hari ini */
/* IS      : email terdefinisi */
/* FS      : Jadwal kereta hari ini ditampilkan */

// *** FUNGSI UTAMA ***
void RunMachineDashboard(const char* email);
/* Tujuan : Menjalankan dashboard mesin */
/* IS      : email terdefinisi */
/* FS      : Dashboard mesin berjalan dan menampilkan menu-menu mesin */

#endif /* DASHBOARD_MACHINE_H */ 