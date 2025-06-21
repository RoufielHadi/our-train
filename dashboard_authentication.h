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
#include "linked.h"

// Konstanta
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN_LENGTH 6
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_PHONE_LENGTH 15
#define MAX_ACCOUNT_NUMBER_LENGTH 20
#define MAX_BALANCE_LENGTH 20
#define MAX_BUFFER_LENGTH 256

// Tipe akun
#define USER_TYPE 1 // Pengguna biasa
#define ADMIN_TYPE 2 // Admin
#define CASHIER_TYPE 3 // Kasir
#define MACHINE_TYPE 4 // Mesin

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

boolean IsAccountNumberValid(const char *accountNumber);
/* Tujuan : Memeriksa apakah nomor rekening valid */
/* IS      : accountNumber terdefinisi */
/* FS      : Mengembalikan TRUE jika nomor rekening valid, FALSE jika tidak */

boolean IsBalanceValid(const char *balance);
/* Tujuan : Memeriksa apakah saldo valid */
/* IS      : balance terdefinisi */
/* FS      : Mengembalikan TRUE jika saldo valid, FALSE jika tidak */

int LoginUser(char* email, char* password);
/* Tujuan : Memverifikasi login user */
/* IS      : email dan password terdefinisi */
/* FS      : Mengembalikan tipe user jika berhasil login, 0 jika gagal */

boolean RegisterUserLinkedList(ListUser *userList, ListPayment *paymentList);
/* Tujuan : Mendaftarkan user baru menggunakan linked list */
/* IS      : userList dan paymentList terdefinisi */
/* FS      : Data user baru disimpan ke linked list dan database, mengembalikan TRUE jika berhasil */

boolean IsEmailExistsLinkedList(ListUser userList, const char* email);
/* Tujuan : Memeriksa apakah email sudah terdaftar menggunakan linked list */
/* IS      : userList dan email terdefinisi */
/* FS      : Mengembalikan TRUE jika email sudah terdaftar, FALSE jika belum */

int LoginUserLinkedList(ListUser userList, char* email, char* password, User* user_aktif);
/* Tujuan : Memverifikasi login user menggunakan linked list */
/* IS      : userList, email, dan password terdefinisi */
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

extern boolean logoutFlag;

#endif /* DASHBOARD_AUTHENTICATION_H */ 