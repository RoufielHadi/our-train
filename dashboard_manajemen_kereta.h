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

// Fungsi-fungsi implementasi untuk dashboard
void DashboardTampilkanDaftarKereta();
void DashboardTambahKereta();
void DashboardEditKereta();
void DashboardHapusKereta();

// Fungsi-fungsi wrapper
void ShowDaftarKereta();
void ShowTambahKereta();
void ShowEditKereta();
void ShowHapusKereta();

// Fungsi utama menu manajemen kereta
void ShowKeretaManagementMenu(const char* email);

#endif /* DASHBOARD_MANAJEMEN_KERETA_H */
