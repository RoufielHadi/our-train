/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi_rekapitulasi_keuntungan.h"
#include "implementasi_riwayat.h"
#include <time.h>

// *** OPERASI DASAR DAFTAR HARGA ***
void InisialisasiDaftarHarga(DaftarHargaTiket *daftar) {
    daftar->jumlah = 0;
}

void TambahHargaKereta(DaftarHargaTiket *daftar, char *id_kereta, char *nama_kereta, 
                      int harga_ekonomi, int harga_ekonomi_premium, int harga_bisnis, 
                      int harga_eksekutif, int harga_luxury, int harga_priority, 
                      int harga_sleeper, int harga_compartment) {
    // Cek jika daftar penuh
    if (daftar->jumlah >= 100) {
        printf("Daftar harga kereta penuh, tidak dapat menambahkan data baru.\n");
        return;
    }
    
    // Cek jika ID kereta sudah ada
    for (int i = 0; i < daftar->jumlah; i++) {
        if (strcmp(daftar->data[i].id_kereta, id_kereta) == 0) {
            printf("ID kereta %s sudah ada dalam daftar.\n", id_kereta);
            return;
        }
    }
    
    // Tambahkan data baru
    strncpy(daftar->data[daftar->jumlah].id_kereta, id_kereta, 9);
    daftar->data[daftar->jumlah].id_kereta[9] = '\0';
    
    strncpy(daftar->data[daftar->jumlah].nama_kereta, nama_kereta, 99);
    daftar->data[daftar->jumlah].nama_kereta[99] = '\0';
    
    daftar->data[daftar->jumlah].harga_ekonomi = harga_ekonomi;
    daftar->data[daftar->jumlah].harga_ekonomi_premium = harga_ekonomi_premium;
    daftar->data[daftar->jumlah].harga_bisnis = harga_bisnis;
    daftar->data[daftar->jumlah].harga_eksekutif = harga_eksekutif;
    daftar->data[daftar->jumlah].harga_luxury = harga_luxury;
    daftar->data[daftar->jumlah].harga_priority = harga_priority;
    daftar->data[daftar->jumlah].harga_sleeper = harga_sleeper;
    daftar->data[daftar->jumlah].harga_compartment = harga_compartment;
    
    daftar->jumlah++;
    
    printf("Data harga tiket kereta %s (%s) berhasil ditambahkan.\n", nama_kereta, id_kereta);
}

boolean UpdateHargaKereta(DaftarHargaTiket *daftar, char *id_kereta, 
                         int harga_ekonomi, int harga_ekonomi_premium, int harga_bisnis, 
                         int harga_eksekutif, int harga_luxury, int harga_priority, 
                         int harga_sleeper, int harga_compartment) {
    // Cari kereta berdasarkan ID
    for (int i = 0; i < daftar->jumlah; i++) {
        if (strcmp(daftar->data[i].id_kereta, id_kereta) == 0) {
            // Update harga
            daftar->data[i].harga_ekonomi = harga_ekonomi;
            daftar->data[i].harga_ekonomi_premium = harga_ekonomi_premium;
            daftar->data[i].harga_bisnis = harga_bisnis;
            daftar->data[i].harga_eksekutif = harga_eksekutif;
            daftar->data[i].harga_luxury = harga_luxury;
            daftar->data[i].harga_priority = harga_priority;
            daftar->data[i].harga_sleeper = harga_sleeper;
            daftar->data[i].harga_compartment = harga_compartment;
            
            printf("Data harga tiket kereta %s berhasil diperbarui.\n", daftar->data[i].nama_kereta);
            return TRUE;
        }
    }
    
    printf("ID kereta %s tidak ditemukan dalam daftar.\n", id_kereta);
    return FALSE;
}

