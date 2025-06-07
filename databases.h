/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DATABASES_H
#define DATABASES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

// Definisi konstanta
#define MAX_FIELD_LENGTH 50
#define MAX_VALUE_LENGTH 255
#define MAX_RECORD_LENGTH 1024
#define MAX_FIELDS 20

// Struktur untuk menyimpan key-value pair
typedef struct {
    char key[MAX_FIELD_LENGTH];
    char value[MAX_VALUE_LENGTH];
} KeyValuePair;

// Struktur untuk menyimpan record (kumpulan key-value pairs)
typedef struct {
    KeyValuePair fields[MAX_FIELDS];
    int fieldCount;
} Record;

// Nama file database
extern const char* DB_AKUN_USER;
extern const char* DB_REKENING_USER;
extern const char* DB_INFORMASI_KERETA;
extern const char* DB_JADWAL_KERETA;
extern const char* DB_KURSI_KERETA;
extern const char* DB_RUTE_KERETA;
extern const char* DB_RIWAYAT_PEMBELIAN;

// Fungsi dasar operasi file
FILE* BukaFile(const char* namaFile, const char* mode);
/* Tujuan : Membuka file dengan mode tertentu */
/* IS      : namaFile dan mode terdefinisi */
/* FS      : Mengembalikan pointer ke file yang telah dibuka */

void TutupFile(FILE* file);
/* Tujuan : Menutup file yang telah dibuka */
/* IS      : file terdefinisi */
/* FS      : File ditutup */

boolean CekFileAda(const char* namaFile);
/* Tujuan : Memeriksa apakah file ada */
/* IS      : namaFile terdefinisi */
/* FS      : Mengembalikan TRUE jika file ada, FALSE jika tidak */

void BuatFileJikaBelumAda(const char* namaFile);
/* Tujuan : Membuat file baru jika belum ada */
/* IS      : namaFile terdefinisi */
/* FS      : File dengan nama namaFile dibuat jika belum ada */

// Fungsi operasi record
void InisialisasiRecord(Record* record);
/* Tujuan : Menginisialisasi record baru */
/* IS      : record terdefinisi */
/* FS      : record diinisialisasi dengan fieldCount = 0 */

void TambahField(Record* record, const char* key, const char* value);
/* Tujuan : Menambahkan field (key-value pair) ke record */
/* IS      : record, key, dan value terdefinisi */
/* FS      : Field baru ditambahkan ke record */

char* AmbilNilai(Record* record, const char* key);
/* Tujuan : Mengambil nilai dari key tertentu dalam record */
/* IS      : record dan key terdefinisi */
/* FS      : Mengembalikan nilai (value) dari key yang dicari */

void UbahNilai(Record* record, const char* key, const char* value);
/* Tujuan : Mengubah nilai dari key tertentu dalam record */
/* IS      : record, key, dan value terdefinisi */
/* FS      : Nilai (value) dari key yang dicari diubah */

void HapusField(Record* record, const char* key);
/* Tujuan : Menghapus field dengan key tertentu dari record */
/* IS      : record dan key terdefinisi */
/* FS      : Field dengan key tersebut dihapus dari record */

void CetakRecord(Record* record);
/* Tujuan : Mencetak seluruh isi record ke layar */
/* IS      : record terdefinisi */
/* FS      : Isi record dicetak ke layar */

// Fungsi konversi dan serialisasi
void RecordKeString(Record* record, char* output, int maxLength);
/* Tujuan : Mengkonversi record menjadi string */
/* IS      : record, output, dan maxLength terdefinisi */
/* FS      : Record dikonversi menjadi string dan disimpan di output */

void StringKeRecord(const char* input, Record* output);
/* Tujuan : Mengkonversi string menjadi record */
/* IS      : input dan output terdefinisi */
/* FS      : String dikonversi menjadi record dan disimpan di output */

// Fungsi operasi database
boolean SimpanRecord(const char* namaFile, Record* record, const char* primaryKey);
/* Tujuan : Menyimpan record ke file database */
/* IS      : namaFile, record, dan primaryKey terdefinisi */
/* FS      : Record disimpan ke file database, mengembalikan TRUE jika berhasil */

boolean BacaRecord(const char* namaFile, Record* record, const char* primaryKey, const char* primaryValue);
/* Tujuan : Membaca record dari file database berdasarkan primary key */
/* IS      : namaFile, record, primaryKey, dan primaryValue terdefinisi */
/* FS      : Record dengan primary key yang sesuai dibaca dari file dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateRecord(const char* namaFile, Record* record, const char* primaryKey);
/* Tujuan : Memperbarui record yang ada di file database */
/* IS      : namaFile, record, dan primaryKey terdefinisi */
/* FS      : Record dengan primary key yang sesuai diperbarui, mengembalikan TRUE jika berhasil */

