/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi_riwayat.h"
#include <time.h>

// *** OPERASI PENCATATAN RIWAYAT ***
void CatatRiwayatPembelian(StackRiwayat *S, User user, InformasiKereta kereta, 
                          int nomor_gerbong, int nomor_kursi) {
    // Buat objek RiwayatTiket baru
    RiwayatTiket tiketBaru;
    
    // Salin data user ke UserRiwayat
    strcpy(tiketBaru.riwayat_user.nama, user.nama);
    strcpy(tiketBaru.riwayat_user.email, user.email);
    strcpy(tiketBaru.riwayat_user.nomor_telepon, user.nomor_telepon);
    
    // Salin data kereta ke KeretaRiwayat
    strcpy(tiketBaru.riwayat_kereta.kode_kereta, kereta.id_Kereta);
    strcpy(tiketBaru.riwayat_kereta.nama_kereta, kereta.nama_kereta);
    strcpy(tiketBaru.riwayat_kereta.stasiun_asal, "");  // Isi sesuai kebutuhan
    strcpy(tiketBaru.riwayat_kereta.stasiun_tujuan, ""); // Isi sesuai kebutuhan
    strcpy(tiketBaru.riwayat_kereta.jam_berangkat, ""); // Isi sesuai kebutuhan
    strcpy(tiketBaru.riwayat_kereta.jam_tiba, ""); // Isi sesuai kebutuhan
    strcpy(tiketBaru.riwayat_kereta.tanggal_berangkat, ""); // Isi sesuai kebutuhan
    
    // Set jenis kereta berdasarkan jenis_layanan
    strcpy(tiketBaru.riwayat_kereta.kelas, kereta.jenis_layanan);
    
    tiketBaru.riwayat_kereta.harga = kereta.harga_tiket;
    
    tiketBaru.riwayat_nomor_gerbong = nomor_gerbong;
    tiketBaru.riwayat_nomor_kursi = nomor_kursi;
    
    // Dapatkan waktu saat ini
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    
    // Set waktu pemesanan
    tiketBaru.riwayat_waktu_pemesanan.detik = local_time->tm_sec;
    tiketBaru.riwayat_waktu_pemesanan.menit = local_time->tm_min;
    tiketBaru.riwayat_waktu_pemesanan.jam = local_time->tm_hour;
    tiketBaru.riwayat_waktu_pemesanan.hari = local_time->tm_mday;
    tiketBaru.riwayat_waktu_pemesanan.bulan = local_time->tm_mon + 1; // tm_mon dimulai dari 0
    tiketBaru.riwayat_waktu_pemesanan.tahun = local_time->tm_year + 1900; // tm_year dimulai dari 1900
    
    // Push ke stack riwayat
    PushRiwayat(S, tiketBaru);
    
    printf("Riwayat pembelian tiket berhasil dicatat.\n");
}

// *** OPERASI PENCARIAN DAN FILTER ***
StackRiwayat CariRiwayatByUser(StackRiwayat S, User user) {
    StackRiwayat hasil, temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&hasil);
    CreateStackRiwayat(&temp);
    
    // Salin stack awal ke temp agar urutan tetap sama
    addressRiwayat P = S.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Cari riwayat yang sesuai dengan pengguna
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            // Bandingkan berdasarkan ID user atau nama
            if (strcmp(tiket.riwayat_user.nama, user.nama) == 0) {
                PushRiwayat(&hasil, tiket);
            }
        }
    }
    
    return hasil;
}

StackRiwayat CariRiwayatByKereta(StackRiwayat S, InformasiKereta kereta) {
    StackRiwayat hasil, temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&hasil);
    CreateStackRiwayat(&temp);
    
    // Salin stack awal ke temp agar urutan tetap sama
    addressRiwayat P = S.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Cari riwayat yang sesuai dengan kereta
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            // Bandingkan berdasarkan ID kereta atau nama
            if (strcmp(tiket.riwayat_kereta.nama_kereta, kereta.nama_kereta) == 0) {
                PushRiwayat(&hasil, tiket);
            }
        }
    }
    
    return hasil;
}

// Fungsi untuk membandingkan waktu (a < b)
boolean IsWaktuLebihAwalRiwayat(Waktu a, Waktu b) {
    if (a.tahun < b.tahun) return TRUE;
    if (a.tahun > b.tahun) return FALSE;
    
    if (a.bulan < b.bulan) return TRUE;
    if (a.bulan > b.bulan) return FALSE;
    
    if (a.hari < b.hari) return TRUE;
    if (a.hari > b.hari) return FALSE;
    
    if (a.jam < b.jam) return TRUE;
    if (a.jam > b.jam) return FALSE;
    
    if (a.menit < b.menit) return TRUE;
    if (a.menit > b.menit) return FALSE;
    
    return a.detik < b.detik;
}

