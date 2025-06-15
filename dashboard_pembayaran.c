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

// Variabel global untuk menyimpan pohon hash
extern HashPassword morseTree;
// Variabel global untuk menyimpan list pembayaran
extern ListPayment globalListPayment;

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
    
    // Tampilkan saldo user
    TampilkanSaldoUser(email_user);
    
    // Cek kecukupan saldo
    if (!CekSaldoCukup(email_user, pembelian->tiket_dipilih.harga_tiket)) {
        printf("\nSaldo Anda tidak mencukupi untuk melakukan pembayaran.\n");
        printf("Silakan isi saldo terlebih dahulu.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return FALSE;
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
    
    // Proses pembayaran
    if (ProsesPembayaran(email_user, pembelian->tiket_dipilih.harga_tiket)) {
        // Update total bayar dan status pembelian
        pembelian->total_bayar = pembelian->tiket_dipilih.harga_tiket;
        pembelian->status = SELESAI;
        
        // Simpan riwayat pembelian
        if (SimpanRiwayatPembelianTiket(*pembelian)) {
            clearScreen();
            printf("+----------------------------------------------+\n");
            printf("|           PEMBAYARAN BERHASIL               |\n");
            printf("+----------------------------------------------+\n");
            printf("Kode Pembelian: %s\n", pembelian->kode_pembelian);
            printf("Total Pembayaran: Rp %.2f\n", pembelian->total_bayar);
            printf("\nTiket berhasil dibeli!\n");
            printf("Terima kasih telah menggunakan layanan OurTrain.\n");
            printf("\nTekan Enter untuk kembali...");
            getchar();
            return TRUE;
        } else {
            printf("\nPembayaran berhasil, tetapi gagal menyimpan riwayat pembelian.\n");
            printf("Silakan hubungi customer service dengan kode pembelian: %s\n", pembelian->kode_pembelian);
            printf("\nTekan Enter untuk kembali...");
            getchar();
            return TRUE;
        }
    } else {
        printf("\nTerjadi kesalahan dalam proses pembayaran.\n");
        printf("Silakan coba lagi nanti.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return FALSE;
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
    printf("Nomor Identitas : %s\n", pembelian.nomor_identitas);
    printf("Jenis Layanan   : %s\n", pembelian.tiket_dipilih.jenis_layanan);
    printf("Harga Tiket     : Rp %.2f\n", pembelian.tiket_dipilih.harga_tiket);
}

boolean ProsesPembayaran(const char* email_user, float total_bayar) {
	
    // Konversi float ke int (dalam sen)
    int jumlah_bayar = (int)(total_bayar * 100);
    
    // Gunakan fungsi KurangiSaldo dari implementasi_pembayaran.h
    // Karena PIN sudah divalidasi sebelumnya, kita bisa menggunakan PIN kosong
    char empty_pin[] = "";
    return KurangiSaldo(&globalListPayment, (char*)email_user, empty_pin, jumlah_bayar / 100);

}

void TampilkanSaldoUser(const char* email_user) {
    // Cari data pembayaran user
    Payment payment_user;
    char email_copy[100];
    strcpy(email_copy, email_user);
    if (CariDataPembayaran(globalListPayment, email_copy, &payment_user)) {
        printf("\n--- INFORMASI SALDO ---\n");
        printf("Email           : %s\n", payment_user.email);
        printf("Nomor Rekening  : %s\n", payment_user.no_rekening);
        printf("Saldo           : Rp %d\n", payment_user.saldo);
    } else {
        printf("\nData pembayaran untuk email %s tidak ditemukan.\n", email_user);
    }
}

boolean ValidasiPinPembayaran(const char* email_user, const char* pin) {
    // Gunakan fungsi ValidasiPIN dari implementasi_pembayaran.h
    // Buat salinan parameter konstan ke non-konstan
    char email_copy[100];
    char pin_copy[10];
    
    strcpy(email_copy, email_user);
    strcpy(pin_copy, pin);
    
    return ValidasiPIN(globalListPayment, email_copy, pin_copy, &morseTree);
}

boolean CekSaldoCukup(const char* email_user, float total_bayar) {
    // Konversi float ke int (dalam sen)
    int jumlah_bayar = (int)(total_bayar * 100);
    
    // Gunakan fungsi CekKecukupanSaldo dari implementasi_pembayaran.h
    char email_copy[100];
    strcpy(email_copy, email_user);
    return CekKecukupanSaldo(globalListPayment, email_copy, jumlah_bayar / 100);
}
