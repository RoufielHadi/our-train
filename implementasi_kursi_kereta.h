/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_KURSI_KERETA_H
#define IMPLEMENTASI_KURSI_KERETA_H

#include "array.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *** PROTOTYPE FUNGSI IMPLEMENTASI KURSI KERETA ***

// *** OPERASI PENGELOLAAN GERBONG ***
void TambahGerbong(KursiKereta *kereta, int jumlah_gerbong_baru);
// Tujuan  : Menambahkan jumlah gerbong pada kereta
// IS      : Kereta terdefinisi dan memiliki jumlah_gerbong yang valid
// FS      : Jumlah gerbong kereta bertambah sebanyak jumlah_gerbong_baru

void KurangiGerbong(KursiKereta *kereta, int jumlah_gerbong_dikurangi);
// Tujuan  : Mengurangi jumlah gerbong pada kereta
// IS      : Kereta terdefinisi dan memiliki jumlah_gerbong yang valid
// FS      : Jumlah gerbong kereta berkurang sebanyak jumlah_gerbong_dikurangi

void UbahJenisKereta(KursiKereta *kereta, JenisKereta jenis_baru);
// Tujuan  : Mengubah jenis kereta dan menyesuaikan konfigurasi kursi
// IS      : Kereta terdefinisi
// FS      : Jenis kereta berubah dan konfigurasi kursi disesuaikan

// *** OPERASI MANAJEMEN KURSI ***
boolean ReservasiKursiOtomatis(KursiKereta *kereta, int *gerbong, int *baris, int *kolom);
// Tujuan  : Mereservasi kursi secara otomatis (kursi pertama yang tersedia)
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika berhasil menemukan kursi kosong dan mereservasinya,
//           FALSE jika semua kursi terisi. Jika berhasil, gerbong, baris, kolom diisi.

boolean ReservasiKursiBerurutan(KursiKereta *kereta, int jumlah_kursi, int *gerbong, int *baris_awal, int *kolom_awal);
// Tujuan  : Mereservasi kursi berurutan untuk kelompok penumpang
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika berhasil menemukan kursi kosong berurutan dan mereservasinya,
//           FALSE jika tidak ada kursi berurutan yang cukup. Jika berhasil, gerbong, baris_awal, kolom_awal diisi.

boolean PindahKursi(KursiKereta *kereta, int gerbong_lama, int baris_lama, int kolom_lama, 
                    int gerbong_baru, int baris_baru, int kolom_baru);
// Tujuan  : Memindahkan reservasi dari satu kursi ke kursi lain
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika berhasil memindahkan reservasi, FALSE jika gagal

// *** OPERASI STATISTIK ***
int HitungKetersediaanKursiGerbong(KursiKereta kereta, int gerbong);
// Tujuan  : Menghitung jumlah kursi yang masih tersedia di gerbong tertentu
// IS      : Kereta sudah terinisialisasi dan gerbong valid
// FS      : Mengembalikan jumlah kursi yang masih tersedia

int HitungKetersediaanKursiTotal(KursiKereta kereta);
// Tujuan  : Menghitung jumlah kursi yang masih tersedia di seluruh kereta
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan jumlah kursi yang masih tersedia

float HitungPersentaseKetersediaanGerbong(KursiKereta kereta, int gerbong);
// Tujuan  : Menghitung persentase kursi yang masih tersedia di gerbong tertentu
// IS      : Kereta sudah terinisialisasi dan gerbong valid
// FS      : Mengembalikan persentase kursi yang masih tersedia (0-100)

// *** OPERASI DISPLAY KHUSUS ***
void TampilkanStatistikKereta(KursiKereta kereta);
// Tujuan  : Menampilkan statistik kereta, termasuk jumlah kursi, ketersediaan, dll
// IS      : Kereta sudah terinisialisasi
// FS      : Informasi statistik kereta ditampilkan ke layar

void TampilkanDiagramOkupansiKereta(KursiKereta kereta);
// Tujuan  : Menampilkan diagram okupansi seluruh kereta
// IS      : Kereta sudah terinisialisasi
// FS      : Diagram visual okupansi kereta ditampilkan ke layar

void ExportDaftarPenumpang(KursiKereta kereta, char *filename);
// Tujuan  : Mengekspor daftar kursi yang terisi ke file teks
// IS      : Kereta sudah terinisialisasi
// FS      : File teks berisi daftar kursi yang terisi dibuat

// *** OPERASI ADMINISTRATIF ***
void ResetSeluruhKursi(KursiKereta *kereta);
// Tujuan  : Mengatur ulang seluruh kursi menjadi kosong
// IS      : Kereta sudah terinisialisasi
// FS      : Seluruh kursi kereta menjadi kosong

void BlokKursiUntukMaintenance(KursiKereta *kereta, int gerbong, int baris_awal, int baris_akhir);
// Tujuan  : Memblokir kursi untuk keperluan pemeliharaan
// IS      : Kereta sudah terinisialisasi
// FS      : Seluruh kursi dalam rentang baris yang ditentukan pada gerbong tertentu diblokir

#endif /* IMPLEMENTASI_KURSI_KERETA_H */ 