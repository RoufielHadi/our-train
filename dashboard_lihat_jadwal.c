/*
Author: Devi Maulani 
NIM: 241524007 
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dashboard_lihat_jadwal.h"
#include "implementasi_jadwal_kereta.h"
#include "clear.h"
#include <ctype.h>
#include "implementasi_pembelian_tiket.h"

// Fungsi untuk dashboard lihat jadwal (navigasi interface)
void ShowLihatJadwalMenu() {
    ListHasilPencarian hasil;
    InisialisasiListHasilPencarian(&hasil);
    char asal[50], tujuan[50];
    char tanggal[11];
    clearScreen();
    printf("+-----------------------------------------+\n");
    printf("|           LIHAT JADWAL KERETA           |\n");
    printf("+-----------------------------------------+\n");
    printf("Masukkan Stasiun Asal  : ");
    fgets(asal, sizeof(asal), stdin);
    asal[strcspn(asal, "\r\n")] = '\0';
    // Normalisasi input: uppercase pertama, lowercase sisanya
    int i;
    for (i = 0; asal[i]; i++) asal[i] = tolower((unsigned char)asal[i]);
    if (asal[0]) asal[0] = toupper((unsigned char)asal[0]);
    printf("Masukkan Stasiun Tujuan: ");
    fgets(tujuan, sizeof(tujuan), stdin);
    tujuan[strcspn(tujuan, "\r\n")] = '\0';
    // Normalisasi input: uppercase pertama, lowercase sisanya
    for (i = 0; tujuan[i]; i++) tujuan[i] = tolower((unsigned char)tujuan[i]);
    if (tujuan[0]) tujuan[0] = toupper((unsigned char)tujuan[0]);

    // Tambahkan input tanggal sebelum pencarian jadwal
    printf("Masukkan Tanggal (dd-mm-yyyy): ");
    fgets(tanggal, sizeof(tanggal), stdin);
    tanggal[strcspn(tanggal, "\r\n")] = '\0';

    // Pastikan data kereta telah dimuat untuk mendapatkan jenis dan harga
    if (isEmptyKereta(globalListKereta)) {
        InisialisasiListKeretaGlobal();
        MuatDataKeretaKeGlobal();
        // Tambahkan kereta dari jadwal_kereta.txt jika belum ada di daftar
        FILE* fileKereta = BukaFile(DB_JADWAL_KERETA, "r");
        if (fileKereta) {
            char line[1024];
            while (fgets(line, sizeof(line), fileKereta)) {
                char kode[20] = "";
                char* token = strtok(line, "|");
                if (token) strncpy(kode, token, sizeof(kode)-1);
                if (kode[0] && GetJenisLayananById(globalListKereta, kode) == NULL) {
                    // Tambahkan dengan data default
                    char namaDef[50]; sprintf(namaDef, "Kereta %s", kode);
                    InformasiKereta ker = BuatInformasiKereta(kode, namaDef, STR_EKONOMI, 0.0, "0");
                    TambahInformasiKereta(&globalListKereta, ker);
                }
            }
            TutupFile(fileKereta);
        }
    }
    // Cari jadwal berdasarkan rute dengan logika pembelian tiket
    if (CariTiket(&hasil, asal, tujuan, tanggal, "")) {
        clearScreen();
        TampilkanHasilPencarian(hasil);
    } else {
        printf("\nTidak ditemukan jadwal untuk rute %s ke %s.\n", asal, tujuan);
    }

    // Tunggu ENTER sebelum kembali
    printf("\nTekan ENTER untuk kembali ke menu utama...");
    getchar();

    HapusListHasilPencarian(&hasil);
}