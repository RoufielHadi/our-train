/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_AUTHENTICATION_H
#define DASHBOARD_AUTHENTICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "hash_password.h"
#include "clear.h"

// Konstanta
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN_LENGTH 6
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_PHONE_LENGTH 15
#define MAX_ACCOUNT_NUMBER_LENGTH 20
#define MAX_BANK_NAME_LENGTH 50
#define MAX_BANK_BRANCH_LENGTH 100
#define MAX_BALANCE_LENGTH 20

// Tipe akun
#define USER_TYPE 1
#define ADMIN_TYPE 2
#define CASHIER_TYPE 3
#define MACHINE_TYPE 4

// *** PROTOTYPE FUNGSI DASHBOARD AUTHENTICATION ***

// *** TAMPILAN DASHBOARD ***
void ShowWelcomeScreen();
/* Tujuan : Menampilkan layar welcome dengan ASCII art */
/* IS      : - */
/* FS      : Layar welcome dengan ASCII art ditampilkan */

void ShowMainMenu();
/* Tujuan : Menampilkan menu utama aplikasi (Register/Login) */
/* IS      : - */
/* FS      : Menu utama aplikasi ditampilkan */

void ShowBox(const char* content);
/* Tujuan : Menampilkan kotak dengan konten di dalamnya */
/* IS      : content terdefinisi */
/* FS      : Kotak dengan konten di dalamnya ditampilkan */

// *** OTENTIKASI USER ***
boolean RegisterUser();
/* Tujuan : Mendaftarkan user baru */
/* IS      : - */
/* FS      : Data user baru disimpan ke database, mengembalikan TRUE jika berhasil */

boolean IsEmailExists(const char* email);
/* Tujuan : Memeriksa apakah email sudah terdaftar */
/* IS      : email terdefinisi */
/* FS      : Mengembalikan TRUE jika email sudah terdaftar, FALSE jika belum */

int LoginUser(char* email, char* password);
/* Tujuan : Memverifikasi login user */
/* IS      : email dan password terdefinisi */
/* FS      : Mengembalikan tipe user jika berhasil login, 0 jika gagal */

// *** FUNGSI NAVIGASI ***
void NavigateToDashboard(int userType, const char* email);
/* Tujuan : Mengarahkan user ke dashboard sesuai tipe akun */
/* IS      : userType dan email terdefinisi */
/* FS      : User diarahkan ke dashboard sesuai tipe akun */

// *** FUNGSI UTAMA ***
void RunAuthentication();
/* Tujuan : Menjalankan alur autentikasi utama */
/* IS      : - */
/* FS      : Proses autentikasi selesai dan user diarahkan ke dashboard yang sesuai */

#endif /* DASHBOARD_AUTHENTICATION_H */ 