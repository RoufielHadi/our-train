/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "boolean.h"
#include "tree_non_biner.h"
#include "tree_biner.h"
#include "implementasi_morse.h"
#include "hash_password.h"
#include "implementasi_rute_kereta.h"

// Data global
Isi_Tree pohonRute;
InfoRute* infoJarak;
int jumlahRute = 0;
HashPassword* morseTree = NULL;

// Prosedur untuk membersihkan layar konsol
void clearScreen() {
    system("cls");
}

// Prosedur untuk menampilkan judul program
void tampilkanJudul() {
    printf("====================================================\n");
    printf("                    OUR TRAIN                       \n");
    printf("      SISTEM PEMESANAN TIKET KERETA API JAWA        \n");
    printf("====================================================\n\n");
}

// Prosedur untuk inisialisasi data
void inisialisasiData() {
    // Inisialisasi pohon rute kereta
    InisialisasiRuteKereta(&pohonRute);
    
    // Menambahkan informasi jarak antar stasiun (hanya contoh)
    TambahInfoRute(&infoJarak, &jumlahRute, "Jakarta Gambir", "Bandung", 173, 180);
    TambahInfoRute(&infoJarak, &jumlahRute, "Bandung", "Yogyakarta", 400, 360);
    TambahInfoRute(&infoJarak, &jumlahRute, "Yogyakarta", "Surabaya Gubeng", 330, 300);
    TambahInfoRute(&infoJarak, &jumlahRute, "Jakarta Kota", "Cirebon", 220, 210);
    TambahInfoRute(&infoJarak, &jumlahRute, "Cirebon", "Semarang Tawang", 235, 225);
    TambahInfoRute(&infoJarak, &jumlahRute, "Semarang Tawang", "Surabaya Pasar Turi", 340, 320);
    TambahInfoRute(&infoJarak, &jumlahRute, "Gadobangkong", "Padalarang", 12, 15);
    TambahInfoRute(&infoJarak, &jumlahRute, "Bandung", "Garut", 70, 90);
    
    // Inisialisasi tree Morse untuk hash password
    InisialisasiMorseCode(&morseTree);
}

// Prosedur untuk menu utama
void menuUtama() {
    int pilihan;
    char namaStasiun[100], stasiunAsal[100], stasiunTujuan[100];
    int radius;
    
    do {
        clearScreen();
        tampilkanJudul();
        printf("MENU UTAMA:\n");
        printf("1. Tampilkan Rute Kereta Api\n");
        printf("2. Cari Stasiun Terdekat\n");
        printf("3. Cari Jalur Terpendek\n");
        printf("4. Cek Ketersediaan Rute\n");
        printf("5. Tambah Stasiun Baru\n");
        printf("6. Tambah Info Jarak Rute\n");
        printf("7. Keluar\n");
        printf("\nPilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1: // Tampilkan Rute
                clearScreen();
                tampilkanJudul();
                TampilkanRute(pohonRute);
                printf("\nTekan Enter untuk kembali ke menu utama...");
                fflush(stdin);
                getch();
                break;
                
            case 2: // Cari Stasiun Terdekat
                clearScreen();
                tampilkanJudul();
                printf("Masukkan nama stasiun: ");
                fflush(stdin);
                scanf(" %[^\n]", namaStasiun);
                printf("Masukkan radius pencarian (km): ");
                scanf("%d", &radius);
                
                TampilkanStasiunTerdekat(pohonRute, infoJarak, jumlahRute, namaStasiun, radius);
                
                printf("\nTekan Enter untuk kembali ke menu utama...");
                fflush(stdin);
                getch();
                break;
                
            case 3: // Cari Jalur Terpendek
                clearScreen();
                tampilkanJudul();
                printf("Masukkan stasiun asal: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunAsal);
                printf("Masukkan stasiun tujuan: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunTujuan);
                
                TampilkanJalurTerpendek(pohonRute, infoJarak, jumlahRute, stasiunAsal, stasiunTujuan);
                
                printf("\nTekan Enter untuk kembali ke menu utama...");
                fflush(stdin);
                getch();
                break;
                
            case 4: // Cek Ketersediaan Rute
                clearScreen();
                tampilkanJudul();
                printf("Masukkan stasiun asal: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunAsal);
                printf("Masukkan stasiun tujuan: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunTujuan);
                
                if (IsRuteTersedia(pohonRute, stasiunAsal, stasiunTujuan)) {
                    printf("\nRute dari %s ke %s tersedia.\n", stasiunAsal, stasiunTujuan);
                    
                    int jarak = HitungJarak(infoJarak, jumlahRute, stasiunAsal, stasiunTujuan);
                    int waktu = HitungWaktuTempuh(infoJarak, jumlahRute, stasiunAsal, stasiunTujuan);
                    
                    if (jarak > 0 && waktu > 0) {
                        printf("Jarak: %d km\n", jarak);
                        printf("Waktu tempuh: %d menit\n", waktu);
                    } else {
                        printf("Informasi jarak dan waktu tempuh belum tersedia untuk rute ini.\n");
                    }
                } else {
                    printf("\nRute dari %s ke %s tidak tersedia.\n", stasiunAsal, stasiunTujuan);
                }
                
                printf("\nTekan Enter untuk kembali ke menu utama...");
                fflush(stdin);
                getch();
                break;
                
            case 5: // Tambah Stasiun Baru
                clearScreen();
                tampilkanJudul();
                printf("Masukkan nama stasiun baru: ");
                fflush(stdin);
                scanf(" %[^\n]", namaStasiun);
                printf("Masukkan nama stasiun induk: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunAsal);
                
                TambahStasiun(&pohonRute, namaStasiun, stasiunAsal);
                
                printf("\nTekan Enter untuk kembali ke menu utama...");
                fflush(stdin);
                getch();
                break;
                
            case 6: // Tambah Info Jarak Rute
                clearScreen();
                tampilkanJudul();
                printf("Masukkan stasiun asal: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunAsal);
                printf("Masukkan stasiun tujuan: ");
                fflush(stdin);
                scanf(" %[^\n]", stasiunTujuan);
                printf("Masukkan jarak (km): ");
                int jarak;
                scanf("%d", &jarak);
                printf("Masukkan waktu tempuh (menit): ");
                int waktuTempuh;
                scanf("%d", &waktuTempuh);
                
                TambahInfoRute(&infoJarak, &jumlahRute, stasiunAsal, stasiunTujuan, jarak, waktuTempuh);
                
                printf("\nTekan Enter untuk kembali ke menu utama...");
                fflush(stdin);
                getch();
                break;
                
            case 7: // Keluar
                printf("\nTerima kasih telah menggunakan OurTrain!\n");
                break;
                
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                printf("Tekan Enter untuk melanjutkan...");
                fflush(stdin);
                getch();
        }
    } while (pilihan != 7);
}

int main() {
    // Inisialisasi data
    inisialisasiData();
    
    // Tampilkan menu utama
    menuUtama();
    
    // Bebas memori
    for (int i = 0; i < jumlahRute; i++) {
        free(infoJarak[i].stasiunAsal);
        free(infoJarak[i].stasiunTujuan);
    }
    free(infoJarak);
    
    return 0;
} 