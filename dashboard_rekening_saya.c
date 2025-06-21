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
#include "boolean.h"
#include "tree_biner.h"
#include "implementasi_morse.h"
#include "dashboard_rekening_saya.h"

// *** TAMPILAN DASHBOARD REKENING SAYA ***
void ShowUserBankDashboard(const char* email) {
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
    printf("|              REKENING SAYA                   |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("| Akun: %-40s |\n", namaUser ? namaUser : email);
    printf("+----------------------------------------------+\n");
    printf("| Menu:                                        |\n");
    printf("|  1. Lihat Informasi Rekening                 |\n");
    printf("|  2. Ganti PIN                                |\n");
    printf("|  3. Top Up Saldo                             |\n");
    printf("|  4. Kembali ke Dashboard Utama               |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilihan: ");
}

// *** MENU REKENING SAYA ***
void ShowBankAccountInfo(const char* email) {
    clearScreen();
    // Ambil data rekening dari database
    Record bankRecord;
    InisialisasiRecord(&bankRecord);
    if (!BacaRekeningUser(&bankRecord, email)) {
        printf("Error: Gagal membaca data rekening user dari database.\n");
        getch();
        return;
    }
    char* noRekening = AmbilNilai(&bankRecord, "nomorRekening");
    char* saldo = AmbilNilai(&bankRecord, "saldo");
    
    // Tampilkan informasi rekening
    printf("+----------------------------------------------+\n");
    printf("|            INFORMASI REKENING                |\n");
    printf("+----------------------------------------------+\n\n");
    printf("Nomor Rekening : %s\n", noRekening ? noRekening : "-");
    printf("Saldo          : %s\n", saldo ? saldo : "0");
    printf("PIN            : ******\n");
    
    printf("\nTekan Enter untuk kembali ke menu rekening saya...");
    getch();
}

boolean ChangeBankPIN(const char* email) {
    clearScreen();
    
    // Ambil data rekening menggunakan Record untuk kompatibilitas
    Record bankRecord;
    InisialisasiRecord(&bankRecord);
    
    if (!BacaRekeningUser(&bankRecord, email)) {
        printf("Gagal membaca data rekening user.\n");
        getch();
        return FALSE;
    }
    
    // Inisialisasi Morse tree untuk verifikasi PIN
    HashPassword* morseTree = NULL;
    InisialisasiMorseCode(&morseTree);
    
    // Ambil data rekening menggunakan linked list
    ListPayment LP;
    Payment paymentInfo;
    boolean updateLinkedList = FALSE;
    
    CreateListPayment(&LP);
    
    // Mencari data rekening di linked list
    PaymentUser* node = SearchPaymentByEmail(LP, (char*)email);
    if (node != NULL) {
        paymentInfo = node->payment_info;
        updateLinkedList = TRUE;
    }
    
    char oldPIN[MAX_PIN_LENGTH + 1];
    char newPIN[MAX_PIN_LENGTH + 1];
    char confirmPIN[MAX_PIN_LENGTH + 1];
    int i;
    char ch;
    
    printf("+----------------------------------------------+\n");
    printf("|                 GANTI PIN                    |\n");
    printf("+----------------------------------------------+\n\n");
    
    // Input PIN lama
    printf("Masukkan PIN lama: ");
    i = 0;
    while ((ch = getch()) != 13) { // 13 adalah kode ASCII untuk Enter
        if (ch == 8) { // 8 adalah kode ASCII untuk Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PIN_LENGTH && ch >= '0' && ch <= '9') {
            oldPIN[i++] = ch;
            printf("*");
        }
    }
    oldPIN[i] = '\0';
    printf("\n");
    
    // Verifikasi PIN lama
    char* storedHashedPin = AmbilNilai(&bankRecord, "pin");
    if (storedHashedPin == NULL || !VerifyPin(morseTree, oldPIN, storedHashedPin)) {
        printf("PIN lama tidak sesuai.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
    
    // Input PIN baru
    printf("Masukkan PIN baru (6 digit): ");
    i = 0;
    while ((ch = getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PIN_LENGTH && ch >= '0' && ch <= '9') {
            newPIN[i++] = ch;
            printf("*");
        }
    }
    newPIN[i] = '\0';
    printf("\n");
    
    // Validasi PIN baru
    if (strlen(newPIN) != 6) {
        printf("PIN harus terdiri dari 6 digit.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
    
    // Konfirmasi PIN baru
    printf("Konfirmasi PIN baru: ");
    i = 0;
    while ((ch = getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PIN_LENGTH && ch >= '0' && ch <= '9') {
            confirmPIN[i++] = ch;
            printf("*");
        }
    }
    confirmPIN[i] = '\0';
    printf("\n");
    
    // Validasi PIN konfirmasi
    if (strcmp(newPIN, confirmPIN) != 0) {
        printf("Konfirmasi PIN tidak sesuai.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
    
    // Hash PIN baru dan update di database
    char* newPinHash = HashPin(morseTree, newPIN);
    UbahNilai(&bankRecord, "pin", newPinHash);
    free(newPinHash);
    
    if (UpdateRecordBiner(DB_REKENING_USER, &bankRecord, "email")) {
        // Jika data rekening ada di linked list, update juga
        if (updateLinkedList) {
            strcpy(paymentInfo.pin, newPIN);
            // Update node data
            node->payment_info = paymentInfo;
        }
        
        printf("\nPIN berhasil diubah!\n");
        getch();
        DeleteListPayment(&LP);
        return TRUE;
    } else {
        printf("\nGagal mengubah PIN.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
}

boolean TopUpBalance(const char* email) {
    clearScreen();
    
    // Ambil data rekening menggunakan Record untuk kompatibilitas
    Record bankRecord;
    InisialisasiRecord(&bankRecord);
    
    if (!BacaRekeningUser(&bankRecord, email)) {
        printf("Gagal membaca data rekening user.\n");
        getch();
        return FALSE;
    }
    
    // Inisialisasi Morse tree untuk verifikasi PIN
    HashPassword* morseTree = NULL;
    InisialisasiMorseCode(&morseTree);
    
    // Ambil data rekening menggunakan linked list
    ListPayment LP;
    Payment paymentInfo;
    boolean updateLinkedList = FALSE;
    
    CreateListPayment(&LP);
    
    // Mencari data rekening di linked list
    PaymentUser* node = SearchPaymentByEmail(LP, (char*)email);
    if (node != NULL) {
        paymentInfo = node->payment_info;
        updateLinkedList = TRUE;
    }
    
    char pin[MAX_PIN_LENGTH + 1];
    char topUpAmount[MAX_BALANCE_LENGTH];
    int i;
    char ch;
    
    printf("+----------------------------------------------+\n");
    printf("|               TOP UP SALDO                   |\n");
    printf("+----------------------------------------------+\n\n");
    
    // Tampilkan saldo saat ini
    printf("Saldo saat ini: %s\n\n", AmbilNilai(&bankRecord, "saldo") ? AmbilNilai(&bankRecord, "saldo") : "0");
    
    // Input PIN untuk verifikasi
    printf("Masukkan PIN: ");
    i = 0;
    while ((ch = getch()) != 13) { // 13 adalah kode ASCII untuk Enter
        if (ch == 8) { // 8 adalah kode ASCII untuk Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PIN_LENGTH && ch >= '0' && ch <= '9') {
            pin[i++] = ch;
            printf("*");
        }
    }
    pin[i] = '\0';
    printf("\n");
    
    // Verifikasi PIN
    char* storedHashedPin2 = AmbilNilai(&bankRecord, "pin");
    if (storedHashedPin2 == NULL || !VerifyPin(morseTree, pin, storedHashedPin2)) {
        printf("PIN tidak sesuai.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
    
    // Input jumlah top up
    printf("\nMasukkan jumlah saldo yang akan ditambahkan: ");
    scanf("%s", topUpAmount);
    
    // Validasi jumlah top up
    if (!ValidasiSaldo(topUpAmount)) {
        printf("Jumlah top up tidak valid. Harus berupa angka positif.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
    
    // Tambahkan saldo
    int currentBalance = atoi(AmbilNilai(&bankRecord, "saldo") ? AmbilNilai(&bankRecord, "saldo") : "0");
    int topUpValue = atoi(topUpAmount);
    int newBalance = currentBalance + topUpValue;
    
    // Konversi nilai saldo baru ke string
    char newBalanceStr[MAX_BALANCE_LENGTH];
    sprintf(newBalanceStr, "%d", newBalance);
    
    // Update saldo di database
    UbahNilai(&bankRecord, "saldo", newBalanceStr);
    
    if (UpdateRecordBiner(DB_REKENING_USER, &bankRecord, "email")) {
        // Jika data rekening ada di linked list, update juga
        if (updateLinkedList) {
            paymentInfo.saldo = newBalance;
            // Update node data
            node->payment_info = paymentInfo;
        }
        
        printf("\nSaldo berhasil ditambahkan!\n");
        printf("Saldo baru: %s\n", newBalanceStr);
        getch();
        DeleteListPayment(&LP);
        return TRUE;
    } else {
        printf("\nGagal menambahkan saldo.\n");
        getch();
        DeleteListPayment(&LP);
        return FALSE;
    }
}

// *** FUNGSI UTAMA ***
void RunUserBankDashboard(const char* email) {
    int choice;
    
    do {
        ShowUserBankDashboard(email);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ShowBankAccountInfo(email);
                break;
                
            case 2:
                ChangeBankPIN(email);
                break;
                
            case 3:
                TopUpBalance(email);
                break;
                
            case 4:
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