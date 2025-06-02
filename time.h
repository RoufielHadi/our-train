/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"

// Struktur data untuk representasi waktu singkat (tanpa tanggal)
typedef struct {
    int jam;
    int menit;
    int detik;
} WaktuSingkat;

// Struktur data untuk representasi waktu lengkap
typedef struct {
    int detik;
    int menit;
    int jam;
    int hari;
    int bulan;
    int tahun;
} Waktu;

// =====================================================
// =================== KONSTRUKTOR ====================
// =====================================================

// ----- Konstruktor WaktuSingkat -----
WaktuSingkat BuatWaktuSingkat(int jam, int menit, int detik);
// Tujuan : Membuat objek waktu singkat dengan jam, menit, dan detik
// IS     : jam, menit, dan detik terdefinisi
// FS     : Mengembalikan objek WaktuSingkat yang telah diinisialisasi

WaktuSingkat WaktuSingkatSekarang();
// Tujuan : Mendapatkan waktu singkat sistem saat ini
// IS     : -
// FS     : Mengembalikan objek WaktuSingkat berdasarkan waktu sistem

// ----- Konstruktor Waktu Lengkap -----
Waktu BuatWaktu(int jam, int menit, int detik);
// Tujuan : Membuat objek waktu dengan jam, menit, dan detik
// IS     : jam, menit, dan detik terdefinisi
// FS     : Mengembalikan objek Waktu yang telah diinisialisasi

Waktu BuatWaktuLengkap(int hari, int bulan, int tahun, int jam, int menit, int detik);
// Tujuan : Membuat objek waktu dengan hari, bulan, tahun, jam, menit, dan detik
// IS     : hari, bulan, tahun, jam, menit, dan detik terdefinisi
// FS     : Mengembalikan objek Waktu yang telah diinisialisasi lengkap

Waktu WaktuSekarang();
// Tujuan : Mendapatkan waktu sistem saat ini
// IS     : -
// FS     : Mengembalikan objek Waktu berdasarkan waktu sistem

// ----- Konversi antar tipe waktu -----
WaktuSingkat KonversiKeWaktuSingkat(Waktu w);
// Tujuan : Mengkonversi Waktu lengkap menjadi WaktuSingkat
// IS     : w terdefinisi
// FS     : Mengembalikan objek WaktuSingkat dari w (tanpa tanggal)

Waktu KonversiKeWaktu(WaktuSingkat ws);
// Tujuan : Mengkonversi WaktuSingkat menjadi Waktu lengkap
// IS     : ws terdefinisi
// FS     : Mengembalikan objek Waktu dari ws (dengan tanggal 0)

// =====================================================
// ============== OPERASI PERBANDINGAN ================
// =====================================================

// ----- Perbandingan WaktuSingkat -----
boolean IsWaktuSingkatSama(WaktuSingkat w1, WaktuSingkat w2);
// Tujuan : Membandingkan kesamaan dua waktu singkat
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan true jika w1 dan w2 sama, false jika tidak

boolean IsWaktuSingkatLebihAwal(WaktuSingkat w1, WaktuSingkat w2);
// Tujuan : Mengecek apakah w1 terjadi lebih awal dari w2
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan true jika w1 lebih awal dari w2, false jika tidak

boolean IsWaktuSingkatLebihAkhir(WaktuSingkat w1, WaktuSingkat w2);
// Tujuan : Mengecek apakah w1 terjadi lebih akhir dari w2
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan true jika w1 lebih akhir dari w2, false jika tidak

int SelisihDetikWaktuSingkat(WaktuSingkat w1, WaktuSingkat w2);
// Tujuan : Menghitung selisih waktu singkat dalam detik
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan selisih waktu w1 dan w2 dalam detik

// ----- Perbandingan Waktu Lengkap -----
boolean IsWaktuSama(Waktu w1, Waktu w2);
// Tujuan : Membandingkan kesamaan dua waktu
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan true jika w1 dan w2 sama, false jika tidak

boolean IsWaktuLebihAwal(Waktu w1, Waktu w2);
// Tujuan : Mengecek apakah w1 terjadi lebih awal dari w2
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan true jika w1 lebih awal dari w2, false jika tidak

boolean IsWaktuLebihAkhir(Waktu w1, Waktu w2);
// Tujuan : Mengecek apakah w1 terjadi lebih akhir dari w2
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan true jika w1 lebih akhir dari w2, false jika tidak

int SelisihDetik(Waktu w1, Waktu w2);
// Tujuan : Menghitung selisih waktu dalam detik
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan selisih waktu w1 dan w2 dalam detik

int SelisihMenit(Waktu w1, Waktu w2);
// Tujuan : Menghitung selisih waktu dalam menit
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan selisih waktu w1 dan w2 dalam menit

int SelisihJam(Waktu w1, Waktu w2);
// Tujuan : Menghitung selisih waktu dalam jam
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan selisih waktu w1 dan w2 dalam jam

int SelisihHari(Waktu w1, Waktu w2);
// Tujuan : Menghitung selisih waktu dalam hari
// IS     : w1 dan w2 terdefinisi
// FS     : Mengembalikan selisih waktu w1 dan w2 dalam hari

// =====================================================
// =============== OPERASI ARITMATIKA =================
// =====================================================

// ----- Aritmatika WaktuSingkat -----
WaktuSingkat TambahDetikWaktuSingkat(WaktuSingkat w, int detik);
// Tujuan : Menambahkan detik ke waktu singkat
// IS     : w dan detik terdefinisi
// FS     : Mengembalikan objek WaktuSingkat setelah ditambahkan detik

