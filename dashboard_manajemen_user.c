/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_manajemen_user.h"
#include "dashboard_manajemen_kasir.h"
#include "dashboard_manajemen_mesin.h"
#include "clear.h"
#include "hash_password.h"
#include "implementasi_morse.h"
#include <string.h>

// Variable global untuk morse tree
extern HashPassword* morseTree;

// Fungsi untuk mendekode hash morse menjadi plaintext
char* DecodeMorseHash(const char* hash) {
    // Implementasi sederhana untuk mengembalikan password berdasarkan hash
    if (hash == NULL) {
        return strdup("(tidak ada)");
    }
    
    // Gunakan fungsi DecodeMorse untuk mengubah hash XOS menjadi kode morse
    char* morseCode = DecodeMorse(hash);
    if (morseCode == NULL) {
        return strdup("(tidak dapat didekode)");
    }
    
    // Gunakan fungsi KonversiMorseKeString untuk mengubah kode morse menjadi plaintext
    char* plaintext = KonversiMorseKeString(morseTree, morseCode);
    free(morseCode);
    
    if (plaintext == NULL) {
        return strdup("(tidak dapat didekode)");
    }
    
    return plaintext;
}

// Fungsi untuk menampilkan dashboard manajemen user
void ShowUserManagementDashboard(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            MANAJEMEN AKUN USER               |\n");
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Lihat Informasi Akun User                |\n");
    printf("|  2. Tambah Akun Kasir & Mesin                |\n");
    printf("|  3. Edit Akun Kasir/Mesin                    |\n");
    printf("|  4. Hapus Akun Kasir/Mesin                   |\n");
    printf("|  5. Hapus Akun User                          |\n");
    printf("|  6. Lihat Informasi Akun Kasir               |\n");
    printf("|  7. Lihat Informasi Akun Mesin               |\n");
    printf("|  8. Lihat Informasi Akun Admin               |\n");
    printf("|  9. Kembali ke Dashboard Admin               |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// Fungsi untuk menampilkan daftar akun user
void ShowUserAccounts(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            DAFTAR AKUN USER                  |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun user dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun user                     |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| No. | Nama                | Email             \n");
            printf("+----------------------------------------------+\n");
            
            int userCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "is_admin");
                int tipe = tipeStr ? atoi(tipeStr) : 1; // Default: user biasa
                
                // Tampilkan hanya user biasa (tipe 1)
                if (tipe == 1) {
                    userCount++;
                    char *nama = AmbilNilai(&records[i], "nama");
                    char *userEmail = AmbilNilai(&records[i], "email");
                    char *alamat = AmbilNilai(&records[i], "alamat");
                    char *noTelp = AmbilNilai(&records[i], "nomor_telepon");
                    
                    printf("| %-3d | %-19s | %-18s\n", userCount, 
                           nama ? nama : "(tidak ada)", 
                           userEmail ? userEmail : "(tidak ada)");
                    
                    printf("|     | Alamat: %-34s\n", alamat ? alamat : "(tidak ada)");
                    printf("|     | No. Telp: %-32s\n", noTelp ? noTelp : "(tidak ada)");
                    printf("+----------------------------------------------+\n");
                }
            }
            
            if (userCount == 0) {
                printf("| Tidak ada data akun user biasa               |\n");
                printf("+----------------------------------------------+\n");
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
        printf("| Gagal membaca data akun user                |\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menampilkan detail akun user dan rekeningnya
void ShowUserAccountDetail(const char* email, const char* userEmail) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|         DETAIL INFORMASI AKUN USER           |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data akun dari database
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    if (BacaAkunUser(&userRecord, userEmail)) {
        // Ambil data user
        char *nama = AmbilNilai(&userRecord, "nama");
        char *alamat = AmbilNilai(&userRecord, "alamat");
        char *noTelp = AmbilNilai(&userRecord, "nomor_telepon");
        
        // Cek kedua field tipe akun untuk kompatibilitas
        char *tipeStr = AmbilNilai(&userRecord, "tipe_akun");
        if (tipeStr == NULL) {
            tipeStr = AmbilNilai(&userRecord, "is_admin");
        }
        int tipe = tipeStr ? atoi(tipeStr) : 1; // Default: user biasa
        
        // Tampilkan informasi akun
        printf("Detail Akun:\n");
        printf("Email          : %s\n", userEmail);
        printf("Nama           : %s\n", nama ? nama : "(tidak ada)");
        printf("Alamat         : %s\n", alamat ? alamat : "(tidak ada)");
        printf("Nomor Telepon  : %s\n", noTelp ? noTelp : "(tidak ada)");
        
        // Tampilkan tipe akun yang benar
        const char* tipeAkun;
        switch (tipe) {
            case 1:
                tipeAkun = "User Biasa";
                break;
            case 2:
                tipeAkun = "Admin";
                break;
            case 3:
                tipeAkun = "Kasir";
                break;
            case 4:
                tipeAkun = "Mesin";
                break;
            default:
                tipeAkun = "Tidak Diketahui";
        }
        printf("Tipe Akun      : %s\n", tipeAkun);
        
        // Tampilkan password (dalam bentuk plaintext)
        char *passwordHash = AmbilNilai(&userRecord, "password");
        if (passwordHash) {
            char *decodedPassword = DecodeMorseHash(passwordHash);
            printf("Password       : %s\n", decodedPassword);
            free(decodedPassword);
        } else {
            printf("Password       : (tidak ada)\n");
        }
        
        // Baca data rekening
        Record rekeningRecord;
        InisialisasiRecord(&rekeningRecord);
        
        printf("\n+----------------------------------------------+\n");
        printf("|       DETAIL INFORMASI REKENING USER         |\n");
        printf("+----------------------------------------------+\n");
        
        if (BacaRekeningUser(&rekeningRecord, userEmail)) {
            char *noRekening = AmbilNilai(&rekeningRecord, "nomorRekening");
            char *saldo = AmbilNilai(&rekeningRecord, "saldo");
            char *pinHash = AmbilNilai(&rekeningRecord, "pin");
            
            printf("Nomor Rekening : %s\n", noRekening ? noRekening : "(tidak ada)");
            printf("Saldo          : %s\n", saldo ? saldo : "0");
            
            // Tampilkan PIN dalam bentuk plaintext
            if (pinHash) {
                char *decodedPin = DecodeMorseHash(pinHash);
                printf("PIN            : %s\n", decodedPin);
                free(decodedPin);
            } else {
                printf("PIN            : (tidak ada)\n");
            }
        } else {
            printf("Tidak ada data rekening untuk user ini.\n");
        }
    } else {
        printf("Gagal membaca data akun user dengan email: %s\n", userEmail);
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk melihat informasi user yang terdaftar
void ViewUserInformation(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|         LIHAT INFORMASI AKUN USER            |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun user dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun user                     |\n");
            printf("\nTekan Enter untuk kembali...");
            getch();
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int userCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                int tipe = tipeStr ? atoi(tipeStr) : 1; // Default: user biasa
                
                // Tampilkan hanya user biasa (tipe 1)
                if (tipe == 1) {
                    userCount++;
                    char *userEmail = AmbilNilai(&records[i], "email");
                    
                    printf("| %-6d | %-35s |\n", userCount, 
                           userEmail ? userEmail : "(tidak ada)");
                }
            }
            
            printf("+----------------------------------------------+\n");
            
            if (userCount == 0) {
                printf("| Tidak ada data akun user biasa               |\n");
                printf("+----------------------------------------------+\n");
            } else {
                // Array untuk menyimpan email user
                char userEmails[100][100]; // Maks 100 user, panjang email max 100
                userCount = 0;
                
                // Isi array email
                for (i = 0; i < count; i++) {
                    char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                    int tipe = tipeStr ? atoi(tipeStr) : 1;
                    
                    if (tipe == 1) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(userEmails[userCount], userEmail);
                            userCount++;
                        }
                    }
                }
                
                // Pilih user untuk dilihat detailnya
                int choice;
                printf("\nMasukkan indeks untuk melihat detail (0 untuk kembali): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= userCount) {
                    ShowUserAccountDetail(email, userEmails[choice-1]);
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
        printf("| Gagal membaca data akun user                |\n");
        printf("\nTekan Enter untuk kembali...");
        getch();
    }
}

// Fungsi untuk menghapus akun user berdasarkan pilihan indeks
void DeleteUserByIndex(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            HAPUS AKUN USER                   |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun user dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun user                     |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int userCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                int tipe = tipeStr ? atoi(tipeStr) : 1; // Default: user biasa
                
                // Tampilkan hanya user biasa (tipe 1)
                if (tipe == 1) {
                    userCount++;
                    char *userEmail = AmbilNilai(&records[i], "email");
                    char *nama = AmbilNilai(&records[i], "nama");
                    
                    printf("| %-6d | %-35s |\n", userCount, 
                           userEmail ? userEmail : "(tidak ada)");
                    printf("|        | Nama: %-31s |\n", 
                           nama ? nama : "(tidak ada)");
                    printf("+----------------------------------------------+\n");
                }
            }
            
            if (userCount == 0) {
                printf("| Tidak ada data akun user biasa               |\n");
                printf("+----------------------------------------------+\n");
            } else {
                // Array untuk menyimpan email user
                char userEmails[100][100]; // Maks 100 user, panjang email max 100
                userCount = 0;
                
                // Isi array email
                for (i = 0; i < count; i++) {
                    char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                    int tipe = tipeStr ? atoi(tipeStr) : 1;
                    
                    if (tipe == 1) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(userEmails[userCount], userEmail);
                            userCount++;
                        }
                    }
                }
                
                // Pilih user untuk dihapus
                int choice;
                printf("\nMasukkan indeks user yang ingin dihapus (0 untuk batal): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= userCount) {
                    // Konfirmasi penghapusan
                    char confirm;
                    printf("\nAnda yakin ingin menghapus user dengan email %s? (Y/N): ", userEmails[choice-1]);
                    fflush(stdin);
                    scanf(" %c", &confirm);
                    
                    if (confirm == 'Y' || confirm == 'y') {
                        // Hapus akun
                        if (HapusAkunDariFile(userEmails[choice-1])) {
                            printf("\nBerhasil menghapus akun dengan email: %s\n", userEmails[choice-1]);
                            // Juga hapus rekening jika ada
                            HapusRekeningUser(userEmails[choice-1]);
                        } else {
                            printf("\nGagal menghapus akun. Silakan coba lagi.\n");
                        }
                    } else {
                        printf("\nPenghapusan akun dibatalkan.\n");
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
        printf("| Gagal membaca data akun user                |\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menghapus akun user (versi lama, tetap dipertahankan untuk kompatibilitas)
void DeleteUserAccount(const char* email) {
    DeleteUserByIndex(email); // Gunakan fungsi baru
}

// Fungsi untuk menambahkan akun kasir dan mesin secara berpasangan
void TambahAkunKasirDanMesin(const char* email, HashPassword* morseTree) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|       TAMBAH AKUN KASIR & MESIN              |\n");
    printf("+----------------------------------------------+\n");
    
    // Input informasi stasiun
    char nama_stasiun[100];
    char alamat_stasiun[200];
    char nomor_telepon_kasir[20];
    char nomor_telepon_mesin[20];
    
    printf("Masukkan Nama Stasiun: ");
    fflush(stdin);
    gets(nama_stasiun);
    
    printf("Masukkan Alamat Stasiun: ");
    fflush(stdin);
    gets(alamat_stasiun);
    
    printf("Masukkan Nomor Telepon Kasir: ");
    fflush(stdin);
    gets(nomor_telepon_kasir);
    
    printf("Masukkan Nomor Telepon Mesin: ");
    fflush(stdin);
    gets(nomor_telepon_mesin);
    
    // Format nama stasiun untuk email
    char nama_stasiun_email[100];
    strcpy(nama_stasiun_email, nama_stasiun);
    
    // Ubah spasi menjadi underscore untuk email
    int i;
    for (i = 0; i < strlen(nama_stasiun_email); i++) {
        if (nama_stasiun_email[i] == ' ') {
            nama_stasiun_email[i] = '_';
        }
        // Ubah ke lowercase
        nama_stasiun_email[i] = tolower(nama_stasiun_email[i]);
    }
    
    // Buat akun kasir dengan format email kasir.namastasiun@ourtrain.com
    char email_kasir[100];
    sprintf(email_kasir, "kasir.%s@ourtrain.com", nama_stasiun_email);
    
    // Buat akun mesin dengan format mesin.namastasiun@ourtrain.com
    char email_mesin[100];
    sprintf(email_mesin, "mesin.%s@ourtrain.com", nama_stasiun_email);
    
    // Password default
    char password_kasir[] = "Kasir123";
    char password_mesin[] = "Mesin123";
    
    // Nama lengkap untuk akun
    char nama_kasir[100];
    sprintf(nama_kasir, "Kasir Stasiun %s", nama_stasiun);
    
    char nama_mesin[100];
    sprintf(nama_mesin, "Mesin Stasiun %s", nama_stasiun);
    
    // Tambahkan akun kasir
    if (TambahAkunKasir(nama_stasiun_email, nama_kasir, alamat_stasiun, nomor_telepon_kasir, password_kasir, morseTree)) {
        printf("\nBerhasil menambahkan akun kasir:\n");
        printf("Email: %s\n", email_kasir);
        printf("Password: %s\n", password_kasir);
        
        // Buat rekening untuk kasir
        Record rekeningKasir;
        InisialisasiRecord(&rekeningKasir);
        
        // Set nilai rekening
        TambahField(&rekeningKasir, "email", email_kasir);
        TambahField(&rekeningKasir, "nomorRekening", "KSR123456789");
        TambahField(&rekeningKasir, "saldo", "0");
        
        // Hash PIN default (123456)
        char* hashedPin = HashPasswordWithMorse(morseTree, "123456");
        TambahField(&rekeningKasir, "pin", hashedPin);
        free(hashedPin);
        
        // Simpan rekening ke database
        if (SimpanRekeningUser(&rekeningKasir)) {
            printf("Rekening kasir berhasil dibuat.\n");
        } else {
            printf("Gagal membuat rekening kasir.\n");
        }
    } else {
        printf("\nGagal menambahkan akun kasir. Email mungkin sudah terdaftar.\n");
    }
    
    // Tambahkan akun mesin
    if (TambahAkunMesin(nama_stasiun_email, nama_mesin, alamat_stasiun, nomor_telepon_mesin, password_mesin, morseTree)) {
        printf("\nBerhasil menambahkan akun mesin:\n");
        printf("Email: %s\n", email_mesin);
        printf("Password: %s\n", password_mesin);
        
        // Buat rekening untuk mesin
        Record rekeningMesin;
        InisialisasiRecord(&rekeningMesin);
        
        // Set nilai rekening
        TambahField(&rekeningMesin, "email", email_mesin);
        TambahField(&rekeningMesin, "nomorRekening", "MSN123456789");
        TambahField(&rekeningMesin, "saldo", "0");
        
        // Hash PIN default (123456)
        char* hashedPin = HashPasswordWithMorse(morseTree, "123456");
        TambahField(&rekeningMesin, "pin", hashedPin);
        free(hashedPin);
        
        // Simpan rekening ke database
        if (SimpanRekeningUser(&rekeningMesin)) {
            printf("Rekening mesin berhasil dibuat.\n");
        } else {
            printf("Gagal membuat rekening mesin.\n");
        }
    } else {
        printf("\nGagal menambahkan akun mesin. Email mungkin sudah terdaftar.\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi utama untuk manajemen user
void RunUserManagementDashboard(const char* email) {
    int pilihan;
    boolean keluar = FALSE;
    
    while (!keluar) {
        ShowUserManagementDashboard(email);
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                // Lihat Informasi Akun User
                ViewUserInformation(email);
                break;
                
            case 2:
                // Tambah Akun Kasir & Mesin (berpasangan)
                TambahAkunKasirDanMesin(email, morseTree);
                break;
                
            case 3:
                // Edit Akun Kasir/Mesin
                printf("\n+----------------------------------------------+\n");
                printf("| Pilih jenis akun untuk diedit:               |\n");
                printf("|  1. Akun Kasir                               |\n");
                printf("|  2. Akun Mesin                               |\n");
                printf("|  3. Kembali                                  |\n");
                printf("+----------------------------------------------+\n");
                printf("Pilihan: ");
                
                int editChoice;
                scanf("%d", &editChoice);
                
                switch (editChoice) {
                    case 1:
                        TampilkanFormEditKasir(email, morseTree);
                        break;
                    case 2:
                        TampilkanFormEditMesin(email, morseTree);
                        break;
                    case 3:
                        break;
                    default:
                        printf("\nPilihan tidak valid!\n");
                        printf("Tekan Enter untuk melanjutkan...");
                        getch();
                        break;
                }
                break;
                
            case 4:
                // Hapus Akun Kasir/Mesin
                printf("\n+----------------------------------------------+\n");
                printf("| Pilih jenis akun untuk dihapus:              |\n");
                printf("|  1. Akun Kasir                               |\n");
                printf("|  2. Akun Mesin                               |\n");
                printf("|  3. Kembali                                  |\n");
                printf("+----------------------------------------------+\n");
                printf("Pilihan: ");
                
                int deleteChoice;
                scanf("%d", &deleteChoice);
                
                switch (deleteChoice) {
                    case 1:
                        TampilkanFormHapusKasir(email);
                        break;
                    case 2:
                        TampilkanFormHapusMesin(email);
                        break;
                    case 3:
                        break;
                    default:
                        printf("\nPilihan tidak valid!\n");
                        printf("Tekan Enter untuk melanjutkan...");
                        getch();
                        break;
                }
                break;
                
            case 5:
                // Hapus Akun User
                DeleteUserByIndex(email);
                break;
                
            case 6:
                // Lihat Informasi Akun Kasir
                ViewKasirAccounts(email);
                break;
                
            case 7:
                // Lihat Informasi Akun Mesin
                ViewMesinAccounts(email);
                break;
                
            case 8:
                // Lihat Informasi Akun Admin
                ViewAdminAccounts(email);
                break;
                
            case 9:
                // Kembali ke Dashboard Admin
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

// Fungsi untuk melihat informasi akun kasir
void ViewKasirAccounts(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|         LIHAT INFORMASI AKUN KASIR           |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun user dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun                         |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int kasirCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                if (tipeStr == NULL) {
                    tipeStr = AmbilNilai(&records[i], "is_admin");
                }
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
            
            printf("+----------------------------------------------+\n");
            
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
                    if (tipeStr == NULL) {
                        tipeStr = AmbilNilai(&records[i], "is_admin");
                    }
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 3) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(kasirEmails[kasirCount], userEmail);
                            kasirCount++;
                        }
                    }
                }
                
                // Pilih kasir untuk dilihat detailnya
                int choice;
                printf("\nMasukkan indeks untuk melihat detail (0 untuk kembali): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= kasirCount) {
                    ShowUserAccountDetail(email, kasirEmails[choice-1]);
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
        printf("| Gagal membaca data akun                     |\n");
        printf("\nTekan Enter untuk kembali...");
        getch();
    }
}

// Fungsi untuk melihat informasi akun mesin
void ViewMesinAccounts(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|         LIHAT INFORMASI AKUN MESIN           |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun user dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun                         |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int mesinCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                if (tipeStr == NULL) {
                    tipeStr = AmbilNilai(&records[i], "is_admin");
                }
                int tipe = tipeStr ? atoi(tipeStr) : 0;
                
                // Tampilkan hanya akun mesin (tipe 4)
                if (tipe == 4) {
                    mesinCount++;
                    char *userEmail = AmbilNilai(&records[i], "email");
                    char *nama = AmbilNilai(&records[i], "nama");
                    
                    printf("| %-6d | %-35s |\n", mesinCount, 
                           userEmail ? userEmail : "(tidak ada)");
                    printf("|        | Nama: %-31s |\n", 
                           nama ? nama : "(tidak ada)");
                    printf("+----------------------------------------------+\n");
                }
            }
            
            printf("+----------------------------------------------+\n");
            
            if (mesinCount == 0) {
                printf("| Tidak ada data akun mesin                    |\n");
                printf("+----------------------------------------------+\n");
            } else {
                // Array untuk menyimpan email mesin
                char mesinEmails[100][100]; // Maks 100 mesin, panjang email max 100
                mesinCount = 0;
                
                // Isi array email
                for (i = 0; i < count; i++) {
                    char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                    if (tipeStr == NULL) {
                        tipeStr = AmbilNilai(&records[i], "is_admin");
                    }
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 4) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(mesinEmails[mesinCount], userEmail);
                            mesinCount++;
                        }
                    }
                }
                
                // Pilih mesin untuk dilihat detailnya
                int choice;
                printf("\nMasukkan indeks untuk melihat detail (0 untuk kembali): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= mesinCount) {
                    ShowUserAccountDetail(email, mesinEmails[choice-1]);
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
        printf("| Gagal membaca data akun                     |\n");
        printf("\nTekan Enter untuk kembali...");
        getch();
    }
}

// Fungsi untuk melihat informasi akun admin
void ViewAdminAccounts(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|         LIHAT INFORMASI AKUN ADMIN           |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun user dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun                         |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int adminCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                if (tipeStr == NULL) {
                    tipeStr = AmbilNilai(&records[i], "is_admin");
                }
                int tipe = tipeStr ? atoi(tipeStr) : 0;
                
                // Tampilkan hanya akun admin (tipe 2)
                if (tipe == 2) {
                    adminCount++;
                    char *userEmail = AmbilNilai(&records[i], "email");
                    char *nama = AmbilNilai(&records[i], "nama");
                    
                    printf("| %-6d | %-35s |\n", adminCount, 
                           userEmail ? userEmail : "(tidak ada)");
                    printf("|        | Nama: %-31s |\n", 
                           nama ? nama : "(tidak ada)");
                    printf("+----------------------------------------------+\n");
                }
            }
            
            printf("+----------------------------------------------+\n");
            
            if (adminCount == 0) {
                printf("| Tidak ada data akun admin                    |\n");
                printf("+----------------------------------------------+\n");
            } else {
                // Array untuk menyimpan email admin
                char adminEmails[100][100]; // Maks 100 admin, panjang email max 100
                adminCount = 0;
                
                // Isi array email
                for (i = 0; i < count; i++) {
                    char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
                    if (tipeStr == NULL) {
                        tipeStr = AmbilNilai(&records[i], "is_admin");
                    }
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 2) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(adminEmails[adminCount], userEmail);
                            adminCount++;
                        }
                    }
                }
                
                // Pilih admin untuk dilihat detailnya
                int choice;
                printf("\nMasukkan indeks untuk melihat detail (0 untuk kembali): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= adminCount) {
                    ShowUserAccountDetail(email, adminEmails[choice-1]);
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
        printf("| Gagal membaca data akun                     |\n");
        printf("\nTekan Enter untuk kembali...");
        getch();
    }
}
