/*
Author: Devi Maulani
NIM: 241524007
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "array.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Windows compatibility - define strcasecmp as _stricmp if not defined
#ifdef _WIN32
  #define strcasecmp _stricmp
#endif

/* *** Konstruktor *** */
void InisialisasiArrayKereta(ArrayKereta *arr) {
    arr->jumlah_kereta = 0;
}

/* *** Operasi Dasar *** */
void TambahKereta(ArrayKereta *arr, char *id_kereta, int jumlah_gerbong, char *tanggal, InfoSegmen *segmen_list, int jumlah_segmen) {
    if (arr->jumlah_kereta >= MAX_KERETA) {
        printf("Error: Array kereta sudah penuh\n");
        return;
    }
    
    // Inisialisasi kereta baru
    KursiKereta *kereta = &(arr->data[arr->jumlah_kereta]);
    
    // Salin ID kereta
    strncpy(kereta->id_kereta, id_kereta, 9);
    kereta->id_kereta[9] = '\0';
    
    // Salin tanggal
    strncpy(kereta->tanggal, tanggal, 10);
    kereta->tanggal[10] = '\0';
    
    // Set jumlah gerbong
    kereta->jumlah_gerbong = (jumlah_gerbong <= MAX_GERBONG) ? jumlah_gerbong : MAX_GERBONG;
    
    // Salin informasi segmen
    int i;
    kereta->jumlah_segmen = (jumlah_segmen <= MAX_SEGMEN) ? jumlah_segmen : MAX_SEGMEN;
    for (i = 0; i < kereta->jumlah_segmen; i++) {
        strncpy(kereta->segmen[i].nama, segmen_list[i].nama, MAX_NAMA_SEGMEN - 1);
        kereta->segmen[i].nama[MAX_NAMA_SEGMEN - 1] = '\0';
    }
    
    // Inisialisasi kursi kereta
    JenisKereta jenis = GetJenisKeretaFromString(id_kereta);
    InisialisasiKursiKereta(kereta, jenis);
    
    // Tambahkan ke array
    arr->jumlah_kereta++;
}

void HapusKereta(ArrayKereta *arr, int index) {
    if (index < 0 || index >= arr->jumlah_kereta) {
        printf("Error: Indeks kereta tidak valid\n");
        return;
    }
    
    // Geser semua elemen setelah index ke kiri
    int i;
    for (i = index; i < arr->jumlah_kereta - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    // Kurangi jumlah kereta
    arr->jumlah_kereta--;
}

int CariKeretaById(ArrayKereta *arr, char *id_kereta) {
	int i;
    for (i = 0; i < arr->jumlah_kereta; i++) {
        if (strcmp(arr->data[i].id_kereta, id_kereta) == 0) {
            return i;
        }
    }
    return -1;
}

void TampilkanDaftarKereta(ArrayKereta arr) {
    printf("\n=== DAFTAR KERETA ===\n");
    printf("%-10s | %-15s | %-10s\n", "ID", "Jenis", "Gerbong");
    printf("-----------------------------------------\n");
    
    int i;
    for (i = 0; i < arr.jumlah_kereta; i++) {
        JenisKereta jenis = GetJenisKeretaFromString(arr.data[i].id_kereta);
        printf("%-10s | %-15s | %-10d\n", 
               arr.data[i].id_kereta, 
               GetNamaJenisKereta(jenis),
               arr.data[i].jumlah_gerbong);
    }
    
    printf("-----------------------------------------\n");
}

/* *** Operasi Kursi *** */
void InisialisasiKursiKereta(KursiKereta *kereta, JenisKereta jenis) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    
    int g;
    for (g = 0; g < kereta->jumlah_gerbong; g++) {
        kereta->data_kursi[g].nomor_gerbong = g + 1;
        
        int k,b,s; 
        for (k = 0; k < konfig.kolom; k++) {
            for (b = 0; b < konfig.baris; b++) {
                for (s = 0; s < kereta->jumlah_segmen; s++) {
                    // Default: kursi tersedia
                    kereta->data_kursi[g].status_kursi[k][b][s] = TRUE;
                }
            }
        }
    }
}

