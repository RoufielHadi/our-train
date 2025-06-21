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
#include "databases.h" // Untuk tipe Record dan operasi file
#include <ctype.h>
#define TambahNilai TambahField

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
    if (email == NULL) {
        return FALSE;
    }
    // Cek keberadaan satu '@'
    char* at = strchr(email, '@');
    if (at == NULL || at == email) {
        return FALSE;
    }
    if (strchr(at + 1, '@') != NULL) {
        return FALSE;
    }
    // Cek domain memiliki titik
    char* dot = strchr(at + 1, '.');
    if (dot == NULL || *(dot + 1) == '\0') {
        return FALSE;
    }
    // Panjang minimum
    size_t len = strlen(email);
    if (len < 5 || len > 100) {
        return FALSE;
    }
    return TRUE;
}

// Fungsi untuk validasi nomor telepon
boolean ValidasiNomorTelepon(char* nomor_telepon) {
    if (nomor_telepon == NULL) {
        return FALSE;
    }
    int panjang = strlen(nomor_telepon);
    // Nomor telepon harus diawali '08' dan panjang antara 11-13 digit
    if (panjang < 11 || panjang > 13) {
        return FALSE;
    }
    if (nomor_telepon[0] != '0' || nomor_telepon[1] != '8') {
        return FALSE;
    }
    // Cek setiap karakter adalah digit
    int i;
    for (i = 0; i < panjang; i++) {
        if (!isdigit((unsigned char)nomor_telepon[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

// Fungsi untuk validasi saldo
boolean ValidasiSaldo(const char* saldo_str) {
    if (saldo_str == NULL || *saldo_str == '\0') {
        return FALSE;
    }
    // Cek setiap karakter adalah digit
    int i;
    for (i = 0; saldo_str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)saldo_str[i])) {
            return FALSE;
        }
    }
    // Konversi ke nilai numerik dan cek non-negatif
    long val = atol(saldo_str);
    if (val < 0) {
        return FALSE;
    }
    return TRUE;
}

// Fungsi untuk memformat nama ke Title Case
void FormatNama(char* nama) {
	int i;
    if (nama == NULL) {
        return;
    }
    int len = strlen(nama);
    int newWord = 1;
    for (i = 0; i < len; i++) {
        if (isspace((unsigned char)nama[i])) {
            newWord = 1;
        } else if (newWord) {
            nama[i] = toupper((unsigned char)nama[i]);
            newWord = 0;
        } else {
            nama[i] = tolower((unsigned char)nama[i]);
        }
    }
}

// Fungsi untuk membuat akun kasir
User BuatAkunKasir(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree) {
    char email[100];
    
    // Format email untuk kasir: kasir.namastasiun@ourtrain.com
    sprintf(email, "kasir.%s@ourtrain.com", nama_stasiun);
    
    // Buat akun dengan tipe pengguna 3 (kasir)
    return BuatAkun(email, nama, alamat, nomor_telepon, password, 3, morseTree);
}

// Fungsi untuk menambahkan akun kasir
boolean TambahAkunKasir(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree) {
    // Format email untuk kasir
    char email[100];
    sprintf(email, "kasir.%s@ourtrain.com", nama_stasiun);
    
    // Periksa apakah email sudah ada
    Record record;
    InisialisasiRecord(&record);
    if (BacaAkunUser(&record, email)) {
        return FALSE; // Email sudah terdaftar
    }
    
    // Buat akun kasir
    User user_kasir = BuatAkunKasir(nama_stasiun, nama, alamat, nomor_telepon, password, morseTree);
    
    // Simpan ke file
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    // Set nilai record
    TambahNilai(&userRecord, "email", user_kasir.email);
    TambahNilai(&userRecord, "nama", user_kasir.nama);
    TambahNilai(&userRecord, "alamat", user_kasir.alamat);
    TambahNilai(&userRecord, "nomor_telepon", user_kasir.nomor_telepon);
    TambahNilai(&userRecord, "password", user_kasir.password);
    
    char tipe_akun_str[2];
    sprintf(tipe_akun_str, "%d", user_kasir.is_admin);
    TambahNilai(&userRecord, "tipe_akun", tipe_akun_str);
    
    // Tulis ke file
    boolean result = TulisAkunUser(&userRecord);
    
    return result;
}

// Fungsi untuk menampilkan semua akun kasir
void TampilkanSemuaAkunKasir(ListUser L) {
    if (isEmptyUser(L)) {
        printf("Daftar akun kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Daftar Akun Kasir:\n");
    printf("===============================\n");
    
    DataUser *user_node = L.First;
    int count = 1;
    
    while (user_node != NULL) {
        // Hanya tampilkan akun dengan tipe kasir (3)
        if (user_node->user_info.is_admin == 3) {
            printf("Kasir #%d\n", count++);
            printf("Email: %s\n", user_node->user_info.email);
            printf("Nama: %s\n", user_node->user_info.nama);
            printf("Alamat: %s\n", user_node->user_info.alamat);
            printf("Nomor Telepon: %s\n", user_node->user_info.nomor_telepon);
            printf("-------------------------------\n");
        }
        
        user_node = user_node->next;
    }
    
    if (count == 1) {
        printf("Tidak ada akun kasir yang terdaftar.\n");
    }
}

// Fungsi untuk menghapus akun kasir berdasarkan email
boolean HapusAkunKasir(char* email) {
    // Periksa apakah email ada
    Record record;
    InisialisasiRecord(&record);
    if (!BacaAkunUser(&record, email)) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Periksa apakah akun adalah kasir
    char* tipe_akun_str = AmbilNilai(&record, "tipe_akun");
    if (tipe_akun_str == NULL || atoi(tipe_akun_str) != 3) {
        return FALSE; // Bukan akun kasir
    }
    
    // Hapus akun dari file
    return HapusAkunDariFile(email);
}

// Fungsi untuk mengedit akun kasir berdasarkan email
boolean EditAkunKasir(char* email, char* nama, char* alamat, char* nomor_telepon, HashPassword *morseTree) {
    // Periksa apakah email ada
    Record record;
    InisialisasiRecord(&record);
    if (!BacaAkunUser(&record, email)) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Periksa apakah akun adalah kasir
    char* tipe_akun_str2 = AmbilNilai(&record, "tipe_akun");
    if (tipe_akun_str2 == NULL || atoi(tipe_akun_str2) != 3) {
        return FALSE; // Bukan akun kasir
    }
    
    // Update nilai record
    TambahNilai(&record, "nama", nama);
    TambahNilai(&record, "alamat", alamat);
    TambahNilai(&record, "nomor_telepon", nomor_telepon);
    
    // Tulis kembali ke file
    boolean result2 = HapusAkunDariFile(email) && TulisAkunUser(&record);
    
    return result2;
}

// Fungsi untuk membuat akun mesin
User BuatAkunMesin(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree) {
    char email[100];
    
    // Format email untuk mesin: mesin.namastasiun@ourtrain.com
    sprintf(email, "mesin.%s@ourtrain.com", nama_stasiun);
    
    // Buat akun dengan tipe pengguna 4 (mesin)
    return BuatAkun(email, nama, alamat, nomor_telepon, password, 4, morseTree);
}

// Fungsi untuk menambahkan akun mesin
boolean TambahAkunMesin(char* nama_stasiun, char* nama, char* alamat, char* nomor_telepon, char* password, HashPassword *morseTree) {
    // Format email untuk mesin
    char email[100];
    sprintf(email, "mesin.%s@ourtrain.com", nama_stasiun);
    
    // Periksa apakah email sudah ada
    Record record2;
    InisialisasiRecord(&record2);
    if (BacaAkunUser(&record2, email)) {
        return FALSE; // Email sudah terdaftar
    }
    
    // Buat akun mesin
    User user_mesin = BuatAkunMesin(nama_stasiun, nama, alamat, nomor_telepon, password, morseTree);
    
    // Simpan ke file
    Record userRecord2;
    InisialisasiRecord(&userRecord2);
    
    // Set nilai record
    TambahNilai(&userRecord2, "email", user_mesin.email);
    TambahNilai(&userRecord2, "nama", user_mesin.nama);
    TambahNilai(&userRecord2, "alamat", user_mesin.alamat);
    TambahNilai(&userRecord2, "nomor_telepon", user_mesin.nomor_telepon);
    TambahNilai(&userRecord2, "password", user_mesin.password);
    
    char tipe_akun_str[2];
    sprintf(tipe_akun_str, "%d", user_mesin.is_admin);
    TambahNilai(&userRecord2, "tipe_akun", tipe_akun_str);
    
    // Tulis ke file
    boolean result3 = TulisAkunUser(&userRecord2);
    
    return result3;
}

// Fungsi untuk menampilkan semua akun mesin
void TampilkanSemuaAkunMesin(ListUser L) {
    if (isEmptyUser(L)) {
        printf("Daftar akun kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Daftar Akun Mesin:\n");
    printf("===============================\n");
    
    DataUser *user_node = L.First;
    int count = 1;
    
    while (user_node != NULL) {
        // Hanya tampilkan akun dengan tipe mesin (4)
        if (user_node->user_info.is_admin == 4) {
            printf("Mesin #%d\n", count++);
            printf("Email: %s\n", user_node->user_info.email);
            printf("Nama: %s\n", user_node->user_info.nama);
            printf("Alamat: %s\n", user_node->user_info.alamat);
            printf("Nomor Telepon: %s\n", user_node->user_info.nomor_telepon);
            printf("-------------------------------\n");
        }
        
        user_node = user_node->next;
    }
    
    if (count == 1) {
        printf("Tidak ada akun mesin yang terdaftar.\n");
    }
}

// Fungsi untuk menghapus akun mesin berdasarkan email
boolean HapusAkunMesin(char* email) {
    Record record3;
    InisialisasiRecord(&record3);
    if (!BacaAkunUser(&record3, email)) {
        return FALSE; // Email tidak ditemukan
    }
    char* tipe_akun_str3 = AmbilNilai(&record3, "tipe_akun");
    if (tipe_akun_str3 == NULL || atoi(tipe_akun_str3) != 4) {
        return FALSE; // Bukan akun mesin
    }
    return HapusAkunDariFile(email);
}

// Fungsi untuk mengedit akun mesin berdasarkan email
boolean EditAkunMesin(char* email, char* nama, char* alamat, char* nomor_telepon, HashPassword *morseTree) {
    Record record4;
    InisialisasiRecord(&record4);
    if (!BacaAkunUser(&record4, email)) {
        return FALSE;
    }
    char* tipe_akun_str4 = AmbilNilai(&record4, "tipe_akun");
    if (tipe_akun_str4 == NULL || atoi(tipe_akun_str4) != 4) {
        return FALSE;
    }

    TambahNilai(&record4, "nama", nama);
    TambahNilai(&record4, "alamat", alamat);
    TambahNilai(&record4, "nomor_telepon", nomor_telepon);

    boolean result4 = HapusAkunDariFile(email) && TulisAkunUser(&record4);
    
    return result4;
}

// Fungsi untuk menulis akun ke file (alias untuk SimpanAkunUser)
boolean TulisAkunUser(Record* record) {
    return SimpanAkunUser(record);
}

// Fungsi untuk menghapus akun dari file (alias untuk HapusAkunUser)
boolean HapusAkunDariFile(char* email) {
    return HapusAkunUser(email);
} 
