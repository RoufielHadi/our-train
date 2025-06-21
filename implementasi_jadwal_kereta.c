/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

/*
Author:Devi maulani
NIM: 241524007
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_jadwal_kereta.h"
#include <ctype.h>  // for tolower

// Definisikan konstanta untuk nama file jadwal
#define FILE_JADWAL DB_JADWAL_KERETA

// Fungsi pembantu untuk membaca jadwal dari file
boolean BacaJadwalDariFile(FILE* fp, JadwalHarian* jadwal) {
    char buffer[MAX_RECORD_LENGTH];
    if (fgets(buffer, MAX_RECORD_LENGTH, fp) == NULL) {
        return FALSE;
    }
    
    // Parsing record string menjadi JadwalHarian
    Record record;
    InisialisasiRecord(&record);
    StringKeRecord(buffer, &record);
    *jadwal = KonversiRecordKeJadwalKereta(record);
    
    return TRUE;
}

// Fungsi pembantu untuk menyimpan jadwal ke file
void SimpanJadwalKeFile(FILE* fp, JadwalHarian* jadwal) {
    // Konversi jadwal ke record
    Record record;
    InisialisasiRecord(&record);
    KonversiJadwalKeRecord(*jadwal, &record);
    
    // Simpan record ke file
    char recordString[MAX_RECORD_LENGTH];
    RecordKeString(&record, recordString, MAX_RECORD_LENGTH);
    fprintf(fp, "%s\n", recordString);
}

// Fungsi untuk membuat jadwal kereta baru
JadwalHarian BuatJadwalKereta(char* id_kereta, char* tanggal) {
    JadwalHarian jadwal_baru;
    strcpy(jadwal_baru.id_kereta, id_kereta);
    strcpy(jadwal_baru.tanggal, tanggal);
    CreateJadwalKereta(&jadwal_baru.jadwal_rute);
    return jadwal_baru;
}

void CreateListJadwal(ListJadwal *L) {
    L->First = NULL;
}

NodeJadwal* CreateNodeJadwal(JadwalHarian jadwal) {
    NodeJadwal* newNode = (NodeJadwal*)malloc(sizeof(NodeJadwal));
    if (newNode == NULL) return NULL;
    newNode->jadwal = jadwal;
    newNode->next = NULL;
    return newNode;
}

boolean TambahStasiunKeJadwal(JadwalHarian *jadwal, char* nama_stasiun, Waktu waktu_transit) {
    StasiunTransit* stasiun_baru = CreateStasiunTransit(nama_stasiun, KonversiKeWaktuSingkat(waktu_transit));
    if (stasiun_baru == NULL) return FALSE;
    InsertLastJadwal(&jadwal->jadwal_rute, stasiun_baru);
    return TRUE;
}

boolean TambahJadwalKeList(ListJadwal *L, JadwalHarian jadwal) {
    NodeJadwal* node_baru = CreateNodeJadwal(jadwal);
    if (node_baru == NULL) return FALSE;
    if (L->First == NULL) {
        L->First = node_baru;
    } else {
        NodeJadwal* temp = L->First;
        while (temp->next != NULL) temp = temp->next;
        temp->next = node_baru;
    }
    return TRUE;
}

NodeJadwal* CariJadwalByRute(ListJadwal L, const char* asal, const char* tujuan) {
    NodeJadwal* temp = L.First;
    while (temp != NULL) {
        if (IsStasiunTersedia(temp->jadwal, asal) && IsStasiunTersedia(temp->jadwal, tujuan)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

NodeJadwal* CariJadwalLengkap(ListJadwal L, const char* asal, const char* tujuan, const char* tanggal, const char* jenis_layanan) {
    NodeJadwal* temp = L.First;
    while (temp != NULL) {
        if (IsStasiunTersedia(temp->jadwal, asal) && IsStasiunTersedia(temp->jadwal, tujuan) &&
            strcmp(temp->jadwal.tanggal, tanggal) == 0) {

            Record infoKereta;
            if (BacaInformasiKereta(&infoKereta, temp->jadwal.id_kereta)) {
                char* jenis = AmbilNilai(&infoKereta, "jenisLayanan");
                if (jenis != NULL && strcmp(jenis, jenis_layanan) == 0) {
                    return temp;
                }
            }
        }
        temp = temp->next;
    }
    return NULL;
}


boolean UpdateJadwal(ListJadwal *L, char* id_kereta, char* tanggal, JadwalHarian jadwal_baru) {
    NodeJadwal* temp = L->First;
    while (temp != NULL) {
        if (strcmp(temp->jadwal.id_kereta, id_kereta) == 0 &&
            strcmp(temp->jadwal.tanggal, tanggal) == 0) {
            temp->jadwal = jadwal_baru;

            Record record;
            KonversiJadwalKeRecord(jadwal_baru, &record);
            UpdateJadwalKereta(&record);

            return TRUE;
        }
        temp = temp->next;
    }
    return FALSE;
}

JadwalHarian KonversiRecordKeJadwalKereta(Record record) {
    JadwalHarian jadwal;

    const char* id_kereta = AmbilNilai(&record, "kodeJadwal");
    const char* tanggal = AmbilNilai(&record, "tanggal");

    if (id_kereta != NULL)
        strncpy(jadwal.id_kereta, id_kereta, sizeof(jadwal.id_kereta));
    else
        strcpy(jadwal.id_kereta, "UNKNOWN");

    if (tanggal != NULL)
        strncpy(jadwal.tanggal, tanggal, sizeof(jadwal.tanggal));
    else
        strcpy(jadwal.tanggal, "00-00-0000");

    CreateJadwalKereta(&jadwal.jadwal_rute);

    // Coba baca dari format baru (stations dan times)
    const char* stations = AmbilNilai(&record, "stations");
    const char* times = AmbilNilai(&record, "times");

    if (stations != NULL && times != NULL) {
        // Salin string untuk dimodifikasi dengan strtok
        char stationsCopy[MAX_RECORD_LENGTH];
        char timesCopy[MAX_RECORD_LENGTH];
        strcpy(stationsCopy, stations);
        strcpy(timesCopy, times);

        // Parsing stasiun dan waktu
        char* stationToken = strtok(stationsCopy, ",");
        char* timeToken = strtok(timesCopy, ",");

        while (stationToken != NULL && timeToken != NULL) {
            // Parse waktu dari string
            Waktu waktu = {0, 0, 0};
            sscanf(timeToken, "%d:%d", &waktu.jam, &waktu.menit);

            // Tambahkan stasiun ke jadwal
            TambahStasiunKeJadwal(&jadwal, stationToken, waktu);

            // Lanjut ke token berikutnya
            stationToken = strtok(NULL, ",");
            timeToken = strtok(NULL, ",");
        }
    } else {
        // Fallback ke format lama jika format baru tidak tersedia
        const char* asal = AmbilNilai(&record, "stasiunAsal");
        const char* tujuan = AmbilNilai(&record, "stasiunTujuan");
        const char* waktuAsal = AmbilNilai(&record, "waktuAsal");
        const char* waktuTujuan = AmbilNilai(&record, "waktuTujuan");

        if (asal != NULL) {
            Waktu w1 = {7, 0, 0};
            if (waktuAsal != NULL) {
                sscanf(waktuAsal, "%d:%d", &w1.jam, &w1.menit);
            }
            TambahStasiunKeJadwal(&jadwal, (char*)asal, w1);
        }

        if (tujuan != NULL) {
            Waktu w2 = {9, 0, 0};
            if (waktuTujuan != NULL) {
                sscanf(waktuTujuan, "%d:%d", &w2.jam, &w2.menit);
            }
            TambahStasiunKeJadwal(&jadwal, (char*)tujuan, w2);
        }
    }

    return jadwal;
}


// Fungsi untuk mengkonversi JadwalHarian ke Record
void KonversiJadwalKeRecord(JadwalHarian jadwal, Record* record) {
    InisialisasiRecord(record);
    TambahField(record, "kodeJadwal", jadwal.id_kereta);
    // Removed date field as it is no longer needed
    
    // Buat string untuk menyimpan semua stasiun dan waktu transit
    char stations[MAX_RECORD_LENGTH] = "";
    char times[MAX_RECORD_LENGTH] = "";
    
    // Traverse linked list jadwal untuk mengumpulkan semua stasiun dan waktu
    StasiunTransit* curr = jadwal.jadwal_rute.head;
    while (curr != NULL) {
        // Tambahkan nama stasiun ke string stations
        if (strlen(stations) > 0) {
            strcat(stations, ",");
        }
        strcat(stations, curr->nama_stasiun);
        
        // Konversi waktu transit ke format string dan tambahkan ke times
        Waktu waktu = KonversiKeWaktu(curr->waktu_transit);
        char waktuStr[10];
        sprintf(waktuStr, "%02d:%02d", waktu.jam, waktu.menit);
        
        if (strlen(times) > 0) {
            strcat(times, ",");
        }
        strcat(times, waktuStr);
        
        curr = curr->next;
    }
    
    // Tambahkan fields untuk stasiun asal dan tujuan (untuk kompatibilitas)
    if (jadwal.jadwal_rute.head != NULL) {
        TambahField(record, "stasiunAsal", jadwal.jadwal_rute.head->nama_stasiun);
        
        // Temukan stasiun terakhir (tujuan)
        StasiunTransit* last = jadwal.jadwal_rute.head;
        while (last->next != NULL) last = last->next;
        TambahField(record, "stasiunTujuan", last->nama_stasiun);
        
        // Tambahkan waktu keberangkatan dan kedatangan
        Waktu waktuAsal = KonversiKeWaktu(jadwal.jadwal_rute.head->waktu_transit);
        char waktuAsalStr[10];
        sprintf(waktuAsalStr, "%02d:%02d", waktuAsal.jam, waktuAsal.menit);
        TambahField(record, "waktuAsal", waktuAsalStr);
        
        Waktu waktuTujuan = KonversiKeWaktu(last->waktu_transit);
        char waktuTujuanStr[10];
        sprintf(waktuTujuanStr, "%02d:%02d", waktuTujuan.jam, waktuTujuan.menit);
        TambahField(record, "waktuTujuan", waktuTujuanStr);
    }
    
    // Tambahkan semua stasiun dan waktu sebagai fields terpisah
    TambahField(record, "stations", stations);
    TambahField(record, "times", times);
}

// Fungsi untuk menghapus jadwal dari list
boolean HapusJadwal(ListJadwal *L, char* id_kereta, char* tanggal) {
    if (L->First == NULL) {
        return FALSE; // List kosong
    }
    
    // Jika jadwal yang dihapus adalah elemen pertama
    if (strcmp(L->First->jadwal.id_kereta, id_kereta) == 0 && 
        strcmp(L->First->jadwal.tanggal, tanggal) == 0) {
        NodeJadwal* temp = L->First;
        L->First = L->First->next;
        free(temp);
        return TRUE;
    }
    
    // Cari jadwal di posisi lain
    NodeJadwal* prev = L->First;
    NodeJadwal* current = prev->next;
    
    while (current != NULL) {
        if (strcmp(current->jadwal.id_kereta, id_kereta) == 0 && 
            strcmp(current->jadwal.tanggal, tanggal) == 0) {
            // Hapus node current
            prev->next = current->next;
            free(current);
            return TRUE;
        }
        
        prev = current;
        current = current->next;
    }
    
    return FALSE; // Jadwal tidak ditemukan
}

// Fungsi untuk menampilkan jadwal kereta
void TampilkanJadwalKereta(JadwalHarian jadwal) {
    printf("===============================\n");
    printf("Jadwal Kereta %s\n", jadwal.id_kereta);
    printf("Tanggal: %s\n", jadwal.tanggal);
    printf("===============================\n");
    
    if (jadwal.jadwal_rute.head == NULL) {
        printf("Belum ada stasiun dalam jadwal ini.\n");
        return;
    }
    
    StasiunTransit* stasiun = jadwal.jadwal_rute.head;
    int i = 1;
    
    printf("Daftar Stasiun Transit:\n");
    while (stasiun != NULL) {
        printf("%d. %s - ", i++, stasiun->nama_stasiun);
        
        // Konversi WaktuSingkat ke Waktu untuk ditampilkan
        Waktu waktu_tampil;
        waktu_tampil.jam = stasiun->waktu_transit.jam;
        waktu_tampil.menit = stasiun->waktu_transit.menit;
        waktu_tampil.detik = 0;
        
        PrintWaktu(waktu_tampil);
        printf("\n");
        
        stasiun = stasiun->next;
    }
    printf("===============================\n");
}

// Fungsi untuk menampilkan semua jadwal kereta
void TampilkanSemuaJadwal(ListJadwal L) {
    if (L.First == NULL) {
        printf("Belum ada jadwal kereta yang terdaftar.\n");
        return;
    }
    
    NodeJadwal* temp = L.First;
    int count = 1;
    
    printf("===============================\n");
    printf("Daftar Semua Jadwal Kereta:\n");
    printf("===============================\n");
    
    while (temp != NULL) {
        printf("Jadwal #%d:\n", count++);
        printf("ID Kereta: %s\n", temp->jadwal.id_kereta);
        printf("Tanggal: %s\n", temp->jadwal.tanggal);
        
        // Tampilkan daftar stasiun
        if (temp->jadwal.jadwal_rute.head == NULL) {
            printf("Belum ada stasiun dalam jadwal ini.\n");
        } else {
            StasiunTransit* stasiun = temp->jadwal.jadwal_rute.head;
            int i = 1;
            
            printf("Daftar Stasiun Transit:\n");
            while (stasiun != NULL) {
                printf("  %d. %s - ", i++, stasiun->nama_stasiun);
                
                // Konversi WaktuSingkat ke Waktu untuk ditampilkan
                Waktu waktu_tampil;
                waktu_tampil.jam = stasiun->waktu_transit.jam;
                waktu_tampil.menit = stasiun->waktu_transit.menit;
                waktu_tampil.detik = 0;
                
                PrintWaktu(waktu_tampil);
                printf("\n");
                
                stasiun = stasiun->next;
            }
        }
        
        printf("-------------------------------\n");
        temp = temp->next;
    }
}

// Fungsi untuk mencari waktu keberangkatan dari stasiun tertentu
boolean CariWaktuKeberangkatan(JadwalHarian jadwal, char* nama_stasiun, Waktu* hasil_waktu) {
    if (jadwal.jadwal_rute.head == NULL) {
        return FALSE; // Jadwal kosong
    }
    
    StasiunTransit* stasiun = jadwal.jadwal_rute.head;
    
    while (stasiun != NULL) {
        if (strcmp(stasiun->nama_stasiun, nama_stasiun) == 0) {
            // Ditemukan, salin waktu transit ke hasil_waktu
            if (hasil_waktu != NULL) {
                hasil_waktu->jam = stasiun->waktu_transit.jam;
                hasil_waktu->menit = stasiun->waktu_transit.menit;
                hasil_waktu->detik = 0;
            }
            return TRUE;
        }
        stasiun = stasiun->next;
    }
    
    return FALSE; // Stasiun tidak ditemukan
}

// Fungsi untuk menghitung durasi perjalanan antar stasiun
int HitungDurasiPerjalanan(JadwalHarian jadwal, char* stasiun_asal, char* stasiun_tujuan) {
    if (jadwal.jadwal_rute.head == NULL) {
        return -1; // Jadwal kosong
    }
    
    StasiunTransit* stasiun = jadwal.jadwal_rute.head;
    boolean found_asal = FALSE;
    Waktu waktu_asal, waktu_tujuan;
    
    // Cari stasiun asal dan tujuan
    while (stasiun != NULL) {
        if (strcmp(stasiun->nama_stasiun, stasiun_asal) == 0) {
            found_asal = TRUE;
            waktu_asal.jam = stasiun->waktu_transit.jam;
            waktu_asal.menit = stasiun->waktu_transit.menit;
            waktu_asal.detik = 0;
        } else if (strcmp(stasiun->nama_stasiun, stasiun_tujuan) == 0 && found_asal) {
            // Stasiun tujuan ditemukan setelah stasiun asal
            waktu_tujuan.jam = stasiun->waktu_transit.jam;
            waktu_tujuan.menit = stasiun->waktu_transit.menit;
            waktu_tujuan.detik = 0;
            
            // Hitung selisih waktu dalam menit
            int durasi = (waktu_tujuan.jam * 60 + waktu_tujuan.menit) - 
                         (waktu_asal.jam * 60 + waktu_asal.menit);
            
            // Jika durasi negatif (misalnya kereta tiba hari berikutnya), tambahkan 24 jam
            if (durasi < 0) {
                durasi += 24 * 60;
            }
            
            return durasi;
        }
        stasiun = stasiun->next;
    }
    
    return -1; // Stasiun asal atau tujuan tidak ditemukan
}

// Helper function for case-insensitive string comparison
static boolean equalsIgnoreCase(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return FALSE;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

// Fungsi untuk memperbarui waktu transit stasiun
boolean UpdateWaktuTransit(JadwalHarian *jadwal, char* nama_stasiun, Waktu waktu_baru) {
    if (jadwal->jadwal_rute.head == NULL) {
        return FALSE; // Jadwal kosong
    }
    StasiunTransit* stasiun = jadwal->jadwal_rute.head;
    while (stasiun != NULL) {
        if (equalsIgnoreCase(stasiun->nama_stasiun, nama_stasiun)) {
            // Update waktu transit
            stasiun->waktu_transit.jam = waktu_baru.jam;
            stasiun->waktu_transit.menit = waktu_baru.menit;
            return TRUE;
        }
        stasiun = stasiun->next;
    }
    return FALSE; // Stasiun tidak ditemukan
}

// Fungsi untuk mengecek ketersediaan stasiun di jadwal
boolean IsStasiunTersedia(JadwalHarian jadwal, const char* nama_stasiun) {
    if (jadwal.jadwal_rute.head == NULL) {
        return FALSE; // Jadwal kosong
    }
    StasiunTransit* stasiun = jadwal.jadwal_rute.head;
    while (stasiun != NULL) {
        if (equalsIgnoreCase(stasiun->nama_stasiun, nama_stasiun)) {
            return TRUE; // Stasiun ditemukan
        }
        stasiun = stasiun->next;
    }
    return FALSE; // Stasiun tidak ditemukan
}

// Fungsi untuk menyalin jadwal
JadwalHarian SalinJadwal(JadwalHarian jadwal) {
    JadwalHarian jadwal_baru = BuatJadwalKereta(jadwal.id_kereta, jadwal.tanggal);
    
    if (jadwal.jadwal_rute.head == NULL) {
        return jadwal_baru; // Jadwal kosong
    }
    
    StasiunTransit* stasiun = jadwal.jadwal_rute.head;
    
    while (stasiun != NULL) {
        // Konversi WaktuSingkat ke Waktu untuk fungsi TambahStasiunKeJadwal
        Waktu waktu;
        waktu.jam = stasiun->waktu_transit.jam;
        waktu.menit = stasiun->waktu_transit.menit;
        waktu.detik = 0;
        
        TambahStasiunKeJadwal(&jadwal_baru, stasiun->nama_stasiun, waktu);
        stasiun = stasiun->next;
    }
    
    return jadwal_baru;
}

// Fungsi untuk membalik urutan jadwal (stasiun pertama jadi terakhir)
JadwalHarian BalikJadwal(JadwalHarian jadwal) {
    JadwalHarian jadwal_baru = BuatJadwalKereta(jadwal.id_kereta, jadwal.tanggal);
    
    // Balik jadwal rute
    jadwal_baru.jadwal_rute = BalikJadwalKereta(jadwal.jadwal_rute);
    
    return jadwal_baru;
}

// Fungsi untuk mengkonversi string tanggal ke format yang sesuai
boolean KonversiTanggal(char* tanggal_input, char* tanggal_output) {
    // Format input: DD/MM/YYYY atau DD-MM-YYYY
    if (strlen(tanggal_input) != 10) {
        return FALSE;
    }
    
    // Cek format
    if (!((tanggal_input[2] == '/' && tanggal_input[5] == '/') || 
          (tanggal_input[2] == '-' && tanggal_input[5] == '-'))) {
        return FALSE;
    }
    
    // Salin dengan format DD-MM-YYYY
    tanggal_output[0] = tanggal_input[0];
    tanggal_output[1] = tanggal_input[1];
    tanggal_output[2] = '-';
    tanggal_output[3] = tanggal_input[3];
    tanggal_output[4] = tanggal_input[4];
    tanggal_output[5] = '-';
    tanggal_output[6] = tanggal_input[6];
    tanggal_output[7] = tanggal_input[7];
    tanggal_output[8] = tanggal_input[8];
    tanggal_output[9] = tanggal_input[9];
    tanggal_output[10] = '\0';
    
    return TRUE;
}

// Fungsi untuk validasi tanggal
boolean ValidasiTanggal(char* tanggal) {
    // Format: DD-MM-YYYY
    if (strlen(tanggal) != 10) {
        return FALSE;
    }
    
    // Cek format
    if (tanggal[2] != '-' || tanggal[5] != '-') {
        return FALSE;
    }
    
    // Cek apakah semua karakter (kecuali pemisah) adalah digit
    int i;
    for ( i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (tanggal[i] < '0' || tanggal[i] > '9') {
                return FALSE;
            }
        }
    }
    
    // Konversi hari, bulan, tahun ke integer
    int hari = (tanggal[0] - '0') * 10 + (tanggal[1] - '0');
    int bulan = (tanggal[3] - '0') * 10 + (tanggal[4] - '0');
    int tahun = (tanggal[6] - '0') * 1000 + (tanggal[7] - '0') * 100 + 
                (tanggal[8] - '0') * 10 + (tanggal[9] - '0');
    
    // Validasi bulan
    if (bulan < 1 || bulan > 12) {
        return FALSE;
    }
    
    // Validasi hari berdasarkan bulan
    int hari_dalam_bulan[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Cek tahun kabisat
    if (bulan == 2 && ((tahun % 4 == 0 && tahun % 100 != 0) || tahun % 400 == 0)) {
        hari_dalam_bulan[2] = 29;
    }
    
    if (hari < 1 || hari > hari_dalam_bulan[bulan]) {
        return FALSE;
    }
    
    return TRUE;
}

// Implementasi fungsi untuk menghapus jadwal berdasarkan ID kereta
boolean HapusSemuaJadwalByKereta(const char* idKereta) {
    boolean ada_perubahan = FALSE;
    FILE *fp = fopen(FILE_JADWAL, "r");
    if (fp == NULL) return FALSE; // Gagal membuka file
    
    // Baca semua data ke array sementara
    JadwalHarian jadwals[1000]; // Asumsi maksimal 1000 jadwal
    int jumlahJadwal = 0;
    
    JadwalHarian temp;
    while (BacaJadwalDariFile(fp, &temp)) {
        // Jika ID kereta tidak sama dengan yang ingin dihapus, simpan
        if (strcmp(temp.id_kereta, idKereta) != 0) {
            jadwals[jumlahJadwal++] = temp;
        } else {
            ada_perubahan = TRUE; // Set bahwa ada jadwal yang dihapus
        }
    }
    
    fclose(fp);
    
    // Tulis ulang file dengan data yang tersisa
    fp = fopen(FILE_JADWAL, "w");
    if (fp == NULL) return FALSE; // Gagal membuka file
    
    int i;
    for (i = 0; i < jumlahJadwal; i++) {
        SimpanJadwalKeFile(fp, &jadwals[i]);
    }
    
    fclose(fp);
    return ada_perubahan; // Berhasil jika ada perubahan
} 
