/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_machine.h"

// *** TAMPILAN DASHBOARD ***
void ShowMachineDashboard(const char* email) {
    clearScreen();
    
    // Ambil data mesin
    Record userRecord;
    InisialisasiRecord(&userRecord);
    BacaAkunUser(&userRecord, email);
    
    char* nama = AmbilNilai(&userRecord, "nama");
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|             MACHINE DASHBOARD                |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Mesin ID: %-34s |\n", nama != NULL ? nama : email);
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Cetak Tiket                              |\n");
    printf("|  2. Pemindaian Tiket                         |\n");
    printf("|  3. Status Mesin                             |\n");
    printf("|  4. Logout                                   |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU MESIN ***
void ShowTicketPrintingMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               CETAK TIKET                    |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowTicketScanningMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             PEMINDAIAN TIKET                 |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowMachineStatusMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               STATUS MESIN                   |\n");
    printf("+----------------------------------------------+\n");
    printf("| Status: Online                               |\n");
    printf("| ID Mesin: %-35s |\n", email);
    printf("| Lokasi: Terminal Tiket                       |\n");
    printf("| Versi Perangkat Lunak: 1.0.0                 |\n");
    printf("| Status Kertas: Tersedia                      |\n");
    printf("| Status Koneksi: Terhubung                    |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunMachineDashboard(const char* email) {
    int choice;
    
    do {
        ShowMachineDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ShowTicketPrintingMenu(email);
                break;
                
            case 2:
                ShowTicketScanningMenu(email);
                break;
                
            case 3:
                ShowMachineStatusMenu(email);
                break;
                
            case 4:
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