/*
Author: Adi Rafi Chaerufarizki 
NIM: 241524001  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "implementasi_informasi_kereta.h"
#include "databases.h"

// Fungsi untuk membuat informasi kereta baru
InformasiKereta BuatInformasiKereta(char* id_kereta, char* nama_kereta, char* jenis_layanan, float harga_tiket, char* jumlah_gerbong) {
    InformasiKereta kereta_baru;
    
    // Salin data ke struktur kereta
    strcpy(kereta_baru.id_Kereta, id_kereta);
    strcpy(kereta_baru.nama_kereta, nama_kereta);
    strcpy(kereta_baru.jenis_layanan, jenis_layanan);
    kereta_baru.harga_tiket = harga_tiket;
    strcpy(kereta_baru.jumlah_gerbong, jumlah_gerbong);
    
    // Inisialisasi jadwal kosong
    CreateJadwalKereta(&kereta_baru.jadwal);
    
    return kereta_baru;
}

// Fungsi untuk menambahkan informasi kereta ke dalam list
boolean TambahInformasiKereta(ListKereta *L, InformasiKereta kereta_baru) {
    // Cek apakah ID kereta sudah terdaftar
    if (SearchKeretaById(*L, kereta_baru.id_Kereta) != NULL) {
        return FALSE; // ID kereta sudah terdaftar
    }
    
    // Buat node baru
    DataInformasiKereta *new_kereta = CreateDataKereta(kereta_baru);
    if (new_kereta == NULL) {
        return FALSE; // Gagal alokasi memori
    }
    
    // Tambahkan ke list
    InsertLastKereta(L, new_kereta);
    return TRUE;
}

// Fungsi untuk mencari informasi kereta berdasarkan ID
boolean CariInformasiKereta(ListKereta L, char* id_kereta, InformasiKereta* hasil) {
    DataInformasiKereta *kereta_node = SearchKeretaById(L, id_kereta);
    if (kereta_node == NULL) {
        return FALSE; // ID kereta tidak ditemukan
    }
    
    // Salin data kereta jika hasil tidak NULL
    if (hasil != NULL) {
        *hasil = kereta_node->kereta_info;
    }
    
    return TRUE;
}

// Fungsi untuk menampilkan informasi kereta
void TampilkanInformasiKereta(InformasiKereta kereta) {
    printf("===============================\n");
    printf("Informasi Kereta:\n");
    printf("ID: %s\n", kereta.id_Kereta);
    printf("Nama: %s\n", kereta.nama_kereta);
    printf("Jenis Layanan: %s\n", kereta.jenis_layanan);
    printf("Harga Tiket: Rp%.2f\n", kereta.harga_tiket);
    printf("Jumlah Gerbong: %s\n", kereta.jumlah_gerbong);
    
    // Tampilkan jadwal jika ada
    if (!isEmptyJadwal(kereta.jadwal)) {
        printf("\nJadwal Stasiun Transit:\n");
        PrintJadwal(kereta.jadwal);
    }
    
    printf("===============================\n");
}

// Fungsi untuk menampilkan semua informasi kereta
void TampilkanSemuaInformasiKereta(ListKereta L) {
    if (isEmptyKereta(L)) {
        printf("Daftar kereta kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Daftar Semua Kereta:\n");
    printf("===============================\n");
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 1;
    
    while (kereta_node != NULL) {
        printf("Kereta #%d\n", count++);
        printf("ID: %s\n", kereta_node->kereta_info.id_Kereta);
        printf("Nama: %s\n", kereta_node->kereta_info.nama_kereta);
        printf("Jenis Layanan: %s\n", kereta_node->kereta_info.jenis_layanan);
        printf("Harga Tiket: Rp%.2f\n", kereta_node->kereta_info.harga_tiket);
        printf("Jumlah Gerbong: %s\n", kereta_node->kereta_info.jumlah_gerbong);
        printf("-------------------------------\n");
        
        kereta_node = kereta_node->next;
    }
}

// Fungsi untuk memfilter kereta berdasarkan jenis layanan
void FilterKeretaBerdasarkanLayanan(ListKereta L, char* jenis_layanan) {
    if (isEmptyKereta(L)) {
        printf("Daftar kereta kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Kereta dengan Layanan %s:\n", jenis_layanan);
    printf("===============================\n");
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 1;
    boolean found = FALSE;
    
    while (kereta_node != NULL) {
        if (strcmp(kereta_node->kereta_info.jenis_layanan, jenis_layanan) == 0) {
            printf("Kereta #%d\n", count++);
            printf("ID: %s\n", kereta_node->kereta_info.id_Kereta);
            printf("Nama: %s\n", kereta_node->kereta_info.nama_kereta);
            printf("Harga Tiket: Rp%.2f\n", kereta_node->kereta_info.harga_tiket);
            printf("Jumlah Gerbong: %s\n", kereta_node->kereta_info.jumlah_gerbong);
            printf("-------------------------------\n");
            found = TRUE;
        }
        
        kereta_node = kereta_node->next;
    }
    
    if (!found) {
        printf("Tidak ada kereta dengan layanan %s.\n", jenis_layanan);
    }
}

// Fungsi untuk memfilter kereta berdasarkan rentang harga
void FilterKeretaBerdasarkanHarga(ListKereta L, float harga_min, float harga_max) {
    if (isEmptyKereta(L)) {
        printf("Daftar kereta kosong.\n");
        return;
    }
    
    printf("===============================\n");
    printf("Kereta dengan Harga Rp%.2f - Rp%.2f:\n", harga_min, harga_max);
    printf("===============================\n");
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 1;
    boolean found = FALSE;
    
    while (kereta_node != NULL) {
        if (kereta_node->kereta_info.harga_tiket >= harga_min && 
            kereta_node->kereta_info.harga_tiket <= harga_max) {
            printf("Kereta #%d\n", count++);
            printf("ID: %s\n", kereta_node->kereta_info.id_Kereta);
            printf("Nama: %s\n", kereta_node->kereta_info.nama_kereta);
            printf("Jenis Layanan: %s\n", kereta_node->kereta_info.jenis_layanan);
            printf("Harga Tiket: Rp%.2f\n", kereta_node->kereta_info.harga_tiket);
            printf("Jumlah Gerbong: %s\n", kereta_node->kereta_info.jumlah_gerbong);
            printf("-------------------------------\n");
            found = TRUE;
        }
        
        kereta_node = kereta_node->next;
    }
    
    if (!found) {
        printf("Tidak ada kereta dengan rentang harga tersebut.\n");
    }
}

// Fungsi untuk mengurutkan kereta berdasarkan harga (ascending)
ListKereta UrutkanKeretaBerdasarkanHarga(ListKereta L, boolean ascending) {
    if (isEmptyKereta(L) || NbElmtKereta(L) == 1) {
        return L; // List kosong atau hanya memiliki 1 elemen
    }
    
    // Implementasi algoritma bubble sort
    DataInformasiKereta *temp_current, *temp_next;
    InformasiKereta temp_kereta;
    int n = NbElmtKereta(L);
    boolean swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = FALSE;
        temp_current = L.First;
        
        for (int j = 0; j < n - i - 1; j++) {
            temp_next = temp_current->next;
            
            boolean should_swap;
            if (ascending) {
                should_swap = temp_current->kereta_info.harga_tiket > temp_next->kereta_info.harga_tiket;
            } else {
                should_swap = temp_current->kereta_info.harga_tiket < temp_next->kereta_info.harga_tiket;
            }
            
            if (should_swap) {
                // Swap data kereta
                temp_kereta = temp_current->kereta_info;
                temp_current->kereta_info = temp_next->kereta_info;
                temp_next->kereta_info = temp_kereta;
                swapped = TRUE;
            }
            
            temp_current = temp_current->next;
        }
        
        if (!swapped) {
            break; // Jika tidak ada swap, berarti sudah terurut
        }
    }
    
    return L;
}

// Fungsi untuk mengurutkan kereta berdasarkan nama (alphabetical)
ListKereta UrutkanKeretaBerdasarkanNama(ListKereta L) {
    if (isEmptyKereta(L) || NbElmtKereta(L) == 1) {
        return L; // List kosong atau hanya memiliki 1 elemen
    }
    
    // Implementasi algoritma bubble sort
    DataInformasiKereta *temp_current, *temp_next;
    InformasiKereta temp_kereta;
    int n = NbElmtKereta(L);
    boolean swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = FALSE;
        temp_current = L.First;
        
        for (int j = 0; j < n - i - 1; j++) {
            temp_next = temp_current->next;
            
            if (strcmp(temp_current->kereta_info.nama_kereta, temp_next->kereta_info.nama_kereta) > 0) {
                // Swap data kereta
                temp_kereta = temp_current->kereta_info;
                temp_current->kereta_info = temp_next->kereta_info;
                temp_next->kereta_info = temp_kereta;
                swapped = TRUE;
            }
            
            temp_current = temp_current->next;
        }
        
        if (!swapped) {
            break; // Jika tidak ada swap, berarti sudah terurut
        }
    }
    
    return L;
}

// Fungsi untuk validasi ID kereta
boolean ValidasiIDKereta(char* id_kereta) {
    // Cek panjang ID kereta (umumnya 3-8 karakter)
    int panjang = strlen(id_kereta);
    if (panjang < 3 || panjang > 8) {
        return FALSE;
    }
    
    // ID kereta biasanya diawali dengan huruf dan diikuti angka
    if (!(id_kereta[0] >= 'A' && id_kereta[0] <= 'Z')) {
        return FALSE;
    }
    
    // Cek karakter lainnya (hanya huruf dan angka)
    for (int i = 0; i < panjang; i++) {
        if (!((id_kereta[i] >= 'A' && id_kereta[i] <= 'Z') || 
              (id_kereta[i] >= '0' && id_kereta[i] <= '9'))) {
            return FALSE;
        }
    }
    
    return TRUE;
}

// Fungsi untuk validasi jenis layanan
boolean ValidasiJenisLayanan(char* jenis_layanan) {
    return (strcmp(jenis_layanan, EKONOMI) == 0 || 
            strcmp(jenis_layanan, BISNIS) == 0 || 
            strcmp(jenis_layanan, EKSEKUTIF) == 0 || 
            strcmp(jenis_layanan, LUXURY) == 0);
}

// Fungsi untuk menghitung jumlah kereta berdasarkan jenis layanan
int HitungJumlahKeretaBerdasarkanLayanan(ListKereta L, char* jenis_layanan) {
    if (isEmptyKereta(L)) {
        return 0;
    }
    
    DataInformasiKereta *kereta_node = L.First;
    int count = 0;
    
    while (kereta_node != NULL) {
        if (strcmp(kereta_node->kereta_info.jenis_layanan, jenis_layanan) == 0) {
            count++;
        }
        kereta_node = kereta_node->next;
    }
    
    return count;
}

// Fungsi untuk menghasilkan ID kereta unik baru
void GenerateIDKereta(ListKereta L, char* id_baru) {
    // Format ID: K<nomor>
    int nomor = 1;
    char temp_id[10];
    
    do {
        sprintf(temp_id, "K%03d", nomor++);
    } while (SearchKeretaById(L, temp_id) != NULL && nomor < 1000);
    
    strcpy(id_baru, temp_id);
}

void TampilkanDaftarKereta() {
    Record records[MAX_FIELDS];
    int jumlahRecord = 0;
    DaftarKereta(records, &jumlahRecord);
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               DAFTAR KERETA                 |\n");
    printf("+----------------------------------------------+\n");
    if (jumlahRecord == 0) {
        printf("| Tidak ada data kereta.                      |\n");
    } else {
        printf("| %-10s | %-15s | %-10s | %-8s | %-6s |\n", "ID", "Nama", "Layanan", "Harga", "Gerbong");
        printf("+------------+-----------------+------------+----------+--------+\n");
        for (int i = 0; i < jumlahRecord; i++) {
            char* id = AmbilNilai(&records[i], "kodeKereta");
            char* nama = AmbilNilai(&records[i], "namaKereta");
            char* layanan = AmbilNilai(&records[i], "jenisLayanan");
            char* harga = AmbilNilai(&records[i], "harga");
            char* gerbong = AmbilNilai(&records[i], "jumlahGerbong");
            printf("| %-10s | %-15s | %-10s | %-8s | %-6s |\n", id ? id : "-", nama ? nama : "-", layanan ? layanan : "-", harga ? harga : "-", gerbong ? gerbong : "-");
        }
    }
    printf("+----------------------------------------------+\n");
}

void TambahKereta() {
    clearScreen();
    printf("+----------------------------------------------+\n");
    printf("|               TAMBAH KERETA                 |\n");
    printf("+----------------------------------------------+\n");
    char id[20], nama[50], layanan[20], harga[20], gerbong[10];
    printf("ID Kereta         : "); scanf("%s", id); while(getchar()!='\n');
    printf("Nama Kereta       : "); fgets(nama, sizeof(nama), stdin); nama[strcspn(nama, "\n")] = 0;
    printf("Jenis Layanan     : "); fgets(layanan, sizeof(layanan), stdin); layanan[strcspn(layanan, "\n")] = 0;
    printf("Harga             : "); fgets(harga, sizeof(harga), stdin); harga[strcspn(harga, "\n")] = 0;
    printf("Jumlah Gerbong    : "); fgets(gerbong, sizeof(gerbong), stdin); gerbong[strcspn(gerbong, "\n")] = 0;

    Record record; InisialisasiRecord(&record);
    TambahField(&record, "kodeKereta", id);
    TambahField(&record, "namaKereta", nama);
    TambahField(&record, "jenisLayanan", layanan);
    TambahField(&record, "harga", harga);
    TambahField(&record, "jumlahGerbong", gerbong);

    if (SimpanInformasiKereta(&record)) {
        printf("\nData kereta berhasil ditambahkan!\n");
    } else {
        printf("\nGagal menambah data kereta (ID sudah ada?)!\n");
    }
    printf("Tekan Enter untuk kembali..."); getchar();
}

void EditKereta() {
    TampilkanDaftarKereta();
    char id[20];
    printf("\nMasukkan ID kereta yang ingin diedit: ");
    scanf("%s", id); while(getchar()!='\n');
    Record record; InisialisasiRecord(&record);
    if (!BacaInformasiKereta(&record, id)) {
        printf("Data kereta tidak ditemukan!\nTekan Enter untuk kembali..."); getchar(); return;
    }
    printf("\nData lama:\n");
    CetakRecord(&record);
    char nama[50] = "", layanan[20] = "", harga[20] = "", gerbong[10] = "";
    printf("Nama Kereta baru (kosongkan jika tidak diubah): "); fgets(nama, sizeof(nama), stdin); nama[strcspn(nama, "\n")] = 0;
    printf("Jenis Layanan baru (kosongkan jika tidak diubah): "); fgets(layanan, sizeof(layanan), stdin); layanan[strcspn(layanan, "\n")] = 0;
    printf("Harga baru (kosongkan jika tidak diubah): "); fgets(harga, sizeof(harga), stdin); harga[strcspn(harga, "\n")] = 0;
    printf("Jumlah Gerbong baru (kosongkan jika tidak diubah): "); fgets(gerbong, sizeof(gerbong), stdin); gerbong[strcspn(gerbong, "\n")] = 0;
    if (strlen(nama) > 0) UbahNilai(&record, "namaKereta", nama);
    if (strlen(layanan) > 0) UbahNilai(&record, "jenisLayanan", layanan);
    if (strlen(harga) > 0) UbahNilai(&record, "harga", harga);
    if (strlen(gerbong) > 0) UbahNilai(&record, "jumlahGerbong", gerbong);
    if (UpdateInformasiKereta(&record)) {
        printf("\nData kereta berhasil diupdate!\n");
    } else {
        printf("\nGagal update data kereta!\n");
    }
    printf("Tekan Enter untuk kembali..."); getchar();
}

void HapusKereta() {
    TampilkanDaftarKereta();
    char id[20];
    printf("\nMasukkan ID kereta yang ingin dihapus: ");
    scanf("%s", id); while(getchar()!='\n');
    printf("Apakah Anda yakin ingin menghapus kereta %s? (y/n): ", id);
    char yakin = getchar(); while(getchar()!='\n' && getchar()!=EOF);
    if (yakin == 'y' || yakin == 'Y') {
        if (HapusInformasiKereta(id)) {
            printf("\nData kereta berhasil dihapus!\n");
        } else {
            printf("\nGagal menghapus data kereta!\n");
        }
    } else {
        printf("\nPenghapusan dibatalkan.\n");
    }
    printf("Tekan Enter untuk kembali..."); getchar();
} 