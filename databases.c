/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

/*
Keterangan File:
- File .dat adalah file data utama yang digunakan untuk menyimpan informasi dalam format biner
  File informasi_akun_user.dat dan informasi_rekening_user.dat menggunakan mode biner (rb/wb/ab)
  untuk operasi I/O yang lebih efisien dan aman terhadap karakter khusus.

- File .bak adalah file backup yang dibuat secara otomatis ketika file .dat diubah atau dihapus.
  File backup ini berguna untuk pemulihan data jika terjadi kerusakan pada file utama.
  Sistem secara otomatis membuat backup sebelum melakukan update atau delete pada data.
*/

#include "databases.h"

// Definisi nama file database
const char* DB_AKUN_USER = "informasi_akun_user.dat";
const char* DB_REKENING_USER = "informasi_rekening_user.dat";
const char* DB_INFORMASI_KERETA = "informasi_kereta.dat";
const char* DB_JADWAL_KERETA = "jadwal_kereta.dat";
const char* DB_KURSI_KERETA = "kursi_kereta.dat";
const char* DB_RUTE_KERETA = "rute_kereta.dat";
const char* DB_RIWAYAT_PEMBELIAN = "riwayat_pembelian.dat";

// Implementasi fungsi dasar operasi file
FILE* BukaFile(const char* namaFile, const char* mode) {
    FILE* file;
    
    // Cek apakah file adalah akun user atau rekening user untuk mode biner
    if ((strcmp(namaFile, "informasi_akun_user.dat") == 0 || 
         strcmp(namaFile, "informasi_rekening_user.dat") == 0)) {
        
        // Pastikan selalu menggunakan mode biner untuk kedua file ini
        char modeBaru[5] = {0};
        
        if (strchr(mode, 'b') == NULL) {
            // Jika belum ada 'b' di mode, tambahkan
            strcpy(modeBaru, mode);
            strcat(modeBaru, "b");
        } else {
            // Mode sudah mengandung 'b'
            strcpy(modeBaru, mode);
        }
        
        file = fopen(namaFile, modeBaru);
    } else {
        // Mode normal untuk file lain
        file = fopen(namaFile, mode);
    }
    
    if (file == NULL) {
        printf("Error: Gagal membuka file %s dengan mode %s\n", namaFile, mode);
    }
    return file;
}

void TutupFile(FILE* file) {
    if (file != NULL) {
        fclose(file);
    }
}

boolean CekFileAda(const char* namaFile) {
    FILE* file = BukaFile(namaFile, "r");
    
    if (file == NULL) {
        return FALSE;
    }
    TutupFile(file);
    return TRUE;
}

void BuatFileJikaBelumAda(const char* namaFile) {
    if (!CekFileAda(namaFile)) {
        FILE* file = BukaFile(namaFile, "w");
        if (file == NULL) {
            printf("Error: Gagal membuat file %s\n", namaFile);
            return;
        }
        TutupFile(file);
        printf("File %s berhasil dibuat.\n", namaFile);
    }
}

// Implementasi fungsi operasi record
void InisialisasiRecord(Record* record) {
    if (record == NULL) {
        return;
    }
    record->fieldCount = 0;
}

void TambahField(Record* record, const char* key, const char* value) {
    if (record == NULL || record->fieldCount >= MAX_FIELDS) {
        return;
    }
    
    // Cek jika key sudah ada, maka update nilainya
    for (int i = 0; i < record->fieldCount; i++) {
        if (strcmp(record->fields[i].key, key) == 0) {
            strncpy(record->fields[i].value, value, MAX_VALUE_LENGTH - 1);
            record->fields[i].value[MAX_VALUE_LENGTH - 1] = '\0';
            return;
        }
    }
    
    // Jika key belum ada, tambahkan field baru
    strncpy(record->fields[record->fieldCount].key, key, MAX_FIELD_LENGTH - 1);
    record->fields[record->fieldCount].key[MAX_FIELD_LENGTH - 1] = '\0';
    
    strncpy(record->fields[record->fieldCount].value, value, MAX_VALUE_LENGTH - 1);
    record->fields[record->fieldCount].value[MAX_VALUE_LENGTH - 1] = '\0';
    
    record->fieldCount++;
}

char* AmbilNilai(Record* record, const char* key) {
    if (record == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < record->fieldCount; i++) {
        if (strcmp(record->fields[i].key, key) == 0) {
            return record->fields[i].value;
        }
    }
    
    return NULL;
}

void UbahNilai(Record* record, const char* key, const char* value) {
    if (record == NULL) {
        return;
    }
    
    for (int i = 0; i < record->fieldCount; i++) {
        if (strcmp(record->fields[i].key, key) == 0) {
            strncpy(record->fields[i].value, value, MAX_VALUE_LENGTH - 1);
            record->fields[i].value[MAX_VALUE_LENGTH - 1] = '\0';
            return;
        }
    }
    
    // Jika key tidak ditemukan, tambahkan field baru
    TambahField(record, key, value);
}

void HapusField(Record* record, const char* key) {
    if (record == NULL) {
        return;
    }
    
    for (int i = 0; i < record->fieldCount; i++) {
        if (strcmp(record->fields[i].key, key) == 0) {
            // Geser field di belakangnya ke depan
            for (int j = i; j < record->fieldCount - 1; j++) {
                strcpy(record->fields[j].key, record->fields[j + 1].key);
                strcpy(record->fields[j].value, record->fields[j + 1].value);
            }
            record->fieldCount--;
            return;
        }
    }
}

