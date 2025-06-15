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
    // Inisialisasi root dan node utama
    (*pohonRute)[1].info = strdup("Rute Kereta Api Jawa");
    (*pohonRute)[1].ps_fs = 2; // First Son: Jalur Utara
    (*pohonRute)[1].ps_nb = 0;
    (*pohonRute)[1].ps_pr = 0; // Root tidak punya parent
    
    // Inisialisasi 3 jalur utama dan jalur cabang
    (*pohonRute)[2].info = strdup("Jalur Utara");
    (*pohonRute)[2].ps_fs = 0; // Akan diisi nanti
    (*pohonRute)[2].ps_nb = 3; // Next Brother: Jalur Selatan
    (*pohonRute)[2].ps_pr = 1; // Parent: Rute Kereta Api Jawa
    
    (*pohonRute)[3].info = strdup("Jalur Selatan");
    (*pohonRute)[3].ps_fs = 0; // Akan diisi nanti
    (*pohonRute)[3].ps_nb = 4; // Next Brother: Jalur Tengah
    (*pohonRute)[3].ps_pr = 1; // Parent: Rute Kereta Api Jawa
    
    (*pohonRute)[4].info = strdup("Jalur Tengah");
    (*pohonRute)[4].ps_fs = 0; // Akan diisi nanti
    (*pohonRute)[4].ps_nb = 5; // Next Brother: Jalur Cabang
    (*pohonRute)[4].ps_pr = 1; // Parent: Rute Kereta Api Jawa
    
    (*pohonRute)[5].info = strdup("Jalur Cabang");
    (*pohonRute)[5].ps_fs = 0; // Akan diisi nanti
    (*pohonRute)[5].ps_nb = 0;
    (*pohonRute)[5].ps_pr = 1; // Parent: Rute Kereta Api Jawa
    
    // Inisialisasi stasiun-stasiun di tiap jalur
    InisialisasiJalurUtara(pohonRute);
    InisialisasiJalurSelatan(pohonRute);
    InisialisasiJalurTengah(pohonRute);
    InisialisasiJalurCabang(pohonRute);
}

void InisialisasiJalurUtara(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Utara
    int idxJalurUtara = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Utara") == 0) {
            idxJalurUtara = i;
            break;
        }
    }
    
    if (idxJalurUtara == 0) return; // Jalur Utara tidak ditemukan
    
    // Menambahkan stasiun-stasiun di Jalur Utara
    // Jakarta - Cirebon - Tegal - Pekalongan - Semarang - Surabaya
    
    // Stasiun di DKI Jakarta dan Jawa Barat
    InsertRuteNode(*pohonRute, "Jakarta Kota", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kampung Bandan", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Ancol", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Tanjung Priok", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kemayoran", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Pasar Senen", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Jatinegara", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Bekasi", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Cikarang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Karawang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Klari", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kosambi", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Cikampek", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Dawuan", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Haurgeulis", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Terisi", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Jatibarang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Arjawinangun", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Cirebon", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Cirebon Prujakan", idxJalurUtara);
    
    // Stasiun di Jawa Tengah
    InsertRuteNode(*pohonRute, "Brebes", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Tegal", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Pemalang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Petarukan", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Pekalongan", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Batang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Weleri", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kaliwungu", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Mangkang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Semarang Poncol", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Semarang Tawang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Alastua", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Demak", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kudus", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Pati", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Juwana", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Rembang", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Lasem", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kragan", idxJalurUtara);
    
    // Stasiun di Jawa Timur
    InsertRuteNode(*pohonRute, "Tuban", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Babat", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Bojonegoro", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Sumberrejo", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Lamongan", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Duduk", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Cerme", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Benowo", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Kandangan", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Tandes", idxJalurUtara);
    InsertRuteNode(*pohonRute, "Surabaya Pasar Turi", idxJalurUtara);
}

