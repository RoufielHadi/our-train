/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_MANAJEMEN_RUTE_H
#define DASHBOARD_MANAJEMEN_RUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clear.h"
#include "boolean.h"
#include "implementasi_rute_kereta.h"

// Helper untuk perbandingan case-insensitive
int equalsIgnoreCase(const char* a, const char* b);
// Tujuan : Membandingkan dua string tanpa memperhatikan case
// IS      : a dan b terdefinisi
// FS      : Return 1 jika sama (case-insensitive), 0 jika berbeda

// Fungsi untuk mengganti nama stasiun di file rute_kereta.txt
void RenameStationInFile(const char* oldName, const char* newName);
// Tujuan : Mengganti nama stasiun di file rute_kereta.txt
// IS      : oldName dan newName terdefinisi
// FS      : Nama stasiun oldName diganti menjadi newName di file

// Fungsi untuk mengubah status stasiun di file rute_kereta.txt
void EditStatusStationInFile(const char* name, boolean status);
// Tujuan : Mengubah status stasiun di file rute_kereta.txt
// IS      : name dan status terdefinisi
// FS      : Status stasiun dengan nama name diubah menjadi status

// Menu Manajemen Rute untuk Admin
void MenuManajemenRuteAdmin(const char* email);
// Tujuan : Menampilkan menu manajemen rute untuk admin
// IS      : email terdefinisi
// FS      : Menu manajemen rute untuk admin selesai dijalankan

// Menu Manajemen Rute untuk User
void MenuManajemenRuteUser(const char* email);
// Tujuan : Menampilkan menu manajemen rute untuk user
// IS      : email terdefinisi
// FS      : Menu manajemen rute untuk user selesai dijalankan

#endif /* DASHBOARD_MANAJEMEN_RUTE_H */