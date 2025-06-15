/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_akun_saya.h"

// *** TAMPILAN DASHBOARD AKUN SAYA ***
void ShowUserAccountDashboard(const char* email) {
    clearScreen();
    
    // Ambil data user dari database
    Record userRecord;
    InisialisasiRecord(&userRecord);
    if (!BacaAkunUser(&userRecord, email)) {
        printf("Error: Gagal membaca data akun user dari database.\n");
        getch();
        return;
    }
    char* namaUser = AmbilNilai(&userRecord, "nama");
    
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|                AKUN SAYA                     |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Akun: %-40s |\n", namaUser ? namaUser : email);
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Lihat Profil Akun Saya                   |\n");
    printf("|  2. Ubah Profil Saya                         |\n");
    printf("|  3. Ganti Password                           |\n");
    printf("|  4. Informasi Aplikasi                       |\n");
    printf("|  5. Pusat Bantuan                            |\n");
    printf("|  6. Logout                                   |\n");
    printf("|  7. Kembali ke Dashboard Utama               |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU AKUN SAYA ***
void ShowUserProfileView(const char* email) {
    clearScreen();
    
    // Ambil data user dari database
    Record userRecord;
    InisialisasiRecord(&userRecord);
    if (!BacaAkunUser(&userRecord, email)) {
        printf("Error: Gagal membaca data akun user dari database.\n");
        getch();
        return;
    }
    char* emailRec = AmbilNilai(&userRecord, "email");
    char* nama = AmbilNilai(&userRecord, "nama");
    char* alamat = AmbilNilai(&userRecord, "alamat");
    char* nomorTelepon = AmbilNilai(&userRecord, "nomor_telepon");
    
    // Tampilkan profil
    printf("+----------------------------------------------+\n");
    printf("|                 PROFIL SAYA                  |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Data Akun:\n");
    printf("Email          : %s\n", emailRec ? emailRec : email);
    printf("Nama           : %s\n", nama ? nama : "-");
    printf("Alamat         : %s\n", alamat ? alamat : "-");
    printf("Nomor Telepon  : %s\n", nomorTelepon ? nomorTelepon : "-");
    
    printf("\nTekan Enter untuk kembali ke menu akun saya...");
    getch();
}

boolean EditUserProfile(const char* email) {
    clearScreen();
    
    // Ambil data user dari database
    Record userRecord;
    InisialisasiRecord(&userRecord);
    if (!BacaAkunUser(&userRecord, email)) {
        printf("Error: Gagal membaca data akun user dari database.\n");
        getch();
        return FALSE;
    }
    
    char nama[MAX_NAME_LENGTH];
    char alamat[MAX_ADDRESS_LENGTH];
    char nomor_telepon[MAX_PHONE_LENGTH];
    boolean isValid;
    
    printf("+----------------------------------------------+\n");
    printf("|               UBAH PROFIL SAYA               |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Data Saat Ini:\n");
    printf("Nama           : %s\n", AmbilNilai(&userRecord, "nama"));
    printf("Alamat         : %s\n", AmbilNilai(&userRecord, "alamat"));
    printf("Nomor Telepon  : %s\n", AmbilNilai(&userRecord, "nomor_telepon"));
    
    printf("\nUbah Data Profil (kosongkan jika tidak ingin mengubah):\n");
    
    // Input nama
    do {
        isValid = TRUE;
        printf("Nama Baru         : ");
        getchar(); // Ambil karakter newline dari input sebelumnya
        fgets(nama, MAX_NAME_LENGTH, stdin);
        nama[strcspn(nama, "\n")] = 0; // Hapus newline
        
        // Jika input kosong, gunakan nilai lama
        if (strlen(nama) == 0) {
            strcpy(nama, AmbilNilai(&userRecord, "nama"));
            break;
        }
        
        // Format nama
        FormatNama(nama);
    } while (!isValid);
    
    // Input alamat
    printf("Alamat Baru       : ");
    fgets(alamat, MAX_ADDRESS_LENGTH, stdin);
    alamat[strcspn(alamat, "\n")] = 0; // Hapus newline
    
    // Jika input kosong, gunakan nilai lama
    if (strlen(alamat) == 0) {
        strcpy(alamat, AmbilNilai(&userRecord, "alamat"));
    }
    
    // Input nomor telepon
    do {
        isValid = TRUE;
        printf("No. Telepon Baru  : ");
        fgets(nomor_telepon, MAX_PHONE_LENGTH, stdin);
        nomor_telepon[strcspn(nomor_telepon, "\n")] = 0; // Hapus newline
        
        // Jika input kosong, gunakan nilai lama
        if (strlen(nomor_telepon) == 0) {
            strcpy(nomor_telepon, AmbilNilai(&userRecord, "nomor_telepon"));
            break;
        }
        
        // Validasi nomor telepon
        if (!ValidasiNomorTelepon(nomor_telepon)) {
            printf("Nomor telepon tidak valid. Harus diawali dengan '08' dan memiliki 11-13 digit.\n");
            isValid = FALSE;
        }
    } while (!isValid);
    
    // Update data user
    UbahNilai(&userRecord, "nama", nama);
    UbahNilai(&userRecord, "alamat", alamat);
    UbahNilai(&userRecord, "nomor_telepon", nomor_telepon);
    
    // Simpan perubahan menggunakan linked list
    if (UpdateAkunUser(&userRecord)) {
        printf("\nProfil berhasil diperbarui!\n");
        getch();
        return TRUE;
    } else {
        printf("\nGagal memperbarui profil.\n");
        getch();
        return FALSE;
    }
}

boolean ChangeUserPassword(const char* email) {
    clearScreen();
    
    // Ambil data user dari database
    Record userRecord;
    InisialisasiRecord(&userRecord);
    if (!BacaAkunUser(&userRecord, email)) {
        printf("Error: Gagal membaca data akun user dari database.\n");
        getch();
        return FALSE;
    }
    
    // Inisialisasi struktur pohon Morse untuk hashing password
    HashPassword* morseTree = NULL;
    InisialisasiMorseCode(&morseTree);
    
    char old_password[MAX_PASSWORD_LENGTH];
    char new_password[MAX_PASSWORD_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];
    int i;
    char ch;
    
    printf("+----------------------------------------------+\n");
    printf("|               GANTI PASSWORD                 |\n");
    printf("+----------------------------------------------+\n\n");
    
    // Input password lama
    printf("Masukkan password lama: ");
    i = 0;
    while ((ch = getch()) != 13) { // 13 adalah kode ASCII untuk Enter
        if (ch == 8) { // 8 adalah kode ASCII untuk Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PASSWORD_LENGTH - 1) {
            old_password[i++] = ch;
            printf("*");
        }
    }
    old_password[i] = '\0';
    printf("\n");
    
    // Input password baru
    printf("Masukkan password baru: ");
    i = 0;
    while ((ch = getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PASSWORD_LENGTH - 1) {
            new_password[i++] = ch;
            printf("*");
        }
    }
    new_password[i] = '\0';
    printf("\n");
    
    // Konfirmasi password baru
    printf("Konfirmasi password baru: ");
    i = 0;
    while ((ch = getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PASSWORD_LENGTH - 1) {
            confirm_password[i++] = ch;
            printf("*");
        }
    }
    confirm_password[i] = '\0';
    printf("\n");
    
    // Validasi password baru
    if (strcmp(new_password, confirm_password) != 0) {
        printf("Konfirmasi password tidak sesuai.\n");
        getch();
        return FALSE;
    }
    
    // Verifikasi password lama menggunakan hash Morse
    char* storedHash = AmbilNilai(&userRecord, "password");
    if (storedHash == NULL || !VerifyPassword(morseTree, old_password, storedHash)) {
        printf("\nPassword lama tidak sesuai.\n");
        getch();
        return FALSE;
    }
    // Hash password baru
    char* newHash = HashPasswordWithMorse(morseTree, new_password);
    if (newHash == NULL) {
        printf("\nGagal membuat hash password baru.\n");
        getch();
        return FALSE;
    }
    UbahNilai(&userRecord, "password", newHash);
    free(newHash);
    // Simpan perubahan ke database
    if (UpdateAkunUser(&userRecord)) {
        printf("\nPassword berhasil diubah!\n");
        getch();
        return TRUE;
    } else {
        printf("\nGagal memperbarui password di database.\n");
        getch();
        return FALSE;
    }
}

void ShowAppInformation() {
    clearScreen();
    
    printf("+----------------------------------------------+\n");
    printf("|            INFORMASI APLIKASI                |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("OurTrain - Aplikasi Reservasi Tiket Kereta Api v1.0\n\n");
    printf("Dikembangkan oleh:\n");
    printf("- Roufiel Hadi (241524028)\n");
    printf("- Dan Tim Pengembang Lainnya\n\n");
    
    printf("Aplikasi ini merupakan sistem reservasi tiket kereta api\n");
    printf("yang menyediakan fitur-fitur berikut:\n");
    printf("- Pembelian tiket kereta api\n");
    printf("- Melihat jadwal keberangkatan kereta\n");
    printf("- Manajemen tiket yang telah dibeli\n");
    printf("- Manajemen akun pengguna\n");
    printf("- Sistem pembayaran terintegrasi\n\n");
    
    printf("Hak Cipta © 2023 OurTrain\n");
    
    printf("\nTekan Enter untuk kembali ke menu akun saya...");
    getch();
}

void ShowHelpCenter() {
    clearScreen();
    
    printf("+----------------------------------------------+\n");
    printf("|               PUSAT BANTUAN                  |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Jika Anda memiliki pertanyaan atau masalah, silakan hubungi:\n\n");
    printf("Email Support   : support@ourtrain.com\n");
    printf("No. Telepon     : 0800-123-4567\n");
    printf("Jam Operasional : Senin - Jumat, 08.00 - 17.00 WIB\n\n");
    
    printf("FAQ:\n\n");
    printf("1. Bagaimana cara memesan tiket?\n");
    printf("   Pilih menu \"Pembelian Tiket\" pada dashboard utama,\n");
    printf("   lalu ikuti petunjuk yang diberikan.\n\n");
    
    printf("2. Bagaimana cara melihat tiket saya?\n");
    printf("   Pilih menu \"Tiket Saya\" pada dashboard utama.\n\n");
    
    printf("3. Bagaimana cara mengubah informasi akun?\n");
    printf("   Pilih menu \"Akun Saya\" > \"Ubah Profil Saya\".\n\n");
    
    printf("4. Bagaimana cara top up saldo?\n");
    printf("   Pilih menu \"Rekening Saya\" > \"Top Up Saldo\".\n\n");
    
    printf("\nTekan Enter untuk kembali ke menu akun saya...");
    getch();
}

// *** FUNGSI UTAMA ***
void RunUserAccountDashboard(const char* email) {
    int choice;
    
    do {
        ShowUserAccountDashboard(email);
        // Baca pilihan user
        char input[10];
        if (fgets(input, sizeof(input), stdin)) {
            choice = atoi(input);
        } else {
            choice = 0;
        }
        
        switch (choice) {
            case 1:
                ShowUserProfileView(email);
                break;
                
            case 2:
                EditUserProfile(email);
                break;
                
            case 3:
                ChangeUserPassword(email);
                break;
                
            case 4:
                ShowAppInformation();
                break;
                
            case 5:
                ShowHelpCenter();
                break;
                
            case 6:
                // Logout: kembali ke menu utama autentikasi (tanpa welcome screen)
                printf("\nAnda telah berhasil logout.\n");
                printf("Tekan Enter untuk kembali ke menu utama...");
                getch();
                // Set flag logout agar keluar dari dashboard user
                logoutFlag = TRUE;
                return;
                
            case 7:
                // Kembali ke Dashboard Utama
                printf("\nKembali ke dashboard utama...\n");
                return;
                
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getch();
                break;
        }
    } while (1);
} 