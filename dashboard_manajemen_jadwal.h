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

// Menampilkan menu manajemen jadwal
void ShowJadwalManagementMenu(const char* email);

// Fungsi-fungsi pendukung
void TampilkanDaftarJadwal();
void TambahJadwal();
void EditJadwal();
void HapusJadwalDashboard();

#endif // DASHBOARD_MANAJEMEN_JADWAL_H
