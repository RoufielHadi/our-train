/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef IMPLEMENTASI_JADWAL_KERETA_H
#define IMPLEMENTASI_JADWAL_KERETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "linked.h"
#include "time.h"
#include "databases.h"

// Struktur untuk menyimpan jadwal kereta lengkap
typedef struct {
    char id_kereta[10];        // ID kereta yang dijalankan
    char tanggal[11];          // Format: DD-MM-YYYY
    JadwalKereta jadwal_rute;  // Linked list stasiun transit
} JadwalHarian;

typedef struct NodeJadwal {
    JadwalHarian jadwal;
    struct NodeJadwal* next;
} NodeJadwal;

typedef struct {
    NodeJadwal* First;
} ListJadwal;

// Fungsi untuk membuat jadwal kereta baru
JadwalHarian BuatJadwalKereta(char* id_kereta, char* tanggal);
/* Tujuan : Membuat struktur JadwalHarian baru berdasarkan id kereta dan tanggal */
/* IS      : id_kereta dan tanggal terdefinisi */
/* FS      : Mengembalikan JadwalHarian dengan data default */

// Fungsi untuk membuat list jadwal kosong
void CreateListJadwal(ListJadwal *L);
/* Tujuan : Menginisialisasi ListJadwal menjadi kosong */
/* IS      : pointer L terdefinisi */
/* FS      : L->First diatur ke NULL */

// Fungsi untuk membuat node jadwal baru
NodeJadwal* CreateNodeJadwal(JadwalHarian jadwal);
/* Tujuan : Membuat node baru berisi JadwalHarian */
/* IS      : jadwal terdefinisi */
/* FS      : Mengembalikan alamat NodeJadwal baru */

// Fungsi untuk menambahkan stasiun ke jadwal kereta
boolean TambahStasiunKeJadwal(JadwalHarian *jadwal, char* nama_stasiun, Waktu waktu_transit);
/* Tujuan : Menambahkan stasiun transit ke JadwalHarian */
/* IS      : jadwal pointer terdefinisi, nama_stasiun dan waktu_transit terdefinisi */
/* FS      : Stasiun ditambahkan, mengembalikan TRUE jika berhasil */

// Fungsi untuk menambahkan jadwal ke list jadwal
boolean TambahJadwalKeList(ListJadwal *L, JadwalHarian jadwal);
/* Tujuan : Menambahkan JadwalHarian ke ListJadwal */
/* IS      : pointer L terdefinisi, jadwal terdefinisi */
/* FS      : Node baru dimasukkan di akhir list, TRUE jika berhasil */

// Fungsi pencarian berdasarkan asal dan tujuan
NodeJadwal* CariJadwalByRute(ListJadwal L, const char* asal, const char* tujuan);
/* Tujuan : Mencari node jadwal pertama dengan rute tertentu */
/* IS      : L, asal, tujuan terdefinisi */
/* FS      : Mengembalikan pointer NodeJadwal jika ditemukan, NULL jika tidak */

// Fungsi pencarian lengkap berdasarkan asal + tujuan + tanggal + jenis layanan
NodeJadwal* CariJadwalLengkap(ListJadwal L, const char* asal, const char* tujuan, const char* tanggal, const char* jenis_layanan);
/* Tujuan : Mencari node jadwal yang lengkap sesuai kriteria */
/* IS      : semua parameter terdefinisi */
/* FS      : Pointer NodeJadwal atau NULL */

// Fungsi untuk mengupdate jadwal dan menyimpan ke database
boolean UpdateJadwal(ListJadwal *L, char* id_kereta, char* tanggal, JadwalHarian jadwal_baru);
/* Tujuan : Memperbarui jadwal dalam list dan database */
/* IS      : L, id_kereta, tanggal, jadwal_baru terdefinisi */
/* FS      : Jadwal diperbarui, TRUE jika berhasil */

// Fungsi untuk mengkonversi Record ke JadwalHarian
JadwalHarian KonversiRecordKeJadwalKereta(Record record);
/* Tujuan : Mengubah Record menjadi JadwalHarian */
/* IS      : record terdefinisi */
/* FS      : Mengembalikan JadwalHarian yang sesuai */

