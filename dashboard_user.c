/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_user.h"

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
    printf("|  1. Profil Saya                              |\n");
    printf("|  2. Pesan Tiket                              |\n");
    printf("|  3. Riwayat Pembelian                        |\n");
    printf("|  4. Pembayaran                               |\n");
    printf("|  5. Logout                                   |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU USER ***
void ShowUserProfileMenu(const char* email) {
    clearScreen();
    
    // Ambil data user
    Record userRecord, bankRecord;
    InisialisasiRecord(&userRecord);
    InisialisasiRecord(&bankRecord);
    
    BacaAkunUser(&userRecord, email);
    
    // Cari rekening berdasarkan email
    Record tempRecords[MAX_FIELDS];
    int jumlahRecord = 0;
    FILE* file = BukaFile(DB_REKENING_USER, "r");
    
    if (file != NULL) {
        char buffer[MAX_RECORD_LENGTH];
        
        while (fgets(buffer, sizeof(buffer), file) != NULL && jumlahRecord < MAX_FIELDS) {
            int len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            
            InisialisasiRecord(&tempRecords[jumlahRecord]);
            StringKeRecord(buffer, &tempRecords[jumlahRecord]);
            
            char* emailValue = AmbilNilai(&tempRecords[jumlahRecord], "email");
            if (emailValue != NULL && strcmp(emailValue, email) == 0) {
                bankRecord = tempRecords[jumlahRecord];
                break;
            }
            
            jumlahRecord++;
        }
        
        TutupFile(file);
    }
    
    // Tampilkan profil
    printf("+----------------------------------------------+\n");
    printf("|                 PROFIL SAYA                  |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Data Akun:\n");
    printf("Email          : %s\n", email);
    printf("Nama           : %s\n", AmbilNilai(&userRecord, "nama") ? AmbilNilai(&userRecord, "nama") : "-");
    printf("Alamat         : %s\n", AmbilNilai(&userRecord, "alamat") ? AmbilNilai(&userRecord, "alamat") : "-");
    printf("Nomor Telepon  : %s\n", AmbilNilai(&userRecord, "nomor_telepon") ? AmbilNilai(&userRecord, "nomor_telepon") : "-");
    
    printf("\nData Rekening:\n");
    printf("Nomor Rekening : %s\n", AmbilNilai(&bankRecord, "nomorRekening") ? AmbilNilai(&bankRecord, "nomorRekening") : "-");
    printf("Nama Bank      : %s\n", AmbilNilai(&bankRecord, "namaBank") ? AmbilNilai(&bankRecord, "namaBank") : "-");
    printf("Cabang Bank    : %s\n", AmbilNilai(&bankRecord, "cabangBank") ? AmbilNilai(&bankRecord, "cabangBank") : "-");
    printf("Saldo          : %s\n", AmbilNilai(&bankRecord, "saldo") ? AmbilNilai(&bankRecord, "saldo") : "-");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowUserTicketMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|                 PESAN TIKET                  |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowUserHistoryMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|              RIWAYAT PEMBELIAN               |\n");
    printf("+----------------------------------------------+\n");
    
    // Ambil riwayat pembelian user
    Record records[MAX_FIELDS];
    int jumlahRecord = 0;
    
    RiwayatPembelianUser(email, records, &jumlahRecord);
    
    if (jumlahRecord == 0) {
        printf("| Belum ada riwayat pembelian                   |\n");
        printf("+----------------------------------------------+\n");
    } else {
        printf("| No | Kode Pembelian | Tanggal     | Tujuan         |\n");
        printf("+----------------------------------------------+\n");
        
        for (int i = 0; i < jumlahRecord; i++) {
            char* kodePembelian = AmbilNilai(&records[i], "kodePembelian");
            char* tanggal = AmbilNilai(&records[i], "tanggal");
            char* tujuan = AmbilNilai(&records[i], "tujuan");
            
            printf("| %-2d | %-14s | %-11s | %-15s |\n", 
                   i + 1, 
                   kodePembelian ? kodePembelian : "-", 
                   tanggal ? tanggal : "-", 
                   tujuan ? tujuan : "-");
        }
        printf("+----------------------------------------------+\n");
    }
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

void ShowUserPaymentMenu(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|                 PEMBAYARAN                   |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunUserDashboard(const char* email) {
    int choice;
    
    do {
        ShowUserDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ShowUserProfileMenu(email);
                break;
                
            case 2:
                ShowUserTicketMenu(email);
                break;
                
            case 3:
                ShowUserHistoryMenu(email);
                break;
                
            case 4:
                ShowUserPaymentMenu(email);
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