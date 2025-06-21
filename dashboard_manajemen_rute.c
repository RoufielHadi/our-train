/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_manajemen_rute.h"
#include "implementasi_rute_kereta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "databases.h"

#define FILE_RUTE "rute_kereta.txt"

// Helper untuk perbandingan case-insensitive
int equalsIgnoreCase(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

// Helper to normalize station name: first letter uppercase, rest lowercase
static void NormalizeNameLocal(char* s) {
    if (!s || !*s) return;
    s[0] = toupper((unsigned char)s[0]);
    int i;
    for (i = 1; s[i]; i++) {
        s[i] = tolower((unsigned char)s[i]);
    }
}

// Fungsi untuk mengganti nama stasiun di file rute_kereta.txt
void RenameStationInFile(const char* oldNameParam, const char* newNameParam) {
    // Normalize names for comparison and storage
    char oldName[50]; strcpy(oldName, oldNameParam); NormalizeNameLocal(oldName);
    char newName[50]; strcpy(newName, newNameParam); NormalizeNameLocal(newName);
    
    FILE* file = fopen(FILE_RUTE, "r");
    if (!file) { printf("Error: tidak dapat membuka file %s\n", FILE_RUTE); return; }
    FILE* tmp = fopen("rute_kereta.tmp", "w");
    if (!tmp) { printf("Error: tidak dapat membuka file sementara\n"); fclose(file); return; }
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        char nameBuf[100], statusBuf[10];
        int pr, nb, fs, indext;
        if (sscanf(buffer, "\"nama\"='%[^']' | \"status\"=%[^ ] | %d | %d | %d | %d", nameBuf, statusBuf, &pr, &nb, &fs, &indext) == 6) {
            if (equalsIgnoreCase(nameBuf, oldName)) {
                fprintf(tmp, "\"nama\"='%s' | \"status\"=%s | %d | %d | %d | %d\n", newName, statusBuf, pr, nb, fs, indext);
                continue;
            }
        }
        fputs(buffer, tmp);
    }
    fclose(file);
    fclose(tmp);
    remove(FILE_RUTE);
    rename("rute_kereta.tmp", FILE_RUTE);
    printf("Nama stasiun berhasil diubah dari %s ke %s.\n", oldName, newName);
}

// Fungsi untuk mengubah status stasiun di file rute_kereta.txt
void EditStatusStationInFile(const char* nameParam, boolean status) {
    char name[50]; strcpy(name, nameParam); NormalizeNameLocal(name);
    FILE* file = fopen(FILE_RUTE, "r");
    if (!file) { printf("Error: tidak dapat membuka file %s\n", FILE_RUTE); return; }
    FILE* tmp = fopen("rute_kereta.tmp", "w");
    if (!tmp) { printf("Error: tidak dapat membuka file sementara\n"); fclose(file); return; }
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        char nameBuf[100], statusBuf[10];
        int pr, nb, fs, indext;
        if (sscanf(buffer, "\"nama\"='%[^']' | \"status\"=%[^ ] | %d | %d | %d | %d", nameBuf, statusBuf, &pr, &nb, &fs, &indext) == 6) {
            if (equalsIgnoreCase(nameBuf, name)) {
                fprintf(tmp, "\"nama\"='%s' | \"status\"=%s | %d | %d | %d | %d\n", name, status ? "TRUE" : "FALSE", pr, nb, fs, indext);
                continue;
            }
        }
        fputs(buffer, tmp);
    }
    fclose(file);
    fclose(tmp);
    remove(FILE_RUTE);
    rename("rute_kereta.tmp", FILE_RUTE);
    printf("Status stasiun %s berhasil diubah menjadi %s.\n", name, status ? "TRUE" : "FALSE");
}

