/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_pembelian_tiket.h"
#include "clear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// External declarations for functions used but not defined in this file
extern ListKereta globalListKereta;
extern boolean isEmptyKereta(ListKereta L);
extern const char* GetJenisLayananById(ListKereta L, const char* id);
extern JenisKereta GetJenisKeretaById(const char* id);
extern InformasiKereta* GetInformasiKeretaById(ListKereta L, const char* id);
extern void InisialisasiListKeretaGlobal(void);
extern boolean MuatDataKeretaKeGlobal(void);
extern void MenuKursiKereta(const char* id_kereta, const char* tanggal, int* nomor_gerbong, char* kode_kursi);

// Forward declarations
boolean PilihTiket(ListHasilPencarian hasil, int nomor_tiket, HasilPencarian* tiket_dipilih);
void InisialisasiPembelianTiket(PembelianTiket* pembelian, HasilPencarian tiket_dipilih);
void TampilkanDetailTiket(PembelianTiket pembelian);

// Global variable to store logged-in user email
char g_logged_in_user_email[100] = "";

// Set logged in user email
void SetLoggedInUser(const char* email) {
    if (email != NULL) {
        strncpy(g_logged_in_user_email, email, sizeof(g_logged_in_user_email) - 1);
        g_logged_in_user_email[sizeof(g_logged_in_user_email) - 1] = '\0';
    }
}

// Get logged in user email
const char* GetLoggedInUser() {
    return g_logged_in_user_email;
}

// Inisialisasi list hasil pencarian
void InisialisasiListHasilPencarian(ListHasilPencarian* list) {
    list->head = NULL;
    list->count = 0;
}

// Menambahkan hasil pencarian ke dalam list
boolean TambahHasilPencarian(ListHasilPencarian* list, HasilPencarian tiket) {
    // Alokasi memori untuk node baru
    NodeHasilPencarian* newNode = (NodeHasilPencarian*)malloc(sizeof(NodeHasilPencarian));
    if (newNode == NULL) {
        return FALSE; // Alokasi gagal
    }
    
    // Salin data tiket ke node baru
    newNode->tiket = tiket;
    newNode->next = NULL;
    
    // Jika list kosong, jadikan node baru sebagai head
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // Cari node terakhir dan tambahkan node baru di akhir
        // Ini mengikuti pola InsertLast dari linked.h
        NodeHasilPencarian* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    list->count++;
    return TRUE;
}

// Menghapus seluruh list hasil pencarian
void HapusListHasilPencarian(ListHasilPencarian* list) {
    NodeHasilPencarian* current = list->head;
    NodeHasilPencarian* next;
    
    // Ini mengikuti pola DeleteList dari linked.h
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->count = 0;
}

// Fungsi bantuan untuk membandingkan dua rute (untuk pengurutan)
int BandingkanRute(const void* a, const void* b) {
    RuteKereta* ruteA = (RuteKereta*)a;
    RuteKereta* ruteB = (RuteKereta*)b;
    
    int cmpAsal = strcmp(ruteA->stasiun_asal, ruteB->stasiun_asal);
    if (cmpAsal != 0) {
        return cmpAsal;
    }
    
    return strcmp(ruteA->stasiun_tujuan, ruteB->stasiun_tujuan);
}

