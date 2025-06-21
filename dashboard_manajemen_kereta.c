/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "dashboard_manajemen_kereta.h"
#include "implementasi_informasi_kereta.h"
#include "databases.h"
#include "dashboard_manajemen_jadwal.h"
#include "implementasi_jadwal_kereta.h"

// Implementasi fungsi-fungsi yang digunakan di dashboard
void DashboardTampilkanDaftarKereta() {
	clearScreen();
	printf("\n====== DAFTAR KERETA ======\n");
	
	// Ambil semua data kereta dari database
	Record keretaRecords[100];
	int jumlahKereta = 0;
	DaftarKereta(keretaRecords, &jumlahKereta);
	
	if (jumlahKereta == 0) {
		printf("Belum ada kereta yang tersimpan.\n");
		return;
	}
	
	printf("+=======+===============+=======================+==============+==============+===============+\n");
	printf("| No.   | ID Kereta     | Nama Kereta          | Jenis Layanan| Harga Tiket  | Jumlah Gerbong|\n");
	printf("+=======+===============+=======================+==============+==============+===============+\n");
	
	int i;
	for (i = 0; i < jumlahKereta; i++) {
		char* kodeKereta = AmbilNilai(&keretaRecords[i], "kodeKereta");
		char* namaKereta = AmbilNilai(&keretaRecords[i], "namaKereta");
		char* jenisLayanan = AmbilNilai(&keretaRecords[i], "jenisLayanan");
		char* hargaTiket = AmbilNilai(&keretaRecords[i], "hargaTiket");
		char* jumlahGerbong = AmbilNilai(&keretaRecords[i], "jumlahGerbong");
		
		// Konversi harga ke float untuk format yang konsisten
		float harga = 0.0;
		if (hargaTiket) harga = atof(hargaTiket);
		
		printf("| %-5d | %-13s | %-21s | %-12s | Rp %-9.2f | %-13s |\n", 
			   i+1, 
			   kodeKereta ? kodeKereta : "N/A", 
			   namaKereta ? namaKereta : "N/A", 
			   jenisLayanan ? jenisLayanan : "N/A",
			   harga,
			   jumlahGerbong ? jumlahGerbong : "N/A");
	}
	
	printf("+=======+===============+=======================+==============+==============+===============+\n");
}

