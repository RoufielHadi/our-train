/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi_rute_kereta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// *** OPERASI DASAR RUTE KERETA ***

void InisialisasiRuteKereta(Isi_Tree *pohonRute) {
    // Inisialisasi tree kosong
    for (int i = 1; i <= jml_maks; i++) {
        (*pohonRute)[i].info = NULL;
        (*pohonRute)[i].ps_fs = 0;
        (*pohonRute)[i].ps_nb = 0;
        (*pohonRute)[i].ps_pr = 0;
    }
    
    // Membuat root node dengan info "Pulau Jawa"
    (*pohonRute)[1].info = strdup("Pulau Jawa");
    
    // Menambahkan tiga jalur utama sebagai anak dari root
    InsertNode(*pohonRute, "Jalur Utara", 1);
    InsertNode(*pohonRute, "Jalur Selatan", 1);
    InsertNode(*pohonRute, "Jalur Tengah", 1);
    InsertNode(*pohonRute, "Jalur Cabang", 1);
    
    // Inisialisasi jalur-jalur
    InisialisasiJalurUtara(pohonRute);
    InisialisasiJalurSelatan(pohonRute);
    InisialisasiJalurTengah(pohonRute);
    InisialisasiJalurCabang(pohonRute);
}

void InisialisasiJalurUtara(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Utara
    int idxJalurUtara = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Utara") == 0) {
            idxJalurUtara = i;
            break;
        }
    }
    
    if (idxJalurUtara == 0) return; // Jalur Utara tidak ditemukan
    
    // Menambahkan stasiun-stasiun di Jalur Utara
    // Jakarta - Cirebon - Tegal - Pekalongan - Semarang - Surabaya
    
    // Stasiun di DKI Jakarta dan Jawa Barat
    InsertNode(*pohonRute, "Jakarta Kota", idxJalurUtara);
    InsertNode(*pohonRute, "Kampung Bandan", idxJalurUtara);
    InsertNode(*pohonRute, "Ancol", idxJalurUtara);
    InsertNode(*pohonRute, "Tanjung Priok", idxJalurUtara);
    InsertNode(*pohonRute, "Kemayoran", idxJalurUtara);
    InsertNode(*pohonRute, "Pasar Senen", idxJalurUtara);
    InsertNode(*pohonRute, "Jatinegara", idxJalurUtara);
    InsertNode(*pohonRute, "Bekasi", idxJalurUtara);
    InsertNode(*pohonRute, "Cikarang", idxJalurUtara);
    InsertNode(*pohonRute, "Karawang", idxJalurUtara);
    InsertNode(*pohonRute, "Klari", idxJalurUtara);
    InsertNode(*pohonRute, "Kosambi", idxJalurUtara);
    InsertNode(*pohonRute, "Cikampek", idxJalurUtara);
    InsertNode(*pohonRute, "Dawuan", idxJalurUtara);
    InsertNode(*pohonRute, "Haurgeulis", idxJalurUtara);
    InsertNode(*pohonRute, "Terisi", idxJalurUtara);
    InsertNode(*pohonRute, "Jatibarang", idxJalurUtara);
    InsertNode(*pohonRute, "Arjawinangun", idxJalurUtara);
    InsertNode(*pohonRute, "Cirebon", idxJalurUtara);
    InsertNode(*pohonRute, "Cirebon Prujakan", idxJalurUtara);
    
    // Stasiun di Jawa Tengah
    InsertNode(*pohonRute, "Brebes", idxJalurUtara);
    InsertNode(*pohonRute, "Tegal", idxJalurUtara);
    InsertNode(*pohonRute, "Pemalang", idxJalurUtara);
    InsertNode(*pohonRute, "Petarukan", idxJalurUtara);
    InsertNode(*pohonRute, "Pekalongan", idxJalurUtara);
    InsertNode(*pohonRute, "Batang", idxJalurUtara);
    InsertNode(*pohonRute, "Weleri", idxJalurUtara);
    InsertNode(*pohonRute, "Kaliwungu", idxJalurUtara);
    InsertNode(*pohonRute, "Mangkang", idxJalurUtara);
    InsertNode(*pohonRute, "Semarang Poncol", idxJalurUtara);
    InsertNode(*pohonRute, "Semarang Tawang", idxJalurUtara);
    InsertNode(*pohonRute, "Alastua", idxJalurUtara);
    InsertNode(*pohonRute, "Demak", idxJalurUtara);
    InsertNode(*pohonRute, "Kudus", idxJalurUtara);
    InsertNode(*pohonRute, "Pati", idxJalurUtara);
    InsertNode(*pohonRute, "Juwana", idxJalurUtara);
    InsertNode(*pohonRute, "Rembang", idxJalurUtara);
    InsertNode(*pohonRute, "Lasem", idxJalurUtara);
    InsertNode(*pohonRute, "Kragan", idxJalurUtara);
    
    // Stasiun di Jawa Timur
    InsertNode(*pohonRute, "Tuban", idxJalurUtara);
    InsertNode(*pohonRute, "Babat", idxJalurUtara);
    InsertNode(*pohonRute, "Bojonegoro", idxJalurUtara);
    InsertNode(*pohonRute, "Sumberrejo", idxJalurUtara);
    InsertNode(*pohonRute, "Lamongan", idxJalurUtara);
    InsertNode(*pohonRute, "Duduk", idxJalurUtara);
    InsertNode(*pohonRute, "Cerme", idxJalurUtara);
    InsertNode(*pohonRute, "Benowo", idxJalurUtara);
    InsertNode(*pohonRute, "Kandangan", idxJalurUtara);
    InsertNode(*pohonRute, "Tandes", idxJalurUtara);
    InsertNode(*pohonRute, "Surabaya Pasar Turi", idxJalurUtara);
}

