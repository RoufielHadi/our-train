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
void MenuKursiKereta(const char* id_kereta, const char* tanggal, const char* stasiun_awal, const char* stasiun_akhir, int* nomor_gerbong_dipilih, char* kode_kursi_dipilih);



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
        // Debug: print the raw line being checked
        printf("Debug [DapatkanRuteUnik]: memeriksa baris: %s", line);
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
        // Debug: print the raw line being checked
        printf("Debug [CariTiket]: memeriksa baris: %s", line);
        // Format: KodeKereta|Stasiun1,Stasiun2,...|waktu1,waktu2,...
        char kode_kereta[10] = "";
        char stasiun_list[1024] = "";
        char waktu_list[1024] = "";
        // Parsing baris
        sscanf(line, "%[^|]|%[^|]|%[^\n]", kode_kereta, stasiun_list, waktu_list);
        // Debug: show parsed train ID and stations
        printf("Debug [CariTiket]: kode_kereta=%s, stasiun_list=%s\n", kode_kereta, stasiun_list);
        
        // Buat jadwal kereta
        JadwalHarian jadwal = BuatJadwalKereta(kode_kereta, (char*)tanggal);
        
        // Parse daftar stasiun dan waktu
        char* stasiun_ptr = stasiun_list;
        char* waktu_ptr = waktu_list;
        
        boolean asal_ditemukan = FALSE;
        boolean tujuan_ditemukan = FALSE;
        int index_asal = -1;
        int index_tujuan = -1;
        int index_current = 0;
        
        // Untuk stasiun dan waktu transit
        while (stasiun_ptr && waktu_ptr && *stasiun_ptr && *waktu_ptr) {
            // Ekstrak token stasiun
            char* next_stasiun_comma = strchr(stasiun_ptr, ',');
            int stasiun_len = next_stasiun_comma ? (next_stasiun_comma - stasiun_ptr) : strlen(stasiun_ptr);
            char station_token[MAX_NAMA_SEGMEN];
            strncpy(station_token, stasiun_ptr, (stasiun_len < MAX_NAMA_SEGMEN - 1) ? stasiun_len : (MAX_NAMA_SEGMEN - 1));
            station_token[(stasiun_len < MAX_NAMA_SEGMEN - 1) ? stasiun_len : (MAX_NAMA_SEGMEN - 1)] = '\0';

            // Trim whitespace
            char* token_trim = station_token;
            while (*token_trim && isspace((unsigned char)*token_trim)) token_trim++;
            char trimmed[MAX_NAMA_SEGMEN];
            strncpy(trimmed, token_trim, MAX_NAMA_SEGMEN - 1);
            trimmed[MAX_NAMA_SEGMEN - 1] = '\0';
            char* end_trim = trimmed + strlen(trimmed) - 1;
            while (end_trim > trimmed && isspace((unsigned char)*end_trim)) { *end_trim = '\0'; end_trim--; }
            char stasiun_current_lower[MAX_NAMA_SEGMEN];
            StringToLower(trimmed, stasiun_current_lower);

            // Ekstrak token waktu
            char* next_waktu_comma = strchr(waktu_ptr, ',');
            int waktu_len = next_waktu_comma ? (next_waktu_comma - waktu_ptr) : strlen(waktu_ptr);
            char time_token[16];
            strncpy(time_token, waktu_ptr, (waktu_len < (int)sizeof(time_token) - 1) ? waktu_len : ((int)sizeof(time_token) - 1));
            time_token[(waktu_len < (int)sizeof(time_token) - 1) ? waktu_len : ((int)sizeof(time_token) - 1)] = '\0';

            int jam, menit;
            sscanf(time_token, "%d:%d", &jam, &menit);
            Waktu waktu = {0, menit, jam, 0, 0, 0};

            // Cek apakah stasiun ini adalah asal atau tujuan
            if (strcmp(stasiun_current_lower, asal_lower) == 0) {
                asal_ditemukan = TRUE;
                index_asal = index_current;
            }
            if (strcmp(stasiun_current_lower, tujuan_lower) == 0) {
                tujuan_ditemukan = TRUE;
                index_tujuan = index_current;
            }

            // Tambahkan stasiun ke jadwal
            TambahStasiunKeJadwal(&jadwal, trimmed, waktu);

            // Update index dan pointers
            index_current++;
            stasiun_ptr = next_stasiun_comma ? (next_stasiun_comma + 1) : NULL;
            waktu_ptr = next_waktu_comma ? (next_waktu_comma + 1) : NULL;
        }
        // Debug: show indices found
        printf("Debug [CariTiket]: %s index_asal=%d, index_tujuan=%d, asal_ditemukan=%d, tujuan_ditemukan=%d\n", kode_kereta, index_asal, index_tujuan, asal_ditemukan, tujuan_ditemukan);
        
        // Jika asal dan tujuan ditemukan dan urutan benar (asal->tujuan)
        if (asal_ditemukan && tujuan_ditemukan && index_asal < index_tujuan) {
            printf("Debug [CariTiket]: melewati filter rute untuk %s (asal=%d, tujuan=%d)\n", kode_kereta, index_asal, index_tujuan);
            // Cek jenis layanan
            const char* jenis = GetJenisLayananById(globalListKereta, kode_kereta);
            // Debug: cek nilai jenis layanan yang diambil dari globalListKereta
            if (jenis != NULL) {
                printf("Debug [CariTiket]: jenis asli untuk %s = '%s'\n", kode_kereta, jenis);
            } else {
                printf("Debug [CariTiket]: jenis layanan untuk %s tidak ditemukan (NULL)\n", kode_kereta);
                // Gunakan nilai default untuk kereta yang tidak ada di database informasi
                jenis = "Ekonomi"; // Default jenis layanan
                printf("Debug [CariTiket]: menggunakan jenis default '%s' untuk %s\n", jenis, kode_kereta);
            }
            char jenis_current_lower[20];
            
            if (jenis != NULL) {
                // Trim leading/trailing whitespace pada jenis layanan
                char jenis_trim[20];
                char* ptr = (char*)jenis;
                while (*ptr && isspace((unsigned char)*ptr)) ptr++;
                strncpy(jenis_trim, ptr, sizeof(jenis_trim) - 1);
                jenis_trim[sizeof(jenis_trim) - 1] = '\0';
                char* end_ptr = jenis_trim + strlen(jenis_trim) - 1;
                while (end_ptr > jenis_trim && isspace((unsigned char)*end_ptr)) { *end_ptr = '\0'; end_ptr--; }
                // Konversi ke lowercase
                StringToLower(jenis_trim, jenis_current_lower);
                printf("Debug [CariTiket]: jenis_current_lower='%s', jenis_lower(filter)='%s'\n", jenis_current_lower, jenis_lower);
                
                // Jika jenis layanan cocok atau kriteria jenis kosong
                if (strlen(jenis_lower) == 0 || strcmp(jenis_current_lower, jenis_lower) == 0) {
                    printf("Debug [CariTiket]: Jenis layanan %s sesuai dengan filter %s\n", jenis_current_lower, jenis_lower);

                    // Dapatkan jumlah kursi dari informasi kereta di database
                    int jumlah_kursi_tersedia = 0;
                    InformasiKereta* info_kereta = GetInformasiKeretaById(globalListKereta, kode_kereta);
                    
                    // Dapatkan jenis kereta untuk konfigurasi kursi
                    JenisKereta jenis_kereta = GetJenisKeretaById(kode_kereta);
                    
                    // Dapatkan konfigurasi kursi berdasarkan jenis kereta (baris dan kolom)
                    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis_kereta);
                    
                    if (info_kereta != NULL) {
                        // Ambil jumlah gerbong dari informasi kereta
                        int jumlah_gerbong = atoi(info_kereta->jumlah_gerbong);
                        
                        // Hitung total kursi = jumlah gerbong * baris * kolom
                        jumlah_kursi_tersedia = jumlah_gerbong * konfig.baris * konfig.kolom;
                        
                        printf("Debug [CariTiket]: Kereta %s memiliki %d gerbong, konfigurasi kursi %dx%d\n", 
                               kode_kereta, jumlah_gerbong, konfig.baris, konfig.kolom);
                    } else {
                        // Jika tidak ada informasi kereta, gunakan nilai default
                        jumlah_kursi_tersedia = 6 * konfig.baris * konfig.kolom; // Asumsi 6 gerbong
                        
                        printf("Debug [CariTiket]: Kereta %s tidak ditemukan di database, menggunakan default: 6 gerbong, konfigurasi kursi %dx%d\n", 
                               kode_kereta, konfig.baris, konfig.kolom);
                    }
                    
                    printf("Debug [CariTiket]: Jumlah kursi tersedia untuk %s = %d\n", kode_kereta, jumlah_kursi_tersedia);

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
                    Waktu waktu_berangkat = {0}, waktu_tiba = {0};
                    
                    // Ekstrak waktu dari string waktu yang sudah dipisahkan
                    char waktu_list_copy[1024];
                    strcpy(waktu_list_copy, waktu_list);
                    
                    // Dapatkan array waktu
                    char* waktu_array[50]; // Maksimal 50 stasiun
                    int waktu_count = 0;
                    
                    char* waktu_token = strtok(waktu_list_copy, ",");
                    while (waktu_token != NULL && waktu_count < 50) {
                        waktu_array[waktu_count++] = waktu_token;
                        waktu_token = strtok(NULL, ",");
                    }
                    
                    // Ambil waktu berdasarkan indeks asal dan tujuan
                    if (index_asal >= 0 && index_asal < waktu_count) {
                        sscanf(waktu_array[index_asal], "%d:%d", &waktu_berangkat.jam, &waktu_berangkat.menit);
                    }
                    
                    if (index_tujuan >= 0 && index_tujuan < waktu_count) {
                        sscanf(waktu_array[index_tujuan], "%d:%d", &waktu_tiba.jam, &waktu_tiba.menit);
                    }
                    
                    printf("Debug [CariTiket]: Waktu berangkat: %02d:%02d, Waktu tiba: %02d:%02d\n", 
                           waktu_berangkat.jam, waktu_berangkat.menit, waktu_tiba.jam, waktu_tiba.menit);
                    
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
    
    // Tentukan lebar maksimum untuk setiap kolom berdasarkan konten
    int max_id_width = 9; // "ID Kereta"
    int max_nama_width = 11; // "Nama Kereta"
    int max_rute_width = 4; // "Rute"
    int max_jenis_width = 5; // "Jenis"
    
    // Scan semua tiket untuk menentukan lebar kolom maksimum
    NodeHasilPencarian* scan = hasil.head;
    while (scan != NULL) {
        char rute[64];
        sprintf(rute, "%s-%s", scan->tiket.stasiun_asal, scan->tiket.stasiun_tujuan);
        
        // Update lebar maksimum
        int id_len = strlen(scan->tiket.id_kereta);
        int nama_len = strlen(scan->tiket.nama_kereta);
        int rute_len = strlen(rute);
        int jenis_len = strlen(scan->tiket.jenis_layanan);
        
        if (id_len > max_id_width) max_id_width = id_len;
        if (nama_len > max_nama_width) max_nama_width = nama_len;
        if (rute_len > max_rute_width) max_rute_width = rute_len;
        if (jenis_len > max_jenis_width) max_jenis_width = jenis_len;
        
        scan = scan->next;
    }
    
    // Tambahkan padding
    max_id_width += 2;
    max_nama_width += 2;
    max_rute_width += 2;
    max_jenis_width += 2;
    
    // Hitung total lebar tabel
    int total_width = 1 + 4 + 3 + max_id_width + 3 + max_nama_width + 3 + max_rute_width + 3 + 10 + 3 + 5 + 3 + 5 + 3 + max_jenis_width + 3 + 8 + 1;
    
    // Buat string format untuk garis horizontal
    char horizontal_line[256];
    memset(horizontal_line, '-', total_width);
    horizontal_line[total_width] = '\0';
    
    clearScreen();
    printf("+%s+\n", horizontal_line);
    
    // Hitung posisi tengah untuk judul
    int title_len = strlen("HASIL PENCARIAN TIKET");
    int padding = (total_width - title_len) / 2;
    printf("|%*s%s%*s|\n", padding, "", "HASIL PENCARIAN TIKET", total_width - padding - title_len, "");
    
    printf("+%s+\n", horizontal_line);
    
    // Header tabel dengan lebar yang disesuaikan
    printf("| %-4s | %-*s | %-*s | %-*s | %-10s | %-5s | %-5s | %-*s | %-8s |\n", 
           "No", max_id_width, "ID Kereta", max_nama_width, "Nama Kereta", max_rute_width, "Rute", 
           "Tanggal", "Brkt", "Tiba", max_jenis_width, "Jenis", "Harga");
    
    printf("+%s+\n", horizontal_line);
    
    NodeHasilPencarian* current = hasil.head;
    int no = 1;
    
    while (current != NULL) {
        char rute[64];
        sprintf(rute, "%s-%s", current->tiket.stasiun_asal, current->tiket.stasiun_tujuan);
        
        printf("| %-4d | %-*s | %-*s | %-*s | %-10s | %-5s | %-5s | %-*s | %8.2f |\n", 
               no++, 
               max_id_width, current->tiket.id_kereta,
               max_nama_width, current->tiket.nama_kereta,
               max_rute_width, rute,
               current->tiket.tanggal,
               current->tiket.waktu_berangkat,
               current->tiket.waktu_tiba,
               max_jenis_width, current->tiket.jenis_layanan,
               current->tiket.harga_tiket);
        
        current = current->next;
    }
    
    printf("+%s+\n", horizontal_line);
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
        printf("Debug [MenuPencarianTiket]: Status load data kereta: %s\n", 
               isEmptyKereta(globalListKereta) ? "GAGAL (masih kosong)" : "BERHASIL");
        
        // Tambahkan proses untuk menambahkan data kereta yang ada di jadwal_kereta.txt
        // tetapi tidak ada di informasi_umum.txt ke globalListKereta
        printf("Debug [MenuPencarianTiket]: Menambahkan kereta yang belum terdaftar ke globalListKereta...\n");
        FILE* jadwal_file = fopen(DB_JADWAL_KERETA, "r");
        if (jadwal_file != NULL) {
            char line[1024];
            while (fgets(line, sizeof(line), jadwal_file)) {
                char kode_kereta[20] = {0};
                // Format: KodeKereta|Stasiun1,Stasiun2,...|waktu1,waktu2,...
                char* token = strtok(line, "|");
                if (token != NULL) {
                    strncpy(kode_kereta, token, sizeof(kode_kereta) - 1);
                    // Cek apakah kereta ada di database global
                    if (GetJenisLayananById(globalListKereta, kode_kereta) == NULL) {
                        // Tambahkan kereta dengan nilai default jika tidak ada
                        printf("Debug [MenuPencarianTiket]: Menambahkan kereta %s yang tidak ada di database\n", kode_kereta);
                        
                        // Buat nama kereta berdasarkan informasi dari file informasi_umum.txt
                        char nama_kereta[50];
                        
                        // Coba cari kereta dengan ID yang mirip untuk mendapatkan nama yang sesuai
                        boolean nama_ditemukan = FALSE;
                        FILE* info_file = fopen("informasi_umum.txt", "r");
                        if (info_file != NULL) {
                            char line[256];
                            while (fgets(line, sizeof(line), info_file)) {
                                char id_info[10], nama_info[50];
                                // Format: ID|Nama|JenisLayanan|Harga|JumlahGerbong
                                if (sscanf(line, "%[^|]|%[^|]", id_info, nama_info) == 2) {
                                    // Jika ID sama dengan kode kereta yang dicari
                                    if (strncmp(id_info, kode_kereta, 4) == 0) {
                                        strcpy(nama_kereta, nama_info);
                                        nama_ditemukan = TRUE;
                                        printf("Debug [MenuPencarianTiket]: Nama kereta untuk %s ditemukan: %s\n", 
                                               kode_kereta, nama_kereta);
                                        break;
                                    }
                                }
                            }
                            fclose(info_file);
                        }
                        
                        // Jika tidak ditemukan nama yang sesuai, gunakan nama default
                        if (!nama_ditemukan) {
                            // Buat nama default berdasarkan ID kereta
                            if (strncmp(kode_kereta, "KA", 2) == 0) {
                                sprintf(nama_kereta, "Kereta %s", kode_kereta);
                            } else {
                                strcpy(nama_kereta, kode_kereta);
                            }
                            printf("Debug [MenuPencarianTiket]: Nama kereta untuk %s tidak ditemukan, menggunakan default: %s\n", 
                                   kode_kereta, nama_kereta);
                        }
                        
                        InformasiKereta kereta_baru = BuatInformasiKereta(
                            kode_kereta,                   // ID
                            nama_kereta,                   // Nama yang lebih deskriptif
                            "Ekonomi",                    // Jenis layanan default
                            10000.0,                      // Harga default
                            "6");                         // Jumlah gerbong default
                        TambahInformasiKereta(&globalListKereta, kereta_baru);
                    }
                }
            }
            fclose(jadwal_file);
        }
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
    // Normalisasi format tanggal ke DD-MM-YYYY jika user memasukkan dengan spasi atau tanda lain
    {
        int d, m, y;
        if (sscanf(tanggal, "%d-%d-%d", &d, &m, &y) == 3 || sscanf(tanggal, "%d %d %d", &d, &m, &y) == 3) {
            char tanggal_norm[11];
            sprintf(tanggal_norm, "%02d-%02d-%04d", d, m, y);
            strcpy(tanggal, tanggal_norm);
        }
    }

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

// Simpan data pembelian ke dalam file riwayat_pemesanan.txt
boolean SimpanRiwayatPembelianTiket(PembelianTiket pembelian) {
    // Validasi status pembelian
    if (pembelian.status != SELESAI) {
        printf("Error: Pembelian belum selesai\n");
        return FALSE;
    }
    // Buka file riwayat_pemesanan.txt untuk append
    FILE *f = fopen("riwayat_pemesanan.txt", "a");
    if (!f) {
        printf("Warning: Gagal membuka riwayat_pemesanan.txt\n");
        return FALSE;
    }
    // Ambil timestamp saat ini
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char waktu_real[20];
    sprintf(waktu_real, "%04d-%02d-%02d %02d:%02d:%02d",
            tm_now->tm_year + 1900,
            tm_now->tm_mon + 1,
            tm_now->tm_mday,
            tm_now->tm_hour,
            tm_now->tm_min,
            tm_now->tm_sec);
    // Tulis data dengan format:
    // id_kereta|nama_kereta|stasiun_asal|stasiun_tujuan|waktu_berangkat|
    // waktu_tiba|tanggal|jenis_layanan|nama_penumpang|email|nomor_telepon|
    // kode_kursi|nomor_gerbong|waktu_real
    fprintf(f, "%s|%s|%s|%s|%s|%s|%s|%.2f|%s|%s|%s|%s|%s|%d|%s\n",
            pembelian.tiket_dipilih.id_kereta,
            pembelian.tiket_dipilih.nama_kereta,
            pembelian.tiket_dipilih.stasiun_asal,
            pembelian.tiket_dipilih.stasiun_tujuan,
            pembelian.tiket_dipilih.waktu_berangkat,
            pembelian.tiket_dipilih.waktu_tiba,
            pembelian.tiket_dipilih.tanggal,
            pembelian.tiket_dipilih.harga_tiket,
            pembelian.tiket_dipilih.jenis_layanan,
            pembelian.nama_penumpang,
            pembelian.email_penumpang,
            pembelian.nomor_telepon,
            pembelian.kode_kursi,
            pembelian.nomor_gerbong,
            waktu_real);
    fclose(f);
    return TRUE;
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
    
    // Pemilihan kursi: loop hingga user memilih kursi atau memilih kembali
    {
        char choice_buf[4];
        while (1) {
            printf("Tekan Enter untuk melanjutkan ke pemilihan kursi atau 0 untuk kembali: ");
            if (fgets(choice_buf, sizeof(choice_buf), stdin) && choice_buf[0] == '0') {
                // Kembali ke menu sebelumnya
                return;
            }

            // Konversi tanggal ke format database YYYY-MM-DD
            char tanggal_db[11];
            if (strlen(pembelian->tiket_dipilih.tanggal) == 10 &&
                pembelian->tiket_dipilih.tanggal[2] == '-' &&
                pembelian->tiket_dipilih.tanggal[5] == '-') {
                sprintf(tanggal_db, "%c%c%c%c-%c%c-%c%c",
                        pembelian->tiket_dipilih.tanggal[6], pembelian->tiket_dipilih.tanggal[7],
                        pembelian->tiket_dipilih.tanggal[8], pembelian->tiket_dipilih.tanggal[9],
                        pembelian->tiket_dipilih.tanggal[3], pembelian->tiket_dipilih.tanggal[4],
                        pembelian->tiket_dipilih.tanggal[0], pembelian->tiket_dipilih.tanggal[1]);
                tanggal_db[10] = '\0';
            } else {
                strcpy(tanggal_db, pembelian->tiket_dipilih.tanggal);
            }

            // Reset pilihan kursi
            pembelian->nomor_gerbong = 0;
            strcpy(pembelian->kode_kursi, "");

            // Siapkan data kursi (baca atau inisialisasi)
            KursiKereta kereta;
            strcpy(kereta.id_kereta, pembelian->tiket_dipilih.id_kereta);
            strcpy(kereta.tanggal, tanggal_db);
            if (!MuatDataKursiDariFile(&kereta, "kursi_kereta.txt")) {
                // ... existing default setup ...
            } else {
                // ... existing reload/append logic ...
            }

            // Panggil menu pemilihan kursi
            MenuKursiKereta(pembelian->tiket_dipilih.id_kereta,
                            tanggal_db,
                            pembelian->tiket_dipilih.stasiun_asal,
                            pembelian->tiket_dipilih.stasiun_tujuan,
                            &pembelian->nomor_gerbong,
                            pembelian->kode_kursi);

            // Periksa apakah kursi telah dipilih
            if (pembelian->nomor_gerbong > 0 && pembelian->kode_kursi[0] != '\0') {
                break;
            }

            // Jika belum memilih, tanyakan ulang atau kembali
            printf("\nAnda belum memilih kursi.\n");
            printf("Tekan Enter untuk mencoba lagi atau 0 untuk kembali: ");
            if (fgets(choice_buf, sizeof(choice_buf), stdin) && choice_buf[0] == '0') {
                return;
            }
            // else ulangi loop
        }
    }

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
                
                // Tampilkan data penumpang yang diambil dari akun
                printf("\nEmail           : %s\n", user_aktif.email);
                printf("Nama            : %s\n", user_aktif.nama);
                printf("Nomor Telepon   : %s\n\n", user_aktif.nomor_telepon);
                
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
                
                // Tampilkan data penumpang yang diambil dari akun
                printf("\nEmail           : %s\n", user_aktif.email);
                printf("Nama            : %s\n", user_aktif.nama);
                printf("Nomor Telepon   : %s\n\n", user_aktif.nomor_telepon);
                
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