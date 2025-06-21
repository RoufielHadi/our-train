/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef IMPLEMENTASI_PEMBELIAN_TIKET_H
#define IMPLEMENTASI_PEMBELIAN_TIKET_H

#include "boolean.h"
#include "databases.h"
#include "implementasi_jadwal_kereta.h"
#include "implementasi_kursi_kereta.h"
#include "implementasi_informasi_kereta.h"
#include "implementasi_akun_user.h"
#include "dashboard_kursi_kereta.h"
#include "linked.h"
#include "clear.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Functions to handle logged in user
void SetLoggedInUser(const char* email);
const char* GetLoggedInUser();

// Definisi konstanta untuk file database
#define DB_JADWAL_KERETA "jadwal_kereta.txt"
#define DB_RIWAYAT_PEMESANAN "riwayat_pemesanan.txt"

// Struktur untuk menyimpan informasi rute kereta
typedef struct {
    char stasiun_asal[MAX_NAMA_SEGMEN];
    char stasiun_tujuan[MAX_NAMA_SEGMEN];
} RuteKereta;

// Struktur untuk menyimpan hasil pencarian tiket
typedef struct {
    char id_kereta[10];       // ID kereta
    char nama_kereta[50];     // Nama kereta 
    char stasiun_asal[MAX_NAMA_SEGMEN];  // Stasiun asal
    char stasiun_tujuan[MAX_NAMA_SEGMEN]; // Stasiun tujuan
    char tanggal[11];         // Format DD-MM-YYYY
    char waktu_berangkat[6];  // Format HH:MM
    char waktu_tiba[6];       // Format HH:MM
    char jenis_layanan[20];   // Jenis layanan kereta
    float harga_tiket;        // Harga tiket
    int kursi_tersedia;       // Jumlah kursi tersedia
} HasilPencarian;

// Struktur untuk node hasil pencarian (me-reuse konsep dari linked.h)
typedef struct NodeHasilPencarian {
    HasilPencarian tiket;
    struct NodeHasilPencarian* next;
} NodeHasilPencarian;

// Struktur untuk list hasil pencarian (me-reuse konsep dari linked.h)
typedef struct {
    NodeHasilPencarian* head;
    int count; // Jumlah hasil pencarian
} ListHasilPencarian;

// Status dalam proses pembelian tiket
typedef enum {
    PENCARIAN,
    PEMILIHAN_TIKET,
    PEMILIHAN_KURSI,
    DATA_PENUMPANG,
    PEMBAYARAN,
    SELESAI
} StatusPembelian;

// Struktur untuk menyimpan informasi pembelian tiket
typedef struct {
    HasilPencarian tiket_dipilih;    // Tiket yang dipilih
    int nomor_gerbong;               // Nomor gerbong yang dipilih
    char kode_kursi[5];              // Kode kursi yang dipilih (misal: A1)
    char email_penumpang[100];       // Email penumpang
    char nama_penumpang[50];         // Nama penumpang
    char nomor_telepon[20];          // Nomor telepon penumpang
    char nomor_identitas[20];        // Nomor KTP/SIM/Paspor
    float total_bayar;               // Total yang harus dibayar
    StatusPembelian status;          // Status dalam proses pembelian
    char kode_pembelian[20];         // Kode unik pembelian
} PembelianTiket;

// ----------------------------------------------- FUNGSI-FUNGSI UNTUK PENCARIAN TIKET --------------------------------------------

// Inisialisasi list hasil pencarian
void InisialisasiListHasilPencarian(ListHasilPencarian* list);
// Tujuan  : Menginisialisasi list hasil pencarian
// IS      : List belum diinisialisasi
// FS      : List memiliki head = NULL dan count = 0

// Menambahkan hasil pencarian ke dalam list
boolean TambahHasilPencarian(ListHasilPencarian* list, HasilPencarian tiket);
// Tujuan  : Menambahkan tiket ke dalam list hasil pencarian
// IS      : List sudah diinisialisasi
// FS      : Tiket ditambahkan ke dalam list, count bertambah 1

// Menghapus seluruh list hasil pencarian
void HapusListHasilPencarian(ListHasilPencarian* list);
// Tujuan  : Menghapus seluruh node dalam list hasil pencarian
// IS      : List mungkin kosong atau berisi beberapa node
// FS      : Seluruh node dihapus, head = NULL, count = 0

// Mendapatkan daftar rute unik dan terurut
void DapatkanRuteUnik(RuteKereta** daftar_rute, int* jumlah_rute);
// Tujuan  : Mendapatkan daftar rute unik yang diurutkan secara alfabetis
// IS      : daftar_rute = NULL, jumlah_rute = 0
// FS      : daftar_rute berisi array rute unik, jumlah_rute berisi jumlah rute

// Menampilkan daftar rute kereta
void TampilkanDaftarRute(RuteKereta* daftar_rute, int jumlah_rute);
// Tujuan  : Menampilkan daftar rute kereta
// IS      : daftar_rute sudah terisi dan jumlah_rute > 0
// FS      : Daftar rute ditampilkan ke layar

// Mencari tiket berdasarkan kriteria
boolean CariTiket(ListHasilPencarian* hasil, const char* stasiun_asal, 
                 const char* stasiun_tujuan, const char* tanggal, const char* jenis_layanan);
