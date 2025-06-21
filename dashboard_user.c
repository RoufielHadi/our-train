/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_user.h"
#include "dashboard_akun_saya.h"
#include "dashboard_rekening_saya.h"
#include "dashboard_tiket_saya.h"
#include "implementasi_akun_user.h"
#include "implementasi_pembelian_tiket.h"
#include "dashboard_lihat_jadwal.h"

// *** TAMPILAN DASHBOARD ***
void ShowUserDashboard(const char* email) {
    clearScreen();
    
    // Ambil data user
    Record userRecord;
    InisialisasiRecord(&userRecord);
    BacaAkunUser(&userRecord, email);
    
    char* nama = AmbilNilai(&userRecord, "nama");
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|             USER DASHBOARD                   |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Selamat datang, %-28s |\n", nama != NULL ? nama : "User");
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Pembelian Tiket                          |\n");
    printf("|  2. Lihat Jadwal Kereta                      |\n");
    printf("|  3. Tiket Saya                               |\n");
    printf("|  4. Akun Saya                                |\n");
    printf("|  5. Rekening Saya                            |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU USER ***
void ShowTicketPurchaseMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               PEMBELIAN TIKET                |\n");
    printf("+----------------------------------------------+\n");
    
    // Save the logged in user email before starting the ticket purchase process
    SetLoggedInUser(email);
    
    // Call the ticket search functionality
    MenuPencarianTiket();
}

void ShowTrainScheduleMenu(const char* email) {
    // Bersihkan layar dan tampilkan menu lihat jadwal
    clearScreen();
    ShowLihatJadwalMenu();
    // Tunggu user menekan ENTER sebelum kembali
    printf("\nTekan ENTER untuk kembali ke menu utama...");
    getchar(); // buang sisa input
    getchar(); // tunggu ENTER
}

// *** FUNGSI UTAMA ***
void RunUserDashboard(const char* email) {
    int choice;
    User user_aktif;
    // Set current user's email for ticket retrieval
    memset(&user_aktif, 0, sizeof(User));
    strcpy(user_aktif.email, email);
    
    do {
        ShowUserDashboard(email);
        // Baca pilihan user sebagai string dan konversi ke integer
        char input[10];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            choice = atoi(input);
        } else {
            choice = 0;
        }
        
        switch (choice) {
            case 1:
                ShowTicketPurchaseMenu(email);
                break;
                
            case 2:
                ShowTrainScheduleMenu(email);
                break;
                
            case 3:
                MenuTiketSaya(user_aktif);
                break;
                
            case 4:
                RunUserAccountDashboard(email);
                if (logoutFlag) {
                    logoutFlag = FALSE;
                    return;
                }
                break;
                
            case 5:
                RunUserBankDashboard(email);
                break;
                
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getch();
                break;
        }
    } while (1);
} 