boolean HapusRecord(const char* namaFile, const char* primaryKey, const char* primaryValue);
/* Tujuan : Menghapus record dari file database */
/* IS      : namaFile, primaryKey, dan primaryValue terdefinisi */
/* FS      : Record dengan primary key yang sesuai dihapus, mengembalikan TRUE jika berhasil */

// Fungsi database spesifik
// 1. Akun User
boolean SimpanAkunUser(Record* record);
/* Tujuan : Menyimpan data akun user ke database */
/* IS      : record terdefinisi dan berisi data akun user */
/* FS      : Data akun user disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaAkunUser(Record* record, const char* username);
/* Tujuan : Membaca data akun user dari database */
/* IS      : record dan username terdefinisi */
/* FS      : Data akun user dengan username yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateAkunUser(Record* record);
/* Tujuan : Memperbarui data akun user di database */
/* IS      : record terdefinisi dan berisi data akun user yang diperbarui */
/* FS      : Data akun user diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusAkunUser(const char* username);
/* Tujuan : Menghapus data akun user dari database */
/* IS      : username terdefinisi */
/* FS      : Data akun user dengan username yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

boolean VerifikasiLogin(const char* username, const char* password);
/* Tujuan : Memverifikasi login user dengan username dan password */
/* IS      : username dan password terdefinisi */
/* FS      : Mengembalikan TRUE jika username dan password cocok, FALSE jika tidak */

// 2. Rekening User
boolean SimpanRekeningUser(Record* record);
/* Tujuan : Menyimpan data rekening user ke database */
/* IS      : record terdefinisi dan berisi data rekening user */
/* FS      : Data rekening user disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaRekeningUser(Record* record, const char* nomorRekening);
/* Tujuan : Membaca data rekening user dari database */
/* IS      : record dan nomorRekening terdefinisi */
/* FS      : Data rekening user dengan nomor rekening yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateRekeningUser(Record* record);
/* Tujuan : Memperbarui data rekening user di database */
/* IS      : record terdefinisi dan berisi data rekening user yang diperbarui */
/* FS      : Data rekening user diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusRekeningUser(const char* nomorRekening);
/* Tujuan : Menghapus data rekening user dari database */
/* IS      : nomorRekening terdefinisi */
/* FS      : Data rekening user dengan nomor rekening yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

// 3. Informasi Kereta
boolean SimpanInformasiKereta(Record* record);
/* Tujuan : Menyimpan data informasi kereta ke database */
/* IS      : record terdefinisi dan berisi data informasi kereta */
/* FS      : Data informasi kereta disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaInformasiKereta(Record* record, const char* kodeKereta);
/* Tujuan : Membaca data informasi kereta dari database */
/* IS      : record dan kodeKereta terdefinisi */
/* FS      : Data informasi kereta dengan kode kereta yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateInformasiKereta(Record* record);
/* Tujuan : Memperbarui data informasi kereta di database */
/* IS      : record terdefinisi dan berisi data informasi kereta yang diperbarui */
/* FS      : Data informasi kereta diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusInformasiKereta(const char* kodeKereta);
/* Tujuan : Menghapus data informasi kereta dari database */
/* IS      : kodeKereta terdefinisi */
/* FS      : Data informasi kereta dengan kode kereta yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

void DaftarKereta(Record* records, int* jumlahRecord);
/* Tujuan : Mendapatkan daftar semua kereta dari database */
/* IS      : records dan jumlahRecord terdefinisi */
/* FS      : records berisi daftar semua kereta, jumlahRecord berisi jumlah kereta yang ditemukan */

// 4. Jadwal Kereta
boolean SimpanJadwalKereta(Record* record);
/* Tujuan : Menyimpan data jadwal kereta ke database */
/* IS      : record terdefinisi dan berisi data jadwal kereta */
/* FS      : Data jadwal kereta disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaJadwalKereta(Record* record, const char* kodeJadwal);
/* Tujuan : Membaca data jadwal kereta dari database */
/* IS      : record dan kodeJadwal terdefinisi */
/* FS      : Data jadwal kereta dengan kode jadwal yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateJadwalKereta(Record* record);
/* Tujuan : Memperbarui data jadwal kereta di database */
/* IS      : record terdefinisi dan berisi data jadwal kereta yang diperbarui */
/* FS      : Data jadwal kereta diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusJadwalKereta(const char* kodeJadwal);
/* Tujuan : Menghapus data jadwal kereta dari database */
/* IS      : kodeJadwal terdefinisi */
/* FS      : Data jadwal kereta dengan kode jadwal yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

void CariJadwalKereta(const char* stasiunAsal, const char* stasiunTujuan, const char* tanggal, Record* records, int* jumlahRecord);
/* Tujuan : Mencari jadwal kereta berdasarkan stasiun asal, stasiun tujuan, dan tanggal */
/* IS      : stasiunAsal, stasiunTujuan, tanggal, records, dan jumlahRecord terdefinisi */
/* FS      : records berisi daftar jadwal kereta yang sesuai dengan kriteria pencarian, jumlahRecord berisi jumlah jadwal yang ditemukan */

