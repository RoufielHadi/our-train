#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "databases.h"

// Function to check database format
int check_biner_main() {
    printf("=== PROGRAM PENGECEKAN FORMAT DATABASE ===\n\n");
    
    // Cek file-file database
    printf("Memeriksa format database...\n\n");
    
    // Cek file akun user
    if (CekFileAda(DB_AKUN_USER)) {
        printf("File %s ditemukan.\n", DB_AKUN_USER);
        
        // Buka file untuk analisis format
        FILE* file = fopen(DB_AKUN_USER, "rb");
        if (file != NULL) {
            // Baca sejumlah besar karakter untuk analisis
            unsigned char buffer[1024];
            int bytesRead = fread(buffer, 1, sizeof(buffer), file);
            fclose(file);
            
            // Hitung karakter non-printable (karakter dengan nilai ASCII < 32 atau > 126)
            // kecuali karakter newline (10) dan carriage return (13)
            int i;
            int nonPrintable = 0;
            for (i = 0; i < bytesRead; i++) {
                if ((buffer[i] < 32 || buffer[i] > 126) && buffer[i] != 10 && buffer[i] != 13) {
                    nonPrintable++;
                }
            }
            
            // Jika setidaknya 10% karakter adalah non-printable, kemungkinan file biner
            float percentNonPrintable = (float)nonPrintable / bytesRead * 100;
            printf("- Jumlah byte: %d\n", bytesRead);
            printf("- Jumlah karakter non-printable: %d (%.2f%%)\n", nonPrintable, percentNonPrintable);
            
            if (percentNonPrintable > 10) {
                printf("- Status: Kemungkinan file dalam FORMAT BINER ✓\n");
            } else {
                printf("- Status: Kemungkinan file dalam FORMAT TEKS ✗\n");
                printf("  Perlu dikonversi ke format biner!\n");
            }
        }
    } else {
        printf("File %s tidak ditemukan.\n", DB_AKUN_USER);
    }
    
    printf("\n");
    
    // Cek file rekening user
    if (CekFileAda(DB_REKENING_USER)) {
        printf("File %s ditemukan.\n", DB_REKENING_USER);
        
        // Buka file untuk analisis format
        FILE* file = fopen(DB_REKENING_USER, "rb");
        if (file != NULL) {
            // Baca sejumlah besar karakter untuk analisis
            unsigned char buffer[1024];
            int bytesRead = fread(buffer, 1, sizeof(buffer), file);
            fclose(file);
            
            // Hitung karakter non-printable (karakter dengan nilai ASCII < 32 atau > 126)
            // kecuali karakter newline (10) dan carriage return (13)
            int i;
            int nonPrintable = 0;
            for (i = 0; i < bytesRead; i++) {
                if ((buffer[i] < 32 || buffer[i] > 126) && buffer[i] != 10 && buffer[i] != 13) {
                    nonPrintable++;
                }
            }
            
            // Jika setidaknya 10% karakter adalah non-printable, kemungkinan file biner
            float percentNonPrintable = (float)nonPrintable / bytesRead * 100;
            printf("- Jumlah byte: %d\n", bytesRead);
            printf("- Jumlah karakter non-printable: %d (%.2f%%)\n", nonPrintable, percentNonPrintable);
            
            if (percentNonPrintable > 10) {
                printf("- Status: Kemungkinan file dalam FORMAT BINER ✓\n");
            } else {
                printf("- Status: Kemungkinan file dalam FORMAT TEKS ✗\n");
                printf("  Perlu dikonversi ke format biner!\n");
            }
        }
    } else {
        printf("File %s tidak ditemukan.\n", DB_REKENING_USER);
    }
    
    printf("\n=== OPSI KONVERSI ===\n");
    printf("1. Konversi database ke format biner\n");
    printf("2. Keluar\n");
    
    int choice;
    printf("\nPilihan: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("\nMengkonversi database...\n");
        if (KonversiDatabaseKeBiner()) {
            printf("Konversi berhasil!\n");
        } else {
            printf("Konversi gagal.\n");
        }
    }
    
    printf("\nProgram selesai.\n");
    printf("\nTekan tombol apapun untuk keluar...");
    getch();
    
    return 0;
}

// Add a function to run the check_biner_main from elsewhere in the program
void run_check_biner() {
    check_biner_main();
} 
