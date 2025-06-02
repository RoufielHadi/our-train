/*
Author: Roufiel Hadi  
NIM: 241524028  
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

// Konstanta untuk jenis layanan kereta
#define EKONOMI "Ekonomi"
#define BISNIS "Bisnis"
#define EKSEKUTIF "Eksekutif"
#define LUXURY "Luxury"

// Fungsi untuk membuat informasi kereta baru
InformasiKereta BuatInformasiKereta(char* id_kereta, char* nama_kereta, char* jenis_layanan, float harga_tiket, char* jumlah_gerbong);

// Fungsi untuk menambahkan informasi kereta ke dalam list
boolean TambahInformasiKereta(ListKereta *L, InformasiKereta kereta_baru);

// Fungsi untuk mencari informasi kereta berdasarkan ID
boolean CariInformasiKereta(ListKereta L, char* id_kereta, InformasiKereta* hasil);

// Fungsi untuk memperbarui informasi kereta
boolean UpdateInformasiKereta(ListKereta *L, char* id_kereta, InformasiKereta kereta_baru);

// Fungsi untuk menghapus informasi kereta
boolean HapusInformasiKereta(ListKereta *L, char* id_kereta);

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

#endif /* IMPLEMENTASI_INFORMASI_KERETA_H */ 