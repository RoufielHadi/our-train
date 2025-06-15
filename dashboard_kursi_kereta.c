/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_kursi_kereta.h"
#include "implementasi_kursi_kereta.h"
#include "clear.h"
#include <ctype.h>

// *** FUNGSI UTAMA DASHBOARD KURSI ***
void MenuKursiKereta(const char* id_kereta, const char* tanggal, int* nomor_gerbong_dipilih, char* kode_kursi_dipilih) {
    /* 
    Fungsi utama untuk menampilkan dashboard manajemen kursi kereta
    id_kereta: ID kereta yang akan dikelola
    tanggal: tanggal perjalanan kereta
    nomor_gerbong_dipilih: pointer untuk menyimpan nomor gerbong yang dipilih
    kode_kursi_dipilih: pointer untuk menyimpan kode kursi yang dipilih
    */
    
    // Variabel untuk menyimpan pilihan menu dan input lainnya
    int pilihan;
    int nomor_gerbong = 1; // Default ke gerbong 1
    char kode_kursi[5] = ""; // Inisialisasi string kosong
    char segmen_awal[MAX_NAMA_SEGMEN];
    char segmen_akhir[MAX_NAMA_SEGMEN];
    KursiKereta kereta;
    boolean kursi_dipilih = FALSE; // Flag untuk menandai apakah kursi sudah dipilih
    int i; // Moved variable declaration outside the loops
    int idx_awal, idx_akhir; // Moved variable declarations outside the loops
    
    // Ambil data kereta dari database
    if (!BacaKeretaDariDatabase(&kereta, id_kereta, tanggal)) {
        printf("Error: Data kereta dengan ID %s pada tanggal %s tidak ditemukan\n", id_kereta, tanggal);
        TungguInput();
        return;
    }
    
    while (1) {
        // Bersihkan layar dan tampilkan header
        clearScreen();
        TampilkanHeaderMenu("MANAJEMEN KURSI KERETA");
        
        // Tampilkan informasi kereta
        printf("\n=== INFORMASI KERETA ===\n");
        printf("ID Kereta: %s\n", id_kereta);
        printf("Jenis: %s\n", GetNamaJenisKereta(GetJenisKeretaById(id_kereta)));
        printf("Tanggal: %s\n", tanggal);
        printf("Jumlah Gerbong: %d\n", kereta.jumlah_gerbong);
        
        // Tampilkan kursi yang dipilih jika ada
        if (kursi_dipilih) {
            printf("\n=== KURSI YANG DIPILIH ===\n");
            printf("Gerbong: %d\n", nomor_gerbong);
            printf("Kursi: %s\n", kode_kursi);
        }
        
        // Tampilkan menu utama
        printf("\n=== MENU PILIHAN ===\n");
        printf("1. Lihat Daftar Gerbong\n");
        printf("2. Tampilkan Denah Kursi\n");
        printf("3. Pesan Kursi\n");
        printf("4. Batalkan Pemesanan Kursi\n");
        printf("5. Lihat Statistik Penumpang\n");
        printf("0. Kembali dan Simpan Pilihan Kursi\n");
        
        printf("\nPilihan Anda: ");
        scanf("%d", &pilihan);
        while (getchar() != '\n'); // Bersihkan buffer
        
        switch (pilihan) {
            case 1: // Lihat Daftar Gerbong
                clearScreen();
                TampilkanHeaderMenu("DAFTAR GERBONG");
                printf("\nID Kereta: %s | Tanggal: %s\n", id_kereta, tanggal);
                
                // Gunakan fungsi dari implementasi_kursi_kereta.c
                TampilkanDaftarGerbong(kereta);
                
                TungguInput();
                break;
                
            case 2: // Tampilkan Denah Kursi
                clearScreen();
                TampilkanHeaderMenu("DENAH KURSI KERETA");
                printf("\nID Kereta: %s | Tanggal: %s\n", id_kereta, tanggal);
                
                // Pilih gerbong
                printf("\nMasukkan nomor gerbong (1-%d): ", kereta.jumlah_gerbong);
                scanf("%d", &nomor_gerbong);
                while (getchar() != '\n'); // Bersihkan buffer
                
                if (nomor_gerbong < 1 || nomor_gerbong > kereta.jumlah_gerbong) {
                    printf("Error: Nomor gerbong tidak valid\n");
                    TungguInput();
                    break;
                }
                
                // Pilih segmen perjalanan
                if (kereta.jumlah_segmen == 0) {
                    printf("Error: Data segmen tidak tersedia\n");
                    TungguInput();
                    break;
                }
                
                printf("\n=== SEGMEN PERJALANAN ===\n");
                for (i = 0; i < kereta.jumlah_segmen; i++) {
                    printf("%d. %s\n", i + 1, kereta.segmen[i].nama);
                }
                
                printf("\nPilih segmen awal (1-%d): ", kereta.jumlah_segmen);
                scanf("%d", &idx_awal);
                while (getchar() != '\n'); // Bersihkan buffer
                
                printf("Pilih segmen akhir (1-%d): ", kereta.jumlah_segmen);
                scanf("%d", &idx_akhir);
                while (getchar() != '\n'); // Bersihkan buffer
                
                // Validasi input segmen
                if (idx_awal < 1 || idx_awal > kereta.jumlah_segmen ||
                    idx_akhir < 1 || idx_akhir > kereta.jumlah_segmen ||
                    idx_awal > idx_akhir) {
                    printf("Error: Pilihan segmen tidak valid\n");
                    TungguInput();
                    break;
                }
                
                // Konversi ke index 0-based
                idx_awal--;
                idx_akhir--;
                
                // Gunakan fungsi dari implementasi_kursi_kereta.c
                TampilkanKursiTersediaUntukRute(kereta, nomor_gerbong,
                                               kereta.segmen[idx_awal].nama,
                                               kereta.segmen[idx_akhir].nama);
                
                TungguInput();
                break;
                
            case 3: // Pesan Kursi
                clearScreen();
                TampilkanHeaderMenu("PEMESANAN KURSI");
                printf("\nID Kereta: %s | Tanggal: %s\n", id_kereta, tanggal);
                
                // Pilih gerbong
                printf("\nMasukkan nomor gerbong (1-%d): ", kereta.jumlah_gerbong);
                scanf("%d", &nomor_gerbong);
                while (getchar() != '\n'); // Bersihkan buffer
                
                if (nomor_gerbong < 1 || nomor_gerbong > kereta.jumlah_gerbong) {
                    printf("Error: Nomor gerbong tidak valid\n");
                    TungguInput();
                    break;
                }
                
                // Pilih kursi
                printf("\nMasukkan kode kursi (contoh: A1, B5): ");
                scanf("%4s", kode_kursi);
                while (getchar() != '\n'); // Bersihkan buffer
                
                // Pilih segmen perjalanan
                printf("\n=== SEGMEN PERJALANAN ===\n");
                for (i = 0; i < kereta.jumlah_segmen; i++) {
                    printf("%d. %s\n", i + 1, kereta.segmen[i].nama);
                }
                
                printf("\nPilih segmen awal (1-%d): ", kereta.jumlah_segmen);
                scanf("%d", &idx_awal);
                while (getchar() != '\n'); // Bersihkan buffer
                
                printf("Pilih segmen akhir (1-%d): ", kereta.jumlah_segmen);
                scanf("%d", &idx_akhir);
                while (getchar() != '\n'); // Bersihkan buffer
                
                // Validasi input segmen
                if (idx_awal < 1 || idx_awal > kereta.jumlah_segmen ||
                    idx_akhir < 1 || idx_akhir > kereta.jumlah_segmen ||
                    idx_awal > idx_akhir) {
                    printf("Error: Pilihan segmen tidak valid\n");
                    TungguInput();
                    break;
                }
                
                // Konversi ke index 0-based
                idx_awal--;
                idx_akhir--;
                
                // Simpan nama segmen
                strncpy(segmen_awal, kereta.segmen[idx_awal].nama, MAX_NAMA_SEGMEN - 1);
                strncpy(segmen_akhir, kereta.segmen[idx_akhir].nama, MAX_NAMA_SEGMEN - 1);
                segmen_awal[MAX_NAMA_SEGMEN - 1] = '\0';
                segmen_akhir[MAX_NAMA_SEGMEN - 1] = '\0';
                
                // Cek ketersediaan kursi menggunakan fungsi dari implementasi_kursi_kereta.c
                if (!CekKursiTersedia(kereta, nomor_gerbong, kode_kursi, segmen_awal, segmen_akhir)) {
                    printf("\nMaaf, kursi %s pada gerbong %d untuk rute %s - %s tidak tersedia\n",
                           kode_kursi, nomor_gerbong, segmen_awal, segmen_akhir);
                    TungguInput();
                    break;
                }
                
                // Proses pembayaran dan konfirmasi
                printf("\n=== KONFIRMASI PEMESANAN ===\n");
                printf("Kereta: %s\n", id_kereta);
                printf("Tanggal: %s\n", tanggal);
                printf("Gerbong: %d\n", nomor_gerbong);
                printf("Kursi: %s\n", kode_kursi);
                printf("Rute: %s - %s\n", segmen_awal, segmen_akhir);
                
                printf("\nLanjutkan pemesanan? (Y/N): ");
                char konfirmasi;
                scanf(" %c", &konfirmasi);
                while (getchar() != '\n'); // Bersihkan buffer
                
                if (konfirmasi == 'Y' || konfirmasi == 'y') {
                    // Gunakan fungsi dari implementasi_kursi_kereta.c
                    if (KonfirmasiPembayaranDanReservasi(&kereta, nomor_gerbong, kode_kursi,
                                                        segmen_awal, segmen_akhir)) {
                        printf("\nPemesanan berhasil! Kursi %s pada gerbong %d telah direservasi\n",
                               kode_kursi, nomor_gerbong);
                        
                        // Simpan perubahan ke database
                        if (SimpanKeretaKeDatabase(kereta)) {
                            printf("Data berhasil disimpan ke database\n");
                            // Set flag kursi dipilih
                            kursi_dipilih = TRUE;
                        } else {
                            printf("Gagal menyimpan data ke database\n");
                        }
                    } else {
                        printf("\nGagal melakukan reservasi kursi\n");
                    }
                } else {
                    printf("\nPemesanan dibatalkan\n");
                }
                
                TungguInput();
                break;
                
            case 4: // Batalkan Pemesanan Kursi
                clearScreen();
                TampilkanHeaderMenu("PEMBATALAN KURSI");
                printf("\nID Kereta: %s | Tanggal: %s\n", id_kereta, tanggal);
                
                // Pilih gerbong
                printf("\nMasukkan nomor gerbong (1-%d): ", kereta.jumlah_gerbong);
                scanf("%d", &nomor_gerbong);
                while (getchar() != '\n'); // Bersihkan buffer
                
                if (nomor_gerbong < 1 || nomor_gerbong > kereta.jumlah_gerbong) {
                    printf("Error: Nomor gerbong tidak valid\n");
                    TungguInput();
                    break;
                }
                
                // Pilih kursi
                printf("\nMasukkan kode kursi (contoh: A1, B5): ");
                scanf("%4s", kode_kursi);
                while (getchar() != '\n'); // Bersihkan buffer
                
                // Pilih segmen perjalanan
                printf("\n=== SEGMEN PERJALANAN ===\n");
                for (i = 0; i < kereta.jumlah_segmen; i++) {
                    printf("%d. %s\n", i + 1, kereta.segmen[i].nama);
                }
                
                printf("\nPilih segmen awal (1-%d): ", kereta.jumlah_segmen);
                scanf("%d", &idx_awal);
                while (getchar() != '\n'); // Bersihkan buffer
                
                printf("Pilih segmen akhir (1-%d): ", kereta.jumlah_segmen);
                scanf("%d", &idx_akhir);
                while (getchar() != '\n'); // Bersihkan buffer
                
                // Validasi input segmen
                if (idx_awal < 1 || idx_awal > kereta.jumlah_segmen ||
                    idx_akhir < 1 || idx_akhir > kereta.jumlah_segmen ||
                    idx_awal > idx_akhir) {
                    printf("Error: Pilihan segmen tidak valid\n");
                    TungguInput();
                    break;
                }
                
                // Konversi ke index 0-based
                idx_awal--;
                idx_akhir--;
                
                // Simpan nama segmen
                strncpy(segmen_awal, kereta.segmen[idx_awal].nama, MAX_NAMA_SEGMEN - 1);
                strncpy(segmen_akhir, kereta.segmen[idx_akhir].nama, MAX_NAMA_SEGMEN - 1);
                segmen_awal[MAX_NAMA_SEGMEN - 1] = '\0';
                segmen_akhir[MAX_NAMA_SEGMEN - 1] = '\0';
                
                // Konfirmasi pembatalan
                printf("\n=== KONFIRMASI PEMBATALAN ===\n");
                printf("Kereta: %s\n", id_kereta);
                printf("Tanggal: %s\n", tanggal);
                printf("Gerbong: %d\n", nomor_gerbong);
                printf("Kursi: %s\n", kode_kursi);
                printf("Rute: %s - %s\n", segmen_awal, segmen_akhir);
                
                printf("\nLanjutkan pembatalan? (Y/N): ");
                scanf(" %c", &konfirmasi);
                while (getchar() != '\n'); // Bersihkan buffer
                
                if (konfirmasi == 'Y' || konfirmasi == 'y') {
                    // Konversi kode kursi menjadi baris dan kolom
                    int baris, kolom;
                    if (KonversiKodeKursi(kode_kursi, &baris, &kolom)) {
                        // Gunakan fungsi dari implementasi_kursi_kereta.c
                        if (BatalkanReservasiPerjalanan(&kereta, nomor_gerbong, baris, kolom,
                                                       segmen_awal, segmen_akhir)) {
                            printf("\nPembatalan berhasil! Kursi %s pada gerbong %d telah dibatalkan\n",
                                   kode_kursi, nomor_gerbong);
                            
                            // Simpan perubahan ke database
                            if (SimpanKeretaKeDatabase(kereta)) {
                                printf("Data berhasil disimpan ke database\n");
                            } else {
                                printf("Gagal menyimpan data ke database\n");
                            }
                        } else {
                            printf("\nGagal melakukan pembatalan kursi\n");
                        }
                    } else {
                        printf("\nFormat kode kursi tidak valid\n");
                    }
                } else {
                    printf("\nPembatalan dibatalkan\n");
                }
                
                TungguInput();
                break;
                
            case 5: // Lihat Statistik Penumpang
                clearScreen();
                TampilkanHeaderMenu("STATISTIK PENUMPANG");
                printf("\nID Kereta: %s | Tanggal: %s\n", id_kereta, tanggal);
                
                // Gunakan fungsi dari implementasi_kursi_kereta.c
                TampilkanStatistikPenumpang(kereta);
                
                TungguInput();
                break;
                
            case 0: // Kembali ke Menu Utama
                if (nomor_gerbong_dipilih != NULL && kode_kursi_dipilih != NULL) {
                    // Simpan pilihan terakhir ke parameter output
                    *nomor_gerbong_dipilih = nomor_gerbong;
                    strcpy(kode_kursi_dipilih, kode_kursi);
                    
                    // Konfirmasi pilihan kursi
                    if (kursi_dipilih) {
                        printf("\nAnda telah memilih kursi %s pada gerbong %d\n", 
                               kode_kursi, nomor_gerbong);
                    } else {
                        printf("\nPerhatian: Anda belum memilih kursi\n");
                    }
                    TungguInput();
                }
                return;
                
            default:
                printf("\nPilihan tidak valid. Silakan pilih kembali.\n");
                TungguInput();
        }
        
        // Setiap kali kembali ke menu utama, muat ulang data kereta dari database
        // untuk mendapatkan data terbaru
        if (!BacaKeretaDariDatabase(&kereta, id_kereta, tanggal)) {
            printf("Error: Data kereta dengan ID %s pada tanggal %s tidak ditemukan\n", id_kereta, tanggal);
            TungguInput();
            return;
        }
    }
}

// *** FUNGSI NAVIGASI MENU ***
void TampilkanHeaderMenu(const char* judul) {
    /*
    Menampilkan header menu dengan judul yang diberikan
    */
    printf("===================================================\n");
    printf("=                OUR TRAIN SYSTEM                 =\n");
    printf("===================================================\n");
    printf("=                   %s", judul);
    
    // Padding untuk membuat header simetris
    int i;
    int padding = 35 - strlen(judul);
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("=\n");
    
    printf("===================================================\n");
}

void TampilkanFooterMenu() {
    /*
    Menampilkan footer menu
    */
    printf("===================================================\n");
    printf("=              TERIMA KASIH                       =\n");
    printf("===================================================\n");
}

void TungguInput() {
    /*
    Menunggu input dari pengguna untuk melanjutkan
    */
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}
