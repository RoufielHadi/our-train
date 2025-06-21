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
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

// Important: include this before other custom headers
#include "boolean.h"
#include "tree_non_biner.h"
#include "clear.h"
#include "implementasi_jadwal_kereta.h"
#include "implementasi_rute_kereta.h"
#include "linked.h"
#include "queue.h"

// Helper: normalize station name to Title Case
void NormalizeName(char *s);
/* Tujuan : Mengubah nama stasiun ke format Title Case */
/* IS      : s terdefinisi */
/* FS      : s dikonversi ke format Title Case */

void TampilkanDetailJadwal(int index);
/* Tujuan : Menampilkan detail jadwal berdasarkan index */
/* IS      : index terdefinisi */
/* FS      : Detail jadwal ditampilkan */

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


void TambahJadwalKereta(const char* idKereta);
/* Tujuan : Menambahkan jadwal untuk kereta tertentu */
/* IS      : idKereta terdefinisi */
/* FS      : Form input jadwal kereta ditampilkan dengan ID yang sudah terisi */


void EditJadwal();
/* Tujuan : Menampilkan form edit jadwal kereta */
/* IS      : tidak ada */
/* FS      : Form edit jadwal kereta ditampilkan */


void DashboardHapusJadwal();
/* Tujuan : Menampilkan form konfirmasi hapus jadwal kereta */
/* IS      : tidak ada */
/* FS      : Form konfirmasi hapus jadwal kereta ditampilkan */

void BacaDataStasiun(Isi_Tree tree);
/* Tujuan : Membaca data stasiun dari file ke struktur tree */
/* IS      : tree terdefinisi */
/* FS      : tree terisi dengan data stasiun dari file */

int GetPathToRoot(Isi_Tree tree, int stationIdx, int path[], int maxPath);
/* Tujuan : Mendapatkan jalur dari stasiun ke root tree */
/* IS      : tree, stationIdx, path, maxPath terdefinisi */
/* FS      : path terisi dengan indeks jalur dari stationIdx ke root, mengembalikan jumlah node di jalur */

int GetRouteStations(const char *origin, const char *destination, char routeNames[][50], int maxStations);
/* Tujuan : Mendapatkan rute lengkap antara dua stasiun */
/* IS      : origin, destination, routeNames, maxStations terdefinisi */
/* FS      : routeNames terisi dengan nama-nama stasiun di rute, mengembalikan jumlah stasiun di rute */

void AddDirectConnection(Isi_Tree tree, int idx1, int idx2);
/* Tujuan : Menambahkan koneksi langsung antara dua stasiun */
/* IS      : tree, idx1, idx2 terdefinisi */
/* FS      : Koneksi antara stasiun dengan indeks idx1 dan idx2 dibuat di tree */

#endif // DASHBOARD_MANAJEMEN_JADWAL_H
