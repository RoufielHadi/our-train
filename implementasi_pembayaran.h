/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef IMPLEMENTASI_PEMBAYARAN_H
#define IMPLEMENTASI_PEMBAYARAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "linked.h"

// Konstanta
#define MIN_SALDO 10000 // Minimal saldo yang harus dimiliki

// Fungsi untuk membuat data pembayaran baru
Payment BuatDataPembayaran(char* email, char* no_rekening, int saldo, char* pin);

// Fungsi untuk menambahkan data pembayaran ke dalam list
boolean TambahDataPembayaran(ListPayment *L, Payment payment_baru);

// Fungsi untuk mencari data pembayaran berdasarkan email
boolean CariDataPembayaran(ListPayment L, char* email, Payment* hasil);

// Fungsi untuk menambah saldo
boolean TambahSaldo(ListPayment *L, char* email, char* pin, int jumlah);

// Fungsi untuk mengurangi saldo (untuk pembelian tiket)
boolean KurangiSaldo(ListPayment *L, char* email, char* pin, int jumlah);

// Fungsi untuk mengubah PIN
boolean UbahPIN(ListPayment *L, char* email, char* pin_lama, char* pin_baru);

// Fungsi untuk menampilkan informasi pembayaran
void TampilkanInfoPembayaran(Payment payment);

// Fungsi untuk menampilkan semua data pembayaran (hanya admin)
void TampilkanSemuaDataPembayaran(ListPayment L);

// Fungsi untuk validasi PIN
boolean ValidasiPIN(ListPayment L, char* email, char* pin);

// Fungsi untuk memperbarui data pembayaran
boolean UpdateDataPembayaran(ListPayment *L, char* email, Payment payment_baru);

// Fungsi untuk menghapus data pembayaran
boolean HapusDataPembayaran(ListPayment *L, char* email);

// Fungsi untuk cek kecukupan saldo
boolean CekKecukupanSaldo(ListPayment L, char* email, int jumlah);

// Fungsi untuk validasi nomor rekening
boolean ValidasiNomorRekening(char* no_rekening);

#endif /* IMPLEMENTASI_PEMBAYARAN_H */ 