// Menu Manajemen Rute untuk Admin
void MenuManajemenRuteAdmin(const char* email) {
    int pilihan;
    Isi_Tree pohonRute;
    // Muat data stasiun ke tree (menggunakan status aktif dari file)
    BacaDataStasiun(pohonRute);
    
    do {
        clearScreen();
        printf("+-------------------------------+\n");
        printf("| MANAJEMEN RUTE (ADMIN SIDE)  |\n");
        printf("+-------------------------------+\n");
        printf("1. Cek Seluruh Rute Kereta\n");
        printf("2. Cek Stasiun Aktif\n");
        printf("3. Edit Nama Stasiun\n");
        printf("4. Edit Status Stasiun\n");
        printf("5. Uji Coba Fitur Rute User\n");
        printf("6. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch(pilihan) {
            case 1: {
                // Cek seluruh rute antara dua stasiun (tampilkan nama + status)
                char origin[50], destination[50];
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "CEK SELURUH RUTE");
                printf("+----------------------------------------------+\n");
                printf("Masukkan stasiun asal   : ");
                fgets(origin, sizeof(origin), stdin); origin[strcspn(origin, "\n")] = '\0';
                NormalizeNameLocal(origin);
                printf("Masukkan stasiun tujuan : ");
                fgets(destination, sizeof(destination), stdin); destination[strcspn(destination, "\n")] = '\0';
                NormalizeNameLocal(destination);
                // Dapatkan jalur lengkap
                char routeNames[jml_maks+1][50];
                int routeLen = GetRouteStations(origin, destination, routeNames, jml_maks+1);
                if (routeLen <= 2) {
                    printf("Tidak ada rute antara %s dan %s.\n", origin, destination);
                } else {
                    printf("\nStasiun antara %s dan %s:\n", origin, destination);
                    printf("+----+------------------------+------------+\n");
                    printf("| No | Nama Stasiun           | Status     |\n");
                    printf("+----+------------------------+------------+\n");
                    int cnt = 0;
                    int i;
                    for (i = 1; i < routeLen - 1; i++) {
                        char nameBuf[50];
                        int idx = CariIndeksStasiun(pohonRute, routeNames[i]);
                        boolean active = FALSE;
                        if (idx > 0) active = IsStationActiveAndName(idx, nameBuf);
                        if (!active) strcpy(nameBuf, routeNames[i]);
                        printf("| %2d | %-22s | %-10s |\n", ++cnt, nameBuf, active ? "Aktif" : "Tidak Aktif");
                    }
                    printf("+----+------------------------+------------+\n");
                }
                printf("\nTekan Enter untuk kembali..."); getchar();
                break;
            }
            case 2: {
                // Cek stasiun aktif antara dua stasiun
                char origin[50], destination[50];
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "CEK STASIUN AKTIF");
                printf("+----------------------------------------------+\n");
                printf("Masukkan stasiun asal   : ");
                fgets(origin, sizeof(origin), stdin); origin[strcspn(origin, "\n")] = '\0';
                NormalizeNameLocal(origin);
                printf("Masukkan stasiun tujuan : ");
                fgets(destination, sizeof(destination), stdin); destination[strcspn(destination, "\n")] = '\0';
                NormalizeNameLocal(destination);
                printf("\nStasiun aktif antara %s dan %s:\n", origin, destination);
                printf("+----+------------------------+\n");
                printf("| No | Nama Stasiun           |\n");
                printf("+----+------------------------+\n");
                // Filter active stations between origin and destination
                {
                    char routeNames[jml_maks+1][50];
                    int routeLen = GetRouteStations(origin, destination, routeNames, jml_maks+1);
                    int cnt = 0;
                    int i;
                    for (i = 1; i < routeLen - 1; i++) {
                        char nameBuf[50];
                        int idx = CariIndeksStasiun(pohonRute, routeNames[i]);
                        if (idx > 0 && IsStationActiveAndName(idx, nameBuf)) {
                            printf("| %2d | %-22s |\n", ++cnt, nameBuf);
                        }
                    }
                    if (cnt == 0) {
                        printf("Tidak ada stasiun aktif antara %s dan %s.\n", origin, destination);
                    }
                    printf("+----+------------------------+\n");
                }
                printf("\nTekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 3: {
                // Edit nama stasiun
                char oldName[50], newName[50];
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "EDIT NAMA STASIUN");
                printf("+----------------------------------------------+\n");
                printf("Masukkan nama stasiun lama : ");
                fgets(oldName, sizeof(oldName), stdin); oldName[strcspn(oldName, "\n")] = '\0';
                NormalizeNameLocal(oldName);
                printf("Masukkan nama stasiun baru : ");
                fgets(newName, sizeof(newName), stdin); newName[strcspn(newName, "\n")] = '\0';
                NormalizeNameLocal(newName);
                RenameStationInFile(oldName, newName);
                printf("Tekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 4: {
                // Edit status stasiun
                char name[50];
                int s;
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "EDIT STATUS STASIUN");
                printf("+----------------------------------------------+\n");
                printf("Masukkan nama stasiun        : ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = '\0';
                NormalizeNameLocal(name);
                printf("Masukkan status baru (1=aktif,0=nonaktif): ");
                scanf("%d", &s); getchar();
                EditStatusStationInFile(name, s ? TRUE : FALSE);
                printf("Tekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 5:
                // Uji Coba Fitur Rute User
                MenuManajemenRuteUser(email);
                break;
            case 6:
                // Kembali ke dashboard admin
                break;
            default:
                printf("\nPilihan tidak valid!");
                printf("\nTekan Enter untuk kembali...");
                getchar();
                break;
        }
    } while(pilihan != 6);
}

// Menu Manajemen Rute untuk User (Cek rute kereta)
void MenuManajemenRuteUser(const char* email) {
    int pilihan;
    Isi_Tree pohonRute;
    // Muat data stasiun dan koneksi dari file
    BacaDataStasiun(pohonRute);
    
    do {
        clearScreen();
        printf("+-------------------------------+\n");
        printf("| MANAJEMEN RUTE (USER SIDE)   |\n");
        printf("+-------------------------------+\n");
        printf("1. Cek Kereta yang berhenti di stasiun\n");
        printf("2. Cek Stasiun Aktif\n");
        printf("3. Cek Jalur yang dilalui kereta\n");
        printf("4. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch(pilihan) {
            case 1: {
                // Cek kereta yang berhenti di stasiun
                char station[50];
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "CEK KERETA YANG BERHENTI DI STASIUN");
                printf("+----------------------------------------------+\n");
                printf("Masukkan nama stasiun: ");
                fgets(station, sizeof(station), stdin); station[strcspn(station, "\n")] = '\0';
                FILE* f = fopen("jadwal_kereta.txt", "r");
                if (!f) {
                    printf("Error: tidak dapat membuka file jadwal_kereta.txt\n");
                    printf("Tekan Enter untuk kembali...");
                    getchar();
                    break;
                }
                printf("\nKereta yang berhenti di %s:\n", station);
                printf("+------+----------------+----------------------+--------------+--------+\n");
                printf("| No.  | ID Kereta       | Nama Kereta          | Layanan      | Harga  |\n");
                printf("+------+----------------+----------------------+--------------+--------+\n");
                int count = 0;
                char line[1024];
                while (fgets(line, sizeof(line), f)) {
                    char tmp[1024];
                    strcpy(tmp, line);
                    char* id = strtok(tmp, "|");
                    char* stops = strtok(NULL, "|");
                    if (stops) {
                        char stopsCopy[512]; strcpy(stopsCopy, stops);
                        char* tok = strtok(stopsCopy, ",");
                        while (tok) {
                            while (*tok == ' ') tok++;
                            char* end = tok + strlen(tok) - 1;
                            while (end > tok && (*end == '\n' || *end == '\r')) { *end = '\0'; end--; }
                            if (equalsIgnoreCase(tok, station)) {
                                // Load train info
                                Record infoKereta; InisialisasiRecord(&infoKereta);
                                char namaKeretaBuf[50] = "-", layananBuf[20] = "-", hargaBuf[20] = "-";
                                if (BacaInformasiKereta(&infoKereta, id)) {
                                    char* namaVal = AmbilNilai(&infoKereta, "namaKereta");
                                    char* layananVal = AmbilNilai(&infoKereta, "jenisLayanan");
                                    char* hargaVal = AmbilNilai(&infoKereta, "harga");
                                    if (namaVal) strncpy(namaKeretaBuf, namaVal, sizeof(namaKeretaBuf)-1);
                                    if (layananVal) strncpy(layananBuf, layananVal, sizeof(layananBuf)-1);
                                    if (hargaVal) strncpy(hargaBuf, hargaVal, sizeof(hargaBuf)-1);
                                }
                                int no = ++count;
                                printf("| %-4d | %-14s | %-20s | %-12s | %-6s |\n", no, id, namaKeretaBuf, layananBuf, hargaBuf);
                                break;
                            }
                            tok = strtok(NULL, ",");
                        }
                    }
                }
                fclose(f);
                printf("+------+----------------+----------------------+--------------+--------+\n");
                if (count == 0) {
                    printf("Tidak ada kereta yang berhenti di %s.\n", station);
                }
                printf("Tekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 2: {
                // Cek stasiun aktif antara dua stasiun
                char origin[50], destination[50];
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "CEK STASIUN AKTIF");
                printf("+----------------------------------------------+\n");
                printf("Masukkan stasiun asal   : ");
                fgets(origin, sizeof(origin), stdin); origin[strcspn(origin, "\n")] = '\0';
                NormalizeNameLocal(origin);
                printf("Masukkan stasiun tujuan : ");
                fgets(destination, sizeof(destination), stdin); destination[strcspn(destination, "\n")] = '\0';
                NormalizeNameLocal(destination);
                printf("\nStasiun aktif antara %s dan %s:\n", origin, destination);
                printf("+----+------------------------+\n");
                printf("| No | Nama Stasiun           |\n");
                printf("+----+------------------------+\n");
                // Filter active stations between origin and destination
                {
                    char routeNames[jml_maks+1][50];
                    int routeLen = GetRouteStations(origin, destination, routeNames, jml_maks+1);
                    int cnt = 0;
                    int i;
                    for (i = 1; i < routeLen - 1; i++) {
                        char nameBuf[50];
                        int idx = CariIndeksStasiun(pohonRute, routeNames[i]);
                        if (idx > 0 && IsStationActiveAndName(idx, nameBuf)) {
                            printf("| %2d | %-22s |\n", ++cnt, nameBuf);
                        }
                    }
                    if (cnt == 0) {
                        printf("Tidak ada stasiun aktif antara %s dan %s.\n", origin, destination);
                    }
                    printf("+----+------------------------+\n");
                }
                printf("\nTekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 3: {
                // cek jalur kereta antara 2 stasiun
                char origin[50], destination[50];
                clearScreen();
                printf("+----------------------------------------------+\n");
                printf("| %-44s |\n", "CEK JALUR KERETA (HANYA STASIUN AKTIF)");
                printf("+----------------------------------------------+\n");
                printf("Masukkan stasiun asal   : ");
                fgets(origin, sizeof(origin), stdin); origin[strcspn(origin, "\n")] = '\0';
                NormalizeNameLocal(origin);
                printf("Masukkan stasiun tujuan : ");
                fgets(destination, sizeof(destination), stdin); destination[strcspn(destination, "\n")] = '\0';
                NormalizeNameLocal(destination);
                char routeNames[jml_maks+1][50];
                int routeLen = GetRouteStations(origin, destination, routeNames, jml_maks+1);
                // filter aktif
                char activeRoutes[200][50];
                int activeCount = 0;
                int i;
                for (i = 0; i < routeLen; i++) {
                    int idx = CariIndeksStasiun(pohonRute, routeNames[i]);
                    char tmpName[50];
                    if (IsStationActiveAndName(idx, tmpName)) {
                        strcpy(activeRoutes[activeCount++], routeNames[i]);
                    }
                }
                if (activeCount == 0) {
                    printf("Tidak ada rute aktif antara %s dan %s.\n", origin, destination);
                    printf("Tekan Enter untuk kembali...");
                    getchar();
                    break;
                }
                FILE* f = fopen("jadwal_kereta.txt", "r");
                if (!f) {
                    printf("Error: tidak dapat membuka file jadwal_kereta.txt\n");
                    printf("Tekan Enter untuk kembali...");
                    getchar();
                    break;
                }
                char line[1024];
                int trainFound = 0;
                while (fgets(line, sizeof(line), f)) {
                    char tmp[1024];
                    strcpy(tmp, line);
                    char* id = strtok(tmp, "|");
                    char* stops = strtok(NULL, "|");
                    char* times = strtok(NULL, "\n");
                    if (!id || !stops || !times) continue;
                    // parse stops and times
                    char stopsCopy[512], timesCopy[512];
                    strcpy(stopsCopy, stops);
                    strcpy(timesCopy, times);
                    char stopList[200][50], timeList[200][20];
                    int stopCount = 0, timeCount = 0;
                    char* tok = strtok(stopsCopy, ",");
                    while (tok) {
                        char* st = tok; while (*st == ' ') st++;
                        char* en = st + strlen(st) - 1; while (en > st && (*en == ' ' || *en == '\r' || *en == '\n')) { *en = '\0'; en--; }
                        strcpy(stopList[stopCount++], st);
                        tok = strtok(NULL, ",");
                    }
                    tok = strtok(timesCopy, ",");
                    while (tok) {
                        char* st = tok; while (*st == ' ') st++;
                        char* en = st + strlen(st) - 1; while (en > st && (*en == ' ' || *en == '\r' || *en == '\n')) { *en = '\0'; en--; }
                        strcpy(timeList[timeCount++], st);
                        tok = strtok(NULL, ",");
                    }
                    // find origin and dest positions in stopList
                    int originPos = -1, destPos = -1;
                    int i;
                    for (i = 0; i < stopCount; i++) {
                        if (equalsIgnoreCase(stopList[i], origin)) originPos = i;
                        if (equalsIgnoreCase(stopList[i], destination)) destPos = i;
                    }
                    if (originPos >= 0 && destPos >= 0 && originPos < destPos) {
                        if (trainFound > 0) printf("\n----------------------------------------\n");
                        // Load train info to display train name
                        Record infoKereta; InisialisasiRecord(&infoKereta);
                        char namaKeretaBuf[50] = "-";
                        if (BacaInformasiKereta(&infoKereta, id)) {
                            char* namaVal = AmbilNilai(&infoKereta, "namaKereta");
                            if (namaVal) strncpy(namaKeretaBuf, namaVal, sizeof(namaKeretaBuf)-1);
                        }
                        printf("ID: %s\n", id);
                        printf("Kereta: %s\n", namaKeretaBuf);
                        printf("+------+--------------------------------+-------+\n");
                        printf("| No.  | Stasiun                        | Jadwal|\n");
                        printf("+------+--------------------------------+-------+\n");
                        int i;
                        for (i = 0; i < activeCount; i++) {
                            char* stationName = activeRoutes[i];
                            int foundIndex = -1;
                            int j;
                            for (j = 0; j < stopCount; j++) {
                                if (equalsIgnoreCase(stopList[j], stationName)) { foundIndex = j; break; }
                            }
                            char* schedule = (char *)"Langsung";
                            if (foundIndex >= originPos && foundIndex <= destPos && foundIndex < timeCount) {
                                schedule = timeList[foundIndex];
                            }
                            printf("| %-4d | %-30s | %-6s |\n", i+1, stationName, schedule);
                        }
                        printf("+------+--------------------------------+-------+\n");
                        trainFound++;
                    }
                }
                fclose(f);
                if (trainFound == 0) {
                    printf("Tidak ada kereta yang melayani rute %s ke %s.\n", origin, destination);
                }
                printf("\nTekan Enter untuk kembali...");
                getchar();
                break;
            }
            case 4:
                // kembali ke menu admin dari fitur rute
                break;
            default:
                printf("\nPilihan tidak valid!");
                printf("\nTekan Enter untuk kembali...");
                getchar();
                break;
        }
    } while(pilihan != 4);
}
