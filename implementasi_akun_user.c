/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_akun_user.h"
#include "hash_password.h" // Untuk fungsi hashing password
#include "tree_biner.h" // Untuk tipe data HashPassword

// Fungsi untuk membuat akun baru
User BuatAkun(char* email, char* nama, char* alamat, char* nomor_telepon, char* password, int tipe_pengguna, HashPassword *morseTree) {
    User user_baru;
    
    // Salin data ke struktur user
    strcpy(user_baru.email, email);
    strcpy(user_baru.nama, nama);
    strcpy(user_baru.alamat, alamat);
    strcpy(user_baru.nomor_telepon, nomor_telepon);
    
    // Hash password sebelum disimpan
    char *hashed_password = HashPasswordWithMorse(morseTree, password);
    strcpy(user_baru.password, hashed_password);
    free(hashed_password);
    
    // Set tipe pengguna
    user_baru.is_admin = tipe_pengguna; // Menggunakan integer untuk tipe pengguna
    
    return user_baru;
}

// Fungsi untuk menambahkan akun baru ke dalam list
boolean TambahAkun(ListUser *L, User user_baru) {
    // Cek apakah email sudah terdaftar
    if (SearchUserByEmail(*L, user_baru.email) != NULL) {
        return FALSE; // Email sudah terdaftar
    }
    
    // Buat node baru
    DataUser *new_user = CreateDataUser(user_baru);
    if (new_user == NULL) {
        return FALSE; // Gagal alokasi memori
    }
    
    // Tambahkan ke list
    InsertLastUser(L, new_user);
    return TRUE;
}