WaktuSingkat TambahMenitWaktuSingkat(WaktuSingkat w, int menit);
// Tujuan : Menambahkan menit ke waktu singkat
// IS     : w dan menit terdefinisi
// FS     : Mengembalikan objek WaktuSingkat setelah ditambahkan menit

WaktuSingkat TambahJamWaktuSingkat(WaktuSingkat w, int jam);
// Tujuan : Menambahkan jam ke waktu singkat
// IS     : w dan jam terdefinisi
// FS     : Mengembalikan objek WaktuSingkat setelah ditambahkan jam

WaktuSingkat KurangDetikWaktuSingkat(WaktuSingkat w, int detik);
// Tujuan : Mengurangi detik dari waktu singkat
// IS     : w dan detik terdefinisi
// FS     : Mengembalikan objek WaktuSingkat setelah dikurangi detik

// ----- Aritmatika Waktu Lengkap -----
Waktu TambahDetik(Waktu w, int detik);
// Tujuan : Menambahkan detik ke waktu
// IS     : w dan detik terdefinisi
// FS     : Mengembalikan objek Waktu setelah ditambahkan detik

Waktu TambahMenit(Waktu w, int menit);
// Tujuan : Menambahkan menit ke waktu
// IS     : w dan menit terdefinisi
// FS     : Mengembalikan objek Waktu setelah ditambahkan menit

Waktu TambahJam(Waktu w, int jam);
// Tujuan : Menambahkan jam ke waktu
// IS     : w dan jam terdefinisi
// FS     : Mengembalikan objek Waktu setelah ditambahkan jam

Waktu TambahHari(Waktu w, int hari);
// Tujuan : Menambahkan hari ke waktu
// IS     : w dan hari terdefinisi
// FS     : Mengembalikan objek Waktu setelah ditambahkan hari

Waktu TambahBulan(Waktu w, int bulan);
// Tujuan : Menambahkan bulan ke waktu
// IS     : w dan bulan terdefinisi
// FS     : Mengembalikan objek Waktu setelah ditambahkan bulan

Waktu TambahTahun(Waktu w, int tahun);
// Tujuan : Menambahkan tahun ke waktu
// IS     : w dan tahun terdefinisi
// FS     : Mengembalikan objek Waktu setelah ditambahkan tahun

Waktu KurangDetik(Waktu w, int detik);
// Tujuan : Mengurangi detik dari waktu
// IS     : w dan detik terdefinisi
// FS     : Mengembalikan objek Waktu setelah dikurangi detik

Waktu KurangMenit(Waktu w, int menit);
// Tujuan : Mengurangi menit dari waktu
// IS     : w dan menit terdefinisi
// FS     : Mengembalikan objek Waktu setelah dikurangi menit

Waktu KurangJam(Waktu w, int jam);
// Tujuan : Mengurangi jam dari waktu
// IS     : w dan jam terdefinisi
// FS     : Mengembalikan objek Waktu setelah dikurangi jam

Waktu KurangHari(Waktu w, int hari);
// Tujuan : Mengurangi hari dari waktu
// IS     : w dan hari terdefinisi
// FS     : Mengembalikan objek Waktu setelah dikurangi hari

// =====================================================
// ============= OPERASI UTILITY ===================
// =====================================================

// ----- Utility WaktuSingkat -----
void PrintWaktuSingkat(WaktuSingkat w);
// Tujuan : Menampilkan waktu singkat dalam format standar
// IS     : w terdefinisi
// FS     : Waktu ditampilkan dalam format HH:MM:SS

boolean IsWaktuSingkatValid(int jam, int menit, int detik);
// Tujuan : Mengecek validitas waktu singkat
// IS     : jam, menit, dan detik terdefinisi
// FS     : Mengembalikan true jika waktu valid, false jika tidak

int KonversiKeDetikWaktuSingkat(WaktuSingkat w);
// Tujuan : Mengkonversi waktu singkat ke total detik
// IS     : w terdefinisi
// FS     : Mengembalikan total detik dari waktu w

WaktuSingkat KonversiDariDetikWaktuSingkat(int totalDetik);
// Tujuan : Mengkonversi total detik ke objek WaktuSingkat
// IS     : totalDetik terdefinisi
// FS     : Mengembalikan objek WaktuSingkat dari total detik

// ----- Utility Waktu Lengkap -----
void PrintWaktu(Waktu w);
// Tujuan : Menampilkan waktu dalam format standar
// IS     : w terdefinisi
// FS     : Waktu ditampilkan dalam format HH:MM:SS

void PrintWaktuLengkap(Waktu w);
// Tujuan : Menampilkan waktu dalam format lengkap
// IS     : w terdefinisi
// FS     : Waktu ditampilkan dalam format DD/MM/YYYY HH:MM:SS

boolean IsWaktuValid(int jam, int menit, int detik);
// Tujuan : Mengecek validitas waktu
// IS     : jam, menit, dan detik terdefinisi
// FS     : Mengembalikan true jika waktu valid, false jika tidak

boolean IsTanggalValid(int hari, int bulan, int tahun);
// Tujuan : Mengecek validitas tanggal
// IS     : hari, bulan, dan tahun terdefinisi
// FS     : Mengembalikan true jika tanggal valid, false jika tidak

int KonversiKeDetik(Waktu w);
// Tujuan : Mengkonversi waktu ke total detik
// IS     : w terdefinisi
// FS     : Mengembalikan total detik dari waktu w

Waktu KonversiDariDetik(int totalDetik);
// Tujuan : Mengkonversi total detik ke objek Waktu
// IS     : totalDetik terdefinisi
// FS     : Mengembalikan objek Waktu dari total detik

#endif /* TIME_H */ 