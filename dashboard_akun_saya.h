/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef DASHBOARD_AKUN_SAYA_H
#define DASHBOARD_AKUN_SAYA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "databases.h"
#include "clear.h"
#include "implementasi_akun_user.h"
#include "hash_password.h"
#include "linked.h"
#include "dashboard_authentication.h"

// *** TAMPILAN DASHBOARD AKUN SAYA ***
void ShowUserAccountDashboard(const char* email);
/* Tujuan : Menampilkan dashboard akun saya untuk user */
/* IS      : email terdefinisi */
/* FS      : Dashboard akun saya ditampilkan */

// *** MENU AKUN SAYA ***
void ShowUserProfileView(const char* email);
/* Tujuan : Menampilkan profil lengkap user */
/* IS      : email terdefinisi */
/* FS      : Profil lengkap user ditampilkan */

boolean EditUserProfile(const char* email);
/* Tujuan : Mengubah data profil user */
/* IS      : email terdefinisi */
/* FS      : Data profil user diubah, mengembalikan TRUE jika berhasil */

boolean ChangeUserPassword(const char* email);
/* Tujuan : Mengubah password user */
/* IS      : email terdefinisi */
/* FS      : Password user diubah, mengembalikan TRUE jika berhasil */

void ShowAppInformation();
/* Tujuan : Menampilkan informasi aplikasi */
/* IS      : - */
/* FS      : Informasi aplikasi ditampilkan */

void ShowHelpCenter();
/* Tujuan : Menampilkan pusat bantuan */
/* IS      : - */
/* FS      : Informasi pusat bantuan ditampilkan */

// *** FUNGSI UTAMA ***
void RunUserAccountDashboard(const char* email);
/* Tujuan : Menjalankan dashboard akun saya */
/* IS      : email terdefinisi */
/* FS      : Dashboard akun saya berjalan dan menampilkan menu-menu akun */

#endif /* DASHBOARD_AKUN_SAYA_H */ 