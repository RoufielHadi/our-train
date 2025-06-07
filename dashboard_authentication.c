/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_authentication.h"
#include "dashboard_user.h"
#include "dashboard_admin.h"
#include "dashboard_cashier.h"
#include "dashboard_machine.h"

// Variable global
HashPassword* morseTree = NULL;

// *** TAMPILAN DASHBOARD ***
void ShowWelcomeScreen() {
    clearScreen();
    printf("\n\n");
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|    ___                 _____                 |\n");
    printf("|   / _ \\  _   _  _ __  |_   _| _ __   __ _    |\n");
    printf("|  | | | || | | || '__|   | |  | '__| / _` |   |\n");
    printf("|  | |_| || |_| || |      | |  | |   | (_| |   |\n");
    printf("|   \\___/  \\__,_||_|      |_|  |_|    \\__,_|   |\n");
    printf("|                                              |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("|           Press Enter to continue            |\n");
    printf("+----------------------------------------------+\n");
    
    getch(); // Menunggu user menekan tombol enter
}

void ShowMainMenu() {
    clearScreen();
    printf("\n\n");
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|       Selamat datang di aplikasi OurTrain    |\n");
    printf("|                                              |\n");
    printf("|              1. Register                     |\n");
    printf("|              2. Login                        |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

void ShowBox(const char* content) {
    int length = strlen(content);
    int boxWidth = 48; // Lebar total kotak
    int contentWidth = boxWidth - 4; // Lebar konten (dikurangi 2 karakter '|' dan 2 spasi)
    
    printf("\n\n");
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    
    // Jika konten terlalu panjang, potong atau tampilkan beberapa baris
    if (length <= contentWidth) {
        // Hitung spasi di kiri dan kanan untuk centering
        int leftPadding = (contentWidth - length) / 2;
        printf("|  %*s%s%*s  |\n", leftPadding, "", content, contentWidth - length - leftPadding, "");
    } else {
        // Bagi konten menjadi beberapa baris
        int start = 0;
        char line[100]; /* Fixed buffer size that's large enough for most cases */
        while (start < length) {
            int lineLength = (length - start) > contentWidth ? contentWidth : (length - start);
            strncpy(line, content + start, lineLength);
            line[lineLength] = '\0';
            printf("|  %-*s  |\n", contentWidth, line);
            start += lineLength;
        }
    }
    
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
}

// *** OTENTIKASI USER ***
boolean RegisterUser() {
    clearScreen();
    Record userRecord, bankRecord;
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char pin[MAX_PIN_LENGTH + 1]; // +1 untuk null terminator
    char name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char accountNumber[MAX_ACCOUNT_NUMBER_LENGTH];
    char bankName[MAX_BANK_NAME_LENGTH];
    char bankBranch[MAX_BANK_BRANCH_LENGTH];
    char balance[MAX_BALANCE_LENGTH];
    
    printf("+----------------------------------------------+\n");
    printf("|                 REGISTER                     |\n");
    printf("+----------------------------------------------+\n\n");
    
    // Input data akun
    printf("Data Akun:\n");
    printf("1. Email: ");
    scanf("%s", email);
    
    // Cek apakah email sudah terdaftar
    if (IsEmailExists(email)) {
        ShowBox("Email sudah terdaftar. Silakan gunakan email lain.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return FALSE;
    }
    
    // Input password
    printf("2. Password: ");
    scanf("%s", password);
    
    // Validasi password
    if (!IsPasswordValid(password)) {
        ShowBox("Password tidak valid. Password harus mengandung huruf besar, huruf kecil, dan angka.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return FALSE;
    }
    
    // Input PIN
    printf("3. PIN (%d digit): ", MAX_PIN_LENGTH);
    scanf("%s", pin);
    
    // Validasi PIN
    if (!IsPinValid(pin)) {
        ShowBox("PIN tidak valid. PIN harus terdiri dari 6 digit angka.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return FALSE;
    }
    
    // Input data tambahan
    printf("4. Nama: ");
    fflush(stdin); // Bersihkan buffer
    getchar(); // Buang karakter newline dari input sebelumnya
    scanf("%[^\n]", name);
    
    printf("5. Alamat: ");
    fflush(stdin); // Bersihkan buffer
    getchar(); // Buang karakter newline dari input sebelumnya
    scanf("%[^\n]", address);
    
    printf("6. Nomor Telepon: ");
    fflush(stdin); // Bersihkan buffer
    scanf("%s", phone);
    
    printf("\nData Rekening:\n");
    printf("1. Nomor Rekening: ");
    scanf("%s", accountNumber);
    
    printf("2. Nama Bank: ");
    fflush(stdin); // Bersihkan buffer
    getchar(); // Buang karakter newline dari input sebelumnya
    scanf("%[^\n]", bankName);
    
    printf("3. Cabang Bank: ");
    fflush(stdin); // Bersihkan buffer
    getchar(); // Buang karakter newline dari input sebelumnya
    scanf("%[^\n]", bankBranch);
    
    printf("4. Saldo Awal: ");
    scanf("%s", balance);
    
    // Inisialisasi record sebelum digunakan
    InisialisasiRecord(&userRecord);
    InisialisasiRecord(&bankRecord);

    // Hash password dan PIN
    char* hashedPassword = HashPasswordWithMorse(morseTree, password);
    char* hashedPin = HashPin(morseTree, pin);
    
    if (hashedPassword == NULL || hashedPin == NULL) {
        ShowBox("Error saat melakukan hashing password atau PIN.");
        printf("Tekan Enter untuk kembali...");
        getch();
        
        // Bersihkan memori yang sudah dialokasikan
        if (hashedPassword) free(hashedPassword);
        if (hashedPin) free(hashedPin);
        
        return FALSE;
    }
    
    // Tambahkan data ke record user
    TambahField(&userRecord, "email", email);
    TambahField(&userRecord, "password", hashedPassword);
    TambahField(&userRecord, "pin", hashedPin);
    TambahField(&userRecord, "nama", name);
    TambahField(&userRecord, "alamat", address);
    TambahField(&userRecord, "nomor_telepon", phone);
    TambahField(&userRecord, "tipe_akun", "1"); // Default user biasa
    
    // Tambahkan data ke record bank
    TambahField(&bankRecord, "email", email);
    TambahField(&bankRecord, "nomorRekening", accountNumber);
    TambahField(&bankRecord, "namaBank", bankName);
    TambahField(&bankRecord, "cabangBank", bankBranch);
    TambahField(&bankRecord, "saldo", balance);
    
    // Simpan ke database
    boolean success = SimpanAkunUser(&userRecord) && SimpanRekeningUser(&bankRecord);
    
    // Bersihkan memori
    free(hashedPassword);
    free(hashedPin);
    
    if (success) {
        ShowBox("Registrasi berhasil! Silakan login.");
    } else {
        ShowBox("Registrasi gagal. Silakan coba lagi.");
    }
    
    printf("Tekan Enter untuk kembali...");
    getch();
    return success;
}

boolean IsEmailExists(const char* email) {
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    return BacaAkunUser(&userRecord, email);
}

int LoginUser(char* email, char* password) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|                  LOGIN                       |\n");
    printf("+----------------------------------------------+\n\n");
    
    printf("Email: ");
    scanf("%s", email);
    
    printf("Password: ");
    scanf("%s", password);
    
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    if (!BacaAkunUser(&userRecord, email)) {
        ShowBox("Email tidak terdaftar.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return 0;
    }
    
    char* storedPassword = AmbilNilai(&userRecord, "password");
    if (storedPassword == NULL) {
        ShowBox("Data password tidak ditemukan.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return 0;
    }
    
    // Verifikasi password
    if (!VerifyPassword(morseTree, password, storedPassword)) {
        ShowBox("Password salah.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return 0;
    }
    
    // Ambil tipe akun
    char* userTypeStr = AmbilNilai(&userRecord, "tipe_akun");
    if (userTypeStr == NULL) {
        ShowBox("Data tipe akun tidak ditemukan.");
        printf("Tekan Enter untuk kembali...");
        getch();
        return 0;
    }
    
    int userType = atoi(userTypeStr);
    ShowBox("Login berhasil!");
    printf("Tekan Enter untuk melanjutkan...");
    getch();
    
    return userType;
}

// *** FUNGSI NAVIGASI ***
void NavigateToDashboard(int userType, const char* email) {
    switch (userType) {
        case USER_TYPE:
            RunUserDashboard(email);
            break;
        case ADMIN_TYPE:
            RunAdminDashboard(email);
            break;
        case CASHIER_TYPE:
            RunCashierDashboard(email);
            break;
        case MACHINE_TYPE:
            RunMachineDashboard(email);
            break;
        default:
            ShowBox("Tipe akun tidak valid.");
            printf("Tekan Enter untuk kembali...");
            getch();
            break;
    }
}

// *** FUNGSI UTAMA ***
void RunAuthentication() {
    // Inisialisasi tree Morse untuk hash password
    InisialisasiMorseCode(&morseTree);
    
    // Buat file database jika belum ada
    BuatFileJikaBelumAda(DB_AKUN_USER);
    BuatFileJikaBelumAda(DB_REKENING_USER);
    
    int choice;
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int userType;
    
    ShowWelcomeScreen();
    
    do {
        ShowMainMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Register
                RegisterUser();
                break;
                
            case 2: // Login
                userType = LoginUser(email, password);
                if (userType > 0) {
                    NavigateToDashboard(userType, email);
                }
                break;
                
            default:
                ShowBox("Pilihan tidak valid. Silakan coba lagi.");
                printf("Tekan Enter untuk kembali...");
                getch();
                break;
        }
    } while (1); // Loop terus menerus
} 