// Mendapatkan daftar rute unik dan terurut
void DapatkanRuteUnik(RuteKereta** daftar_rute, int* jumlah_rute) {
    // Baca semua jadwal kereta dari file
    FILE* file = fopen(DB_JADWAL_KERETA, "r");
    if (file == NULL) {
        *jumlah_rute = 0;
        *daftar_rute = NULL;
        return;
    }
    
    // Baca file baris per baris
    char line[1024];
    RuteKereta* temp_rute = NULL;
    int max_rute = 100;  // Alokasi awal
    int count = 0;
    
    // Alokasi array untuk menyimpan rute sementara
    temp_rute = (RuteKereta*)malloc(max_rute * sizeof(RuteKereta));
    if (temp_rute == NULL) {
        fclose(file);
        *jumlah_rute = 0;
        *daftar_rute = NULL;
        return;
    }
    
    while (fgets(line, sizeof(line), file)) {
        // Format: KodeKereta|Stasiun1,Stasiun2,...|waktu1,waktu2,...
        char* token = strtok(line, "|");
        if (token == NULL) continue;
        
        // Token kedua berisi daftar stasiun
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        
        // Pisahkan stasiun
        char stasiun_list[1024];
        strncpy(stasiun_list, token, sizeof(stasiun_list) - 1);
        stasiun_list[sizeof(stasiun_list) - 1] = '\0';
        
        char* stasiun_token = strtok(stasiun_list, ",");
        char stasiun_pertama[MAX_NAMA_SEGMEN] = "";
        
        // Simpan stasiun pertama
        if (stasiun_token != NULL) {
            strncpy(stasiun_pertama, stasiun_token, MAX_NAMA_SEGMEN - 1);
            stasiun_pertama[MAX_NAMA_SEGMEN - 1] = '\0';
        }
        
        // Cari semua stasiun selanjutnya dan buat rute untuk setiap kombinasi stasiun
        while (stasiun_token != NULL) {
            char stasiun_berikutnya[MAX_NAMA_SEGMEN] = "";
            stasiun_token = strtok(NULL, ",");
            
            if (stasiun_token != NULL) {
                strncpy(stasiun_berikutnya, stasiun_token, MAX_NAMA_SEGMEN - 1);
                stasiun_berikutnya[MAX_NAMA_SEGMEN - 1] = '\0';
                
                // Tambahkan rute baru ke array
                if (count >= max_rute) {
                    // Realokasi jika perlu
                    max_rute *= 2;
                    RuteKereta* temp = (RuteKereta*)realloc(temp_rute, max_rute * sizeof(RuteKereta));
                    if (temp == NULL) {
                        free(temp_rute);
                        fclose(file);
                        *jumlah_rute = 0;
                        *daftar_rute = NULL;
                        return;
                    }
                    temp_rute = temp;
                }
                
                // Tambahkan rute stasiun_pertama ke stasiun_berikutnya
                strcpy(temp_rute[count].stasiun_asal, stasiun_pertama);
                strcpy(temp_rute[count].stasiun_tujuan, stasiun_berikutnya);
                count++;
                
                // Update stasiun pertama untuk iterasi berikutnya
                strcpy(stasiun_pertama, stasiun_berikutnya);
            }
        }
    }
    
    fclose(file);
    
    // Hapus rute duplikat
    if (count > 0) {
        // Urutkan rute terlebih dahulu
        qsort(temp_rute, count, sizeof(RuteKereta), BandingkanRute);
        
        // Alokasi memori untuk array hasil (tanpa duplikat)
        *daftar_rute = (RuteKereta*)malloc(count * sizeof(RuteKereta));
        if (*daftar_rute == NULL) {
            free(temp_rute);
            *jumlah_rute = 0;
            return;
        }
        
        // Salin rute pertama
        (*daftar_rute)[0] = temp_rute[0];
        int unique_count = 1;
        
        // Salin hanya rute yang unik
        int i;
        for (i = 1; i < count; i++) {
            if (strcmp(temp_rute[i].stasiun_asal, temp_rute[i-1].stasiun_asal) != 0 ||
                strcmp(temp_rute[i].stasiun_tujuan, temp_rute[i-1].stasiun_tujuan) != 0) {
                (*daftar_rute)[unique_count] = temp_rute[i];
                unique_count++;
            }
        }
        
        // Update jumlah rute unik
        *jumlah_rute = unique_count;
        
        // Realokasi array hasil sesuai jumlah rute unik
        RuteKereta* temp = (RuteKereta*)realloc(*daftar_rute, unique_count * sizeof(RuteKereta));
        if (temp != NULL) {
            *daftar_rute = temp;
        }
    } else {
        *daftar_rute = NULL;
        *jumlah_rute = 0;
    }
    
    free(temp_rute);
}

// Menampilkan daftar rute kereta
void TampilkanDaftarRute(RuteKereta* daftar_rute, int jumlah_rute) {
	int i;
    clearScreen();
    printf("+-----------------------------------------+\n");
    printf("|           DAFTAR RUTE KERETA           |\n");
    printf("+-----------------------------------------+\n");
    printf("| %-20s | %-20s |\n", "Stasiun Asal", "Stasiun Tujuan");
    printf("+-----------------------------------------+\n");
    
    for (i = 0; i < jumlah_rute; i++) {
        printf("| %-20s | %-20s |\n", 
               daftar_rute[i].stasiun_asal,
               daftar_rute[i].stasiun_tujuan);
    }
    
    printf("+-----------------------------------------+\n");
}

// Fungsi utilitas untuk mengonversi string ke lowercase
void StringToLower(char* str, char* result) {
    int i = 0;
    while (str[i]) {
        result[i] = tolower((unsigned char)str[i]);
        i++;
    }
    result[i] = '\0';
}

