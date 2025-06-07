/*
Author: Devi Maulani 
NIM: 241524007
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi_kursi_kereta.h"

// *** OPERASI PENGELOLAAN GERBONG ***
void TambahGerbong(KursiKereta *kereta, int jumlah_gerbong_baru) {
    // Validasi input
    if (jumlah_gerbong_baru <= 0) {
        printf("Jumlah gerbong yang ditambahkan harus positif.\n");
        return;
    }
    
    // Cek apakah melebihi batas maksimum
    int total_gerbong = kereta->jumlah_gerbong + jumlah_gerbong_baru;
    if (total_gerbong > MAX_GERBONG) {
        printf("Tidak dapat menambahkan gerbong. Maksimum gerbong adalah %d.\n", MAX_GERBONG);
        return;
    }
    
    // Simpan jumlah gerbong awal
    int gerbong_awal = kereta->jumlah_gerbong;
    
    // Update jumlah gerbong
    kereta->jumlah_gerbong = total_gerbong;
    
    // Inisialisasi gerbong baru
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    for (int g = gerbong_awal; g < total_gerbong; g++) {
        kereta->data_kursi[g].nomor_gerbong = g + 1;
        
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                kereta->data_kursi[g].status_kursi[k][b] = FALSE; // Kursi kosong
            }
        }
    }
    
    printf("Berhasil menambahkan %d gerbong baru. Total gerbong sekarang: %d.\n", 
           jumlah_gerbong_baru, kereta->jumlah_gerbong);
}

void KurangiGerbong(KursiKereta *kereta, int jumlah_gerbong_dikurangi) {
    // Validasi input
    if (jumlah_gerbong_dikurangi <= 0) {
        printf("Jumlah gerbong yang dikurangi harus positif.\n");
        return;
    }
    
    // Cek apakah gerbong cukup untuk dikurangi
    if (jumlah_gerbong_dikurangi >= kereta->jumlah_gerbong) {
        printf("Tidak dapat mengurangi gerbong. Kereta harus memiliki minimal 1 gerbong.\n");
        return;
    }
    
    // Hitung jumlah kursi terisi pada gerbong yang akan dihapus
    int kursi_terisi = 0;
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    for (int g = kereta->jumlah_gerbong - jumlah_gerbong_dikurangi; g < kereta->jumlah_gerbong; g++) {
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                if (kereta->data_kursi[g].status_kursi[k][b]) {
                    kursi_terisi++;
                }
            }
        }
    }
    
    // Beri peringatan jika ada kursi terisi yang akan dihapus
    if (kursi_terisi > 0) {
        printf("Peringatan: %d kursi yang terisi akan dihapus.\n", kursi_terisi);
    }
    
    // Update jumlah gerbong
    kereta->jumlah_gerbong -= jumlah_gerbong_dikurangi;
    
    printf("Berhasil mengurangi %d gerbong. Total gerbong sekarang: %d.\n", 
           jumlah_gerbong_dikurangi, kereta->jumlah_gerbong);
}

void UbahJenisKereta(KursiKereta *kereta, JenisKereta jenis_baru) {
    // Simpan data jenis lama
    JenisKereta jenis_lama = kereta->jenis;
    KonfigurasiKursi konfig_lama = GetKonfigurasiKursiByJenis(jenis_lama);
    
    // Update jenis kereta
    kereta->jenis = jenis_baru;
    KonfigurasiKursi konfig_baru = GetKonfigurasiKursiByJenis(jenis_baru);
    
    // Hitung jumlah kursi terisi yang akan hilang
    int kursi_terisi_hilang = 0;
    
    for (int g = 0; g < kereta->jumlah_gerbong; g++) {
        for (int b = 0; b < konfig_lama.baris; b++) {
            for (int k = 0; k < konfig_lama.kolom; k++) {
                // Jika kursi terisi dan berada di luar batas konfigurasi baru
                if (kereta->data_kursi[g].status_kursi[k][b] && 
                    (b >= konfig_baru.baris || k >= konfig_baru.kolom)) {
                    kursi_terisi_hilang++;
                }
            }
        }
    }
    
    // Inisialisasi ulang status kursi sesuai dengan konfigurasi baru
    for (int g = 0; g < kereta->jumlah_gerbong; g++) {
        // Reset status kursi di area yang sudah ada
        for (int b = 0; b < konfig_baru.baris; b++) {
            for (int k = 0; k < konfig_baru.kolom; k++) {
                // Pertahankan status kursi jika dalam batas konfigurasi lama
                if (b < konfig_lama.baris && k < konfig_lama.kolom) {
                    // Status tidak berubah
                } else {
                    // Inisialisasi kursi baru sebagai kosong
                    kereta->data_kursi[g].status_kursi[k][b] = FALSE;
                }
            }
        }
    }
    
    printf("Jenis kereta berhasil diubah dari %s menjadi %s.\n", 
           GetNamaJenisKereta(jenis_lama), GetNamaJenisKereta(jenis_baru));
    
    if (kursi_terisi_hilang > 0) {
        printf("Perhatian: %d kursi terisi hilang karena perubahan konfigurasi.\n", kursi_terisi_hilang);
    }
}

// *** OPERASI MANAJEMEN KURSI ***
boolean ReservasiKursiOtomatis(KursiKereta *kereta, int *gerbong, int *baris, int *kolom) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    // Cari kursi kosong pertama
    for (int g = 0; g < kereta->jumlah_gerbong; g++) {
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                if (!kereta->data_kursi[g].status_kursi[k][b]) {
                    // Kursi kosong ditemukan
                    kereta->data_kursi[g].status_kursi[k][b] = TRUE; // Reservasi
                    
                    // Konversi indeks ke nomor (1-based)
                    *gerbong = g + 1;
                    *baris = b + 1;
                    *kolom = k + 1;
                    
                    return TRUE;
                }
            }
        }
    }
    
    // Tidak ada kursi kosong
    return FALSE;
}

boolean ReservasiKursiBerurutan(KursiKereta *kereta, int jumlah_kursi, int *gerbong, int *baris_awal, int *kolom_awal) {
    if (jumlah_kursi <= 0) {
        printf("Jumlah kursi harus positif.\n");
        return FALSE;
    }
    
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    // Cari kursi berurutan dalam satu baris
    for (int g = 0; g < kereta->jumlah_gerbong; g++) {
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k <= konfig.kolom - jumlah_kursi; k++) {
                boolean available = TRUE;
                
                // Cek apakah ada jumlah_kursi kursi kosong berurutan
                for (int i = 0; i < jumlah_kursi; i++) {
                    if (kereta->data_kursi[g].status_kursi[k + i][b]) {
                        available = FALSE;
                        break;
                    }
                }
                
                if (available) {
                    // Reservasi kursi berurutan
                    for (int i = 0; i < jumlah_kursi; i++) {
                        kereta->data_kursi[g].status_kursi[k + i][b] = TRUE;
                    }
                    
                    // Konversi indeks ke nomor (1-based)
                    *gerbong = g + 1;
                    *baris_awal = b + 1;
                    *kolom_awal = k + 1;
                    
                    return TRUE;
                }
            }
        }
    }
    
    // Tidak menemukan kursi berurutan yang cukup
    return FALSE;
}

boolean PindahKursi(KursiKereta *kereta, int gerbong_lama, int baris_lama, int kolom_lama, 
                    int gerbong_baru, int baris_baru, int kolom_baru) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    // Validasi input
    if (gerbong_lama < 1 || gerbong_lama > kereta->jumlah_gerbong ||
        baris_lama < 1 || baris_lama > konfig.baris ||
        kolom_lama < 1 || kolom_lama > konfig.kolom ||
        gerbong_baru < 1 || gerbong_baru > kereta->jumlah_gerbong ||
        baris_baru < 1 || baris_baru > konfig.baris ||
        kolom_baru < 1 || kolom_baru > konfig.kolom) {
        return FALSE; // Input tidak valid
    }
    
    // Konversi ke indeks array (0-based)
    int g_lama = gerbong_lama - 1;
    int b_lama = baris_lama - 1;
    int k_lama = kolom_lama - 1;
    
    int g_baru = gerbong_baru - 1;
    int b_baru = baris_baru - 1;
    int k_baru = kolom_baru - 1;
    
    // Cek apakah kursi lama memang terisi
    if (!kereta->data_kursi[g_lama].status_kursi[k_lama][b_lama]) {
        return FALSE; // Kursi lama tidak terisi
    }
    
    // Cek apakah kursi baru kosong
    if (kereta->data_kursi[g_baru].status_kursi[k_baru][b_baru]) {
        return FALSE; // Kursi baru sudah terisi
    }
    
    // Pindahkan reservasi
    kereta->data_kursi[g_lama].status_kursi[k_lama][b_lama] = FALSE;
    kereta->data_kursi[g_baru].status_kursi[k_baru][b_baru] = TRUE;
    
    return TRUE;
}

// *** OPERASI STATISTIK ***
int HitungKetersediaanKursiGerbong(KursiKereta kereta, int gerbong) {
    if (gerbong < 1 || gerbong > kereta.jumlah_gerbong) {
        return -1; // Gerbong tidak valid
    }
    
    int g = gerbong - 1; // Konversi ke indeks array
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    int total_kursi = konfig.kolom * konfig.baris;
    int kursi_terisi = 0;
    
    for (int b = 0; b < konfig.baris; b++) {
        for (int k = 0; k < konfig.kolom; k++) {
            if (kereta.data_kursi[g].status_kursi[k][b]) {
                kursi_terisi++;
            }
        }
    }
    
    return total_kursi - kursi_terisi;
}

int HitungKetersediaanKursiTotal(KursiKereta kereta) {
    int total = HitungJumlahKursiKereta(kereta);
    int terisi = HitungJumlahKursiTerisi(kereta);
    return total - terisi;
}

float HitungPersentaseKetersediaanGerbong(KursiKereta kereta, int gerbong) {
    if (gerbong < 1 || gerbong > kereta.jumlah_gerbong) {
        return -1.0; // Gerbong tidak valid
    }
    
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    int total_kursi = konfig.kolom * konfig.baris;
    int kursi_tersedia = HitungKetersediaanKursiGerbong(kereta, gerbong);
    
    return (float)kursi_tersedia / total_kursi * 100.0;
}

// *** OPERASI DISPLAY KHUSUS ***
void TampilkanStatistikKereta(KursiKereta kereta) {
    int total_kursi = HitungJumlahKursiKereta(kereta);
    int kursi_terisi = HitungJumlahKursiTerisi(kereta);
    int kursi_tersedia = total_kursi - kursi_terisi;
    float persentase_terisi = HitungPersentaseKursiTerisi(kereta);
    
    printf("=== STATISTIK KERETA %s ===\n", kereta.id_kereta);
    printf("Jenis Kereta   : %s\n", GetNamaJenisKereta(kereta.jenis));
    printf("Jumlah Gerbong : %d\n", kereta.jumlah_gerbong);
    printf("Total Kursi    : %d\n", total_kursi);
    printf("Kursi Terisi   : %d (%.2f%%)\n", kursi_terisi, persentase_terisi);
    printf("Kursi Tersedia : %d (%.2f%%)\n", kursi_tersedia, 100.0 - persentase_terisi);
    
    printf("\nStatistik per Gerbong:\n");
    printf("Gerbong | Kursi Tersedia | Persentase Tersedia\n");
    printf("----------------------------------------------\n");
    
    for (int g = 1; g <= kereta.jumlah_gerbong; g++) {
        int tersedia = HitungKetersediaanKursiGerbong(kereta, g);
        float persen = HitungPersentaseKetersediaanGerbong(kereta, g);
        printf("%-7d | %-14d | %.2f%%\n", g, tersedia, persen);
    }
}

void TampilkanDiagramOkupansiKereta(KursiKereta kereta) {
    printf("=== DIAGRAM OKUPANSI KERETA %s ===\n", kereta.id_kereta);
    printf("Jenis Kereta: %s\n\n", GetNamaJenisKereta(kereta.jenis));
    
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    
    for (int g = 1; g <= kereta.jumlah_gerbong; g++) {
        printf("Gerbong %d:\n", g);
        TampilkanKursiGerbong(kereta, g);
        printf("\n");
    }
}

void ExportDaftarPenumpang(KursiKereta kereta, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuat file %s\n", filename);
        return;
    }
    
    fprintf(file, "DAFTAR KURSI TERISI KERETA %s\n", kereta.id_kereta);
    fprintf(file, "Jenis Kereta: %s\n", GetNamaJenisKereta(kereta.jenis));
    fprintf(file, "Jumlah Gerbong: %d\n\n", kereta.jumlah_gerbong);
    
    fprintf(file, "Gerbong | Baris | Kolom\n");
    fprintf(file, "-----------------------\n");
    
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    int jumlah_terisi = 0;
    
    for (int g = 0; g < kereta.jumlah_gerbong; g++) {
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                if (kereta.data_kursi[g].status_kursi[k][b]) {
                    fprintf(file, "%-7d | %-5d | %c\n", 
                           g + 1, b + 1, 'A' + k);
                    jumlah_terisi++;
                }
            }
        }
    }
    
    fprintf(file, "\nTotal Kursi Terisi: %d\n", jumlah_terisi);
    
    fclose(file);
    printf("Daftar kursi terisi berhasil diekspor ke file %s\n", filename);
}

// *** OPERASI ADMINISTRATIF ***
void ResetSeluruhKursi(KursiKereta *kereta) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    for (int g = 0; g < kereta->jumlah_gerbong; g++) {
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                kereta->data_kursi[g].status_kursi[k][b] = FALSE; // Kursi kosong
            }
        }
    }
    
    printf("Seluruh kursi kereta %s berhasil direset.\n", kereta->id_kereta);
}

void BlokKursiUntukMaintenance(KursiKereta *kereta, int gerbong, int baris_awal, int baris_akhir) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    // Validasi input
    if (gerbong < 1 || gerbong > kereta->jumlah_gerbong ||
        baris_awal < 1 || baris_awal > konfig.baris ||
        baris_akhir < baris_awal || baris_akhir > konfig.baris) {
        printf("Input tidak valid.\n");
        return;
    }
    
    int g = gerbong - 1; // Konversi ke indeks array
    int kursi_terisi_diblokir = 0;
    
    for (int b = baris_awal - 1; b <= baris_akhir - 1; b++) {
        for (int k = 0; k < konfig.kolom; k++) {
            if (kereta->data_kursi[g].status_kursi[k][b]) {
                kursi_terisi_diblokir++;
            }
            kereta->data_kursi[g].status_kursi[k][b] = TRUE; // Blokir kursi
        }
    }
    
    printf("Baris %d-%d pada gerbong %d berhasil diblokir untuk maintenance.\n", 
           baris_awal, baris_akhir, gerbong);
    
    if (kursi_terisi_diblokir > 0) {
        printf("Perhatian: %d kursi yang sudah terisi terpaksa diblokir.\n", kursi_terisi_diblokir);
    }
} 