boolean ReservasiKursi(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_idx) {
    // Validasi parameter
    if (gerbong < 1 || gerbong > kereta->jumlah_gerbong) {
        printf("Error: Nomor gerbong tidak valid\n");
        return FALSE;
    }
    JenisKereta jenis = GetJenisKeretaFromString(kereta->id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    if (baris < 0 || baris >= konfig.baris || kolom < 0 || kolom >= konfig.kolom) {
        printf("Error: Posisi kursi tidak valid\n");
        return FALSE;
    }
    if (segmen_idx < 0 || segmen_idx >= kereta->jumlah_segmen) {
        printf("Error: Indeks segmen tidak valid\n");
        return FALSE;
    }
    // Cek apakah kursi tersedia
    if (!kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][segmen_idx]) {
        printf("Error: Kursi sudah terisi\n");
        return FALSE;
    }
    // Reservasi kursi (set menjadi terisi)
    kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][segmen_idx] = FALSE;
    return TRUE;
}

boolean ReservasiKursiMultiSegmen(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_awal, int segmen_akhir) {
    // Validasi parameter
    if (segmen_awal < 0 || segmen_awal >= kereta->jumlah_segmen ||
        segmen_akhir < 0 || segmen_akhir >= kereta->jumlah_segmen ||
        segmen_awal > segmen_akhir) {
        printf("Error: Indeks segmen tidak valid\n");
        return FALSE;
    }
    // Cek apakah kursi tersedia untuk semua segmen
    int s;
    for (s = segmen_awal; s <= segmen_akhir; s++) {
        if (!kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][s]) {
            printf("Error: Kursi sudah terisi pada segmen %s\n", kereta->segmen[s].nama);
            return FALSE;
        }
    }
    // Reservasi kursi untuk semua segmen (set menjadi terisi)
    for (s = segmen_awal; s <= segmen_akhir; s++) {
        kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][s] = FALSE;
    }
    return TRUE;
}

boolean BatalkanReservasi(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_idx) {
    // Validasi parameter
    if (gerbong < 1 || gerbong > kereta->jumlah_gerbong) {
        printf("Error: Nomor gerbong tidak valid\n");
        return FALSE;
    }
    
    JenisKereta jenis = GetJenisKeretaFromString(kereta->id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    
    if (baris < 0 || baris >= konfig.baris || kolom < 0 || kolom >= konfig.kolom) {
        printf("Error: Posisi kursi tidak valid\n");
        return FALSE;
    }
    
    if (segmen_idx < 0 || segmen_idx >= kereta->jumlah_segmen) {
        printf("Error: Indeks segmen tidak valid\n");
        return FALSE;
    }
    
    // Cek apakah kursi sudah kosong
    if (!kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][segmen_idx]) {
        printf("Error: Kursi sudah kosong\n");
        return FALSE;
    }
    
    // Batalkan reservasi
    kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][segmen_idx] = FALSE;
    return TRUE;
}

boolean BatalkanReservasiMultiSegmen(KursiKereta *kereta, int gerbong, int baris, int kolom, int segmen_awal, int segmen_akhir) {
    // Validasi parameter
    if (segmen_awal < 0 || segmen_awal >= kereta->jumlah_segmen ||
        segmen_akhir < 0 || segmen_akhir >= kereta->jumlah_segmen ||
        segmen_awal > segmen_akhir) {
        printf("Error: Indeks segmen tidak valid\n");
        return FALSE;
    }
    
    // Batalkan reservasi untuk semua segmen
    int s;
    for (s = segmen_awal; s <= segmen_akhir; s++) {
        kereta->data_kursi[gerbong-1].status_kursi[kolom][baris][s] = FALSE;
    }
    
    return TRUE;
}

