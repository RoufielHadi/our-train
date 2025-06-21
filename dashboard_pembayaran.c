/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "dashboard_pembayaran.h"
#include "hash_password.h"
#include "tree_biner.h"
#include "databases.h"
#include "implementasi_pembayaran.h"
#include "linked.h"
#include "dashboard_kursi_kereta.h"

// Variabel global untuk menyimpan pohon hash
extern HashPassword* morseTree;

// Helper: baca data pembayaran langsung dari database
static boolean BacaPaymentEmail(const char* email, Payment* hasil) {
    Record rec; InisialisasiRecord(&rec);
    if (BacaRekeningUser(&rec, email)) {
        char* nr = AmbilNilai(&rec, "nomorRekening");
        char* saldo_str = AmbilNilai(&rec, "saldo");
        char* pin_str = AmbilNilai(&rec, "pin");
        strcpy(hasil->email, email);
        strcpy(hasil->no_rekening, nr ? nr : "");
        hasil->saldo = saldo_str ? atoi(saldo_str) : 0;
        strcpy(hasil->pin, pin_str ? pin_str : "");
        return TRUE;
    }
    return FALSE;
}

// *** FUNGSI UTAMA DASHBOARD PEMBAYARAN ***
boolean MenuPembayaran(PembelianTiket* pembelian, const char* email_user) {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|                PEMBAYARAN                   |\n");
    printf("+----------------------------------------------+\n");
    
    // Cek status pembelian
    if (pembelian->status != DATA_PENUMPANG) {
        printf("Error: Tahap pembelian tiket belum sampai ke pembayaran.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return FALSE;
    }

    
    // Tampilkan detail pembayaran
    TampilkanDetailPembayaran(*pembelian);
    
    // Tampilkan saldo user (baca langsung DB)
    {
        Payment p; 
        if (BacaPaymentEmail(email_user, &p)) {
            printf("\n--- INFORMASI SALDO ---\n");
            printf("Email           : %s\n", p.email);
            printf("Nomor Rekening  : %s\n", p.no_rekening);
            printf("Saldo           : Rp %d\n", p.saldo);
        } else {
            printf("\nData pembayaran untuk email %s tidak ditemukan.\n", email_user);
            printf("Silakan isi saldo terlebih dahulu.\n");
            printf("Tekan Enter untuk kembali..."); getchar();
            return FALSE;
        }
    }
    
    // Cek kecukupan saldo langsung DB
    {
        Payment p; BacaPaymentEmail(email_user, &p);
        if (p.saldo < (int)pembelian->tiket_dipilih.harga_tiket) {
            printf("\nSaldo Anda tidak mencukupi untuk melakukan pembayaran.\n");
            printf("Silakan isi saldo terlebih dahulu.\n");
            printf("Tekan Enter untuk kembali..."); getchar();
            return FALSE;
        }
    }
    
    // Konfirmasi pembayaran
    printf("\nLanjutkan pembayaran? (y/n): ");
    char pilihan;
    scanf(" %c", &pilihan);
    while(getchar() != '\n'); // Membersihkan buffer
    
    if (pilihan != 'y' && pilihan != 'Y') {
        printf("Pembayaran dibatalkan.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return FALSE;
    }
    
    // Minta PIN untuk konfirmasi
    char pin[7]; // 6 digit + null terminator
    int percobaan = 0;
    boolean pin_valid = FALSE;
    
    while (percobaan < 3 && !pin_valid) {
        printf("\nMasukkan PIN (6 digit): ");
        fgets(pin, sizeof(pin), stdin);
        pin[strcspn(pin, "\n")] = '\0'; // Hapus newline
        
        // Validasi PIN
        pin_valid = ValidasiPinPembayaran(email_user, pin);
        
        if (!pin_valid) {
            percobaan++;
            printf("PIN salah! Sisa percobaan: %d\n", 3 - percobaan);
            
            if (percobaan >= 3) {
                printf("Anda telah 3 kali salah memasukkan PIN.\n");
                printf("Pembayaran dibatalkan untuk keamanan.\n");
                printf("Tekan Enter untuk kembali...");
                getchar();
                return FALSE;
            }
        }
    }
    
    // Proses pembayaran: langsung update DB
    {
        // Baca record
        Record rec; InisialisasiRecord(&rec);
        if (!BacaRekeningUser(&rec, email_user)) {
            return FALSE;
        }
        // Kurangi saldo di record
        int newSaldo;
        {
            char* saldo_str = AmbilNilai(&rec, "saldo");
            newSaldo = saldo_str ? atoi(saldo_str) - (int)pembelian->tiket_dipilih.harga_tiket : 0;
        }
        char buf[20]; sprintf(buf, "%d", newSaldo);
        UbahNilai(&rec, "saldo", buf);
        // Update DB
        if (!UpdateRekeningUser(&rec)) return FALSE;
    }
    
    // Proses berhasil: update status pembelian dan simpan riwayat
    pembelian->total_bayar = pembelian->tiket_dipilih.harga_tiket;
    pembelian->status = SELESAI;
    // Reserve seat in database now that payment succeeded
    {
        KursiKereta kereta;
        strcpy(kereta.id_kereta, pembelian->tiket_dipilih.id_kereta);
        strcpy(kereta.tanggal, pembelian->tiket_dipilih.tanggal);
        // Determine jumlah_gerbong from existing DB
        kereta.jumlah_gerbong = HitungJumlahGerbongDariFile(kereta.id_kereta,
                                                          kereta.tanggal,
                                                          DB_KURSI_KERETA);
        if (kereta.jumlah_gerbong <= 0) kereta.jumlah_gerbong = 1;
        JenisKereta jenis = GetJenisKeretaById(kereta.id_kereta);
        // Initialize and load current seat data
        InisialisasiKursiDenganJadwal(&kereta, jenis);
        MuatDataKursiDariFile(&kereta, DB_KURSI_KERETA);
        // Mark the purchased seat as reserved
        PilihKursi(&kereta,
                   pembelian->nomor_gerbong,
                   pembelian->kode_kursi,
                   pembelian->tiket_dipilih.stasiun_asal,
                   pembelian->tiket_dipilih.stasiun_tujuan);
        // Save updates to the database file
        if (!SimpanDataKursiKeFile(&kereta, DB_KURSI_KERETA)) {
            printf("\nWarning: Gagal menyimpan status kursi ke database setelah pembayaran.\n");
        }
    }
    // Simpan riwayat pembelian
    if (SimpanRiwayatPembelianTiket(*pembelian)) {
        clearScreen();
        printf("+----------------------------------------------+\n");
        printf("|           PEMBAYARAN BERHASIL               |\n");
        printf("+----------------------------------------------+\n");
        // Tampilkan kode dan total
        printf("Kode Pembelian : %s\n", pembelian->kode_pembelian);
        printf("Total Bayar     : Rp %.2f\n\n", pembelian->total_bayar);
        // Tampilkan detail tiket
        TampilkanDetailPembayaran(*pembelian);
        // Pesan terima kasih
        printf("\nTiket berhasil dibeli!\n");
        printf("Terima kasih telah menggunakan layanan OurTrain.\n");
        // Tunggu sekali tekan Enter
        printf("Tekan Enter untuk kembali..."); getchar();
        return TRUE;
    } else {
        clearScreen();
        printf("+----------------------------------------------+\n");
        printf("|         PEMBAYARAN TIDAK TERSIMPAN          |\n");
        printf("+----------------------------------------------+\n");
        printf("Pembayaran berhasil, tetapi gagal menyimpan riwayat.\n");
        printf("Kode Pembelian : %s\n", pembelian->kode_pembelian);
        printf("Silakan hubungi customer service.\n");
        printf("Tekan Enter untuk kembali..."); getchar();
        return TRUE;
    }
}

// *** FUNGSI PENDUKUNG DASHBOARD PEMBAYARAN ***
void TampilkanDetailPembayaran(PembelianTiket pembelian) {
    printf("\n--- DETAIL PEMBAYARAN ---\n");
    printf("Kereta          : %s (%s)\n", 
           pembelian.tiket_dipilih.id_kereta,
           pembelian.tiket_dipilih.nama_kereta);
    printf("Rute            : %s - %s\n", 
           pembelian.tiket_dipilih.stasiun_asal,
           pembelian.tiket_dipilih.stasiun_tujuan);
    printf("Tanggal         : %s\n", pembelian.tiket_dipilih.tanggal);
    printf("Waktu           : %s - %s\n", 
           pembelian.tiket_dipilih.waktu_berangkat,
           pembelian.tiket_dipilih.waktu_tiba);
    printf("Kursi           : %s (Gerbong %d)\n", 
           pembelian.kode_kursi,
           pembelian.nomor_gerbong);
    printf("Penumpang       : %s\n", pembelian.nama_penumpang);
    printf("Jenis Layanan   : %s\n", pembelian.tiket_dipilih.jenis_layanan);
    printf("Harga Tiket     : Rp %.2f\n", pembelian.tiket_dipilih.harga_tiket);
}

boolean ValidasiPinPembayaran(const char* email_user, const char* pin) {
    // Baca langsung record untuk validasi
    Record rec; InisialisasiRecord(&rec);
    if (!BacaRekeningUser(&rec, email_user)) return FALSE;
    char* pin_str = AmbilNilai(&rec, "pin");
    char* hashed = HashPasswordWithMorse(morseTree, pin);
    boolean ok = pin_str && strcmp(pin_str, hashed) == 0;
    free(hashed);
    return ok;
}

boolean CekSaldoCukup(const char* email_user, float total_bayar) {
    Record rec; InisialisasiRecord(&rec);
    if (!BacaRekeningUser(&rec, email_user)) return FALSE;
    char* saldo_str = AmbilNilai(&rec, "saldo");
    int saldo = saldo_str ? atoi(saldo_str):0;
    return saldo >= (int)total_bayar;
}