void CetakRecord(Record* record) {
    if (record == NULL) {
        printf("Record kosong\n");
        return;
    }
    
    printf("Record (%d fields):\n", record->fieldCount);
    for (int i = 0; i < record->fieldCount; i++) {
        printf("  \"%s\"='%s;'\n", record->fields[i].key, record->fields[i].value);
    }
}

// Implementasi fungsi konversi dan serialisasi
void RecordKeString(Record* record, char* output, int maxLength) {
    if (record == NULL || output == NULL) {
        return;
    }
    
    output[0] = '\0';
    int len = 0;
    
    for (int i = 0; i < record->fieldCount; i++) {
        char buffer[MAX_FIELD_LENGTH + MAX_VALUE_LENGTH + 10]; // Alokasi ekstra untuk tanda petik dan format
        
        // Format: "key"='value;' |
        sprintf(buffer, "\"%s\"='%s;' | ", record->fields[i].key, record->fields[i].value);
        
        // Periksa sisa ruang di output
        if (len + strlen(buffer) >= maxLength - 1) {
            break;
        }
        
        strcat(output, buffer);
        len += strlen(buffer);
    }
    
    // Hapus trailing ' | ' jika ada
    if (len > 3) {
        output[len - 3] = '\0';
    }
}

void StringKeRecord(const char* input, Record* output) {
    if (input == NULL || output == NULL) {
        return;
    }
    
    InisialisasiRecord(output);
    
    char buffer[MAX_RECORD_LENGTH];
    strncpy(buffer, input, MAX_RECORD_LENGTH - 1);
    buffer[MAX_RECORD_LENGTH - 1] = '\0';
    
    char* token = strtok(buffer, "|");
    while (token != NULL) {
        // Parse format: "key"='value;'
        char key[MAX_FIELD_LENGTH] = {0};
        char value[MAX_VALUE_LENGTH] = {0};
        
        // Ekstrak key
        char* keyStart = strchr(token, '"');
        if (keyStart != NULL) {
            keyStart++; // Skip "
            char* keyEnd = strchr(keyStart, '"');
            if (keyEnd != NULL) {
                int keyLen = keyEnd - keyStart;
                if (keyLen < MAX_FIELD_LENGTH) {
                    strncpy(key, keyStart, keyLen);
                    key[keyLen] = '\0';
                }
            }
        }
        
        // Ekstrak value
        char* valueStart = strchr(token, '\'');
        if (valueStart != NULL) {
            valueStart++; // Skip '
            char* valueEnd = strchr(valueStart, ';');
            if (valueEnd != NULL) {
                int valueLen = valueEnd - valueStart;
                if (valueLen < MAX_VALUE_LENGTH) {
                    strncpy(value, valueStart, valueLen);
                    value[valueLen] = '\0';
                }
            }
        }
        
        // Jika berhasil mengekstrak key dan value, tambahkan ke record
        if (strlen(key) > 0 && strlen(value) > 0) {
            TambahField(output, key, value);
        }
        
        token = strtok(NULL, "|");
    }
}

// Implementasi fungsi operasi biner
boolean SimpanRecordBiner(const char* namaFile, Record* record, const char* primaryKey) {
    if (record == NULL || primaryKey == NULL) {
        return FALSE;
    }
    
    // Buat file jika belum ada
    BuatFileJikaBelumAda(namaFile);
    
    // Cek apakah record dengan primary key ini sudah ada
    Record existingRecord;
    InisialisasiRecord(&existingRecord);
    
    char* primaryValue = AmbilNilai(record, primaryKey);
    if (primaryValue == NULL) {
        printf("Error: Primary key '%s' tidak ditemukan dalam record\n", primaryKey);
        return FALSE;
    }
    
    // Jika record sudah ada, gunakan fungsi update
    if (BacaRecordBiner(namaFile, &existingRecord, primaryKey, primaryValue)) {
        return UpdateRecordBiner(namaFile, record, primaryKey);
    }
    
    // Jika record belum ada, tambahkan record baru
    FILE* file = BukaFile(namaFile, "ab"); // append binary
    if (file == NULL) {
        printf("Error: Gagal membuka file %s dalam mode append binary\n", namaFile);
        return FALSE;
    }
    
    // Menulis struktur Record langsung dalam format biner
    size_t result = fwrite(record, sizeof(Record), 1, file);
    
    // Pastikan data ditulis ke disk
    fflush(file);
    
    TutupFile(file);
    
    // Periksa hasil penulisan
    if (result != 1) {
        printf("Error: Gagal menulis record ke file %s\n", namaFile);
        return FALSE;
    }
    
    // Record berhasil ditambahkan
    
    return TRUE;
}

boolean BacaRecordBiner(const char* namaFile, Record* record, const char* primaryKey, const char* primaryValue) {
    if (record == NULL || primaryKey == NULL || primaryValue == NULL) {
        return FALSE;
    }
    
    if (!CekFileAda(namaFile)) {
        printf("Error: File %s tidak ditemukan\n", namaFile);
        return FALSE;
    }
    
    FILE* file = BukaFile(namaFile, "rb"); // read binary
    if (file == NULL) {
        printf("Error: Gagal membuka file %s dalam mode read binary\n", namaFile);
        return FALSE;
    }
    
    boolean found = FALSE;
    Record tempRecord;
    
    // Baca file record per record dalam format biner
    while (fread(&tempRecord, sizeof(Record), 1, file) == 1) {
        // Cek apakah record ini yang dicari
        char* value = AmbilNilai(&tempRecord, primaryKey);
        if (value != NULL && strcmp(value, primaryValue) == 0) {
            // Copy record yang ditemukan
            *record = tempRecord;
            found = TRUE;
            break;
        }
    }
    
    TutupFile(file);
    
    if (!found) {
        // Record tidak ditemukan
    }
    
    return found;
}

