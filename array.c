/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "array.h"
#include <stdlib.h>
#include <string.h>

/* *** Konstruktor *** */
void InisialisasiArrayKereta(ArrayKereta *arr) {
    arr->jumlah_kereta = 0;
}

/* *** Operasi Dasar *** */
void TambahKereta(ArrayKereta *arr, char *id_kereta, JenisKereta jenis, int jumlah_gerbong) {
    if (arr->jumlah_kereta < MAX_KERETA) {
        // Menyalin ID kereta
        strncpy(arr->data[arr->jumlah_kereta].id_kereta, id_kereta, 9);
        arr->data[arr->jumlah_kereta].id_kereta[9] = '\0';  // Pastikan string berakhir null
        
        // Set jenis kereta dan jumlah gerbong
        arr->data[arr->jumlah_kereta].jenis = jenis;
        
        // Batasi jumlah gerbong sesuai maksimum
        if (jumlah_gerbong > MAX_GERBONG) {
            jumlah_gerbong = MAX_GERBONG;
        }
        arr->data[arr->jumlah_kereta].jumlah_gerbong = jumlah_gerbong;
        
        // Inisialisasi kursi kereta
        InisialisasiKursiKereta(&arr->data[arr->jumlah_kereta]);
        
        // Tambahkan jumlah kereta
        arr->jumlah_kereta++;
    } else {
        printf("Array penuh, tidak bisa menambahkan kereta baru.\n");
    }
}

void HapusKereta(ArrayKereta *arr, int index) {
    if (index >= 0 && index < arr->jumlah_kereta) {
        for (int i = index; i < arr->jumlah_kereta - 1; i++) {
            arr->data[i] = arr->data[i + 1];
        }
        arr->jumlah_kereta--;
    } else {
        printf("Indeks tidak valid.\n");
    }
}

int CariKeretaById(ArrayKereta *arr, char *id_kereta) {
    for (int i = 0; i < arr->jumlah_kereta; i++) {
        if (strcmp(arr->data[i].id_kereta, id_kereta) == 0) {
            return i;
        }
    }
    return -1; // Tidak ditemukan
}

void TampilkanDaftarKereta(ArrayKereta arr) {
    if (arr.jumlah_kereta == 0) {
        printf("Tidak ada kereta yang tersedia.\n");
    } else {
        printf("=== DAFTAR KERETA ===\n");
        printf("No. | ID Kereta | Jenis Kereta     | Jumlah Gerbong | Kapasitas\n");
        printf("------------------------------------------------------------\n");
        
        for (int i = 0; i < arr.jumlah_kereta; i++) {
            KursiKereta kereta = arr.data[i];
            int kapasitas = HitungJumlahKursiKereta(kereta);
            
            printf("%-3d | %-9s | %-16s | %-14d | %-9d\n", 
                   i + 1, 
                   kereta.id_kereta, 
                   GetNamaJenisKereta(kereta.jenis), 
                   kereta.jumlah_gerbong,
                   kapasitas);
        }
    }
}

/* *** Operasi Kursi *** */
void InisialisasiKursiKereta(KursiKereta *kereta) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    for (int g = 0; g < kereta->jumlah_gerbong; g++) {
        kereta->data_kursi[g].nomor_gerbong = g + 1;
        
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                kereta->data_kursi[g].status_kursi[k][b] = FALSE; // Kursi kosong
            }
        }
    }
}

boolean ReservasiKursi(KursiKereta *kereta, int gerbong, int baris, int kolom) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    // Validasi input
    if (gerbong < 1 || gerbong > kereta->jumlah_gerbong ||
        baris < 1 || baris > konfig.baris ||
        kolom < 1 || kolom > konfig.kolom) {
        return FALSE; // Input tidak valid
    }
    
    // Konversi ke indeks array (0-based)
    int g = gerbong - 1;
    int b = baris - 1;
    int k = kolom - 1;
    
    // Cek apakah kursi sudah terisi
    if (kereta->data_kursi[g].status_kursi[k][b]) {
        return FALSE; // Kursi sudah terisi
    }
    
    // Reservasi kursi
    kereta->data_kursi[g].status_kursi[k][b] = TRUE;
    return TRUE;
}

boolean BatalkanReservasi(KursiKereta *kereta, int gerbong, int baris, int kolom) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta->jenis);
    
    // Validasi input
    if (gerbong < 1 || gerbong > kereta->jumlah_gerbong ||
        baris < 1 || baris > konfig.baris ||
        kolom < 1 || kolom > konfig.kolom) {
        return FALSE; // Input tidak valid
    }
    
    // Konversi ke indeks array (0-based)
    int g = gerbong - 1;
    int b = baris - 1;
    int k = kolom - 1;
    
    // Cek apakah kursi memang terisi
    if (!kereta->data_kursi[g].status_kursi[k][b]) {
        return FALSE; // Kursi sudah kosong
    }
    
    // Batalkan reservasi
    kereta->data_kursi[g].status_kursi[k][b] = FALSE;
    return TRUE;
}