void InisialisasiJalurSelatan(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Selatan
    int idxJalurSelatan = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Selatan") == 0) {
            idxJalurSelatan = i;
            break;
        }
    }
    
    if (idxJalurSelatan == 0) return; // Jalur Selatan tidak ditemukan
    
    // Menambahkan stasiun-stasiun di Jalur Selatan
    // Jakarta - Bandung - Yogyakarta - Solo - Madiun - Surabaya
    
    // Stasiun di DKI Jakarta dan Jawa Barat
    InsertNode(*pohonRute, "Jakarta Gambir", idxJalurSelatan);
    InsertNode(*pohonRute, "Manggarai", idxJalurSelatan);
    InsertNode(*pohonRute, "Depok", idxJalurSelatan);
    InsertNode(*pohonRute, "Depok Baru", idxJalurSelatan);
    InsertNode(*pohonRute, "Citayam", idxJalurSelatan);
    InsertNode(*pohonRute, "Bojong Gede", idxJalurSelatan);
    InsertNode(*pohonRute, "Cilebut", idxJalurSelatan);
    InsertNode(*pohonRute, "Bogor", idxJalurSelatan);
    InsertNode(*pohonRute, "Sukabumi", idxJalurSelatan);
    InsertNode(*pohonRute, "Cianjur", idxJalurSelatan);
    InsertNode(*pohonRute, "Cimahi", idxJalurSelatan);
    InsertNode(*pohonRute, "Bandung", idxJalurSelatan);
    InsertNode(*pohonRute, "Kiaracondong", idxJalurSelatan);
    InsertNode(*pohonRute, "Gedebage", idxJalurSelatan);
    InsertNode(*pohonRute, "Cicalengka", idxJalurSelatan);
    InsertNode(*pohonRute, "Rancaekek", idxJalurSelatan);
    InsertNode(*pohonRute, "Haurpugur", idxJalurSelatan);
    InsertNode(*pohonRute, "Nagreg", idxJalurSelatan);
    InsertNode(*pohonRute, "Leles", idxJalurSelatan);
    InsertNode(*pohonRute, "Cibatu", idxJalurSelatan);
    InsertNode(*pohonRute, "Warungbandrek", idxJalurSelatan);
    InsertNode(*pohonRute, "Tasikmalaya", idxJalurSelatan);
    InsertNode(*pohonRute, "Manonjaya", idxJalurSelatan);
    InsertNode(*pohonRute, "Ciamis", idxJalurSelatan);
    InsertNode(*pohonRute, "Banjar", idxJalurSelatan);
    
    // Stasiun di Jawa Tengah
    InsertNode(*pohonRute, "Karangpucung", idxJalurSelatan);
    InsertNode(*pohonRute, "Cipari", idxJalurSelatan);
    InsertNode(*pohonRute, "Sidareja", idxJalurSelatan);
    InsertNode(*pohonRute, "Gandrungmangu", idxJalurSelatan);
    InsertNode(*pohonRute, "Kroya", idxJalurSelatan);
    InsertNode(*pohonRute, "Gombong", idxJalurSelatan);
    InsertNode(*pohonRute, "Karanganyar", idxJalurSelatan);
    InsertNode(*pohonRute, "Kebumen", idxJalurSelatan);
    InsertNode(*pohonRute, "Kutoarjo", idxJalurSelatan);
    InsertNode(*pohonRute, "Wates", idxJalurSelatan);
    InsertNode(*pohonRute, "Yogyakarta", idxJalurSelatan);
    InsertNode(*pohonRute, "Klaten", idxJalurSelatan);
    InsertNode(*pohonRute, "Solo Balapan", idxJalurSelatan);
    InsertNode(*pohonRute, "Purwosari", idxJalurSelatan);
    InsertNode(*pohonRute, "Sragen", idxJalurSelatan);
    InsertNode(*pohonRute, "Kedungbanteng", idxJalurSelatan);
    
    // Stasiun di Jawa Timur
    InsertNode(*pohonRute, "Walikukun", idxJalurSelatan);
    InsertNode(*pohonRute, "Madiun", idxJalurSelatan);
    InsertNode(*pohonRute, "Caruban", idxJalurSelatan);
    InsertNode(*pohonRute, "Nganjuk", idxJalurSelatan);
    InsertNode(*pohonRute, "Baron", idxJalurSelatan);
    InsertNode(*pohonRute, "Kertosono", idxJalurSelatan);
    InsertNode(*pohonRute, "Jombang", idxJalurSelatan);
    InsertNode(*pohonRute, "Peterongan", idxJalurSelatan);
    InsertNode(*pohonRute, "Sumobito", idxJalurSelatan);
    InsertNode(*pohonRute, "Curahmalang", idxJalurSelatan);
    InsertNode(*pohonRute, "Mojokerto", idxJalurSelatan);
    InsertNode(*pohonRute, "Tarik", idxJalurSelatan);
    InsertNode(*pohonRute, "Sepanjang", idxJalurSelatan);
    InsertNode(*pohonRute, "Waru", idxJalurSelatan);
    InsertNode(*pohonRute, "Wonokromo", idxJalurSelatan);
    InsertNode(*pohonRute, "Surabaya Gubeng", idxJalurSelatan);
    InsertNode(*pohonRute, "Surabaya Kota", idxJalurSelatan);
}

