/*
Author: Devi Maulani 
NIM: 241524007 
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dashboard_lihat_jadwal.h"
#include "implementasi_jadwal_kereta.h"

// Fungsi untuk dashboard lihat jadwal (navigasi interface)
void ShowLihatJadwalMenu() {
    char asal[50], tujuan[50];
    printf("=== LIHAT JADWAL KERETA ===\n");
    printf("Masukkan Stasiun Asal  : ");
    scanf(" %[^\n]", asal);
    printf("Masukkan Stasiun Tujuan: ");
    scanf(" %[^\n]", tujuan);

    // Buat list jadwal kosong
    ListJadwal daftarJadwal;
    CreateListJadwal(&daftarJadwal);
    
    // Muat data jadwal dari database
    Record records[100];
    int jumlah_records = 0;
    BacaSemuaJadwalKereta(records, &jumlah_records, 100);
    
    // Konversi records ke JadwalHarian dan tambahkan ke list
    int i;
    for (i = 0; i < jumlah_records; i++) {
        JadwalHarian jadwal = KonversiRecordKeJadwalKereta(records[i]);
        TambahJadwalKeList(&daftarJadwal, jadwal);
    }
    
    // Cari jadwal menggunakan fungsi dari implementasi_jadwal_kereta
    NodeJadwal* hasil = CariJadwalByRute(daftarJadwal, asal, tujuan);

    if (hasil == NULL) {
        printf("\nTidak ditemukan jadwal untuk rute %s ke %s.\n", asal, tujuan);
    } else {
        // Buat list baru untuk hasil pencarian
        ListJadwal hasilPencarian;
        CreateListJadwal(&hasilPencarian);
        
        // Salin hasil ke list baru
        NodeJadwal* current = hasil;
        while (current != NULL) {
            TambahJadwalKeList(&hasilPencarian, current->jadwal);
            current = current->next;
        }
        
        printf("\nJadwal ditemukan:\n");
        TampilkanSemuaJadwal(hasilPencarian);
        
        // Bersihkan list hasil pencarian
        NodeJadwal* temp = hasilPencarian.First;
        while (temp != NULL) {
            NodeJadwal* hapus = temp;
            temp = temp->next;
            free(hapus);
        }
    }
    
    // Bersihkan list daftar jadwal
    NodeJadwal* temp = daftarJadwal.First;
    while (temp != NULL) {
        NodeJadwal* hapus = temp;
        temp = temp->next;
        free(hapus);
    }
}
