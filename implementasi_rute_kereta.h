/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_RUTE_KERETA_H
#define IMPLEMENTASI_RUTE_KERETA_H

#include "tree_non_biner.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk menyimpan informasi stasiun dengan status
typedef struct {
    char name[50];
    boolean active;
    int index;
} StationInfo;

// Struktur data untuk menyimpan informasi jarak antar stasiun dalam rute
typedef struct {
    char* stasiunAsal;
    char* stasiunTujuan;
    int jarak; // dalam kilometer
    int waktuTempuh; // dalam menit
} InfoRute;

// Struktur data untuk menyimpan informasi jalur kereta
typedef struct {
    char* namaJalur;
    Isi_Tree pohonRute;
    InfoRute* infoJarak;
    int jumlahRute;
} JalurKereta;

// *** PROTOTYPE FUNGSI IMPLEMENTASI RUTE KERETA ***

// *** OPERASI DASAR RUTE KERETA ***
void InisialisasiRuteKereta(Isi_Tree *pohonRute);
/* Tujuan : Menginisialisasi tree untuk rute kereta api di Pulau Jawa */
/* IS      : pohonRute belum terdefinisi */
/* FS      : pohonRute terdefinisi dengan struktur tree rute kereta api */

void InisialisasiJalurUtara(Isi_Tree *pohonRute);
/* Tujuan : Menginisialisasi tree untuk rute kereta api jalur utara di Pulau Jawa */
/* IS      : pohonRute belum terdefinisi */
/* FS      : pohonRute terdefinisi dengan struktur tree jalur utara */

void InisialisasiJalurSelatan(Isi_Tree *pohonRute);
/* Tujuan : Menginisialisasi tree untuk rute kereta api jalur selatan di Pulau Jawa */
/* IS      : pohonRute belum terdefinisi */
/* FS      : pohonRute terdefinisi dengan struktur tree jalur selatan */

void InisialisasiJalurTengah(Isi_Tree *pohonRute);
/* Tujuan : Menginisialisasi tree untuk rute kereta api jalur tengah di Pulau Jawa */
/* IS      : pohonRute belum terdefinisi */
/* FS      : pohonRute terdefinisi dengan struktur tree jalur tengah */

void InisialisasiJalurCabang(Isi_Tree *pohonRute);
/* Tujuan : Menginisialisasi tree untuk rute kereta api jalur cabang di Pulau Jawa */
/* IS      : pohonRute belum terdefinisi */
/* FS      : pohonRute terdefinisi dengan struktur tree jalur cabang */

// *** OPERASI PENCARIAN RUTE ***
boolean IsRuteTersedia(Isi_Tree pohonRute, const char* stasiunAsal, const char* stasiunTujuan);
/* Tujuan : Memeriksa apakah rute tersedia antara dua stasiun */
/* IS      : pohonRute sudah terdefinisi, stasiunAsal dan stasiunTujuan terdefinisi */
/* FS      : Mengembalikan true jika rute tersedia, false jika tidak */

int HitungJarak(InfoRute* infoJarak, int jumlahRute, const char* stasiunAsal, const char* stasiunTujuan);
/* Tujuan : Menghitung jarak antara dua stasiun */
/* IS      : infoJarak sudah terdefinisi, stasiunAsal dan stasiunTujuan terdefinisi */
/* FS      : Mengembalikan jarak dalam kilometer, -1 jika rute tidak ditemukan */

int HitungWaktuTempuh(InfoRute* infoJarak, int jumlahRute, const char* stasiunAsal, const char* stasiunTujuan);
/* Tujuan : Menghitung waktu tempuh antara dua stasiun */
/* IS      : infoJarak sudah terdefinisi, stasiunAsal dan stasiunTujuan terdefinisi */
/* FS      : Mengembalikan waktu tempuh dalam menit, -1 jika rute tidak ditemukan */

// *** OPERASI MANAJEMEN RUTE ***
void TambahStasiun(Isi_Tree *pohonRute, const char* namaStasiun, const char* stasiunInduk);
/* Tujuan : Menambahkan stasiun baru ke dalam tree rute */
/* IS      : pohonRute sudah terdefinisi, namaStasiun dan stasiunInduk terdefinisi */
/* FS      : Stasiun baru ditambahkan ke dalam tree rute */

void TambahInfoRute(InfoRute **infoJarak, int *jumlahRute, const char* stasiunAsal, const char* stasiunTujuan, int jarak, int waktuTempuh);
/* Tujuan : Menambahkan informasi rute baru */
/* IS      : infoJarak sudah terdefinisi, parameter rute terdefinisi */
/* FS      : Informasi rute baru ditambahkan ke array infoJarak */

void HapusStasiun(Isi_Tree *pohonRute, const char* namaStasiun);
/* Tujuan : Menghapus stasiun dari tree rute */
/* IS      : pohonRute sudah terdefinisi, namaStasiun terdefinisi */
/* FS      : Stasiun dihapus dari tree rute jika ditemukan */

// *** OPERASI VISUALISASI RUTE ***
void TampilkanRute(Isi_Tree pohonRute);
/* Tujuan : Menampilkan seluruh rute kereta api */
/* IS      : pohonRute sudah terdefinisi */
/* FS      : Seluruh rute kereta api ditampilkan ke layar */

