/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef IMPLEMENTASI_MORSE_H
#define IMPLEMENTASI_MORSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

// Forward declaration - gunakan void* untuk sementara
typedef struct HashPassword HashPassword;

// *** PROTOTYPE FUNGSI IMPLEMENTASI MORSE ***

// *** OPERASI DASAR MORSE CODE ***
void InisialisasiMorseCode(HashPassword **morseTree);
/* Tujuan : Menginisialisasi tree untuk kode Morse */
/* IS      : morseTree belum terdefinisi */
/* FS      : morseTree terdefinisi dengan struktur tree Morse lengkap */

char* KonversiKarakterKeMorse(HashPassword *morseTree, char karakter);
/* Tujuan : Mengkonversi karakter menjadi kode Morse */
/* IS      : morseTree sudah terdefinisi, karakter terdefinisi */
/* FS      : Mengembalikan string kode Morse untuk karakter tersebut */

char KonversiMorseKeKarakter(HashPassword *morseTree, const char *morseCode);
/* Tujuan : Mengkonversi kode Morse menjadi karakter */
/* IS      : morseTree sudah terdefinisi, morseCode terdefinisi */
/* FS      : Mengembalikan karakter yang sesuai dengan kode Morse tersebut */

char* KonversiStringKeMorse(HashPassword *morseTree, const char *teks);
/* Tujuan : Mengkonversi string menjadi kode Morse */
/* IS      : morseTree sudah terdefinisi, teks terdefinisi */
/* FS      : Mengembalikan string kode Morse untuk seluruh teks */

char* KonversiMorseKeString(HashPassword *morseTree, const char *morseCode);
/* Tujuan : Mengkonversi kode Morse menjadi string teks */
/* IS      : morseTree sudah terdefinisi, morseCode terdefinisi */
/* FS      : Mengembalikan string teks yang sesuai dengan kode Morse tersebut */

// *** OPERASI ENCODING/DECODING KHUSUS ***
char* EncodeMorse(const char *morseCode);
/* Tujuan : Mengubah kode Morse standar (. dan -) menjadi XOS */
/* IS      : morseCode berisi kode Morse standar */
/* FS      : Mengembalikan string dengan kode Morse yang dienkripsi (titik=X, strip=O, spasi=S) */

char* DecodeMorse(const char *encodedMorse);
/* Tujuan : Mengubah kode Morse XOS menjadi kode Morse standar */
/* IS      : encodedMorse berisi kode Morse terenkripsi */
/* FS      : Mengembalikan string dengan kode Morse standar (X=., O=-, S= ) */

// *** OPERASI PEMBANTU ***
HashPassword* BuatNodeMorse(char karakter);
/* Tujuan : Membuat node untuk tree Morse */
/* IS      : karakter terdefinisi */
/* FS      : Mengembalikan pointer ke node baru dengan info=karakter */

void TampilkanTabelMorse(HashPassword *root);
/* Tujuan : Menampilkan tabel kode Morse ke layar */
/* IS      : root sudah terdefinisi */
/* FS      : Tabel kode Morse ditampilkan ke layar */

// *** FUNGSI BINARY TREE MORSE ***
void BuildMorseTree(HashPassword **root);
/* Tujuan : Membangun tree Morse dengan pendekatan hardcoded */
/* IS      : root belum terdefinisi atau kosong */
/* FS      : root terisi dengan tree Morse yang komplit */

// *** FUNGSI PENCARIAN PATH ***
char* GetMorseCodeFromTree(HashPassword *root, char karakter);
/* Tujuan : Mendapatkan kode Morse dari karakter berdasarkan tree */
/* IS      : root sudah terdefinisi, karakter terdefinisi */
/* FS      : Mengembalikan string kode Morse untuk karakter tersebut */

boolean FindCharPath(HashPassword *root, char karakter, char *path, int *index, int depth);
/* Tujuan : Mencari jalur ke karakter dalam tree Morse */
/* IS      : root sudah terdefinisi, path adalah buffer untuk menyimpan jalur */
/* FS      : Mengembalikan TRUE jika karakter ditemukan dan path terisi */

// *** FUNGSI VISUALISASI TREE ***
void VisualisasiTreeMorse(HashPassword *root, int level, char *path);
/* Tujuan : Menampilkan visualisasi tree Morse dengan karakter dan jalur */
/* IS      : root sudah terdefinisi, level adalah 0, path adalah string kosong */
/* FS      : Tree ditampilkan dengan karakter dan jalur (dot dan dash) */

// *** FUNGSI STATISTIK TREE ***
int HitungKarakterDalamTree(HashPassword *root);
/* Tujuan : Menghitung jumlah karakter dalam tree Morse */
/* IS      : root sudah terdefinisi */
/* FS      : Mengembalikan jumlah karakter yang ada dalam tree */

void HitungKarakterPerKategori(HashPassword *root, int *kapital, int *kecil, int *angka, int *simbol, int *lainnya);
/* Tujuan : Menghitung jumlah karakter per kategori dalam tree Morse */
/* IS      : root sudah terdefinisi, pointer untuk setiap kategori terdefinisi */
/* FS      : Jumlah karakter per kategori terisi dengan nilai yang sesuai */

#endif /* IMPLEMENTASI_MORSE_H */ 