// Mencari tiket berdasarkan kriteria
boolean CariTiket(ListHasilPencarian* hasil, const char* stasiun_asal, 
                 const char* stasiun_tujuan, const char* tanggal, const char* jenis_layanan) {
    // Inisialisasi variabel untuk case insensitive search
    char asal_lower[MAX_NAMA_SEGMEN];
    char tujuan_lower[MAX_NAMA_SEGMEN];
    char jenis_lower[20];
    
    StringToLower((char*)stasiun_asal, asal_lower);
    StringToLower((char*)stasiun_tujuan, tujuan_lower);
    StringToLower((char*)jenis_layanan, jenis_lower);
    
    // Pastikan list hasil pencarian kosong
    HapusListHasilPencarian(hasil);
    
    // Buat list jadwal sementara untuk pencarian
    JadwalKereta jadwal_kereta;
    CreateJadwalKereta(&jadwal_kereta);
    
    // Load semua jadwal kereta
    FILE* file = fopen(DB_JADWAL_KERETA, "r");
    if (file == NULL) {
        return FALSE;
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Format: KodeKereta|Stasiun1,Stasiun2,...|waktu1,waktu2,...
        char kode_kereta[10] = "";
        char stasiun_list[1024] = "";
        char waktu_list[1024] = "";
        
        // Parsing baris
        sscanf(line, "%[^|]|%[^|]|%[^\n]", kode_kereta, stasiun_list, waktu_list);
        
        // Buat jadwal kereta
        JadwalHarian jadwal = BuatJadwalKereta(kode_kereta, (char*)tanggal);
        
        // Parse daftar stasiun dan waktu
        char* stasiun_token = strtok(stasiun_list, ",");
        char* waktu_token = strtok(waktu_list, ",");
        
        boolean asal_ditemukan = FALSE;
        boolean tujuan_ditemukan = FALSE;
        int index_asal = -1;
        int index_tujuan = -1;
        int index_current = 0;
        
        // Untuk stasiun dan waktu transit
        while (stasiun_token != NULL && waktu_token != NULL) {
            // Trim leading/trailing whitespace
            char* token_ptr = stasiun_token;
            while (*token_ptr && isspace((unsigned char)*token_ptr)) token_ptr++;
            char trimmed[MAX_NAMA_SEGMEN];
            strncpy(trimmed, token_ptr, MAX_NAMA_SEGMEN - 1);
            trimmed[MAX_NAMA_SEGMEN - 1] = '\0';
            char* end_ptr = trimmed + strlen(trimmed) - 1;
            while (end_ptr > trimmed && isspace((unsigned char)*end_ptr)) { *end_ptr = '\0'; end_ptr--; }
            char stasiun_current_lower[MAX_NAMA_SEGMEN];
            StringToLower(trimmed, stasiun_current_lower);
            
            // Cek apakah stasiun ini adalah asal atau tujuan
            if (strcmp(stasiun_current_lower, asal_lower) == 0) {
                asal_ditemukan = TRUE;
                index_asal = index_current;
            }
            
            if (strcmp(stasiun_current_lower, tujuan_lower) == 0) {
                tujuan_ditemukan = TRUE;
                index_tujuan = index_current;
            }
            
            // Parse waktu
            int jam, menit;
            sscanf(waktu_token, "%d:%d", &jam, &menit);
            Waktu waktu = {0, menit, jam, 0, 0, 0};
            
            // Tambahkan stasiun ke jadwal
            TambahStasiunKeJadwal(&jadwal, stasiun_token, waktu);
            
            // Lanjut ke token berikutnya
            stasiun_token = strtok(NULL, ",");
            waktu_token = strtok(NULL, ",");
            index_current++;
        }
        
        // Jika asal dan tujuan ditemukan dan urutan benar (asal->tujuan)
        if (asal_ditemukan && tujuan_ditemukan && index_asal < index_tujuan) {
            // Cek jenis layanan
            const char* jenis = GetJenisLayananById(globalListKereta, kode_kereta);
            char jenis_current_lower[20];
            
            if (jenis != NULL) {
                StringToLower((char*)jenis, jenis_current_lower);
                
                // Jika jenis layanan cocok atau kriteria jenis kosong
                if (strlen(jenis_lower) == 0 || strcmp(jenis_current_lower, jenis_lower) == 0) {
                    // Cek ketersediaan kursi
                    KursiKereta kursi_kereta;
                    boolean kursi_tersedia = BacaKeretaDariDatabase(&kursi_kereta, kode_kereta, tanggal);
                    
                    if (!kursi_tersedia) {
                        printf("Debug: Kursi tidak tersedia untuk kereta %s pada tanggal %s\n", kode_kereta, tanggal);
                    } else {
                        printf("Debug: Kursi tersedia untuk kereta %s pada tanggal %s\n", kode_kereta, tanggal);
                    }
                    
                    // Hitung jumlah kursi tersedia
                    int g;
                    int jumlah_kursi_tersedia = 0;
                    if (kursi_tersedia) {
                        for (g = 0; g < kursi_kereta.jumlah_gerbong; g++) {
                            JenisKereta jenis_kereta = GetJenisKeretaById(kode_kereta);
                            KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis_kereta);
                            
                            int b,k,s;
                            for (b = 0; b < konfig.baris; b++) {
                                for (k = 0; k < konfig.kolom; k++) {
                                    boolean kursi_kosong = TRUE;
                                    for (s = index_asal; s < index_tujuan && kursi_kosong; s++) {
                                        if (kursi_kereta.data_kursi[g].status_kursi[k][b][s]) {
                                            kursi_kosong = FALSE;
                                        }
                                    }
                                    
                                    if (kursi_kosong) {
                                        jumlah_kursi_tersedia++;
                                    }
                                }
                            }
                        }
                    }
                    
                    printf("Debug: Jumlah kursi tersedia: %d\n", jumlah_kursi_tersedia);
                    
                    // Tambahkan ke hasil pencarian
                    HasilPencarian hasil_tiket;
                    strcpy(hasil_tiket.id_kereta, kode_kereta);
                    
                    // Ambil nama kereta
                    InformasiKereta* info = GetInformasiKeretaById(globalListKereta, kode_kereta);
                    if (info != NULL) {
                        strcpy(hasil_tiket.nama_kereta, info->nama_kereta);
                        strcpy(hasil_tiket.jenis_layanan, info->jenis_layanan);
                        hasil_tiket.harga_tiket = info->harga_tiket;
                    } else {
                        strcpy(hasil_tiket.nama_kereta, "Unknown");
                        strcpy(hasil_tiket.jenis_layanan, "Unknown");
                        hasil_tiket.harga_tiket = 0.0;
                    }
                    
                    // Stasiun asal dan tujuan
                    strcpy(hasil_tiket.stasiun_asal, stasiun_asal);
                    strcpy(hasil_tiket.stasiun_tujuan, stasiun_tujuan);
                    
                    // Tanggal
                    strcpy(hasil_tiket.tanggal, tanggal);
                    
                    // simpan juga format database jika diperlukan
                    strcpy(hasil_tiket.tanggal, tanggal);
                    
                    // Waktu keberangkatan dan tiba
                    Waktu waktu_berangkat, waktu_tiba;
                    CariWaktuKeberangkatan(jadwal, (char*)stasiun_asal, &waktu_berangkat);
                    CariWaktuKeberangkatan(jadwal, (char*)stasiun_tujuan, &waktu_tiba);
                    
                    sprintf(hasil_tiket.waktu_berangkat, "%02d:%02d", waktu_berangkat.jam, waktu_berangkat.menit);
                    sprintf(hasil_tiket.waktu_tiba, "%02d:%02d", waktu_tiba.jam, waktu_tiba.menit);
                    
                    // Jumlah kursi tersedia
                    hasil_tiket.kursi_tersedia = jumlah_kursi_tersedia;
                    
                    // Tambahkan ke list hasil
                    TambahHasilPencarian(hasil, hasil_tiket);
                }
            }
        }
    }
    
    fclose(file);
    
    return hasil->count > 0;
}

