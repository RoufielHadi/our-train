/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_manajemen_mesin.h"
#include "clear.h"

// Fungsi untuk menampilkan dashboard manajemen mesin
void TampilkanDashboardManajemenMesin(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            MANAJEMEN AKUN MESIN              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Tambah Akun Mesin                        |\n");
    printf("|  2. Edit Akun Mesin                          |\n");
    printf("|  3. Hapus Akun Mesin                         |\n");
    printf("|  4. Kembali ke Menu Admin                    |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// Fungsi untuk menampilkan form tambah mesin
void TampilkanFormTambahMesin(const char* email, HashPassword* morseTree) {
    // Implementation will be expanded later
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            TAMBAH AKUN MESIN                 |\n");
    printf("+----------------------------------------------+\n");
    printf("| Fitur ini akan tersedia pada versi mendatang |\n");
    printf("+----------------------------------------------+\n");
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menampilkan form edit mesin
void TampilkanFormEditMesin(const char* email, HashPassword* morseTree) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            EDIT AKUN MESIN                   |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun mesin dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun mesin                    |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int mesinCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
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
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 4) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(mesinEmails[mesinCount], userEmail);
                            mesinCount++;
                        }
                    }
                }
                
                // Pilih mesin untuk diedit
                int choice;
                printf("\nMasukkan indeks mesin yang ingin diedit (0 untuk batal): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= mesinCount) {
                    // Edit akun mesin yang dipilih
                    EditMesinAccount(mesinEmails[choice-1], morseTree);
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
        printf("| Gagal membaca data akun mesin                |\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menampilkan form hapus mesin
void TampilkanFormHapusMesin(const char* email) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|            HAPUS AKUN MESIN                  |\n");
    printf("+----------------------------------------------+\n");
    
    // Baca data dari file
    Record *records;
    int count = 0;
    int i; // Deklarasi variabel loop di luar
    
    // Load data akun mesin dari database
    if (BacaSemuaAkunUser(&records, &count)) {
        if (count == 0) {
            printf("| Tidak ada data akun mesin                    |\n");
        } else {
            printf("+----------------------------------------------+\n");
            printf("| Indeks | Email                               |\n");
            printf("+----------------------------------------------+\n");
            
            int mesinCount = 0;
            for (i = 0; i < count; i++) {
                // Ambil tipe pengguna
                char *tipeStr = AmbilNilai(&records[i], "tipe_akun");
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
                    int tipe = tipeStr ? atoi(tipeStr) : 0;
                    
                    if (tipe == 4) {
                        char *userEmail = AmbilNilai(&records[i], "email");
                        if (userEmail) {
                            strcpy(mesinEmails[mesinCount], userEmail);
                            mesinCount++;
                        }
                    }
                }
                
                // Pilih mesin untuk dihapus
                int choice;
                printf("\nMasukkan indeks mesin yang ingin dihapus (0 untuk batal): ");
                scanf("%d", &choice);
                
                if (choice > 0 && choice <= mesinCount) {
                    // Konfirmasi penghapusan
                    char confirm;
                    printf("\nAnda yakin ingin menghapus mesin dengan email %s? (Y/N): ", mesinEmails[choice-1]);
                    fflush(stdin);
                    scanf(" %c", &confirm);
                    
                    if (confirm == 'Y' || confirm == 'y') {
                        // Hapus akun
                        if (HapusAkunDariFile(mesinEmails[choice-1])) {
                            printf("\nBerhasil menghapus akun mesin dengan email: %s\n", mesinEmails[choice-1]);
                            // Juga hapus rekening jika ada
                            HapusRekeningUser(mesinEmails[choice-1]);
                        } else {
                            printf("\nGagal menghapus akun mesin. Silakan coba lagi.\n");
                        }
                    } else {
                        printf("\nPenghapusan akun mesin dibatalkan.\n");
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
        printf("| Gagal membaca data akun mesin                |\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk mengedit akun mesin
void EditMesinAccount(const char* mesinEmail, HashPassword* morseTree) {
    clearScreen();
    
    // Ambil data mesin dari database
    Record mesinRecord;
    InisialisasiRecord(&mesinRecord);
    if (!BacaAkunUser(&mesinRecord, mesinEmail)) {
        printf("Error: Gagal membaca data akun mesin dari database.\n");
        getch();
        return;
    }
    
    char nama[100];
    char alamat[200];
    char nomor_telepon[20];
    char password[50];
    boolean isValid;
    
    printf("+----------------------------------------------+\n");
    printf("|            EDIT AKUN MESIN                   |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Data Saat Ini:\n");
    printf("Email          : %s\n", mesinEmail);
    printf("Nama           : %s\n", AmbilNilai(&mesinRecord, "nama"));
    printf("Alamat         : %s\n", AmbilNilai(&mesinRecord, "alamat"));
    printf("Nomor Telepon  : %s\n", AmbilNilai(&mesinRecord, "nomor_telepon"));
    
    printf("\nUbah Data Profil (kosongkan jika tidak ingin mengubah):\n");
    
    // Input nama
    printf("Nama Baru         : ");
    getchar(); // Ambil karakter newline dari input sebelumnya
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Hapus newline
    
    // Jika input kosong, gunakan nilai lama
    if (strlen(nama) == 0) {
        strcpy(nama, AmbilNilai(&mesinRecord, "nama"));
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
        strcpy(alamat, AmbilNilai(&mesinRecord, "alamat"));
    }
    
    // Input nomor telepon
    do {
        isValid = TRUE;
        printf("No. Telepon Baru  : ");
        fgets(nomor_telepon, sizeof(nomor_telepon), stdin);
        nomor_telepon[strcspn(nomor_telepon, "\n")] = 0; // Hapus newline
        
        // Jika input kosong, gunakan nilai lama
        if (strlen(nomor_telepon) == 0) {
            strcpy(nomor_telepon, AmbilNilai(&mesinRecord, "nomor_telepon"));
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
    
    // Update data mesin
    UbahNilai(&mesinRecord, "nama", nama);
    UbahNilai(&mesinRecord, "alamat", alamat);
    UbahNilai(&mesinRecord, "nomor_telepon", nomor_telepon);
    
    // Update password jika diisi
    if (strlen(password) > 0) {
        char* hashedPassword = HashPasswordWithMorse(morseTree, password);
        UbahNilai(&mesinRecord, "password", hashedPassword);
        free(hashedPassword);
    }
    
    // Simpan perubahan ke database
    if (UpdateAkunUser(&mesinRecord)) {
        printf("\nData akun mesin berhasil diperbarui!\n");
    } else {
        printf("\nGagal memperbarui data akun mesin.\n");
    }
    
    getch();
}

// Fungsi utama untuk manajemen mesin
void JalankanDashboardManajemenMesin(const char* email, HashPassword* morseTree) {
    int pilihan;
    boolean keluar = FALSE;
    
    while (!keluar) {
        TampilkanDashboardManajemenMesin(email);
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                TampilkanFormTambahMesin(email, morseTree);
                break;
                
            case 2:
                TampilkanFormEditMesin(email, morseTree);
                break;
                
            case 3:
                TampilkanFormHapusMesin(email);
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