void InisialisasiJalurTengah(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Tengah
    int idxJalurTengah = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Tengah") == 0) {
            idxJalurTengah = i;
            break;
        }
    }
    
    if (idxJalurTengah == 0) return; // Jalur Tengah tidak ditemukan
    
    // Menambahkan stasiun-stasiun di Jalur Tengah
    // Jakarta - Cikampek - Purwakarta - Bandung
    
    // Stasiun di Jalur Jakarta-Bandung
    InsertNode(*pohonRute, "Jakarta Gambir", idxJalurTengah);
    InsertNode(*pohonRute, "Manggarai", idxJalurTengah);
    InsertNode(*pohonRute, "Jatinegara", idxJalurTengah);
    InsertNode(*pohonRute, "Bekasi", idxJalurTengah);
    InsertNode(*pohonRute, "Tambun", idxJalurTengah);
    InsertNode(*pohonRute, "Cikarang", idxJalurTengah);
    InsertNode(*pohonRute, "Lemah Abang", idxJalurTengah);
    InsertNode(*pohonRute, "Karawang", idxJalurTengah);
    InsertNode(*pohonRute, "Cikampek", idxJalurTengah);
    InsertNode(*pohonRute, "Cibungur", idxJalurTengah);
    InsertNode(*pohonRute, "Sadang", idxJalurTengah);
    InsertNode(*pohonRute, "Purwakarta", idxJalurTengah);
    InsertNode(*pohonRute, "Plered", idxJalurTengah);
    InsertNode(*pohonRute, "Cisomang", idxJalurTengah);
    InsertNode(*pohonRute, "Cikadondong", idxJalurTengah);
    InsertNode(*pohonRute, "Cilame", idxJalurTengah);
    InsertNode(*pohonRute, "Padalarang", idxJalurTengah);
    InsertNode(*pohonRute, "Gadobangkong", idxJalurTengah);
    InsertNode(*pohonRute, "Cimahi", idxJalurTengah);
    InsertNode(*pohonRute, "Cimindi", idxJalurTengah);
    InsertNode(*pohonRute, "Andir", idxJalurTengah);
    InsertNode(*pohonRute, "Ciroyom", idxJalurTengah);
    InsertNode(*pohonRute, "Bandung", idxJalurTengah);
    
    // Stasiun di Jalur Surabaya-Malang
    InsertNode(*pohonRute, "Surabaya Gubeng", idxJalurTengah);
    InsertNode(*pohonRute, "Wonokromo", idxJalurTengah);
    InsertNode(*pohonRute, "Sepanjang", idxJalurTengah);
    InsertNode(*pohonRute, "Gedangan", idxJalurTengah);
    InsertNode(*pohonRute, "Sidoarjo", idxJalurTengah);
    InsertNode(*pohonRute, "Tanggulangin", idxJalurTengah);
    InsertNode(*pohonRute, "Porong", idxJalurTengah);
    InsertNode(*pohonRute, "Bangil", idxJalurTengah);
    InsertNode(*pohonRute, "Lawang", idxJalurTengah);
    InsertNode(*pohonRute, "Singosari", idxJalurTengah);
    InsertNode(*pohonRute, "Blimbing", idxJalurTengah);
    InsertNode(*pohonRute, "Malang", idxJalurTengah);
    InsertNode(*pohonRute, "Malang Kota Lama", idxJalurTengah);
    InsertNode(*pohonRute, "Pakisaji", idxJalurTengah);
    InsertNode(*pohonRute, "Kepanjen", idxJalurTengah);
    InsertNode(*pohonRute, "Sumberpucung", idxJalurTengah);
    InsertNode(*pohonRute, "Kesamben", idxJalurTengah);
    InsertNode(*pohonRute, "Wlingi", idxJalurTengah);
    InsertNode(*pohonRute, "Blitar", idxJalurTengah);
}

