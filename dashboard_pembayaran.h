/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_PEMBAYARAN_H
#define DASHBOARD_PEMBAYARAN_H

#include "implementasi_pembayaran.h"
#include "implementasi_pembelian_tiket.h"
#include "implementasi_akun_user.h"
#include "boolean.h"
#include "clear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// *** FUNGSI UTAMA DASHBOARD PEMBAYARAN ***
boolean MenuPembayaran(PembelianTiket* pembelian, const char* email_user);
// Tujuan  : Menampilkan menu pembayaran dan memproses pembayaran tiket
// IS      : pembelian terdefinisi dengan status = DATA_PENUMPANG, email_user terdefinisi
// FS      : Pembayaran diproses, status = SELESAI jika berhasil, return TRUE jika berhasil

// *** FUNGSI PENDUKUNG DASHBOARD PEMBAYARAN ***
void TampilkanDetailPembayaran(PembelianTiket pembelian);
// Tujuan  : Menampilkan detail pembayaran yang akan dilakukan
// IS      : pembelian terdefinisi
// FS      : Detail pembayaran ditampilkan ke layar

boolean ProsesPembayaran(const char* email_user, float total_bayar);
// Tujuan  : Memproses pembayaran dengan mengurangi saldo user
// IS      : email_user terdefinisi, total_bayar > 0
// FS      : Saldo user berkurang, return TRUE jika berhasil

void TampilkanSaldoUser(const char* email_user);
// Tujuan  : Menampilkan saldo user
// IS      : email_user terdefinisi
// FS      : Saldo user ditampilkan ke layar

boolean ValidasiPinPembayaran(const char* email_user, const char* pin);
// Tujuan  : Memvalidasi PIN user untuk pembayaran
// IS      : email_user dan pin terdefinisi
// FS      : Return TRUE jika PIN valid

boolean CekSaldoCukup(const char* email_user, float total_bayar);
// Tujuan  : Mengecek apakah saldo user cukup untuk pembayaran
// IS      : email_user terdefinisi, total_bayar > 0
// FS      : Return TRUE jika saldo cukup

#endif /* DASHBOARD_PEMBAYARAN_H */