boolean UpdateRecordBiner(const char* namaFile, Record* record, const char* primaryKey) {
    if (record == NULL || primaryKey == NULL) {
        return FALSE;
    }
    
    if (!CekFileAda(namaFile)) {
        printf("Error: File %s tidak ditemukan untuk update\n", namaFile);
        return FALSE;
    }
    
    char* primaryValue = AmbilNilai(record, primaryKey);
    if (primaryValue == NULL) {
        printf("Error: Primary key '%s' tidak ditemukan dalam record\n", primaryKey);
        return FALSE;
    }
    
    printf("Melakukan update pada record dengan %s = %s (format biner)\n", primaryKey, primaryValue);
    
    // Buka file untuk membaca
    FILE* file = BukaFile(namaFile, "rb"); // read binary
    if (file == NULL) {
        printf("Error: Gagal membuka file %s dalam mode read binary untuk update\n", namaFile);
        return FALSE;
    }
    
    // Buat file sementara untuk menulis
    char tempFile[100];
    sprintf(tempFile, "%s.tmp", namaFile);
    
    FILE* tempFilePtr = BukaFile(tempFile, "wb"); // write binary
    if (tempFilePtr == NULL) {
        TutupFile(file);
        printf("Error: Gagal membuat file sementara %s\n", tempFile);
        return FALSE;
    }
    
    boolean found = FALSE;
    Record tempRecord;
    
    printf("Mencari dan memperbarui record di %s (format biner)...\n", namaFile);
    
    // Proses record per record
    while (fread(&tempRecord, sizeof(Record), 1, file) == 1) {
        // Cek apakah record ini yang akan diupdate
        char* value = AmbilNilai(&tempRecord, primaryKey);
        if (value != NULL && strcmp(value, primaryValue) == 0) {
            // Tulis record yang diupdate
            fwrite(record, sizeof(Record), 1, tempFilePtr);
            found = TRUE;
            printf("Update record dengan %s = %s (format biner)\n", primaryKey, primaryValue);
        } else {
            // Tulis record original
            fwrite(&tempRecord, sizeof(Record), 1, tempFilePtr);
        }
    }
    
    TutupFile(file);
    TutupFile(tempFilePtr);
    
    // Jika record tidak ditemukan, hapus file sementara dan return FALSE
    if (!found) {
        printf("Tidak ada record dengan %s = %s ditemukan untuk update (format biner)\n", primaryKey, primaryValue);
        remove(tempFile);
        return FALSE;
    }
    
    // Buat backup file asli sebelum melakukan penggantian
    char backupFile[100];
    sprintf(backupFile, "%s.bak", namaFile);
    
    // Hapus backup lama jika ada
    if (CekFileAda(backupFile)) {
        remove(backupFile);
        printf("Backup lama %s dihapus\n", backupFile);
    }
    
    // Buat backup file saat ini
    if (rename(namaFile, backupFile) == 0) {
        printf("Backup file dibuat: %s\n", backupFile);
    } else {
        printf("Gagal membuat backup file: %s\n", backupFile);
    }
    
    // Ganti file original dengan file sementara
    if (rename(tempFile, namaFile) == 0) {
        printf("File berhasil diupdate: %s (format biner)\n", namaFile);
    } else {
        printf("Gagal mengganti file asli dengan file sementara");
        // Coba kembalikan backup jika ada
        if (CekFileAda(backupFile)) {
            rename(backupFile, namaFile);
        }
        return FALSE;
    }
    
    return TRUE;
}