boolean CekStatusKursi(KursiKereta kereta, int gerbong, int baris, int kolom) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    
    // Validasi input
    if (gerbong < 1 || gerbong > kereta.jumlah_gerbong ||
        baris < 1 || baris > konfig.baris ||
        kolom < 1 || kolom > konfig.kolom) {
        return FALSE; // Input tidak valid, anggap kursi tidak ada
    }
    
    // Konversi ke indeks array (0-based)
    int g = gerbong - 1;
    int b = baris - 1;
    int k = kolom - 1;
    
    return kereta.data_kursi[g].status_kursi[k][b];
}

void TampilkanKursiGerbong(KursiKereta kereta, int gerbong) {
    if (gerbong < 1 || gerbong > kereta.jumlah_gerbong) {
        printf("Nomor gerbong tidak valid.\n");
        return;
    }
    
    int g = gerbong - 1; // Konversi ke indeks array
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    
    printf("=== DENAH KURSI KERETA %s ===\n", kereta.id_kereta);
    printf("Gerbong: %d | Jenis: %s\n", gerbong, GetNamaJenisKereta(kereta.jenis));
    printf("----------------------------------\n");
    
    // Header kolom (nomor kursi)
    printf("    ");
    for (int k = 0; k < konfig.kolom; k++) {
        printf("%c   ", 'A' + k);
    }
    printf("\n");
    
    // Tampilkan kursi
    for (int b = 0; b < konfig.baris; b++) {
        printf("%2d  ", b + 1); // Nomor baris
        
        for (int k = 0; k < konfig.kolom; k++) {
            char status = kereta.data_kursi[g].status_kursi[k][b] ? 'X' : 'O';
            printf("%c   ", status);
        }
        printf("\n");
    }
    
    printf("\nKeterangan: O = Kursi kosong, X = Kursi terisi\n");
}

/* *** Utilitas *** */
KonfigurasiKursi GetKonfigurasiKursiByJenis(JenisKereta jenis) {
    KonfigurasiKursi konfig;
    
    switch (jenis) {
        case EKONOMI:
            konfig.kolom = 5;
            konfig.baris = 20;
            break;
        case EKONOMI_PREMIUM:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case BISNIS:
            konfig.kolom = 4;
            konfig.baris = 16;
            break;
        case EKSEKUTIF:
            konfig.kolom = 4;
            konfig.baris = 12;
            break;
        case LUXURY:
            konfig.kolom = 3;
            konfig.baris = 10;
            break;
        case PRIORITY:
            konfig.kolom = 3;
            konfig.baris = 12;
            break;
        case SLEEPER:
            konfig.kolom = 2;
            konfig.baris = 10;
            break;
        case COMPARTMENT:
            konfig.kolom = 4;
            konfig.baris = 4;
            break;
        default:
            konfig.kolom = 4;
            konfig.baris = 16;
    }
    
    return konfig;
}

const char* GetNamaJenisKereta(JenisKereta jenis) {
    switch (jenis) {
        case EKONOMI:
            return "Ekonomi";
        case EKONOMI_PREMIUM:
            return "Ekonomi Premium";
        case BISNIS:
            return "Bisnis";
        case EKSEKUTIF:
            return "Eksekutif";
        case LUXURY:
            return "Luxury";
        case PRIORITY:
            return "Priority";
        case SLEEPER:
            return "Sleeper";
        case COMPARTMENT:
            return "Compartment";
        default:
            return "Tidak Dikenal";
    }
}

int HitungJumlahKursiKereta(KursiKereta kereta) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    return kereta.jumlah_gerbong * konfig.kolom * konfig.baris;
}

int HitungJumlahKursiTerisi(KursiKereta kereta) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(kereta.jenis);
    int jumlah = 0;
    
    for (int g = 0; g < kereta.jumlah_gerbong; g++) {
        for (int b = 0; b < konfig.baris; b++) {
            for (int k = 0; k < konfig.kolom; k++) {
                if (kereta.data_kursi[g].status_kursi[k][b]) {
                    jumlah++;
                }
            }
        }
    }
    
    return jumlah;
}

float HitungPersentaseKursiTerisi(KursiKereta kereta) {
    int total = HitungJumlahKursiKereta(kereta);
    if (total == 0) return 0.0;
    
    int terisi = HitungJumlahKursiTerisi(kereta);
    return (float)terisi / total * 100.0;
}


