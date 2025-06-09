/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "implementasi_informasi_kereta.h"
#include "databases.h"
#include "linked.h"
#include "clear.h"

// Fungsi untuk membuat informasi kereta baru
InformasiKereta BuatInformasiKereta(char* id_kereta, char* nama_kereta, char* jenis_layanan, float harga_tiket, char* jumlah_gerbong) {
    InformasiKereta kereta_baru;
    
    // Salin data ke struktur kereta
    strcpy(kereta_baru.id_Kereta, id_kereta);
    strcpy(kereta_baru.nama_kereta, nama_kereta);
    strcpy(kereta_baru.jenis_layanan, jenis_layanan);
    kereta_baru.harga_tiket = harga_tiket;
    strcpy(kereta_baru.jumlah_gerbong, jumlah_gerbong);
    
    // Inisialisasi jadwal kosong
    CreateJadwalKereta(&kereta_baru.jadwal);
    
    return kereta_baru;
}

// Fungsi untuk menambahkan informasi kereta ke dalam list
boolean TambahInformasiKereta(ListKereta *L, InformasiKereta kereta_baru) {
    // Cek apakah ID kereta sudah terdaftar
    if (SearchKeretaById(*L, kereta_baru.id_Kereta) != NULL) {
        return FALSE; // ID kereta sudah terdaftar
    }
    
    // Buat node baru
    DataInformasiKereta *new_kereta = CreateDataKereta(kereta_baru);
    if (new_kereta == NULL) {
        return FALSE; // Gagal alokasi memori
    }
    
    // Tambahkan ke list
    InsertLastKereta(L, new_kereta);
    return TRUE;
}

// Fungsi untuk mencari informasi kereta berdasarkan ID
boolean CariInformasiKereta(ListKereta L, char* id_kereta, InformasiKereta* hasil) {
    DataInformasiKereta *kereta_node = SearchKeretaById(L, id_kereta);
    if (kereta_node == NULL) {
        return FALSE; // ID kereta tidak ditemukan
    }
    
    // Salin data kereta jika hasil tidak NULL
    if (hasil != NULL) {
        *hasil = kereta_node->kereta_info;
    }
    
    return TRUE;
}

// Fungsi untuk menampilkan informasi kereta
void TampilkanInformasiKereta(InformasiKereta kereta) {
    printf("===============================\n");
    printf("Informasi Kereta:\n");
    printf("ID: %s\n", kereta.id_Kereta);
    printf("Nama: %s\n", kereta.nama_kereta);
    printf("Jenis Layanan: %s\n", kereta.jenis_layanan);
    printf("Harga Tiket: Rp%.2f\n", kereta.harga_tiket);
    printf("Jumlah Gerbong: %s\n", kereta.jumlah_gerbong);
    
    // Tampilkan jadwal jika ada
    if (!isEmptyJadwal(kereta.jadwal)) {
        printf("\nJadwal Stasiun Transit:\n");
        PrintJadwal(kereta.jadwal);
    }
    
    printf("===============================\n");
}