boolean HapusRecordBiner(const char* namaFile, const char* primaryKey, const char* primaryValue) {
    if (primaryKey == NULL || primaryValue == NULL) {
        return FALSE;
    }
    
    if (!CekFileAda(namaFile)) {
        printf("Error: File %s tidak ditemukan untuk hapus\n", namaFile);
        return FALSE;
    }
    
    printf("Menghapus record dengan %s = %s dari file %s (format biner)\n", primaryKey, primaryValue, namaFile);
    
    // Buka file untuk membaca
    FILE* file = BukaFile(namaFile, "rb"); // read binary
    if (file == NULL) {
        printf("Error: Gagal membuka file %s dalam mode read binary untuk hapus\n", namaFile);
        return FALSE;
    }
    
    // Buat file sementara untuk menulis
    char tempFile[100];
    sprintf(tempFile, "%s.tmp", namaFile);
    
    FILE* tempFilePtr = BukaFile(tempFile, "wb"); // write binary
    if (tempFilePtr == NULL) {
        TutupFile(file);
        printf("Error: Gagal membuat file sementara %s\n", tempFile);
        return FALSE;
    }
    
    boolean found = FALSE;
    Record tempRecord;
    int recordCount = 0;
    int deletedCount = 0;
    
    // Proses record per record
    while (fread(&tempRecord, sizeof(Record), 1, file) == 1) {
        recordCount++;
        
        // Cek apakah record ini yang akan dihapus
        char* value = AmbilNilai(&tempRecord, primaryKey);
        if (value != NULL && strcmp(value, primaryValue) == 0) {
            // Ini adalah record yang akan dihapus
            found = TRUE;
            deletedCount++;
            printf("Menghapus record dengan %s = %s (format biner)\n", primaryKey, primaryValue);
        } else {
            // Tulis record original
            fwrite(&tempRecord, sizeof(Record), 1, tempFilePtr);
        }
    }
    
    TutupFile(file);
    TutupFile(tempFilePtr);
    
    printf("Total record diproses: %d, dihapus: %d (format biner)\n", recordCount, deletedCount);
    
    // Jika record tidak ditemukan, hapus file sementara dan return FALSE
    if (!found) {
        printf("Tidak ada record dengan %s = %s ditemukan untuk hapus (format biner)\n", primaryKey, primaryValue);
        remove(tempFile);
        return FALSE;
    }
    
    // Buat backup file asli sebelum melakukan penggantian
    char backupFile[100];
    sprintf(backupFile, "%s.bak", namaFile);
    
    // Hapus backup lama jika ada
    if (CekFileAda(backupFile)) {
        remove(backupFile);
        printf("Backup lama %s dihapus\n", backupFile);
    }
    
    // Buat backup file saat ini
    if (rename(namaFile, backupFile) == 0) {
        printf("Backup file dibuat: %s\n", backupFile);
    } else {
        printf("Gagal membuat backup file: %s\n", backupFile);
    }
    
    // Ganti file original dengan file sementara
    if (rename(tempFile, namaFile) == 0) {
        printf("File berhasil diupdate setelah hapus: %s (format biner)\n", namaFile);
    } else {
        printf("Gagal mengganti file asli dengan file sementara");
        // Coba kembalikan backup jika ada
        if (CekFileAda(backupFile)) {
            rename(backupFile, namaFile);
        }
        return FALSE;
    }
    
    return TRUE;
}

// Implementasi fungsi database spesifik

// 1. Akun User
boolean SimpanAkunUser(Record* record) {
    return SimpanRecordBiner(DB_AKUN_USER, record, "email");
}

boolean BacaAkunUser(Record* record, const char* email) {
    return BacaRecordBiner(DB_AKUN_USER, record, "email", email);
}

boolean UpdateAkunUser(Record* record) {
    return UpdateRecordBiner(DB_AKUN_USER, record, "email");
}

boolean HapusAkunUser(const char* email) {
    return HapusRecordBiner(DB_AKUN_USER, "email", email);
}

boolean VerifikasiLogin(const char* email, const char* password) {
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    if (!BacaAkunUser(&userRecord, email)) {
        return FALSE; // Email tidak ditemukan
    }
    
    char* storedPassword = AmbilNilai(&userRecord, "password");
    if (storedPassword == NULL) {
        return FALSE; // Field password tidak ditemukan
    }
    
    return (strcmp(password, storedPassword) == 0);
}

// 2. Rekening User
boolean SimpanRekeningUser(Record* record) {
    return SimpanRecordBiner(DB_REKENING_USER, record, "email");
}

boolean BacaRekeningUser(Record* record, const char* email) {
    return BacaRecordBiner(DB_REKENING_USER, record, "email", email);
}

boolean UpdateRekeningUser(Record* record) {
    return UpdateRecordBiner(DB_REKENING_USER, record, "email");
}

boolean HapusRekeningUser(const char* email) {
    return HapusRecordBiner(DB_REKENING_USER, "email", email);
}

// 3. Informasi Kereta
boolean SimpanInformasiKereta(Record* record) {
    return SimpanRecordBiner(DB_INFORMASI_KERETA, record, "kodeKereta");
}

boolean BacaInformasiKereta(Record* record, const char* kodeKereta) {
    return BacaRecordBiner(DB_INFORMASI_KERETA, record, "kodeKereta", kodeKereta);
}

boolean UpdateInformasiKereta(Record* record) {
    return UpdateRecordBiner(DB_INFORMASI_KERETA, record, "kodeKereta");
}

boolean HapusInformasiKereta(const char* kodeKereta) {
    return HapusRecordBiner(DB_INFORMASI_KERETA, "kodeKereta", kodeKereta);
}

void DaftarKereta(Record* records, int* jumlahRecord) {
    if (records == NULL || jumlahRecord == NULL) {
        return;
    }
    
    *jumlahRecord = 0;
    
    if (!CekFileAda(DB_INFORMASI_KERETA)) {
        return;
    }
    
    FILE* file = BukaFile(DB_INFORMASI_KERETA, "r");
    if (file == NULL) {
        return;
    }
    
    char buffer[MAX_RECORD_LENGTH];
    
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL && *jumlahRecord < MAX_FIELDS) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        StringKeRecord(buffer, &records[*jumlahRecord]);
        (*jumlahRecord)++;
    }
    
    TutupFile(file);
}

// 4. Jadwal Kereta
boolean SimpanJadwalKereta(Record* record) {
    return SimpanRecordBiner(DB_JADWAL_KERETA, record, "kodeJadwal");
}

boolean BacaJadwalKereta(Record* record, const char* kodeJadwal) {
    return BacaRecordBiner(DB_JADWAL_KERETA, record, "kodeJadwal", kodeJadwal);
}

boolean UpdateJadwalKereta(Record* record) {
    return UpdateRecordBiner(DB_JADWAL_KERETA, record, "kodeJadwal");
}

boolean HapusJadwalKereta(const char* kodeJadwal) {
    return HapusRecordBiner(DB_JADWAL_KERETA, "kodeJadwal", kodeJadwal);
}