void InisialisasiJalurSelatan(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Selatan
    int idxJalurSelatan = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Selatan") == 0) {
            idxJalurSelatan = i;
            break;
        }
    }
    
    if (idxJalurSelatan == 0) return; // Jalur Selatan tidak ditemukan
    
    // Menambahkan stasiun-stasiun di Jalur Selatan
    // Jakarta - Bandung - Yogyakarta - Solo - Madiun - Surabaya
    
    // Stasiun di DKI Jakarta dan Jawa Barat
    InsertRuteNode(*pohonRute, "Jakarta Gambir", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Manggarai", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Depok", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Depok Baru", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Citayam", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Bojong Gede", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Cilebut", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Bogor", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Sukabumi", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Cianjur", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Cimahi", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Bandung", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Kiaracondong", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Gedebage", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Cicalengka", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Rancaekek", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Haurpugur", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Nagreg", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Leles", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Cibatu", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Warungbandrek", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Tasikmalaya", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Manonjaya", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Ciamis", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Banjar", idxJalurSelatan);
    
    // Stasiun di Jawa Tengah
    InsertRuteNode(*pohonRute, "Karangpucung", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Cipari", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Sidareja", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Gandrungmangu", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Kroya", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Gombong", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Karanganyar", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Kebumen", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Kutoarjo", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Wates", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Yogyakarta", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Klaten", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Solo Balapan", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Purwosari", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Sragen", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Kedungbanteng", idxJalurSelatan);
    
    // Stasiun di Jawa Timur
    InsertRuteNode(*pohonRute, "Walikukun", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Madiun", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Caruban", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Nganjuk", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Baron", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Kertosono", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Jombang", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Peterongan", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Sumobito", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Curahmalang", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Mojokerto", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Tarik", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Sepanjang", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Waru", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Wonokromo", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Surabaya Gubeng", idxJalurSelatan);
    InsertRuteNode(*pohonRute, "Surabaya Kota", idxJalurSelatan);
}

void InisialisasiJalurTengah(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Tengah
    int idxJalurTengah = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Tengah") == 0) {
            idxJalurTengah = i;
            break;
        }
    }
    
    if (idxJalurTengah == 0) return; // Jalur Tengah tidak ditemukan
    
    // Menambahkan stasiun-stasiun di Jalur Tengah
    // Jakarta - Cikampek - Purwakarta - Bandung
    
    // Stasiun di Jalur Jakarta-Bandung
    InsertRuteNode(*pohonRute, "Jakarta Gambir", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Manggarai", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Jatinegara", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Bekasi", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Tambun", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cikarang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Lemah Abang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Karawang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cikampek", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cibungur", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Sadang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Purwakarta", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Plered", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cisomang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cikadondong", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cilame", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Padalarang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Gadobangkong", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cimahi", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Cimindi", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Andir", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Ciroyom", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Bandung", idxJalurTengah);
    
    // Stasiun di Jalur Surabaya-Malang
    InsertRuteNode(*pohonRute, "Surabaya Gubeng", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Wonokromo", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Sepanjang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Gedangan", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Sidoarjo", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Tanggulangin", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Porong", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Bangil", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Lawang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Singosari", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Blimbing", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Malang", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Malang Kota Lama", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Pakisaji", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Kepanjen", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Sumberpucung", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Kesamben", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Wlingi", idxJalurTengah);
    InsertRuteNode(*pohonRute, "Blitar", idxJalurTengah);
}