boolean HapusHargaKereta(DaftarHargaTiket *daftar, char *id_kereta) {
    // Cari indeks kereta yang akan dihapus
    int idx = -1;
    for (int i = 0; i < daftar->jumlah; i++) {
        if (strcmp(daftar->data[i].id_kereta, id_kereta) == 0) {
            idx = i;
            break;
        }
    }
    
    // Jika tidak ditemukan
    if (idx == -1) {
        printf("ID kereta %s tidak ditemukan dalam daftar.\n", id_kereta);
        return FALSE;
    }
    
    // Geser elemen di belakangnya
    for (int i = idx; i < daftar->jumlah - 1; i++) {
        daftar->data[i] = daftar->data[i + 1];
    }
    
    daftar->jumlah--;
    
    printf("Data harga tiket kereta dengan ID %s berhasil dihapus.\n", id_kereta);
    return TRUE;
}

HargaTiketKereta* GetHargaKereta(DaftarHargaTiket daftar, char *id_kereta) {
    for (int i = 0; i < daftar.jumlah; i++) {
        if (strcmp(daftar.data[i].id_kereta, id_kereta) == 0) {
            return &daftar.data[i];
        }
    }
    
    return NULL; // Tidak ditemukan
}

// *** OPERASI FILE DAFTAR HARGA ***
void SaveDaftarHargaToFile(DaftarHargaTiket daftar, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
    
    // Tulis header
    fprintf(file, "ID_Kereta,Nama_Kereta,Ekonomi,Ekonomi_Premium,Bisnis,Eksekutif,Luxury,Priority,Sleeper,Compartment\n");
    
    // Tulis data
    for (int i = 0; i < daftar.jumlah; i++) {
        fprintf(file, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
               daftar.data[i].id_kereta,
               daftar.data[i].nama_kereta,
               daftar.data[i].harga_ekonomi,
               daftar.data[i].harga_ekonomi_premium,
               daftar.data[i].harga_bisnis,
               daftar.data[i].harga_eksekutif,
               daftar.data[i].harga_luxury,
               daftar.data[i].harga_priority,
               daftar.data[i].harga_sleeper,
               daftar.data[i].harga_compartment);
    }
    
    fclose(file);
    printf("Daftar harga tiket kereta berhasil disimpan ke file %s\n", filename);
}

void LoadDaftarHargaFromFile(DaftarHargaTiket *daftar, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    
    // Reset daftar
    InisialisasiDaftarHarga(daftar);
    
    // Skip header
    char buffer[512];
    fgets(buffer, sizeof(buffer), file);
    
    // Baca data
    char id_kereta[10], nama_kereta[100];
    int harga_ekonomi, harga_ekonomi_premium, harga_bisnis, harga_eksekutif;
    int harga_luxury, harga_priority, harga_sleeper, harga_compartment;
    
    while (fscanf(file, "%9[^,],%99[^,],%d,%d,%d,%d,%d,%d,%d,%d\n",
                 id_kereta, nama_kereta,
                 &harga_ekonomi, &harga_ekonomi_premium, &harga_bisnis, &harga_eksekutif,
                 &harga_luxury, &harga_priority, &harga_sleeper, &harga_compartment) == 10) {
        
        TambahHargaKereta(daftar, id_kereta, nama_kereta,
                         harga_ekonomi, harga_ekonomi_premium, harga_bisnis, harga_eksekutif,
                         harga_luxury, harga_priority, harga_sleeper, harga_compartment);
    }
    
    fclose(file);
    printf("Daftar harga tiket kereta berhasil dimuat dari file %s\n", filename);
}

// *** OPERASI PERHITUNGAN KEUNTUNGAN ***
int HitungHargaTiket(DaftarHargaTiket daftar, char *id_kereta, int jenis_kereta) {
    HargaTiketKereta *harga = GetHargaKereta(daftar, id_kereta);
    if (harga == NULL) {
        return 0; // Data tidak ditemukan
    }
    
    // Return harga sesuai jenis kereta
    switch (jenis_kereta) {
        case 0: // EKONOMI
            return harga->harga_ekonomi;
        case 1: // EKONOMI_PREMIUM
            return harga->harga_ekonomi_premium;
        case 2: // BISNIS
            return harga->harga_bisnis;
        case 3: // EKSEKUTIF
            return harga->harga_eksekutif;
        case 4: // LUXURY
            return harga->harga_luxury;
        case 5: // PRIORITY
            return harga->harga_priority;
        case 6: // SLEEPER
            return harga->harga_sleeper;
        case 7: // COMPARTMENT
            return harga->harga_compartment;
        default:
            return 0;
    }
}