// Fungsi untuk login
boolean Login(ListUser L, char* email, char* password, User* user_aktif, HashPassword *morseTree) {
    // Cari akun berdasarkan email
    DataUser *user_node = SearchUserByEmail(L, email);
    if (user_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Verifikasi password
    char *hashed_password = HashPasswordWithMorse(morseTree, password);
    boolean result = FALSE;
    
    if (strcmp(user_node->user_info.password, hashed_password) == 0) {
        // Password benar, salin data user
        if (user_aktif != NULL) {
            *user_aktif = user_node->user_info;
        }
        result = TRUE;
    }
    
    free(hashed_password);
    return result;
}

// Fungsi untuk mencari akun berdasarkan email
boolean CariAkun(ListUser L, char* email, User* hasil) {
    DataUser *user_node = SearchUserByEmail(L, email);
    if (user_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Salin data user jika hasil tidak NULL
    if (hasil != NULL) {
        *hasil = user_node->user_info;
    }
    
    return TRUE;
}

// Fungsi untuk memperbarui informasi akun
boolean UpdateAkun(ListUser *L, char* email, User user_baru) {
    DataUser *user_node = SearchUserByEmail(*L, email);
    if (user_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Update data user
    strcpy(user_node->user_info.nama, user_baru.nama);
    strcpy(user_node->user_info.alamat, user_baru.alamat);
    strcpy(user_node->user_info.nomor_telepon, user_baru.nomor_telepon);
    
    // Jangan update password di sini, gunakan fungsi UbahPassword
    // Jangan update email karena email digunakan sebagai identifier unik
    
    return TRUE;
}

// Fungsi untuk menghapus akun
boolean HapusAkun(ListUser *L, char* email) {
    if (isEmptyUser(*L)) {
        return FALSE; // List kosong
    }
    
    // Jika akun yang dihapus adalah elemen pertama
    if (strcmp(L->First->user_info.email, email) == 0) {
        DeleteFirstUser(L);
        return TRUE;
    }
    
    // Cari akun di posisi lain
    DataUser *prev = L->First;
    DataUser *current = prev->next;
    
    while (current != NULL) {
        if (strcmp(current->user_info.email, email) == 0) {
            // Hapus node current
            prev->next = current->next;
            free(current);
            return TRUE;
        }
        
        prev = current;
        current = current->next;
    }
    
    return FALSE; // Email tidak ditemukan
}

// Fungsi untuk menampilkan informasi akun
void TampilkanAkun(User user) {
    printf("===============================\n");
    printf("Informasi Akun:\n");
    printf("Email: %s\n", user.email);
    printf("Nama: %s\n", user.nama);
    printf("Alamat: %s\n", user.alamat);
    printf("Nomor Telepon: %s\n", user.nomor_telepon);
    
    // Tampilkan tipe pengguna
    printf("Tipe Pengguna: ");
    switch (user.is_admin) {
        case 1:
            printf("Admin\n");
            break;
        case 2:
            printf("Kasir\n");
            break;
        case 3:
            printf("Mesin\n");
            break;
        case 4:
            printf("User Biasa\n");
            break;
        default:
            printf("Tidak Diketahui\n");
    }
    printf("===============================\n");
}

// Fungsi untuk menampilkan semua akun (hanya admin)
void TampilkanSemuaAkun(ListUser L) {
    if (isEmptyUser(L)) {
        printf("Daftar akun kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Daftar Semua Akun:\n");
    printf("===============================\n");
    
    DataUser *user_node = L.First;
    int count = 1;
    
    while (user_node != NULL) {
        printf("Akun #%d\n", count++);
        printf("Email: %s\n", user_node->user_info.email);
        printf("Nama: %s\n", user_node->user_info.nama);
        printf("Alamat: %s\n", user_node->user_info.alamat);
        printf("Nomor Telepon: %s\n", user_node->user_info.nomor_telepon);
        
        // Tampilkan tipe pengguna
        printf("Tipe Pengguna: ");
        switch (user_node->user_info.is_admin) {
            case 1:
                printf("Admin\n");
                break;
            case 2:
                printf("Kasir\n");
                break;
            case 3:
                printf("Mesin\n");
                break;
            case 4:
                printf("User Biasa\n");
                break;
            default:
                printf("Tidak Diketahui\n");
        }
        printf("-------------------------------\n");
        
        user_node = user_node->next;
    }
}

// Fungsi untuk mengubah password
boolean UbahPassword(ListUser *L, char* email, char* password_lama, char* password_baru, HashPassword *morseTree) {
    DataUser *user_node = SearchUserByEmail(*L, email);
    if (user_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Verifikasi password lama
    char *hashed_password_lama = HashPasswordWithMorse(morseTree, password_lama);
    
    if (strcmp(user_node->user_info.password, hashed_password_lama) != 0) {
        free(hashed_password_lama);
        return FALSE; // Password lama salah
    }
    free(hashed_password_lama);
    
    // Update password
    char *hashed_password_baru = HashPasswordWithMorse(morseTree, password_baru);
    strcpy(user_node->user_info.password, hashed_password_baru);
    free(hashed_password_baru);
    
    return TRUE;
}

// Fungsi untuk mengubah tipe pengguna (hanya admin)
boolean UbahTipePengguna(ListUser *L, char* email, int tipe_pengguna_baru) {
    // Validasi tipe pengguna
    if (tipe_pengguna_baru < 1 || tipe_pengguna_baru > 4) {
        return FALSE; // Tipe pengguna tidak valid
    }
    
    DataUser *user_node = SearchUserByEmail(*L, email);
    if (user_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Update tipe pengguna
    user_node->user_info.is_admin = tipe_pengguna_baru;
    
    return TRUE;
}

// Fungsi untuk validasi email
boolean ValidasiEmail(char* email) {
    // Implementasi sederhana validasi email
    // Cek apakah email mengandung karakter '@' dan '.'
    if (strchr(email, '@') == NULL || strchr(email, '.') == NULL) {
        return FALSE;
    }
    
    // Cek panjang email
    if (strlen(email) < 5 || strlen(email) > 100) {
        return FALSE;
    }
    
    return TRUE;
}

// Fungsi untuk validasi nomor telepon
boolean ValidasiNomorTelepon(char* nomor_telepon) {
    // Cek panjang nomor telepon
    int panjang = strlen(nomor_telepon);
    if (panjang < 10 || panjang > 13) {
        return FALSE;
    }
    
    // Cek apakah semua karakter adalah digit
    for (int i = 0; i < panjang; i++) {
        if (nomor_telepon[i] < '0' || nomor_telepon[i] > '9') {
            return FALSE;
        }
    }
    
    return TRUE;
} 