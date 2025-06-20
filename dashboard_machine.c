/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_machine.h"
#include "implementasi_antrian_offline.h"
#include "implementasi_tiket_saya.h"
#include "time.h"
#include <time.h>

// Global queue for the machine to store customer queue
Queue machineQueue;
static char queueFilename[100]; // To store queue for this machine

// Extract station name from email (e.g., machine.bandung@ourtrain.id -> Bandung)
void ExtractStationFromEmail(const char* email, char* station) {
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
void ShowMachineDashboard(const char* email) {
    clearScreen();
    
    // Ambil data mesin
    Record userRecord;
    InisialisasiRecord(&userRecord);
    BacaAkunUser(&userRecord, email);
    
    char* nama = AmbilNilai(&userRecord, "nama");
    
    // Get station name
    char station[50];
    ExtractStationFromEmail(email, station);
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|             DASHBOARD MESIN                  |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("\n");
    printf("+----------------------------------------------+\n");
    printf("|         TAMPILAN ANTRIAN SEKARANG            |\n");
    printf("+----------------------------------------------+\n");
    
    // Show current queue number
    if (!isEmptyQueue(machineQueue)) {
        printf("| Nomor antrian saat ini: %-20d |\n", Front(machineQueue));
    } else {
        printf("| Belum ada antrian                          |\n");
    }
    printf("+----------------------------------------------+\n");
    
    printf("\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Ambil Antrian                            |\n");
    printf("|  2. Pindai Tiket                             |\n");
    printf("|  3. Lihat Kereta Hari Ini                    |\n");
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

// Get tickets for a user in the next 24 hours
void ShowTicketScanningMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             PEMINDAIAN TIKET                 |\n");
    printf("+----------------------------------------------+\n");
    
    char userEmail[100];
    printf("Masukkan email pengguna: ");
    scanf("%s", userEmail);
    
    // Create a user struct
    User user;
    strcpy(user.email, userEmail);
    
    // Initialize tiket saya
    TiketSaya tiketSaya;
    CreateTiketSaya(&tiketSaya);
    
    // Get tickets from file
    AmbilTiketSaya("riwayat_pemesanan.txt", user, &tiketSaya);
    
    // Get current time
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    
    // Create time 24 hours from now
    time_t tomorrow = now + (24 * 60 * 60);
    struct tm *tomorrow_time = localtime(&tomorrow);
    
    Waktu current_waktu = {current_time->tm_sec, current_time->tm_min, current_time->tm_hour, 
                          current_time->tm_mday, current_time->tm_mon + 1, current_time->tm_year + 1900};
    Waktu tomorrow_waktu = {tomorrow_time->tm_sec, tomorrow_time->tm_min, tomorrow_time->tm_hour, 
                           tomorrow_time->tm_mday, tomorrow_time->tm_mon + 1, tomorrow_time->tm_year + 1900};
    
    // Filter and display tickets in the next 24 hours
    printf("\nTiket dalam 24 jam ke depan:\n");
    printf("+----+----------------+----------------------+----------+\n");
    printf("| No | ID Kereta      | Nama Kereta          | Jadwal   |\n");
    printf("+----+----------------+----------------------+----------+\n");
    
    int count = 0;
    if (!isEmptyStackRiwayat(tiketSaya.tiket_user)) {
        addressRiwayat p = tiketSaya.tiket_user.top;
        int index = 1;
        
        while (p != NULL) {
            RiwayatTiket tiket = p->info;
            
            // Check if the ticket is within the next 24 hours
            // For this simple implementation, we're just checking if the ticket time is between now and tomorrow
            if ((!IsWaktuLebihAwal(tiket.riwayat_waktu_pemesanan, current_waktu) || IsWaktuSama(tiket.riwayat_waktu_pemesanan, current_waktu)) && 
                (IsWaktuLebihAwal(tiket.riwayat_waktu_pemesanan, tomorrow_waktu) || IsWaktuSama(tiket.riwayat_waktu_pemesanan, tomorrow_waktu))) {
                
                printf("| %-2d | %-14s | %-20s | %02d:%02d    |\n", 
                    index, 
                    tiket.riwayat_kereta.kode_kereta, 
                    tiket.riwayat_kereta.nama_kereta,
                    tiket.riwayat_waktu_pemesanan.jam,
                    tiket.riwayat_waktu_pemesanan.menit);
                count++;
            }
            
            p = p->next;
            index++;
        }
    }
    
    if (count == 0) {
        printf("| Tidak ada tiket dalam 24 jam ke depan         |\n");
    }
    
    printf("+----+----------------+----------------------+----------+\n");
    
    // Clean up
    DealokasiTiketSaya(&tiketSaya);
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// Show all trains stopping at this station today
void ShowTrainsForTodayMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|             KERETA HARI INI                  |\n");
    printf("+----------------------------------------------+\n");
    
    // Extract station name from email
    char station[50];
    ExtractStationFromEmail(email, station);
    
    printf("Stasiun: %s\n\n", station);
    
    FILE* f = fopen("jadwal_kereta.txt", "r");
    if (!f) {
        printf("Error: tidak dapat membuka file jadwal_kereta.txt\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    printf("Kereta yang berhenti di %s hari ini:\n", station);
    printf("+------+----------------+----------------------+----------+-------------+\n");
    printf("| No.  | ID Kereta      | Nama Kereta          | Jadwal   | Tujuan Akhir|\n");
    printf("+------+----------------+----------------------+----------+-------------+\n");
    
    char line[1024];
    int count = 0;
    
    while (fgets(line, sizeof(line), f)) {
        char tmp[1024];
        strcpy(tmp, line);
        char* id = strtok(tmp, "|");
        char* stops = strtok(NULL, "|");
        char* times = strtok(NULL, "\n");
        
        if (stops) {
            char stopsCopy[512], timesCopy[512];
            strcpy(stopsCopy, stops);
            strcpy(timesCopy, times ? times : "");
            
            // Parse stops and find station
            char* tok = strtok(stopsCopy, ",");
            int stationIndex = -1, i = 0;
            
            while (tok) {
                while (*tok == ' ') tok++;
                char* end = tok + strlen(tok) - 1;
                while (end > tok && (*end == '\n' || *end == '\r' || *end == ' ')) {
                    *end = '\0';
                    end--;
                }
                
                // Case insensitive compare
                if (strcasecmp(tok, station) == 0) {
                    stationIndex = i;
                    break;
                }
                
                tok = strtok(NULL, ",");
                i++;
            }
            
            // If station found, get schedule
            if (stationIndex >= 0 && times) {
                // Get time for this station
                strcpy(timesCopy, times);
                char* timeTok = strtok(timesCopy, ",");
                char stationTime[20] = "?";
                
                for (i = 0; timeTok != NULL && i <= stationIndex; i++) {
                    while (*timeTok == ' ') timeTok++;
                    char* end = timeTok + strlen(timeTok) - 1;
                    while (end > timeTok && (*end == '\n' || *end == '\r' || *end == ' ')) {
                        *end = '\0';
                        end--;
                    }
                    
                    if (i == stationIndex) {
                        strcpy(stationTime, timeTok);
                    }
                    
                    timeTok = strtok(NULL, ",");
                }
                
                // Get last station as destination
                strcpy(stopsCopy, stops);
                char lastStation[50] = "?";
                tok = strtok(stopsCopy, ",");
                while (tok) {
                    while (*tok == ' ') tok++;
                    char* end = tok + strlen(tok) - 1;
                    while (end > tok && (*end == '\n' || *end == '\r' || *end == ' ')) {
                        *end = '\0';
                        end--;
                    }
                    
                    strcpy(lastStation, tok);
                    tok = strtok(NULL, ",");
                }
                
                // Get train info
                Record infoKereta;
                InisialisasiRecord(&infoKereta);
                char namaKeretaBuf[50] = "-";
                
                if (BacaInformasiKereta(&infoKereta, id)) {
                    char* namaVal = AmbilNilai(&infoKereta, "namaKereta");
                    if (namaVal) strncpy(namaKeretaBuf, namaVal, sizeof(namaKeretaBuf)-1);
                }
                
                count++;
                printf("| %-4d | %-14s | %-20s | %-8s | %-11s |\n", 
                       count, id, namaKeretaBuf, stationTime, lastStation);
            }
        }
    }
    
    fclose(f);
    
    if (count == 0) {
        printf("| Tidak ada kereta yang berhenti di %s hari ini     |\n", station);
    }
    
    printf("+------+----------------+----------------------+----------+-------------+\n");
    
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

// Function to take a queue number
void TakeQueueNumber(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               AMBIL ANTRIAN                  |\n");
    printf("+----------------------------------------------+\n");
    
    // Get station name for queue ID
    char station[50];
    ExtractStationFromEmail(email, station);
    
    // Take a new queue number
    int queueNumber = AmbilNomorAntrian(&machineQueue);
    
    printf("\nAnda telah mengambil nomor antrian: %d\n", queueNumber);
    printf("Stasiun: %s\n", station);
    
    // Save queue to file
    SimpanAntrianKeFile(machineQueue, queueFilename);
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunMachineDashboard(const char* email) {
    int choice;
    // Set up queue for this machine station
    char station[50];
    ExtractStationFromEmail(email, station);
    sprintf(queueFilename, "queue_%s.dat", station);
    // Initialize and load queue from file
    InisialisasiAntrianOffline(&machineQueue);
    MuatAntrianDariFile(&machineQueue, queueFilename);
    printf("Debug: Loading queue from %s\n", queueFilename);
    
    do {
        ShowMachineDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                TakeQueueNumber(email);
                break;
                
            case 2:
                ShowTicketScanningMenu(email);
                break;
                
            case 3:
                ShowTrainsForTodayMenu(email);
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