long HitungTotalKeuntungan(StackRiwayat riwayat, DaftarHargaTiket daftar) {
    if (isEmptyStackRiwayat(riwayat)) {
        return 0;
    }
    
    long total = 0;
    
    // Buat stack sementara untuk mempertahankan stack asli
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin stack asli ke temp
    addressRiwayat P = riwayat.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Hitung keuntungan dari setiap tiket
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            // Asumsikan bahwa jenis kereta disimpan dalam suatu field
            // dalam struktur InformasiKereta (misalnya jenis_kereta)
            int harga = HitungHargaTiket(daftar, tiket.riwayat_kereta.id_kereta, tiket.riwayat_kereta.jenis_kereta);
            total += harga;
        }
    }
    
    return total;
}

long HitungKeuntunganPeriode(StackRiwayat riwayat, DaftarHargaTiket daftar, 
                           struct Waktu waktu_awal, struct Waktu waktu_akhir) {
    // Filter riwayat berdasarkan periode waktu
    StackRiwayat filtered = FilterRiwayatByWaktu(riwayat, waktu_awal, waktu_akhir);
    
    // Hitung keuntungan dari riwayat yang telah difilter
    long keuntungan = HitungTotalKeuntungan(filtered, daftar);
    
    // Bersihkan stack filtered
    DeAlokasiStackRiwayat(&filtered);
    
    return keuntungan;
}

// *** OPERASI REKAPITULASI ***
RekapitulasiKeuntungan BuatRekapitulasi(StackRiwayat riwayat, DaftarHargaTiket daftar, 
                                      struct Waktu waktu_awal, struct Waktu waktu_akhir) {
    RekapitulasiKeuntungan rekap;
    
    // Set periode waktu
    rekap.periode_awal = waktu_awal;
    rekap.periode_akhir = waktu_akhir;
    
    // Filter riwayat berdasarkan periode waktu
    StackRiwayat filtered = FilterRiwayatByWaktu(riwayat, waktu_awal, waktu_akhir);
    
    // Hitung jumlah tiket
    rekap.jumlah_tiket = NbElmtStackRiwayat(filtered);
    
    // Hitung total keuntungan
    rekap.total_keuntungan = HitungTotalKeuntungan(filtered, daftar);
    
    // Cari kereta terlaris
    if (rekap.jumlah_tiket > 0) {
        // Hitung jumlah tiket per kereta
        struct {
            char id_kereta[10];
            char nama_kereta[100];
            int jumlah;
        } kereta_count[100]; // Asumsi maksimal 100 kereta
        
        int jumlah_kereta = 0;
        
        // Inisialisasi
        StackRiwayat temp;
        RiwayatTiket tiket;
        
        CreateStackRiwayat(&temp);
        
        // Salin stack filtered ke temp
        addressRiwayat P = filtered.top;
        while (P != NULL) {
            PushRiwayat(&temp, P->info);
            P = P->next;
        }
        
        // Hitung jumlah tiket per kereta
        while (!isEmptyStackRiwayat(temp)) {
            if (PopRiwayat(&temp, &tiket)) {
                boolean found = FALSE;
                
                for (int i = 0; i < jumlah_kereta; i++) {
                    if (strcmp(kereta_count[i].id_kereta, tiket.riwayat_kereta.id_kereta) == 0) {
                        kereta_count[i].jumlah++;
                        found = TRUE;
                        break;
                    }
                }
                
                if (!found && jumlah_kereta < 100) {
                    strcpy(kereta_count[jumlah_kereta].id_kereta, tiket.riwayat_kereta.id_kereta);
                    strcpy(kereta_count[jumlah_kereta].nama_kereta, tiket.riwayat_kereta.nama_kereta);
                    kereta_count[jumlah_kereta].jumlah = 1;
                    jumlah_kereta++;
                }
            }
        }
        
        // Cari kereta dengan jumlah tiket terbanyak
        int max_idx = 0;
        for (int i = 1; i < jumlah_kereta; i++) {
            if (kereta_count[i].jumlah > kereta_count[max_idx].jumlah) {
                max_idx = i;
            }
        }
        
        // Set kereta terlaris
        strcpy(rekap.kereta_terlaris, kereta_count[max_idx].nama_kereta);
        rekap.jumlah_tiket_terlaris = kereta_count[max_idx].jumlah;
    } else {
        // Jika tidak ada tiket
        strcpy(rekap.kereta_terlaris, "Tidak ada");
        rekap.jumlah_tiket_terlaris = 0;
    }
    
    // Bersihkan stack filtered
    DeAlokasiStackRiwayat(&filtered);
    
    return rekap;
}

