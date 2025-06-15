/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef DASHBOARD_MANAJEMEN_JADWAL_H
#define DASHBOARD_MANAJEMEN_JADWAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "clear.h"


void MenuManajemenJadwal(const char* email);
/* Tujuan : Menampilkan menu manajemen jadwal kereta */
/* IS      : email terdefinisi */
/* FS      : Menu manajemen jadwal ditampilkan */


void TampilkanDaftarJadwal();
/* Tujuan : Menampilkan daftar semua jadwal kereta */
/* IS      : tidak ada */
/* FS      : Semua jadwal kereta ditampilkan */


void TambahJadwal();
/* Tujuan : Menampilkan form tambah jadwal kereta */
/* IS      : tidak ada */
/* FS      : Form input jadwal kereta ditampilkan */


void EditJadwal();
/* Tujuan : Menampilkan form edit jadwal kereta */
/* IS      : tidak ada */
/* FS      : Form edit jadwal kereta ditampilkan */


void DashboardHapusJadwal();
/* Tujuan : Menampilkan form konfirmasi hapus jadwal kereta */

#endif // DASHBOARD_MANAJEMEN_JADWAL_H
