/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "hash_password.h"

// *** VALIDASI PASSWORD ***
boolean IsPasswordValid(const char *password) {
    if (password == NULL) {
        return FALSE;
    }
    
    int len = strlen(password);
    boolean hasUpper = FALSE;
    boolean hasLower = FALSE;
    boolean hasDigit = FALSE;
    
    // Password terlalu pendek
    if (len < 8) {
        printf("Password harus memiliki minimal 8 karakter.\n");
        return FALSE;
    }
    
    // Periksa setiap karakter
    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) {
            hasUpper = TRUE;
        } else if (islower(password[i])) {
            hasLower = TRUE;
        } else if (isdigit(password[i])) {
            hasDigit = TRUE;
        }
    }
    
    // Periksa kriteria
    if (!hasUpper) {
        printf("Password harus memiliki minimal satu huruf besar.\n");
        return FALSE;
    }
    
    if (!hasLower) {
        printf("Password harus memiliki minimal satu huruf kecil.\n");
        return FALSE;
    }
    
    if (!hasDigit) {
        printf("Password harus memiliki minimal satu angka.\n");
        return FALSE;
    }
    
    return TRUE;
}

boolean IsPinValid(const char *pin) {
    if (pin == NULL) {
        return FALSE;
    }
    
    int len = strlen(pin);
    
    // PIN harus tepat 6 digit
    if (len != PIN_LENGTH) {
        printf("PIN harus terdiri dari %d digit.\n", PIN_LENGTH);
        return FALSE;
    }
    
    // PIN harus terdiri dari angka saja
    for (int i = 0; i < len; i++) {
        if (!isdigit(pin[i])) {
            printf("PIN hanya boleh terdiri dari angka.\n");
            return FALSE;
        }
    }
    
    return TRUE;
}

// *** HASHING PASSWORD ***
char* HashPasswordWithMorse(HashPassword *morseTree, const char *password) {
    if (morseTree == NULL || password == NULL) {
        return NULL;
    }
    
    // Konversi password ke kode Morse menggunakan tree baru
    char *morseCode = KonversiStringKeMorse(morseTree, password);
    
    // Encode kode Morse ke format XOS
    char *hashedPassword = EncodeMorse(morseCode);
    
    free(morseCode);
    return hashedPassword;
}

char* HashPin(HashPassword *morseTree, const char *pin) {
    if (morseTree == NULL || pin == NULL) {
        return NULL;
    }
    
    // Gunakan fungsi yang sama dengan password
    return HashPasswordWithMorse(morseTree, pin);
}

// *** VERIFIKASI PASSWORD ***
boolean VerifyPassword(HashPassword *morseTree, const char *password, const char *hashedPassword) {
    if (morseTree == NULL || password == NULL || hashedPassword == NULL) {
        return FALSE;
    }
    
    // Hash password yang diinput
    char *newHash = HashPasswordWithMorse(morseTree, password);
    
    // Bandingkan dengan hash yang tersimpan
    boolean result = (strcmp(newHash, hashedPassword) == 0);
    
    free(newHash);
    return result;
}

boolean VerifyPin(HashPassword *morseTree, const char *pin, const char *hashedPin) {
    if (morseTree == NULL || pin == NULL || hashedPin == NULL) {
        return FALSE;
    }
    
    // Hash PIN yang diinput
    char *newHash = HashPin(morseTree, pin);
    
    // Bandingkan dengan hash yang tersimpan
    boolean result = (strcmp(newHash, hashedPin) == 0);
    
    free(newHash);
    return result;
}

// *** FUNGSI INTERAKTIF ***
char* GetPasswordFromUser() {
    char buffer[100];
    char *password = NULL;
    boolean valid = FALSE;
    
    while (!valid) {
        printf("Masukkan password (minimal 8 karakter, terdiri dari huruf besar, huruf kecil, dan angka): ");
        scanf("%99s", buffer);
        
        if (IsPasswordValid(buffer)) {
            password = strdup(buffer);
            valid = TRUE;
        } else {
            printf("Password tidak valid. Silakan coba lagi.\n");
        }
    }
    
    return password;
}

char* GetPinFromUser() {
    char buffer[20];
    char *pin = NULL;
    boolean valid = FALSE;
    
    while (!valid) {
        printf("Masukkan PIN (%d digit angka): ", PIN_LENGTH);
        scanf("%19s", buffer);
        
        if (IsPinValid(buffer)) {
            pin = strdup(buffer);
            valid = TRUE;
        } else {
            printf("PIN tidak valid. Silakan coba lagi.\n");
        }
    }
    
    return pin;
}

// *** MANAJEMEN PASSWORD ***
void SimpanPasswordKeFile(const char *username, const char *hashedPassword, const char *hashedPin, const char *filename) {
    FILE *file = fopen(filename, "a"); // Buka file dalam mode append
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
    
    // Tulis data ke file (format: username,hashedPassword,hashedPin)
    fprintf(file, "%s,%s,%s\n", username, hashedPassword, hashedPin);
    
    fclose(file);
    printf("Data pengguna berhasil disimpan.\n");
}

boolean VerifikasiLogin(HashPassword *morseTree, const char *username, const char *password, const char *pin, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File pengguna tidak ditemukan.\n");
        return FALSE;
    }
    
    char buffer[1000];
    char fileUsername[100], fileHashedPassword[500], fileHashedPin[500];
    boolean userFound = FALSE;
    boolean loginSuccess = FALSE;
    
    // Baca file baris per baris
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Parse data (format: username,hashedPassword,hashedPin)
        if (sscanf(buffer, "%[^,],%[^,],%s", fileUsername, fileHashedPassword, fileHashedPin) == 3) {
            // Cek apakah username cocok
            if (strcmp(username, fileUsername) == 0) {
                userFound = TRUE;
                
                // Verifikasi password dan PIN
                if (VerifyPassword(morseTree, password, fileHashedPassword) && 
                    VerifyPin(morseTree, pin, fileHashedPin)) {
                    loginSuccess = TRUE;
                }
                
                break;
            }
        }
    }
    
    fclose(file);
    
    if (!userFound) {
        printf("Username tidak ditemukan.\n");
    } else if (!loginSuccess) {
        printf("Password atau PIN salah.\n");
    }
    
    return loginSuccess;
} 