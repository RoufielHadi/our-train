#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementasi_kursi_kereta.h"
#include "array.h"
#include "databases.h"
#include "boolean.h"
#include <ctype.h>
#include "implementasi_informasi_kereta.h"

// Utility: Hilangkan spasi di awal/akhir
static char* trim(char *s) {
    while(isspace((unsigned char)*s)) s++;
    if(*s == 0) return s;
    char *end = s + strlen(s) - 1;
    while(end > s && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return s;
}

// 1. Memuat data kursi kereta dari file database
boolean MuatDataKursiDariFile(KursiKereta *kereta, const char *namaFile) {
    FILE *f = fopen(namaFile, "r");
    if (!f) {
        printf("Error: Gagal membuka file %s\n", namaFile);
        return FALSE;
    }
    char line[8192];
    boolean found = FALSE;
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, kereta->id_kereta) || !strstr(line, kereta->tanggal)) continue;
        // Parsing record: ID_Kereta, Gerbong, Tanggal, status kursi A1..D20
        char *part = strtok(line, "|");
        int gerbongIdx = -1;
        while (part) {
            char *eq = strchr(part, '=');
            if (!eq) { part = strtok(NULL, "|"); continue; }
            *eq = '\0';
            char *key = trim(part);
            char *val = trim(eq + 1);
            // Hilangkan kutip tunggal di awal dan akhir
            if (*val == '\'') val++;
            char *endq = strrchr(val, '\'');
            if (endq) *endq = '\0';

            if (strcmp(key, "Gerbong") == 0) {
                // Format G<number>
                if (val[0] == 'G') gerbongIdx = atoi(val + 1) - 1;
            }
            else if (isupper((unsigned char)key[0]) && isdigit((unsigned char)key[1])) {
                // Label kursi, misal A1
                int col = key[0] - 'A';
                int row = atoi(key + 1) - 1;
                // Parse comma-separated status values without strtok to avoid conflicts
                {
                    int s = 0;
                    char *start = val;
                    while (s < kereta->jumlah_segmen) {
                        char *comma = strchr(start, ',');
                        int len = comma ? (int)(comma - start) : (int)strlen(start);
                        char tmpVal[32];
                        if (len >= (int)sizeof(tmpVal)) len = sizeof(tmpVal) - 1;
                        strncpy(tmpVal, start, len);
                        tmpVal[len] = '\0';
                        boolean status = (strcmp(tmpVal, "True") == 0);
                        kereta->data_kursi[gerbongIdx].status_kursi[col][row][s] = status;
                        s++;
                        if (!comma) break;
                        start = comma + 1;
                    }
                }
                found = TRUE;
            }
            part = strtok(NULL, "|");
        }
    }
    fclose(f);
    return found;
}

// 2. Menginisialisasi kursi berdasarkan jadwal kereta (membangun segmen perjalanan)
boolean InisialisasiKursiDenganJadwal(KursiKereta *kereta, JenisKereta jenis) {
    FILE *f = fopen(DB_JADWAL_KERETA, "r");
    if (!f) return FALSE;
    char line[4096];
    while (fgets(line, sizeof(line), f)) {
        char buf[1024]; strcpy(buf, line);
        char *id = strtok(buf, "|");
        if (!id || strcmp(id, kereta->id_kereta) != 0) continue;
        char *stations = strtok(NULL, "|");
        char *times = strtok(NULL, "|");
        if (!stations || !times) { fclose(f); return FALSE; }
        // Bangun daftar segmen: pair stasiun[i] ke stasiun[i+1]
        char stcopy[1024]; strncpy(stcopy, stations, sizeof(stcopy)-1);
        int seg = 0;
        char *prev = strtok(stcopy, ",");
        char *cur;
        while ((cur = strtok(NULL, ",")) && seg < MAX_SEGMEN) {
            snprintf(kereta->segmen[seg].nama, MAX_NAMA_SEGMEN, "%s-%s", prev, cur);
            prev = cur; seg++;
        }
        kereta->jumlah_segmen = seg;
        kereta->jumlah_gerbong = kereta->jumlah_gerbong; // dipakai di caller
        // Inisialisasi semua kursi ke FALSE (kosong)
        InisialisasiKursiKereta(kereta, jenis);
        fclose(f);
        return TRUE;
    }
    fclose(f);
    return FALSE;
}

