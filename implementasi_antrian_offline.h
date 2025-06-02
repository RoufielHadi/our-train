/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_ANTRIAN_OFFLINE_H
#define IMPLEMENTASI_ANTRIAN_OFFLINE_H

#include "queue.h"
#include "boolean.h"
#include "stack.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *** PROTOTYPE FUNGSI IMPLEMENTASI ANTRIAN OFFLINE ***

// *** OPERASI MANAJEMEN NOMOR ANTRIAN ***
void InisialisasiAntrianOffline(Queue *Q);
/* Tujuan : Menginisialisasi antrian offline baru */
/* IS      : Queue belum terdefinisi */
/* FS      : Queue terdefinisi dengan kondisi kosong dan siap digunakan */

int AmbilNomorAntrian(Queue *Q);
/* Tujuan : Mengambil nomor antrian baru dan menambahkannya ke antrian */
/* IS      : Queue terdefinisi */
/* FS      : Nomor antrian baru ditambahkan ke antrian dan dikembalikan */

boolean PanggilAntrian(Queue *Q, int *nomorDipanggil);
/* Tujuan : Memanggil antrian berikutnya */
/* IS      : Queue terdefinisi */
/* FS      : Jika antrian tidak kosong, nomor antrian terdepan dihapus dan dikembalikan
             melalui nomorDipanggil, kemudian mengembalikan TRUE. Jika antrian kosong,
             mengembalikan FALSE */

void LewatiAntrian(Queue *Q);
/* Tujuan : Melewati antrian terdepan dan memindahkannya ke belakang */
/* IS      : Queue terdefinisi dan tidak kosong */
/* FS      : Antrian terdepan dipindahkan ke belakang antrian */

void BatalkanAntrian(Queue *Q, int nomorAntrian);
/* Tujuan : Membatalkan nomor antrian tertentu */
/* IS      : Queue terdefinisi */
/* FS      : Jika nomor antrian ditemukan, dihapus dari antrian */

// *** OPERASI TAMPILAN ANTRIAN ***
void TampilkanStatusAntrian(Queue Q);
/* Tujuan : Menampilkan informasi status antrian saat ini */
/* IS      : Queue terdefinisi */
/* FS      : Informasi status antrian ditampilkan ke layar */

void TampilkanEstimasiWaktu(Queue Q, int waktuLayananPerOrang);
/* Tujuan : Menampilkan estimasi waktu tunggu untuk setiap nomor antrian */
/* IS      : Queue terdefinisi, waktuLayananPerOrang dalam menit */
/* FS      : Estimasi waktu tunggu untuk setiap nomor antrian ditampilkan */

// *** OPERASI PEMBELIAN TIKET ***
boolean ProsesLayananTiket(Queue *Q, StackRiwayat *riwayat, struct User user, 
                          struct InformasiKereta kereta, int nomor_gerbong, int nomor_kursi);
/* Tujuan : Memproses layanan pembelian tiket untuk antrian terdepan */
/* IS      : Queue dan riwayat terdefinisi */
/* FS      : Jika antrian tidak kosong, pembelian tiket diproses, antrian terdepan dihapus,
             data pembelian ditambahkan ke riwayat, dan mengembalikan TRUE.
             Jika antrian kosong, mengembalikan FALSE */

// *** OPERASI STATISTIK ***
int HitungRataRataWaktuTunggu(Queue Q, int waktuLayananPerOrang);
/* Tujuan : Menghitung rata-rata waktu tunggu dalam antrian */
/* IS      : Queue terdefinisi, waktuLayananPerOrang dalam menit */
/* FS      : Mengembalikan rata-rata waktu tunggu dalam menit */

int HitungEstimasiSelesai(Queue Q, int waktuLayananPerOrang);
/* Tujuan : Menghitung estimasi waktu untuk menyelesaikan seluruh antrian */
/* IS      : Queue terdefinisi, waktuLayananPerOrang dalam menit */
/* FS      : Mengembalikan total waktu yang dibutuhkan dalam menit */

// *** OPERASI FILE ***
void SimpanAntrianKeFile(Queue Q, const char *namaFile);
/* Tujuan : Menyimpan data antrian ke file */
/* IS      : Queue terdefinisi */
/* FS      : Data antrian tersimpan dalam file */

void MuatAntrianDariFile(Queue *Q, const char *namaFile);
/* Tujuan : Memuat data antrian dari file */
/* IS      : Queue terdefinisi */
/* FS      : Queue berisi data antrian yang dimuat dari file */

#endif /* IMPLEMENTASI_ANTRIAN_OFFLINE_H */ 