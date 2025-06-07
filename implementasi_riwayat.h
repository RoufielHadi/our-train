/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_RIWAYAT_H
#define IMPLEMENTASI_RIWAYAT_H

#include "stack.h"
#include "linked.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *** PROTOTYPE FUNGSI IMPLEMENTASI RIWAYAT ***

// *** OPERASI PENCATATAN RIWAYAT ***
void CatatRiwayatPembelian(StackRiwayat *S, User user, InformasiKereta kereta, 
                          int nomor_gerbong, int nomor_kursi);
/* Tujuan : Mencatat riwayat pembelian tiket dengan waktu saat ini */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Riwayat pembelian ditambahkan ke dalam stack */

// *** OPERASI PENCARIAN DAN FILTER ***
StackRiwayat CariRiwayatByUser(StackRiwayat S, User user);
/* Tujuan : Mencari semua riwayat pembelian oleh pengguna tertentu */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Mengembalikan stack baru berisi riwayat pembelian pengguna yang dicari */

StackRiwayat CariRiwayatByKereta(StackRiwayat S, InformasiKereta kereta);
/* Tujuan : Mencari semua riwayat pembelian untuk kereta tertentu */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Mengembalikan stack baru berisi riwayat pembelian untuk kereta yang dicari */

StackRiwayat FilterRiwayatByWaktu(StackRiwayat S, Waktu waktu_awal, Waktu waktu_akhir);
/* Tujuan : Memfilter riwayat pembelian berdasarkan rentang waktu */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Mengembalikan stack baru berisi riwayat dalam rentang waktu yang ditentukan */

// *** OPERASI TAMPILAN ***
void TampilkanRiwayatPengguna(StackRiwayat S, User user);
/* Tujuan : Menampilkan semua riwayat pembelian untuk pengguna tertentu */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Informasi riwayat pembelian pengguna ditampilkan ke layar */

void TampilkanRingkasanRiwayat(StackRiwayat S);
/* Tujuan : Menampilkan ringkasan dari seluruh riwayat pembelian */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Ringkasan riwayat (jumlah tiket, kereta populer, dll) ditampilkan */

void ExportRiwayatToCSV(StackRiwayat S, const char *filename);
/* Tujuan : Mengekspor riwayat pembelian ke file CSV */
/* IS      : Stack riwayat terdefinisi */
/* FS      : File CSV berisi data riwayat pembelian dibuat */

// *** OPERASI ADMINISTRATIF ***
void HapusRiwayatSebelumTanggal(StackRiwayat *S, Waktu batas_waktu);
/* Tujuan : Menghapus semua riwayat pembelian sebelum tanggal tertentu */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Riwayat pembelian sebelum batas waktu dihapus dari stack */

int HitungJumlahRiwayatPengguna(StackRiwayat S, User user);
/* Tujuan : Menghitung jumlah pembelian tiket oleh pengguna tertentu */
/* IS      : Stack riwayat terdefinisi */
/* FS      : Mengembalikan jumlah pembelian oleh pengguna */

// *** FUNGSI VALIDASI ***
boolean IsRiwayatValid(RiwayatTiket tiket);
/* Tujuan : Memeriksa apakah data riwayat tiket valid */
/* IS      : Data riwayat tiket terdefinisi */
/* FS      : Mengembalikan TRUE jika data valid, FALSE jika tidak */

#endif /* IMPLEMENTASI_RIWAYAT_H */ 