void CariJadwalKereta(const char* stasiunAsal, const char* stasiunTujuan, const char* tanggal, Record* records, int* jumlahRecord) {
    if (records == NULL || jumlahRecord == NULL) {
        return;
    }
    
    *jumlahRecord = 0;
    
    if (!CekFileAda(DB_JADWAL_KERETA)) {
        return;
    }
    
    FILE* file = BukaFile(DB_JADWAL_KERETA, "r");
    if (file == NULL) {
        return;
    }
    
    char buffer[MAX_RECORD_LENGTH];
    
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL && *jumlahRecord < MAX_FIELDS) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cek apakah jadwal ini sesuai dengan kriteria pencarian
        char* asalValue = AmbilNilai(&tempRecord, "stasiunAsal");
        char* tujuanValue = AmbilNilai(&tempRecord, "stasiunTujuan");
        char* tanggalValue = AmbilNilai(&tempRecord, "tanggal");
        
        if (asalValue != NULL && tujuanValue != NULL && tanggalValue != NULL) {
            if ((strcmp(stasiunAsal, "") == 0 || strcmp(asalValue, stasiunAsal) == 0) &&
                (strcmp(stasiunTujuan, "") == 0 || strcmp(tujuanValue, stasiunTujuan) == 0) &&
                (strcmp(tanggal, "") == 0 || strcmp(tanggalValue, tanggal) == 0)) {
                
                // Jadwal sesuai dengan kriteria
                records[*jumlahRecord] = tempRecord;
                (*jumlahRecord)++;
            }
        }
    }
    
    TutupFile(file);
}

void BacaSemuaJadwalKereta(Record* records, int* jumlahRecord, int maxRecords) {
    if (records == NULL || jumlahRecord == NULL) {
        return;
    }
    
    *jumlahRecord = 0;
    
    if (!CekFileAda(DB_JADWAL_KERETA)) {
        return;
    }
    
    FILE* file = BukaFile(DB_JADWAL_KERETA, "r");
    if (file == NULL) {
        return;
    }
    
    char buffer[MAX_RECORD_LENGTH];
    
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL && *jumlahRecord < maxRecords) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        StringKeRecord(buffer, &records[*jumlahRecord]);
        (*jumlahRecord)++;
    }
    
    TutupFile(file);
}

// 5. Kursi Kereta
boolean SimpanKursiKereta(Record* record) {
    // Primary key adalah kombinasi kodeKereta dan tanggal
    char primaryKey[MAX_FIELD_LENGTH * 2];
    char* kodeKereta = AmbilNilai(record, "kodeKereta");
    char* tanggal = AmbilNilai(record, "tanggal");
    
    if (kodeKereta == NULL || tanggal == NULL) {
        return FALSE;
    }
    
    sprintf(primaryKey, "%s_%s", kodeKereta, tanggal);
    TambahField(record, "primaryKey", primaryKey);
    
    return SimpanRecordBiner(DB_KURSI_KERETA, record, "primaryKey");
}

boolean BacaKursiKereta(Record* record, const char* kodeKereta, const char* tanggal) {
    char primaryKey[MAX_FIELD_LENGTH * 2];
    sprintf(primaryKey, "%s_%s", kodeKereta, tanggal);
    
    return BacaRecordBiner(DB_KURSI_KERETA, record, "primaryKey", primaryKey);
}

boolean UpdateKursiKereta(Record* record) {
    return UpdateRecordBiner(DB_KURSI_KERETA, record, "primaryKey");
}

boolean HapusKursiKereta(const char* kodeKereta, const char* tanggal) {
    char primaryKey[MAX_FIELD_LENGTH * 2];
    sprintf(primaryKey, "%s_%s", kodeKereta, tanggal);
    
    return HapusRecordBiner(DB_KURSI_KERETA, "primaryKey", primaryKey);
}

void DaftarKursiTersedia(const char* kodeKereta, const char* tanggal, Record* record) {
    InisialisasiRecord(record);
    
    Record kursiRecord;
    InisialisasiRecord(&kursiRecord);
    
    // Baca data kursi kereta
    if (!BacaKursiKereta(&kursiRecord, kodeKereta, tanggal)) {
        return;
    }
    
    // Cari field kursiTersedia di record
    char* kursiTersedia = AmbilNilai(&kursiRecord, "kursiTersedia");
    if (kursiTersedia != NULL) {
        TambahField(record, "kursiTersedia", kursiTersedia);
    }
}

// 6. Rute Kereta
boolean SimpanRuteKereta(Record* record) {
    return SimpanRecordBiner(DB_RUTE_KERETA, record, "kodeRute");
}

boolean BacaRuteKereta(Record* record, const char* kodeRute) {
    return BacaRecordBiner(DB_RUTE_KERETA, record, "kodeRute", kodeRute);
}

boolean UpdateRuteKereta(Record* record) {
    return UpdateRecordBiner(DB_RUTE_KERETA, record, "kodeRute");
}

boolean HapusRuteKereta(const char* kodeRute) {
    return HapusRecordBiner(DB_RUTE_KERETA, "kodeRute", kodeRute);
}

