/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

/*
Author fungsi antar modul : Devi Maulani
NIM: 241524007  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/


#ifndef IMPLEMENTASI_INFORMASI_KERETA_H
#define IMPLEMENTASI_INFORMASI_KERETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "linked.h"
#include "array.h"
#include "clear.h"

// Konstanta untuk jenis layanan kereta untuk menghindari konflik dengan enum di array.h
#define STR_EKONOMI "Ekonomi"
#define STR_BISNIS "Bisnis"
#define STR_EKSEKUTIF "Eksekutif"
#define STR_LUXURY "Luxury"


// Deklarasi variabel global untuk akses di seluruh program
extern ListKereta globalListKereta;
extern ArrayKereta globalArrayKereta;

// UI functions for kereta management
void TampilkanDaftarKeretaDBUI();
void TambahKeretaUI();
void EditKereta();
void HapusKeretaUI();

// Fungsi untuk membuat informasi kereta baru
InformasiKereta BuatInformasiKereta(char* id_kereta, char* nama_kereta, char* jenis_layanan, float harga_tiket, char* jumlah_gerbong);

// Fungsi untuk menambahkan informasi kereta ke dalam list
boolean TambahInformasiKereta(ListKereta *L, InformasiKereta kereta_baru);

// Fungsi untuk mencari informasi kereta berdasarkan ID
boolean CariInformasiKereta(ListKereta L, char* id_kereta, InformasiKereta* hasil);

// Fungsi untuk menampilkan informasi kereta
void TampilkanInformasiKereta(InformasiKereta kereta);

// Fungsi untuk menampilkan semua informasi kereta
void TampilkanSemuaInformasiKereta(ListKereta L);

// Fungsi untuk memfilter kereta berdasarkan jenis layanan
void FilterKeretaBerdasarkanLayanan(ListKereta L, char* jenis_layanan);

// Fungsi untuk memfilter kereta berdasarkan rentang harga
void FilterKeretaBerdasarkanHarga(ListKereta L, float harga_min, float harga_max);

// Fungsi untuk mengurutkan kereta berdasarkan harga (ascending)
ListKereta UrutkanKeretaBerdasarkanHarga(ListKereta L, boolean ascending);

// Fungsi untuk mengurutkan kereta berdasarkan nama (alphabetical)
ListKereta UrutkanKeretaBerdasarkanNama(ListKereta L);

// Fungsi untuk validasi ID kereta
boolean ValidasiIDKereta(char* id_kereta);

// Fungsi untuk validasi jenis layanan
boolean ValidasiJenisLayanan(char* jenis_layanan);

// Fungsi untuk menghitung jumlah kereta berdasarkan jenis layanan
int HitungJumlahKeretaBerdasarkanLayanan(ListKereta L, char* jenis_layanan);

// Fungsi untuk menghasilkan ID kereta unik baru
void GenerateIDKereta(ListKereta L, char* id_baru);

// Fungsi helper untuk integrasi antar modul
// ==================================================

// Mendapatkan pointer ke informasi kereta berdasarkan ID
InformasiKereta* GetInformasiKeretaById(ListKereta L, const char* id_kereta);
// Tujuan  : Mendapatkan pointer ke informasi kereta berdasarkan ID
// IS      : L terdefinisi, id_kereta valid
// FS      : Mengembalikan pointer ke InformasiKereta jika ditemukan, NULL jika tidak


// Mendapatkan jenis layanan kereta berdasarkan ID
const char* GetJenisLayananById(ListKereta L, const char* id_kereta);
// Tujuan  : Mendapatkan jenis layanan kereta berdasarkan ID
// IS      : L terdefinisi, id_kereta valid
// FS      : Mengembalikan string jenis layanan kereta


// Mendapatkan harga tiket kereta berdasarkan ID
float GetHargaTiketById(ListKereta L, const char* id_kereta);
// Tujuan  : Mendapatkan harga tiket kereta berdasarkan ID
// IS      : L terdefinisi, id_kereta valid
// FS      : Mengembalikan harga tiket kereta, 0 jika tidak ditemukan


// Mendapatkan jumlah gerbong kereta berdasarkan ID
int GetJumlahGerbongById(ListKereta L, const char* id_kereta);
// Tujuan  : Mendapatkan jumlah gerbong kereta berdasarkan ID
// IS      : L terdefinisi, id_kereta valid
// FS      : Mengembalikan jumlah gerbong kereta, 0 jika tidak ditemukan


// Inisialisasi list kereta global
void InisialisasiListKeretaGlobal();
// Tujuan  : Menginisialisasi list kereta global untuk digunakan di seluruh program
// IS      : -
// FS      : globalListKereta diinisialisasi sebagai list kosong


// Memuat semua data kereta dari database ke list global
boolean MuatDataKeretaKeGlobal();
// Tujuan  : Memuat semua data kereta dari database ke list global
// IS      : globalListKereta sudah diinisialisasi
// FS      : globalListKereta berisi semua data kereta dari database


// Prototipe: Mendapatkan enum JenisKereta berdasarkan ID kereta (menggunakan data globalListKereta)
JenisKereta GetJenisKeretaById(const char* id_kereta);

#endif /* IMPLEMENTASI_INFORMASI_KERETA_H */ 
