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

#include "tree_biner.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan pasangan karakter dan kode Morse
typedef struct {
    char character;
    char* morseCode;
} MorseCode;

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

MorseCode* GetMorseTable();
/* Tujuan : Mendapatkan tabel kode Morse untuk semua karakter */
/* IS      : - */
/* FS      : Mengembalikan array berisi pasangan karakter dan kode Morse */

int GetMorseTableSize();
/* Tujuan : Mendapatkan ukuran tabel kode Morse */
/* IS      : - */
/* FS      : Mengembalikan jumlah entri dalam tabel kode Morse */

void TampilkanTabelMorse();
/* Tujuan : Menampilkan tabel kode Morse ke layar */
/* IS      : - */
/* FS      : Tabel kode Morse ditampilkan ke layar */

// *** FUNGSI BARU SESUAI DENGAN GITHUB REPOSITORY ***
char TraverseMorseTree(HashPassword *root, const char *code);
/* Tujuan : Melakukan traversal pada tree Morse berdasarkan kode Morse */
/* IS      : root sudah terdefinisi, code berisi kode Morse untuk satu karakter */
/* FS      : Mengembalikan karakter sesuai dengan kode Morse */

void BuildMorseTree(HashPassword **root);
/* Tujuan : Membangun tree Morse dengan pendekatan baru */
/* IS      : root belum terdefinisi atau kosong */
/* FS      : root terisi dengan tree Morse yang komplit */

void InsertIntoMorseTree(HashPassword **root, char character, const char *code);
/* Tujuan : Menyisipkan karakter ke dalam tree Morse berdasarkan kodenya */
/* IS      : root sudah terdefinisi, character dan code terdefinisi */
/* FS      : Karakter disisipkan ke dalam tree pada posisi yang sesuai */

#endif /* IMPLEMENTASI_MORSE_H */ 