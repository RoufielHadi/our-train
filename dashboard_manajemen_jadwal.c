/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

#include "boolean.h"
#include "tree_non_biner.h"
#include "clear.h"
#include "dashboard_manajemen_jadwal.h"
#include "implementasi_jadwal_kereta.h"
#include "implementasi_rute_kereta.h"
#include "linked.h"
#include "queue.h"

// Deklarasi fungsi yang hilang dari time.h
Waktu KonversiDariWaktuSingkat(WaktuSingkat ws);

// Prototype for detail view
void TampilkanDetailJadwal(int index);

// Helper: normalize station name to Title Case
void NormalizeName(char *s) {
	int i;
    for (i = 0; s[i]; i++) {
        if (i == 0)
            s[i] = toupper((unsigned char)s[i]);
        else
            s[i] = tolower((unsigned char)s[i]);
        }
    }

// Implementasi fungsi-fungsi yang digunakan di dashboard
void TampilkanDaftarJadwal() {
    // Baca semua jadwal kereta dari database
    Record jadwalRecords[100];
    int jumlahJadwal = 0;
    BacaSemuaJadwalKereta(jadwalRecords, &jumlahJadwal, 100);

    if (jumlahJadwal == 0) {
        printf("Belum ada jadwal kereta yang tersimpan.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return;
    }

    int pilihan;
    int i;
    do {
        clearScreen();
        printf("\nDaftar Jadwal Kereta:\n");
        printf("+=======+===============+==============================+==============================+\n");
        printf("| No.   | ID Kereta     | Stasiun Asal (Jam)           | Stasiun Tujuan (Jam)         |\n");
        printf("+=======+===============+==============================+==============================+\n");
        for (i = 0; i < jumlahJadwal; i++) {
            char* idKereta = AmbilNilai(&jadwalRecords[i], "kodeJadwal");
            char* stasiunAsal = AmbilNilai(&jadwalRecords[i], "stasiunAsal");
            char* waktuAsal = AmbilNilai(&jadwalRecords[i], "waktuAsal");
            char* stasiunTujuan = AmbilNilai(&jadwalRecords[i], "stasiunTujuan");
            char* waktuTujuan = AmbilNilai(&jadwalRecords[i], "waktuTujuan");
            printf("| %-5d | %-13s | %-14s (%5s) | %-14s (%5s) |\n",
                   i+1,
                   idKereta ? idKereta : "N/A",
                   stasiunAsal ? stasiunAsal : "N/A",
                   waktuAsal ? waktuAsal : "  -  ",
                   stasiunTujuan ? stasiunTujuan : "N/A",
                   waktuTujuan ? waktuTujuan : "  -  ");
        }
        printf("+=======+===============+==============================+==============================+\n");
        printf("Pilih nomor jadwal untuk detail (0 untuk kembali): ");
        scanf("%d", &pilihan); while(getchar()!='\n');
        if (pilihan > 0 && pilihan <= jumlahJadwal) {
            TampilkanDetailJadwal(pilihan);
        } else if (pilihan != 0) {
            printf("Pilihan tidak valid. Tekan Enter untuk melanjutkan...");
            getchar();
        }
    } while (pilihan != 0);
}

// Fungsi untuk menampilkan detail jadwal berdasarkan indeks
void TampilkanDetailJadwal(int index) {
    FILE* file = BukaFile(DB_JADWAL_KERETA, "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file jadwal_kereta.txt\n");
        return;
    }
    char buffer[MAX_RECORD_LENGTH];
    int i = 1;
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL) {
        if (i == index) break;
        i++;
    }
    TutupFile(file);
    if (i != index) {
        printf("Jadwal tidak ditemukan.\n");
        return;
    }
    int len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';

    char* id = strtok(buffer, "|");
    char* stations = strtok(NULL, "|");
    char* times = strtok(NULL, "|");

    printf("\nDetail Jadwal Kereta %s:\n", id ? id : "N/A");

    if (stations && times) {
        // Split stations and times into arrays
        char stationsCopy[MAX_RECORD_LENGTH], timesCopy[MAX_RECORD_LENGTH];
        strcpy(stationsCopy, stations);
        strcpy(timesCopy, times);
        char* stationsArray[100];
        char* timesArray[100];
        int sCount = 0, tCount = 0;
        char* tok;
        tok = strtok(stationsCopy, ",");
        while (tok && sCount < 100) { stationsArray[sCount++] = tok; tok = strtok(NULL, ","); }
        tok = strtok(timesCopy, ",");
        while (tok && tCount < 100) { timesArray[tCount++] = tok; tok = strtok(NULL, ","); }
        int maxItems = sCount < tCount ? sCount : tCount;
        printf("------------------------------------------\n");
        for (i = 0; i < maxItems; i++) {
            printf("%2d. %-20s - (%s)\n", i+1, stationsArray[i], timesArray[i]);
        }
        printf("------------------------------------------\n");
    }
    printf("Tekan Enter untuk kembali ke daftar...");
    getchar();
}

void TambahJadwal() {
    clearScreen();
    printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
    // Meminta input ID Kereta dan validasi keberadaan
    char id_kereta[10];
    printf("Masukkan ID Kereta: ");
    scanf("%s", id_kereta); while(getchar()!='\n');
    Record infoKereta; InisialisasiRecord(&infoKereta);
    if (!BacaInformasiKereta(&infoKereta, id_kereta)) {
        printf("Error: Kereta dengan ID %s tidak ditemukan!\n", id_kereta);
        printf("\nTekan Enter untuk kembali..."); getchar();
        return;
    }
    // Panggil fungsi detail tanpa tanggal
    TambahJadwalKereta(id_kereta);
    return; // Add explicit return to prevent fall-through
}