// Fungsi untuk membandingkan waktu (a <= b)
boolean IsWaktuLebihAwalAtauSama(Waktu a, Waktu b) {
    if (a.tahun < b.tahun) return TRUE;
    if (a.tahun > b.tahun) return FALSE;
    
    if (a.bulan < b.bulan) return TRUE;
    if (a.bulan > b.bulan) return FALSE;
    
    if (a.hari < b.hari) return TRUE;
    if (a.hari > b.hari) return FALSE;
    
    if (a.jam < b.jam) return TRUE;
    if (a.jam > b.jam) return FALSE;
    
    if (a.menit < b.menit) return TRUE;
    if (a.menit > b.menit) return FALSE;
    
    return a.detik <= b.detik;
}

StackRiwayat FilterRiwayatByWaktu(StackRiwayat S, Waktu waktu_awal, Waktu waktu_akhir) {
    StackRiwayat hasil, temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&hasil);
    CreateStackRiwayat(&temp);
    
    // Salin stack awal ke temp agar urutan tetap sama
    addressRiwayat P = S.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Filter riwayat berdasarkan rentang waktu
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            // Cek apakah waktu pemesanan berada dalam rentang
            if (IsWaktuLebihAwalAtauSama(waktu_awal, tiket.riwayat_waktu_pemesanan) && 
                IsWaktuLebihAwalAtauSama(tiket.riwayat_waktu_pemesanan, waktu_akhir)) {
                PushRiwayat(&hasil, tiket);
            }
        }
    }
    
    return hasil;
}

// *** OPERASI TAMPILAN ***
void TampilkanRiwayatPengguna(StackRiwayat S, User user) {
    StackRiwayat hasil = CariRiwayatByUser(S, user);
    
    printf("\n=== RIWAYAT PEMBELIAN TIKET PENGGUNA: %s ===\n", user.nama);
    
    if (isEmptyStackRiwayat(hasil)) {
        printf("Tidak ada riwayat pembelian untuk pengguna ini.\n");
    } else {
        TampilStackRiwayat(hasil);
    }
    
    // Bersihkan stack hasil
    DeAlokasiStackRiwayat(&hasil);
}

void TampilkanRingkasanRiwayat(StackRiwayat S) {
    if (isEmptyStackRiwayat(S)) {
        printf("Tidak ada riwayat pembelian.\n");
        return;
    }
    
    int total_pembelian = NbElmtStackRiwayat(S);
    
    // Buat stack sementara untuk analisis
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin stack awal ke temp
    addressRiwayat P = S.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Hitung jumlah pengguna unik
    char pengguna_unik[100][100]; // Asumsi maksimal 100 pengguna unik
    int jumlah_pengguna_unik = 0;
    
    // Hitung jumlah kereta unik
    char kereta_unik[100][100]; // Asumsi maksimal 100 kereta unik
    int jumlah_kereta_unik = 0;
    
    // Tampung waktu pembelian terbaru dan terlama
    Waktu waktu_terbaru, waktu_terlama;
    boolean first = TRUE;
    
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            // Cek pengguna unik
            boolean pengguna_ada = FALSE;
            int i;
            for (i = 0; i < jumlah_pengguna_unik; i++) {
                if (strcmp(pengguna_unik[i], tiket.riwayat_user.nama) == 0) {
                    pengguna_ada = TRUE;
                    break;
                }
            }
            if (!pengguna_ada && jumlah_pengguna_unik < 100) {
                strcpy(pengguna_unik[jumlah_pengguna_unik], tiket.riwayat_user.nama);
                jumlah_pengguna_unik++;
            }
            
            // Cek kereta unik
            boolean kereta_ada = FALSE;
            for (i = 0; i < jumlah_kereta_unik; i++) {
                if (strcmp(kereta_unik[i], tiket.riwayat_kereta.nama_kereta) == 0) {
                    kereta_ada = TRUE;
                    break;
                }
            }
            if (!kereta_ada && jumlah_kereta_unik < 100) {
                strcpy(kereta_unik[jumlah_kereta_unik], tiket.riwayat_kereta.nama_kereta);
                jumlah_kereta_unik++;
            }
            
            // Cek waktu pembelian
            if (first) {
                waktu_terbaru = tiket.riwayat_waktu_pemesanan;
                waktu_terlama = tiket.riwayat_waktu_pemesanan;
                first = FALSE;
            } else {
                if (IsWaktuLebihAwalRiwayat(waktu_terbaru, tiket.riwayat_waktu_pemesanan)) {
                    waktu_terbaru = tiket.riwayat_waktu_pemesanan;
                }
                if (IsWaktuLebihAwalRiwayat(tiket.riwayat_waktu_pemesanan, waktu_terlama)) {
                    waktu_terlama = tiket.riwayat_waktu_pemesanan;
                }
            }
        }
    }
    
    // Tampilkan ringkasan
    printf("\n=== RINGKASAN RIWAYAT PEMBELIAN TIKET ===\n");
    printf("Total Pembelian    : %d tiket\n", total_pembelian);
    printf("Jumlah Pengguna    : %d pengguna\n", jumlah_pengguna_unik);
    printf("Jumlah Kereta      : %d kereta\n", jumlah_kereta_unik);
    
    if (!first) {
        printf("Pembelian Terbaru  : %02d/%02d/%04d %02d:%02d:%02d\n",
               waktu_terbaru.hari, waktu_terbaru.bulan, waktu_terbaru.tahun,
               waktu_terbaru.jam, waktu_terbaru.menit, waktu_terbaru.detik);
        
        printf("Pembelian Terlama  : %02d/%02d/%04d %02d:%02d:%02d\n",
               waktu_terlama.hari, waktu_terlama.bulan, waktu_terlama.tahun,
               waktu_terlama.jam, waktu_terlama.menit, waktu_terlama.detik);
    }
    
    printf("\nDaftar Pengguna yang Membeli Tiket:\n");
    int i;
    for (i = 0; i < jumlah_pengguna_unik; i++) {
        printf("- %s\n", pengguna_unik[i]);
    }
    
    printf("\nDaftar Kereta yang Dibeli Tiketnya:\n");
    for (i = 0; i < jumlah_kereta_unik; i++) {
        printf("- %s\n", kereta_unik[i]);
    }
}