void DashboardTambahKereta() {
	clearScreen();
	printf("\n====== TAMBAH KERETA BARU ======\n");
	
	// Meminta input dari user
	char idKereta[10];
	char namaKereta[50];
	char jenisLayanan[20];
	float hargaTiket;
	char jumlahGerbong[5];
	boolean valid;
	
	// Input dan validasi ID Kereta
	do {
		clearScreen();
		printf("\n====== TAMBAH KERETA BARU ======\n");
		printf("Format ID Kereta: KXXX (X adalah digit)\n\n");
		
		printf("Masukkan ID Kereta: ");
		scanf("%s", idKereta); while(getchar()!='\n');
		
		// Validasi ID kereta
		valid = TRUE;
		if (!ValidasiIDKereta(idKereta)) {
			printf("Error: Format ID kereta tidak valid! Format yang benar: KXXX (X adalah digit)\n");
			printf("Tekan Enter untuk mencoba lagi...");
			getchar();
			valid = FALSE;
			continue;
		}
		
		// Cek apakah ID kereta sudah ada
		Record existingKereta;
		InisialisasiRecord(&existingKereta);
		if (valid && BacaInformasiKereta(&existingKereta, idKereta)) {
			printf("Error: Kereta dengan ID %s sudah ada!\n", idKereta);
			printf("Tekan Enter untuk mencoba lagi...");
			getchar();
			valid = FALSE;
		}
	} while (!valid);
	
	// Input nama kereta
	clearScreen();
	printf("\n====== TAMBAH KERETA BARU ======\n");
	printf("ID Kereta: %s\n\n", idKereta);
	
	printf("Masukkan Nama Kereta: ");
	scanf("%[^\n]", namaKereta); while(getchar()!='\n');
	
	// Input dan validasi jenis layanan
	do {
		clearScreen();
		printf("\n====== TAMBAH KERETA BARU ======\n");
		printf("ID Kereta: %s\n", idKereta);
		printf("Nama Kereta: %s\n\n", namaKereta);
		
		printf("Jenis Layanan (%s/%s/%s/%s): ", STR_EKONOMI, STR_BISNIS, STR_EKSEKUTIF, STR_LUXURY);
		scanf("%[^\n]", jenisLayanan); while(getchar()!='\n');
		
		valid = TRUE;
		// Validasi jenis layanan
		if (!ValidasiJenisLayanan(jenisLayanan)) {
			printf("Error: Jenis layanan tidak valid! Gunakan %s, %s, %s, atau %s\n", 
				   STR_EKONOMI, STR_BISNIS, STR_EKSEKUTIF, STR_LUXURY);
			printf("Tekan Enter untuk mencoba lagi...");
			getchar();
			valid = FALSE;
		}
	} while (!valid);
	
	// Input dan validasi harga tiket
	do {
		clearScreen();
		printf("\n====== TAMBAH KERETA BARU ======\n");
		printf("ID Kereta: %s\n", idKereta);
		printf("Nama Kereta: %s\n", namaKereta);
		printf("Jenis Layanan: %s\n\n", jenisLayanan);
		
		printf("Masukkan Harga Tiket (Rp): ");
		scanf("%f", &hargaTiket); while(getchar()!='\n');
		
		valid = TRUE;
		if (hargaTiket <= 0) {
			printf("Error: Harga tiket harus lebih dari 0!\n");
			printf("Tekan Enter untuk mencoba lagi...");
			getchar();
			valid = FALSE;
		}
	} while (!valid);
	
	// Input jumlah gerbong
	do {
		clearScreen();
		printf("\n====== TAMBAH KERETA BARU ======\n");
		printf("ID Kereta: %s\n", idKereta);
		printf("Nama Kereta: %s\n", namaKereta);
		printf("Jenis Layanan: %s\n", jenisLayanan);
		printf("Harga Tiket: Rp %.2f\n\n", hargaTiket);
		
		printf("Masukkan Jumlah Gerbong: ");
		scanf("%s", jumlahGerbong); while(getchar()!='\n');
		
		valid = TRUE;
		// Validasi jumlah gerbong (harus angka positif)
		int jumlah = atoi(jumlahGerbong);
		if (jumlah <= 0) {
			printf("Error: Jumlah gerbong harus berupa angka positif!\n");
			printf("Tekan Enter untuk mencoba lagi...");
			getchar();
			valid = FALSE;
		}
	} while (!valid);
	
	// Tampilkan ringkasan data kereta
	clearScreen();
	printf("\n====== RINGKASAN DATA KERETA ======\n");
	printf("ID Kereta     : %s\n", idKereta);
	printf("Nama Kereta   : %s\n", namaKereta);
	printf("Jenis Layanan : %s\n", jenisLayanan);
	printf("Harga Tiket   : Rp %.2f\n", hargaTiket);
	printf("Jumlah Gerbong: %s\n\n", jumlahGerbong);
	
	printf("Konfirmasi penyimpanan data (Y/N): ");
	char konfirmasi;
	scanf(" %c", &konfirmasi); while(getchar()!='\n');
	
	if (konfirmasi == 'Y' || konfirmasi == 'y') {
		// Simpan data ke database
		Record keretaRecord;
		InisialisasiRecord(&keretaRecord);
		
		TambahField(&keretaRecord, "kodeKereta", idKereta);
		TambahField(&keretaRecord, "namaKereta", namaKereta);
		TambahField(&keretaRecord, "jenisLayanan", jenisLayanan);
		
		// Konversi harga ke string
		char hargaStr[20];
		sprintf(hargaStr, "%.2f", hargaTiket);
		TambahField(&keretaRecord, "hargaTiket", hargaStr);
		
		TambahField(&keretaRecord, "jumlahGerbong", jumlahGerbong);
		
		if (SimpanInformasiKereta(&keretaRecord)) {
			printf("Kereta berhasil ditambahkan!\n");
			printf("Tekan Enter untuk melanjutkan...");
			getchar();
			TambahJadwalKereta(idKereta);
		} else {
			printf("Error: Gagal menyimpan informasi kereta!\n");
		}
	} else {
		printf("Penambahan kereta dibatalkan.\n");
	}
	return;
}

