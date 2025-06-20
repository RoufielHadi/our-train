#include "dashboard_kursi_kereta.h"
#include "implementasi_kursi_kereta.h"
#include "implementasi_informasi_kereta.h"
#include "clear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Deklarasi eksternal untuk informasi kereta
extern ListKereta globalListKereta;
extern int GetJumlahGerbongById(ListKereta L, const char* id);
extern JenisKereta GetJenisKeretaById(const char* id);
extern const char* GetNamaJenisKereta(JenisKereta jenis);

// ===== FUNGSI UTAMA =====
void MenuKursiKereta(const char* id_kereta,
                     const char* tanggal,
                     const char* stasiun_awal,
                     const char* stasiun_akhir,
                     int* nomor_gerbong_dipilih,
                     char* kode_kursi_dipilih) {
    int nomor_gerbong = 1;
    char kode_kursi[5] = "";
    KursiKereta kereta;
    boolean kursi_dipilih = FALSE;

    // Salin ID dan tanggal ke struktur kursi
    strcpy(kereta.id_kereta, id_kereta);
    strcpy(kereta.tanggal, tanggal);

    // 1. Muat info kereta untuk dapatkan jumlah gerbong
    MuatDataKeretaKeGlobal();
    // Ambil jumlah gerbong dari database informasi umum
    int commonG = GetJumlahGerbongById(globalListKereta, id_kereta);
    // Hitung jumlah gerbong yang tersedia di database kursi sebagai fallback
    int dbG = HitungJumlahGerbongDariFile(id_kereta, tanggal, "kursi_kereta.txt");
    if (commonG <= 0) {
        if (dbG <= 0) {
            printf("Peringatan: Kereta tidak ditemukan, default gerbong=1\n");
            kereta.jumlah_gerbong = 1;
        } else {
            // Gunakan jumlah gerbong dari database kursi jika info umum tidak tersedia
            kereta.jumlah_gerbong = dbG;
        }
    } else {
        // Gunakan jumlah gerbong dari database informasi umum
        kereta.jumlah_gerbong = commonG;
    }

    // 2. Inisialisasi segmen perjalanan dan data kursi berdasarkan jadwal
    {
        JenisKereta jenis = GetJenisKeretaById(id_kereta);
        // Inisialisasi kerangka kursi (jumlah segmen) sesuai jadwal
        InisialisasiKursiDenganJadwal(&kereta, jenis);
        // Muat status kursi dari database (jika ada)
        MuatDataKursiDariFile(&kereta, DB_KURSI_KERETA);
    }

    // 3. Loop interaktif
    while (1) {
        clearScreen();
        TampilkanHeaderMenu("PEMILIHAN KURSI");

        // Tampilkan info ringkas
        printf("\nKereta  : %s (%s)\n",
               id_kereta,
               GetNamaJenisKereta(GetJenisKeretaById(id_kereta)));
        printf("Rute    : %s - %s\n", stasiun_awal, stasiun_akhir);
        printf("Tanggal : %s\n", tanggal);

        // Denah kursi
        printf("\n=== DENAH KURSI GERBONG %d ===\n", nomor_gerbong);
        TampilkanKursiLangsungDariDatabase(
            id_kereta, tanggal, nomor_gerbong, stasiun_awal, stasiun_akhir);

        // Tampilkan pilihan yang sudah dipilih
        if (kursi_dipilih) {
            printf("\nKursi terpilih: %s (gerbong %d)\n",
                   kode_kursi, nomor_gerbong);
        }

        // Menu navigasi
        printf("\n=== MENU ===\n");
        printf("1. Ganti Gerbong\n");
        printf("2. Pilih Kursi\n");
        printf("0. Selesai dan Lanjutkan\n");
        printf("Pilihan Anda: ");
        int pilihan;
        scanf("%d", &pilihan);
        while (getchar() != '\n');

        if (pilihan == 1) {
            // Ganti nomor gerbong
            printf("\nMasukkan nomor gerbong (1-%d): ",
                   kereta.jumlah_gerbong);
            scanf("%d", &nomor_gerbong);
            while (getchar() != '\n');
            if (nomor_gerbong < 1 || nomor_gerbong > kereta.jumlah_gerbong) {
                printf("Error: Nomor gerbong tidak valid\n");
                TungguInput();
                nomor_gerbong = 1;
            }
        }
        else if (pilihan == 2) {
            // Pilih kursi
            printf("\nMasukkan kode kursi (contoh: A1, B5): ");
            scanf("%4s", kode_kursi);
            while (getchar() != '\n');

            // Konfirmasi pilihan
            printf("\n=== KONFIRMASI KURSI ===\n");
            printf("Kereta  : %s\n", id_kereta);
            printf("Tanggal : %s\n", tanggal);
            printf("Gerbong : %d\n", nomor_gerbong);
            printf("Kursi   : %s\n", kode_kursi);
            printf("Rute    : %s - %s\n", stasiun_awal, stasiun_akhir);
            printf("\nKonfirmasi? (Y/N): ");
            char konfirmasi;
            scanf(" %c", &konfirmasi);
            while (getchar() != '\n');

            if (konfirmasi == 'Y' || konfirmasi == 'y') {
                // Panggil PilihKursi untuk semua segmen
                if (PilihKursi(&kereta,
                               nomor_gerbong,
                               kode_kursi,
                               stasiun_awal,
                               stasiun_akhir)) {
                    // Update the seat database file after successful reservation
                    if (!SimpanDataKursiKeFile(&kereta, DB_KURSI_KERETA)) {
                        // Fallback: append a new record if update failed (initial creation)
                        FILE *f = fopen(DB_KURSI_KERETA, "a");
                        if (f) {
                            fprintf(f, "ID_Kereta = '%s' | Gerbong = 'G%d' | Tanggal = '%s' ",
                                    kereta.id_kereta, nomor_gerbong, kereta.tanggal);
                            JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
                            KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
                            int c, r, s;
                            for (c = 0; c < konfig.kolom; c++) {
                                for (r = 0; r < konfig.baris; r++) {
                                    fprintf(f, "| %c%d = '", 'A' + c, r + 1);
                                    for (s = 0; s < kereta.jumlah_segmen; s++) {
                                        fprintf(f, "%s", kereta.data_kursi[nomor_gerbong-1].status_kursi[c][r][s] ? "True" : "False");
                                        if (s + 1 < kereta.jumlah_segmen) fprintf(f, ",");
                                    }
                                    fprintf(f, "' ");
                                }
                            }
                            fprintf(f, "\n");
                            fclose(f);
                        } else {
                            printf("\nWarning: Gagal membuka file %s untuk menambahkan data kursi.\n", DB_KURSI_KERETA);
                        }
                    }
                    kursi_dipilih = TRUE;
                    if (nomor_gerbong_dipilih && kode_kursi_dipilih) {
                        *nomor_gerbong_dipilih = nomor_gerbong;
                        strcpy(kode_kursi_dipilih, kode_kursi);
                    }
                    printf("\nKursi %s berhasil dipilih. Tekan Enter...",
                           kode_kursi);
                    TungguInput();
                    break; // keluar ke pembayaran
                } else {
                    printf("\nError: Kursi %s tidak tersedia. Tekan Enter...",
                           kode_kursi);
                    TungguInput();
                }
            }
        }
        else if (pilihan == 0) {
            if (!kursi_dipilih) {
                printf("\nAnda belum memilih kursi. Yakin lanjut? (Y/N): ");
                char c = getchar();
                while (getchar() != '\n');
                if (c != 'Y' && c != 'y') continue;
            }
            break;
        }
        else {
            printf("Pilihan tidak valid. Tekan Enter...");
            TungguInput();
        }
    }

    TampilkanFooterMenu();
}

// ===== FUNGSI BANTU NAVIGASI =====
void TampilkanHeaderMenu(const char* judul) {
    printf("===================================================\n");
    printf("=                OUR TRAIN SYSTEM                 =\n");
    printf("===================================================\n");
    printf("=                   %s", judul);
    int padding = 35 - strlen(judul);
    int i;
    for ( i = 0; i < padding; i++) printf(" ");
    printf("=\n");
    printf("===================================================\n");
}

void TampilkanFooterMenu() {
    printf("===================================================\n");
    printf("=              TERIMA KASIH                       =\n");
    printf("===================================================\n");
}

void TungguInput() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}