void TampilkanRekapitulasi(RekapitulasiKeuntungan rekap) {
    printf("\n=== REKAPITULASI KEUNTUNGAN ===\n");
    printf("Periode: %02d/%02d/%04d - %02d/%02d/%04d\n",
           rekap.periode_awal.hari, rekap.periode_awal.bulan, rekap.periode_awal.tahun,
           rekap.periode_akhir.hari, rekap.periode_akhir.bulan, rekap.periode_akhir.tahun);
    
    printf("Jumlah Tiket Terjual  : %d tiket\n", rekap.jumlah_tiket);
    printf("Total Keuntungan      : Rp %ld\n", rekap.total_keuntungan);
    printf("Kereta Terlaris       : %s (%d tiket)\n", 
           rekap.kereta_terlaris, rekap.jumlah_tiket_terlaris);
    
    // Hitung rata-rata keuntungan per tiket
    if (rekap.jumlah_tiket > 0) {
        double rata_rata = (double)rekap.total_keuntungan / rekap.jumlah_tiket;
        printf("Rata-rata Harga Tiket  : Rp %.2f\n", rata_rata);
    } else {
        printf("Rata-rata Harga Tiket  : -\n");
    }
}

void ExportRekapitulasiToCSV(RekapitulasiKeuntungan rekap, StackRiwayat riwayat, 
                           DaftarHargaTiket daftar, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
    
    // Tulis header rekapitulasi
    fprintf(file, "REKAPITULASI KEUNTUNGAN\n");
    fprintf(file, "Periode,%02d/%02d/%04d - %02d/%02d/%04d\n",
           rekap.periode_awal.hari, rekap.periode_awal.bulan, rekap.periode_awal.tahun,
           rekap.periode_akhir.hari, rekap.periode_akhir.bulan, rekap.periode_akhir.tahun);
    
    fprintf(file, "Jumlah Tiket Terjual,%d\n", rekap.jumlah_tiket);
    fprintf(file, "Total Keuntungan,Rp %ld\n", rekap.total_keuntungan);
    fprintf(file, "Kereta Terlaris,%s (%d tiket)\n", 
           rekap.kereta_terlaris, rekap.jumlah_tiket_terlaris);
    
    if (rekap.jumlah_tiket > 0) {
        double rata_rata = (double)rekap.total_keuntungan / rekap.jumlah_tiket;
        fprintf(file, "Rata-rata Harga Tiket,Rp %.2f\n", rata_rata);
    } else {
        fprintf(file, "Rata-rata Harga Tiket,-\n");
    }
    
    fprintf(file, "\n");
    
    // Filter riwayat berdasarkan periode waktu
    StackRiwayat filtered = FilterRiwayatByWaktu(riwayat, rekap.periode_awal, rekap.periode_akhir);
    
    // Tulis header detail
    fprintf(file, "DETAIL PENJUALAN TIKET\n");
    fprintf(file, "Nama Pengguna,Nama Kereta,Gerbong,Kursi,Tanggal Pemesanan,Waktu Pemesanan,Harga\n");
    
    // Buat stack sementara
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin stack filtered ke temp
    addressRiwayat P = filtered.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Tulis detail tiket
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            int harga = HitungHargaTiket(daftar, tiket.riwayat_kereta.id_kereta, tiket.riwayat_kereta.jenis_kereta);
            
            fprintf(file, "%s,%s,%d,%d,%02d/%02d/%04d,%02d:%02d:%02d,Rp %d\n",
                   tiket.riwayat_user.nama,
                   tiket.riwayat_kereta.nama_kereta,
                   tiket.riwayat_nomor_gerbong,
                   tiket.riwayat_nomor_kursi,
                   tiket.riwayat_waktu_pemesanan.hari,
                   tiket.riwayat_waktu_pemesanan.bulan,
                   tiket.riwayat_waktu_pemesanan.tahun,
                   tiket.riwayat_waktu_pemesanan.jam,
                   tiket.riwayat_waktu_pemesanan.menit,
                   tiket.riwayat_waktu_pemesanan.detik,
                   harga);
        }
    }
    
    // Bersihkan stack filtered
    DeAlokasiStackRiwayat(&filtered);
    
    fclose(file);
    printf("Rekapitulasi keuntungan berhasil diekspor ke file %s\n", filename);
}

