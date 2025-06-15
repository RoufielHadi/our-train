/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "time.h"

// ====================== KONSTRUKTOR ===================

// ----- Konstruktor WaktuSingkat -----
WaktuSingkat BuatWaktuSingkat(int jam, int menit, int detik) {
    WaktuSingkat w;
    w.jam = jam;
    w.menit = menit;
    w.detik = detik;
    return w;
}

WaktuSingkat WaktuSingkatSekarang() {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    
    WaktuSingkat w;
    w.detik = tm_now->tm_sec;
    w.menit = tm_now->tm_min;
    w.jam = tm_now->tm_hour;
    
    return w;
}

// ----- Konstruktor Waktu Lengkap -----
Waktu BuatWaktu(int jam, int menit, int detik) {
    Waktu w;
    w.jam = jam;
    w.menit = menit;
    w.detik = detik;
    w.hari = 0;
    w.bulan = 0;
    w.tahun = 0;
    return w;
}

Waktu BuatWaktuLengkap(int hari, int bulan, int tahun, int jam, int menit, int detik) {
    Waktu w;
    w.jam = jam;
    w.menit = menit;
    w.detik = detik;
    w.hari = hari;
    w.bulan = bulan;
    w.tahun = tahun;
    return w;
}

Waktu WaktuSekarang() {
    Waktu w;
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    
    w.detik = tm_now->tm_sec;
    w.menit = tm_now->tm_min;
    w.jam = tm_now->tm_hour;
    w.hari = tm_now->tm_mday;
    w.bulan = tm_now->tm_mon + 1; // tm_mon dimulai dari 0
    w.tahun = tm_now->tm_year + 1900; // tm_year dihitung dari tahun 1900
    
    return w;
}

// ----- Konversi antar tipe waktu -----
WaktuSingkat KonversiKeWaktuSingkat(Waktu w) {
    WaktuSingkat ws;
    ws.jam = w.jam;
    ws.menit = w.menit;
    ws.detik = w.detik;
    return ws;
}

Waktu KonversiKeWaktu(WaktuSingkat ws) {
    Waktu w;
    w.jam = ws.jam;
    w.menit = ws.menit;
    w.detik = ws.detik;
    w.hari = 0;
    w.bulan = 0;
    w.tahun = 0;
    return w;
}

// ============== OPERASI PERBANDINGAN ================

// ----- Perbandingan WaktuSingkat -----
boolean IsWaktuSingkatSama(WaktuSingkat w1, WaktuSingkat w2) {
    return (w1.detik == w2.detik && w1.menit == w2.menit && w1.jam == w2.jam);
}

boolean IsWaktuSingkatLebihAwal(WaktuSingkat w1, WaktuSingkat w2) {
    if (w1.jam < w2.jam) return TRUE;
    if (w1.jam > w2.jam) return FALSE;
    
    if (w1.menit < w2.menit) return TRUE;
    if (w1.menit > w2.menit) return FALSE;
    
    return FALSE;
}

boolean IsWaktuSingkatLebihAkhir(WaktuSingkat w1, WaktuSingkat w2) {
    if (IsWaktuSingkatSama(w1, w2)) return FALSE;
    return !IsWaktuSingkatLebihAwal(w1, w2);
}

int SelisihDetikWaktuSingkat(WaktuSingkat w1, WaktuSingkat w2) {
    int detik1 = w1.detik + w1.menit * 60 + w1.jam * 3600;
    int detik2 = w2.detik + w2.menit * 60 + w2.jam * 3600;
    return detik2 - detik1;
}

// ----- Perbandingan Waktu Lengkap -----
boolean IsWaktuSama(Waktu w1, Waktu w2) {
    return (w1.detik == w2.detik && w1.menit == w2.menit && w1.jam == w2.jam && 
            w1.hari == w2.hari && w1.bulan == w2.bulan && w1.tahun == w2.tahun);
}

boolean IsWaktuLebihAwal(Waktu w1, Waktu w2) {
    if (w1.tahun < w2.tahun) return TRUE;
    if (w1.tahun > w2.tahun) return FALSE;
    
    if (w1.bulan < w2.bulan) return TRUE;
    if (w1.bulan > w2.bulan) return FALSE;
    
    if (w1.hari < w2.hari) return TRUE;
    if (w1.hari > w2.hari) return FALSE;
    
    if (w1.jam < w2.jam) return TRUE;
    if (w1.jam > w2.jam) return FALSE;
    
    if (w1.menit < w2.menit) return TRUE;
    if (w1.menit > w2.menit) return FALSE;
    
    return FALSE;
}