void TambahJadwalKereta(const char* idKereta) {
    // ID kereta sudah ditentukan dari parameter
    char id_kereta[10];
    strcpy(id_kereta, idKereta);
    
    char stasiunAsal[50];
    char stasiunTujuan[50];
    Waktu waktuAsal, waktuTujuan;
    boolean valid;
    
    // Validasi apakah kereta dengan ID tersebut ada
    Record infoKereta;
    InisialisasiRecord(&infoKereta);
    if (!BacaInformasiKereta(&infoKereta, id_kereta)) {
        clearScreen();
        printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
        printf("Error: Kereta dengan ID %s tidak ditemukan!\n", id_kereta);
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    // Baca data stasiun
    Isi_Tree stationTree;
    BacaDataStasiun(stationTree);

    // Input stasiun awal dan validasi
    boolean validStation = FALSE;
    int idxStasiun = 0;
    char tmpName[50];
    do {
    clearScreen();
    printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
    printf("ID Kereta: %s\n\n", id_kereta);
    printf("Masukkan stasiun awal: ");
        if (fgets(stasiunAsal, sizeof(stasiunAsal), stdin) == NULL) stasiunAsal[0] = '\0';
        stasiunAsal[strcspn(stasiunAsal, "\n")] = '\0';
        NormalizeName(stasiunAsal);
        idxStasiun = CariIndeksStasiun(stationTree, stasiunAsal);
        if (idxStasiun == 0 || !IsStationActiveAndName(idxStasiun, tmpName)) {
            printf("Error: Stasiun %s tidak ditemukan atau tidak aktif.\n", stasiunAsal);
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            validStation = FALSE;
        } else {
            validStation = TRUE;
        }
    } while (!validStation);
    
    // Input waktu keberangkatan
    do {
        clearScreen();
        printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
        printf("ID Kereta: %s\n", id_kereta);
        printf("Stasiun Awal: %s\n\n", stasiunAsal);
        
        printf("Masukkan Waktu keberangkatan stasiun awal (HH:MM): ");
        if (scanf("%d:%d", &waktuAsal.jam, &waktuAsal.menit) != 2) {
            while(getchar()!='\n'); // Bersihkan buffer
            printf("Error: Format waktu tidak valid! Gunakan format HH:MM\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            valid = FALSE;
            continue;
        }
        while(getchar()!='\n');
        
        valid = TRUE;
        // Validasi waktu
        if (waktuAsal.jam < 0 || waktuAsal.jam > 23 || waktuAsal.menit < 0 || waktuAsal.menit > 59) {
            printf("Error: Waktu tidak valid! Jam (0-23) dan Menit (0-59)\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            valid = FALSE;
        }
    } while (!valid);
    
    waktuAsal.detik = 0;
    
    // Input stasiun tujuan dan validasi
    boolean validStation2 = FALSE;
    int idxStasiun2 = 0;
    do {
    clearScreen();
    printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
    printf("ID Kereta: %s\n", id_kereta);
    printf("Stasiun Awal: %s (%02d:%02d)\n\n", stasiunAsal, waktuAsal.jam, waktuAsal.menit);
    printf("Masukkan stasiun akhir: ");
        if (fgets(stasiunTujuan, sizeof(stasiunTujuan), stdin) == NULL) stasiunTujuan[0] = '\0';
        stasiunTujuan[strcspn(stasiunTujuan, "\n")] = '\0';
        NormalizeName(stasiunTujuan);
        idxStasiun2 = CariIndeksStasiun(stationTree, stasiunTujuan);
        if (idxStasiun2 == 0 || !IsStationActiveAndName(idxStasiun2, tmpName)) {
            printf("Error: Stasiun %s tidak ditemukan atau tidak aktif.\n", stasiunTujuan);
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            validStation2 = FALSE;
        } else {
            validStation2 = TRUE;
        }
    } while (!validStation2);
    
    // Input waktu kedatangan
    do {
        clearScreen();
        printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
        printf("ID Kereta: %s\n", id_kereta);
        printf("Stasiun Awal: %s (%02d:%02d)\n", stasiunAsal, waktuAsal.jam, waktuAsal.menit);
        printf("Stasiun Akhir: %s\n\n", stasiunTujuan);
        
        printf("Masukkan Waktu kedatangan stasiun akhir (HH:MM): ");
        if (scanf("%d:%d", &waktuTujuan.jam, &waktuTujuan.menit) != 2) {
            while(getchar()!='\n'); // Bersihkan buffer
            printf("Error: Format waktu tidak valid! Gunakan format HH:MM\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            valid = FALSE;
            continue;
        }
        while(getchar()!='\n');
        
        valid = TRUE;
        // Validasi waktu
        if (waktuTujuan.jam < 0 || waktuTujuan.jam > 23 || waktuTujuan.menit < 0 || waktuTujuan.menit > 59) {
            printf("Error: Waktu tidak valid! Jam (0-23) dan Menit (0-59)\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            valid = FALSE;
            continue;
        }
        
        // Validasi waktu kedatangan harus setelah waktu keberangkatan
        int waktuAsalMenit = waktuAsal.jam * 60 + waktuAsal.menit;
        int waktuTujuanMenit = waktuTujuan.jam * 60 + waktuTujuan.menit;
        
        if (waktuTujuanMenit <= waktuAsalMenit) {
            printf("Error: Waktu kedatangan harus setelah waktu keberangkatan!\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            valid = FALSE;
        }
    } while (!valid);
    
    waktuTujuan.detik = 0;
    
    // Buat jadwal baru
    JadwalHarian jadwalBaru = BuatJadwalKereta(id_kereta, (char *)"");
    
    // Tambahkan stasiun ke jadwal
    TambahStasiunKeJadwal(&jadwalBaru, stasiunAsal, waktuAsal);
    
    // Tampilkan stasiun aktif yang berada di antara stasiun asal dan tujuan
    StationInfo activeStations[50];
    int stationCount = GetActiveStationsBetween(stationTree, stasiunAsal, stasiunTujuan, activeStations, 50);
    
    // Array untuk melacak stasiun yang sudah dipilih
    boolean stationSelected[50] = {FALSE};
    int selectedCount = 0;
    char selectedStations[50][50];
    Waktu selectedTimes[50];
    
    // Tanyakan apakah user ingin menambahkan stasiun transit
        clearScreen();
        printf("\n====== TAMBAH JADWAL KERETA BARU ======\n");
        printf("ID Kereta: %s\n", id_kereta);
        printf("Stasiun Awal: %s (%02d:%02d)\n", stasiunAsal, waktuAsal.jam, waktuAsal.menit);
        printf("Stasiun Akhir: %s (%02d:%02d)\n\n", stasiunTujuan, waktuTujuan.jam, waktuTujuan.menit);
        
    printf("Apakah anda ingin menambahkan stasiun transit? (y/n): ");
    char jawaban;
    scanf(" %c", &jawaban); while(getchar()!='\n');
        
    if (jawaban == 'y' || jawaban == 'Y') {
        // Gunakan GetRouteStations untuk mendapatkan semua stasiun dalam rute
        char routeNames[100][50];
        int routeCount = GetRouteStations(stasiunAsal, stasiunTujuan, routeNames, 100);
        
        // Muat data stasiun untuk cek status aktif
        Isi_Tree stationTree;
        BacaDataStasiun(stationTree);
        
        // Konversi hasil ke format StationInfo untuk kompatibilitas dengan kode selanjutnya (hanya stasiun aktif)
        stationCount = 0;
        int i;
        for (i = 1; i < routeCount - 1; i++) { // Skip origin and destination
            // Cek status stasiun
            char tmpName2[50];
            int idx2 = CariIndeksStasiun(stationTree, routeNames[i]);
            if (idx2 > 0 && IsStationActiveAndName(idx2, tmpName2)) {
                strcpy(activeStations[stationCount].name, tmpName2);
                activeStations[stationCount].active = TRUE;
                activeStations[stationCount].index = idx2;
                stationCount++;
            }
        }
        
        if (stationCount > 0) {
            boolean tambahTransitLagi = TRUE;
            
            while (tambahTransitLagi) {
                clearScreen();
                printf("\n====== TAMBAH STASIUN TRANSIT ======\n");
                printf("ID Kereta: %s\n", id_kereta);
                printf("Stasiun Awal: %s (%02d:%02d)\n", stasiunAsal, waktuAsal.jam, waktuAsal.menit);
                printf("Stasiun Akhir: %s (%02d:%02d)\n\n", stasiunTujuan, waktuTujuan.jam, waktuTujuan.menit);
                
                printf("Berdasarkan hasil pemilihan anda memilih stasiun awal %s dan stasiun akhir %s\n", stasiunAsal, stasiunTujuan);
                printf("maka stasiun yang ada diantara keduanya adalah:\n\n");
                
                printf("+======+==========================+===========+\n");
                printf("| No.  | Nama Stasiun             | Status    |\n");
                printf("+======+==========================+===========+\n");
                
                int availableCount = 0;
                int i;
                for (i = 0; i < stationCount; i++) {
                    // Tampilkan hanya stasiun yang belum dipilih
                    if (!stationSelected[i]) {
                        availableCount++;
                        printf("| %-4d | %-24s | %-9s |\n", availableCount, activeStations[i].name, "Tersedia");
                    }
                }
                
                if (availableCount == 0) {
                    printf("| ---- | Tidak ada stasiun tersedia | --------- |\n");
                    printf("+======+==========================+===========+\n");
                    printf("\nSemua stasiun transit sudah dipilih.\n");
                    printf("Tekan Enter untuk melanjutkan...");
                    getchar();
                    tambahTransitLagi = FALSE;
                    continue;
                }
                
                printf("+======+==========================+===========+\n");
            
                // Tampilkan stasiun yang sudah dipilih
                if (selectedCount > 0) {
                    printf("\nStasiun transit yang dipilih:\n");
                    printf("+======+==========================+==============+\n");
                    printf("| No.  | Nama Stasiun             | Waktu        |\n");
                    printf("+======+==========================+==============+\n");
                    
                    // Urutkan stasiun dipilih berdasarkan waktu
                    int i;
                    for (i = 0; i < selectedCount; i++) {
                        printf("| %-4d | %-24s | %02d:%02d        |\n", 
                               i+1, selectedStations[i], selectedTimes[i].jam, selectedTimes[i].menit);
                    }
                    printf("+======+==========================+==============+\n");
                }
                
                printf("\nPilih stasiun yang akan jadi tempat transit (0 untuk selesai): ");
                int pilihan;
                scanf("%d", &pilihan); while(getchar()!='\n');
                
                if (pilihan == 0) {
                    tambahTransitLagi = FALSE;
                    continue;
                }
                
                // Konversi pilihan ke indeks stasiun yang tersedia
                if (pilihan < 0 || pilihan > availableCount) {
                    printf("Pilihan tidak valid!\n");
                    printf("Tekan Enter untuk mencoba lagi...");
                    getchar();
                    continue;
                }
                
                // Cari indeks stasiun yang sesuai dengan pilihan
                int actualIndex = -1;
                int count = 0;
                for (i = 0; i < stationCount; i++) {
                    if (!stationSelected[i]) {
                        count++;
                        if (count == pilihan) {
                            actualIndex = i;
                            break;
                        }
                    }
                }
                
                if (actualIndex == -1) {
                    printf("Error: Stasiun tidak ditemukan!\n");
                    printf("Tekan Enter untuk mencoba lagi...");
                    getchar();
                    continue;
                }
                
                char stasiunTransit[50];
                strcpy(stasiunTransit, activeStations[actualIndex].name);
                
                Waktu waktuTransit;
                boolean waktuValid;
                
                // Tentukan rentang waktu valid: dari stasiun transit terakhir (atau asal) hingga tujuan
                Waktu waktuSebelumnya;
                if (selectedCount > 0) {
                    waktuSebelumnya = selectedTimes[selectedCount-1];
                } else {
                    waktuSebelumnya = waktuAsal;
                }
                Waktu waktuSesudahnya = waktuTujuan;
                
                do {
                    clearScreen();
                    printf("\n====== TAMBAH STASIUN TRANSIT ======\n");
                    printf("ID Kereta: %s\n", id_kereta);
                    printf("Stasiun Awal: %s (%02d:%02d)\n", stasiunAsal, waktuAsal.jam, waktuAsal.menit);
                    printf("Stasiun Transit: %s\n", stasiunTransit);
                    printf("Stasiun Akhir: %s (%02d:%02d)\n\n", stasiunTujuan, waktuTujuan.jam, waktuTujuan.menit);
                    
                    printf("Waktu keberangkatan harus antara (%02d:%02d) dan (%02d:%02d)\n\n", 
                           waktuSebelumnya.jam, waktuSebelumnya.menit, waktuSesudahnya.jam, waktuSesudahnya.menit);
                    
                    printf("Masukkan jam keberangkatan di stasiun transit (HH:MM): ");
                    if (scanf("%d:%d", &waktuTransit.jam, &waktuTransit.menit) != 2) {
                        while(getchar()!='\n'); // Bersihkan buffer
                        printf("Error: Format waktu tidak valid! Gunakan format HH:MM\n");
                        printf("Tekan Enter untuk mencoba lagi...");
                        getchar();
                        waktuValid = FALSE;
                        continue;
                    }
                    while(getchar()!='\n');
                    
                    waktuValid = TRUE;
                    
                    // Validasi waktu
                    if (waktuTransit.jam < 0 || waktuTransit.jam > 23 || waktuTransit.menit < 0 || waktuTransit.menit > 59) {
                        printf("Error: Waktu tidak valid! Jam (0-23) dan Menit (0-59)\n");
                        printf("Tekan Enter untuk mencoba lagi...");
                        getchar();
                        waktuValid = FALSE;
                        continue;
                    }
                    
                    // Validasi bahwa waktu transit berada di antara waktu sebelumnya dan sesudahnya
                    int waktuSebelumnyaMenit = waktuSebelumnya.jam * 60 + waktuSebelumnya.menit;
                    int waktuSesudahnyaMenit = waktuSesudahnya.jam * 60 + waktuSesudahnya.menit;
                    int waktuTransitMenit = waktuTransit.jam * 60 + waktuTransit.menit;
                    
                    if (waktuTransitMenit <= waktuSebelumnyaMenit || waktuTransitMenit >= waktuSesudahnyaMenit) {
                        printf("Error: Waktu transit harus di antara waktu stasiun sebelumnya dan sesudahnya!\n");
                        printf("Tekan Enter untuk mencoba lagi...");
                        getchar();
                        waktuValid = FALSE;
                    }
                } while (!waktuValid);
                
                waktuTransit.detik = 0;
                
                // Tandai stasiun sebagai terpilih
                stationSelected[actualIndex] = TRUE;
                strcpy(selectedStations[selectedCount], stasiunTransit);
                selectedTimes[selectedCount] = waktuTransit;
                selectedCount++;
                
                printf("\nStasiun transit %s berhasil ditambahkan!\n", stasiunTransit);
                printf("Apakah anda ingin menambahkan stasiun transit lainnya? (y/n): ");
                scanf(" %c", &jawaban); while(getchar()!='\n');
                
                if (jawaban != 'y' && jawaban != 'Y') {
                    tambahTransitLagi = FALSE;
                }
            }
            
            // Tambahkan stasiun yang dipilih ke jadwal berdasarkan waktu
            // Urutkan stasiun berdasarkan waktu transit
            int i,j;
            for (i = 0; i < selectedCount; i++) {
                for (j = i + 1; j < selectedCount; j++) {
                    int waktuI = selectedTimes[i].jam * 60 + selectedTimes[i].menit;
                    int waktuJ = selectedTimes[j].jam * 60 + selectedTimes[j].menit;
                    
                    if (waktuI > waktuJ) {
                        // Tukar waktu
                        Waktu tempWaktu = selectedTimes[i];
                        selectedTimes[i] = selectedTimes[j];
                        selectedTimes[j] = tempWaktu;
                        
                        // Tukar nama stasiun
                        char tempNama[50];
                        strcpy(tempNama, selectedStations[i]);
                        strcpy(selectedStations[i], selectedStations[j]);
                        strcpy(selectedStations[j], tempNama);
                    }
                }
            }
            
            // Tambahkan stasiun transit ke jadwal sesuai urutan waktu
            for (i = 0; i < selectedCount; i++) {
                TambahStasiunKeJadwal(&jadwalBaru, selectedStations[i], selectedTimes[i]);
            }
        } else {
            printf("\nTidak ada stasiun aktif yang tersedia di antara %s dan %s.\n", stasiunAsal, stasiunTujuan);
            printf("Stasiun tersebut mungkin tidak terhubung dalam rute yang sama atau tidak ada stasiun transit di antaranya.\n");
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
        }
    }
    
    // Tambahkan stasiun tujuan ke jadwal
    TambahStasiunKeJadwal(&jadwalBaru, stasiunTujuan, waktuTujuan);
    
    // Tampilkan ringkasan jadwal
    clearScreen();
    printf("\n====== RINGKASAN JADWAL KERETA ======\n");
    printf("ID Kereta: %s\n", id_kereta);
    
    printf("Rute Perjalanan:\n");
    printf("------------------------------------------\n");
    StasiunTransit* curr = jadwalBaru.jadwal_rute.head;
    int idx = 1;
    while (curr != NULL) {
        Waktu waktu = KonversiDariWaktuSingkat(curr->waktu_transit);
        printf("%2d. %-20s - (%02d:%02d)\n", idx++, curr->nama_stasiun, waktu.jam, waktu.menit);
        curr = curr->next;
    }
    printf("------------------------------------------\n\n");
    
    printf("Konfirmasi penyimpanan jadwal (Y/N): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi); while(getchar()!='\n');
    
    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        // Simpan jadwal dalam format sederhana: ID|stations|times
        char stations[MAX_RECORD_LENGTH] = "";
        char times[MAX_RECORD_LENGTH] = "";
        StasiunTransit* currNode = jadwalBaru.jadwal_rute.head;
        while (currNode != NULL) {
            // Tambahkan nama stasiun
            if (strlen(stations) > 0) strcat(stations, ",");
            strcat(stations, currNode->nama_stasiun);
            // Tambahkan waktu
            Waktu wt = KonversiDariWaktuSingkat(currNode->waktu_transit);
            char bufTime[6]; sprintf(bufTime, "%02d:%02d", wt.jam, wt.menit);
            if (strlen(times) > 0) strcat(times, ",");
            strcat(times, bufTime);
            currNode = currNode->next;
        }
        FILE* out = fopen(DB_JADWAL_KERETA, "a");
        if (out != NULL) {
            fprintf(out, "%s|%s|%s\n", id_kereta, stations, times);
            fclose(out);
            printf("Jadwal berhasil ditambahkan!\n");
        } else {
            printf("Error: Gagal membuka file jadwal_kereta.txt untuk menulis!\n");
        }
    } else {
        printf("Penambahan jadwal dibatalkan.\n");
    }
    
    printf("Tekan Enter untuk kembali...");
    getchar();
    return;
}

// Fungsi untuk menampilkan daftar jadwal dan mengembalikan ID kereta yang dipilih
char* TampilkanDaftarJadwalDanPilih() {
    // Baca semua jadwal kereta dari database
    Record jadwalRecords[100];
    int jumlahJadwal = 0;
    BacaSemuaJadwalKereta(jadwalRecords, &jumlahJadwal, 100);
    static char selectedID[20] = "";

    if (jumlahJadwal == 0) {
        printf("Belum ada jadwal kereta yang tersimpan.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return NULL;
    }

    int pilihan;
    clearScreen();
    printf("\nDaftar Jadwal Kereta:\n");
    printf("+=======+===============+==============================+==============================+\n");
    printf("| No.   | ID Kereta     | Stasiun Asal (Jam)           | Stasiun Tujuan (Jam)         |\n");
    printf("+=======+===============+==============================+==============================+\n");
    
    int i;
    for (i = 0; i < jumlahJadwal; i++) {
        char* idKereta = AmbilNilai(&jadwalRecords[i], "kodeJadwal");
        char* stasiunAsal = AmbilNilai(&jadwalRecords[i], "stasiunAsal");
        char* waktuAsal = AmbilNilai(&jadwalRecords[i], "waktuAsal");
        char* stasiunTujuan = AmbilNilai(&jadwalRecords[i], "stasiunTujuan");
        char* waktuTujuan = AmbilNilai(&jadwalRecords[i], "waktuTujuan");
        printf("| %-5d | %-13s | %-14s (%5s) | %-14s (%5s) |\n",
               i+1,
               idKereta ? idKereta : "N/A",
               stasiunAsal ? stasiunAsal : "N/A",
               waktuAsal ? waktuAsal : "  -  ",
               stasiunTujuan ? stasiunTujuan : "N/A",
               waktuTujuan ? waktuTujuan : "  -  ");
    }
    printf("+=======+===============+==============================+==============================+\n");
    
    printf("Masukkan nomor jadwal yang ingin dipilih (0 untuk kembali): ");
    scanf("%d", &pilihan); while(getchar()!='\n');
    
    if (pilihan > 0 && pilihan <= jumlahJadwal) {
        char* idKereta = AmbilNilai(&jadwalRecords[pilihan-1], "kodeJadwal");
        if (idKereta) {
            strcpy(selectedID, idKereta);
            return selectedID;
        }
    }
    
    return NULL;
}

void EditJadwal() {
    clearScreen();
    printf("\n====== EDIT JADWAL KERETA ======\n");
    
    // Tampilkan daftar jadwal dan minta user memilih ID kereta langsung
    char* selectedID = TampilkanDaftarJadwalDanPilih();
    
    if (selectedID == NULL) {
        printf("Tidak ada jadwal yang dipilih.\n");
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    char idKereta[50];
    strcpy(idKereta, selectedID);
    
    // Baca jadwal dari database
    Record jadwalRecord;
    InisialisasiRecord(&jadwalRecord);
    
    if (!BacaJadwalKereta(&jadwalRecord, idKereta)) {
        // Fallback: cari via format sederhana (hasil BacaSemuaJadwalKereta)
        Record semua[200]; int jml = 0;
        BacaSemuaJadwalKereta(semua, &jml, 200);
        boolean ketemu = FALSE;
        int i;
        for (i = 0; i < jml; i++) {
            char* kode = AmbilNilai(&semua[i], "kodeJadwal");
            if (kode && strcmp(kode, idKereta) == 0) {
                jadwalRecord = semua[i];
                ketemu = TRUE;
                break;
            }
        }
        if (!ketemu) {
            printf("Error: Jadwal dengan ID kereta %s tidak ditemukan!\n", idKereta);
            printf("\nTekan Enter untuk kembali..."); 
            getchar();
            return;
        }
    }
    
    // Konversi record ke jadwal
    JadwalHarian jadwal = KonversiRecordKeJadwalKereta(jadwalRecord);
    
    // Tampilkan detail jadwal yang akan diedit (tanpa tanggal)
    clearScreen();
    printf("\n====== EDIT JADWAL KERETA ======\n");
    printf("ID Kereta: %s\n", idKereta);
    printf("Rute Perjalanan:\n");
    printf("+======+==========================+==============+\n");
    printf("| No.  | Nama Stasiun             | Waktu        |\n");
    printf("+======+==========================+==============+\n");
    
    int idx = 1;
    StasiunTransit* p = jadwal.jadwal_rute.head;
    while (p != NULL) {
        Waktu waktu = KonversiDariWaktuSingkat(p->waktu_transit);
        printf("| %-4d | %-24s | %02d:%02d        |\n", 
            idx++, p->nama_stasiun, waktu.jam, waktu.menit);
        p = p->next;
    }
    printf("+======+==========================+==============+\n");
    
    // Opsi edit: edit existing station or add new transit station
    printf("\nOpsi Edit:\n");
    printf("1. Edit Stasiun dan Waktu Transit\n");
    printf("2. Tambah Stasiun Transit\n");
    printf("3. Kembali\n");
    printf("Pilihan: ");
    
    int pilihan;
    scanf("%d", &pilihan); while(getchar()!='\n');
    
    char stasiunBaru[50];
    Waktu waktuBaru;
    boolean isAdd = FALSE;

    if (pilihan == 3) {
        return;
    } else if (pilihan == 2) {
        isAdd = TRUE;
        // Tambah stasiun transit
        char origin[50], dest[50];
        // Origin: first station
        strcpy(origin, jadwal.jadwal_rute.head->nama_stasiun);
        // Destination: last station
        StasiunTransit* last = jadwal.jadwal_rute.head;
        while (last->next) last = last->next;
        strcpy(dest, last->nama_stasiun);
        
        // Gunakan GetRouteStations untuk mendapatkan semua stasiun dalam rute
        char routeNames[100][50];
        int routeCount = GetRouteStations(origin, dest, routeNames, 100);
        
        // Muat data stasiun untuk cek status aktif
        Isi_Tree stationTree;
        BacaDataStasiun(stationTree);
        
        if (routeCount <= 2) {
            printf("Tidak ada stasiun transit yang dapat ditambahkan.\n");
            printf("Stasiun tersebut mungkin tidak terhubung dalam rute yang sama atau tidak ada stasiun transit di antaranya.\n");
            printf("Tekan Enter untuk kembali...");
            getchar();
        } else {
            printf("+======+==============================+\n");
            printf("| No.  | Nama Stasiun                 |\n");
            printf("+======+==============================+\n");
            
            // Tampilkan hanya stasiun aktif antara origin dan destination
            int displayCount = 0;
            int i;
            for (i = 1; i < routeCount - 1; i++) {
                char tmpName2[50];
                int idx2 = CariIndeksStasiun(stationTree, routeNames[i]);
                if (idx2 > 0 && IsStationActiveAndName(idx2, tmpName2)) {
                    displayCount++;
                    printf("| %-4d | %-28s |\n", displayCount, tmpName2);
                }
            }
            printf("+======+==============================+\n");
            printf("Pilih nomor stasiun (0 untuk batal): ");
            int choice;
            scanf("%d", &choice); while(getchar()!='\n');
            if (choice > 0 && choice <= displayCount) {
                // Cari actualIndex berdasarkan urutan aktif
                int displayIdx = 0, actualIndex = -1;
                int i;
                for (i = 1; i < routeCount - 1; i++) {
                    char tmpName2[50];
                    int idx2 = CariIndeksStasiun(stationTree, routeNames[i]);
                    if (idx2 > 0 && IsStationActiveAndName(idx2, tmpName2)) {
                        displayIdx++;
                        if (displayIdx == choice) {
                            actualIndex = i;
                            break;
                        }
                    }
                }
                char newStation[50];
                strcpy(newStation, routeNames[actualIndex]);
                Waktu newTime; boolean validTime;
                do {
                    printf("Masukkan Waktu untuk stasiun %s (HH:MM): ", newStation);
                    if (scanf("%d:%d", &newTime.jam, &newTime.menit) != 2) {
                        while(getchar()!='\n');
                        printf("Format waktu tidak valid!\n");
                        validTime = FALSE;
                    } else {
                        while(getchar()!='\n');
                        newTime.detik = 0;
                        validTime = TRUE;
                    }
                } while (!validTime);
                // Insert to schedule in correct route order
                char prevStation[50];
                strcpy(prevStation, routeNames[actualIndex - 1]);
                // Determine insertion point
                StasiunTransit* insertAfter = NULL;
                StasiunTransit* p2 = jadwal.jadwal_rute.head;
                while (p2) {
                    if (strcmp(p2->nama_stasiun, prevStation) == 0) { insertAfter = p2; break; }
                    p2 = p2->next;
                }
                if (!insertAfter) {
                    // fallback: find node before destination
                    StasiunTransit* q = jadwal.jadwal_rute.head;
                    while (q->next && strcmp(q->next->nama_stasiun, dest) != 0) q = q->next;
                    insertAfter = q;
                }
                StasiunTransit* newNode = CreateStasiunTransit(newStation, KonversiKeWaktuSingkat(newTime));
                newNode->next = insertAfter->next;
                insertAfter->next = newNode;
                printf("Stasiun transit %s berhasil ditambahkan!\n", newStation);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
            } else {
                printf("Pilihan tidak valid atau batal.\n");
                printf("Tekan Enter untuk kembali...");
                getchar();
            }
        }
    } else if (pilihan != 1) {
        printf("Pilihan tidak valid!\n");
        printf("\nTekan Enter untuk kembali...");
        getchar();
        return;
    }
    
    // Pilih nomor stasiun untuk diedit
    if (!isAdd) {
        int idx;
        printf("Masukkan nomor stasiun yang ingin diedit: ");
        scanf("%d", &idx); while(getchar()!='\n');
        
        // Temukan stasiun ke-idx
        StasiunTransit* curr = jadwal.jadwal_rute.head;
        int count = 1;
        while (curr != NULL && count < idx) {
            curr = curr->next;
            count++;
        }
        if (curr == NULL) {
            printf("Error: Nomor stasiun tidak valid!\n");
            printf("\nTekan Enter untuk kembali...");
            getchar();
            return;
        }
        
        // Determine previous and next station names for position
        char prevName[50], nextName[50];
        // previous
        if (idx > 1) {
            StasiunTransit* p = jadwal.jadwal_rute.head;
            int cn = 1;
            while (p && cn < idx-1) { p = p->next; cn++; }
            strcpy(prevName, p ? p->nama_stasiun : "");
                } else {
            strcpy(prevName, jadwal.jadwal_rute.head->nama_stasiun);
                }
        // next
        if (curr->next) {
            strcpy(nextName, curr->next->nama_stasiun);
            } else {
            StasiunTransit* q = jadwal.jadwal_rute.head;
            while (q->next) q = q->next;
            strcpy(nextName, q->nama_stasiun);
        }
        // Determine edit context: transit, dest (last), or origin (first)
        if (idx > 1 && curr->next != NULL) {
            // Transit station: list stations between prev and next
            Isi_Tree tree;
            BacaDataStasiun(tree);
            StationInfo options[50];
            int optCount = GetActiveStationsBetween(tree, prevName, nextName, options, 50);
            if (optCount <= 0) {
                printf("Tidak ada stasiun valid di antara %s dan %s.\n", prevName, nextName);
                printf("Tekan Enter untuk kembali..."); getchar();
                return;
            }
            printf("Daftar Stasiun di antara %s dan %s:\n", prevName, nextName);
            int k;
            for (k = 0; k < optCount; k++) {
                printf("%2d. %s\n", k+1, options[k].name);
            }
            printf("Pilih nomor stasiun baru (0 untuk batal): ");
            int choice;
            scanf("%d", &choice); while(getchar()!='\n');
            if (choice <= 0 || choice > optCount) {
                printf("Batal mengedit stasiun.\n");
                printf("Tekan Enter untuk kembali..."); getchar();
                return;
            }
            strcpy(curr->nama_stasiun, options[choice-1].name);
            printf("Stasiun transit diubah ke %s.\n", curr->nama_stasiun);
        } else if (curr->next == NULL) {
            // Last station: list stations beyond prevName
            Isi_Tree tree;
            BacaDataStasiun(tree);
            StationInfo options[200];
            char nameBuf[50];
            int optCount = 0;
            int prevIdx = CariIndeksStasiun(tree, prevName);
            int currIdx = CariIndeksStasiun(tree, curr->nama_stasiun);
            // Determine direction relative to tree index
            if (prevIdx < currIdx) {
            	int i;
                for (i = prevIdx + 1; i <= jml_maks; i++) {
                    if (IsStationActiveAndName(i, nameBuf)) {
                        strcpy(options[optCount].name, nameBuf);
                        options[optCount].index = i;
                        options[optCount].active = TRUE;
                        optCount++;
                    }
                }
            } else {
            	int i;
                for (i = prevIdx - 1; i >= 1; i--) {
                    if (IsStationActiveAndName(i, nameBuf)) {
                        strcpy(options[optCount].name, nameBuf);
                        options[optCount].index = i;
                        options[optCount].active = TRUE;
                        optCount++;
                    }
                }
            }
            if (optCount <= 0) {
                printf("Tidak ada stasiun setelah %s.\n", prevName);
                printf("Tekan Enter untuk kembali..."); getchar();
                return;
            }
            printf("Daftar Stasiun setelah %s:\n", prevName);
            int k;
            for (k = 0; k < optCount; k++) {
                printf("%2d. %s\n", k+1, options[k].name);
            }
            printf("Pilih nomor stasiun baru (0 untuk batal): ");
            int choice;
            scanf("%d", &choice); while(getchar()!='\n');
            if (choice <= 0 || choice > optCount) {
                printf("Batal mengedit stasiun.\n");
                printf("Tekan Enter untuk kembali..."); getchar();
                return;
            }
            strcpy(curr->nama_stasiun, options[choice-1].name);
            printf("Stasiun akhir diubah ke %s.\n", curr->nama_stasiun);
        } else {
            // First station: list stations before nextName
            Isi_Tree tree;
            BacaDataStasiun(tree);
            StationInfo options[200];
            char nameBuf[50];
            int optCount = 0;
            int nextIdx = CariIndeksStasiun(tree, nextName);
            int i;
            for (i = nextIdx - 1; i >= 1; i--) {
                if (IsStationActiveAndName(i, nameBuf)) {
                    strcpy(options[optCount].name, nameBuf);
                    options[optCount].index = i;
                    options[optCount].active = TRUE;
                    optCount++;
                }
            }
            if (optCount <= 0) {
                printf("Tidak ada stasiun sebelum %s.\n", nextName);
                printf("Tekan Enter untuk kembali..."); getchar();
                return;
            }
            printf("Daftar Stasiun sebelum %s:\n", nextName);
            int k;
            for (k = 0; k < optCount; k++) {
                printf("%2d. %s\n", k+1, options[k].name);
            }
            printf("Pilih nomor stasiun baru (0 untuk batal): ");
            int choice;
            scanf("%d", &choice); while(getchar()!='\n');
            if (choice <= 0 || choice > optCount) {
                printf("Batal mengedit stasiun.\n");
                printf("Tekan Enter untuk kembali..."); getchar();
                return;
            }
            strcpy(curr->nama_stasiun, options[choice-1].name);
            printf("Stasiun awal diubah ke %s.\n", curr->nama_stasiun);
        }
        
        // Edit time for this station with validation (must be between prev and next station times)
        {
            // Determine previous and next station times
            Waktu prevTime = {0}, nextTime = {23,59,0};
            StasiunTransit* pPrev = jadwal.jadwal_rute.head;
            while (pPrev && strcmp(pPrev->nama_stasiun, prevName) != 0) pPrev = pPrev->next;
            if (pPrev) prevTime = KonversiDariWaktuSingkat(pPrev->waktu_transit);
            StasiunTransit* pNext = jadwal.jadwal_rute.head;
            while (pNext && strcmp(pNext->nama_stasiun, nextName) != 0) pNext = pNext->next;
            if (pNext) nextTime = KonversiDariWaktuSingkat(pNext->waktu_transit);
            boolean validTimeEdit = FALSE;
            do {
                printf("Masukkan Waktu Baru (HH:MM): ");
                if (scanf("%d:%d", &waktuBaru.jam, &waktuBaru.menit) != 2) {
                    while(getchar()!='\n');
                    printf("Error: Format waktu tidak valid! Gunakan format HH:MM\n");
                } else {
                    while(getchar()!='\n');
                    if (waktuBaru.jam < 0 || waktuBaru.jam > 23 || waktuBaru.menit < 0 || waktuBaru.menit > 59) {
                        printf("Error: Waktu tidak valid! Jam (0-23) dan Menit (0-59)\n");
                    } else {
                        int newMins = waktuBaru.jam * 60 + waktuBaru.menit;
                        int prevMins = prevTime.jam * 60 + prevTime.menit;
                        int nextMins = nextTime.jam * 60 + nextTime.menit;
                        if (newMins <= prevMins || newMins >= nextMins) {
                            printf("Error: Waktu harus setelah %02d:%02d dan sebelum %02d:%02d\n", prevTime.jam, prevTime.menit, nextTime.jam, nextTime.menit);
                        } else {
                            validTimeEdit = TRUE;
                        }
                    }
                }
            } while (!validTimeEdit);
            waktuBaru.detik = 0;
            curr->waktu_transit = KonversiKeWaktuSingkat(waktuBaru);
        }
    }
            
    // Hapus jadwal lama (format baru) dan simpan yang baru, dengan fallback format lama
    boolean deleted = HapusJadwalKereta(idKereta);
    if (!deleted) {
        FILE* file = fopen(DB_JADWAL_KERETA, "r");
        FILE* tempFile = fopen("jadwal_kereta.tmp", "w");
        if (file && tempFile) {
            char buffer[1024]; boolean found = FALSE;
            while (fgets(buffer, sizeof(buffer), file)) {
                buffer[strcspn(buffer, "\n")] = '\0';
                char* copy = strdup(buffer);
                if (!copy) continue;
                char* id = strtok(copy, "|");
                if (id && strcmp(id, idKereta) == 0) {
                    found = TRUE;
                } else {
                    fprintf(tempFile, "%s\n", buffer);
                }
                free(copy);
            }
            fclose(file); fclose(tempFile);
            if (found) { remove(DB_JADWAL_KERETA); rename("jadwal_kereta.tmp", DB_JADWAL_KERETA); deleted = TRUE; }
            else { remove("jadwal_kereta.tmp"); }
        }
    }
    if (deleted) {
        // Build pipe-delimited stations|times
        char stations[MAX_RECORD_LENGTH] = "";
        char times[MAX_RECORD_LENGTH] = "";
        StasiunTransit* tempNode = jadwal.jadwal_rute.head;
        while (tempNode != NULL) {
            if (strlen(stations) > 0) strcat(stations, ",");
            strcat(stations, tempNode->nama_stasiun);
            Waktu wt = KonversiDariWaktuSingkat(tempNode->waktu_transit);
            char buf[10]; sprintf(buf, "%02d:%02d", wt.jam, wt.menit);
            if (strlen(times) > 0) strcat(times, ",");
            strcat(times, buf);
            tempNode = tempNode->next;
        }
        FILE* out = fopen(DB_JADWAL_KERETA, "a");
        if (out != NULL) {
            fprintf(out, "%s|%s|%s\n", idKereta, stations, times);
            fclose(out);
                    printf("Jadwal berhasil diperbarui!\n");
                } else {
                    printf("Error: Gagal menyimpan perubahan jadwal!\n");
                }
            } else {
                printf("Error: Gagal menghapus jadwal lama sebelum memperbarui!\n");
    }
    
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

void DashboardHapusJadwal() {
    clearScreen();
    printf("\n====== HAPUS JADWAL KERETA ======\n");
    
    // Tampilkan daftar jadwal dan minta user memilih ID kereta langsung
    char* selectedID = TampilkanDaftarJadwalDanPilih();
    
    if (selectedID == NULL) {
        printf("Tidak ada jadwal yang dipilih.\n");
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    char idKereta[50]; // Increased size to handle quoted format
    strcpy(idKereta, selectedID);
    
    // Strip quotes and extra formatting if present
    if (strstr(idKereta, "\"kodeJadwal\"=") != NULL) {
        char cleanId[10];
        // Extract actual ID from "kodeJadwal"='KA050;'
        if (sscanf(idKereta, "\"kodeJadwal\"='%[^;]", cleanId) == 1) {
            strcpy(idKereta, cleanId);
        }
    }
    
    // Konfirmasi penghapusan
    char konfirmasi;
    printf("Apakah Anda yakin ingin menghapus jadwal kereta dengan ID %s? (y/n): ", idKereta);
    scanf("%c", &konfirmasi); while(getchar()!='\n');
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Coba hapus jadwal dengan format baru
        boolean success = HapusJadwalKereta(idKereta);
        
        // Jika gagal, coba dengan format lama (pipe-delimited)
        if (!success) {
            // Buka file langsung untuk menangani format lama
            FILE* file = fopen("jadwal_kereta.txt", "r");
            FILE* tempFile = fopen("jadwal_kereta.tmp", "w");
            
            if (file != NULL && tempFile != NULL) {
                char buffer[1024];
                boolean found = FALSE;
                
                while (fgets(buffer, sizeof(buffer), file)) {
                    // Hapus newline
                    buffer[strcspn(buffer, "\n")] = 0;
                    
                    // PERBAIKAN: Gunakan strdup untuk menyalin buffer sebelum memodifikasinya
                    char* bufferCopy = strdup(buffer);
                    if (!bufferCopy) continue;
                    
                    // Parse format lama: ID|stations|times
                    char* id = strtok(bufferCopy, "|");
                    
                    // Cek apakah ID sama persis (tidak gunakan substring)
                    if (id && strcmp(id, idKereta) == 0) {
                        found = TRUE;
                        // Skip line - jangan tulis ke file sementara
                    } else {
                        // Line ini tidak sesuai dengan ID yang akan dihapus, tulis ke file sementara
                        fprintf(tempFile, "%s\n", buffer);
                    }
                    
                    free(bufferCopy);
                }
                
                fclose(file);
                fclose(tempFile);
                
                // Replace original with temp file
                if (found) {
                    remove("jadwal_kereta.txt");
                    rename("jadwal_kereta.tmp", "jadwal_kereta.txt");
                    success = TRUE;
                } else {
                    remove("jadwal_kereta.tmp");
                }
            }
        }
        
        if (success) {
            printf("Jadwal berhasil dihapus!\n");
        } else {
            printf("Error: Gagal menghapus jadwal atau jadwal tidak ditemukan!\n");
        }
    } else {
        printf("Penghapusan dibatalkan.\n");
    }
    
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

void MenuManajemenJadwal(const char* email) {
    int pilihan;
    boolean keluar = FALSE;
    
    while (!keluar) {
        clearScreen();
        printf("+----------------------------------------------+\n");
        printf("|             MANAJEMEN JADWAL                 |\n");
        printf("+----------------------------------------------+\n");
        printf("| 1. Tampilkan Daftar Jadwal                   |\n");
        printf("| 2. Tambah Jadwal                             |\n");
        printf("| 3. Edit Jadwal                               |\n");
        printf("| 4. Hapus Jadwal                              |\n");
        printf("| 5. Kembali                                   |\n");
        printf("+----------------------------------------------+\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan); while(getchar()!='\n');
        
        switch (pilihan) {
            case 1:
                TampilkanDaftarJadwal();
                break;
            case 2:
                TambahJadwal();
                break;
            case 3:
                EditJadwal();
                break;
            case 4:
                DashboardHapusJadwal();
                break;
            case 5:
                keluar = TRUE;
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
        }
    }
}
