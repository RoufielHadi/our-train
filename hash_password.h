/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef HASH_PASSWORD_H
#define HASH_PASSWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "boolean.h"

// Forward declaration
typedef struct HashPassword HashPassword;

// Konstanta untuk panjang PIN
#define PIN_LENGTH 6

// *** PROTOTYPE FUNGSI HASH PASSWORD ***

// *** VALIDASI PASSWORD ***
boolean IsPasswordValid(const char *password);
/* Tujuan : Memeriksa apakah password memenuhi kriteria (huruf besar, huruf kecil, dan angka) */
/* IS      : password terdefinisi */
/* FS      : Mengembalikan TRUE jika password valid, FALSE jika tidak */

boolean IsPinValid(const char *pin);
/* Tujuan : Memeriksa apakah PIN memenuhi kriteria (6 digit angka) */
/* IS      : pin terdefinisi */
/* FS      : Mengembalikan TRUE jika PIN valid, FALSE jika tidak */

// *** HASHING PASSWORD ***
char* HashPasswordWithMorse(HashPassword *morseTree, const char *password);
/* Tujuan : Melakukan hashing password menggunakan kode Morse dengan encoding XOS */
/* IS      : morseTree dan password terdefinisi */
/* FS      : Mengembalikan string hash dari password */

char* HashPin(HashPassword *morseTree, const char *pin);
/* Tujuan : Melakukan hashing PIN menggunakan kode Morse dengan encoding XOS */
/* IS      : morseTree dan pin terdefinisi */
/* FS      : Mengembalikan string hash dari PIN */

// *** VERIFIKASI PASSWORD ***
boolean VerifyPassword(HashPassword *morseTree, const char *password, const char *hashedPassword);
/* Tujuan : Memverifikasi apakah password cocok dengan hash yang tersimpan */
/* IS      : morseTree, password, dan hashedPassword terdefinisi */
/* FS      : Mengembalikan TRUE jika password cocok, FALSE jika tidak */

boolean VerifyPin(HashPassword *morseTree, const char *pin, const char *hashedPin);
/* Tujuan : Memverifikasi apakah PIN cocok dengan hash yang tersimpan */
/* IS      : morseTree, pin, dan hashedPin terdefinisi */
/* FS      : Mengembalikan TRUE jika PIN cocok, FALSE jika tidak */

// *** FUNGSI INTERAKTIF ***
char* GetPasswordFromUser();
/* Tujuan : Meminta input password dari user dengan validasi */
/* IS      : - */
/* FS      : Mengembalikan string password yang valid */

char* GetPinFromUser();
/* Tujuan : Meminta input PIN dari user dengan validasi */
/* IS      : - */
/* FS      : Mengembalikan string PIN yang valid */

// *** MANAJEMEN PASSWORD ***
void SimpanPasswordKeFile(const char *username, const char *hashedPassword, const char *hashedPin, const char *filename);
/* Tujuan : Menyimpan username dan password yang telah di-hash ke file */
/* IS      : username, hashedPassword, hashedPin, dan filename terdefinisi */
/* FS      : Username dan password tersimpan dalam file */

boolean VerifikasiLoginFromFile(HashPassword *morseTree, const char *username, const char *password, const char *pin, const char *filename);
/* Tujuan : Memverifikasi login user berdasarkan username, password, dan PIN dari file */
/* IS      : morseTree, username, password, pin, dan filename terdefinisi */
/* FS      : Mengembalikan TRUE jika login berhasil, FALSE jika gagal */

#endif /* HASH_PASSWORD_H */ 