// 4. Menampilkan denah kursi gerbong, 'O' untuk available, 'X' untuk terisi
void TampilkanKursiLangsungDariDatabase(const char *id_kereta, const char *tanggal, int gerbong, const char *stasiun_awal, const char *stasiun_akhir) {
    KursiKereta kereta;
    strcpy(kereta.id_kereta, id_kereta);
    strcpy(kereta.tanggal, tanggal);
    // Dapatkan jenis kereta dari database umum
    JenisKereta jenis = GetJenisKeretaById(id_kereta);
    // Muat jadwal dan data kursi
    if (!InisialisasiKursiDenganJadwal(&kereta, jenis) || !MuatDataKursiDariFile(&kereta, DB_KURSI_KERETA)) {
        printf("Gagal memuat data kursi.\n");
        return;
    }
    // Tentukan indeks segmen berdasarkan stasiun asal & tujuan
    // Bangun daftar stasiun dari segmen
    int stationCount = kereta.jumlah_segmen + 1;
    char stationList[MAX_SEGMEN+1][MAX_NAMA_SEGMEN];
    char tmpStation[MAX_NAMA_SEGMEN];
    int i;
    // Stasiun pertama
    strncpy(tmpStation, kereta.segmen[0].nama, MAX_NAMA_SEGMEN);
    tmpStation[MAX_NAMA_SEGMEN-1] = '\0';
    char *dashPtr = strchr(tmpStation, '-');
    if (dashPtr) *dashPtr = '\0';
    strcpy(stationList[0], tmpStation);
    // Stasiun berikutnya
    for (i = 0; i < kereta.jumlah_segmen; i++) {
        strncpy(tmpStation, kereta.segmen[i].nama, MAX_NAMA_SEGMEN);
        tmpStation[MAX_NAMA_SEGMEN-1] = '\0';
        dashPtr = strchr(tmpStation, '-');
        if (dashPtr) strcpy(stationList[i+1], dashPtr+1);
        else stationList[i+1][0] = '\0';
    }
    // Cari indeks stasiun asal & tujuan
    int originIdx = -1, destIdx = -1;
    for (i = 0; i < stationCount; i++) {
        if (strcasecmp(stationList[i], stasiun_awal) == 0) originIdx = i;
        if (strcasecmp(stationList[i], stasiun_akhir) == 0) destIdx = i;
    }
    // Hitung indeks segmen: dari originIdx sampai destIdx-1
    int idxAwal, idxAkhir;
    if (originIdx < 0 || destIdx < 0 || originIdx >= destIdx) {
        // fallback ke semua segmen
        idxAwal = 0;
        idxAkhir = kereta.jumlah_segmen - 1;
    } else {
        idxAwal = originIdx;
        idxAkhir = destIdx - 1;
    }
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    // Hitung jumlah kolom yang tersedia di database kursi untuk gerbong ini
    int numCols = HitungJumlahKolomDariFile(id_kereta, tanggal, gerbong, DB_KURSI_KERETA);
    if (numCols <= 0 || numCols > konfig.kolom) numCols = konfig.kolom;
    // Cetak header kolom sesuai jumlah kolom DB
    printf("    ");
    int c, r;
    for (c = 0; c < numCols; c++) printf("%c ", 'A' + c);
    printf("\n");
    // Cetak tiap baris kursi
    for (r = 0; r < konfig.baris; r++) {
        printf("%2d: ", r + 1);
        for (c = 0; c < numCols; c++) {
            boolean avail = TRUE;
            int s;
            // Periksa kursi pada segmen perjalanan (idxAwal..idxAkhir)
            for (s = idxAwal; s <= idxAkhir; s++) {
                if (!kereta.data_kursi[gerbong-1].status_kursi[c][r][s]) { avail = FALSE; break; }
            }
            printf("%c ", avail ? 'O' : 'X');
        }
        printf("\n");
    }
}

// Fungsi untuk memilih kursi: parsing kode dan memanggil ReservasiKursiMultiSegmen
boolean PilihKursi(KursiKereta *kereta, int gerbong, const char *kode_kursi, const char *stasiun_awal, const char *stasiun_akhir) {
    // Parsing kolom (A..), baris (1..)
    int col = toupper((unsigned char)kode_kursi[0]) - 'A';
    int row = atoi(kode_kursi + 1) - 1;
    // Validasi input
    JenisKereta jenis = GetJenisKeretaFromString(kereta->id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);
    if (col < 0 || col >= konfig.kolom || row < 0 || row >= konfig.baris) {
        return FALSE;
    }
    // Tentukan indeks segmen berdasarkan stasiun awal dan akhir
    int idxAwal = -1, idxAkhir = -1;
    int i;
    char segCopy[MAX_NAMA_SEGMEN];
    for (i = 0; i < kereta->jumlah_segmen; i++) {
        strncpy(segCopy, kereta->segmen[i].nama, MAX_NAMA_SEGMEN);
        segCopy[MAX_NAMA_SEGMEN-1] = '\0';
        char *dash = strchr(segCopy, '-');
        if (dash) {
            *dash = '\0';
            if (strcasecmp(segCopy, stasiun_awal) == 0) {
                idxAwal = i;
            }
        }
    }
    for (i = 0; i < kereta->jumlah_segmen; i++) {
        strncpy(segCopy, kereta->segmen[i].nama, MAX_NAMA_SEGMEN);
        segCopy[MAX_NAMA_SEGMEN-1] = '\0';
        char *dash = strchr(segCopy, '-');
        if (dash) {
            char *st2 = dash + 1;
            if (strcasecmp(st2, stasiun_akhir) == 0) {
                idxAkhir = i;
            }
        }
    }
    // Fallback jika tidak ditemukan: cek semua segmen (inklusif)
    if (idxAwal < 0 || idxAkhir < 0 || idxAwal > idxAkhir) {
        idxAwal = 0;
        idxAkhir = kereta->jumlah_segmen - 1;
    }
    // Reservasi dari segmen awal sampai akhir (inklusif)
    return ReservasiKursiMultiSegmen(kereta, gerbong, row, col, idxAwal, idxAkhir);
}

