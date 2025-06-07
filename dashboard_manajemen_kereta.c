/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_manajemen_kereta.h"
#include "implementasi_informasi_kereta.h"

// Implementasi fungsi-fungsi yang digunakan di dashboard
void DashboardTampilkanDaftarKereta() {
    printf("\nDaftar Kereta Api:\n");
    printf("Fitur ini akan tersedia dalam versi selanjutnya.\n");
}

void DashboardTambahKereta() {
    printf("\nMenambahkan Kereta Baru:\n");
    printf("Fitur ini akan tersedia dalam versi selanjutnya.\n");
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

void DashboardEditKereta() {
    printf("\nMengubah Data Kereta:\n");
    printf("Fitur ini akan tersedia dalam versi selanjutnya.\n");
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

void DashboardHapusKereta() {
    printf("\nMenghapus Kereta:\n");
    printf("Fitur ini akan tersedia dalam versi selanjutnya.\n");
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

// Fungsi-fungsi wrapper untuk fungsi-fungsi di implementasi_informasi_kereta.h
void ShowDaftarKereta() {
    DashboardTampilkanDaftarKereta();
}

void ShowTambahKereta() {
    DashboardTambahKereta();
}

void ShowEditKereta() {
    DashboardEditKereta();
}

void ShowHapusKereta() {
    DashboardHapusKereta();
}

void ShowKeretaManagementMenu(const char* email) {
    int pilihan;
    do {
        clearScreen();
        printf("+----------------------------------------------+\n");
        printf("|             MANAJEMEN KERETA                |\n");
        printf("+----------------------------------------------+\n");
        printf("| 1. Tampilkan Daftar Kereta                  |\n");
        printf("| 2. Tambah Kereta                            |\n");
        printf("| 3. Edit Kereta                              |\n");
        printf("| 4. Hapus Kereta                             |\n");
        printf("| 5. Kembali                                  |\n");
        printf("+----------------------------------------------+\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan); while(getchar()!='\n');
        switch (pilihan) {
            case 1:
                ShowDaftarKereta();
                printf("Tekan Enter untuk kembali..."); getchar();
                break;
            case 2:
                ShowTambahKereta();
                break;
            case 3:
                ShowEditKereta();
                break;
            case 4:
                ShowHapusKereta();
                break;
            case 5:
                return;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
        }
    } while (1);
}