// *** OPERASI ANALISIS LANJUTAN ***
void AnalisisKeuntunganPerKereta(StackRiwayat riwayat, DaftarHargaTiket daftar) {
    if (isEmptyStackRiwayat(riwayat)) {
        printf("Tidak ada data riwayat pembelian tiket.\n");
        return;
    }
    
    // Struktur untuk menyimpan data analisis
    struct {
        char id_kereta[10];
        char nama_kereta[100];
        int jumlah_tiket;
        long total_keuntungan;
    } analisis[100]; // Asumsi maksimal 100 kereta
    
    int jumlah_kereta = 0;
    
    // Buat stack sementara
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin stack riwayat ke temp
    addressRiwayat P = riwayat.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Analisis data
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            int harga = HitungHargaTiket(daftar, tiket.riwayat_kereta.id_kereta, tiket.riwayat_kereta.jenis_kereta);
            
            boolean found = FALSE;
            for (int i = 0; i < jumlah_kereta; i++) {
                if (strcmp(analisis[i].id_kereta, tiket.riwayat_kereta.id_kereta) == 0) {
                    analisis[i].jumlah_tiket++;
                    analisis[i].total_keuntungan += harga;
                    found = TRUE;
                    break;
                }
            }
            
            if (!found && jumlah_kereta < 100) {
                strcpy(analisis[jumlah_kereta].id_kereta, tiket.riwayat_kereta.id_kereta);
                strcpy(analisis[jumlah_kereta].nama_kereta, tiket.riwayat_kereta.nama_kereta);
                analisis[jumlah_kereta].jumlah_tiket = 1;
                analisis[jumlah_kereta].total_keuntungan = harga;
                jumlah_kereta++;
            }
        }
    }
    
    // Tampilkan hasil analisis
    printf("\n=== ANALISIS KEUNTUNGAN PER KERETA ===\n");
    printf("%-5s | %-30s | %-15s | %-20s | %-15s\n", 
           "No", "Nama Kereta", "Jumlah Tiket", "Total Keuntungan", "Rata-rata Harga");
    printf("--------------------------------------------------------------------------\n");
    
    for (int i = 0; i < jumlah_kereta; i++) {
        double rata_rata = (double)analisis[i].total_keuntungan / analisis[i].jumlah_tiket;
        
        printf("%-5d | %-30s | %-15d | Rp %-16ld | Rp %-12.2f\n", 
               i + 1, 
               analisis[i].nama_kereta, 
               analisis[i].jumlah_tiket, 
               analisis[i].total_keuntungan,
               rata_rata);
    }
}