// 5. Kursi Kereta
boolean SimpanKursiKereta(Record* record);
/* Tujuan : Menyimpan data kursi kereta ke database */
/* IS      : record terdefinisi dan berisi data kursi kereta */
/* FS      : Data kursi kereta disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaKursiKereta(Record* record, const char* kodeKereta, const char* tanggal);
/* Tujuan : Membaca data kursi kereta dari database */
/* IS      : record, kodeKereta, dan tanggal terdefinisi */
/* FS      : Data kursi kereta dengan kode kereta dan tanggal yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateKursiKereta(Record* record);
/* Tujuan : Memperbarui data kursi kereta di database */
/* IS      : record terdefinisi dan berisi data kursi kereta yang diperbarui */
/* FS      : Data kursi kereta diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusKursiKereta(const char* kodeKereta, const char* tanggal);
/* Tujuan : Menghapus data kursi kereta dari database */
/* IS      : kodeKereta dan tanggal terdefinisi */
/* FS      : Data kursi kereta dengan kode kereta dan tanggal yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

void DaftarKursiTersedia(const char* kodeKereta, const char* tanggal, Record* record);
/* Tujuan : Mendapatkan daftar kursi tersedia untuk kereta dan tanggal tertentu */
/* IS      : kodeKereta, tanggal, dan record terdefinisi */
/* FS      : record berisi informasi kursi yang tersedia */

// 6. Rute Kereta
boolean SimpanRuteKereta(Record* record);
/* Tujuan : Menyimpan data rute kereta ke database */
/* IS      : record terdefinisi dan berisi data rute kereta */
/* FS      : Data rute kereta disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaRuteKereta(Record* record, const char* kodeRute);
/* Tujuan : Membaca data rute kereta dari database */
/* IS      : record dan kodeRute terdefinisi */
/* FS      : Data rute kereta dengan kode rute yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateRuteKereta(Record* record);
/* Tujuan : Memperbarui data rute kereta di database */
/* IS      : record terdefinisi dan berisi data rute kereta yang diperbarui */
/* FS      : Data rute kereta diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusRuteKereta(const char* kodeRute);
/* Tujuan : Menghapus data rute kereta dari database */
/* IS      : kodeRute terdefinisi */
/* FS      : Data rute kereta dengan kode rute yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

void CariRute(const char* stasiunAsal, const char* stasiunTujuan, Record* records, int* jumlahRecord);
/* Tujuan : Mencari rute kereta berdasarkan stasiun asal dan stasiun tujuan */
/* IS      : stasiunAsal, stasiunTujuan, records, dan jumlahRecord terdefinisi */
/* FS      : records berisi daftar rute kereta yang sesuai dengan kriteria pencarian, jumlahRecord berisi jumlah rute yang ditemukan */

// 7. Riwayat Pembelian
boolean SimpanRiwayatPembelian(Record* record);
/* Tujuan : Menyimpan data riwayat pembelian ke database */
/* IS      : record terdefinisi dan berisi data riwayat pembelian */
/* FS      : Data riwayat pembelian disimpan ke database, mengembalikan TRUE jika berhasil */

boolean BacaRiwayatPembelian(Record* record, const char* kodePembelian);
/* Tujuan : Membaca data riwayat pembelian dari database */
/* IS      : record dan kodePembelian terdefinisi */
/* FS      : Data riwayat pembelian dengan kode pembelian yang sesuai dibaca dari database dan disimpan di record, mengembalikan TRUE jika berhasil */

boolean UpdateRiwayatPembelian(Record* record);
/* Tujuan : Memperbarui data riwayat pembelian di database */
/* IS      : record terdefinisi dan berisi data riwayat pembelian yang diperbarui */
/* FS      : Data riwayat pembelian diperbarui di database, mengembalikan TRUE jika berhasil */

boolean HapusRiwayatPembelian(const char* kodePembelian);
/* Tujuan : Menghapus data riwayat pembelian dari database */
/* IS      : kodePembelian terdefinisi */
/* FS      : Data riwayat pembelian dengan kode pembelian yang sesuai dihapus dari database, mengembalikan TRUE jika berhasil */

void RiwayatPembelianUser(const char* username, Record* records, int* jumlahRecord);
/* Tujuan : Mendapatkan riwayat pembelian untuk user tertentu */
/* IS      : username, records, dan jumlahRecord terdefinisi */
/* FS      : records berisi daftar riwayat pembelian user, jumlahRecord berisi jumlah riwayat yang ditemukan */

#endif /* DATABASES_H */ 