boolean IsWaktuLebihAkhir(Waktu w1, Waktu w2) {
    if (IsWaktuSama(w1, w2)) return FALSE;
    return !IsWaktuLebihAwal(w1, w2);
}

int SelisihDetik(Waktu w1, Waktu w2) {
    // Mengkonversi kedua waktu menjadi detik sejak epoch dan menghitung selisihnya
    time_t time1, time2;
    struct tm tm1 = {0}, tm2 = {0};
    
    tm1.tm_sec = w1.detik;
    tm1.tm_min = w1.menit;
    tm1.tm_hour = w1.jam;
    tm1.tm_mday = (w1.hari > 0) ? w1.hari : 1;
    tm1.tm_mon = (w1.bulan > 0) ? w1.bulan - 1 : 0;
    tm1.tm_year = (w1.tahun > 0) ? w1.tahun - 1900 : 0;
    
    tm2.tm_sec = w2.detik;
    tm2.tm_min = w2.menit;
    tm2.tm_hour = w2.jam;
    tm2.tm_mday = (w2.hari > 0) ? w2.hari : 1;
    tm2.tm_mon = (w2.bulan > 0) ? w2.bulan - 1 : 0;
    tm2.tm_year = (w2.tahun > 0) ? w2.tahun - 1900 : 0;
    
    time1 = mktime(&tm1);
    time2 = mktime(&tm2);
    
    return (int)difftime(time2, time1);
}

int SelisihMenit(Waktu w1, Waktu w2) {
    return SelisihDetik(w1, w2) / 60;
}

int SelisihJam(Waktu w1, Waktu w2) {
    return SelisihDetik(w1, w2) / 3600;
}

int SelisihHari(Waktu w1, Waktu w2) {
    return SelisihDetik(w1, w2) / 86400; // 86400 detik dalam sehari
}

// =============== OPERASI ARITMATIKA =================

// ----- Aritmatika WaktuSingkat -----
WaktuSingkat TambahDetikWaktuSingkat(WaktuSingkat w, int detik) {
    int totalDetik = KonversiKeDetikWaktuSingkat(w) + detik;
    return KonversiDariDetikWaktuSingkat(totalDetik);
}

WaktuSingkat TambahMenitWaktuSingkat(WaktuSingkat w, int menit) {
    return TambahDetikWaktuSingkat(w, menit * 60);
}

WaktuSingkat TambahJamWaktuSingkat(WaktuSingkat w, int jam) {
    return TambahDetikWaktuSingkat(w, jam * 3600);
}

WaktuSingkat KurangDetikWaktuSingkat(WaktuSingkat w, int detik) {
    return TambahDetikWaktuSingkat(w, -detik);
}

// ----- Aritmatika Waktu Lengkap -----
Waktu TambahDetik(Waktu w, int detik) {
    time_t time_result;
    struct tm tm_result = {0};
    
    tm_result.tm_sec = w.detik;
    tm_result.tm_min = w.menit;
    tm_result.tm_hour = w.jam;
    tm_result.tm_mday = (w.hari > 0) ? w.hari : 1;
    tm_result.tm_mon = (w.bulan > 0) ? w.bulan - 1 : 0;
    tm_result.tm_year = (w.tahun > 0) ? w.tahun - 1900 : 0;
    
    time_result = mktime(&tm_result);
    time_result += detik;
    
    tm_result = *localtime(&time_result);
    
    Waktu hasil;
    hasil.detik = tm_result.tm_sec;
    hasil.menit = tm_result.tm_min;
    hasil.jam = tm_result.tm_hour;
    hasil.hari = tm_result.tm_mday;
    hasil.bulan = tm_result.tm_mon + 1;
    hasil.tahun = tm_result.tm_year + 1900;
    
    return hasil;
}

Waktu TambahMenit(Waktu w, int menit) {
    return TambahDetik(w, menit * 60);
}

Waktu TambahJam(Waktu w, int jam) {
    return TambahDetik(w, jam * 3600);
}

Waktu TambahHari(Waktu w, int hari) {
    return TambahDetik(w, hari * 86400);
}

Waktu TambahBulan(Waktu w, int bulan) {
    Waktu hasil = w;
    hasil.bulan += bulan;
    
    // Normalisasi bulan
    while (hasil.bulan > 12) {
        hasil.bulan -= 12;
        hasil.tahun++;
    }
    
    // Sesuaikan hari jika perlu
    int max_hari = 31; // Default untuk bulan dengan 31 hari
    
    if (hasil.bulan == 4 || hasil.bulan == 6 || hasil.bulan == 9 || hasil.bulan == 11) {
        max_hari = 30;
    } else if (hasil.bulan == 2) {
        // Cek tahun kabisat
        if ((hasil.tahun % 4 == 0 && hasil.tahun % 100 != 0) || (hasil.tahun % 400 == 0)) {
            max_hari = 29;
        } else {
            max_hari = 28;
        }
    }
    
    if (hasil.hari > max_hari) {
        hasil.hari = max_hari;
    }
    
    return hasil;
}

