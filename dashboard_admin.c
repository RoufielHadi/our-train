/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_admin.h"
#include "dashboard_manajemen_kereta.h"
#include "dashboard_manajemen_jadwal.h"

// *** TAMPILAN DASHBOARD ***
void ShowAdminDashboard(const char* email) {
    clearScreen();
    
    // Ambil data admin
    Record userRecord;
    InisialisasiRecord(&userRecord);
    BacaAkunUser(&userRecord, email);
    
    char* nama = AmbilNilai(&userRecord, "nama");
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|             ADMIN DASHBOARD                  |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Selamat datang, Admin %-22s |\n", nama != NULL ? nama : "");
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Manajemen User                           |\n");
    printf("|  2. Manajemen Kereta                         |\n");
    printf("|  3. Manajemen Jadwal                         |\n");
    printf("|  4. Manajemen Rute                           |\n");
    printf("|  5. Logout                                   |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU ADMIN ***
void ShowUserManagementMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|              MANAJEMEN USER                  |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowTrainManagementMenu(const char* email) {
    ShowKeretaManagementMenu(email);
}

void ShowScheduleManagementMenu(const char* email) {
    ShowJadwalManagementMenu(email);
}

void ShowRouteManagementMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|              MANAJEMEN RUTE                  |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunAdminDashboard(const char* email) {
    int choice;
    
    do {
        ShowAdminDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ShowUserManagementMenu(email);
                break;
                
            case 2:
                ShowTrainManagementMenu(email);
                break;
                
            case 3:
                ShowScheduleManagementMenu(email);
                break;
                
            case 4:
                ShowRouteManagementMenu(email);
                break;
                
            case 5:
                // Logout
                printf("\nAnda telah berhasil logout.\n");
                printf("Tekan Enter untuk kembali ke menu utama...");
                getch();
                return;
                
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getch();
                break;
        }
    } while (1);
} 