void ExportRiwayatToCSV(StackRiwayat S, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
    
    // Tulis header CSV
    fprintf(file, "Nama_Pengguna,Nama_Kereta,Gerbong,Kursi,Tanggal,Waktu\n");
    
    // Buat stack sementara untuk mempertahankan urutan
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin stack awal ke temp
    addressRiwayat P = S.top;
    while (P != NULL) {
        PushRiwayat(&temp, P->info);
        P = P->next;
    }
    
    // Tulis data ke CSV
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            fprintf(file, "%s,%s,%d,%d,%02d/%02d/%04d,%02d:%02d:%02d\n",
                   tiket.riwayat_user.nama,
                   tiket.riwayat_kereta.nama_kereta,
                   tiket.riwayat_nomor_gerbong,
                   tiket.riwayat_nomor_kursi,
                   tiket.riwayat_waktu_pemesanan.hari,
                   tiket.riwayat_waktu_pemesanan.bulan,
                   tiket.riwayat_waktu_pemesanan.tahun,
                   tiket.riwayat_waktu_pemesanan.jam,
                   tiket.riwayat_waktu_pemesanan.menit,
                   tiket.riwayat_waktu_pemesanan.detik);
        }
    }
    
    fclose(file);
    printf("Riwayat berhasil diekspor ke file CSV: %s\n", filename);
}

// *** OPERASI ADMINISTRATIF ***
void HapusRiwayatSebelumTanggal(StackRiwayat *S, Waktu batas_waktu) {
    // Jika stack kosong, tidak perlu melakukan apa-apa
    if (isEmptyStackRiwayat(*S)) {
        return;
    }
    
    // Buat stack sementara untuk menyimpan riwayat yang akan dipertahankan
    StackRiwayat temp;
    RiwayatTiket tiket;
    
    CreateStackRiwayat(&temp);
    
    // Salin riwayat yang waktunya lebih dari atau sama dengan batas waktu
    while (!isEmptyStackRiwayat(*S)) {
        if (PopRiwayat(S, &tiket)) {
            if (!IsWaktuLebihAwalAtauSama(tiket.riwayat_waktu_pemesanan, batas_waktu)) {
                PushRiwayat(&temp, tiket);
            }
        }
    }
    
    // Salin kembali ke stack asli untuk mempertahankan urutan
    while (!isEmptyStackRiwayat(temp)) {
        if (PopRiwayat(&temp, &tiket)) {
            PushRiwayat(S, tiket);
        }
    }
    
    printf("Riwayat pembelian sebelum tanggal %02d/%02d/%04d berhasil dihapus.\n",
           batas_waktu.hari, batas_waktu.bulan, batas_waktu.tahun);
}

int HitungJumlahRiwayatPengguna(StackRiwayat S, User user) {
    StackRiwayat hasil = CariRiwayatByUser(S, user);
    int jumlah = NbElmtStackRiwayat(hasil);
    
    // Bersihkan stack hasil
    DeAlokasiStackRiwayat(&hasil);
    
    return jumlah;
}

// *** FUNGSI VALIDASI ***
boolean IsRiwayatValid(RiwayatTiket tiket) {
    // Validasi data user
    if (strlen(tiket.riwayat_user.nama) == 0) {
        return FALSE; // Nama pengguna kosong
    }
    
    // Validasi data kereta
    if (strlen(tiket.riwayat_kereta.nama_kereta) == 0) {
        return FALSE; // Nama kereta kosong
    }
    
    // Validasi nomor gerbong dan kursi
    if (tiket.riwayat_nomor_gerbong <= 0 || tiket.riwayat_nomor_kursi <= 0) {
        return FALSE; // Nomor gerbong atau kursi tidak valid
    }
    
    // Validasi waktu pemesanan
    if (tiket.riwayat_waktu_pemesanan.tahun < 2000 || 
        tiket.riwayat_waktu_pemesanan.bulan < 1 || tiket.riwayat_waktu_pemesanan.bulan > 12 ||
        tiket.riwayat_waktu_pemesanan.hari < 1 || tiket.riwayat_waktu_pemesanan.hari > 31) {
        return FALSE; // Tanggal tidak valid
    }
    
    return TRUE; // Semua validasi lulus
} 
