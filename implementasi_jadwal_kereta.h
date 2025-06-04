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

// Fungsi untuk membuat list jadwal kosong
void CreateListJadwal(ListJadwal *L);

// Fungsi untuk membuat node jadwal baru
NodeJadwal* CreateNodeJadwal(JadwalHarian jadwal);

// Fungsi untuk menambahkan stasiun ke jadwal kereta
boolean TambahStasiunKeJadwal(JadwalHarian *jadwal, char* nama_stasiun, Waktu waktu_transit);

// Fungsi untuk menambahkan jadwal ke list jadwal
boolean TambahJadwalKeList(ListJadwal *L, JadwalHarian jadwal);

// Fungsi untuk mencari jadwal berdasarkan ID kereta dan tanggal
NodeJadwal* CariJadwal(ListJadwal L, char* id_kereta, char* tanggal);

// Fungsi untuk menghapus jadwal dari list
boolean HapusJadwal(ListJadwal *L, char* id_kereta, char* tanggal);

// Fungsi untuk menampilkan jadwal kereta
void TampilkanJadwalKereta(JadwalHarian jadwal);

// Fungsi untuk menampilkan semua jadwal kereta
void TampilkanSemuaJadwal(ListJadwal L);

// Fungsi untuk mencari waktu keberangkatan dari stasiun tertentu
boolean CariWaktuKeberangkatan(JadwalHarian jadwal, char* nama_stasiun, Waktu* hasil_waktu);

// Fungsi untuk menghitung durasi perjalanan antar stasiun
int HitungDurasiPerjalanan(JadwalHarian jadwal, char* stasiun_asal, char* stasiun_tujuan);

// Fungsi untuk memperbarui waktu transit stasiun
boolean UpdateWaktuTransit(JadwalHarian *jadwal, char* nama_stasiun, Waktu waktu_baru);

// Fungsi untuk mengecek ketersediaan stasiun di jadwal
boolean IsStasiunTersedia(JadwalHarian jadwal, char* nama_stasiun);

// Fungsi untuk menyalin jadwal
JadwalHarian SalinJadwal(JadwalHarian jadwal);

// Fungsi untuk membalik urutan jadwal (stasiun pertama jadi terakhir)
JadwalHarian BalikJadwal(JadwalHarian jadwal);

// Fungsi untuk mengkonversi string tanggal ke format yang sesuai
boolean KonversiTanggal(char* tanggal_input, char* tanggal_output);

// Fungsi untuk validasi tanggal
boolean ValidasiTanggal(char* tanggal);

// Fungsi CRUD untuk dashboard jadwal
void TampilkanDaftarJadwal();
void TambahJadwal();
void EditJadwal();
void HapusJadwalDashboard();

#endif /* IMPLEMENTASI_JADWAL_KERETA_H */ 