void CariRute(const char* stasiunAsal, const char* stasiunTujuan, Record* records, int* jumlahRecord) {
    if (records == NULL || jumlahRecord == NULL) {
        return;
    }
    
    *jumlahRecord = 0;
    
    if (!CekFileAda(DB_RUTE_KERETA)) {
        return;
    }
    
    FILE* file = BukaFile(DB_RUTE_KERETA, "r");
    if (file == NULL) {
        return;
    }
    
    char buffer[MAX_RECORD_LENGTH];
    
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL && *jumlahRecord < MAX_FIELDS) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cek apakah rute ini sesuai dengan kriteria pencarian
        char* asalValue = AmbilNilai(&tempRecord, "stasiunAsal");
        char* tujuanValue = AmbilNilai(&tempRecord, "stasiunTujuan");
        
        if (asalValue != NULL && tujuanValue != NULL) {
            if ((strcmp(stasiunAsal, "") == 0 || strcmp(asalValue, stasiunAsal) == 0) &&
                (strcmp(stasiunTujuan, "") == 0 || strcmp(tujuanValue, stasiunTujuan) == 0)) {
                
                // Rute sesuai dengan kriteria
                records[*jumlahRecord] = tempRecord;
                (*jumlahRecord)++;
            }
        }
    }
    
    TutupFile(file);
}

// 7. Riwayat Pembelian
boolean SimpanRiwayatPembelian(Record* record) {
    return SimpanRecordBiner(DB_RIWAYAT_PEMBELIAN, record, "kodePembelian");
}

boolean BacaRiwayatPembelian(Record* record, const char* kodePembelian) {
    return BacaRecordBiner(DB_RIWAYAT_PEMBELIAN, record, "kodePembelian", kodePembelian);
}

boolean UpdateRiwayatPembelian(Record* record) {
    return UpdateRecordBiner(DB_RIWAYAT_PEMBELIAN, record, "kodePembelian");
}

boolean HapusRiwayatPembelian(const char* kodePembelian) {
    return HapusRecordBiner(DB_RIWAYAT_PEMBELIAN, "kodePembelian", kodePembelian);
}

void RiwayatPembelianUser(const char* username, Record* records, int* jumlahRecord) {
    if (records == NULL || jumlahRecord == NULL) {
        return;
    }
    
    *jumlahRecord = 0;
    
    if (!CekFileAda(DB_RIWAYAT_PEMBELIAN)) {
        return;
    }
    
    FILE* file = BukaFile(DB_RIWAYAT_PEMBELIAN, "r");
    if (file == NULL) {
        return;
    }
    
    char buffer[MAX_RECORD_LENGTH];
    
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL && *jumlahRecord < MAX_FIELDS) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cek apakah riwayat ini milik user yang dicari
        char* usernameValue = AmbilNilai(&tempRecord, "username");
        
        if (usernameValue != NULL && strcmp(usernameValue, username) == 0) {
            // Riwayat pembelian user yang dicari
            records[*jumlahRecord] = tempRecord;
            (*jumlahRecord)++;
        }
    }
    
    TutupFile(file);
}

// Implementasi fungsi operasi database
boolean SimpanRecord(const char* namaFile, Record* record, const char* primaryKey) {
    if (record == NULL || primaryKey == NULL) {
        return FALSE;
    }
    
    // Untuk file akun dan rekening user, gunakan operasi biner
    if (strcmp(namaFile, DB_AKUN_USER) == 0 || strcmp(namaFile, DB_REKENING_USER) == 0) {
        return SimpanRecordBiner(namaFile, record, primaryKey);
    }
    
    // Buat file jika belum ada
    BuatFileJikaBelumAda(namaFile);
    
    // Cek apakah record dengan primary key ini sudah ada
    Record existingRecord;
    InisialisasiRecord(&existingRecord);
    
    char* primaryValue = AmbilNilai(record, primaryKey);
    if (primaryValue == NULL) {
        printf("Error: Primary key '%s' tidak ditemukan dalam record\n", primaryKey);
        return FALSE;
    }
    
    // Jika record sudah ada, gunakan fungsi update
    if (BacaRecord(namaFile, &existingRecord, primaryKey, primaryValue)) {
        return UpdateRecord(namaFile, record, primaryKey);
    }
    
    // Jika record belum ada, tambahkan record baru
    FILE* file = BukaFile(namaFile, "a");
    if (file == NULL) {
        return FALSE;
    }
    
    char recordStr[MAX_RECORD_LENGTH];
    RecordKeString(record, recordStr, MAX_RECORD_LENGTH);
    
    // Tulis record ke file (sama untuk mode biner dan teks)
    fprintf(file, "%s\n", recordStr);
    
    TutupFile(file);
    
    return TRUE;
}

boolean BacaRecord(const char* namaFile, Record* record, const char* primaryKey, const char* primaryValue) {
    if (record == NULL || primaryKey == NULL || primaryValue == NULL) {
        return FALSE;
    }
    
    // Untuk file akun dan rekening user, gunakan operasi biner
    if (strcmp(namaFile, DB_AKUN_USER) == 0 || strcmp(namaFile, DB_REKENING_USER) == 0) {
        return BacaRecordBiner(namaFile, record, primaryKey, primaryValue);
    }
    
    if (!CekFileAda(namaFile)) {
        return FALSE;
    }
    
    FILE* file = BukaFile(namaFile, "r");
    if (file == NULL) {
        return FALSE;
    }
    
    boolean found = FALSE;
    char buffer[MAX_RECORD_LENGTH];
    
    // Baca file baris per baris (sama untuk mode biner dan teks)
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cek apakah record ini yang dicari
        char* value = AmbilNilai(&tempRecord, primaryKey);
        if (value != NULL && strcmp(value, primaryValue) == 0) {
            // Copy record yang ditemukan
            *record = tempRecord;
            found = TRUE;
            break;
        }
    }
    
    TutupFile(file);
    return found;
}

