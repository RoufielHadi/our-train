/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "boolean.h"
#include "tree_biner.h"
#include "implementasi_morse.h"
#include "dashboard_authentication.h"
#include "dashboard_user.h"
#include "dashboard_admin.h"
#include "dashboard_cashier.h"
#include "dashboard_machine.h"
#include "implementasi_akun_user.h"

// Variable global
HashPassword* morseTree = NULL;
ListUser userList;
ListPayment paymentList;
boolean logoutFlag = FALSE;

// Fungsi validasi rekening
boolean IsAccountNumberValid(const char *accountNumber) {
    if (accountNumber == NULL) {
        return FALSE;
    }
    
    // Nomor rekening harus berupa angka dan panjangnya antara 10-16 digit
    if (strlen(accountNumber) < 10 || strlen(accountNumber) > 16) {
        return FALSE;
    }
    
    int i;
    for (i = 0; accountNumber[i] != '\0'; i++) {
        if (!isdigit(accountNumber[i])) {
            return FALSE;
        }
    }
    
    return TRUE;
}

boolean IsBalanceValid(const char *balance) {
    if (balance == NULL) {
        return FALSE;
    }
    
    // Saldo harus berupa angka
    int i;
    for (i = 0; balance[i] != '\0'; i++) {
        if (!isdigit(balance[i])) {
            return FALSE;
        }
    }
    
    return TRUE;
}

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
boolean RegisterUserLinkedList(ListUser *userList, ListPayment *paymentList) {
    clearScreen();
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char pin[MAX_PIN_LENGTH + 1]; // +1 untuk null terminator
    char name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char accountNumber[MAX_ACCOUNT_NUMBER_LENGTH];
    char balance[MAX_BALANCE_LENGTH];
    char buffer[MAX_BUFFER_LENGTH]; // Buffer tambahan untuk input
    
    // Input data akun: ulang jika format salah, bersihkan layar tiap iterasi
    // Email
    while (1) {
        clearScreen();
        // Header REGISTER
        printf("+----------------------------------------------+\n");
        printf("|                 REGISTER                     |\n");
        printf("+----------------------------------------------+\n\n");
        // Bagian Data Akun
        printf("Data Akun:\n");
        printf("Email: ");
        scanf("%s", email);
        // Validasi format email
        if (!ValidasiEmail(email)) {
            ShowBox("Format email tidak valid. Contoh: user@domain.tld");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        } else if (IsEmailExistsLinkedList(*userList, email)) {
            ShowBox("Email sudah terdaftar. Silakan gunakan email lain.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        } else {
            break; // validasi sukses
        }
    }
    // Password
    while (1) {
        clearScreen();
        // Header REGISTER dan Data Akun
        printf("+----------------------------------------------+\n");
        printf("|                 REGISTER                     |\n");
        printf("+----------------------------------------------+\n\n");
        printf("Data Akun:\n");
        printf("Email: %s\n", email);
        printf("Password: ");
        scanf("%s", password);
        if (!IsPasswordValid(password)) {
            ShowBox("Password tidak valid. Password harus mengandung huruf besar, huruf kecil, dan angka.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        } else {
            break;
        }
    }
    // PIN
    while (1) {
        clearScreen();
        // Header REGISTER dan Data Akun
        printf("+----------------------------------------------+\n");
        printf("|                 REGISTER                     |\n");
        printf("+----------------------------------------------+\n\n");
        printf("Data Akun:\n");
        printf("Email: %s\n", email);
        printf("Password: ******\n");
        printf("PIN (%d digit): ", MAX_PIN_LENGTH);
        scanf("%s", pin);
        if (!IsPinValid(pin)) {
            ShowBox("PIN tidak valid. PIN harus terdiri dari 6 digit angka.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        } else {
            break;
        }
    }
    // Bersihkan buffer sebelum membaca string berikutnya
    while (getchar() != '\n');
    // Nama
    printf("Nama: ");
    if (fgets(name, MAX_NAME_LENGTH, stdin) != NULL) {
        name[strcspn(name, "\n")] = '\0';
        // Format nama ke Title Case
        FormatNama(name);
    }
    // Alamat
    printf("Alamat: ");
    if (fgets(address, MAX_ADDRESS_LENGTH, stdin) != NULL) {
        address[strcspn(address, "\n")] = '\0';
    }
    // Nomor Telepon
    while (1) {
        printf("Nomor Telepon: ");
        if (fgets(phone, MAX_PHONE_LENGTH, stdin) != NULL) {
            phone[strcspn(phone, "\n")] = '\0';
            if (!ValidasiNomorTelepon(phone)) {
                ShowBox("Nomor telepon tidak valid. Harus diawali dengan '08' dan memiliki 11-13 digit.");
                printf("Tekan Enter untuk melanjutkan..."); getch();
                clearScreen(); // Bersihkan layar jika input tidak valid
                // Header REGISTER dan Data Akun yang sudah diinput sebelumnya
                printf("+----------------------------------------------+\n");
                printf("|                 REGISTER                     |\n");
                printf("+----------------------------------------------+\n\n");
                printf("Data Akun:\n");
                printf("Email: %s\n", email);
                printf("Password: ******\n");
                printf("PIN: ******\n");
                printf("Nama: %s\n", name);
                printf("Alamat: %s\n", address);
            } else {
                break; // validasi sukses
            }
        }
    }
    // Data Rekening
    clearScreen();
    // Header REGISTER
    printf("+----------------------------------------------+\n");
    printf("|                 REGISTER                     |\n");
    printf("+----------------------------------------------+\n\n");
    // Data Akun
    printf("Data Akun:\n");
    printf("Email: %s\n\n", email);
    // Nomor Rekening
    while (1) {
        printf("Data Rekening:\n");
        printf("Nomor Rekening: ");
        scanf("%s", accountNumber);
        if (!IsAccountNumberValid(accountNumber)) {
            ShowBox("Nomor rekening tidak valid. Harus 10-16 digit angka.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
            clearScreen();
            // Header REGISTER dan Data Akun yang sudah diinput sebelumnya
            printf("+----------------------------------------------+\n");
            printf("|                 REGISTER                     |\n");
            printf("+----------------------------------------------+\n\n");
            printf("Data Akun:\n");
            printf("Email: %s\n\n", email);
        } else {
            break;
        }
    }
    // Bersihkan buffer sebelum input saldo
    while (getchar() != '\n');
    // Saldo Awal
    while (1) {
        clearScreen();
        // Header REGISTER
        printf("+----------------------------------------------+\n");
        printf("|                 REGISTER                     |\n");
        printf("+----------------------------------------------+\n\n");
        // Data Akun dan Data Rekening
        printf("Data Akun:\n");
        printf("Email: %s\n\n", email);
        printf("Data Rekening:\n");
        printf("Nomor Rekening: %s\n\n", accountNumber);
        printf("Saldo Awal: ");
        scanf("%s", balance);
        if (!ValidasiSaldo(balance)) {
            ShowBox("Saldo tidak valid. Harus angka >= 0.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        } else {
            break;
        }
    }
    
    // Pilih tipe akun
    int accountType;
    while (1) {
        clearScreen();
        // Header REGISTER
        printf("+----------------------------------------------+\n");
        printf("|                 REGISTER                     |\n");
        printf("+----------------------------------------------+\n\n");
        // Tampilkan data sebelumnya
        printf("Data Akun:\n");
        printf("Email: %s\n", email);
        printf("Nama: %s\n", name);
        printf("Alamat: %s\n", address);
        printf("Nomor Telepon: %s\n\n", phone);
        printf("Data Rekening:\n");
        printf("Nomor Rekening: %s\n", accountNumber);
        printf("Saldo Awal: %s\n\n", balance);
        printf("Pilih tipe akun:\n");
        printf("1. Pengguna biasa\n");
        printf("2. Admin\n");
        printf("3. Kasir\n");
        printf("4. Mesin\n");
        printf("Masukkan pilihan (1-4): ");
        scanf("%d", &accountType);
        if (accountType >= USER_TYPE && accountType <= MACHINE_TYPE) {
            break;
        } else {
            ShowBox("Pilihan tipe akun tidak valid.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        }
    }
    
    // Buat objek User dan Payment menggunakan struct dari linked.h
    User userData;
    Payment paymentData;
    
    // Isi data User
    strcpy(userData.email, email);
    strcpy(userData.nama, name);
    strcpy(userData.alamat, address);
    strcpy(userData.nomor_telepon, phone);
    
    // Hash password
    char* hashedPassword = HashPasswordWithMorse(morseTree, password);
    if (hashedPassword != NULL) {
        strcpy(userData.password, hashedPassword);
        free(hashedPassword);
    }
    
    // Set tipe pengguna sesuai pilihan
    userData.is_admin = accountType;
    
    // Isi data Payment
    strcpy(paymentData.email, email);
    strcpy(paymentData.no_rekening, accountNumber);
    paymentData.saldo = atoi(balance);
    
    // Hash PIN
    char* hashedPin = HashPasswordWithMorse(morseTree, pin);
    if (hashedPin != NULL) {
        strcpy(paymentData.pin, hashedPin);
        free(hashedPin);
    }
    
    // Tambahkan data ke linked list
    DataUser* newUser = CreateDataUser(userData);
    PaymentUser* newPayment = CreateDataPayment(paymentData);
    
    if (newUser == NULL || newPayment == NULL) {
        ShowBox("Gagal membuat data user baru.");
        
        // Bersihkan memori yang sudah dialokasikan
        if (newUser) DeAlokasiUser(&newUser);
        if (newPayment) DeAlokasiPayment(&newPayment);
        
        printf("Tekan Enter untuk kembali...");
        getch();
        return FALSE;
    }
    
    // Tambahkan ke linked list
    InsertLastUser(userList, newUser);
    InsertLastPayment(paymentList, newPayment);
    
    // Juga simpan ke database untuk kompatibilitas
    Record userRecord, bankRecord;
    InisialisasiRecord(&userRecord);
    InisialisasiRecord(&bankRecord);
    
    // Tambahkan data ke record user
    TambahField(&userRecord, "email", email); // Gunakan email sebagai primary key
    TambahField(&userRecord, "password", userData.password);
    TambahField(&userRecord, "nama", name);
    TambahField(&userRecord, "alamat", address);
    TambahField(&userRecord, "nomor_telepon", phone);
    {
        char tipeStr[3];
        sprintf(tipeStr, "%d", accountType);
        TambahField(&userRecord, "tipe_akun", tipeStr);
    }
    
    // Tambahkan data ke record bank
    TambahField(&bankRecord, "email", email);
    TambahField(&bankRecord, "nomorRekening", accountNumber);
    TambahField(&bankRecord, "saldo", balance);
    TambahField(&bankRecord, "pin", paymentData.pin);
    
    // Simpan ke database
    boolean success = SimpanAkunUser(&userRecord) && SimpanRekeningUser(&bankRecord);
    
    if (success) {
        ShowBox("Registrasi berhasil! Silakan login.");
    } else {
        ShowBox("Registrasi berhasil di memory tapi gagal di database.");
    }
    
    printf("Tekan Enter untuk kembali...");
    getch();
    return TRUE;
}

boolean RegisterUser() {
    return RegisterUserLinkedList(&userList, &paymentList);
}

boolean IsEmailExistsLinkedList(ListUser userList, const char* email) {
    // Cek di linked list dulu
    DataUser* user = SearchUserByEmail(userList, (char*)email);
    if (user != NULL) {
        return TRUE;
    }
    
    // Cek juga di database untuk memastikan
    Record userRecord;
    InisialisasiRecord(&userRecord);
    return BacaAkunUser(&userRecord, email);
}

boolean IsEmailExists(const char* email) {
    return IsEmailExistsLinkedList(userList, email);
}

int LoginUserLinkedList(ListUser userList, char* email, char* password, User* user_aktif) {
    // Cek login menggunakan linked list
    if (Login(userList, email, password, user_aktif, morseTree)) {
        return user_aktif->is_admin;
    }
    
    // Jika tidak berhasil di linked list, cek di database untuk kompatibilitas
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    if (!BacaAkunUser(&userRecord, email)) {
        return 0; // Email tidak terdaftar
    }
    
    char* storedPassword = AmbilNilai(&userRecord, "password");
    if (storedPassword == NULL) {
        return 0; // Data password tidak ditemukan
    }
    
    char* hashedPassword = HashPasswordWithMorse(morseTree, password);
    boolean match = (strcmp(hashedPassword, storedPassword) == 0);
    free(hashedPassword);
    
    if (match) {
        // Jika login berhasil di database, tambahkan user ke linked list
        User newUser;
        strcpy(newUser.email, email);
        
        char* nama = AmbilNilai(&userRecord, "nama");
        if (nama != NULL) strcpy(newUser.nama, nama);
        else strcpy(newUser.nama, "");
        
        char* alamat = AmbilNilai(&userRecord, "alamat");
        if (alamat != NULL) strcpy(newUser.alamat, alamat);
        else strcpy(newUser.alamat, "");
        
        char* telepon = AmbilNilai(&userRecord, "nomor_telepon");
        if (telepon != NULL) strcpy(newUser.nomor_telepon, telepon);
        else strcpy(newUser.nomor_telepon, "");
        
        strcpy(newUser.password, storedPassword);
        
        // Cek kedua field: tipe_akun (standar) dan is_admin (kompatibilitas)
        char* tipeStr = AmbilNilai(&userRecord, "tipe_akun");
        if (tipeStr != NULL) {
            newUser.is_admin = atoi(tipeStr);
        } else {
            // Jika tidak ada tipe_akun, coba cek is_admin
            char* isAdminStr = AmbilNilai(&userRecord, "is_admin");
            newUser.is_admin = isAdminStr ? atoi(isAdminStr) : 1; // Default: user biasa
        }
        
        // Tambahkan ke linked list jika belum ada
        if (SearchUserByEmail(userList, email) == NULL) {
            DataUser* newUserNode = CreateDataUser(newUser);
            if (newUserNode != NULL) {
                InsertLastUser(&userList, newUserNode);
            }
        }
        
        if (user_aktif != NULL) {
            *user_aktif = newUser;
        }
        
        return newUser.is_admin;
    }
    
    return 0; // Login gagal
}

// Fungsi Login interaktif: loop hingga berhasil atau diarahkan ke registrasi
int LoginUser(char* email, char* password) {
    User user_aktif;
    char choice[4];
    
    while (1) {
        clearScreen();
        // Header LOGIN
        printf("+----------------------------------------------+\n");
        printf("|                  LOGIN                       |\n");
        printf("+----------------------------------------------+\n\n");
        // Input email dan password
        printf("Email   : "); scanf("%s", email);
        printf("Password: "); scanf("%s", password);
        
        int userType = LoginUserLinkedList(userList, email, password, &user_aktif);
        
        if (userType > 0) {
            // Login berhasil
    ShowBox("Login berhasil!");
            printf("Tekan Enter untuk melanjutkan..."); getch();
    return userType;
        } else {
            // Login gagal
            if (!IsEmailExistsLinkedList(userList, email)) {
                ShowBox("Email tidak terdaftar.");
            } else {
                ShowBox("Password salah.");
            }
        }
        
        // Tanyakan apakah user memiliki akun
        while (1) {
            clearScreen();
            printf("Anda sudah memiliki akun? (Y/N): ");
            scanf("%s", choice);
            if (choice[0]=='Y' || choice[0]=='y') {
                break; // ulangi login
            } else if (choice[0]=='N' || choice[0]=='n') {
                RegisterUser();
                break; // setelah registrasi, ulangi login
            } else {
                ShowBox("Pilihan tidak valid. Jawab Y atau N.");
                printf("Tekan Enter untuk melanjutkan..."); getch();
            }
        }
    }
}

// *** FUNGSI NAVIGASI ***
void NavigateToDashboard(int userType, const char* email) {
    switch (userType) {
        case USER_TYPE: // 1 = Pengguna biasa
            RunUserDashboard(email);
            break;
        case ADMIN_TYPE: // 2 = Admin
            JalankanDashboardAdmin(email);
            break;
        case CASHIER_TYPE: // 3 = Kasir
            RunCashierDashboard(email);
            break;
        case MACHINE_TYPE: // 4 = Mesin
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
    
    // Inisialisasi linked list untuk user dan payment
    CreateListUser(&userList);
    CreateListPayment(&paymentList);
    
    // Buat file database jika belum ada
    BuatFileJikaBelumAda(DB_AKUN_USER);
    BuatFileJikaBelumAda(DB_REKENING_USER);
    // Konversi file database teks ke format biner jika perlu
    KonversiDatabaseKeBiner();

    int choice;
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int userType;
    
    ShowWelcomeScreen();
    
    do {
        clearScreen();
        ShowMainMenu();
        char input[4];
        printf("Pilihan: "); scanf("%s", input);
        if (input[0]=='1' && input[1]=='\0') {
                RegisterUser();
        } else if (input[0]=='2' && input[1]=='\0') {
                userType = LoginUser(email, password);
                if (userType > 0) {
                    NavigateToDashboard(userType, email);
                }
        } else {
            ShowBox("Pilihan tidak valid. Silakan pilih 1 atau 2.");
            printf("Tekan Enter untuk melanjutkan..."); getch();
        }
    } while (1);
    
    // Bersihkan memori linked list (sebetulnya tidak akan pernah tercapai karena infinite loop di atas)
    DeleteListUser(&userList);
    DeleteListPayment(&paymentList);
} 