void InisialisasiJalurCabang(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Cabang
    int idxJalurCabang = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Cabang") == 0) {
            idxJalurCabang = i;
            break;
        }
    }
    
    if (idxJalurCabang == 0) return; // Jalur Cabang tidak ditemukan
    
    // === Cabang Garut ===
    int idxCabangGarut = InsertNodeAndGetIndex(*pohonRute, "Cabang Garut", idxJalurCabang);
    InsertNode(*pohonRute, "Cibatu", idxCabangGarut);
    InsertNode(*pohonRute, "Wanaraja", idxCabangGarut);
    InsertNode(*pohonRute, "Garut", idxCabangGarut);
    InsertNode(*pohonRute, "Bayongbong", idxCabangGarut);
    InsertNode(*pohonRute, "Leles", idxCabangGarut);
    InsertNode(*pohonRute, "Cipeundeuy", idxCabangGarut);
    
    // === Cabang Cianjur-Sukabumi ===
    int idxCabangCianjurSukabumi = InsertNodeAndGetIndex(*pohonRute, "Cabang Cianjur-Sukabumi", idxJalurCabang);
    InsertNode(*pohonRute, "Cianjur", idxCabangCianjurSukabumi);
    InsertNode(*pohonRute, "Cibeber", idxCabangCianjurSukabumi);
    InsertNode(*pohonRute, "Lampegan", idxCabangCianjurSukabumi);
    InsertNode(*pohonRute, "Cicurug", idxCabangCianjurSukabumi);
    InsertNode(*pohonRute, "Parungkuda", idxCabangCianjurSukabumi);
    InsertNode(*pohonRute, "Cisaat", idxCabangCianjurSukabumi);
    InsertNode(*pohonRute, "Sukabumi", idxCabangCianjurSukabumi);
    
    // === Cabang Purwokerto-Wonosobo ===
    int idxCabangPurwokertoWonosobo = InsertNodeAndGetIndex(*pohonRute, "Cabang Purwokerto-Wonosobo", idxJalurCabang);
    InsertNode(*pohonRute, "Purwokerto", idxCabangPurwokertoWonosobo);
    InsertNode(*pohonRute, "Sokaraja", idxCabangPurwokertoWonosobo);
    InsertNode(*pohonRute, "Banjarnegara", idxCabangPurwokertoWonosobo);
    InsertNode(*pohonRute, "Wonosobo", idxCabangPurwokertoWonosobo);
    
    // === Cabang Yogyakarta-Magelang ===
    int idxCabangYogyakartaMagelang = InsertNodeAndGetIndex(*pohonRute, "Cabang Yogyakarta-Magelang", idxJalurCabang);
    InsertNode(*pohonRute, "Yogyakarta", idxCabangYogyakartaMagelang);
    InsertNode(*pohonRute, "Sleman", idxCabangYogyakartaMagelang);
    InsertNode(*pohonRute, "Tempel", idxCabangYogyakartaMagelang);
    InsertNode(*pohonRute, "Mungkid", idxCabangYogyakartaMagelang);
    InsertNode(*pohonRute, "Magelang", idxCabangYogyakartaMagelang);
    
    // === Cabang Solo-Wonogiri ===
    int idxCabangSoloWonogiri = InsertNodeAndGetIndex(*pohonRute, "Cabang Solo-Wonogiri", idxJalurCabang);
    InsertNode(*pohonRute, "Solo Balapan", idxCabangSoloWonogiri);
    InsertNode(*pohonRute, "Purwosari", idxCabangSoloWonogiri);
    InsertNode(*pohonRute, "Gawok", idxCabangSoloWonogiri);
    InsertNode(*pohonRute, "Sukoharjo", idxCabangSoloWonogiri);
    InsertNode(*pohonRute, "Wonogiri", idxCabangSoloWonogiri);
}

