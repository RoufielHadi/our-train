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
    
    // Baca data dari file dan split berdasarkan '|'
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Hapus newline di akhir
        buffer[strcspn(buffer, "\n")] = '\0';
        // Split line ke tokens
        char* tokens[16];
        int count = 0;
        char* p = strtok(buffer, "|");
        while (p != NULL && count < 16) {
            tokens[count++] = p;
            p = strtok(NULL, "|");
        }
        // Minimal 14 field dibutuhkan
        if (count < 14) continue;
        // Ambil field yang fixed
        char* kode_kereta_f = tokens[0];
        char* nama_kereta_f = tokens[1];
        char* stasiun_asal_f = tokens[2];
        char* stasiun_tujuan_f = tokens[3];
        char* jam_berangkat_f = tokens[4];
        char* jam_tiba_f = tokens[5];
        char* tanggal_berangkat_f = tokens[6];
        char* harga_str;
        char* kelas_str;
        int idx = 7;
        // Jika 15 field, field[7]=harga, field[8]=kelas
        if (count == 15) {
            harga_str = tokens[7];
            kelas_str = tokens[8];
            idx = 9;
        } else {
            harga_str = "0";  // default harga
            kelas_str = tokens[7];
            idx = 8;
        }
        // Ambil field selanjutnya
        char* nama_penumpang_f = tokens[idx++];
        char* email_f         = tokens[idx++];
        char* telepon_f       = tokens[idx++];
        char* gerbong_f       = tokens[idx++];
        char* kursi_f         = tokens[idx++];
        char* waktu_pesan_f   = tokens[idx];
        // Cek kecocokan email
        if (strcmp(email_f, user_aktif.email) != 0) continue;
        // Buat object tiket dan isi data
                RiwayatTiket tiket;
                // Data user
        strcpy(tiket.riwayat_user.nama, nama_penumpang_f);
        strcpy(tiket.riwayat_user.email, email_f);
        strcpy(tiket.riwayat_user.nomor_telepon, telepon_f);
                // Data kereta
        strcpy(tiket.riwayat_kereta.kode_kereta, kode_kereta_f);
        strcpy(tiket.riwayat_kereta.nama_kereta, nama_kereta_f);
        strcpy(tiket.riwayat_kereta.stasiun_asal, stasiun_asal_f);
        strcpy(tiket.riwayat_kereta.stasiun_tujuan, stasiun_tujuan_f);
        strcpy(tiket.riwayat_kereta.jam_berangkat, jam_berangkat_f);
        strcpy(tiket.riwayat_kereta.jam_tiba, jam_tiba_f);
        strcpy(tiket.riwayat_kereta.tanggal_berangkat, tanggal_berangkat_f);
        strcpy(tiket.riwayat_kereta.kelas, kelas_str);
        tiket.riwayat_kereta.harga = atoi(harga_str);
                // Data gerbong dan kursi
        tiket.riwayat_nomor_gerbong = atoi(kursi_f);  // nomor gerbong
        tiket.riwayat_nomor_kursi   = atoi(gerbong_f + 1);  // nomor kursi
        // Simpan kode huruf kursi (misalnya 'B' dari 'B5')
        tiket.riwayat_kode_kursi[0] = gerbong_f[0];
        tiket.riwayat_kode_kursi[1] = '\0';
                // Data waktu pemesanan
        int _tahun, _bulan, _hari, _jam, _menit, _detik;
        if (sscanf(waktu_pesan_f, "%d-%d-%d %d:%d:%d", &_tahun, &_bulan, &_hari, &_jam, &_menit, &_detik) == 6) {
            tiket.riwayat_waktu_pemesanan.tahun = _tahun;
            tiket.riwayat_waktu_pemesanan.bulan = _bulan;
            tiket.riwayat_waktu_pemesanan.hari  = _hari;
            tiket.riwayat_waktu_pemesanan.jam   = _jam;
            tiket.riwayat_waktu_pemesanan.menit = _menit;
            tiket.riwayat_waktu_pemesanan.detik = _detik;
        }
        // Push ke stack sementara
                PushRiwayat(&tempStack, tiket);
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
    // Jika tidak ada tiket, tampilkan pesan
    if (isEmptyStackRiwayat(T.tiket_user)) {
        printf("\n===== TIKET SAYA =====\n");
        printf("%-8s: %s\n", "Email", user_aktif.email);
        printf("========================================\n");
        printf("Anda belum memiliki tiket!\n");
        printf("========================================\n");
        return;
    }

    // Buat stack sementara untuk menyimpan elemen yang di-pop agar urutan tetap
    StackRiwayat tempStack;
    CreateStackRiwayat(&tempStack);
    RiwayatTiket tiket;
    
    // Header tampilan tiket
    printf("\n===== TIKET SAYA =====\n");
    printf("%-8s: %s\n", "Email", user_aktif.email);
    printf("========================================\n\n");
    
    // Tampilkan setiap tiket secara rapi
    int nomor = 1;
    addressRiwayat P = T.tiket_user.top;
    while (P != NULL) {
        tiket = P->info;
        printf("Tiket #%d\n", nomor++);
        printf("----------------------------------------\n");
        printf("%-8s: %s\n", "Kereta", tiket.riwayat_kereta.nama_kereta);
        printf("%-8s: %s -> %s\n", "Rute", tiket.riwayat_kereta.stasiun_asal, tiket.riwayat_kereta.stasiun_tujuan);
        printf("%-8s: %s\n", "Tanggal", tiket.riwayat_kereta.tanggal_berangkat);
        printf("%-8s: %s - %s\n", "Jam", tiket.riwayat_kereta.jam_berangkat, tiket.riwayat_kereta.jam_tiba);
        printf("\n");
        // Simpan ke stack sementara dan lanjut ke node berikutnya
        PushRiwayat(&tempStack, tiket);
        P = P->next;
    }
    // Footer tampilan
    printf("========================================\n");
    
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
boolean TampilkanDetailTiketSaya(TiketSaya T, User user_aktif, int indeks) {
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
            printf("%-8s: %d\n", "Gerbong", tiket.riwayat_nomor_gerbong);
            printf("%-8s: %s%d\n", "Kursi", tiket.riwayat_kode_kursi, tiket.riwayat_nomor_kursi);
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
        
        if (!TampilkanDetailTiketSaya(tiketSaya, user_aktif, indeks)) {
            printf("Gagal menampilkan detail tiket!\n");
        }
    }
    
    // Bersihkan memori
    DealokasiTiketSaya(&tiketSaya);
}