void AnalisisKeuntunganPerBulan(StackRiwayat riwayat, DaftarHargaTiket daftar, int tahun) {
    if (isEmptyStackRiwayat(riwayat)) {
        printf("Tidak ada data riwayat pembelian tiket.\n");
        return;
    }
    
    // Array untuk menyimpan data per bulan
    struct {
        int jumlah_tiket;
        long total_keuntungan;
    } bulan[12] = {0}; // Inisialisasi semua nilai dengan 0
    
    // Buat stack sementara
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin stack riwayat ke temp
    addressRiwayat P = riwayat.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Analisis data
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            // Cek jika tahun sesuai
            if (tiket.riwayat_waktu_pemesanan.tahun == tahun) {
                int bulan_idx = tiket.riwayat_waktu_pemesanan.bulan - 1; // 0-based index
                
                if (bulan_idx >= 0 && bulan_idx < 12) {
                    int harga = HitungHargaTiket(daftar, tiket.riwayat_kereta.id_kereta, tiket.riwayat_kereta.jenis_kereta);
                    
                    bulan[bulan_idx].jumlah_tiket++;
                    bulan[bulan_idx].total_keuntungan += harga;
                }
            }
        }
    }
    
    // Tampilkan hasil analisis
    printf("\n=== ANALISIS KEUNTUNGAN PER BULAN TAHUN %d ===\n", tahun);
    printf("%-10s | %-15s | %-20s | %-15s\n", 
           "Bulan", "Jumlah Tiket", "Total Keuntungan", "Rata-rata Harga");
    printf("------------------------------------------------------------\n");
    
    const char *nama_bulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    
    long total_tahunan = 0;
    int total_tiket = 0;
    
    for (int i = 0; i < 12; i++) {
        double rata_rata = (bulan[i].jumlah_tiket > 0) ? 
                          (double)bulan[i].total_keuntungan / bulan[i].jumlah_tiket : 0;
        
        printf("%-10s | %-15d | Rp %-16ld | Rp %-12.2f\n", 
               nama_bulan[i], 
               bulan[i].jumlah_tiket, 
               bulan[i].total_keuntungan,
               rata_rata);
        
        total_tahunan += bulan[i].total_keuntungan;
        total_tiket += bulan[i].jumlah_tiket;
    }
    
    printf("------------------------------------------------------------\n");
    double rata_rata_tahunan = (total_tiket > 0) ? (double)total_tahunan / total_tiket : 0;
    printf("%-10s | %-15d | Rp %-16ld | Rp %-12.2f\n", 
           "TOTAL", total_tiket, total_tahunan, rata_rata_tahunan);
}

