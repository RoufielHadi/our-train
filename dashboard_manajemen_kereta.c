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
                TampilkanDaftarKereta();
                printf("Tekan Enter untuk kembali..."); getchar();
                break;
            case 2:
                TambahKereta();
                break;
            case 3:
                EditKereta();
                break;
            case 4:
                HapusKereta();
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