// Menampilkan hasil pencarian tiket
void TampilkanHasilPencarian(ListHasilPencarian hasil) {
    if (hasil.count == 0) {
        printf("\nTidak ditemukan tiket yang sesuai dengan kriteria pencarian.\n");
        return;
    }
    
    clearScreen();
    printf("+---------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                            HASIL PENCARIAN TIKET                                              |\n");
    printf("+---------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-4s | %-15s | %-15s | %-15s | %-10s | %-5s | %-5s | %-10s | %-8s | %-4s |\n", 
           "No", "ID Kereta", "Nama Kereta", "Rute", "Tanggal", "Brkt", "Tiba", "Jenis", "Harga", "Kursi");
    printf("+---------------------------------------------------------------------------------------------------------------+\n");
    
    NodeHasilPencarian* current = hasil.head;
    int no = 1;
    
    while (current != NULL) {
        char rute[32];
        sprintf(rute, "%s-%s", current->tiket.stasiun_asal, current->tiket.stasiun_tujuan);
        
        printf("| %-4d | %-15s | %-15s | %-15s | %-10s | %-5s | %-5s | %-10s | %8.2f | %-4d |\n", 
               no++, 
               current->tiket.id_kereta,
               current->tiket.nama_kereta,
               rute,
               current->tiket.tanggal,
               current->tiket.waktu_berangkat,
               current->tiket.waktu_tiba,
               current->tiket.jenis_layanan,
               current->tiket.harga_tiket,
               current->tiket.kursi_tersedia);
        
        current = current->next;
    }
    
    printf("+---------------------------------------------------------------------------------------------------------------+\n");
    printf("Ditemukan %d tiket yang sesuai dengan kriteria pencarian.\n", hasil.count);
}

