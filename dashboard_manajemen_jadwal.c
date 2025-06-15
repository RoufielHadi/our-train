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
#include "databases.h"

// Prototype for detail view
void TampilkanDetailJadwal(int index);

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
    
    // Meminta input dari user
    char id_kereta[10];
    char tanggal[11];
    char stasiunAsal[50];
    char stasiunTujuan[50];
    Waktu waktuAsal, waktuTujuan;
    
    printf("Masukkan ID Kereta: ");
    scanf("%s", id_kereta); while(getchar()!='\n');
    
    // Validasi apakah kereta dengan ID tersebut ada
    Record infoKereta;
    InisialisasiRecord(&infoKereta);
    if (!BacaInformasiKereta(&infoKereta, id_kereta)) {
        printf("Error: Kereta dengan ID %s tidak ditemukan!\n", id_kereta);
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    printf("Masukkan Tanggal (DD-MM-YYYY): ");
    scanf("%s", tanggal); while(getchar()!='\n');
    
    if (!ValidasiTanggal(tanggal)) {
        printf("Error: Format tanggal tidak valid! Gunakan format DD-MM-YYYY\n");
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    // Cek apakah jadwal dengan ID dan tanggal ini sudah ada
    Record existingJadwal;
    InisialisasiRecord(&existingJadwal);
    if (BacaJadwalKereta(&existingJadwal, id_kereta)) {
        printf("Error: Jadwal untuk kereta dengan ID %s pada tanggal %s sudah ada!\n", id_kereta, tanggal);
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    printf("Masukkan Stasiun Asal: ");
    scanf("%[^\n]", stasiunAsal); while(getchar()!='\n');
    
    printf("Masukkan Waktu Keberangkatan (HH:MM): ");
    scanf("%d:%d", &waktuAsal.jam, &waktuAsal.menit);
    waktuAsal.detik = 0;
    while(getchar()!='\n');
    
    printf("Masukkan Stasiun Tujuan: ");
    scanf("%[^\n]", stasiunTujuan); while(getchar()!='\n');
    
    printf("Masukkan Waktu Kedatangan (HH:MM): ");
    scanf("%d:%d", &waktuTujuan.jam, &waktuTujuan.menit);
    waktuTujuan.detik = 0;
    while(getchar()!='\n');
    
    // Buat jadwal baru
    JadwalHarian jadwalBaru = BuatJadwalKereta(id_kereta, tanggal);
    
    // Tambahkan stasiun ke jadwal
    TambahStasiunKeJadwal(&jadwalBaru, stasiunAsal, waktuAsal);
    TambahStasiunKeJadwal(&jadwalBaru, stasiunTujuan, waktuTujuan);
    
    // Konversi ke record dan simpan
    Record jadwalRecord;
    InisialisasiRecord(&jadwalRecord);
    KonversiJadwalKeRecord(jadwalBaru, &jadwalRecord);
    
    if (SimpanJadwalKereta(&jadwalRecord)) {
        printf("Jadwal berhasil ditambahkan!\n");
    } else {
        printf("Error: Gagal menyimpan jadwal!\n");
    }
    
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

void EditJadwal() {
    clearScreen();
    printf("\n====== EDIT JADWAL KERETA ======\n");
    
    // Tampilkan daftar jadwal terlebih dahulu
    TampilkanDaftarJadwal();
    
    char idKereta[10];
    printf("\nMasukkan ID Kereta yang ingin diedit jadwalnya: ");
    scanf("%s", idKereta); while(getchar()!='\n');
    
    // Baca jadwal dari database
    Record jadwalRecord;
    InisialisasiRecord(&jadwalRecord);
    
    if (!BacaJadwalKereta(&jadwalRecord, idKereta)) {
        printf("Error: Jadwal dengan ID kereta %s tidak ditemukan!\n", idKereta);
        printf("\nTekan Enter untuk kembali..."); 
        getchar();
        return;
    }
    
    // Konversi record ke jadwal
    JadwalHarian jadwal = KonversiRecordKeJadwalKereta(jadwalRecord);
    
    // Tampilkan detail jadwal yang akan diedit
    TampilkanJadwalKereta(jadwal);
    
    // Opsi edit
    printf("\nOpsi Edit:\n");
    printf("1. Edit Tanggal\n");
    printf("2. Edit Stasiun Asal dan Waktu\n");
    printf("3. Edit Stasiun Tujuan dan Waktu\n");
    printf("4. Kembali\n");
    printf("Pilihan: ");
    
    int pilihan;
    scanf("%d", &pilihan); while(getchar()!='\n');
    
    char tanggalBaru[11];
    char stasiunBaru[50];
    Waktu waktuBaru;
    
    switch (pilihan) {
        case 1: {
            printf("Masukkan Tanggal Baru (DD-MM-YYYY): ");
            scanf("%s", tanggalBaru); while(getchar()!='\n');
            
            if (!ValidasiTanggal(tanggalBaru)) {
                printf("Error: Format tanggal tidak valid! Gunakan format DD-MM-YYYY\n");
            } else {
                // Hapus jadwal lama
                HapusJadwalKereta(idKereta);
                
                // Perbarui tanggal
                strcpy(jadwal.tanggal, tanggalBaru);
                
                // Simpan kembali
                Record recordBaru;
                InisialisasiRecord(&recordBaru);
                KonversiJadwalKeRecord(jadwal, &recordBaru);
                
                if (SimpanJadwalKereta(&recordBaru)) {
                    printf("Jadwal berhasil diperbarui!\n");
                } else {
                    printf("Error: Gagal memperbarui jadwal!\n");
                }
            }
            break;
        }
        case 2: {
            // Edit stasiun asal
            if (jadwal.jadwal_rute.head == NULL) {
                printf("Error: Data jadwal tidak lengkap!\n");
                break;
            }
            
            printf("Masukkan Nama Stasiun Asal Baru: ");
            scanf("%[^\n]", stasiunBaru); while(getchar()!='\n');
            
            printf("Masukkan Waktu Keberangkatan Baru (HH:MM): ");
            scanf("%d:%d", &waktuBaru.jam, &waktuBaru.menit);
            waktuBaru.detik = 0;
            while(getchar()!='\n');
            
            // Update stasiun asal
            strcpy(jadwal.jadwal_rute.head->nama_stasiun, stasiunBaru);
            jadwal.jadwal_rute.head->waktu_transit = KonversiKeWaktuSingkat(waktuBaru);
            
            // Update database
            Record recordBaru;
            InisialisasiRecord(&recordBaru);
            KonversiJadwalKeRecord(jadwal, &recordBaru);
            
            if (UpdateJadwalKereta(&recordBaru)) {
                printf("Jadwal berhasil diperbarui!\n");
            } else {
                printf("Error: Gagal memperbarui jadwal!\n");
            }
            break;
        }
        case 3: {
            // Edit stasiun tujuan
            if (jadwal.jadwal_rute.head == NULL || jadwal.jadwal_rute.head->next == NULL) {
                printf("Error: Data jadwal tidak lengkap!\n");
                break;
            }
            
            printf("Masukkan Nama Stasiun Tujuan Baru: ");
            scanf("%[^\n]", stasiunBaru); while(getchar()!='\n');
            
            printf("Masukkan Waktu Kedatangan Baru (HH:MM): ");
            scanf("%d:%d", &waktuBaru.jam, &waktuBaru.menit);
            waktuBaru.detik = 0;
            while(getchar()!='\n');
            
            // Temukan stasiun tujuan (terakhir)
            StasiunTransit* last = jadwal.jadwal_rute.head;
            while (last->next != NULL) last = last->next;
            
            // Update stasiun tujuan
            strcpy(last->nama_stasiun, stasiunBaru);
            last->waktu_transit = KonversiKeWaktuSingkat(waktuBaru);
            
            // Update database
            Record recordBaru;
            InisialisasiRecord(&recordBaru);
            KonversiJadwalKeRecord(jadwal, &recordBaru);
            
            if (UpdateJadwalKereta(&recordBaru)) {
                printf("Jadwal berhasil diperbarui!\n");
            } else {
                printf("Error: Gagal memperbarui jadwal!\n");
            }
            break;
        }
        case 4:
            return;
            
        default:
            printf("Pilihan tidak valid!\n");
            break;
    }
    
    printf("\nTekan Enter untuk kembali..."); 
    getchar();
}

void DashboardHapusJadwal() {
    clearScreen();
    printf("\n====== HAPUS JADWAL KERETA ======\n");
    
    // Tampilkan daftar jadwal terlebih dahulu
    TampilkanDaftarJadwal();
    
    char idKereta[10];
    printf("\nMasukkan ID Kereta yang ingin dihapus jadwalnya: ");
    scanf("%s", idKereta); while(getchar()!='\n');
    
    // Konfirmasi penghapusan
    char konfirmasi;
    printf("Apakah Anda yakin ingin menghapus jadwal kereta dengan ID %s? (y/n): ", idKereta);
    scanf("%c", &konfirmasi); while(getchar()!='\n');
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        if (HapusJadwalKereta(idKereta)) {
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
