/*
Author: Devi Maulani 
NIM: 241524007 
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_tiket_saya.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fungsi untuk menginisialisasi TiketSaya
void CreateTiketSaya(TiketSaya *T) {
    // Inisialisasi stack dalam TiketSaya
    CreateStackRiwayat(&(T->tiket_user));
}

// Fungsi untuk mengambil semua tiket user yang sedang login
void AmbilTiketSaya(const char *filename, User user_aktif, TiketSaya *hasil) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
    
    // Kosongkan stack hasil jika sudah berisi
    DeAlokasiStackRiwayat(&(hasil->tiket_user));
    CreateStackRiwayat(&(hasil->tiket_user));
    
    // Buffer untuk membaca data
    char buffer[512];
    char kode_kereta[20], nama_kereta[100], stasiun_asal[100], stasiun_tujuan[100];
    char jam_berangkat[10], jam_tiba[10], tanggal_berangkat[20];
    char harga[20], kelas[20], nama_penumpang[100], email[100], telepon[20];
    char gerbong[10], kursi[10], waktu_pemesanan[50];
    
    // Stack sementara untuk mempertahankan urutan yang benar
    StackRiwayat tempStack;
    CreateStackRiwayat(&tempStack);
    
    // Baca data dari file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                kode_kereta, nama_kereta, stasiun_asal, stasiun_tujuan, 
                jam_berangkat, jam_tiba, tanggal_berangkat, harga, kelas,
                nama_penumpang, email, telepon, gerbong, kursi, waktu_pemesanan) == 15) {
            
            // Cek apakah tiket ini milik user yang sedang login
            if (strcmp(email, user_aktif.email) == 0) {
                // Buat objek RiwayatTiket
                RiwayatTiket tiket;
                
                // Data user
                strcpy(tiket.riwayat_user.nama, nama_penumpang);
                strcpy(tiket.riwayat_user.email, email);
                strcpy(tiket.riwayat_user.nomor_telepon, telepon);
                
                // Data kereta
                strcpy(tiket.riwayat_kereta.kode_kereta, kode_kereta);
                strcpy(tiket.riwayat_kereta.nama_kereta, nama_kereta);
                strcpy(tiket.riwayat_kereta.stasiun_asal, stasiun_asal);
                strcpy(tiket.riwayat_kereta.stasiun_tujuan, stasiun_tujuan);
                strcpy(tiket.riwayat_kereta.jam_berangkat, jam_berangkat);
                strcpy(tiket.riwayat_kereta.jam_tiba, jam_tiba);
                strcpy(tiket.riwayat_kereta.tanggal_berangkat, tanggal_berangkat);
                strcpy(tiket.riwayat_kereta.kelas, kelas);
                tiket.riwayat_kereta.harga = atoi(harga);
                
                // Data gerbong dan kursi
                // Mengabaikan huruf di depan (misalnya: B5 -> 5)
                tiket.riwayat_nomor_gerbong = atoi(gerbong+1);
                tiket.riwayat_nomor_kursi = atoi(kursi);
                
                // Data waktu pemesanan
                // Parsing waktu pemesanan (format: 2025-06-04 23:01:12)
                int tahun, bulan, hari, jam, menit, detik;
                sscanf(waktu_pemesanan, "%d-%d-%d %d:%d:%d", 
                      &tahun, &bulan, &hari, &jam, &menit, &detik);
                
                tiket.riwayat_waktu_pemesanan.tahun = tahun;
                tiket.riwayat_waktu_pemesanan.bulan = bulan;
                tiket.riwayat_waktu_pemesanan.hari = hari;
                tiket.riwayat_waktu_pemesanan.jam = jam;
                tiket.riwayat_waktu_pemesanan.menit = menit;
                tiket.riwayat_waktu_pemesanan.detik = detik;
                
                // Tambahkan ke stack
                PushRiwayat(&tempStack, tiket);
            }
        }
    }
    
    // Pindahkan dari stack sementara ke stack hasil agar urutan tetap benar
    RiwayatTiket tiket;
    while (!isEmptyStackRiwayat(tempStack)) {
        if (PopRiwayat(&tempStack, &tiket)) {
            PushRiwayat(&(hasil->tiket_user), tiket);
        }
    }
    
    fclose(file);
}

// Fungsi untuk menampilkan semua tiket user yang sedang login
void TampilkanTiketSaya(TiketSaya T, User user_aktif) {
    if (isEmptyStackRiwayat(T.tiket_user)) {
        printf("\n===== TIKET SAYA =====\n");
        printf("Email: %s\n", user_aktif.email);
        printf("------------------------\n");
        printf("Anda belum memiliki tiket!\n");
        printf("========================\n");
        return;
    }

    // Buat stack sementara untuk menyimpan elemen yang di-pop
    StackRiwayat tempStack;
    CreateStackRiwayat(&tempStack);
    RiwayatTiket tiket;
    
    printf("\n===== TIKET SAYA =====\n");
    printf("Email: %s\n", user_aktif.email);
    printf("------------------------\n");
    
    int nomor = 1;
    addressRiwayat P = T.tiket_user.top;
    
    // Salin elemen ke stack sementara dan tampilkan
    while (P != NULL) {
        tiket = P->info;
        
        printf("%d. Kereta: %s\n", nomor++, tiket.riwayat_kereta.nama_kereta);
        printf("   Rute: %s -> %s\n", tiket.riwayat_kereta.stasiun_asal, tiket.riwayat_kereta.stasiun_tujuan);
        printf("   Tanggal: %s\n", tiket.riwayat_kereta.tanggal_berangkat);
        printf("   Jam: %s - %s\n", tiket.riwayat_kereta.jam_berangkat, tiket.riwayat_kereta.jam_tiba);
        printf("------------------------\n");
        
        // Simpan ke stack sementara dan lanjut ke node berikutnya
        PushRiwayat(&tempStack, tiket);
        P = P->next;
    }
    
    printf("========================\n");
    
    // Kembalikan elemen ke stack asli
    StackRiwayat tempStack2;
    CreateStackRiwayat(&tempStack2);
    
    while (!isEmptyStackRiwayat(tempStack)) {
        if (PopRiwayat(&tempStack, &tiket)) {
            PushRiwayat(&tempStack2, tiket);
        }
    }
    
    while (!isEmptyStackRiwayat(tempStack2)) {
        if (PopRiwayat(&tempStack2, &tiket)) {
            PushRiwayat(&(T.tiket_user), tiket);
        }
    }
}

// Fungsi untuk menampilkan detail tiket berdasarkan indeks
boolean TampilkanDetailTiketPembelian(TiketSaya T, User user_aktif, int indeks) {
    if (isEmptyStackRiwayat(T.tiket_user)) {
        printf("Anda belum memiliki tiket!\n");
        return FALSE;
    }
    
    int total = NbElmtStackRiwayat(T.tiket_user);
    if (indeks < 1 || indeks > total) {
        printf("Indeks tiket tidak valid!\n");
        return FALSE;
    }
    
    // Buat stack sementara untuk menyimpan elemen yang di-pop
    StackRiwayat tempStack;
    CreateStackRiwayat(&tempStack);
    RiwayatTiket tiket;
    
    // Ambil tiket berdasarkan indeks
    int current = 1;
    addressRiwayat P = T.tiket_user.top;
    
    // Salin elemen ke stack sementara
    while (P != NULL) {
        tiket = P->info;
        
        // Jika indeks sesuai, tampilkan detail
        if (current == indeks) {
            printf("\n===== DETAIL TIKET =====\n");
            printf("Nama Penumpang: %s\n", tiket.riwayat_user.nama);
            printf("Email: %s\n", tiket.riwayat_user.email);
            printf("Telepon: %s\n", tiket.riwayat_user.nomor_telepon);
            printf("------------------------\n");
            printf("Kode Kereta: %s\n", tiket.riwayat_kereta.kode_kereta);
            printf("Nama Kereta: %s\n", tiket.riwayat_kereta.nama_kereta);
            printf("Rute: %s -> %s\n", tiket.riwayat_kereta.stasiun_asal, tiket.riwayat_kereta.stasiun_tujuan);
            printf("Tanggal Berangkat: %s\n", tiket.riwayat_kereta.tanggal_berangkat);
            printf("Jam Berangkat: %s\n", tiket.riwayat_kereta.jam_berangkat);
            printf("Jam Tiba: %s\n", tiket.riwayat_kereta.jam_tiba);
            printf("Kelas: %s\n", tiket.riwayat_kereta.kelas);
            printf("Harga: Rp%d\n", tiket.riwayat_kereta.harga);
            printf("Gerbong: %d\n", tiket.riwayat_nomor_gerbong);
            printf("Kursi: %d\n", tiket.riwayat_nomor_kursi);
            printf("------------------------\n");
            printf("Waktu Pemesanan: %02d-%02d-%04d %02d:%02d:%02d\n", 
                   tiket.riwayat_waktu_pemesanan.hari,
                   tiket.riwayat_waktu_pemesanan.bulan,
                   tiket.riwayat_waktu_pemesanan.tahun,
                   tiket.riwayat_waktu_pemesanan.jam,
                   tiket.riwayat_waktu_pemesanan.menit,
                   tiket.riwayat_waktu_pemesanan.detik);
            printf("=======================\n");
        }
        
        // Simpan ke stack sementara
        PushRiwayat(&tempStack, tiket);
        P = P->next;
        current++;
    }
    
    // Kembalikan elemen ke stack asli
    StackRiwayat tempStack2;
    CreateStackRiwayat(&tempStack2);
    
    while (!isEmptyStackRiwayat(tempStack)) {
        if (PopRiwayat(&tempStack, &tiket)) {
            PushRiwayat(&tempStack2, tiket);
        }
    }
    
    while (!isEmptyStackRiwayat(tempStack2)) {
        if (PopRiwayat(&tempStack2, &tiket)) {
            PushRiwayat(&(T.tiket_user), tiket);
        }
    }
    
    return TRUE;
}

// Fungsi untuk dealokasi memori TiketSaya
void DealokasiTiketSaya(TiketSaya *T) {
    // Hapus semua elemen dalam stack
    DeAlokasiStackRiwayat(&(T->tiket_user));
}

// Fungsi untuk menampilkan semua tiket pengguna
void LihatSemuaTiket(User user_aktif) {
    // Inisialisasi variabel TiketSaya
    TiketSaya tiketSaya;
    CreateTiketSaya(&tiketSaya);
    
    // Ambil tiket user dari file riwayat
    AmbilTiketSaya("riwayat_pemesanan.txt", user_aktif, &tiketSaya);
    
    // Tampilkan tiket
    TampilkanTiketSaya(tiketSaya, user_aktif);
    
    // Bersihkan memori
    DealokasiTiketSaya(&tiketSaya);
}

// Fungsi untuk melihat detail tiket berdasarkan indeks
void LihatDetailTiketByIndex(User user_aktif) {
    // Inisialisasi variabel TiketSaya
    TiketSaya tiketSaya;
    CreateTiketSaya(&tiketSaya);
    
    // Ambil tiket user dari file riwayat
    AmbilTiketSaya("riwayat_pemesanan.txt", user_aktif, &tiketSaya);
    
    // Tampilkan tiket
    TampilkanTiketSaya(tiketSaya, user_aktif);
    
    // Jika ada tiket, minta indeks
    if (!isEmptyStackRiwayat(tiketSaya.tiket_user)) {
        int indeks;
        printf("\nMasukkan nomor tiket yang ingin dilihat detailnya: ");
        scanf("%d", &indeks);
        
        if (!TampilkanDetailTiket(tiketSaya, user_aktif, indeks)) {
            printf("Gagal menampilkan detail tiket!\n");
        }
    }
    
    // Bersihkan memori
    DealokasiTiketSaya(&tiketSaya);
}