// Fungsi pencarian tiket utama (entry point)
void MenuPencarianTiket() {
    ListHasilPencarian hasil;
    RuteKereta* daftar_rute = NULL;
    int jumlah_rute = 0;
    HasilPencarian tiket_dipilih;
    PembelianTiket pembelian;
    char stasiun_asal[MAX_NAMA_SEGMEN];
    char stasiun_tujuan[MAX_NAMA_SEGMEN];
    char tanggal[11];
    char jenis_layanan[20];
    
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|              PENCARIAN TIKET                 |\n");
    printf("+----------------------------------------------+\n");
    
    // Muat data informasi kereta jika belum dimuat
    if (isEmptyKereta(globalListKereta)) {
        InisialisasiListKeretaGlobal();
        MuatDataKeretaKeGlobal();
    }
    
    // Inisialisasi list hasil pencarian
    InisialisasiListHasilPencarian(&hasil);
    
    // Dapatkan daftar rute yang tersedia
    DapatkanRuteUnik(&daftar_rute, &jumlah_rute);
    
    if (jumlah_rute == 0) {
        printf("Belum ada rute kereta yang tersedia.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return;
    }
    
    // Tampilkan daftar rute
    TampilkanDaftarRute(daftar_rute, jumlah_rute);
    
    // Dapatkan input rute dari pengguna
    printf("\nMasukkan stasiun asal: ");
    fgets(stasiun_asal, sizeof(stasiun_asal), stdin);
    stasiun_asal[strcspn(stasiun_asal, "\n")] = '\0';
    // Trim whitespace from both ends
    char *start = stasiun_asal;
    while (*start && isspace((unsigned char)*start)) start++;
    memmove(stasiun_asal, start, strlen(start) + 1);
    char *end = stasiun_asal + strlen(stasiun_asal) - 1;
    while (end >= stasiun_asal && isspace((unsigned char)*end)) { *end = '\0'; end--; }

    printf("Masukkan stasiun tujuan: ");
    fgets(stasiun_tujuan, sizeof(stasiun_tujuan), stdin);
    stasiun_tujuan[strcspn(stasiun_tujuan, "\n")] = '\0';
    // Trim whitespace from both ends
    start = stasiun_tujuan;
    while (*start && isspace((unsigned char)*start)) start++;
    memmove(stasiun_tujuan, start, strlen(start) + 1);
    end = stasiun_tujuan + strlen(stasiun_tujuan) - 1;
    while (end >= stasiun_tujuan && isspace((unsigned char)*end)) { *end = '\0'; end--; }

    // Dapatkan input tanggal
    printf("Masukkan tanggal keberangkatan (DD-MM-YYYY): ");
    fgets(tanggal, sizeof(tanggal), stdin);
    tanggal[strcspn(tanggal, "\n")] = '\0';

    // Dapatkan input jenis layanan
    printf("Masukkan jenis layanan (Ekonomi/Bisnis/Eksekutif): ");
    fgets(jenis_layanan, sizeof(jenis_layanan), stdin);
    jenis_layanan[strcspn(jenis_layanan, "\n")] = '\0';
    // Trim whitespace from service type
    start = jenis_layanan;
    while (*start && isspace((unsigned char)*start)) start++;
    memmove(jenis_layanan, start, strlen(start) + 1);
    end = jenis_layanan + strlen(jenis_layanan) - 1;
    while (end >= jenis_layanan && isspace((unsigned char)*end)) { *end = '\0'; end--; }
    
    // Lakukan pencarian
    if (CariTiket(&hasil, stasiun_asal, stasiun_tujuan, tanggal, jenis_layanan)) {
        clearScreen();
        TampilkanHasilPencarian(hasil);

        // Proses pemilihan tiket
        int nomor_pilihan = 0;
        printf("\nMasukkan nomor tiket yang ingin dipilih (0 untuk kembali): ");
        scanf("%d", &nomor_pilihan);
        while(getchar() != '\n'); // Membersihkan buffer

        if (nomor_pilihan == 0) {
            printf("Pemilihan tiket dibatalkan.\n");
            HapusListHasilPencarian(&hasil);
            free(daftar_rute);
            printf("Tekan Enter untuk kembali...");
            getchar();
            return;
        }

        // Proses pilihan tiket
        if (PilihTiket(hasil, nomor_pilihan, &tiket_dipilih)) {
            // Inisialisasi struktur pembelian
            InisialisasiPembelianTiket(&pembelian, tiket_dipilih);
            
            // Generate kode pembelian unik
            GenerateKodePembelian(pembelian.kode_pembelian);
            
            clearScreen();
            TampilkanDetailTiket(pembelian);
            
            printf("\nTiket berhasil dipilih!\n");
            printf("Kode Pembelian: %s\n", pembelian.kode_pembelian);
            printf("Lanjutkan ke pemilihan kursi? (y/n): ");
            char pilihan;
            scanf(" %c", &pilihan);
            while(getchar() != '\n'); // Membersihkan buffer
            
            if (pilihan == 'y' || pilihan == 'Y') {
                // Di sini akan lanjut ke tahap berikutnya (pemilihan kursi)
                MenuPemilihanKursi(&pembelian);
            }
        } else {
            printf("\nGagal memilih tiket. Silakan coba lagi.\n");
        }
    } else {
        printf("\nTidak ada tiket yang sesuai dengan kriteria pencarian.\n");
    }
    
    // Pembersihan memori
    HapusListHasilPencarian(&hasil);
    free(daftar_rute);
    
    printf("Tekan Enter untuk kembali...");
    getchar();
}

// Fungsi untuk membuat kode pembelian unik
void GenerateKodePembelian(char* kode_pembelian) {
    // Format kode: TIX-YYYYMMDD-XXX
    // YYYYMMDD: Tahun, bulan, tanggal saat ini
    // XXX: 3 digit angka acak

    // Dapatkan waktu saat ini
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    
    // Generate 3 digit angka acak
    int random_num = rand() % 1000;
    
    // Format kode pembelian
    sprintf(kode_pembelian, "TIX-%04d%02d%02d-%03d", 
            tm_now->tm_year + 1900, 
            tm_now->tm_mon + 1, 
            tm_now->tm_mday,
            random_num);
}

// Simpan data pembelian ke dalam file riwayat pembelian
boolean SimpanRiwayatPembelianTiket(PembelianTiket pembelian) {
    // Validasi status pembelian
    if (pembelian.status != SELESAI) {
        printf("Error: Pembelian belum selesai\n");
        return FALSE;
    }
    
    // Konversi data pembelian ke Record
    Record record;
    InisialisasiRecord(&record);
    
    // Tambahkan informasi pembelian
    TambahField(&record, "kode_pembelian", pembelian.kode_pembelian);
    TambahField(&record, "id_kereta", pembelian.tiket_dipilih.id_kereta);
    TambahField(&record, "nama_kereta", pembelian.tiket_dipilih.nama_kereta);
    TambahField(&record, "stasiun_asal", pembelian.tiket_dipilih.stasiun_asal);
    TambahField(&record, "stasiun_tujuan", pembelian.tiket_dipilih.stasiun_tujuan);
    TambahField(&record, "tanggal", pembelian.tiket_dipilih.tanggal);
    TambahField(&record, "waktu_berangkat", pembelian.tiket_dipilih.waktu_berangkat);
    TambahField(&record, "waktu_tiba", pembelian.tiket_dipilih.waktu_tiba);
    TambahField(&record, "jenis_layanan", pembelian.tiket_dipilih.jenis_layanan);
    
    // Konversi harga tiket ke string
    char harga_str[20];
    sprintf(harga_str, "%.2f", pembelian.tiket_dipilih.harga_tiket);
    TambahField(&record, "harga_tiket", harga_str);
    
    // Tambahkan informasi kursi
    char nomor_gerbong_str[5];
    sprintf(nomor_gerbong_str, "%d", pembelian.nomor_gerbong);
    TambahField(&record, "nomor_gerbong", nomor_gerbong_str);
    TambahField(&record, "kode_kursi", pembelian.kode_kursi);
    
    // Tambahkan informasi penumpang
    TambahField(&record, "nama_penumpang", pembelian.nama_penumpang);
    TambahField(&record, "nomor_identitas", pembelian.nomor_identitas);
    
    // Konversi total bayar ke string
    char total_bayar_str[20];
    sprintf(total_bayar_str, "%.2f", pembelian.total_bayar);
    TambahField(&record, "total_bayar", total_bayar_str);
    
    // Tambahkan waktu pembelian
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char waktu_pembelian[20];
    sprintf(waktu_pembelian, "%04d-%02d-%02d %02d:%02d:%02d", 
            tm_now->tm_year + 1900, 
            tm_now->tm_mon + 1, 
            tm_now->tm_mday,
            tm_now->tm_hour,
            tm_now->tm_min,
            tm_now->tm_sec);
    TambahField(&record, "waktu_pembelian", waktu_pembelian);
    
    // Simpan record ke file
    return SimpanRecord(DB_RIWAYAT_PEMBELIAN, &record, "kode_pembelian");
}

// Fungsi untuk pemilihan kursi pada proses pembelian tiket
void MenuPemilihanKursi(PembelianTiket* pembelian) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|              PEMILIHAN KURSI                |\n");
    printf("+----------------------------------------------+\n");
    
    // Tampilkan informasi tiket yang dipilih
    printf("Kereta: %s (%s)\n", 
           pembelian->tiket_dipilih.id_kereta,
           pembelian->tiket_dipilih.nama_kereta);
    printf("Rute  : %s - %s\n", 
           pembelian->tiket_dipilih.stasiun_asal,
           pembelian->tiket_dipilih.stasiun_tujuan);
    printf("Tanggal: %s\n\n", pembelian->tiket_dipilih.tanggal);
    
    printf("Tekan Enter untuk melanjutkan ke pemilihan kursi...");
    getchar();
    
    // Konversi format tanggal dari DD-MM-YYYY menjadi YYYY-MM-DD untuk database
    char tanggal_db[11];
    if (strlen(pembelian->tiket_dipilih.tanggal) == 10 && 
        pembelian->tiket_dipilih.tanggal[2] == '-' && 
        pembelian->tiket_dipilih.tanggal[5] == '-') {
        // Format tanggal input: DD-MM-YYYY
        sprintf(tanggal_db, "%c%c%c%c-%c%c-%c%c", 
                pembelian->tiket_dipilih.tanggal[6], pembelian->tiket_dipilih.tanggal[7], 
                pembelian->tiket_dipilih.tanggal[8], pembelian->tiket_dipilih.tanggal[9], // YYYY
                pembelian->tiket_dipilih.tanggal[3], pembelian->tiket_dipilih.tanggal[4], // MM
                pembelian->tiket_dipilih.tanggal[0], pembelian->tiket_dipilih.tanggal[1]); // DD
        tanggal_db[10] = '\0';
    } else {
        // Jika format tidak sesuai, gunakan tanggal asli
        strcpy(tanggal_db, pembelian->tiket_dipilih.tanggal);
    }
    
    printf("Debug: Menggunakan tanggal database: %s\n", tanggal_db);
    
    // Panggil MenuKursiKereta dengan parameter output dan tanggal yang sudah dikonversi
    MenuKursiKereta(pembelian->tiket_dipilih.id_kereta, 
                   tanggal_db,
                   &pembelian->nomor_gerbong,
                   pembelian->kode_kursi);
    
    // Update status pembelian
    pembelian->status = PEMILIHAN_KURSI;
    
    // Konfirmasi kursi yang dipilih
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|          KURSI BERHASIL DIPILIH             |\n");
    printf("+----------------------------------------------+\n");
    printf("Anda telah memilih kursi %s di gerbong %d\n\n", 
           pembelian->kode_kursi, pembelian->nomor_gerbong);
    
    // Langsung lanjut ke menu data penumpang
    printf("Lanjut ke pengisian data penumpang? (y/n): ");
    char pilihan;
    scanf(" %c", &pilihan);
    while(getchar() != '\n'); // Membersihkan buffer
    
    if (pilihan == 'y' || pilihan == 'Y') {
        // Lanjut ke pengisian data penumpang
        MenuDataPenumpang(pembelian);
    }
}