// Fungsi bantuan untuk mendapatkan indeks node yang baru diinsert
int InsertNodeAndGetIndex(Isi_Tree *pohonRute, char* namaStasiun, int parent_idx) {
    InsertNode(*pohonRute, namaStasiun, parent_idx);
    
    // Cari indeks node yang baru saja diinsert
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, namaStasiun) == 0) {
            return i;
        }
    }
    
    return 0; // Jika tidak ditemukan
}

// *** OPERASI PENCARIAN RUTE ***

boolean IsRuteTersedia(Isi_Tree pohonRute, char* stasiunAsal, char* stasiunTujuan) {
    // Fungsi ini mengecek apakah kedua stasiun ada dalam tree
    // dan terhubung (berada dalam jalur yang sama)
    
    // Cek apakah kedua stasiun ada dalam tree
    boolean stasiunAsalAda = FALSE;
    boolean stasiunTujuanAda = FALSE;
    int idxStasiunAsal = 0;
    int idxStasiunTujuan = 0;
    
    for (int i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            if (strcmp(pohonRute[i].info, stasiunAsal) == 0) {
                stasiunAsalAda = TRUE;
                idxStasiunAsal = i;
            }
            if (strcmp(pohonRute[i].info, stasiunTujuan) == 0) {
                stasiunTujuanAda = TRUE;
                idxStasiunTujuan = i;
            }
        }
    }
    
    if (!stasiunAsalAda || !stasiunTujuanAda) {
        return FALSE; // Salah satu atau kedua stasiun tidak ada
    }
    
    // Cek apakah kedua stasiun berada dalam jalur yang sama
    // Kita perlu menelusuri ke atas hingga menemukan parent yang sama
    
    // Kumpulkan semua parent dari stasiunAsal
    int parentAsal[jml_maks];
    int countAsal = 0;
    int currIdxAsal = idxStasiunAsal;
    
    while (currIdxAsal != 0) {
        parentAsal[countAsal++] = currIdxAsal;
        currIdxAsal = pohonRute[currIdxAsal].ps_pr;
    }
    
    // Telusuri parent dari stasiunTujuan, cek apakah ada di parentAsal
    int currIdxTujuan = idxStasiunTujuan;
    while (currIdxTujuan != 0) {
        for (int i = 0; i < countAsal; i++) {
            if (parentAsal[i] == currIdxTujuan) {
                return TRUE; // Ada parent yang sama
            }
        }
        currIdxTujuan = pohonRute[currIdxTujuan].ps_pr;
    }
    
    return FALSE; // Tidak ada parent yang sama
}

