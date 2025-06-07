/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "databases.h"

// Definisi nama file database
const char* DB_AKUN_USER = "informasi_akun_user.dat";
const char* DB_REKENING_USER = "informasi_rekening_user.dat";
const char* DB_INFORMASI_KERETA = "informasi_kereta.txt";
const char* DB_JADWAL_KERETA = "jadwal_kereta.txt";
const char* DB_KURSI_KERETA = "kursi_kereta.txt";
const char* DB_RUTE_KERETA = "rute_kereta.txt";
const char* DB_RIWAYAT_PEMBELIAN = "riwayat_pembelian.txt";

// Implementasi fungsi dasar operasi file
FILE* BukaFile(const char* namaFile, const char* mode) {
    FILE* file = fopen(namaFile, mode);
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
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        return FALSE;
    }
    fclose(file);
    return TRUE;
}

void BuatFileJikaBelumAda(const char* namaFile) {
    if (!CekFileAda(namaFile)) {
        FILE* file = fopen(namaFile, "w");
        if (file == NULL) {
            printf("Error: Gagal membuat file %s\n", namaFile);
            return;
        }
        fclose(file);
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

// Implementasi fungsi operasi database
boolean SimpanRecord(const char* namaFile, Record* record, const char* primaryKey) {
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
    
    fprintf(file, "%s\n", recordStr);
    TutupFile(file);
    
    return TRUE;
}

boolean BacaRecord(const char* namaFile, Record* record, const char* primaryKey, const char* primaryValue) {
    if (record == NULL || primaryKey == NULL || primaryValue == NULL) {
        return FALSE;
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
    FILE* tempFilePtr = BukaFile(tempFile, "w");
    if (tempFilePtr == NULL) {
        TutupFile(file);
        return FALSE;
    }
    
    boolean found = FALSE;
    char buffer[MAX_RECORD_LENGTH];
    
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
    
    // Ganti file original dengan file sementara
    remove(namaFile);
    rename(tempFile, namaFile);
    
    return TRUE;
}

boolean HapusRecord(const char* namaFile, const char* primaryKey, const char* primaryValue) {
    if (primaryKey == NULL || primaryValue == NULL) {
        return FALSE;
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
    FILE* tempFilePtr = BukaFile(tempFile, "w");
    if (tempFilePtr == NULL) {
        TutupFile(file);
        return FALSE;
    }
    
    boolean found = FALSE;
    char buffer[MAX_RECORD_LENGTH];
    
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
    
    // Ganti file original dengan file sementara
    remove(namaFile);
    rename(tempFile, namaFile);
    
    return TRUE;
}

// Implementasi fungsi database spesifik

// 1. Akun User
boolean SimpanAkunUser(Record* record) {
    return SimpanRecord(DB_AKUN_USER, record, "username");
}

boolean BacaAkunUser(Record* record, const char* username) {
    return BacaRecord(DB_AKUN_USER, record, "username", username);
}

boolean UpdateAkunUser(Record* record) {
    return UpdateRecord(DB_AKUN_USER, record, "username");
}

boolean HapusAkunUser(const char* username) {
    return HapusRecord(DB_AKUN_USER, "username", username);
}

boolean VerifikasiLogin(const char* username, const char* password) {
    Record userRecord;
    InisialisasiRecord(&userRecord);
    
    if (!BacaAkunUser(&userRecord, username)) {
        return FALSE; // Username tidak ditemukan
    }
    
    char* storedPassword = AmbilNilai(&userRecord, "password");
    if (storedPassword == NULL) {
        return FALSE; // Field password tidak ditemukan
    }
    
    return (strcmp(password, storedPassword) == 0);
}

// 2. Rekening User
boolean SimpanRekeningUser(Record* record) {
    return SimpanRecord(DB_REKENING_USER, record, "nomorRekening");
}

boolean BacaRekeningUser(Record* record, const char* nomorRekening) {
    return BacaRecord(DB_REKENING_USER, record, "nomorRekening", nomorRekening);
}

boolean UpdateRekeningUser(Record* record) {
    return UpdateRecord(DB_REKENING_USER, record, "nomorRekening");
}

boolean HapusRekeningUser(const char* nomorRekening) {
    return HapusRecord(DB_REKENING_USER, "nomorRekening", nomorRekening);
}

// 3. Informasi Kereta
boolean SimpanInformasiKereta(Record* record) {
    return SimpanRecord(DB_INFORMASI_KERETA, record, "kodeKereta");
}

boolean BacaInformasiKereta(Record* record, const char* kodeKereta) {
    return BacaRecord(DB_INFORMASI_KERETA, record, "kodeKereta", kodeKereta);
}

boolean UpdateInformasiKereta(Record* record) {
    return UpdateRecord(DB_INFORMASI_KERETA, record, "kodeKereta");
}

boolean HapusInformasiKereta(const char* kodeKereta) {
    return HapusRecord(DB_INFORMASI_KERETA, "kodeKereta", kodeKereta);
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
    return SimpanRecord(DB_JADWAL_KERETA, record, "kodeJadwal");
}

boolean BacaJadwalKereta(Record* record, const char* kodeJadwal) {
    return BacaRecord(DB_JADWAL_KERETA, record, "kodeJadwal", kodeJadwal);
}

boolean UpdateJadwalKereta(Record* record) {
    return UpdateRecord(DB_JADWAL_KERETA, record, "kodeJadwal");
}

boolean HapusJadwalKereta(const char* kodeJadwal) {
    return HapusRecord(DB_JADWAL_KERETA, "kodeJadwal", kodeJadwal);
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
    
    return SimpanRecord(DB_KURSI_KERETA, record, "primaryKey");
}

boolean BacaKursiKereta(Record* record, const char* kodeKereta, const char* tanggal) {
    char primaryKey[MAX_FIELD_LENGTH * 2];
    sprintf(primaryKey, "%s_%s", kodeKereta, tanggal);
    
    return BacaRecord(DB_KURSI_KERETA, record, "primaryKey", primaryKey);
}

boolean UpdateKursiKereta(Record* record) {
    return UpdateRecord(DB_KURSI_KERETA, record, "primaryKey");
}

boolean HapusKursiKereta(const char* kodeKereta, const char* tanggal) {
    char primaryKey[MAX_FIELD_LENGTH * 2];
    sprintf(primaryKey, "%s_%s", kodeKereta, tanggal);
    
    return HapusRecord(DB_KURSI_KERETA, "primaryKey", primaryKey);
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
    return SimpanRecord(DB_RUTE_KERETA, record, "kodeRute");
}

boolean BacaRuteKereta(Record* record, const char* kodeRute) {
    return BacaRecord(DB_RUTE_KERETA, record, "kodeRute", kodeRute);
}

boolean UpdateRuteKereta(Record* record) {
    return UpdateRecord(DB_RUTE_KERETA, record, "kodeRute");
}

boolean HapusRuteKereta(const char* kodeRute) {
    return HapusRecord(DB_RUTE_KERETA, "kodeRute", kodeRute);
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
    return SimpanRecord(DB_RIWAYAT_PEMBELIAN, record, "kodePembelian");
}

boolean BacaRiwayatPembelian(Record* record, const char* kodePembelian) {
    return BacaRecord(DB_RIWAYAT_PEMBELIAN, record, "kodePembelian", kodePembelian);
}

boolean UpdateRiwayatPembelian(Record* record) {
    return UpdateRecord(DB_RIWAYAT_PEMBELIAN, record, "kodePembelian");
}

boolean HapusRiwayatPembelian(const char* kodePembelian) {
    return HapusRecord(DB_RIWAYAT_PEMBELIAN, "kodePembelian", kodePembelian);
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