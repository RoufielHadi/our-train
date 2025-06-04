/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Membuat stack riwayat kosong
void CreateStackRiwayat(StackRiwayat *S) {
    S->top = NULL;
}

// Mengecek apakah stack riwayat kosong
boolean isEmptyStackRiwayat(StackRiwayat S) {
    return (S.top == NULL);
}

// Push elemen baru ke dalam stack riwayat
void PushRiwayat(StackRiwayat *S, RiwayatTiket tiket) {
    addressRiwayat P = (addressRiwayat)malloc(sizeof(DataRiwayat));
    if (P == NULL) {
        printf("Gagal mengalokasikan memori untuk elemen baru!\n");
        return;
    }
    
    P->info = tiket;
    P->next = S->top;
    S->top = P;
}

// Pop elemen dari stack riwayat
boolean PopRiwayat(StackRiwayat *S, RiwayatTiket *tiket) {
    if (isEmptyStackRiwayat(*S)) {
        printf("Stack kosong! Tidak dapat melakukan Pop.\n");
        return FALSE;
    }
    
    addressRiwayat P = S->top;
    *tiket = P->info;
    S->top = P->next;
    free(P);
    
    return TRUE;
}

// Mengembalikan elemen teratas dari stack riwayat tanpa menghapusnya
boolean TopRiwayat(StackRiwayat S, RiwayatTiket *tiket) {
    if (!isEmptyStackRiwayat(S)) {
        *tiket = S.top->info;
        return TRUE;
    } else {
        printf("Stack kosong! Tidak ada elemen di puncak.\n");
        return FALSE;
    }
}

// Menghitung jumlah elemen dalam stack riwayat
int NbElmtStackRiwayat(StackRiwayat S) {
    int count = 0;
    addressRiwayat P = S.top;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

// Menampilkan elemen dalam stack riwayat
void TampilStackRiwayat(StackRiwayat S) {
    if (isEmptyStackRiwayat(S)) {
        printf("Stack kosong!\n");
        return;
    }

    addressRiwayat P = S.top;
    printf("\n--- Riwayat Pembelian Tiket ---\n");
    int nomor = 1;
    
    while (P != NULL) {
        printf("Nomor: %d\n", nomor++);
        printf("Pengguna: %s\n", P->info.riwayat_user.nama);
        printf("Kereta: %s\n", P->info.riwayat_kereta.nama_kereta);
        printf("Gerbong: %d, Kursi: %d\n", P->info.riwayat_nomor_gerbong, P->info.riwayat_nomor_kursi);
        printf("Waktu Pemesanan: %02d:%02d:%02d %02d/%02d/%04d\n", 
               P->info.riwayat_waktu_pemesanan.jam,
               P->info.riwayat_waktu_pemesanan.menit,
               P->info.riwayat_waktu_pemesanan.detik,
               P->info.riwayat_waktu_pemesanan.hari,
               P->info.riwayat_waktu_pemesanan.bulan,
               P->info.riwayat_waktu_pemesanan.tahun);
        printf("---------------------------------\n");
        P = P->next;
    }
}

// Menghapus semua elemen dalam stack riwayat
void DeAlokasiStackRiwayat(StackRiwayat *S) {
    addressRiwayat P;
    while (!isEmptyStackRiwayat(*S)) {
        P = S->top;
        S->top = P->next;
        free(P);
    }
}

// Menyimpan stack riwayat ke dalam file
void SaveRiwayatToFile(StackRiwayat S, const char *filename) {
    FILE *file = fopen(filename, "w"); // Menggunakan mode write, bukan append
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }

    // Buat stack sementara untuk menyimpan elemen yang di-pop
    StackRiwayat tempStack;
    CreateStackRiwayat(&tempStack);
    RiwayatTiket tiket;
    
    // Salin semua elemen ke stack sementara agar urutan tetap sama
    while (!isEmptyStackRiwayat(S)) {
        addressRiwayat P = S.top;
        PushRiwayat(&tempStack, P->info);
        S.top = P->next;
    }
    
    // Tulis elemen-elemen ke file
    while (!isEmptyStackRiwayat(tempStack)) {
        if (PopRiwayat(&tempStack, &tiket)) {
            // Tulis data ke file dalam format yang sesuai
            fprintf(file, "%s,%s,%d,%d,%02d:%02d:%02d %02d/%02d/%04d\n",
                   tiket.riwayat_user.nama,
                   tiket.riwayat_kereta.nama_kereta,
                   tiket.riwayat_nomor_gerbong,
                   tiket.riwayat_nomor_kursi,
                   tiket.riwayat_waktu_pemesanan.jam,
                   tiket.riwayat_waktu_pemesanan.menit,
                   tiket.riwayat_waktu_pemesanan.detik,
                   tiket.riwayat_waktu_pemesanan.hari,
                   tiket.riwayat_waktu_pemesanan.bulan,
                   tiket.riwayat_waktu_pemesanan.tahun);
        }
    }

    fclose(file);
    printf("Riwayat berhasil disimpan ke file %s\n", filename);
}

// Membaca stack riwayat dari file
void LoadRiwayatFromFile(StackRiwayat *S, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Riwayat pembelian belum ada.\n");
        return;
    }

    // Hapus stack yang ada
    DeAlokasiStackRiwayat(S);

    // Buffer untuk membaca data
    char buffer[256];
    char nama_user[100], nama_kereta[100];
    int gerbong, kursi;
    int jam, menit, detik, hari, bulan, tahun;
    
    // Stack sementara untuk mempertahankan urutan yang benar
    StackRiwayat tempStack;
    CreateStackRiwayat(&tempStack);

    // Baca data dari file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Parse data dari buffer
        if (sscanf(buffer, "%[^,],%[^,],%d,%d,%d:%d:%d %d/%d/%d",
                   nama_user, nama_kereta, &gerbong, &kursi, 
                   &jam, &menit, &detik, &hari, &bulan, &tahun) == 10) {
            
            // Buat objek RiwayatTiket
            RiwayatTiket tiket;
            strcpy(tiket.riwayat_user.nama, nama_user);
            strcpy(tiket.riwayat_kereta.nama_kereta, nama_kereta);
            tiket.riwayat_nomor_gerbong = gerbong;
            tiket.riwayat_nomor_kursi = kursi;
            tiket.riwayat_waktu_pemesanan.jam = jam;
            tiket.riwayat_waktu_pemesanan.menit = menit;
            tiket.riwayat_waktu_pemesanan.detik = detik;
            tiket.riwayat_waktu_pemesanan.hari = hari;
            tiket.riwayat_waktu_pemesanan.bulan = bulan;
            tiket.riwayat_waktu_pemesanan.tahun = tahun;
            
            // Tambahkan ke stack sementara
            PushRiwayat(&tempStack, tiket);
        }
    }
    
    // Pindahkan dari stack sementara ke stack utama agar urutan tetap benar
    RiwayatTiket tiket;
    while (!isEmptyStackRiwayat(tempStack)) {
        if (PopRiwayat(&tempStack, &tiket)) {
            PushRiwayat(S, tiket);
        }
    }

    fclose(file);
    printf("Riwayat berhasil dimuat dari file %s\n", filename);
}