// 5. Menyimpan perubahan kursi (setelah pembayaran)
boolean SimpanDataKursiKeFile(KursiKereta *kereta, const char *namaFile) {
    char tempName[256];
    sprintf(tempName, "%s.tmp", namaFile);
    FILE *fin = fopen(namaFile, "r");
    if (!fin) {
        printf("Error: Gagal membuka file %s untuk update\n", namaFile);
        return FALSE;
    }
    FILE *fout = fopen(tempName, "w");
    if (!fout) {
        printf("Error: Gagal membuat file sementara %s\n", tempName);
        fclose(fin);
        return FALSE;
    }

    char line[8192];
    boolean updated = FALSE;
    JenisKereta jenis = GetJenisKeretaFromString(kereta->id_kereta);
    KonfigurasiKursi konfig = GetKonfigurasiKursiByJenis(jenis);

    while (fgets(line, sizeof(line), fin)) {
        char copy[8192]; strcpy(copy, line);
        // Cari record yang sesuai id, tanggal, dan gerbong
        if (strstr(copy, kereta->id_kereta) && strstr(copy, kereta->tanggal)) {
            int gIndex = -1;
            int g;
            for (g = 0; g < kereta->jumlah_gerbong; g++) {
                char gerbKey[32];
                sprintf(gerbKey, "Gerbong = 'G%d'", g+1);
                if (strstr(copy, gerbKey)) { gIndex = g; break; }
            }
            if (gIndex >= 0) {
                // Tulis ulang baris dengan status kursi terbaru
                fprintf(fout, "ID_Kereta = '%s' | Gerbong = 'G%d' | Tanggal = '%s' ",
                        kereta->id_kereta, gIndex+1, kereta->tanggal);
                int c,r,s;
                for (c = 0; c < konfig.kolom; c++) {
                    for (r = 0; r < konfig.baris; r++) {
                        fprintf(fout, "| %c%d = '", 'A'+c, r+1);
                        for (s = 0; s < kereta->jumlah_segmen; s++) {
                            fprintf(fout, "%s", kereta->data_kursi[gIndex].status_kursi[c][r][s] ? "True" : "False");
                            if (s + 1 < kereta->jumlah_segmen) fprintf(fout, ",");
                        }
                        fprintf(fout, "' ");
                    }
                }
                fprintf(fout, "\n");
                updated = TRUE;
                continue; // lanjut baca baris berikutnya
            }
        }
        // Baris lain tetap ditulis
        fputs(line, fout);
    }
    fclose(fin);
    fclose(fout);

    if (!updated) {
        // Tidak ada perubahan, hapus file sementara
        remove(tempName);
        return FALSE;
    }
    // Replace file asli dengan file sementara
    remove(namaFile);
    rename(tempName, namaFile);
    return TRUE;
}

// Menghitung jumlah gerbong yang tersedia dalam file database kursi
int HitungJumlahGerbongDariFile(const char *id_kereta, const char *tanggal, const char *namaFile) {
    FILE *f = fopen(namaFile, "r");
    if (!f) return 0;
    char line[8192];
    int maxG = 0;
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, id_kereta) || !strstr(line, tanggal)) continue;
        char *p = strstr(line, "Gerbong");
        if (p) {
            char *eq = strchr(p, '=');
            if (eq) {
                char *val = eq + 1;
                // Skip spaces and quotes
                while (*val && (isspace((unsigned char)*val) || *val == '\'' || *val == '"')) val++;
                int g = atoi(val);
                if (g > maxG) maxG = g;
            }
        }
    }
    fclose(f);
    return maxG;
}

// Menghitung jumlah kolom yang tersedia dalam file database kursi
int HitungJumlahKolomDariFile(const char *id_kereta, const char *tanggal, int gerbong, const char *namaFile) {
    FILE *f = fopen(namaFile, "r");
    if (!f) return 0;
    char line[8192];
    int maxCol = 0;
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, id_kereta) || !strstr(line, tanggal)) continue;
        // Pastikan baris gerbong sesuai
        char gerbKey[32]; sprintf(gerbKey, "Gerbong = 'G%d'", gerbong);
        if (!strstr(line, gerbKey)) continue;
        // Hitung kolom maksimal
        char *part = strtok(line, "|");
        while (part) {
            char *eq = strchr(part, '=');
            if (eq) {
                *eq = '\0';
                char *key = trim(part);
                if (key[0] >= 'A' && key[0] <= 'Z' && isdigit((unsigned char)key[1])) {
                    int col = key[0] - 'A' + 1;
                    if (col > maxCol) maxCol = col;
                }
            }
            part = strtok(NULL, "|");
        }
        break;
    }
    fclose(f);
    return maxCol;
}
