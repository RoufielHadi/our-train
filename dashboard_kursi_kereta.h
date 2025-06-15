/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_KURSI_KERETA_H
#define DASHBOARD_KURSI_KERETA_H

#include "implementasi_kursi_kereta.h"
#include "boolean.h"
#include "clear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// *** FUNGSI UTAMA DASHBOARD KURSI ***
void MenuKursiKereta(const char* id_kereta, const char* tanggal, int* nomor_gerbong_dipilih, char* kode_kursi_dipilih);
// Tujuan  : Menampilkan menu utama dashboard manajemen kursi kereta
// IS      : id_kereta dan tanggal terdefinisi
// FS      : User dapat memilih berbagai menu pengelolaan kursi kereta

// *** FUNGSI NAVIGASI MENU ***
void TampilkanHeaderMenu(const char* judul);
// Tujuan  : Menampilkan header menu dengan judul tertentu
// IS      : judul terdefinisi
// FS      : Header menu ditampilkan ke layar dengan judul di tengah header

void TampilkanFooterMenu();
// Tujuan  : Menampilkan footer menu
// IS      : -
// FS      : Footer menu ditampilkan ke layar

void TungguInput();
// Tujuan  : Menunggu input dari user untuk melanjutkan
// IS      : -
// FS      : Program berhenti hingga user menekan Enter

#endif /* DASHBOARD_KURSI_KERETA_H */