Waktu TambahTahun(Waktu w, int tahun) {
    Waktu hasil = w;
    hasil.tahun += tahun;
    
    // Sesuaikan hari jika tanggal 29 Februari dan bukan tahun kabisat
    if (hasil.bulan == 2 && hasil.hari == 29) {
        if (!((hasil.tahun % 4 == 0 && hasil.tahun % 100 != 0) || (hasil.tahun % 400 == 0))) {
            hasil.hari = 28;
        }
    }
    
    return hasil;
}

Waktu KurangDetik(Waktu w, int detik) {
    return TambahDetik(w, -detik);
}

Waktu KurangMenit(Waktu w, int menit) {
    return TambahMenit(w, -menit);
}

Waktu KurangJam(Waktu w, int jam) {
    return TambahJam(w, -jam);
}

Waktu KurangHari(Waktu w, int hari) {
    return TambahHari(w, -hari);
}

// ============= OPERASI UTILITY ===================

// ----- Utility WaktuSingkat -----
void PrintWaktuSingkat(WaktuSingkat w) {
    printf("%02d:%02d:%02d", w.jam, w.menit, w.detik);
}

boolean IsWaktuSingkatValid(int jam, int menit, int detik) {
    return (jam >= 0 && jam < 24 && menit >= 0 && menit < 60 && detik >= 0 && detik < 60);
}

int KonversiKeDetikWaktuSingkat(WaktuSingkat w) {
    return w.detik + w.menit * 60 + w.jam * 3600;
}

WaktuSingkat KonversiDariDetikWaktuSingkat(int totalDetik) {
    WaktuSingkat w;
    
    // Normalisasi jika detik negatif
    while (totalDetik < 0) {
        totalDetik += 86400; // Tambahkan satu hari dalam detik
    }
    
    // Normalisasi jika detik melebihi satu hari
    totalDetik %= 86400; // Satu hari = 24 * 60 * 60 = 86400 detik
    
    w.jam = totalDetik / 3600;
    totalDetik %= 3600;
    w.menit = totalDetik / 60;
    w.detik = totalDetik % 60;
    
    return w;
}

// ----- Utility Waktu Lengkap -----
void PrintWaktu(Waktu w) {
    printf("%02d:%02d:%02d", w.jam, w.menit, w.detik);
}

void PrintWaktuLengkap(Waktu w) {
    printf("%02d/%02d/%04d %02d:%02d:%02d", 
           w.hari, w.bulan, w.tahun, w.jam, w.menit, w.detik);
}

boolean IsWaktuValid(int jam, int menit, int detik) {
    return (jam >= 0 && jam < 24 && menit >= 0 && menit < 60 && detik >= 0 && detik < 60);
}

boolean IsTanggalValid(int tanggal, int bulan, int tahun) {
    // Validasi tahun (tahun harus positif)
    if (tahun <= 0) return FALSE;
    
    // Validasi bulan (bulan harus antara 1-12)
    if (bulan < 1 || bulan > 12) return FALSE;
    
    // Validasi tanggal berdasarkan bulan
    if (tanggal < 1) return FALSE;
    
    // Cek jumlah hari dalam bulan
    int jumlahHari;
    switch (bulan) {
        case 2: // Februari
            // Cek tahun kabisat
            if ((tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0)) {
                jumlahHari = 29;
            } else {
                jumlahHari = 28;
            }
            break;
        case 4: case 6: case 9: case 11: // April, Juni, September, November
            jumlahHari = 30;
            break;
        default: // Januari, Maret, Mei, Juli, Agustus, Oktober, Desember
            jumlahHari = 31;
            break;
    }
    
    return (tanggal <= jumlahHari);
}

int KonversiKeDetik(Waktu w) {
    // Hanya mengkonversi komponen jam-menit-detik
    return w.detik + w.menit * 60 + w.jam * 3600;
}

Waktu KonversiDariDetik(int totalDetik) {
    Waktu w;
    w.jam = totalDetik / 3600;
    totalDetik %= 3600;
    w.menit = totalDetik / 60;
    w.detik = totalDetik % 60;
    w.hari = 0;
    w.bulan = 0;
    w.tahun = 0;
    
    return w;
} 