void InisialisasiJalurCabang(Isi_Tree *pohonRute) {
    // Cari indeks node Jalur Cabang
    int idxJalurCabang = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, "Jalur Cabang") == 0) {
            idxJalurCabang = i;
            break;
        }
    }
    
    if (idxJalurCabang == 0) return; // Jalur Cabang tidak ditemukan
    
    // === Cabang Garut ===
    int idxCabangGarut = InsertRuteNodeAndGetIndex(pohonRute, "Cabang Garut", idxJalurCabang);
    InsertRuteNode(*pohonRute, "Cibatu", idxCabangGarut);
    InsertRuteNode(*pohonRute, "Wanaraja", idxCabangGarut);
    InsertRuteNode(*pohonRute, "Garut", idxCabangGarut);
    InsertRuteNode(*pohonRute, "Bayongbong", idxCabangGarut);
    InsertRuteNode(*pohonRute, "Leles", idxCabangGarut);
    InsertRuteNode(*pohonRute, "Cipeundeuy", idxCabangGarut);
    
    // === Cabang Cianjur-Sukabumi ===
    int idxCabangCianjurSukabumi = InsertRuteNodeAndGetIndex(pohonRute, "Cabang Cianjur-Sukabumi", idxJalurCabang);
    InsertRuteNode(*pohonRute, "Cianjur", idxCabangCianjurSukabumi);
    InsertRuteNode(*pohonRute, "Cibeber", idxCabangCianjurSukabumi);
    InsertRuteNode(*pohonRute, "Lampegan", idxCabangCianjurSukabumi);
    InsertRuteNode(*pohonRute, "Cicurug", idxCabangCianjurSukabumi);
    InsertRuteNode(*pohonRute, "Parungkuda", idxCabangCianjurSukabumi);
    InsertRuteNode(*pohonRute, "Cisaat", idxCabangCianjurSukabumi);
    InsertRuteNode(*pohonRute, "Sukabumi", idxCabangCianjurSukabumi);
    
    // === Cabang Purwokerto-Wonosobo ===
    int idxCabangPurwokertoWonosobo = InsertRuteNodeAndGetIndex(pohonRute, "Cabang Purwokerto-Wonosobo", idxJalurCabang);
    InsertRuteNode(*pohonRute, "Purwokerto", idxCabangPurwokertoWonosobo);
    InsertRuteNode(*pohonRute, "Sokaraja", idxCabangPurwokertoWonosobo);
    InsertRuteNode(*pohonRute, "Banjarnegara", idxCabangPurwokertoWonosobo);
    InsertRuteNode(*pohonRute, "Wonosobo", idxCabangPurwokertoWonosobo);
    
    // === Cabang Yogyakarta-Magelang ===
    int idxCabangYogyakartaMagelang = InsertRuteNodeAndGetIndex(pohonRute, "Cabang Yogyakarta-Magelang", idxJalurCabang);
    InsertRuteNode(*pohonRute, "Yogyakarta", idxCabangYogyakartaMagelang);
    InsertRuteNode(*pohonRute, "Sleman", idxCabangYogyakartaMagelang);
    InsertRuteNode(*pohonRute, "Tempel", idxCabangYogyakartaMagelang);
    InsertRuteNode(*pohonRute, "Mungkid", idxCabangYogyakartaMagelang);
    InsertRuteNode(*pohonRute, "Magelang", idxCabangYogyakartaMagelang);
    
    // === Cabang Solo-Wonogiri ===
    int idxCabangSoloWonogiri = InsertRuteNodeAndGetIndex(pohonRute, "Cabang Solo-Wonogiri", idxJalurCabang);
    InsertRuteNode(*pohonRute, "Solo Balapan", idxCabangSoloWonogiri);
    InsertRuteNode(*pohonRute, "Purwosari", idxCabangSoloWonogiri);
    InsertRuteNode(*pohonRute, "Gawok", idxCabangSoloWonogiri);
    InsertRuteNode(*pohonRute, "Sukoharjo", idxCabangSoloWonogiri);
    InsertRuteNode(*pohonRute, "Wonogiri", idxCabangSoloWonogiri);
}

// Fungsi bantuan untuk mendapatkan indeks node yang baru diinsert
int InsertRuteNodeAndGetIndex(Isi_Tree *pohonRute, const char* namaStasiun, int parent_idx) {
    InsertRuteNode(*pohonRute, namaStasiun, parent_idx);
    
    // Cari indeks node yang baru saja diinsert
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, namaStasiun) == 0) {
            return i;
        }
    }
    
    return 0; // Jika tidak ditemukan
}

// *** OPERASI PENCARIAN RUTE ***

boolean IsRuteTersedia(Isi_Tree pohonRute, const char* stasiunAsal, const char* stasiunTujuan) {
    // Fungsi ini mengecek apakah kedua stasiun ada dalam tree
    // dan terhubung (berada dalam jalur yang sama)
    
    // Cek apakah kedua stasiun ada dalam tree
    boolean stasiunAsalAda = FALSE;
    boolean stasiunTujuanAda = FALSE;
    int idxStasiunAsal = 0;
    int idxStasiunTujuan = 0;
    int i;
    
    for (i = 1; i <= jml_maks; i++) {
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
        for (i = 0; i < countAsal; i++) {
            if (parentAsal[i] == currIdxTujuan) {
                return TRUE; // Ada parent yang sama
            }
        }
        currIdxTujuan = pohonRute[currIdxTujuan].ps_pr;
    }
    
    return FALSE; // Tidak ada parent yang sama
}

