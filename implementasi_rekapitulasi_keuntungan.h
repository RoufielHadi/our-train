/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_REKAPITULASI_KEUNTUNGAN_H
#define IMPLEMENTASI_REKAPITULASI_KEUNTUNGAN_H

#include "stack.h"
#include "linked.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struktur untuk menyimpan data harga tiket kereta
typedef struct {
    char id_kereta[10];
    char nama_kereta[100];
    int harga_ekonomi;
    int harga_ekonomi_premium;
    int harga_bisnis;
    int harga_eksekutif;
    int harga_luxury;
    int harga_priority;
    int harga_sleeper;
    int harga_compartment;
} HargaTiketKereta;

// Definisi array untuk menyimpan daftar harga tiket kereta
typedef struct {
    HargaTiketKereta data[100]; // Maksimal 100 kereta
    int jumlah;
} DaftarHargaTiket;

// Definisi struktur untuk menyimpan rekapitulasi keuntungan
typedef struct {
    int jumlah_tiket;
    long total_keuntungan;
    char kereta_terlaris[100];
    int jumlah_tiket_terlaris;
    struct Waktu periode_awal;
    struct Waktu periode_akhir;
} RekapitulasiKeuntungan;

// *** PROTOTYPE FUNGSI IMPLEMENTASI REKAPITULASI KEUNTUNGAN ***

// *** OPERASI DASAR DAFTAR HARGA ***
void InisialisasiDaftarHarga(DaftarHargaTiket *daftar);
/* Tujuan : Menginisialisasi daftar harga tiket kereta */
/* IS      : Daftar belum terdefinisi */
/* FS      : Daftar terdefinisi dengan jumlah = 0 */

void TambahHargaKereta(DaftarHargaTiket *daftar, char *id_kereta, char *nama_kereta, 
                      int harga_ekonomi, int harga_ekonomi_premium, int harga_bisnis, 
                      int harga_eksekutif, int harga_luxury, int harga_priority, 
                      int harga_sleeper, int harga_compartment);
/* Tujuan : Menambahkan data harga tiket untuk kereta baru */
/* IS      : Daftar harga terdefinisi */
/* FS      : Data harga tiket kereta baru ditambahkan ke daftar */

boolean UpdateHargaKereta(DaftarHargaTiket *daftar, char *id_kereta, 
                         int harga_ekonomi, int harga_ekonomi_premium, int harga_bisnis, 
                         int harga_eksekutif, int harga_luxury, int harga_priority, 
                         int harga_sleeper, int harga_compartment);
/* Tujuan : Memperbarui data harga tiket untuk kereta yang sudah ada */
/* IS      : Daftar harga terdefinisi */
/* FS      : Data harga tiket kereta diperbarui, mengembalikan TRUE jika berhasil */

boolean HapusHargaKereta(DaftarHargaTiket *daftar, char *id_kereta);
/* Tujuan : Menghapus data harga tiket untuk kereta tertentu */
/* IS      : Daftar harga terdefinisi */
/* FS      : Data harga tiket kereta dihapus, mengembalikan TRUE jika berhasil */

HargaTiketKereta* GetHargaKereta(DaftarHargaTiket daftar, char *id_kereta);
/* Tujuan : Mendapatkan data harga tiket untuk kereta tertentu */
/* IS      : Daftar harga terdefinisi */
/* FS      : Mengembalikan pointer ke data harga tiket jika ditemukan, NULL jika tidak */

// *** OPERASI FILE DAFTAR HARGA ***
void SaveDaftarHargaToFile(DaftarHargaTiket daftar, const char *filename);
/* Tujuan : Menyimpan daftar harga tiket ke dalam file */
/* IS      : Daftar harga terdefinisi */
/* FS      : Daftar harga tiket tersimpan dalam file */

void LoadDaftarHargaFromFile(DaftarHargaTiket *daftar, const char *filename);
/* Tujuan : Membaca daftar harga tiket dari file */
/* IS      : Daftar harga terdefinisi */
/* FS      : Daftar harga tiket diisi dengan data dari file */

// *** OPERASI PERHITUNGAN KEUNTUNGAN ***
int HitungHargaTiket(DaftarHargaTiket daftar, char *id_kereta, int jenis_kereta);
/* Tujuan : Menghitung harga tiket berdasarkan ID kereta dan jenis kereta */
/* IS      : Daftar harga terdefinisi */
/* FS      : Mengembalikan harga tiket, 0 jika data tidak ditemukan */

long HitungTotalKeuntungan(StackRiwayat riwayat, DaftarHargaTiket daftar);
/* Tujuan : Menghitung total keuntungan dari seluruh riwayat pembelian */
/* IS      : Stack riwayat dan daftar harga terdefinisi */
/* FS      : Mengembalikan total keuntungan dalam Rupiah */

long HitungKeuntunganPeriode(StackRiwayat riwayat, DaftarHargaTiket daftar, 
                           struct Waktu waktu_awal, struct Waktu waktu_akhir);
/* Tujuan : Menghitung keuntungan dalam periode tertentu */
/* IS      : Stack riwayat dan daftar harga terdefinisi */
/* FS      : Mengembalikan total keuntungan dalam periode dalam Rupiah */

// *** OPERASI REKAPITULASI ***
RekapitulasiKeuntungan BuatRekapitulasi(StackRiwayat riwayat, DaftarHargaTiket daftar, 
                                      struct Waktu waktu_awal, struct Waktu waktu_akhir);
/* Tujuan : Membuat rekapitulasi keuntungan untuk periode tertentu */
/* IS      : Stack riwayat dan daftar harga terdefinisi */
/* FS      : Mengembalikan struktur RekapitulasiKeuntungan yang berisi hasil rekapitulasi */

void TampilkanRekapitulasi(RekapitulasiKeuntungan rekap);
/* Tujuan : Menampilkan hasil rekapitulasi keuntungan */
/* IS      : Struktur rekapitulasi terdefinisi */
/* FS      : Informasi rekapitulasi ditampilkan ke layar */

void ExportRekapitulasiToCSV(RekapitulasiKeuntungan rekap, StackRiwayat riwayat, 
                           DaftarHargaTiket daftar, const char *filename);
/* Tujuan : Mengekspor hasil rekapitulasi keuntungan ke file CSV */
/* IS      : Struktur rekapitulasi, stack riwayat, dan daftar harga terdefinisi */
/* FS      : File CSV berisi data rekapitulasi keuntungan dibuat */

// *** OPERASI ANALISIS LANJUTAN ***
void AnalisisKeuntunganPerKereta(StackRiwayat riwayat, DaftarHargaTiket daftar);
/* Tujuan : Menganalisis keuntungan per kereta */
/* IS      : Stack riwayat dan daftar harga terdefinisi */
/* FS      : Hasil analisis keuntungan per kereta ditampilkan ke layar */

void AnalisisKeuntunganPerBulan(StackRiwayat riwayat, DaftarHargaTiket daftar, int tahun);
/* Tujuan : Menganalisis keuntungan per bulan untuk tahun tertentu */
/* IS      : Stack riwayat dan daftar harga terdefinisi */
/* FS      : Hasil analisis keuntungan per bulan ditampilkan ke layar */

void PrediksiKeuntunganBulanan(StackRiwayat riwayat, DaftarHargaTiket daftar);
/* Tujuan : Memprediksi keuntungan untuk bulan berikutnya berdasarkan data historis */
/* IS      : Stack riwayat dan daftar harga terdefinisi */
/* FS      : Hasil prediksi keuntungan ditampilkan ke layar */

#endif /* IMPLEMENTASI_REKAPITULASI_KEUNTUNGAN_H */ 