// Implementasi fungsi MenuDataPenumpang
void MenuDataPenumpang(PembelianTiket* pembelian) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|          PENGISIAN DATA PENUMPANG           |\n");
    printf("+----------------------------------------------+\n");
    
    // Tampilkan informasi tiket yang dipilih
    printf("Kereta: %s (%s)\n", 
           pembelian->tiket_dipilih.id_kereta,
           pembelian->tiket_dipilih.nama_kereta);
    printf("Rute  : %s - %s\n", 
           pembelian->tiket_dipilih.stasiun_asal,
           pembelian->tiket_dipilih.stasiun_tujuan);
    printf("Tanggal: %s\n", pembelian->tiket_dipilih.tanggal);
    printf("Kursi : %s (Gerbong %d)\n\n", 
           pembelian->kode_kursi, 
           pembelian->nomor_gerbong);
    
    // Cek apakah user ingin menggunakan data akun yang sedang login
    printf("Apakah pemesan adalah penumpang? (y/n): ");
    char pilihan;
    scanf(" %c", &pilihan);
    while(getchar() != '\n'); // Membersihkan buffer
    
    if (pilihan == 'y' || pilihan == 'Y') {
        // Check if we have a logged in user
        if (strlen(g_logged_in_user_email) > 0) {
            // Use the logged in user's email
            printf("\nMenggunakan akun dengan email: %s\n", g_logged_in_user_email);
            
            // Cari akun berdasarkan email
            User user_aktif;
            ListUser L;
            CreateListUser(&L);
            
            // Dalam sistem nyata, akan ada fungsi untuk mendapatkan data akun aktif
            // Untuk simulasi, kita baca dari database
            Record record;
            InisialisasiRecord(&record);
            if (BacaAkunUser(&record, g_logged_in_user_email)) {
                // Konversi record ke User
                strcpy(user_aktif.email, g_logged_in_user_email);
                strcpy(user_aktif.nama, AmbilNilai(&record, "nama"));
                strcpy(user_aktif.alamat, AmbilNilai(&record, "alamat"));
                strcpy(user_aktif.nomor_telepon, AmbilNilai(&record, "nomor_telepon"));
                
                // Isi data penumpang dari akun
                IsiDataPenumpangDariAkun(pembelian, user_aktif);
                printf("\nData penumpang berhasil diisi dari akun.\n");
                
                // Simpan email untuk pembayaran nanti
                strcpy(pembelian->email_penumpang, g_logged_in_user_email);
            } else {
                printf("\nAkun dengan email %s tidak ditemukan.\n", g_logged_in_user_email);
                printf("Silakan isi data penumpang secara manual.\n\n");
                // Lanjut ke pengisian manual
                pilihan = 'n';
            }
        } else {
            // Ambil data dari akun yang sedang login
            // Dalam sistem nyata, akan ada variabel global user_aktif
            // Untuk simulasi, kita akan meminta email untuk mencari akun
            printf("\nMasukkan email akun Anda: ");
            char email[100];
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0'; // Hapus newline
            
            // Cari akun berdasarkan email
            User user_aktif;
            ListUser L;
            CreateListUser(&L);
            
            // Dalam sistem nyata, akan ada fungsi untuk mendapatkan data akun aktif
            // Untuk simulasi, kita baca dari database
            Record record;
            InisialisasiRecord(&record);
            if (BacaAkunUser(&record, email)) {
                // Konversi record ke User
                strcpy(user_aktif.email, email);
                strcpy(user_aktif.nama, AmbilNilai(&record, "nama"));
                strcpy(user_aktif.alamat, AmbilNilai(&record, "alamat"));
                strcpy(user_aktif.nomor_telepon, AmbilNilai(&record, "nomor_telepon"));
                
                // Isi data penumpang dari akun
                IsiDataPenumpangDariAkun(pembelian, user_aktif);
                printf("\nData penumpang berhasil diisi dari akun.\n");
                
                // Simpan email untuk pembayaran nanti
                strcpy(pembelian->email_penumpang, email);
            } else {
                printf("\nAkun dengan email %s tidak ditemukan.\n", email);
                printf("Silakan isi data penumpang secara manual.\n\n");
                // Lanjut ke pengisian manual
                pilihan = 'n';
            }
        }
    }
    
    if (pilihan == 'n' || pilihan == 'N') {
        // Isi data penumpang secara manual
        printf("\n--- Isi Data Penumpang ---\n");
        
        printf("Email: ");
        fgets(pembelian->email_penumpang, sizeof(pembelian->email_penumpang), stdin);
        pembelian->email_penumpang[strcspn(pembelian->email_penumpang, "\n")] = '\0';
        
        printf("Nama: ");
        fgets(pembelian->nama_penumpang, sizeof(pembelian->nama_penumpang), stdin);
        pembelian->nama_penumpang[strcspn(pembelian->nama_penumpang, "\n")] = '\0';
        
        printf("Nomor Telepon: ");
        fgets(pembelian->nomor_telepon, sizeof(pembelian->nomor_telepon), stdin);
        pembelian->nomor_telepon[strcspn(pembelian->nomor_telepon, "\n")] = '\0';
        
        printf("Nomor Identitas (KTP/SIM/Paspor): ");
        fgets(pembelian->nomor_identitas, sizeof(pembelian->nomor_identitas), stdin);
        pembelian->nomor_identitas[strcspn(pembelian->nomor_identitas, "\n")] = '\0';
    }
    
    // Validasi data penumpang
    if (!ValidasiDataPenumpang(*pembelian)) {
        printf("\nData penumpang tidak valid. Silakan periksa kembali.\n");
        printf("Tekan Enter untuk mengisi ulang...");
        getchar();
        MenuDataPenumpang(pembelian); // Rekursif untuk mengisi ulang
        return;
    }
    
    // Update status pembelian
    pembelian->status = DATA_PENUMPANG;
    
    // Tampilkan konfirmasi data penumpang
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|          DATA PENUMPANG BERHASIL            |\n");
    printf("+----------------------------------------------+\n");
    printf("Email           : %s\n", pembelian->email_penumpang);
    printf("Nama            : %s\n", pembelian->nama_penumpang);
    printf("Nomor Telepon   : %s\n", pembelian->nomor_telepon);
    printf("Nomor Identitas : %s\n\n", pembelian->nomor_identitas);
    
    // Lanjut ke pembayaran
    printf("Lanjut ke pembayaran? (y/n): ");
    scanf(" %c", &pilihan);
    while(getchar() != '\n'); // Membersihkan buffer
    
    if (pilihan == 'y' || pilihan == 'Y') {
        // Lanjut ke pembayaran
        MenuPembayaran(pembelian, pembelian->email_penumpang);
    } else {
        printf("\nProses pembelian tiket dibatalkan.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
    }
}

