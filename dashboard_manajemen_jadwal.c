/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_manajemen_jadwal.h"
#include "implementasi_jadwal_kereta.h"

void ShowJadwalManagementMenu(const char* email) {
    int pilihan;
    do {
        clearScreen();
        printf("+----------------------------------------------+\n");
        printf("|             MANAJEMEN JADWAL                |\n");
        printf("+----------------------------------------------+\n");
        printf("| 1. Tampilkan Daftar Jadwal                  |\n");
        printf("| 2. Tambah Jadwal                            |\n");
        printf("| 3. Edit Jadwal                              |\n");
        printf("| 4. Hapus Jadwal                             |\n");
        printf("| 5. Kembali                                  |\n");
        printf("+----------------------------------------------+\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan); while(getchar()!='\n');
        switch (pilihan) {
            case 1:
                TampilkanDaftarJadwal();
                printf("Tekan Enter untuk kembali..."); getchar();
                break;
            case 2:
                TambahJadwal();
                break;
            case 3:
                EditJadwal();
                break;
            case 4:
                HapusJadwalDashboard();
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