void DashboardEditKereta() {
	clearScreen();
	printf("\n====== EDIT DATA KERETA ======\n");
	
	// Tampilkan daftar kereta terlebih dahulu
	DashboardTampilkanDaftarKereta();
	
	char idKereta[10];
	int pilihan_index;
	
	printf("\nMasukkan ID Kereta yang ingin diedit (contoh: KA123 bukan nomor baris): ");
	scanf("%s", idKereta); while(getchar()!='\n');
	
	// Jika user memasukkan nomor indeks bukan kode kereta
	if (idKereta[0] >= '0' && idKereta[0] <= '9') {
		printf("Anda memasukkan nomor baris, bukan ID kereta! Gunakan format KA123.\n");
		printf("\nTekan Enter untuk kembali..."); 
		getchar();
		return;
	}
	
	// Baca data kereta dari database
	Record keretaRecord;
	InisialisasiRecord(&keretaRecord);
	
	if (!BacaInformasiKereta(&keretaRecord, idKereta)) {
		printf("Error: Kereta dengan ID %s tidak ditemukan!\n", idKereta);
		printf("\nTekan Enter untuk kembali..."); 
		getchar();
		return;
	}
	
	// Tampilkan data kereta yang akan diedit
	char* namaKereta = AmbilNilai(&keretaRecord, "namaKereta");
	char* jenisLayanan = AmbilNilai(&keretaRecord, "jenisLayanan");
	char* hargaTiketStr = AmbilNilai(&keretaRecord, "hargaTiket");
	char* jumlahGerbong = AmbilNilai(&keretaRecord, "jumlahGerbong");
	
	printf("\n====== DATA KERETA SAAT INI ======\n");
	printf("ID Kereta     : %s\n", idKereta);
	printf("Nama Kereta   : %s\n", namaKereta ? namaKereta : "N/A");
	printf("Jenis Layanan : %s\n", jenisLayanan ? jenisLayanan : "N/A");
	printf("Harga Tiket   : %s\n", hargaTiketStr ? hargaTiketStr : "N/A");
	printf("Jumlah Gerbong: %s\n", jumlahGerbong ? jumlahGerbong : "N/A");
	
	// Opsi edit
	printf("\nOpsi Edit:\n");
	printf("1. Edit Nama Kereta\n");
	printf("2. Edit Jenis Layanan\n");
	printf("3. Edit Harga Tiket\n");
	printf("4. Edit Jumlah Gerbong\n");
	printf("5. Kembali\n");
	printf("Pilihan: ");
	
	int pilihan;
	scanf("%d", &pilihan); while(getchar()!='\n');
	
	char dataBaru[50];
	float hargaBaru;
	
	switch (pilihan) {
		case 1:
			printf("Masukkan Nama Kereta Baru: ");
			scanf("%[^\n]", dataBaru); while(getchar()!='\n');
			UbahNilai(&keretaRecord, "namaKereta", dataBaru);
			break;
			
		case 2:
			printf("Masukkan Jenis Layanan Baru (%s/%s/%s/%s): ", 
				   STR_EKONOMI, STR_BISNIS, STR_EKSEKUTIF, STR_LUXURY);
			scanf("%[^\n]", dataBaru); while(getchar()!='\n');
			
			// Validasi jenis layanan
			if (!ValidasiJenisLayanan(dataBaru)) {
				printf("Error: Jenis layanan tidak valid!\n");
				printf("\nTekan Enter untuk kembali..."); 
				getchar();
				return;
			}
			
			UbahNilai(&keretaRecord, "jenisLayanan", dataBaru);
			break;
			
		case 3:
			printf("Masukkan Harga Tiket Baru (Rp): ");
			scanf("%f", &hargaBaru); while(getchar()!='\n');
			
			if (hargaBaru <= 0) {
				printf("Error: Harga tiket harus lebih dari 0!\n");
				printf("\nTekan Enter untuk kembali..."); 
				getchar();
				return;
			}
			
			sprintf(dataBaru, "%.2f", hargaBaru);
			UbahNilai(&keretaRecord, "hargaTiket", dataBaru);
			break;
			
		case 4:
			printf("Masukkan Jumlah Gerbong Baru: ");
			scanf("%s", dataBaru); while(getchar()!='\n');
			UbahNilai(&keretaRecord, "jumlahGerbong", dataBaru);
			break;
			
		case 5:
			return;
			
		default:
			printf("Pilihan tidak valid!\n");
			printf("\nTekan Enter untuk kembali..."); 
			getchar();
			return;
	}
	
	// Update database
	if (UpdateInformasiKereta(&keretaRecord)) {
		printf("Data kereta berhasil diperbarui!\n");
	} else {
		printf("Error: Gagal memperbarui data kereta!\n");
	}
	
	printf("\nTekan Enter untuk kembali..."); 
	getchar();
}

