/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_pembayaran.h"
#include "hash_password.h" // Untuk fungsi hashing PIN

// Fungsi untuk membuat data pembayaran baru
Payment BuatDataPembayaran(char* email, char* no_rekening, int saldo, char* pin) {
    Payment payment_baru;
    
    // Salin data ke struktur payment
    strcpy(payment_baru.email, email);
    strcpy(payment_baru.no_rekening, no_rekening);
    payment_baru.saldo = saldo;
    
    // Hash PIN sebelum disimpan
    char hashed_pin[64];
    HashPassword(pin, hashed_pin); // Menggunakan fungsi hash yang sama dengan password
    strcpy(payment_baru.pin, hashed_pin);
    
    return payment_baru;
}

// Fungsi untuk menambahkan data pembayaran ke dalam list
boolean TambahDataPembayaran(ListPayment *L, Payment payment_baru) {
    // Cek apakah email sudah terdaftar
    if (SearchPaymentByEmail(*L, payment_baru.email) != NULL) {
        return FALSE; // Email sudah terdaftar
    }
    
    // Buat node baru
    PaymentUser *new_payment = CreateDataPayment(payment_baru);
    if (new_payment == NULL) {
        return FALSE; // Gagal alokasi memori
    }
    
    // Tambahkan ke list
    InsertLastPayment(L, new_payment);
    return TRUE;
}

// Fungsi untuk mencari data pembayaran berdasarkan email
boolean CariDataPembayaran(ListPayment L, char* email, Payment* hasil) {
    PaymentUser *payment_node = SearchPaymentByEmail(L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Salin data payment jika hasil tidak NULL
    if (hasil != NULL) {
        *hasil = payment_node->payment_info;
    }
    
    return TRUE;
}

// Fungsi untuk menambah saldo
boolean TambahSaldo(ListPayment *L, char* email, char* pin, int jumlah) {
    if (jumlah <= 0) {
        return FALSE; // Jumlah tidak valid
    }
    
    PaymentUser *payment_node = SearchPaymentByEmail(*L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Verifikasi PIN
    if (!ValidasiPIN(*L, email, pin)) {
        return FALSE; // PIN tidak valid
    }
    
    // Tambah saldo
    payment_node->payment_info.saldo += jumlah;
    
    return TRUE;
}

// Fungsi untuk mengurangi saldo (untuk pembelian tiket)
boolean KurangiSaldo(ListPayment *L, char* email, char* pin, int jumlah) {
    if (jumlah <= 0) {
        return FALSE; // Jumlah tidak valid
    }
    
    PaymentUser *payment_node = SearchPaymentByEmail(*L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Verifikasi PIN
    if (!ValidasiPIN(*L, email, pin)) {
        return FALSE; // PIN tidak valid
    }
    
    // Cek kecukupan saldo
    if (payment_node->payment_info.saldo < jumlah) {
        return FALSE; // Saldo tidak cukup
    }
    
    // Kurangi saldo
    payment_node->payment_info.saldo -= jumlah;
    
    return TRUE;
}

// Fungsi untuk mengubah PIN
boolean UbahPIN(ListPayment *L, char* email, char* pin_lama, char* pin_baru) {
    PaymentUser *payment_node = SearchPaymentByEmail(*L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Verifikasi PIN lama
    if (!ValidasiPIN(*L, email, pin_lama)) {
        return FALSE; // PIN lama tidak valid
    }
    
    // Update PIN
    char hashed_pin_baru[64];
    HashPassword(pin_baru, hashed_pin_baru);
    strcpy(payment_node->payment_info.pin, hashed_pin_baru);
    
    return TRUE;
}

// Fungsi untuk menampilkan informasi pembayaran
void TampilkanInfoPembayaran(Payment payment) {
    printf("===============================\n");
    printf("Informasi Pembayaran:\n");
    printf("Email: %s\n", payment.email);
    printf("No. Rekening: %s\n", payment.no_rekening);
    printf("Saldo: Rp%d\n", payment.saldo);
    printf("===============================\n");
}

// Fungsi untuk menampilkan semua data pembayaran (hanya admin)
void TampilkanSemuaDataPembayaran(ListPayment L) {
    if (isEmptyPayment(L)) {
        printf("Daftar pembayaran kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Daftar Semua Data Pembayaran:\n");
    printf("===============================\n");
    
    PaymentUser *payment_node = L.First;
    int count = 1;
    
    while (payment_node != NULL) {
        printf("Pembayaran #%d\n", count++);
        printf("Email: %s\n", payment_node->payment_info.email);
        printf("No. Rekening: %s\n", payment_node->payment_info.no_rekening);
        printf("Saldo: Rp%d\n", payment_node->payment_info.saldo);
        printf("-------------------------------\n");
        
        payment_node = payment_node->next;
    }
}

// Fungsi untuk validasi PIN
boolean ValidasiPIN(ListPayment L, char* email, char* pin) {
    PaymentUser *payment_node = SearchPaymentByEmail(L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Verifikasi PIN
    char hashed_pin[64];
    HashPassword(pin, hashed_pin);
    
    return (strcmp(payment_node->payment_info.pin, hashed_pin) == 0);
}

// Fungsi untuk memperbarui data pembayaran
boolean UpdateDataPembayaran(ListPayment *L, char* email, Payment payment_baru) {
    PaymentUser *payment_node = SearchPaymentByEmail(*L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    // Update data payment (kecuali email karena primary key)
    strcpy(payment_node->payment_info.no_rekening, payment_baru.no_rekening);
    
    // Pin dan saldo tidak diupdate di sini, gunakan fungsi khusus untuk itu
    
    return TRUE;
}

// Fungsi untuk menghapus data pembayaran
boolean HapusDataPembayaran(ListPayment *L, char* email) {
    if (isEmptyPayment(*L)) {
        return FALSE; // List kosong
    }
    
    // Jika pembayaran yang dihapus adalah elemen pertama
    if (strcmp(L->First->payment_info.email, email) == 0) {
        DeleteFirstPayment(L);
        return TRUE;
    }
    
    // Cari pembayaran di posisi lain
    PaymentUser *prev = L->First;
    PaymentUser *current = prev->next;
    
    while (current != NULL) {
        if (strcmp(current->payment_info.email, email) == 0) {
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

// Fungsi untuk cek kecukupan saldo
boolean CekKecukupanSaldo(ListPayment L, char* email, int jumlah) {
    PaymentUser *payment_node = SearchPaymentByEmail(L, email);
    if (payment_node == NULL) {
        return FALSE; // Email tidak ditemukan
    }
    
    return (payment_node->payment_info.saldo >= jumlah);
}

// Fungsi untuk validasi nomor rekening
boolean ValidasiNomorRekening(char* no_rekening) {
    // Cek panjang nomor rekening (umumnya 10-16 digit)
    int panjang = strlen(no_rekening);
    if (panjang < 10 || panjang > 16) {
        return FALSE;
    }
    
    // Cek apakah semua karakter adalah digit
    for (int i = 0; i < panjang; i++) {
        if (no_rekening[i] < '0' || no_rekening[i] > '9') {
            return FALSE;
        }
    }
    
    return TRUE;
} 