boolean CekStatusKursi(KursiKereta kereta, int gerbong, int baris, int kolom, int segmen_idx) {
    // Validasi parameter
    if (gerbong < 1 || gerbong > kereta.jumlah_gerbong) {
        printf("Error: Nomor gerbong tidak valid\n");
        return FALSE;
    }
    
    JenisKereta jenis = GetJenisKeretaFromString(kereta.id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    
    if (baris < 0 || baris >= konfig.baris || kolom < 0 || kolom >= konfig.kolom) {
        printf("Error: Posisi kursi tidak valid\n");
        return FALSE;
    }
    
    if (segmen_idx < 0 || segmen_idx >= kereta.jumlah_segmen) {
        printf("Error: Indeks segmen tidak valid\n");
        return FALSE;
    }
    
    // Return status kursi
    return kereta.data_kursi[gerbong-1].status_kursi[kolom][baris][segmen_idx];
}

void TampilkanKursiGerbong(KursiKereta kereta, int gerbong, int segmen_idx, JenisKereta jenis) {
    // Validasi parameter
    if (gerbong < 1 || gerbong > kereta.jumlah_gerbong) {
        printf("Error: Nomor gerbong tidak valid\n");
        return;
    }
    
    if (segmen_idx < 0 || segmen_idx >= kereta.jumlah_segmen) {
        printf("Error: Indeks segmen tidak valid\n");
        return;
    }
    
    printf("\n=== DENAH KURSI GERBONG %d ===\n", gerbong);
    printf("Segmen: %s\n", kereta.segmen[segmen_idx].nama);
    printf("----------------------------------\n");
    
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    int g = gerbong - 1; // Konversi ke indeks array
    
    // Header kolom (nomor kursi)
    int k;
    printf("    ");
    for (k = 0; k < konfig.kolom; k++) {
        printf("%c   ", 'A' + k);
    }
    printf("\n");
    
    // Tampilkan kursi
    int b;
    for (b = 0; b < konfig.baris; b++) {
        printf("%2d  ", b + 1); // Nomor baris
        
        int k;
        for (k = 0; k < konfig.kolom; k++) {
            char status = kereta.data_kursi[g].status_kursi[k][b][segmen_idx] ? 'X' : 'O';
            printf("%c   ", status);
        }
        printf("\n");
    }
    
    printf("\nKeterangan: O = Kursi tersedia, X = Kursi terisi\n");
}

/* *** Utilitas *** */
KonfigurasiKursi GetKonfigurasiKursiByJenis(JenisKereta jenis) {
    KonfigurasiKursi konfig;
    
    switch (jenis) {
        case EKONOMI:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case EKONOMI_PREMIUM:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case BISNIS:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case EKSEKUTIF:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case LUXURY:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case PRIORITY:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case SLEEPER:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        case COMPARTMENT:
            konfig.kolom = 4;
            konfig.baris = 20;
            break;
        default:
            konfig.kolom = 4;
            konfig.baris = 20;
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
            return "Unknown";
    }
}

JenisKereta GetJenisKeretaFromString(const char* jenis_str) {
    if (strcasecmp(jenis_str, "Ekonomi") == 0) return EKONOMI;
    if (strcasecmp(jenis_str, "Ekonomi Premium") == 0) return EKONOMI_PREMIUM;
    if (strcasecmp(jenis_str, "Bisnis") == 0) return BISNIS;
    if (strcasecmp(jenis_str, "Eksekutif") == 0) return EKSEKUTIF;
    if (strcasecmp(jenis_str, "Luxury") == 0) return LUXURY;
    if (strcasecmp(jenis_str, "Priority") == 0) return PRIORITY;
    if (strcasecmp(jenis_str, "Sleeper") == 0) return SLEEPER;
    if (strcasecmp(jenis_str, "Compartment") == 0) return COMPARTMENT;
    
    // Default jika tidak cocok
    return EKONOMI;
}

int HitungJumlahKursiKereta(KursiKereta kereta, JenisKereta jenis) {
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    return kereta.jumlah_gerbong * konfig.baris * konfig.kolom;
}

int HitungJumlahKursiTerisiSegmen(KursiKereta kereta, int segmen_idx) {
    // Validasi parameter
    if (segmen_idx < 0 || segmen_idx >= kereta.jumlah_segmen) {
        printf("Error: Indeks segmen tidak valid\n");
        return 0;
    }
    
    JenisKereta jenis = GetJenisKeretaFromString(kereta.id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    int count = 0;
    
    int g,k,b;
    for (g = 0; g < kereta.jumlah_gerbong; g++) {
        for (k = 0; k < konfig.kolom; k++) {
            for (b = 0; b < konfig.baris; b++) {
                if (kereta.data_kursi[g].status_kursi[k][b][segmen_idx]) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

float HitungPersentaseKursiTerisiSegmen(KursiKereta kereta, int segmen_idx, JenisKereta jenis) {
    // Validasi parameter
    if (segmen_idx < 0 || segmen_idx >= kereta.jumlah_segmen) {
        printf("Error: Indeks segmen tidak valid\n");
        return 0.0;
    }
    
    int jumlah_kursi = HitungJumlahKursiKereta(kereta, jenis);
    if (jumlah_kursi == 0) {
        return 0.0;
    }
    
    int kursi_terisi = HitungJumlahKursiTerisiSegmen(kereta, segmen_idx);
    return (float)kursi_terisi / jumlah_kursi * 100.0;
}

int CariIndexSegmen(KursiKereta kereta, const char *nama_segmen) {
    int i;
    for (i = 0; i < kereta.jumlah_segmen; i++) {
        // Bandingkan case-insensitive
        if (strcasecmp(kereta.segmen[i].nama, nama_segmen) == 0) {
            return i;
        }
    }
    return -1;
}