int HitungJarak(InfoRute* infoJarak, int jumlahRute, const char* stasiunAsal, const char* stasiunTujuan) {
    // Mencari rute langsung
    int i;
    for (i = 0; i < jumlahRute; i++) {
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

int HitungWaktuTempuh(InfoRute* infoJarak, int jumlahRute, const char* stasiunAsal, const char* stasiunTujuan) {
    // Mencari rute langsung
    int i;
    for (i = 0; i < jumlahRute; i++) {
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

void TambahStasiun(Isi_Tree *pohonRute, const char* namaStasiun, const char* stasiunInduk) {
    // Cari indeks stasiun induk
    int idxStasiunInduk = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
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
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL && strcmp((*pohonRute)[i].info, namaStasiun) == 0) {
            printf("Stasiun \"%s\" sudah ada dalam tree.\n", namaStasiun);
            return;
        }
    }
    
    // Tambahkan stasiun baru
    InsertRuteNode(*pohonRute, namaStasiun, idxStasiunInduk);
    printf("Stasiun \"%s\" berhasil ditambahkan sebagai anak dari \"%s\".\n", 
           namaStasiun, stasiunInduk);
}

void TambahInfoRute(InfoRute **infoJarak, int *jumlahRute, const char* stasiunAsal, const char* stasiunTujuan, int jarak, int waktuTempuh) {
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

void HapusStasiun(Isi_Tree *pohonRute, const char* namaStasiun) {
    // Cari indeks stasiun
    int idxStasiun = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
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
	int i;
    if (idx == 0 || pohonRute[idx].info == NULL) return;
    
    // Tampilkan indentasi sesuai level
    for (i = 0; i < level; i++) {
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

void TampilkanStasiunTerdekat(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, const char* namaStasiun, int radius) {
    printf("=== STASIUN TERDEKAT DARI %s (RADIUS %d KM) ===\n\n", namaStasiun, radius);
    
    // Cari stasiun yang berjarak kurang dari atau sama dengan radius
    int count = 0;
    int i;
    for (i = 0; i < jumlahRute; i++) {
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

void TampilkanJalurTerpendek(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, const char* stasiunAsal, const char* stasiunTujuan) {
    printf("=== JALUR TERPENDEK DARI %s KE %s ===\n\n", stasiunAsal, stasiunTujuan);
    
    // Implementasi algoritma Dijkstra untuk mencari jalur terpendek
    // Karena implementasi lengkap algoritma Dijkstra cukup kompleks,
    // di sini kita akan menggunakan pendekatan sederhana
    
    // Cari rute langsung
    int i;
    for (i = 0; i < jumlahRute; i++) {
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

int CariIndeksStasiun(Isi_Tree pohonRute, const char* namaStasiun) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL && strcmp(pohonRute[i].info, namaStasiun) == 0) {
            return i;
        }
    }
    return 0; // Tidak ditemukan
}

char** DapatkanDaftarStasiun(Isi_Tree pohonRute, int *jumlahStasiun) {
    // Hitung jumlah stasiun
    *jumlahStasiun = 0;
    int i, idx;
    for (i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            (*jumlahStasiun)++;
        }
    }
    
    // Alokasi array untuk menyimpan nama stasiun
    char** daftarStasiun = (char**)malloc(*jumlahStasiun * sizeof(char*));
    
    // Isi array dengan nama stasiun
    idx = 0;
    for (i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            daftarStasiun[idx++] = (char*)pohonRute[i].info;
        }
    }
    
    return daftarStasiun;
}

void SimpanRuteKeFile(Isi_Tree pohonRute, InfoRute* infoJarak, int jumlahRute, const char* namaFile) {
    FILE* file = fopen(namaFile, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s untuk ditulis.\n", namaFile);
        return;
    }
    
    // Simpan jumlah stasiun dan jumlah rute
    int jumlahStasiun = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            jumlahStasiun++;
        }
    }
    fprintf(file, "%d %d\n", jumlahStasiun, jumlahRute);
    
    // Simpan informasi stasiun
    for (i = 1; i <= jml_maks; i++) {
        if (pohonRute[i].info != NULL) {
            fprintf(file, "%d %s %d %d %d\n", i, pohonRute[i].info, 
                    pohonRute[i].ps_pr, pohonRute[i].ps_fs, pohonRute[i].ps_nb);
        }
    }
    
    // Simpan informasi rute
    for (i = 0; i < jumlahRute; i++) {
        fprintf(file, "%s %s %d %d\n", 
                infoJarak[i].stasiunAsal, infoJarak[i].stasiunTujuan, 
                infoJarak[i].jarak, infoJarak[i].waktuTempuh);
    }
    
    fclose(file);
    printf("Data rute berhasil disimpan ke file %s.\n", namaFile);
}

void BacaRuteDariFile(Isi_Tree *pohonRute, InfoRute** infoJarak, int *jumlahRute, const char* namaFile) {
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s.\n", namaFile);
        return;
    }
    
    // Baca jumlah stasiun dan jumlah rute
    int jumlahStasiun;
    int i, idx, ps_pr, ps_fs, ps_nb;
    char namaStasiun[100], stasiunAsal[100], stasiunTujuan[100];
    int jarak, waktuTempuh;
    
    fscanf(file, "%d %d\n", &jumlahStasiun, jumlahRute);
    
    // Bersihkan tree
    for (i = 1; i <= jml_maks; i++) {
        if ((*pohonRute)[i].info != NULL) {
            free((void*)(*pohonRute)[i].info);
            (*pohonRute)[i].info = NULL;
        }
        (*pohonRute)[i].ps_fs = 0;
        (*pohonRute)[i].ps_nb = 0;
        (*pohonRute)[i].ps_pr = 0;
    }
    
    // Baca informasi stasiun
    for (i = 0; i < jumlahStasiun; i++) {
        fscanf(file, "%d %s %d %d %d\n", &idx, namaStasiun, &ps_pr, &ps_fs, &ps_nb);
        
        (*pohonRute)[idx].info = strdup(namaStasiun);
        (*pohonRute)[idx].ps_pr = ps_pr;
        (*pohonRute)[idx].ps_fs = ps_fs;
        (*pohonRute)[idx].ps_nb = ps_nb;
    }
    
    // Alokasi memori untuk infoJarak
    *infoJarak = (InfoRute*)malloc(*jumlahRute * sizeof(InfoRute));
    
    // Baca informasi rute
    for (i = 0; i < *jumlahRute; i++) {
        fscanf(file, "%s %s %d %d\n", stasiunAsal, stasiunTujuan, &jarak, &waktuTempuh);
        
        (*infoJarak)[i].stasiunAsal = strdup(stasiunAsal);
        (*infoJarak)[i].stasiunTujuan = strdup(stasiunTujuan);
        (*infoJarak)[i].jarak = jarak;
        (*infoJarak)[i].waktuTempuh = waktuTempuh;
    }
    
    fclose(file);
    printf("Data rute berhasil dibaca dari file %s.\n", namaFile);
}

// Fungsi untuk menambahkan node baru
void InsertRuteNode(Isi_Tree P, const char* info, int parent_idx) {
    if (parent_idx < 1 || parent_idx > jml_maks) {
        printf("Indeks parent tidak valid.\n");
        return;
    }
    
    // Cari slot kosong
    int empty_idx = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info == NULL) {
            empty_idx = i;
            break;
        }
    }
    
    if (empty_idx == 0) {
        printf("Tree penuh, tidak dapat menambahkan node baru.\n");
        return;
    }
    
    // Alokasi node baru
    P[empty_idx].info = strdup(info); // Duplikasi string untuk mencegah masalah memori
    P[empty_idx].ps_fs = 0;
    P[empty_idx].ps_nb = 0;
    P[empty_idx].ps_pr = parent_idx;
    
    // Cek apakah parent sudah memiliki First Son
    if (P[parent_idx].ps_fs == 0) {
        // Jika belum, node baru menjadi First Son
        P[parent_idx].ps_fs = empty_idx;
    } else {
        // Jika sudah, traverse hingga Next Brother terakhir dan tambahkan node baru
        int current = P[parent_idx].ps_fs;
        while (P[current].ps_nb != 0) {
            current = P[current].ps_nb;
        }
        P[current].ps_nb = empty_idx;
    }
} 