// Tujuan  : Mencari tiket berdasarkan stasiun asal, stasiun tujuan, tanggal, dan jenis layanan
// IS      : hasil sudah diinisialisasi
// FS      : hasil berisi tiket yang sesuai kriteria, return TRUE jika ditemukan

// Menampilkan hasil pencarian tiket
void TampilkanHasilPencarian(ListHasilPencarian hasil);
// Tujuan  : Menampilkan hasil pencarian tiket
// IS      : hasil berisi tiket yang sudah dicari
// FS      : Hasil pencarian ditampilkan ke layar

// --------------------------------------------- FUNGSI-FUNGSI UNTUK PEMILIHAN TIKET ----------------------------------------------

// Memilih tiket dari hasil pencarian
boolean PilihTiket(ListHasilPencarian hasil, int nomor_tiket, HasilPencarian* tiket_dipilih);
// Tujuan  : Memilih tiket berdasarkan nomor urut
// IS      : hasil terdefinisi, nomor_tiket terdefinisi
// FS      : tiket_dipilih berisi tiket yang dipilih, return TRUE jika berhasil

// Inisialisasi struktur pembelian tiket baru
void InisialisasiPembelianTiket(PembelianTiket* pembelian, HasilPencarian tiket_dipilih);
// Tujuan  : Menginisialisasi struktur pembelian tiket
// IS      : pembelian dan tiket_dipilih terdefinisi
// FS      : pembelian terisi dengan data awal dari tiket_dipilih

// Tampilkan detail tiket yang dipilih
void TampilkanDetailTiket(PembelianTiket pembelian);
// Tujuan  : Menampilkan detail tiket yang dipilih
// IS      : pembelian terdefinisi
// FS      : Detail tiket ditampilkan ke layar

// Simpan data pembelian ke dalam file riwayat pembelian
boolean SimpanRiwayatPembelianTiket(PembelianTiket pembelian);
// Tujuan  : Menyimpan data pembelian tiket ke dalam file riwayat
// IS      : pembelian sudah terisi lengkap dan status = SELESAI
// FS      : Data pembelian tersimpan dalam file, return TRUE jika berhasil

// Fungsi utilitas untuk mengonversi string ke lowercase
void StringToLower(char* str, char* result);
// Tujuan  : Mengonversi string ke lowercase
// IS      : str berisi string input
// FS      : result berisi string dalam bentuk lowercase

// Fungsi untuk membuat kode pembelian unik
void GenerateKodePembelian(char* kode_pembelian);
// Tujuan  : Membuat kode pembelian unik
// IS      : kode_pembelian terdefinisi
// FS      : kode_pembelian berisi kode unik

// Fungsi pencarian tiket utama (entry point dalam pembelian tiket)
void MenuPencarianTiket();
// Tujuan  : Menampilkan menu pencarian tiket dan melakukan pencarian
// IS      : -
// FS      : Pencarian tiket dilakukan dan hasilnya ditampilkan

// -------------------------------------------- FUNGSI-FUNGSI UNTUK PEMILIHAN KURSI -----------------------------------------------

// Fungsi untuk pemilihan kursi pada proses pembelian tiket
void MenuPemilihanKursi(PembelianTiket* pembelian);
// Tujuan  : Menampilkan menu pemilihan kursi dan melakukan pemilihan kursi
// IS      : pembelian terdefinisi dengan status = PEMILIHAN_TIKET
// FS      : Kursi dipilih, status = PEMILIHAN_KURSI

// --------------------------------------------- FUNGSI-FUNGSI UNTUK DATA PENUMPANG -----------------------------------------------

// Mengisi data penumpang
void MenuDataPenumpang(PembelianTiket* pembelian);
// Tujuan  : Menampilkan menu pengisian data penumpang
// IS      : pembelian terdefinisi dengan status = PEMILIHAN_KURSI
// FS      : Data penumpang terisi, status = DATA_PENUMPANG

// Mengisi data penumpang dari akun yang sedang login
boolean IsiDataPenumpangDariAkun(PembelianTiket* pembelian, User user_aktif);
// Tujuan  : Mengisi data penumpang dari akun yang sedang login
// IS      : pembelian dan user_aktif terdefinisi
// FS      : Data penumpang terisi dari data user_aktif, return TRUE jika berhasil

// Validasi data penumpang
boolean ValidasiDataPenumpang(PembelianTiket pembelian);
// Tujuan  : Memvalidasi data penumpang
// IS      : pembelian terdefinisi
// FS      : Return TRUE jika data penumpang valid

// ------------------------------------------- FUNGSI-FUNGSI UNTUK PEMBAYARAN -----------------------------------------------------

// Fungsi untuk pembayaran tiket (deklarasi)
// Implementasi ada di dashboard_pembayaran.c
boolean MenuPembayaran(PembelianTiket* pembelian, const char* email_user);
// Tujuan  : Menampilkan menu pembayaran dan memproses pembayaran tiket
// IS      : pembelian terdefinisi dengan status = DATA_PENUMPANG, email_user terdefinisi
// FS      : Pembayaran diproses, status = SELESAI jika berhasil, return TRUE jika berhasil

#endif /* IMPLEMENTASI_PEMBELIAN_TIKET_H */