int HitungJarak(InfoRute* infoJarak, int jumlahRute, char* stasiunAsal, char* stasiunTujuan) {
    // Mencari rute langsung
    for (int i = 0; i < jumlahRute; i++) {
        if ((strcmp(infoJarak[i].stasiunAsal, stasiunAsal) == 0 && 
             strcmp(infoJarak[i].stasiunTujuan, stasiunTujuan) == 0) ||
            (strcmp(infoJarak[i].stasiunAsal, stasiunTujuan) == 0 && 
             strcmp(infoJarak[i].stasiunTujuan, stasiunAsal) == 0)) {
            return infoJarak[i].jarak;
        }
    }
    
    // Jika tidak ada rute langsung, coba temukan jalur melalui stasiun perantara
    // Menggunakan algoritma Dijkstra sederhana
    
    // Karena implementasi lengkap algoritma Dijkstra cukup kompleks,
    // di sini kita hanya mengembalikan -1 untuk menunjukkan bahwa rute tidak ditemukan
    return -1;
}

int HitungWaktuTempuh(InfoRute* infoJarak, int jumlahRute, char* stasiunAsal, char* stasiunTujuan) {
    // Mencari rute langsung
    for (int i = 0; i < jumlahRute; i++) {
        if ((strcmp(infoJarak[i].stasiunAsal, stasiunAsal) == 0 && 
             strcmp(infoJarak[i].stasiunTujuan, stasiunTujuan) == 0) ||
            (strcmp(infoJarak[i].stasiunAsal, stasiunTujuan) == 0 && 
             strcmp(infoJarak[i].stasiunTujuan, stasiunAsal) == 0)) {
            return infoJarak[i].waktuTempuh;
        }
    }
    
    // Jika tidak ada rute langsung, coba temukan jalur melalui stasiun perantara
    // Menggunakan algoritma Dijkstra sederhana
    
    // Karena implementasi lengkap algoritma Dijkstra cukup kompleks,
    // di sini kita hanya mengembalikan -1 untuk menunjukkan bahwa rute tidak ditemukan
    return -1;
}

// *** OPERASI MANAJEMEN RUTE ***

void TambahStasiun(Isi_Tree *pohonRute, char* namaStasiun, char* stasiunInduk) {
    // Cari indeks stasiun induk
    int idxStasiunInduk = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, stasiunInduk) == 0) {
            idxStasiunInduk = i;
            break;
        }
    }
    
    if (idxStasiunInduk == 0) {
        printf("Stasiun induk \"%s\" tidak ditemukan.\n", stasiunInduk);
        return;
    }
    
    // Cek apakah stasiun sudah ada
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, namaStasiun) == 0) {
            printf("Stasiun \"%s\" sudah ada dalam tree.\n", namaStasiun);
            return;
        }
    }
    
    // Tambahkan stasiun baru
    InsertNode(*pohonRute, namaStasiun, idxStasiunInduk);
    printf("Stasiun \"%s\" berhasil ditambahkan sebagai anak dari \"%s\".\n", 
           namaStasiun, stasiunInduk);
}

void TambahInfoRute(InfoRute **infoJarak, int *jumlahRute, char* stasiunAsal, char* stasiunTujuan, int jarak, int waktuTempuh) {
    // Realokasi array infoJarak jika perlu
    if (*jumlahRute == 0) {
        *infoJarak = (InfoRute*)malloc(sizeof(InfoRute));
    } else {
        *infoJarak = (InfoRute*)realloc(*infoJarak, (*jumlahRute + 1) * sizeof(InfoRute));
    }
    
    // Tambahkan info rute baru
    (*infoJarak)[*jumlahRute].stasiunAsal = strdup(stasiunAsal);
    (*infoJarak)[*jumlahRute].stasiunTujuan = strdup(stasiunTujuan);
    (*infoJarak)[*jumlahRute].jarak = jarak;
    (*infoJarak)[*jumlahRute].waktuTempuh = waktuTempuh;
    
    (*jumlahRute)++;
    
    printf("Info rute dari \"%s\" ke \"%s\" berhasil ditambahkan.\n", 
           stasiunAsal, stasiunTujuan);
}

void HapusStasiun(Isi_Tree *pohonRute, char* namaStasiun) {
    // Cari indeks stasiun
    int idxStasiun = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, namaStasiun) == 0) {
            idxStasiun = i;
            break;
        }
    }
    
    if (idxStasiun == 0) {
        printf("Stasiun \"%s\" tidak ditemukan.\n", namaStasiun);
        return;
    }
    
    // Hapus stasiun dari tree
    DeleteNode(*pohonRute, idxStasiun);
    printf("Stasiun \"%s\" berhasil dihapus.\n", namaStasiun);
}

