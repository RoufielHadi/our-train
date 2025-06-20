#ifndef IMPLEMENTASI_KURSI_KERETA_H
#define IMPLEMENTASI_KURSI_KERETA_H

#include "array.h"
#include "databases.h"
#include "boolean.h"

// Memuat data kursi kereta dari file database ke struktur kursi
boolean MuatDataKursiDariFile(KursiKereta *kereta, const char *namaFile);

// Menginisialisasi kursi berdasarkan jadwal kereta (sinkronisasi antara jadwal dan kursi)
boolean InisialisasiKursiDenganJadwal(KursiKereta *kereta, JenisKereta jenis);

// Menampilkan denah kursi gerbong tertentu berdasarkan status di database
void TampilkanKursiLangsungDariDatabase(const char *id_kereta, const char *tanggal, int gerbong, const char *stasiun_awal, const char *stasiun_akhir);

// Menyimpan perubahan kursi (setelah pembayaran) ke file database
boolean SimpanDataKursiKeFile(KursiKereta *kereta, const char *namaFile);

// Fungsi untuk memilih kursi: parsing kode dan memanggil ReservasiKursiMultiSegmen
boolean PilihKursi(KursiKereta *kereta, int gerbong, const char *kode_kursi, const char *stasiun_awal, const char *stasiun_akhir);

// Menghitung jumlah gerbong yang tersedia dalam file database kursi
int HitungJumlahGerbongDariFile(const char *id_kereta, const char *tanggal, const char *namaFile);

// Menghitung jumlah kolom yang tersedia dalam file database kursi
int HitungJumlahKolomDariFile(const char *id_kereta, const char *tanggal, int gerbong, const char *namaFile);

#endif /* IMPLEMENTASI_KURSI_KERETA_H */