// Implementasi fungsi IsiDataPenumpangDariAkun
boolean IsiDataPenumpangDariAkun(PembelianTiket* pembelian, User user_aktif) {
    // Salin data dari akun ke pembelian
    strcpy(pembelian->email_penumpang, user_aktif.email);
    strcpy(pembelian->nama_penumpang, user_aktif.nama);
    strcpy(pembelian->nomor_telepon, user_aktif.nomor_telepon);
    
    // Nomor identitas perlu diisi manual karena tidak ada di User
    printf("Nomor Identitas (KTP/SIM/Paspor): ");
    fgets(pembelian->nomor_identitas, sizeof(pembelian->nomor_identitas), stdin);
    pembelian->nomor_identitas[strcspn(pembelian->nomor_identitas, "\n")] = '\0';
    
    return TRUE;
}

// Implementasi fungsi ValidasiDataPenumpang
boolean ValidasiDataPenumpang(PembelianTiket pembelian) {
    // Validasi email
    if (!ValidasiEmail(pembelian.email_penumpang)) {
        printf("Error: Format email tidak valid.\n");
        return FALSE;
    }
    
    // Validasi nama (tidak boleh kosong)
    if (strlen(pembelian.nama_penumpang) == 0) {
        printf("Error: Nama penumpang tidak boleh kosong.\n");
        return FALSE;
    }
    
    // Validasi nomor telepon
    if (!ValidasiNomorTelepon(pembelian.nomor_telepon)) {
        printf("Error: Format nomor telepon tidak valid.\n");
        return FALSE;
    }
    
    // Validasi nomor identitas (minimal 10 karakter)
    if (strlen(pembelian.nomor_identitas) < 10) {
        printf("Error: Nomor identitas minimal 10 karakter.\n");
        return FALSE;
    }
    
    return TRUE;
}

