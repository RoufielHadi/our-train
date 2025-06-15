/*
Author: Devi Maulani
NIM: 241524007  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_kursi_kereta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


// Deklarasi fungsi helper internal
boolean MuatDataKursiDariFileLama(KursiKereta *kereta, const char *namafile);

// Fungsi wrapper untuk HitungJumlahKursiKereta
int HitungJumlahKursiKeretaWrapper(KursiKereta kereta) {
    JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
    return HitungJumlahKursiKereta(kereta, jenis);
}

// KONVERSI ANTARA STRUKTUR KURSIKERETA DAN RECORD
void KursiKeretaKeRecord(KursiKereta kereta, Record *record) {
    // Tambahkan informasi dasar kereta
    TambahField(record, "id_kereta", kereta.id_kereta);
    TambahField(record, "tanggal", kereta.tanggal);
    
    // Tambahkan jumlah gerbong
    char jumlah_gerbong[5];
    sprintf(jumlah_gerbong, "%d", kereta.jumlah_gerbong);
    TambahField(record, "jumlah_gerbong", jumlah_gerbong);
    
    // Tambahkan jumlah segmen
    char jumlah_segmen[5];
    sprintf(jumlah_segmen, "%d", kereta.jumlah_segmen);
    TambahField(record, "jumlah_segmen", jumlah_segmen);
    
    // Tambahkan daftar segmen
    char segmen_list[MAX_VALUE_LENGTH] = "";
    int i;
    for (i = 0; i < kereta.jumlah_segmen; i++) {
        strcat(segmen_list, kereta.segmen[i].nama);
        if (i < kereta.jumlah_segmen - 1) {
            strcat(segmen_list, ",");
        }
    }
    TambahField(record, "segmen_list", segmen_list);
    
    // Tambahkan primary key (kombinasi id_kereta dan tanggal)
    char primary_key[MAX_VALUE_LENGTH];
    sprintf(primary_key, "%s_%s", kereta.id_kereta, kereta.tanggal);
    TambahField(record, "primary_key", primary_key);
    
    // Status kursi disimpan dalam format JSON-like string karena terlalu kompleks untuk disimpan sebagai value biasa
    // Format: "gerbong:baris:kolom:segmen" : status, ...
    char status_kursi[MAX_VALUE_LENGTH * 10] = ""; // Perlu alokasi lebih besar karena banyaknya data
    int pos = 0;
    JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    
    int g, b, k, s;
    for (g = 0; g < kereta.jumlah_gerbong; g++) {
        for (b = 0; b < konfig.baris; b++) {
            for (k = 0; k < konfig.kolom; k++) {
                for (s = 0; s < kereta.jumlah_segmen; s++) {
                    if (kereta.data_kursi[g].status_kursi[k][b][s]) {
                        // Hanya menyimpan kursi yang terisi untuk menghemat ruang
                        char temp[50];
                        sprintf(temp, "%d:%d:%d:%d,", g, b, k, s);
                        
                        // Pastikan tidak melebihi kapasitas string
                        if (strlen(status_kursi) + strlen(temp) < sizeof(status_kursi) - 1) {
                            strcat(status_kursi, temp);
                            pos += strlen(temp);
                        }
                    }
                }
            }
        }
    }
    
    // Hapus trailing comma jika ada
    if (pos > 0 && status_kursi[pos-1] == ',') {
        status_kursi[pos-1] = '\0';
    }
    
    TambahField(record, "status_kursi", status_kursi);
}

boolean RecordKeKursiKereta(Record record, KursiKereta *kereta) {
    // Ambil informasi dasar kereta
    char *id_kereta = AmbilNilai(&record, "id_kereta");
    char *tanggal = AmbilNilai(&record, "tanggal");
    char *jumlah_gerbong_str = AmbilNilai(&record, "jumlah_gerbong");
    char *jumlah_segmen_str = AmbilNilai(&record, "jumlah_segmen");
    char *segmen_list = AmbilNilai(&record, "segmen_list");
    char *status_kursi = AmbilNilai(&record, "status_kursi");
    
    if (!id_kereta || !tanggal || !jumlah_gerbong_str || !jumlah_segmen_str || !segmen_list) {
        return FALSE; // Data tidak lengkap
    }
    
    // Isi informasi dasar kereta
    strncpy(kereta->id_kereta, id_kereta, 9);
    kereta->id_kereta[9] = '\0';
    
    strncpy(kereta->tanggal, tanggal, 10);
    kereta->tanggal[10] = '\0';
    
    kereta->jumlah_gerbong = atoi(jumlah_gerbong_str);
    if (kereta->jumlah_gerbong > MAX_GERBONG) {
        kereta->jumlah_gerbong = MAX_GERBONG;
    }
    
    kereta->jumlah_segmen = atoi(jumlah_segmen_str);
    if (kereta->jumlah_segmen > MAX_SEGMEN) {
        kereta->jumlah_segmen = MAX_SEGMEN;
    }
    
    // Parse segmen_list
    char segmen_copy[MAX_VALUE_LENGTH];
    strncpy(segmen_copy, segmen_list, MAX_VALUE_LENGTH - 1);
    segmen_copy[MAX_VALUE_LENGTH - 1] = '\0';
    
    char *token = strtok(segmen_copy, ",");
    int segmen_idx = 0;
    
    while (token != NULL && segmen_idx < kereta->jumlah_segmen) {
        strncpy(kereta->segmen[segmen_idx].nama, token, MAX_NAMA_SEGMEN - 1);
        kereta->segmen[segmen_idx].nama[MAX_NAMA_SEGMEN - 1] = '\0';
        segmen_idx++;
        token = strtok(NULL, ",");
    }
    
    // Inisialisasi semua kursi sebagai kosong
    JenisKereta jenis = GetJenisKeretaById(kereta->id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    int g, b, k, s;
    for (g = 0; g < kereta->jumlah_gerbong; g++) {
        kereta->data_kursi[g].nomor_gerbong = g + 1;
        for (b = 0; b < konfig.baris; b++) {
            for (k = 0; k < konfig.kolom; k++) {
                for (s = 0; s < kereta->jumlah_segmen; s++) {
                    kereta->data_kursi[g].status_kursi[k][b][s] = FALSE;
                }
            }
        }
    }
    
    // Parse status_kursi jika ada
    if (status_kursi && strlen(status_kursi) > 0) {
        char status_copy[MAX_VALUE_LENGTH * 10];
        strncpy(status_copy, status_kursi, sizeof(status_copy) - 1);
        status_copy[sizeof(status_copy) - 1] = '\0';
        
        token = strtok(status_copy, ",");
        while (token != NULL) {
            int g, b, k, s;
            if (sscanf(token, "%d:%d:%d:%d", &g, &b, &k, &s) == 4) {
                // Pastikan indeks valid
                if (g >= 0 && g < kereta->jumlah_gerbong &&
                    b >= 0 && b < konfig.baris &&
                    k >= 0 && k < konfig.kolom &&
                    s >= 0 && s < kereta->jumlah_segmen) {
                    kereta->data_kursi[g].status_kursi[k][b][s] = TRUE;
                }
            }
            token = strtok(NULL, ",");
        }
    }
    
    return TRUE;
}

// OPERASI FILE
boolean MuatDataKursiDariFile(KursiKereta *kereta, const char *namafile) {
    // Pertama, coba baca menggunakan fungsi database
    Record record;
    InisialisasiRecord(&record);
    
    FILE *file = fopen(namafile, "r");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", namafile);
        return FALSE;
    }
    
    char buffer[1024 * 8]; // Buffer lebih besar untuk file besar
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[bytes_read] = '\0';
    fclose(file);
    
    // Periksa format file
    if (strstr(buffer, "ID_KERETA:") != NULL) {
        // Format file adalah format lama (teks biasa)
        return MuatDataKursiDariFileLama(kereta, namafile);
    } else {
        // Format file adalah format database record
        StringKeRecord(buffer, &record);
        return RecordKeKursiKereta(record, kereta);
    }
}

// Fungsi helper untuk membaca format file lama
boolean MuatDataKursiDariFileLama(KursiKereta *kereta, const char *namafile) {
    FILE *file = fopen(namafile, "r");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", namafile);
        return FALSE;
    }
    
    char buffer[256];
    char id_kereta[10] = {0};
    char tanggal[11] = {0};
    int jumlah_gerbong = 0;
    char segmen_str[1024] = {0};
    
    // Baca ID Kereta
    if (fscanf(file, "ID_KERETA: %s\n", id_kereta) != 1) {
        fclose(file);
        return FALSE;
    }
    strncpy(kereta->id_kereta, id_kereta, 9);
    kereta->id_kereta[9] = '\0';
    
    // Baca tanggal
    if (fscanf(file, "TANGGAL: %s\n", tanggal) != 1) {
        fclose(file);
        return FALSE;
    }
    strncpy(kereta->tanggal, tanggal, 10);
    kereta->tanggal[10] = '\0';
    
    // Baca jumlah gerbong
    if (fscanf(file, "JUMLAH_GERBONG: %d\n", &jumlah_gerbong) != 1) {
        fclose(file);
        return FALSE;
    }
    kereta->jumlah_gerbong = jumlah_gerbong;
    
    // Baca segmen
    if (fscanf(file, "SEGMEN: %[^\n]\n", segmen_str) != 1) {
        fclose(file);
        return FALSE;
    }
    
    // Parse segmen
    char *token = strtok(segmen_str, ",");
    int segmen_count = 0;
    
    while (token != NULL && segmen_count < MAX_SEGMEN) {
        strncpy(kereta->segmen[segmen_count].nama, token, MAX_NAMA_SEGMEN - 1);
        kereta->segmen[segmen_count].nama[MAX_NAMA_SEGMEN - 1] = '\0';
        segmen_count++;
        token = strtok(NULL, ",");
    }
    
    kereta->jumlah_segmen = segmen_count;
    
    // Inisialisasi status kursi
    JenisKereta jenis = GetJenisKeretaById(kereta->id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    int g, k, b, s;
    for (g = 0; g < kereta->jumlah_gerbong; g++) {
        kereta->data_kursi[g].nomor_gerbong = g + 1;
        for (k = 0; k < konfig.kolom; k++) {
            for (b = 0; b < konfig.baris; b++) {
                for (s = 0; s < kereta->jumlah_segmen; s++) {
                    kereta->data_kursi[g].status_kursi[k][b][s] = FALSE;
                }
            }
        }
    }
    
    // Lewati baris kosong
    fgets(buffer, sizeof(buffer), file);
    
    // Proses data gerbong dan kursi
    for (g = 0; g < kereta->jumlah_gerbong; g++) {
        char gerbong_id[20];
        int kapasitas;
        
        // Baca ID gerbong
        if (fscanf(file, "GERBONG: %s\n", gerbong_id) != 1) {
            break;
        }
        
        // Baca kapasitas
        if (fscanf(file, "KAPASITAS: %d\n", &kapasitas) != 1) {
            break;
        }
        
        // Lewati kata KURSI:
        if (fscanf(file, "KURSI:\n") != 0) {
            break;
        }
        
        // Baca data kursi
        while (fgets(buffer, sizeof(buffer), file)) {
            if (buffer[0] == '\n' || buffer[0] == '\r') {
                // Baris kosong menandakan akhir dari data kursi gerbong ini
                break;
            }
            
            // Format: A1:segmen1:status,segmen2:status,...
            char kursi_id[5];
            char *p = buffer;
            
            // Parse ID kursi (misalnya A1)
            char *colon = strchr(p, ':');
            if (!colon) continue;
            
            int len = colon - p;
            if (len > 4) len = 4;
            strncpy(kursi_id, p, len);
            kursi_id[len] = '\0';
            
            // Hitung baris dan kolom dari kursi_id
            int kolom = kursi_id[0] - 'A' + 1; // A=1, B=2, etc.
            int baris = atoi(kursi_id + 1);
            
            // Validasi baris dan kolom
            if (kolom < 1 || kolom > konfig.kolom || baris < 1 || baris > konfig.baris) {
                continue;
            }
            
            p = colon + 1;
            
            // Parse status untuk setiap segmen
            while (*p) {
                // Dapatkan nama segmen
                colon = strchr(p, ':');
                if (!colon) break;
                
                len = colon - p;
                char segmen_nama[MAX_NAMA_SEGMEN];
                if (len > MAX_NAMA_SEGMEN - 1) len = MAX_NAMA_SEGMEN - 1;
                strncpy(segmen_nama, p, len);
                segmen_nama[len] = '\0';
                
                // Cari indeks segmen
                int segmen_idx = CariIndexSegmen(*kereta, segmen_nama);
                if (segmen_idx == -1) {
                    // Segmen tidak ditemukan, lewati
                    // Cari koma berikutnya
                    char *comma = strchr(colon + 1, ',');
                    if (comma) {
                        p = comma + 1;
                    } else {
                        break;
                    }
                    continue;
                }
                
                p = colon + 1;
                
                // Baca status (true/false)
                if (strncmp(p, "true", 4) == 0) {
                    kereta->data_kursi[g].status_kursi[kolom-1][baris-1][segmen_idx] = TRUE;
                    p += 4;
                } else if (strncmp(p, "false", 5) == 0) {
                    kereta->data_kursi[g].status_kursi[kolom-1][baris-1][segmen_idx] = FALSE;
                    p += 5;
                }
                
                // Cari koma berikutnya
                char *comma = strchr(p, ',');
                if (comma) {
                    p = comma + 1;
                } else {
                    break;
                }
            }
        }
    }
    
    fclose(file);
    return TRUE;
}

boolean SimpanDataKursiKeFile(KursiKereta kereta, const char *namafile) {
    // Konversi struktur kereta menjadi Record
    Record record;
    KursiKeretaKeRecord(kereta, &record);
    
    // Konversi Record menjadi string
    char recordStr[MAX_RECORD_LENGTH * 10]; // Alokasi lebih besar karena data kursi kompleks
    RecordKeString(&record, recordStr, sizeof(recordStr));
    
    // Tulis string ke file
    FILE *file = fopen(namafile, "w");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s untuk penulisan\n", namafile);
        return FALSE;
    }
    
    fprintf(file, "%s\n", recordStr);
    fclose(file);
    
    return TRUE;
}

// OPERASI KERETA DALAM DATABASE
boolean BuatKeretaBaru(ArrayKereta *arr, char *id_kereta, int jumlah_gerbong, char *tanggal, const char *daftar_segmen) {
    if (arr->jumlah_kereta >= MAX_KERETA) {
        printf("Error: Database kereta sudah penuh\n");
        return FALSE;
    }
    
    // Parse daftar segmen
    InfoSegmen segmen_list[MAX_SEGMEN];
    int jumlah_segmen = 0;
    
    char segmen_str[1024];
    strncpy(segmen_str, daftar_segmen, sizeof(segmen_str) - 1);
    segmen_str[sizeof(segmen_str) - 1] = '\0';
    
    char *token = strtok(segmen_str, ",");
    while (token != NULL && jumlah_segmen < MAX_SEGMEN) {
        strncpy(segmen_list[jumlah_segmen].nama, token, MAX_NAMA_SEGMEN - 1);
        segmen_list[jumlah_segmen].nama[MAX_NAMA_SEGMEN - 1] = '\0';
        jumlah_segmen++;
        token = strtok(NULL, ",");
    }
    
    if (jumlah_segmen == 0) {
        printf("Error: Tidak ada segmen yang valid\n");
        return FALSE;
    }
    
    // Tambahkan kereta baru
    TambahKereta(arr, id_kereta, jumlah_gerbong, tanggal, segmen_list, jumlah_segmen);
    
    // Simpan ke database
    return SimpanKeretaKeDatabase(arr->data[arr->jumlah_kereta - 1]);
}

boolean HapusKeretaDariDatabase(ArrayKereta *arr, char *id_kereta) {
    int index = CariKeretaById(arr, id_kereta);
    if (index == -1) {
        printf("Error: Kereta dengan ID %s tidak ditemukan\n", id_kereta);
        return FALSE;
    }
    
    // Hapus dari database
    boolean result = HapusKursiKereta(id_kereta, arr->data[index].tanggal);
    
    // Hapus dari array
    if (result) {
        HapusKereta(arr, index);
    }
    
    return result;
}

boolean SimpanKeretaKeDatabase(KursiKereta kereta) {
    Record record;
    KursiKeretaKeRecord(kereta, &record);
    
    return SimpanKursiKereta(&record);
}

boolean BacaKeretaDariDatabase(KursiKereta *kereta, const char *id_kereta, const char *tanggal) {
    Record record;
    InisialisasiRecord(&record);
    
    // Try reading from binary database first
    if (BacaKursiKereta(&record, id_kereta, tanggal)) {
        return RecordKeKursiKereta(record, kereta);
    }
    
    // Fallback: read from old text-format database file
    if (MuatDataKursiDariFile(kereta, DB_KURSI_KERETA)) {
        // Verify this block matches the requested id and date
        if (strcmp(kereta->id_kereta, id_kereta) == 0 && strcmp(kereta->tanggal, tanggal) == 0) {
            return TRUE;
        }
    }
    
    return FALSE;
}

// OPERASI RESERVASI DALAM KONTEKS PERJALANAN
boolean ReservasiKursiPerjalanan(KursiKereta *kereta, int gerbong, int baris, int kolom, const char *segmen_awal, const char *segmen_akhir) {
    // Cari indeks segmen awal dan akhir
    int idx_awal = CariIndexSegmen(*kereta, segmen_awal);
    int idx_akhir = CariIndexSegmen(*kereta, segmen_akhir);
    
    if (idx_awal == -1 || idx_akhir == -1 || idx_awal > idx_akhir) {
        printf("Error: Segmen perjalanan tidak valid\n");
        return FALSE;
    }
    
    // Lakukan reservasi untuk semua segmen antara awal dan akhir
    boolean result = ReservasiKursiMultiSegmen(kereta, gerbong, baris, kolom, idx_awal, idx_akhir);
    
    // Jika berhasil, simpan perubahan ke database
    if (result) {
        SimpanKeretaKeDatabase(*kereta);
    }
    
    return result;
}

boolean BatalkanReservasiPerjalanan(KursiKereta *kereta, int gerbong, int baris, int kolom, const char *segmen_awal, const char *segmen_akhir) {
    // Cari indeks segmen awal dan akhir
    int idx_awal = CariIndexSegmen(*kereta, segmen_awal);
    int idx_akhir = CariIndexSegmen(*kereta, segmen_akhir);
    
    if (idx_awal == -1 || idx_akhir == -1 || idx_awal > idx_akhir) {
        printf("Error: Segmen perjalanan tidak valid\n");
        return FALSE;
    }
    
    // Batalkan reservasi untuk semua segmen antara awal dan akhir
    boolean result = BatalkanReservasiMultiSegmen(kereta, gerbong, baris, kolom, idx_awal, idx_akhir);
    
    // Jika berhasil, simpan perubahan ke database
    if (result) {
        SimpanKeretaKeDatabase(*kereta);
    }
    
    return result;
}

// ANALISIS DATA
float HitungPersentaseOkupansiSegmen(KursiKereta kereta, const char *nama_segmen) {
    int segmen_idx = CariIndexSegmen(kereta, nama_segmen);
    if (segmen_idx == -1) {
        printf("Error: Segmen %s tidak ditemukan\n", nama_segmen);
        return 0.0;
    }
    
    JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
    return HitungPersentaseKursiTerisiSegmen(kereta, segmen_idx, jenis);
}

int HitungJumlahPenumpangSegmen(KursiKereta kereta, const char *nama_segmen) {
    int segmen_idx = CariIndexSegmen(kereta, nama_segmen);
    if (segmen_idx == -1) {
        printf("Error: Segmen %s tidak ditemukan\n", nama_segmen);
        return 0;
    }
    
    return HitungJumlahKursiTerisiSegmen(kereta, segmen_idx);
}

void TampilkanStatistikPenumpang(KursiKereta kereta) {
    printf("\n=== STATISTIK PENUMPANG KERETA %s ===\n", kereta.id_kereta);
    printf("Tanggal: %s\n\n", kereta.tanggal);
    printf("%-25s | %-15s | %-15s | %-10s\n", "Segmen", "Jml Penumpang", "Total Kursi", "Okupansi");
    printf("----------------------------------------------------------------------------\n");
    
    JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
    int total_kursi = HitungJumlahKursiKeretaWrapper(kereta);
    
    int s;
    for (s = 0; s < kereta.jumlah_segmen; s++) {
        int penumpang = HitungJumlahKursiTerisiSegmen(kereta, s);
        float okupansi = HitungPersentaseKursiTerisiSegmen(kereta, s, jenis);
        
        printf("%-25s | %-15d | %-15d | %.2f%%\n", 
               kereta.segmen[s].nama,
               penumpang,
               total_kursi,
               okupansi);
    }
    
    printf("----------------------------------------------------------------------------\n");
}

// UTILITAS DATABASE
boolean MuatSemuaKeretaDariFolder(ArrayKereta *arr, const char *folder_path) {
    DIR *dir;
    struct dirent *entry;
    int jumlah_dimuat = 0;
    
    dir = opendir(folder_path);
    if (dir == NULL) {
        printf("Error: Tidak dapat membuka folder %s\n", folder_path);
        return FALSE;
    }
    
    // Inisialisasi array jika belum
    if (arr->jumlah_kereta == 0) {
        InisialisasiArrayKereta(arr);
    }
    
    // Baca semua file di folder
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // Lewati . dan ..
        
        // Cek apakah file .txt atau .dat
        char *ext = strrchr(entry->d_name, '.');
        if (ext == NULL || (strcmp(ext, ".txt") != 0 && strcmp(ext, ".dat") != 0)) continue;
        
        // Buat path lengkap
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);
        
        // Muat kereta dari file
        KursiKereta kereta;
        if (MuatDataKursiDariFile(&kereta, path)) {
            // Tambahkan ke array jika belum penuh
            if (arr->jumlah_kereta < MAX_KERETA) {
                arr->data[arr->jumlah_kereta] = kereta;
                arr->jumlah_kereta++;
                jumlah_dimuat++;
            } else {
                printf("Warning: Array kereta penuh, tidak semua file dimuat\n");
                break;
            }
        }
    }
    
    closedir(dir);
    
    printf("Berhasil memuat %d kereta dari folder %s\n", jumlah_dimuat, folder_path);
    return jumlah_dimuat > 0;
}

boolean SimpanSemuaKeretaKeFolder(ArrayKereta arr, const char *folder_path) {
    // Cek apakah folder ada, jika tidak, coba buat
    DIR *dir = opendir(folder_path);
    if (dir == NULL) {
        // Folder tidak ada, coba buat
        #ifdef _WIN32
        int result = mkdir(folder_path);
        #else
        int result = mkdir(folder_path, 0777);
        #endif
        
        if (result != 0) {
            printf("Error: Tidak dapat membuat folder %s\n", folder_path);
            return FALSE;
        }
    } else {
        closedir(dir);
    }
    
    int jumlah_disimpan = 0;
    
    // Simpan setiap kereta ke file terpisah dan database
    int i;
    for (i = 0; i < arr.jumlah_kereta; i++) {
        // Simpan ke file terpisah
        char path[512];
        snprintf(path, sizeof(path), "%s/%s_%s.dat", 
                 folder_path, 
                 arr.data[i].id_kereta, 
                 arr.data[i].tanggal);
        
        // Simpan ke database juga
        if (SimpanKeretaKeDatabase(arr.data[i]) && SimpanDataKursiKeFile(arr.data[i], path)) {
            jumlah_disimpan++;
        }
    }
    
    printf("Berhasil menyimpan %d kereta ke folder %s dan database\n", jumlah_disimpan, folder_path);
    return jumlah_disimpan > 0;
}

boolean CekKursiTersedia(KursiKereta kereta, int gerbong, const char* kode_kursi, 
                         const char* segmen_awal, const char* segmen_akhir) {
    int baris, kolom;
    
    // Konversi kode kursi ke baris dan kolom
    if (!KonversiKodeKursi(kode_kursi, &baris, &kolom)) {
        return FALSE;
    }
    
    // Cari index segmen awal dan akhir
    int idx_awal = CariIndexSegmen(kereta, segmen_awal);
    int idx_akhir = CariIndexSegmen(kereta, segmen_akhir);
    
    if (idx_awal == -1 || idx_akhir == -1 || idx_awal > idx_akhir) {
        return FALSE;
    }
    
    // Cek apakah kursi tersedia untuk semua segmen
    int s;
    for (s = idx_awal; s <= idx_akhir; s++) {
        if (CekStatusKursi(kereta, gerbong, baris, kolom, s)) {
            return FALSE;
        }
    }
    
    return TRUE;
}

boolean KonfirmasiPembayaranDanReservasi(KursiKereta *kereta, int gerbong, 
                                        const char* kode_kursi,
                                        const char* segmen_awal, const char* segmen_akhir) {
    // Simulasikan proses pembayaran
    boolean pembayaran_berhasil = TRUE; // Dalam sistem nyata, ini akan memanggil gateway pembayaran
    
    if (pembayaran_berhasil) {
        int baris, kolom;
        
        // Konversi kode kursi ke baris dan kolom
        if (!KonversiKodeKursi(kode_kursi, &baris, &kolom)) {
            return FALSE;
        }
        
        // Reservasi kursi untuk segmen perjalanan yang dipilih
        return ReservasiKursiPerjalanan(kereta, gerbong, baris, kolom, segmen_awal, segmen_akhir);
    }
    
    return FALSE;
}

void TampilkanKursiTersediaUntukRute(KursiKereta kereta, int gerbong,
                                    const char* segmen_awal, const char* segmen_akhir) {
    // Cari index segmen awal dan akhir
    int idx_awal = CariIndexSegmen(kereta, segmen_awal);
    int idx_akhir = CariIndexSegmen(kereta, segmen_akhir);
    
    if (idx_awal == -1 || idx_akhir == -1 || idx_awal > idx_akhir) {
        printf("Error: Rute tidak valid\n");
        return;
    }
    
    printf("\n=== DENAH KURSI KERETA %s (GERBONG %d) ===\n", kereta.id_kereta, gerbong);
    printf("Rute: %s - %s\n", segmen_awal, segmen_akhir);
    printf("----------------------------------\n");
    
    JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    int g = gerbong - 1; // Konversi ke indeks array
    
    // Header kolom (nomor kursi)
    printf("    ");
    int k, b, s;
    for (k = 0; k < konfig.kolom; k++) {
        printf("%c   ", 'A' + k);
    }
    printf("\n");
    
    // Tampilkan kursi
    for (b = 0; b < konfig.baris; b++) {
        printf("%2d  ", b + 1); // Nomor baris
        
        for (k = 0; k < konfig.kolom; k++) {
            // Cek semua segmen dalam rute
            boolean kursi_tersedia = TRUE;
            for (s = idx_awal; s <= idx_akhir; s++) {
                if (kereta.data_kursi[g].status_kursi[k][b][s]) {
                    kursi_tersedia = FALSE;
                    break;
                }
            }
            
            char status = kursi_tersedia ? 'O' : 'X';
            printf("%c   ", status);
        }
        printf("\n");
    }
    
    printf("\nKeterangan: O = Kursi tersedia, X = Kursi terisi\n");
}

boolean KonversiKodeKursi(const char* kode_kursi, int *baris, int *kolom) {
    // Validasi input
    if (kode_kursi == NULL || baris == NULL || kolom == NULL) {
        return FALSE;
    }
    
    // Panjang kode kursi harus minimal 2 karakter
    size_t len = strlen(kode_kursi);
    if (len < 2) {
        return FALSE;
    }
    
    // Format kode kursi: [A-Z][1-99]
    // Contoh: A1, B12, C5
    char kolom_char = kode_kursi[0];
    
    // Kolom harus huruf kapital A-Z atau huruf kecil a-z
    if (!isalpha(kolom_char)) {
        return FALSE;
    }
    
    // Konversi ke huruf kapital jika huruf kecil
    kolom_char = toupper(kolom_char);
    
    // Konversi kolom A=1, B=2, dst
    *kolom = kolom_char - 'A' + 1;
    
    // Konversi baris (angka setelah huruf)
    size_t i;
    *baris = 0;
    for (i = 1; i < len; i++) {
        if (!isdigit(kode_kursi[i])) {
            return FALSE;
        }
        *baris = *baris * 10 + (kode_kursi[i] - '0');
    }
    
    // Validasi baris (harus >= 1)
    if (*baris < 1) {
        return FALSE;
    }
    
    return TRUE;
}

void TampilkanDaftarGerbong(KursiKereta kereta) {
    printf("\n=== DAFTAR GERBONG KERETA %s ===\n", kereta.id_kereta);
    printf("%-10s | %-15s | %-10s\n", "Gerbong", "Jenis", "Kapasitas");
    printf("-----------------------------------------\n");
    
    JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    int kapasitas_per_gerbong = konfig.baris * konfig.kolom;
    
    int g;
    for (g = 0; g < kereta.jumlah_gerbong; g++) {
        printf("%-10d | %-15s | %-10d\n", 
               g + 1, 
               GetNamaJenisKereta(jenis),
               kapasitas_per_gerbong);
    }
    
    printf("-----------------------------------------\n");
}

boolean PesanKursi(KursiKereta *kereta, int gerbong, const char* kode_kursi,
                  const char* segmen_awal, const char* segmen_akhir) {
    // Konversi kode kursi ke baris dan kolom
    int baris, kolom;
    if (!KonversiKodeKursi(kode_kursi, &baris, &kolom)) {
        printf("Kode kursi tidak valid.\n");
        return FALSE;
    }
    
    // Validasi nomor gerbong
    if (gerbong < 1 || gerbong > kereta->jumlah_gerbong) {
        printf("Nomor gerbong tidak valid.\n");
        return FALSE;
    }
    
    // Periksa apakah kursi tersedia
    if (!CekKursiTersedia(*kereta, gerbong, kode_kursi, segmen_awal, segmen_akhir)) {
        printf("Kursi %s tidak tersedia untuk rute %s - %s.\n", 
               kode_kursi, segmen_awal, segmen_akhir);
        return FALSE;
    }
    
    // Lakukan reservasi untuk segmen yang dipilih
    return ReservasiKursiPerjalanan(kereta, gerbong, baris, kolom, segmen_awal, segmen_akhir);
}

// Modifikasi fungsi GetJenisKeretaById
JenisKereta GetJenisKeretaById(const char* id_kereta) {
	// Gunakan fungsi helper dari implementasi_informasi_kereta.h
    const char* jenis_layanan = GetJenisLayananById(globalListKereta, id_kereta);
    
	// Konversi string jenis layanan ke enum JenisKereta
    if (jenis_layanan != NULL) {
        if (strcmp(jenis_layanan, STR_EKONOMI) == 0) return EKONOMI;
        if (strcmp(jenis_layanan, STR_BISNIS) == 0) return BISNIS;
        if (strcmp(jenis_layanan, STR_EKSEKUTIF) == 0) return EKSEKUTIF;
        if (strcmp(jenis_layanan, STR_LUXURY) == 0) return LUXURY;
    }

    return EKONOMI; // Default jika tidak ditemukan
}


// Tampilkan informasi lengkap kereta dengan kursi
void TampilkanInfoKeretaDenganKursi(KursiKereta kereta) {
    printf("\n=== INFORMASI KERETA %s ===\n", kereta.id_kereta);
    printf("Tanggal: %s\n", kereta.tanggal);
    
    // Ambil informasi tambahan dari globalListKereta
    InformasiKereta* info = GetInformasiKeretaById(globalListKereta, kereta.id_kereta);
    if (info != NULL) {
        printf("Nama Kereta: %s\n", info->nama_kereta);
        printf("Jenis Layanan: %s\n", info->jenis_layanan);
        printf("Harga Tiket: Rp%.2f\n", info->harga_tiket);
        printf("Jumlah Gerbong: %s\n", info->jumlah_gerbong);
    }
    
    printf("\nJumlah Gerbong: %d\n", kereta.jumlah_gerbong);
    printf("Jumlah Segmen: %d\n", kereta.jumlah_segmen);
    
    // Tampilkan daftar segmen
    printf("\nDaftar Segmen Perjalanan:\n");
    int i;
    for (i = 0; i < kereta.jumlah_segmen; i++) {
        printf("%d. %s\n", i+1, kereta.segmen[i].nama);
    }
    
    // Tampilkan statistik penumpang
    printf("\nStatistik Penumpang:\n");
    TampilkanStatistikPenumpang(kereta);
    
    printf("===============================\n");
}