void DashboardHapusKereta() {
	clearScreen();
	printf("\n====== HAPUS KERETA ======\n");
	
	// Tampilkan daftar kereta terlebih dahulu
	DashboardTampilkanDaftarKereta();
	
	char idKereta[10];
	printf("\nMasukkan ID Kereta yang ingin dihapus (contoh: KA123 bukan nomor baris): ");
	scanf("%s", idKereta); while(getchar()!='\n');
	
	// Jika user memasukkan nomor indeks bukan kode kereta
	if (idKereta[0] >= '0' && idKereta[0] <= '9') {
		printf("Anda memasukkan nomor baris, bukan ID kereta! Gunakan format KA123.\n");
		printf("\nTekan Enter untuk kembali..."); 
		getchar();
		return;
	}
	
	// Baca data kereta dari database untuk konfirmasi
	Record keretaRecord;
	InisialisasiRecord(&keretaRecord);
	
	if (!BacaInformasiKereta(&keretaRecord, idKereta)) {
		printf("Error: Kereta dengan ID %s tidak ditemukan!\n", idKereta);
		printf("\nTekan Enter untuk kembali..."); 
		getchar();
		return;
	}
	
	// Tampilkan data kereta yang akan dihapus
	char* namaKereta = AmbilNilai(&keretaRecord, "namaKereta");
	
	printf("\nAnda akan menghapus kereta berikut:\n");
	printf("ID Kereta   : %s\n", idKereta);
	printf("Nama Kereta : %s\n", namaKereta ? namaKereta : "N/A");
	
	char konfirmasi;
	printf("\nApakah Anda yakin ingin menghapus kereta ini? (y/n): ");
	scanf("%c", &konfirmasi);
	
	if (konfirmasi == 'y' || konfirmasi == 'Y') {
		// Hapus jadwal kereta terkait terlebih dahulu
		boolean jadwalDihapus = HapusSemuaJadwalByKereta(idKereta);
		if (jadwalDihapus) {
			printf("Jadwal kereta terkait berhasil dihapus!\n");
		}
		
		// Hapus informasi kereta
		if (HapusInformasiKereta(idKereta)) {
			printf("\nKereta berhasil dihapus!\n");
		} else {
			printf("\nError: Gagal menghapus kereta!\n");
		}
	} else {
		printf("\nPenghapusan kereta dibatalkan.\n");
	}
	
	printf("\nTekan Enter untuk kembali..."); 
	getchar();
}

void TampilkanDaftarKeretaUI(void) {
	clearScreen();
	printf("\n====== DAFTAR KERETA ======\n");
	
	// Ambil semua data kereta dari database
	Record keretaRecords[100];
	int jumlahKereta = 0;
	DaftarKereta(keretaRecords, &jumlahKereta);
	
	if (jumlahKereta == 0) {
		printf("Belum ada kereta yang tersimpan.\n");
	} else {
		printf("+=======+===============+=======================+==============+==============+===============+\n");
		printf("| No.   | ID Kereta     | Nama Kereta          | Jenis Layanan| Harga Tiket  | Jumlah Gerbong|\n");
		printf("+=======+===============+=======================+==============+==============+===============+\n");
		
		int i;
		for (i = 0; i < jumlahKereta; i++) {
			char* kodeKereta = AmbilNilai(&keretaRecords[i], "kodeKereta");
			char* namaKereta = AmbilNilai(&keretaRecords[i], "namaKereta");
			char* jenisLayanan = AmbilNilai(&keretaRecords[i], "jenisLayanan");
			char* hargaTiket = AmbilNilai(&keretaRecords[i], "hargaTiket");
			char* jumlahGerbong = AmbilNilai(&keretaRecords[i], "jumlahGerbong");
			
			// Konversi harga ke float untuk format yang konsisten
			float harga = 0.0;
			if (hargaTiket) harga = atof(hargaTiket);
			
			printf("| %-5d | %-13s | %-21s | %-12s | Rp %-9.2f | %-13s |\n", 
				i+1, 
				kodeKereta ? kodeKereta : "N/A", 
				namaKereta ? namaKereta : "N/A", 
				jenisLayanan ? jenisLayanan : "N/A",
				harga,
				jumlahGerbong ? jumlahGerbong : "N/A");
		}
		
		printf("+=======+===============+=======================+==============+==============+===============+\n");
	}

}

void TampilkanFormTambahKereta() {
	DashboardTambahKereta();
}

void TampilkanFormEditKereta() {
	DashboardEditKereta();
}

void TampilkanFormHapusKereta() {
	DashboardHapusKereta();
}

void MenuManajemenKereta(const char* email) {
	int choice;
	
	do {
		clearScreen();
		printf("+----------------------------------------------+\n");
		printf("|             MANAJEMEN KERETA                 |\n");
		printf("+----------------------------------------------+\n");
		printf("| Menu:                                        |\n");
		printf("|  1. Lihat Daftar Kereta                      |\n");
		printf("|  2. Tambah Kereta Baru                       |\n");
		printf("|  3. Edit Data Kereta                         |\n");
		printf("|  4. Hapus Kereta                             |\n");
		printf("|  5. Kembali ke Menu Admin                    |\n");
		printf("+----------------------------------------------+\n");
		printf("Pilihan: ");
		
		scanf("%d", &choice);
		while(getchar()!='\n'); // Bersihkan buffer
		
		switch (choice) {
			case 1:
				TampilkanDaftarKeretaUI();
				break;
				
			case 2:
				TampilkanFormTambahKereta();
				break;
				
			case 3:
				TampilkanFormEditKereta();
				break;
				
			case 4:
				TampilkanFormHapusKereta();
				break;
				
			case 5:
				return;
				
			default:
				printf("Pilihan tidak valid!\n");
				printf("Tekan Enter untuk melanjutkan..."); 
				getchar();
				break;
		}
	} while (1);
}