// Implementasi fungsi PilihTiket
boolean PilihTiket(ListHasilPencarian hasil, int nomor_tiket, HasilPencarian* tiket_dipilih) {
    if (nomor_tiket < 1 || nomor_tiket > hasil.count) {
        return FALSE;
    }
    
    // Cari tiket dengan nomor_tiket
    NodeHasilPencarian* current = hasil.head;
    int no = 1;
    
    while (current != NULL && no < nomor_tiket) {
        current = current->next;
        no++;
    }
    
    if (current != NULL) {
        *tiket_dipilih = current->tiket;
        return TRUE;
    }
    
    return FALSE;
}

// Implementasi fungsi InisialisasiPembelianTiket
void InisialisasiPembelianTiket(PembelianTiket* pembelian, HasilPencarian tiket_dipilih) {
    pembelian->tiket_dipilih = tiket_dipilih;
    pembelian->nomor_gerbong = 0;
    strcpy(pembelian->kode_kursi, "");
    strcpy(pembelian->email_penumpang, "");
    strcpy(pembelian->nama_penumpang, "");
    strcpy(pembelian->nomor_telepon, "");
    strcpy(pembelian->nomor_identitas, "");
    pembelian->total_bayar = tiket_dipilih.harga_tiket;
    pembelian->status = PEMILIHAN_TIKET;
    strcpy(pembelian->kode_pembelian, "");
}

// Implementasi fungsi TampilkanDetailTiket
void TampilkanDetailTiket(PembelianTiket pembelian) {
    printf("+----------------------------------------------+\n");
    printf("|             DETAIL TIKET                     |\n");
    printf("+----------------------------------------------+\n");
    printf("Kereta       : %s (%s)\n", pembelian.tiket_dipilih.id_kereta, pembelian.tiket_dipilih.nama_kereta);
    printf("Rute         : %s - %s\n", pembelian.tiket_dipilih.stasiun_asal, pembelian.tiket_dipilih.stasiun_tujuan);
    printf("Tanggal      : %s\n", pembelian.tiket_dipilih.tanggal);
    printf("Waktu        : %s - %s\n", pembelian.tiket_dipilih.waktu_berangkat, pembelian.tiket_dipilih.waktu_tiba);
    printf("Jenis Layanan: %s\n", pembelian.tiket_dipilih.jenis_layanan);
    printf("Harga        : %.2f\n", pembelian.tiket_dipilih.harga_tiket);
    printf("+----------------------------------------------+\n");
}

// Implementation for MenuKursiKereta and MenuPembayaran are now removed
// since they are already defined in dashboard_kursi_kereta.c and dashboard_pembayaran.c