boolean UpdateRecord(const char* namaFile, Record* record, const char* primaryKey) {
    if (record == NULL || primaryKey == NULL) {
        return FALSE;
    }
    
    // Untuk file akun dan rekening user, gunakan operasi biner
    if (strcmp(namaFile, DB_AKUN_USER) == 0 || strcmp(namaFile, DB_REKENING_USER) == 0) {
        return UpdateRecordBiner(namaFile, record, primaryKey);
    }
    
    if (!CekFileAda(namaFile)) {
        return FALSE;
    }
    
    char* primaryValue = AmbilNilai(record, primaryKey);
    if (primaryValue == NULL) {
        printf("Error: Primary key '%s' tidak ditemukan dalam record\n", primaryKey);
        return FALSE;
    }
    
    // Buka file untuk membaca
    FILE* file = BukaFile(namaFile, "r");
    if (file == NULL) {
        return FALSE;
    }
    
    // Buat file sementara untuk menulis
    char tempFile[100];
    sprintf(tempFile, "%s.tmp", namaFile);
    
    FILE* tempFilePtr = fopen(tempFile, "w");
    if (tempFilePtr == NULL) {
        TutupFile(file);
        return FALSE;
    }
    
    boolean found = FALSE;
    char buffer[MAX_RECORD_LENGTH];
    
    // Proses baris per baris (sama untuk mode biner dan teks)
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record untuk pengecekan
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cek apakah record ini yang akan diupdate
        char* value = AmbilNilai(&tempRecord, primaryKey);
        if (value != NULL && strcmp(value, primaryValue) == 0) {
            // Tulis record yang diupdate
            char updatedRecordStr[MAX_RECORD_LENGTH];
            RecordKeString(record, updatedRecordStr, MAX_RECORD_LENGTH);
            fprintf(tempFilePtr, "%s\n", updatedRecordStr);
            found = TRUE;
        } else {
            // Tulis record original
            fprintf(tempFilePtr, "%s\n", buffer);
        }
    }
    
    TutupFile(file);
    TutupFile(tempFilePtr);
    
    // Jika record tidak ditemukan, hapus file sementara dan return FALSE
    if (!found) {
        remove(tempFile);
        return FALSE;
    }
    
    // Buat backup file asli sebelum melakukan penggantian
    char backupFile[100];
    sprintf(backupFile, "%s.bak", namaFile);
    
    // Hapus backup lama jika ada
    if (CekFileAda(backupFile)) {
        remove(backupFile);
    }
    
    // Buat backup file saat ini
    rename(namaFile, backupFile);
    
    // Ganti file original dengan file sementara
    rename(tempFile, namaFile);
    
    return TRUE;
}

boolean HapusRecord(const char* namaFile, const char* primaryKey, const char* primaryValue) {
    if (primaryKey == NULL || primaryValue == NULL) {
        return FALSE;
    }
    
    // Untuk file akun dan rekening user, gunakan operasi biner
    if (strcmp(namaFile, DB_AKUN_USER) == 0 || strcmp(namaFile, DB_REKENING_USER) == 0) {
        return HapusRecordBiner(namaFile, primaryKey, primaryValue);
    }
    
    if (!CekFileAda(namaFile)) {
        return FALSE;
    }
    
    // Buka file untuk membaca
    FILE* file = BukaFile(namaFile, "r");
    if (file == NULL) {
        return FALSE;
    }
    
    // Buat file sementara untuk menulis
    char tempFile[100];
    sprintf(tempFile, "%s.tmp", namaFile);
    
    FILE* tempFilePtr = fopen(tempFile, "w");
    if (tempFilePtr == NULL) {
        TutupFile(file);
        return FALSE;
    }
    
    boolean found = FALSE;
    char buffer[MAX_RECORD_LENGTH];
    
    // Proses baris per baris (sama untuk mode biner dan teks)
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record untuk pengecekan
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cek apakah record ini yang akan dihapus
        char* value = AmbilNilai(&tempRecord, primaryKey);
        if (value != NULL && strcmp(value, primaryValue) == 0) {
            found = TRUE;
            // Skip record ini (tidak ditulis ke file sementara)
        } else {
            // Tulis record original
            fprintf(tempFilePtr, "%s\n", buffer);
        }
    }
    
    TutupFile(file);
    TutupFile(tempFilePtr);
    
    // Jika record tidak ditemukan, hapus file sementara dan return FALSE
    if (!found) {
        remove(tempFile);
        return FALSE;
    }
    
    // Buat backup file asli sebelum melakukan penggantian
    char backupFile[100];
    sprintf(backupFile, "%s.bak", namaFile);
    
    // Hapus backup lama jika ada
    if (CekFileAda(backupFile)) {
        remove(backupFile);
    }
    
    // Buat backup file saat ini
    rename(namaFile, backupFile);
    
    // Ganti file original dengan file sementara
    rename(tempFile, namaFile);
    
    return TRUE;
}