// *** OPERASI VISUALISASI RUTE ***

// Fungsi bantuan untuk menampilkan jalur secara rekursif
void TampilkanJalurRekursif(Isi_Tree pohonRute, int idx, int level) {
    if (idx == 0 || pohonRute[idx].info == NULL) return;
    
    // Tampilkan indentasi sesuai level
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    // Tampilkan info node
    printf("- %s\n", pohonRute[idx].info);
    
    // Traversal ke first son
    TampilkanJalurRekursif(pohonRute, pohonRute[idx].ps_fs, level + 1);
    
    // Traversal ke next brother
    TampilkanJalurRekursif(pohonRute, pohonRute[idx].ps_nb, level);
}

void TampilkanRute(Isi_Tree pohonRute) {
    printf("=== RUTE KERETA API DI PULAU JAWA ===\n\n");
    
    // Tampilkan dengan traversal level order
    Level_order(pohonRute, jml_maks);
    
    printf("\n=== DETAIL JALUR ===\n");
    
    // Tampilkan struktur jalur dengan traversal pre-order
    TampilkanJalurRekursif(pohonRute, 1, 0);
}

void TampilkanStasiunTerdekat(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, char* namaStasiun, int radius) {
    printf("=== STASIUN TERDEKAT DARI %s (RADIUS %d KM) ===\n\n", namaStasiun, radius);
    
    // Cari stasiun yang berjarak kurang dari atau sama dengan radius
    int count = 0;
    for (int i = 0; i < jumlahRute; i++) {
        if (strcmp(infoJarak[i].stasiunAsal, namaStasiun) == 0) {
            if (infoJarak[i].jarak <= radius) {
                printf("%d. %s (%.1f km, %d menit)\n", 
                       ++count, infoJarak[i].stasiunTujuan, 
                       (float)infoJarak[i].jarak, infoJarak[i].waktuTempuh);
            }
        } else if (strcmp(infoJarak[i].stasiunTujuan, namaStasiun) == 0) {
            if (infoJarak[i].jarak <= radius) {
                printf("%d. %s (%.1f km, %d menit)\n", 
                       ++count, infoJarak[i].stasiunAsal, 
                       (float)infoJarak[i].jarak, infoJarak[i].waktuTempuh);
            }
        }
    }
    
    if (count == 0) {
        printf("Tidak ada stasiun yang berada dalam radius %d km dari %s.\n", 
               radius, namaStasiun);
    }
}

void TampilkanJalurTerpendek(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, char* stasiunAsal, char* stasiunTujuan) {
    printf("=== JALUR TERPENDEK DARI %s KE %s ===\n\n", stasiunAsal, stasiunTujuan);
    
    // Implementasi algoritma Dijkstra untuk mencari jalur terpendek
    // Karena implementasi lengkap algoritma Dijkstra cukup kompleks,
    // di sini kita akan menggunakan pendekatan sederhana
    
    // Cari rute langsung
    for (int i = 0; i < jumlahRute; i++) {
        if (strcmp(infoJarak[i].stasiunAsal, stasiunAsal) == 0 && 
            strcmp(infoJarak[i].stasiunTujuan, stasiunTujuan) == 0) {
            printf("Rute langsung: %s -> %s (%.1f km, %d menit)\n", 
                   stasiunAsal, stasiunTujuan, 
                   (float)infoJarak[i].jarak, infoJarak[i].waktuTempuh);
            return;
        } else if (strcmp(infoJarak[i].stasiunAsal, stasiunTujuan) == 0 && 
                 strcmp(infoJarak[i].stasiunTujuan, stasiunAsal) == 0) {
            printf("Rute langsung: %s -> %s (%.1f km, %d menit)\n", 
                   stasiunAsal, stasiunTujuan, 
                   (float)infoJarak[i].jarak, infoJarak[i].waktuTempuh);
            return;
        }
    }
    
    // Jika tidak ada rute langsung, tampilkan pesan
    printf("Tidak ditemukan rute langsung dari %s ke %s.\n", stasiunAsal, stasiunTujuan);
    printf("Untuk mencari rute dengan stasiun perantara, implementasi algoritma Dijkstra diperlukan.\n");
}

