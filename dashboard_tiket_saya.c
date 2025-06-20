/*
Author: Devi Maulani 
NIM: 241524007 
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_tiket_saya.h"
#include <stdio.h>
#include <stdlib.h>
#include "clear.h"

// Fungsi untuk menampilkan menu "Tiket Saya"
void MenuTiketSaya(User user_aktif) {
    // Inisialisasi variabel TiketSaya
    TiketSaya tiketSaya;
    CreateTiketSaya(&tiketSaya);
    
    // Ambil tiket user dari file riwayat
    AmbilTiketSaya("riwayat_pemesanan.txt", user_aktif, &tiketSaya);
    
    int pilihan = 0;
    int indeks = 0;
    
    do {
        // Bersihkan layar
        clearScreen();
        
        // Tampilkan menu
        printf("+----------------------------------------------+\n");
        printf("|               TIKET SAYA                    |\n");
        printf("+----------------------------------------------+\n");
        printf("| 1. Tampilkan Tiket Saya                     |\n");
        printf("| 2. Lihat Detail Tiket                       |\n");
        printf("| 0. Kembali ke Menu Utama                    |\n");
        printf("+----------------------------------------------+\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                // Lihat semua tiket
                clearScreen();
                TampilkanTiketSaya(tiketSaya, user_aktif);
                printf("\nTekan ENTER untuk kembali...");
                getchar(); // Ambil karakter enter dari pilihan sebelumnya
                getchar(); // Tunggu hingga user menekan ENTER
                break;
                
            case 2:
                // Mode lihat detail: loop hingga user input 0 untuk kembali
                if (isEmptyStackRiwayat(tiketSaya.tiket_user)) {
                    // Jika tidak ada tiket
                    clearScreen();
                    printf("\n===== TIKET SAYA =====\n");
                    printf("%-8s: %s\n", "Email", user_aktif.email);
                    printf("========================================\n");
                    printf("Anda belum memiliki tiket!\n");
                    printf("========================================\n");
                    printf("\nTekan ENTER untuk kembali...");
                    getchar(); getchar();
                } else {
                    int pilihanDetail;
                    do {
                        // Tampilkan kembali daftar tiket
                        clearScreen();
                        TampilkanTiketSaya(tiketSaya, user_aktif);
                        // Minta indeks detail
                        printf("\nMasukkan nomor tiket untuk detail (0 untuk kembali): ");
                        scanf("%d", &pilihanDetail);
                        getchar(); // buang newline
                        if (pilihanDetail > 0) {
                            // Tampilkan detail tiket
                            clearScreen();
                            TampilkanDetailTiketSaya(tiketSaya, user_aktif, pilihanDetail);
                            printf("\nTekan ENTER untuk kembali ke daftar...");
                            getchar();
                        }
                    } while (pilihanDetail != 0);
                }
                break;
                
            case 0:
                // Kembali ke Menu Utama
                printf("Kembali ke menu utama...\n");
                break;
                
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
                printf("Tekan ENTER untuk melanjutkan...");
                getchar(); // Ambil karakter enter dari pilihan sebelumnya
                getchar(); // Tunggu hingga user menekan ENTER
        }
    } while (pilihan != 0);
    
    // Bersihkan memori
    DealokasiTiketSaya(&tiketSaya);
}