// Menghapus file informasi_akun_user.dat dan informasi_rekening_user.dat
void HapusFileLama() {
    // Hapus file .dat dan .bak yang lama
    if (CekFileAda("informasi_akun_user.dat")) {
        remove("informasi_akun_user.dat");
    }
    if (CekFileAda("informasi_akun_user.bak")) {
        remove("informasi_akun_user.bak");
    }
    if (CekFileAda("informasi_rekening_user.dat")) {
        remove("informasi_rekening_user.dat");
    }
    if (CekFileAda("informasi_rekening_user.bak")) {
        remove("informasi_rekening_user.bak");
    }
    
    printf("File informasi akun dan rekening lama telah dihapus.\n");
    printf("File baru akan dibuat menggunakan format biner.\n");
}

// Fungsi untuk menampilkan seluruh isi record untuk debug
void TampilkanRecord(Record* record, const char* title) {
    if (record == NULL) {
        printf("%s: Record kosong\n", title);
        return;
    }
    
    printf("------ %s ------\n", title);
    printf("Jumlah field: %d\n", record->fieldCount);
    
    for (int i = 0; i < record->fieldCount; i++) {
        printf("Field %d: '%s' = '%s'\n", 
              i, record->fields[i].key, record->fields[i].value);
    }
    printf("-----------------------\n");
}

// Fungsi untuk menampilkan isi file (debugging)
void TampilkanIsiFile(const char* namaFile) {
    if (!CekFileAda(namaFile)) {
        printf("File %s tidak ada.\n", namaFile);
        return;
    }
    
    FILE* file = BukaFile(namaFile, "rb"); // read binary
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", namaFile);
        return;
    }
    
    printf("=== Isi File %s ===\n", namaFile);
    
    char buffer[MAX_RECORD_LENGTH];
    int lineCount = 0;
    
    while (fgets(buffer, MAX_RECORD_LENGTH, file) != NULL) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        printf("Baris %d: %s\n", ++lineCount, buffer);
        
        // Konversi string ke record untuk menampilkan data
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Cetak isi record
        CetakRecord(&tempRecord);
    }
    
    printf("=== Total %d baris ===\n", lineCount);
    
    TutupFile(file);
}

// Fungsi untuk mengkonversi file dari format teks ke format biner
boolean KonversiFileTeksToBiner(const char* namaFile) {
    if (namaFile == NULL) {
        return FALSE;
    }
    
    if (!CekFileAda(namaFile)) {
        printf("Error: File %s tidak ditemukan untuk konversi\n", namaFile);
        return FALSE;
    }
    
    printf("Mengkonversi file %s dari format teks ke format biner...\n", namaFile);
    
    // Buka file teks untuk dibaca
    FILE* fileText = BukaFile(namaFile, "r"); // read text
    if (fileText == NULL) {
        printf("Error: Gagal membuka file %s dalam mode baca teks\n", namaFile);
        return FALSE;
    }
    
    // Buat file sementara untuk menulis dalam format biner
    char tempFile[100];
    sprintf(tempFile, "%s.bin.tmp", namaFile);
    
    FILE* fileBiner = BukaFile(tempFile, "wb"); // write binary
    if (fileBiner == NULL) {
        TutupFile(fileText);
        printf("Error: Gagal membuat file sementara %s\n", tempFile);
        return FALSE;
    }
    
    char buffer[MAX_RECORD_LENGTH];
    int recordCount = 0;
    
    // Proses baris per baris dari file teks
    while (fgets(buffer, MAX_RECORD_LENGTH, fileText) != NULL) {
        // Hapus newline jika ada
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Konversi string ke record
        Record tempRecord;
        InisialisasiRecord(&tempRecord);
        StringKeRecord(buffer, &tempRecord);
        
        // Tulis record dalam format biner
        fwrite(&tempRecord, sizeof(Record), 1, fileBiner);
        recordCount++;
    }
    
    TutupFile(fileText);
    TutupFile(fileBiner);
    
    printf("Total record dikonversi: %d\n", recordCount);
    
    // Buat backup file asli
    char backupFile[100];
    sprintf(backupFile, "%s.text.bak", namaFile);
    
    // Hapus backup lama jika ada
    if (CekFileAda(backupFile)) {
        remove(backupFile);
    }
    
    // Buat backup file teks
    if (rename(namaFile, backupFile) != 0) {
        printf("Error: Gagal membuat backup file teks\n");
        remove(tempFile);
        return FALSE;
    }
    
    // Ganti file original dengan file biner
    if (rename(tempFile, namaFile) != 0) {
        printf("Error: Gagal mengganti file original dengan file biner\n");
        // Coba kembalikan backup
        rename(backupFile, namaFile);
        return FALSE;
    }
    
    printf("File %s berhasil dikonversi ke format biner\n", namaFile);
    return TRUE;
}

// Fungsi untuk mengkonversi semua file database ke format biner
boolean KonversiDatabaseKeBiner() {
    boolean success = TRUE;
    
    printf("Mengkonversi semua file database ke format biner...\n");
    
    // Cek dan konversi file akun user
    if (CekFileAda(DB_AKUN_USER)) {
        if (!KonversiFileTeksToBiner(DB_AKUN_USER)) {
            printf("Gagal mengkonversi file %s\n", DB_AKUN_USER);
            success = FALSE;
        }
    }
    
    // Cek dan konversi file rekening user
    if (CekFileAda(DB_REKENING_USER)) {
        if (!KonversiFileTeksToBiner(DB_REKENING_USER)) {
            printf("Gagal mengkonversi file %s\n", DB_REKENING_USER);
            success = FALSE;
        }
    }
    
    if (success) {
        printf("Semua file database berhasil dikonversi ke format biner\n");
    } else {
        printf("Terdapat error pada proses konversi database\n");
    }
    
    return success;
} 