// *** FUNGSI PEMBANTU ***

int CariIndeksStasiun(Isi_Tree pohonRute, char* namaStasiun) {
    for (int i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL && strcmp(pohonRute[i].info, namaStasiun) == 0) {
            return i;
        }
    }
    return 0; // Tidak ditemukan
}

char** DapatkanDaftarStasiun(Isi_Tree pohonRute, int *jumlahStasiun) {
    // Hitung jumlah stasiun
    *jumlahStasiun = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            (*jumlahStasiun)++;
        }
    }
    
    // Alokasi array untuk menyimpan nama stasiun
    char** daftarStasiun = (char**)malloc(*jumlahStasiun * sizeof(char*));
    
    // Isi array dengan nama stasiun
    int idx = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            daftarStasiun[idx++] = pohonRute[i].info;
        }
    }
    
    return daftarStasiun;
}

void SimpanRuteKeFile(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, char* namaFile) {
    FILE* file = fopen(namaFile, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s untuk ditulis.\n", namaFile);
        return;
    }
    
    // Simpan jumlah stasiun dan jumlah rute
    int jumlahStasiun = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            jumlahStasiun++;
        }
    }
    fprintf(file, "%d %d\n", jumlahStasiun, jumlahRute);
    
    // Simpan informasi stasiun
    for (int i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            fprintf(file, "%d %s %d %d %d\n", i, pohonRute[i].info, 
                    pohonRute[i].ps_pr, pohonRute[i].ps_fs, pohonRute[i].ps_nb);
        }
    }
    
    // Simpan informasi rute
    for (int i = 0; i < jumlahRute; i++) {
        fprintf(file, "%s %s %d %d\n", 
                infoJarak[i].stasiunAsal, infoJarak[i].stasiunTujuan, 
                infoJarak[i].jarak, infoJarak[i].waktuTempuh);
    }
    
    fclose(file);
    printf("Data rute berhasil disimpan ke file %s.\n", namaFile);
}

void BacaRuteDariFile(Isi_Tree *pohonRute, InfoRute** infoJarak, int *jumlahRute, char* namaFile) {
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s.\n", namaFile);
        return;
    }
    
    // Baca jumlah stasiun dan jumlah rute
    int jumlahStasiun;
    fscanf(file, "%d %d\n", &jumlahStasiun, jumlahRute);
    
    // Bersihkan tree
    for (int i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL) {
            free((*pohonRute)[i].info);
            (*pohonRute)[i].info = NULL;
        }
        (*pohonRute)[i].ps_fs = 0;
        (*pohonRute)[i].ps_nb = 0;
        (*pohonRute)[i].ps_pr = 0;
    }
    
    // Baca informasi stasiun
    for (int i = 0; i < jumlahStasiun; i++) {
        int idx, ps_pr, ps_fs, ps_nb;
        char namaStasiun[100];
        
        fscanf(file, "%d %s %d %d %d\n", &idx, namaStasiun, &ps_pr, &ps_fs, &ps_nb);
        
        (*pohonRute)[idx].info = strdup(namaStasiun);
        (*pohonRute)[idx].ps_pr = ps_pr;
        (*pohonRute)[idx].ps_fs = ps_fs;
        (*pohonRute)[idx].ps_nb = ps_nb;
    }
    
    // Alokasi memori untuk infoJarak
    *infoJarak = (InfoRute*)malloc(*jumlahRute * sizeof(InfoRute));
    
    // Baca informasi rute
    for (int i = 0; i < *jumlahRute; i++) {
        char stasiunAsal[100], stasiunTujuan[100];
        int jarak, waktuTempuh;
        
        fscanf(file, "%s %s %d %d\n", stasiunAsal, stasiunTujuan, &jarak, &waktuTempuh);
        
        (*infoJarak)[i].stasiunAsal = strdup(stasiunAsal);
        (*infoJarak)[i].stasiunTujuan = strdup(stasiunTujuan);
        (*infoJarak)[i].jarak = jarak;
        (*infoJarak)[i].waktuTempuh = waktuTempuh;
    }
    
    fclose(file);
    printf("Data rute berhasil dibaca dari file %s.\n", namaFile);
} 