void TampilkanStasiunTerdekat(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, const char* namaStasiun, int radius);
/* Tujuan : Menampilkan stasiun-stasiun terdekat dari suatu stasiun */
/* IS      : pohonRute dan infoJarak sudah terdefinisi, namaStasiun terdefinisi, radius dalam kilometer */
/* FS      : Stasiun-stasiun yang berada dalam radius tertentu dari stasiun yang ditentukan ditampilkan */

void TampilkanJalurTerpendek(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, const char* stasiunAsal, const char* stasiunTujuan);
/* Tujuan : Menampilkan jalur terpendek antara dua stasiun */
/* IS      : pohonRute dan infoJarak sudah terdefinisi, stasiunAsal dan stasiunTujuan terdefinisi */
/* FS      : Jalur terpendek antara dua stasiun ditampilkan ke layar */

// *** FUNGSI PEMBANTU ***
int CariIndeksStasiun(Isi_Tree pohonRute, const char* namaStasiun);
/* Tujuan : Mencari indeks stasiun dalam tree rute */
/* IS      : pohonRute sudah terdefinisi, namaStasiun terdefinisi */
/* FS      : Mengembalikan indeks stasiun, 0 jika tidak ditemukan */

char** DapatkanDaftarStasiun(Isi_Tree pohonRute, int *jumlahStasiun);
/* Tujuan : Mendapatkan daftar semua stasiun dalam tree rute */
/* IS      : pohonRute sudah terdefinisi */
/* FS      : Mengembalikan array berisi nama-nama stasiun dan mengisi jumlahStasiun */

void SimpanRuteKeFile(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, const char* namaFile);
/* Tujuan : Menyimpan data rute ke file */
/* IS      : pohonRute dan infoJarak sudah terdefinisi, namaFile terdefinisi */
/* FS      : Data rute tersimpan dalam file */

void BacaRuteDariFile(Isi_Tree *pohonRute, InfoRute** infoJarak, int *jumlahRute, const char* namaFile);
/* Tujuan : Membaca data rute dari file */
/* IS      : namaFile terdefinisi */
/* FS      : pohonRute dan infoJarak terisi dengan data dari file */

int InsertRuteNodeAndGetIndex(Isi_Tree *pohonRute, const char* namaStasiun, int parent_idx);
/* Tujuan : Menambahkan stasiun baru ke dalam tree rute dan mengembalikan indeksnya */
/* IS      : pohonRute sudah terdefinisi, namaStasiun dan parent_idx terdefinisi */
/* FS      : Stasiun baru ditambahkan ke dalam tree rute dan indeksnya dikembalikan */

void InsertRuteNode(Isi_Tree P, const char* info, int parent_idx);
/* Tujuan : Menambahkan node baru ke dalam tree */
/* IS      : P terdefinisi, info dan parent_idx terdefinisi */
/* FS      : Node baru ditambahkan ke dalam tree */

// *** FUNGSI YANG DIPINDAHKAN DARI DASHBOARD_MANAJEMEN_JADWAL.H ***

// Helper to check if a station index is active and get its name
boolean IsStationActiveAndName(int idx, char *outName);
/* Tujuan : Mengecek apakah stasiun aktif dan mengambil namanya */
/* IS      : idx terdefinisi */
/* FS      : outName diisi dengan nama stasiun jika aktif, return TRUE jika berhasil */

// Fungsi untuk mendapatkan daftar stasiun yang aktif di antara stasiun asal dan tujuan
int GetActiveStationsBetween(Isi_Tree tree, const char *origin, const char *destination, StationInfo *stations, int maxStations);
/* Tujuan : Mendapatkan daftar stasiun aktif di antara stasiun asal dan tujuan */
/* IS      : tree, origin, destination terdefinisi */
/* FS      : Mengisi stations dengan stasiun yang ditemukan, return jumlah stasiun */

// Fungsi untuk membaca data stasiun dari file ke struktur tree
void BacaDataStasiun(Isi_Tree tree);
/* Tujuan : Membaca data stasiun dari file rute_kereta.txt */
/* IS      : tree terdefinisi */
/* FS      : tree terisi dengan data stasiun dari file */

// Fungsi untuk mendapatkan jalur dari stasiun ke root
int GetPathToRoot(Isi_Tree tree, int stationIdx, int path[], int maxPath);
/* Tujuan : Mendapatkan jalur dari stasiun ke root */
/* IS      : tree, stationIdx terdefinisi */
/* FS      : path terisi dengan jalur, return panjang jalur */

// Fungsi untuk mendapatkan rute lengkap (termasuk origin & destination) antara dua stasiun
int GetRouteStations(const char *origin, const char *destination, char routeNames[][50], int maxStations);
/* Tujuan : Mendapatkan rute lengkap antara dua stasiun */
/* IS      : origin, destination terdefinisi */
/* FS      : routeNames terisi dengan nama stasiun, return jumlah stasiun dalam rute */

// Fungsi untuk menambahkan koneksi langsung antara dua stasiun
void AddDirectConnection(Isi_Tree tree, int idx1, int idx2);
/* Tujuan : Menambahkan koneksi langsung antara dua stasiun */
/* IS      : tree, idx1, idx2 terdefinisi */
/* FS      : Koneksi ditambahkan ke adjacency list */

#endif /* IMPLEMENTASI_RUTE_KERETA_H */ 