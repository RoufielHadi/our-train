#ifndef DASHBOARD_KURSI_KERETA_H
#define DASHBOARD_KURSI_KERETA_H

#include "implementasi_kursi_kereta.h"
#include "boolean.h"
#include "clear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Fungsi utama dashboard pemilihan kursi kereta
//   id_kereta            : kode kereta (misal "KA361")
//   tanggal              : tanggal perjalanan (misal "2025-06-21")
//   stasiun_awal         : nama stasiun awal
//   stasiun_akhir        : nama stasiun tujuan
//   nomor_gerbong_dipilih: output nomor gerbong yang dipilih
//   kode_kursi_dipilih   : output kode kursi (misal "A1")
void MenuKursiKereta(const char* id_kereta,
                     const char* tanggal,
                     const char* stasiun_awal,
                     const char* stasiun_akhir,
                     int* nomor_gerbong_dipilih,
                     char* kode_kursi_dipilih);

// Tampilan header/menu/footer
void TampilkanHeaderMenu(const char* judul);
void TampilkanFooterMenu();
void TungguInput();

#endif /* DASHBOARD_KURSI_KERETA_H */
