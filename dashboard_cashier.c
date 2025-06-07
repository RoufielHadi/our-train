/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_cashier.h"

// *** TAMPILAN DASHBOARD ***
void ShowCashierDashboard(const char* email) {
    clearScreen();
    
    // Ambil data kasir
    Record userRecord;
    InisialisasiRecord(&userRecord);
    BacaAkunUser(&userRecord, email);
    
    char* nama = AmbilNilai(&userRecord, "nama");
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|             CASHIER DASHBOARD                |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Selamat datang, Kasir %-22s |\n", nama != NULL ? nama : "");
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Penjualan Tiket                          |\n");
    printf("|  2. Verifikasi Tiket                         |\n");
    printf("|  3. Laporan Penjualan                        |\n");
    printf("|  4. Logout                                   |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU KASIR ***
void ShowTicketSalesMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|              PENJUALAN TIKET                 |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowTicketVerificationMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             VERIFIKASI TIKET                 |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowSalesReportMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             LAPORAN PENJUALAN                |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunCashierDashboard(const char* email) {
    int choice;
    
    do {
        ShowCashierDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ShowTicketSalesMenu(email);
                break;
                
            case 2:
                ShowTicketVerificationMenu(email);
                break;
                
            case 3:
                ShowSalesReportMenu(email);
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