void PrediksiKeuntunganBulanan(StackRiwayat riwayat, DaftarHargaTiket daftar) {
    if (isEmptyStackRiwayat(riwayat)) {
        printf("Tidak ada data riwayat pembelian tiket untuk prediksi.\n");
        return;
    }
    
    // Dapatkan waktu saat ini
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    
    int tahun_ini = local_time->tm_year + 1900;
    int bulan_ini = local_time->tm_mon + 1;
    
    // Tentukan tahun dan bulan sebelumnya (untuk perbandingan)
    int tahun_lalu = tahun_ini;
    int bulan_lalu = bulan_ini - 1;
    
    if (bulan_lalu < 1) {
        bulan_lalu = 12;
        tahun_lalu--;
    }
    
    // Tentukan tahun dan bulan berikutnya (untuk prediksi)
    int tahun_depan = tahun_ini;
    int bulan_depan = bulan_ini + 1;
    
    if (bulan_depan > 12) {
        bulan_depan = 1;
        tahun_depan++;
    }
    
    // Buat batas waktu untuk bulan ini
    struct Waktu awal_bulan_ini, akhir_bulan_ini;
    awal_bulan_ini.tahun = tahun_ini;
    awal_bulan_ini.bulan = bulan_ini;
    awal_bulan_ini.hari = 1;
    awal_bulan_ini.jam = 0;
    awal_bulan_ini.menit = 0;
    awal_bulan_ini.detik = 0;
    
    akhir_bulan_ini.tahun = tahun_ini;
    akhir_bulan_ini.bulan = bulan_ini;
    akhir_bulan_ini.hari = 31; // Asumsi maksimal 31 hari
    akhir_bulan_ini.jam = 23;
    akhir_bulan_ini.menit = 59;
    akhir_bulan_ini.detik = 59;
    
    // Buat batas waktu untuk bulan lalu
    struct Waktu awal_bulan_lalu, akhir_bulan_lalu;
    awal_bulan_lalu.tahun = tahun_lalu;
    awal_bulan_lalu.bulan = bulan_lalu;
    awal_bulan_lalu.hari = 1;
    awal_bulan_lalu.jam = 0;
    awal_bulan_lalu.menit = 0;
    awal_bulan_lalu.detik = 0;
    
    akhir_bulan_lalu.tahun = tahun_lalu;
    akhir_bulan_lalu.bulan = bulan_lalu;
    akhir_bulan_lalu.hari = 31; // Asumsi maksimal 31 hari
    akhir_bulan_lalu.jam = 23;
    akhir_bulan_lalu.menit = 59;
    akhir_bulan_lalu.detik = 59;
    
    // Hitung keuntungan bulan ini
    long keuntungan_bulan_ini = HitungKeuntunganPeriode(riwayat, daftar, awal_bulan_ini, akhir_bulan_ini);
    
    // Hitung keuntungan bulan lalu
    long keuntungan_bulan_lalu = HitungKeuntunganPeriode(riwayat, daftar, awal_bulan_lalu, akhir_bulan_lalu);
    
    // Hitung rata-rata pertumbuhan
    double pertumbuhan = 0;
    if (keuntungan_bulan_lalu > 0) {
        pertumbuhan = ((double)keuntungan_bulan_ini - keuntungan_bulan_lalu) / keuntungan_bulan_lalu * 100;
    }
    
    // Prediksi keuntungan bulan depan
    long prediksi_bulan_depan = keuntungan_bulan_ini;
    if (keuntungan_bulan_lalu > 0) {
        prediksi_bulan_depan = keuntungan_bulan_ini * (1 + pertumbuhan / 100);
    }
    
    // Tampilkan hasil prediksi
    const char *nama_bulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    
    printf("\n=== PREDIKSI KEUNTUNGAN BULANAN ===\n");
    printf("Bulan Lalu       : %s %d - Rp %ld\n", nama_bulan[bulan_lalu-1], tahun_lalu, keuntungan_bulan_lalu);
    printf("Bulan Ini        : %s %d - Rp %ld\n", nama_bulan[bulan_ini-1], tahun_ini, keuntungan_bulan_ini);
    printf("Pertumbuhan      : %.2f%%\n", pertumbuhan);
    printf("Prediksi %s %d : Rp %ld\n", nama_bulan[bulan_depan-1], tahun_depan, prediksi_bulan_depan);
    
    if (pertumbuhan > 0) {
        printf("\nAnalisis: Terjadi pertumbuhan keuntungan sebesar %.2f%% dari bulan lalu.\n", pertumbuhan);
        printf("Jika tren ini berlanjut, prediksi keuntungan bulan depan adalah Rp %ld.\n", prediksi_bulan_depan);
    } else if (pertumbuhan < 0) {
        printf("\nAnalisis: Terjadi penurunan keuntungan sebesar %.2f%% dari bulan lalu.\n", -pertumbuhan);
        printf("Jika tren ini berlanjut, prediksi keuntungan bulan depan adalah Rp %ld.\n", prediksi_bulan_depan);
    } else {
        printf("\nAnalisis: Keuntungan stabil dibandingkan bulan lalu.\n");
        printf("Prediksi keuntungan bulan depan adalah Rp %ld.\n", prediksi_bulan_depan);
    }
} 