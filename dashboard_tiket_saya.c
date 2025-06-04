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
                // Lihat detail tiket
                clearScreen();
                TampilkanTiketSaya(tiketSaya, user_aktif);
                
                if (!isEmptyStackRiwayat(tiketSaya.tiket_user)) {
                    printf("\nMasukkan nomor tiket yang ingin dilihat detailnya: ");
                    scanf("%d", &indeks);
                    
                    if (!TampilkanDetailTiket(tiketSaya, user_aktif, indeks)) {
                        printf("Gagal menampilkan detail tiket!\n");
                    }
                }
                
                printf("\nTekan ENTER untuk kembali...");
                getchar(); // Ambil karakter enter dari pilihan sebelumnya
                getchar(); // Tunggu hingga user menekan ENTER
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
