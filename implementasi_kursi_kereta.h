/*
Author: Devi Maulani
NIM: 241524007  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef IMPLEMENTASI_KURSI_KERETA_H
#define IMPLEMENTASI_KURSI_KERETA_H

#include "implementasi_informasi_kereta.h"
#include "array.h"
#include "databases.h"


// Konstanta nama file/direktori database kursi kereta
#define DB_FOLDER_KURSI "kursi_kereta"

// Fungsi wrapper untuk menghitung jumlah kursi
int HitungJumlahKursiKeretaWrapper(KursiKereta kereta);
// Tujuan  : Menghitung total jumlah kursi dalam kereta
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan jumlah total kursi

// KONVERSI ANTARA STRUKTUR KURSIKERETA DAN RECORD
void KursiKeretaKeRecord(KursiKereta kereta, Record *record);
// Tujuan  : Mengkonversi struktur KursiKereta menjadi Record untuk operasi database
// IS      : Struktur kereta dan record terdefinisi
// FS      : Record berisi informasi dari struktur kereta

boolean RecordKeKursiKereta(Record record, KursiKereta *kereta);
// Tujuan  : Mengkonversi Record menjadi struktur KursiKereta
// IS      : Record dan pointer ke struktur kereta terdefinisi
// FS      : Struktur kereta terisi dengan informasi dari record, return TRUE jika berhasil

// OPERASI FILE
boolean MuatDataKursiDariFile(KursiKereta *kereta, const char *namafile);
// Tujuan  : Memuat data kursi dari file database
// IS      : Kereta sudah terinisialisasi, file ada dan formatnya sesuai
// FS      : Data kursi dimuat ke dalam struktur kereta

boolean SimpanDataKursiKeFile(KursiKereta kereta, const char *namafile);
// Tujuan  : Menyimpan data kursi ke file database
// IS      : Kereta sudah terisi dengan data valid
// FS      : Data kursi disimpan ke file

// OPERASI KERETA DALAM DATABASE
boolean BuatKeretaBaru(ArrayKereta *arr, char *id_kereta, int jumlah_gerbong, char *tanggal, const char *daftar_segmen);
// Tujuan  : Membuat kereta baru dengan segmen dari string daftar segmen (format: "segmen1,segmen2,...")
// IS      : Array mungkin kosong atau berisi beberapa kereta
// FS      : Kereta baru ditambahkan ke dalam array jika belum penuh

boolean HapusKeretaDariDatabase(ArrayKereta *arr, char *id_kereta);
// Tujuan  : Menghapus kereta dari database berdasarkan ID
// IS      : Array tidak kosong
// FS      : Kereta dengan ID tertentu dihapus jika ditemukan

boolean SimpanKeretaKeDatabase(KursiKereta kereta);
// Tujuan  : Menyimpan data kereta ke database menggunakan fungsi dari databases.c
// IS      : Kereta sudah terisi dengan data valid
// FS      : Data kereta disimpan ke database, return TRUE jika berhasil

boolean BacaKeretaDariDatabase(KursiKereta *kereta, const char *id_kereta, const char *tanggal);
// Tujuan  : Membaca data kereta dari database menggunakan fungsi dari databases.c
// IS      : id_kereta dan tanggal terdefinisi
// FS      : Kereta terisi dengan data dari database, return TRUE jika berhasil

// OPERASI RESERVASI DALAM KONTEKS PERJALANAN
boolean ReservasiKursiPerjalanan(KursiKereta *kereta, int gerbong, int baris, int kolom, const char *segmen_awal, const char *segmen_akhir);
// Tujuan  : Mereservasi kursi untuk perjalanan dari segmen_awal hingga segmen_akhir
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika kursi berhasil direservasi untuk seluruh segmen perjalanan

boolean BatalkanReservasiPerjalanan(KursiKereta *kereta, int gerbong, int baris, int kolom, const char *segmen_awal, const char *segmen_akhir);
// Tujuan  : Membatalkan reservasi kursi untuk perjalanan
// IS      : Kereta sudah terinisialisasi
// FS      : Mengembalikan TRUE jika pembatalan berhasil untuk seluruh segmen perjalanan

// ANALISIS DATA
float HitungPersentaseOkupansiSegmen(KursiKereta kereta, const char *nama_segmen);
// Tujuan  : Menghitung persentase okupansi pada segmen tertentu
// IS      : Kereta sudah terinisialisasi dan memiliki data segmen
// FS      : Mengembalikan persentase kursi terisi (0-100) pada segmen tersebut

int HitungJumlahPenumpangSegmen(KursiKereta kereta, const char *nama_segmen);
// Tujuan  : Menghitung jumlah penumpang pada segmen tertentu
// IS      : Kereta sudah terinisialisasi dan memiliki data segmen
// FS      : Mengembalikan jumlah kursi yang terisi pada segmen tersebut

void TampilkanStatistikPenumpang(KursiKereta kereta);
// Tujuan  : Menampilkan statistik penumpang untuk semua segmen
// IS      : Kereta sudah terinisialisasi
// FS      : Statistik penumpang ditampilkan ke layar

// UTILITAS DATABASE
boolean MuatSemuaKeretaDariFolder(ArrayKereta *arr, const char *folder_path);
// Tujuan  : Memuat semua file kereta dari folder tertentu
// IS      : Array kereta sudah terinisialisasi
// FS      : Semua kereta dari folder dimuat ke dalam array

boolean SimpanSemuaKeretaKeFolder(ArrayKereta arr, const char *folder_path);
// Tujuan  : Menyimpan semua kereta dalam array ke folder
// IS      : Array kereta berisi data valid
// FS      : Semua kereta disimpan ke folder dalam file terpisah

// Menampilkan daftar gerbong yang tersedia untuk kereta tertentu
void TampilkanDaftarGerbong(KursiKereta kereta);
// Tujuan  : Menampilkan daftar gerbong yang tersedia untuk kereta tertentu
// IS      : Kereta sudah terinisialisasi
// FS      : Daftar gerbong ditampilkan ke layar

// Mengkonversi kode kursi (misal A1) ke baris dan kolom
boolean KonversiKodeKursi(const char* kode_kursi, int *baris, int *kolom);
// Tujuan  : Mengkonversi kode kursi (misal A1) ke baris dan kolom
// IS      : kode_kursi, pointer baris, dan pointer kolom terdefinisi
// FS      : Nilai baris dan kolom terisi sesuai kode kursi, return TRUE jika berhasil

// Mengecek apakah kursi tersedia pada rute/segmen tertentu
boolean CekKursiTersedia(KursiKereta kereta, int gerbong, const char* kode_kursi, 
                        const char* segmen_awal, const char* segmen_akhir);
// Tujuan  : Mengecek apakah kursi tersedia pada rute/segmen tertentu
// IS      : Kereta, gerbong, kode_kursi, segmen_awal, dan segmen_akhir terdefinisi
// FS      : Mengembalikan TRUE jika kursi tersedia untuk seluruh segmen perjalanan

// Pesan kursi berdasarkan kode kursi
boolean PesanKursi(KursiKereta *kereta, int gerbong, const char* kode_kursi,
                  const char* segmen_awal, const char* segmen_akhir);
// Tujuan  : Memesan kursi berdasarkan kode kursi
// IS      : Kereta sudah terinisialisasi, gerbong, kode_kursi, segmen_awal, dan segmen_akhir valid
// FS      : Kursi dipesan jika tersedia, return TRUE jika berhasil

// Konfirmasi pembayaran dan mengubah status kursi
boolean KonfirmasiPembayaranDanReservasi(KursiKereta *kereta, int gerbong, 
                                        const char* kode_kursi,
                                        const char* segmen_awal, const char* segmen_akhir);
// Tujuan  : Mengkonfirmasi pembayaran dan mengubah status kursi
// IS      : Kereta sudah terinisialisasi, kursi tersedia untuk dipesan
// FS      : Status kursi diubah menjadi terisi, return TRUE jika berhasil

// Tampilkan kursi tersedia untuk rute tertentu
void TampilkanKursiTersediaUntukRute(KursiKereta kereta, int gerbong,
                                    const char* segmen_awal, const char* segmen_akhir);
// Tujuan  : Menampilkan kursi yang tersedia untuk rute tertentu
// IS      : Kereta sudah terinisialisasi, gerbong, segmen_awal, dan segmen_akhir valid
// FS      : Denah kursi dengan status ketersediaan ditampilkan ke layar

// Mendapatkan jenis kereta dari database informasi kereta
JenisKereta GetJenisKeretaById(const char* id_kereta);
// Tujuan  : Mendapatkan jenis kereta dari database informasi kereta
// IS      : id_kereta terdefinisi
// FS      : Mengembalikan jenis kereta dari database informasi kereta

// Tampilkan informasi lengkap kereta dengan kursi
void TampilkanInfoKeretaDenganKursi(KursiKereta kereta);
// Tujuan  : Menampilkan informasi lengkap kereta termasuk informasi kursi
// IS      : Kereta sudah terinisialisasi dan globalListKereta sudah dimuat
// FS      : Informasi lengkap kereta dan kursi ditampilkan ke layar

#endif /* IMPLEMENTASI_KURSI_KERETA_H */
