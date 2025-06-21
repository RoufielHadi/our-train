/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_cashier.h"
#include "implementasi_antrian_offline.h"
#include <time.h>

// Global queue for the cashier
Queue cashierQueue;
static char queueFilename[100]; // To store queue for this cashier

// Extract station name from email (e.g., cashier.bandung@ourtrain.id -> Bandung)
void ExtractStationNameFromEmail(const char* email, char* station) {
    const char* start = strchr(email, '.');
    if (start) {
        start++; // Skip the dot
        const char* end = strchr(start, '@');
        if (end) {
            int len = end - start;
            strncpy(station, start, len);
            station[len] = '\0';
            
            // Capitalize first letter
            if (station[0] >= 'a' && station[0] <= 'z') {
                station[0] = station[0] - 'a' + 'A';
            }
        } else {
            // If no @ found, try to extract station name anyway
            strcpy(station, start);
            // Capitalize first letter
            if (station[0] >= 'a' && station[0] <= 'z') {
                station[0] = station[0] - 'a' + 'A';
            }
        }
    } else {
        strcpy(station, "Unknown");
    }
}

// *** TAMPILAN DASHBOARD ***
void ShowCashierDashboard(const char* email) {
    clearScreen();
    
    // Ambil data kasir
    Record userRecord;
    InisialisasiRecord(&userRecord);
    BacaAkunUser(&userRecord, email);
    
    char* nama = AmbilNilai(&userRecord, "nama");
    
    // Get station name
    char station[50];
    ExtractStationNameFromEmail(email, station);
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|             CASHIER DASHBOARD                |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Selamat datang, Kasir %-22s |\n", nama != NULL ? nama : "");
    printf("| Stasiun: %-37s |\n", station);
    printf("+----------------------------------------------+\n");
    
    // Display current queue status
    printf("+----------------------------------------------+\n");
    printf("|          ANTRIAN SAAT INI                    |\n");
    printf("+----------------------------------------------+\n");
    if (!isEmptyQueue(cashierQueue)) {
        printf("| Nomor antrian sekarang: %-21d |\n", Front(cashierQueue));
        printf("| Jumlah antrian: %-29d |\n", NbElmtQueue(cashierQueue));
    } else {
        printf("| Belum ada antrian                           |\n");
    }
    printf("+----------------------------------------------+\n");
    
    printf("| Menu:                                        |\n");
    printf("|  1. Panggil Antrian Berikutnya               |\n");
    printf("|  2. Lewati Antrian                           |\n");
    printf("|  3. Tampilkan Status Antrian                 |\n");
    printf("|  4. Logout                                   |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU KASIR ***
void ShowCallNextQueueMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|         PANGGIL ANTRIAN BERIKUTNYA           |\n");
    printf("+----------------------------------------------+\n");
    
    // Get station name
    char station[50];
    ExtractStationNameFromEmail(email, station);
    
    int nomorAntrian;
    if (PanggilAntrian(&cashierQueue, &nomorAntrian)) {
        printf("\nPanggilan antrian nomor: %d\n", nomorAntrian);
        printf("Stasiun: %s\n", station);
        
        // Save queue to file
        SimpanAntrianKeFile(cashierQueue, queueFilename);
    } else {
        printf("\nTidak ada antrian yang tersedia.\n");
    }
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowSkipQueueMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             LEWATI ANTRIAN                   |\n");
    printf("+----------------------------------------------+\n");
    
    if (!isEmptyQueue(cashierQueue)) {
        int currentQueue = Front(cashierQueue);
        LewatiAntrian(&cashierQueue);
        printf("\nAntrian nomor %d dilewati.\n", currentQueue);
        
        // Save queue to file
        SimpanAntrianKeFile(cashierQueue, queueFilename);
    } else {
        printf("\nTidak ada antrian yang tersedia untuk dilewati.\n");
    }
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowQueueStatusMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             STATUS ANTRIAN                   |\n");
    printf("+----------------------------------------------+\n");
    
    // Get station name
    char station[50];
    ExtractStationNameFromEmail(email, station);
    
    printf("Stasiun: %s\n\n", station);
    
    TampilkanStatusAntrian(cashierQueue);
    
    // Show estimated service time (assuming 5 minutes per customer)
    TampilkanEstimasiWaktu(cashierQueue, 5);
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunCashierDashboard(const char* email) {
    int choice;
    // Set up queue for this cashier station
    char station[50];
    ExtractStationNameFromEmail(email, station);
    sprintf(queueFilename, "queue_%s.dat", station);
    // Initialize and load queue from file
    InisialisasiAntrianOffline(&cashierQueue);
    MuatAntrianDariFile(&cashierQueue, queueFilename);
    printf("Debug: Loading queue from %s\n", queueFilename);
    
    do {
        ShowCashierDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ShowCallNextQueueMenu(email);
                break;
                
            case 2:
                ShowSkipQueueMenu(email);
                break;
                
            case 3:
                ShowQueueStatusMenu(email);
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