// Fungsi untuk menampilkan semua informasi kereta
void TampilkanSemuaInformasiKereta(ListKereta L) {
    if (isEmptyKereta(L)) {
        printf("Daftar kereta kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Daftar Semua Kereta:\n");
    printf("===============================\n");
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 1;
    
    while (kereta_node != NULL) {
        printf("Kereta #%d\n", count++);
        printf("ID: %s\n", kereta_node->kereta_info.id_Kereta);
        printf("Nama: %s\n", kereta_node->kereta_info.nama_kereta);
        printf("Jenis Layanan: %s\n", kereta_node->kereta_info.jenis_layanan);
        printf("Harga Tiket: Rp%.2f\n", kereta_node->kereta_info.harga_tiket);
        printf("Jumlah Gerbong: %s\n", kereta_node->kereta_info.jumlah_gerbong);
        printf("-------------------------------\n");
        
        kereta_node = kereta_node->next;
    }
}

// Fungsi untuk memfilter kereta berdasarkan jenis layanan
void FilterKeretaBerdasarkanLayanan(ListKereta L, char* jenis_layanan) {
    if (isEmptyKereta(L)) {
        printf("Daftar kereta kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Kereta dengan Layanan %s:\n", jenis_layanan);
    printf("===============================\n");
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 1;
    boolean found = FALSE;
    
    while (kereta_node != NULL) {
        if (strcmp(kereta_node->kereta_info.jenis_layanan, jenis_layanan) == 0) {
            printf("Kereta #%d\n", count++);
            printf("ID: %s\n", kereta_node->kereta_info.id_Kereta);
            printf("Nama: %s\n", kereta_node->kereta_info.nama_kereta);
            printf("Harga Tiket: Rp%.2f\n", kereta_node->kereta_info.harga_tiket);
            printf("Jumlah Gerbong: %s\n", kereta_node->kereta_info.jumlah_gerbong);
            printf("-------------------------------\n");
            found = TRUE;
        }
        
        kereta_node = kereta_node->next;
    }
    
    if (!found) {
        printf("Tidak ada kereta dengan layanan %s.\n", jenis_layanan);
    }
}

// Fungsi untuk memfilter kereta berdasarkan rentang harga
void FilterKeretaBerdasarkanHarga(ListKereta L, float harga_min, float harga_max) {
    if (isEmptyKereta(L)) {
        printf("Daftar kereta kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Kereta dengan Harga Rp%.2f - Rp%.2f:\n", harga_min, harga_max);
    printf("===============================\n");
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 1;
    boolean found = FALSE;
    
    while (kereta_node != NULL) {
        if (kereta_node->kereta_info.harga_tiket >= harga_min && 
            kereta_node->kereta_info.harga_tiket <= harga_max) {
            printf("Kereta #%d\n", count++);
            printf("ID: %s\n", kereta_node->kereta_info.id_Kereta);
            printf("Nama: %s\n", kereta_node->kereta_info.nama_kereta);
            printf("Jenis Layanan: %s\n", kereta_node->kereta_info.jenis_layanan);
            printf("Harga Tiket: Rp%.2f\n", kereta_node->kereta_info.harga_tiket);
            printf("Jumlah Gerbong: %s\n", kereta_node->kereta_info.jumlah_gerbong);
            printf("-------------------------------\n");
            found = TRUE;
        }
        
        kereta_node = kereta_node->next;
    }
    
    if (!found) {
        printf("Tidak ada kereta dengan rentang harga tersebut.\n");
    }
}

// Fungsi untuk mengurutkan kereta berdasarkan harga (ascending)
ListKereta UrutkanKeretaBerdasarkanHarga(ListKereta L, boolean ascending) {
    if (isEmptyKereta(L) || NbElmtKereta(L) == 1) {
        return L; // List kosong atau hanya memiliki 1 elemen
    }
    
    // Implementasi algoritma bubble sort
    DataInformasiKereta *temp_current, *temp_next;
    InformasiKereta temp_kereta;
    int n = NbElmtKereta(L);
    boolean swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = FALSE;
        temp_current = L.First;
        
        for (int j = 0; j < n - i - 1; j++) {
            temp_next = temp_current->next;
            
            boolean should_swap;
            if (ascending) {
                should_swap = temp_current->kereta_info.harga_tiket > temp_next->kereta_info.harga_tiket;
            } else {
                should_swap = temp_current->kereta_info.harga_tiket < temp_next->kereta_info.harga_tiket;
            }
            
            if (should_swap) {
                // Swap data kereta
                temp_kereta = temp_current->kereta_info;
                temp_current->kereta_info = temp_next->kereta_info;
                temp_next->kereta_info = temp_kereta;
                swapped = TRUE;
            }
            
            temp_current = temp_current->next;
        }
        
        if (!swapped) {
            break; // Jika tidak ada swap, berarti sudah terurut
        }
    }
    
    return L;
}

// Fungsi untuk mengurutkan kereta berdasarkan nama (alphabetical)
ListKereta UrutkanKeretaBerdasarkanNama(ListKereta L) {
    if (isEmptyKereta(L) || NbElmtKereta(L) == 1) {
        return L; // List kosong atau hanya memiliki 1 elemen
    }
    
    // Implementasi algoritma bubble sort
    DataInformasiKereta *temp_current, *temp_next;
    InformasiKereta temp_kereta;
    int n = NbElmtKereta(L);
    boolean swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = FALSE;
        temp_current = L.First;
        
        for (int j = 0; j < n - i - 1; j++) {
            temp_next = temp_current->next;
            
            if (strcmp(temp_current->kereta_info.nama_kereta, temp_next->kereta_info.nama_kereta) > 0) {
                // Swap data kereta
                temp_kereta = temp_current->kereta_info;
                temp_current->kereta_info = temp_next->kereta_info;
                temp_next->kereta_info = temp_kereta;
                swapped = TRUE;
            }
            
            temp_current = temp_current->next;
        }
        
        if (!swapped) {
            break; // Jika tidak ada swap, berarti sudah terurut
        }
    }
    
    return L;
}

// Fungsi untuk validasi ID kereta
boolean ValidasiIDKereta(char* id_kereta) {
    // Cek panjang ID kereta (umumnya 3-8 karakter)
    int panjang = strlen(id_kereta);
    if (panjang < 3 || panjang > 8) {
        return FALSE;
    }
    
    // ID kereta biasanya diawali dengan huruf dan diikuti angka
    if (!(id_kereta[0] >= 'A' && id_kereta[0] <= 'Z')) {
        return FALSE;
    }
    
    // Cek karakter lainnya (hanya huruf dan angka)
    for (int i = 0; i < panjang; i++) {
        if (!((id_kereta[i] >= 'A' && id_kereta[i] <= 'Z') || 
              (id_kereta[i] >= '0' && id_kereta[i] <= '9'))) {
            return FALSE;
        }
    }
    
    return TRUE;
}

// Fungsi untuk validasi jenis layanan
boolean ValidasiJenisLayanan(char* jenis_layanan) {
    return (strcmp(jenis_layanan, EKONOMI) == 0 || 
            strcmp(jenis_layanan, BISNIS) == 0 || 
            strcmp(jenis_layanan, EKSEKUTIF) == 0 || 
            strcmp(jenis_layanan, LUXURY) == 0);
}

// Fungsi untuk menghitung jumlah kereta berdasarkan jenis layanan
int HitungJumlahKeretaBerdasarkanLayanan(ListKereta L, char* jenis_layanan) {
    if (isEmptyKereta(L)) {
        return 0;
    }
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 0;
    
    while (kereta_node != NULL) {
        if (strcmp(kereta_node->kereta_info.jenis_layanan, jenis_layanan) == 0) {
            count++;
        }
        kereta_node = kereta_node->next;
    }
    
    return count;
}

// Fungsi untuk menghasilkan ID kereta unik baru
void GenerateIDKereta(ListKereta L, char* id_baru) {
    // Format ID: K<nomor>
    int nomor = 1;
    char temp_id[10];
    
    do {
        sprintf(temp_id, "K%03d", nomor++);
    } while (SearchKeretaById(L, temp_id) != NULL && nomor < 1000);
    
    strcpy(id_baru, temp_id);
}

// Fungsi UI untuk menampilkan daftar kereta
void TampilkanDaftarKeretaInfo() {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|           DAFTAR KERETA TERSEDIA             |\n");
    printf("+----------------------------------------------+\n\n");
    
    // Baca data kereta dari database
    Record records[100];
    int jumlah_records = 0;
    
    for (int i = 0; i < 100; i++) {
        InisialisasiRecord(&records[i]);
    }
    
    DaftarKereta(records, &jumlah_records);
    
    if (jumlah_records == 0) {
        printf("Belum ada data kereta yang tersedia.\n\n");
    } else {
        printf("%-10s %-30s %-15s %-15s %-15s\n", "ID", "Nama Kereta", "Jenis Layanan", "Harga Tiket", "Jumlah Gerbong");
        printf("----------------------------------------------------------------------------------------\n");
        
        for (int i = 0; i < jumlah_records; i++) {
            char* kodeKereta = AmbilNilai(&records[i], "kodeKereta");
            char* namaKereta = AmbilNilai(&records[i], "namaKereta");
            char* jenisLayanan = AmbilNilai(&records[i], "jenisLayanan");
            char* hargaTiket = AmbilNilai(&records[i], "hargaTiket");
            char* jumlahGerbong = AmbilNilai(&records[i], "jumlahGerbong");
            
            if (kodeKereta && namaKereta && jenisLayanan && hargaTiket && jumlahGerbong) {
                printf("%-10s %-30s %-15s Rp %-12s %-15s\n", 
                       kodeKereta, namaKereta, jenisLayanan, hargaTiket, jumlahGerbong);
            }
        }
        printf("----------------------------------------------------------------------------------------\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getch();
}

// Fungsi UI untuk menambah kereta
void TambahKeretaInfo() {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               TAMBAH KERETA                  |\n");
    printf("+----------------------------------------------+\n\n");
    
    char id_kereta[20];
    char nama_kereta[50];
    char jenis_layanan[20];
    char harga_tiket[20];
    char jumlah_gerbong[5];
    
    printf("Masukkan informasi kereta baru:\n");
    printf("ID Kereta (format: KA-XXX): ");
    scanf("%s", id_kereta);
    
    // Validasi ID kereta
    if (!ValidasiIDKereta(id_kereta)) {
        printf("\nID Kereta tidak valid! Format yang benar adalah KA-XXX (X adalah angka).\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    // Cek apakah ID kereta sudah ada
    Record record;
    InisialisasiRecord(&record);
    if (BacaInformasiKereta(&record, id_kereta)) {
        printf("\nID Kereta sudah terdaftar! Silakan gunakan ID lain.\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    // Input nama kereta
    printf("Nama Kereta: ");
    getchar(); // Buang karakter newline
    scanf("%[^\n]", nama_kereta);
    
    // Input jenis layanan
    printf("Jenis Layanan (Ekonomi/Bisnis/Eksekutif/Luxury): ");
    getchar(); // Buang karakter newline
    scanf("%[^\n]", jenis_layanan);
    
    // Validasi jenis layanan
    if (!ValidasiJenisLayanan(jenis_layanan)) {
        printf("\nJenis Layanan tidak valid! Pilihan yang tersedia: Ekonomi, Bisnis, Eksekutif, Luxury.\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    // Input harga tiket
    printf("Harga Tiket: ");
    scanf("%s", harga_tiket);
    
    // Input jumlah gerbong
    printf("Jumlah Gerbong: ");
    scanf("%s", jumlah_gerbong);
    
    // Simpan data ke database
    InisialisasiRecord(&record);
    TambahField(&record, "kodeKereta", id_kereta);
    TambahField(&record, "namaKereta", nama_kereta);
    TambahField(&record, "jenisLayanan", jenis_layanan);
    TambahField(&record, "hargaTiket", harga_tiket);
    TambahField(&record, "jumlahGerbong", jumlah_gerbong);
    
    if (SimpanInformasiKereta(&record)) {
        printf("\nData kereta berhasil disimpan!\n");
    } else {
        printf("\nGagal menyimpan data kereta.\n");
    }
    
    printf("Tekan Enter untuk kembali...");
    getch();
}

// Fungsi UI untuk mengedit kereta
void EditKereta() {
    TampilkanDaftarKeretaInfo();
    char id[20];
    printf("\nMasukkan ID kereta yang ingin diedit: ");
    scanf("%s", id);
    
    // Cek apakah ID kereta ada
    Record record;
    InisialisasiRecord(&record);
    if (!BacaInformasiKereta(&record, id)) {
        printf("\nID Kereta tidak ditemukan!\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    // Tampilkan data kereta yang akan diedit
    printf("\nData Kereta yang akan diedit:\n");
    printf("Nama Kereta: %s\n", AmbilNilai(&record, "namaKereta"));
    printf("Jenis Layanan: %s\n", AmbilNilai(&record, "jenisLayanan"));
    printf("Harga Tiket: %s\n", AmbilNilai(&record, "hargaTiket"));
    printf("Jumlah Gerbong: %s\n\n", AmbilNilai(&record, "jumlahGerbong"));
    
    char nama_kereta[50];
    char jenis_layanan[20];
    char harga_tiket[20];
    char jumlah_gerbong[5];
    
    printf("Masukkan informasi kereta baru (kosongkan untuk tidak mengubah):\n");
    
    // Input nama kereta
    printf("Nama Kereta: ");
    getchar(); // Buang karakter newline
    fgets(nama_kereta, sizeof(nama_kereta), stdin);
    nama_kereta[strcspn(nama_kereta, "\n")] = 0; // Hapus newline dari fgets
    
    // Input jenis layanan
    printf("Jenis Layanan (Ekonomi/Bisnis/Eksekutif/Luxury): ");
    fgets(jenis_layanan, sizeof(jenis_layanan), stdin);
    jenis_layanan[strcspn(jenis_layanan, "\n")] = 0; // Hapus newline dari fgets
    
    // Validasi jenis layanan jika diisi
    if (strlen(jenis_layanan) > 0 && !ValidasiJenisLayanan(jenis_layanan)) {
        printf("\nJenis Layanan tidak valid! Pilihan yang tersedia: Ekonomi, Bisnis, Eksekutif, Luxury.\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    // Input harga tiket
    printf("Harga Tiket: ");
    fgets(harga_tiket, sizeof(harga_tiket), stdin);
    harga_tiket[strcspn(harga_tiket, "\n")] = 0; // Hapus newline dari fgets
    
    // Input jumlah gerbong
    printf("Jumlah Gerbong: ");
    fgets(jumlah_gerbong, sizeof(jumlah_gerbong), stdin);
    jumlah_gerbong[strcspn(jumlah_gerbong, "\n")] = 0; // Hapus newline dari fgets
    
    // Update data yang diisi
    if (strlen(nama_kereta) > 0) {
        UbahNilai(&record, "namaKereta", nama_kereta);
    }
    if (strlen(jenis_layanan) > 0) {
        UbahNilai(&record, "jenisLayanan", jenis_layanan);
    }
    if (strlen(harga_tiket) > 0) {
        UbahNilai(&record, "hargaTiket", harga_tiket);
    }
    if (strlen(jumlah_gerbong) > 0) {
        UbahNilai(&record, "jumlahGerbong", jumlah_gerbong);
    }
    
    // Simpan perubahan ke database
    if (UpdateInformasiKereta(&record)) {
        printf("\nData kereta berhasil diperbarui!\n");
    } else {
        printf("\nGagal memperbarui data kereta.\n");
    }
    
    printf("Tekan Enter untuk kembali...");
    getch();
}

// Fungsi UI untuk menghapus kereta
void HapusKeretaInfo() {
    TampilkanDaftarKeretaInfo();
    char id[20];
    printf("\nMasukkan ID kereta yang ingin dihapus: ");
    scanf("%s", id);
    
    // Cek apakah ID kereta ada
    Record record;
    InisialisasiRecord(&record);
    if (!BacaInformasiKereta(&record, id)) {
        printf("\nID Kereta tidak ditemukan!\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    
    // Konfirmasi penghapusan
    printf("\nData Kereta yang akan dihapus:\n");
    printf("Nama Kereta: %s\n", AmbilNilai(&record, "namaKereta"));
    printf("Jenis Layanan: %s\n", AmbilNilai(&record, "jenisLayanan"));
    printf("Harga Tiket: %s\n", AmbilNilai(&record, "hargaTiket"));
    printf("Jumlah Gerbong: %s\n\n", AmbilNilai(&record, "jumlahGerbong"));
    
    printf("Apakah Anda yakin ingin menghapus kereta ini? (Y/N): ");
    char konfirmasi;
    getchar(); // Buang karakter newline
    scanf("%c", &konfirmasi);
    
    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        // Hapus data dari database
        if (HapusInformasiKereta(id)) {
            printf("\nData kereta berhasil dihapus!\n");
        } else {
            printf("\nGagal menghapus data kereta.\n");
        }
    } else {
        printf("\nPenghapusan dibatalkan.\n");
    }
    
    printf("Tekan Enter untuk kembali...");
    getch();
} 