// Fungsi konversi JadwalHarian ke Record untuk database
void KonversiJadwalKeRecord(JadwalHarian jadwal, Record* record);
/* Tujuan : Mengubah JadwalHarian menjadi Record */
/* IS      : jadwal, pointer record terdefinisi */
/* FS      : Record diisi dengan data jadwal */

// Fungsi untuk menghapus jadwal dari list
boolean HapusJadwal(ListJadwal *L, char* id_kereta, char* tanggal);
/* Tujuan : Menghapus node JadwalHarian berdasarkan id dan tanggal */
/* IS      : L, id_kereta, tanggal terdefinisi */
/* FS      : Node dihapus, TRUE jika berhasil */

// Fungsi untuk menampilkan jadwal kereta
void TampilkanJadwalKereta(JadwalHarian jadwal);
/* Tujuan : Menampilkan detail JadwalHarian */
/* IS      : jadwal terdefinisi */
/* FS      : Data jadwal dicetak ke layar */

// Fungsi untuk menampilkan semua jadwal kereta
void TampilkanSemuaJadwal(ListJadwal L);
/* Tujuan : Menampilkan setiap jadwal dalam list */
/* IS      : L terdefinisi */
/* FS      : Semua jadwal dicetak */

// Fungsi untuk mencari waktu keberangkatan dari stasiun tertentu
boolean CariWaktuKeberangkatan(JadwalHarian jadwal, char* nama_stasiun, Waktu* hasil_waktu);
/* Tujuan : Mengambil waktu keberangkatan di stasiun tertentu */
/* IS      : jadwal, nama_stasiun, hasil_waktu terdefinisi */
/* FS      : waktu disimpan di hasil_waktu, TRUE jika ditemukan */

// Fungsi untuk menghitung durasi perjalanan antar stasiun
int HitungDurasiPerjalanan(JadwalHarian jadwal, char* stasiun_asal, char* stasiun_tujuan);
/* Tujuan : Menghitung selisih waktu antara dua stasiun */
/* IS      : jadwal, stasiun_asal, stasiun_tujuan terdefinisi */
/* FS      : Mengembalikan durasi dalam menit */

// Fungsi untuk memperbarui waktu transit stasiun
boolean UpdateWaktuTransit(JadwalHarian *jadwal, char* nama_stasiun, Waktu waktu_baru);
/* Tujuan : Mengubah waktu transit pada stasiun tertentu */
/* IS      : jadwal, nama_stasiun, waktu_baru terdefinisi */
/* FS      : Waktu transit diperbarui, TRUE jika berhasil */

// Fungsi untuk mengecek ketersediaan stasiun di jadwal
boolean IsStasiunTersedia(JadwalHarian jadwal, const char* nama_stasiun);
/* Tujuan : Mengecek apakah stasiun ada di jadwal */
/* IS      : jadwal, nama_stasiun terdefinisi */
/* FS      : Mengembalikan TRUE jika ada */

// Fungsi untuk menyalin jadwal
JadwalHarian SalinJadwal(JadwalHarian jadwal);
/* Tujuan : Membuat salinan JadwalHarian */
/* IS      : jadwal terdefinisi */
/* FS      : Mengembalikan salinan jadwal */

// Fungsi untuk membalik urutan jadwal (stasiun pertama jadi terakhir)
JadwalHarian BalikJadwal(JadwalHarian jadwal);
/* Tujuan : Membalik urutan stasiun dalam jadwal */
/* IS      : jadwal terdefinisi */
/* FS      : Mengembalikan jadwal terbalik */

// Fungsi untuk mengkonversi string tanggal ke format yang sesuai
boolean KonversiTanggal(char* tanggal_input, char* tanggal_output);
/* Tujuan : Mengubah format tanggal input ke output */
/* IS      : tanggal_input terdefinisi */
/* FS      : tanggal_output diisi jika valid */

// Fungsi untuk validasi tanggal
boolean ValidasiTanggal(char* tanggal);
/* Tujuan : Memeriksa format tanggal valid */
/* IS      : tanggal terdefinisi */
/* FS      : Mengembalikan TRUE jika valid */

#endif /* IMPLEMENTASI_JADWAL_KERETA_H */