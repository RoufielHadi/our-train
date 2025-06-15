/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_manajemen_kasir.h"
#include "clear.h"

// Fungsi untuk menampilkan dashboard manajemen kasir
void TampilkanDashboardManajemenKasir(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            MANAJEMEN AKUN KASIR              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Tambah Akun Kasir                        |\n");
    printf("|  2. Edit Akun Kasir                          |\n");
    printf("|  3. Hapus Akun Kasir                         |\n");
    printf("|  4. Kembali ke Menu Admin                    |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// Fungsi untuk menampilkan form tambah kasir
void TampilkanFormTambahKasir(const char* email, HashPassword* morseTree) {
    // Implementation will be expanded later
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            TAMBAH AKUN KASIR                 |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menampilkan form edit kasir
void TampilkanFormEditKasir(const char* email, HashPassword* morseTree) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            EDIT AKUN KASIR                   |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun kasir dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun kasir                    |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int kasirCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                int tipe = tipeStr ? atoi(tipeStr) : 0;
                
                // Tampilkan hanya akun kasir (tipe 3)
                if (tipe == 3) {
                    kasirCount++;
                    char *userEmail = AmbilNilai(&records[i], "email");
                    char *nama = AmbilNilai(&records[i], "nama");
                    
                    printf("| %-6d | %-35s |\n", kasirCount, 
                           userEmail ? userEmail : "(tidak ada)");
                    printf("|        | Nama: %-31s |\n", 
                           nama ? nama : "(tidak ada)");
                    printf("+----------------------------------------------+\n");
                }
            }
            
            if (kasirCount == 0) {
                printf("| Tidak ada data akun kasir                    |\n");
                printf("+----------------------------------------------+\n");
            } else {
                // Array untuk menyimpan email kasir
                char kasirEmails[100][100]; // Maks 100 kasir, panjang email max 100
                kasirCount = 0;
                
                // Isi array email
                for (i = 0; i < count; i++) {
                    char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 3) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(kasirEmails[kasirCount], userEmail);
                            kasirCount++;
                        }
                    }
                }
                
                // Pilih kasir untuk diedit
                int choice;
                printf("\nMasukkan indeks kasir yang ingin diedit (0 untuk batal): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= kasirCount) {
                    // Edit akun kasir yang dipilih
                    EditKasirAccount(kasirEmails[choice-1], morseTree);
                }
            }
        }
        
        // Bebaskan memori
        for (i = 0; i < count; i++) {
            InisialisasiRecord(&records[i]);
        }
        if (records != NULL) {
            free(records);
        }
    } else {
        printf("| Gagal membaca data akun kasir                |\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menampilkan form hapus kasir
void TampilkanFormHapusKasir(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            HAPUS AKUN KASIR                  |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun kasir dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun kasir                    |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int kasirCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                int tipe = tipeStr ? atoi(tipeStr) : 0;
                
                // Tampilkan hanya akun kasir (tipe 3)
                if (tipe == 3) {
                    kasirCount++;
                    char *userEmail = AmbilNilai(&records[i], "email");
                    char *nama = AmbilNilai(&records[i], "nama");
                    
                    printf("| %-6d | %-35s |\n", kasirCount, 
                           userEmail ? userEmail : "(tidak ada)");
                    printf("|        | Nama: %-31s |\n", 
                           nama ? nama : "(tidak ada)");
                    printf("+----------------------------------------------+\n");
                }
            }
            
            if (kasirCount == 0) {
                printf("| Tidak ada data akun kasir                    |\n");
                printf("+----------------------------------------------+\n");
            } else {
                // Array untuk menyimpan email kasir
                char kasirEmails[100][100]; // Maks 100 kasir, panjang email max 100
                kasirCount = 0;
                
                // Isi array email
                for (i = 0; i < count; i++) {
                    char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 3) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(kasirEmails[kasirCount], userEmail);
                            kasirCount++;
                        }
                    }
                }
                
                // Pilih kasir untuk dihapus
                int choice;
                printf("\nMasukkan indeks kasir yang ingin dihapus (0 untuk batal): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= kasirCount) {
                    // Konfirmasi penghapusan
                    char confirm;
                    printf("\nAnda yakin ingin menghapus kasir dengan email %s? (Y/N): ", kasirEmails[choice-1]);
                    fflush(stdin);
                    scanf(" %c", &confirm);
                    
                    if (confirm == 'Y' || confirm == 'y') {
                        // Hapus akun
                        if (HapusAkunDariFile(kasirEmails[choice-1])) {
                            printf("\nBerhasil menghapus akun kasir dengan email: %s\n", kasirEmails[choice-1]);
                            // Juga hapus rekening jika ada
                            HapusRekeningUser(kasirEmails[choice-1]);
                        } else {
                            printf("\nGagal menghapus akun kasir. Silakan coba lagi.\n");
                        }
                    } else {
                        printf("\nPenghapusan akun kasir dibatalkan.\n");
                    }
                } else if (choice != 0) {
                    printf("\nIndeks akun tidak valid.\n");
                }
            }
        }
        
        // Bebaskan memori
        for (i = 0; i < count; i++) {
            InisialisasiRecord(&records[i]);
        }
        if (records != NULL) {
            free(records);
        }
    } else {
        printf("| Gagal membaca data akun kasir                |\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk mengedit akun kasir
void EditKasirAccount(const char* kasirEmail, HashPassword* morseTree) {
    clearScreen();
    
    // Ambil data kasir dari database
    Record kasirRecord;
    InisialisasiRecord(&kasirRecord);
    if (!BacaAkunUser(&kasirRecord, kasirEmail)) {
        printf("Error: Gagal membaca data akun kasir dari database.\n");
        getch();
        return;
    }
    
    char nama[100];
    char alamat[200];
    char nomor_telepon[20];
    char password[50];
    boolean isValid;
    
    printf("+----------------------------------------------+\n");
    printf("|            EDIT AKUN KASIR                   |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Data Saat Ini:\n");
    printf("Email          : %s\n", kasirEmail);
    printf("Nama           : %s\n", AmbilNilai(&kasirRecord, "nama"));
    printf("Alamat         : %s\n", AmbilNilai(&kasirRecord, "alamat"));
    printf("Nomor Telepon  : %s\n", AmbilNilai(&kasirRecord, "nomor_telepon"));
    
    printf("\nUbah Data Profil (kosongkan jika tidak ingin mengubah):\n");
    
    // Input nama
    printf("Nama Baru         : ");
    getchar(); // Ambil karakter newline dari input sebelumnya
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Hapus newline
    
    // Jika input kosong, gunakan nilai lama
    if (strlen(nama) == 0) {
        strcpy(nama, AmbilNilai(&kasirRecord, "nama"));
    } else {
        // Format nama
        FormatNama(nama);
    }
    
    // Input alamat
    printf("Alamat Baru       : ");
    fgets(alamat, sizeof(alamat), stdin);
    alamat[strcspn(alamat, "\n")] = 0; // Hapus newline
    
    // Jika input kosong, gunakan nilai lama
    if (strlen(alamat) == 0) {
        strcpy(alamat, AmbilNilai(&kasirRecord, "alamat"));
    }
    
    // Input nomor telepon
    do {
        isValid = TRUE;
        printf("No. Telepon Baru  : ");
        fgets(nomor_telepon, sizeof(nomor_telepon), stdin);
        nomor_telepon[strcspn(nomor_telepon, "\n")] = 0; // Hapus newline
        
        // Jika input kosong, gunakan nilai lama
        if (strlen(nomor_telepon) == 0) {
            strcpy(nomor_telepon, AmbilNilai(&kasirRecord, "nomor_telepon"));
            break;
        }
        
        // Validasi nomor telepon
        if (!ValidasiNomorTelepon(nomor_telepon)) {
            printf("Nomor telepon tidak valid. Harus diawali dengan '08' dan memiliki 11-13 digit.\n");
            isValid = FALSE;
        }
    } while (!isValid);
    
    // Input password baru (opsional)
    printf("Password Baru (kosongkan jika tidak ingin mengubah): ");
    char ch;
    int i = 0;
    while ((ch = getch()) != 13) { // 13 adalah kode ASCII untuk Enter
        if (ch == 8) { // 8 adalah kode ASCII untuk Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < sizeof(password) - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    
    // Update data kasir
    UbahNilai(&kasirRecord, "nama", nama);
    UbahNilai(&kasirRecord, "alamat", alamat);
    UbahNilai(&kasirRecord, "nomor_telepon", nomor_telepon);
    
    // Update password jika diisi
    if (strlen(password) > 0) {
        char* hashedPassword = HashPasswordWithMorse(morseTree, password);
        UbahNilai(&kasirRecord, "password", hashedPassword);
        free(hashedPassword);
    }
    
    // Simpan perubahan ke database
    if (UpdateAkunUser(&kasirRecord)) {
        printf("\nData akun kasir berhasil diperbarui!\n");
    } else {
        printf("\nGagal memperbarui data akun kasir.\n");
    }
    
    getch();
}

// Fungsi utama untuk manajemen kasir
void JalankanDashboardManajemenKasir(const char* email, HashPassword* morseTree) {
    int pilihan;
    boolean keluar = FALSE;
    
    while (!keluar) {
        TampilkanDashboardManajemenKasir(email);
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                TampilkanFormTambahKasir(email, morseTree);
                break;
                
            case 2:
                TampilkanFormEditKasir(email, morseTree);
                break;
                
            case 3:
                TampilkanFormHapusKasir(email);
                break;
                
            case 4:
                keluar = TRUE;
                break;
                
            default:
                printf("\nPilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                getch();
                break;
        }
    }
} 
