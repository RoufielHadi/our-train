/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi_antrian_offline.h"
#include "implementasi_riwayat.h"
#include <time.h>

// Counter untuk nomor antrian
static int counter_nomor_antrian = 0;

// *** OPERASI MANAJEMEN NOMOR ANTRIAN ***
void InisialisasiAntrianOffline(Queue *Q) {
    CreateQueue(Q);
    counter_nomor_antrian = 0; // Reset counter nomor antrian
}

int AmbilNomorAntrian(Queue *Q) {
    // Increment counter untuk nomor antrian baru
    counter_nomor_antrian++;
    
    // Tambahkan ke antrian
    Enqueue(Q, counter_nomor_antrian);
    
    printf("Nomor antrian %d telah diambil.\n", counter_nomor_antrian);
    return counter_nomor_antrian;
}

boolean PanggilAntrian(Queue *Q, int *nomorDipanggil) {
    // Dequeue nomor antrian terdepan
    if (Dequeue(Q, nomorDipanggil)) {
        printf("Memanggil nomor antrian: %d\n", *nomorDipanggil);
        return TRUE;
    } else {
        printf("Tidak ada antrian yang tersedia.\n");
        return FALSE;
    }
}

void LewatiAntrian(Queue *Q) {
    if (isEmptyQueue(*Q)) {
        printf("Tidak ada antrian yang bisa dilewati.\n");
        return;
    }
    
    // Ambil nomor antrian terdepan
    int nomorAntrian;
    if (Dequeue(Q, &nomorAntrian)) {
        // Masukkan kembali ke belakang antrian
        Enqueue(Q, nomorAntrian);
        printf("Nomor antrian %d dilewati dan dipindahkan ke belakang.\n", nomorAntrian);
    }
}

void BatalkanAntrian(Queue *Q, int nomorAntrian) {
    if (isEmptyQueue(*Q)) {
        printf("Tidak ada antrian yang bisa dibatalkan.\n");
        return;
    }
    
    // Buat queue sementara
    Queue tempQ;
    CreateQueue(&tempQ);
    
    boolean found = FALSE;
    int currentNomor;
    
    // Pindahkan semua elemen kecuali yang akan dibatalkan
    while (!isEmptyQueue(*Q)) {
        if (Dequeue(Q, &currentNomor)) {
            if (currentNomor != nomorAntrian) {
                Enqueue(&tempQ, currentNomor);
            } else {
                found = TRUE;
            }
        }
    }
    
    // Kembalikan elemen ke antrian asli
    while (!isEmptyQueue(tempQ)) {
        if (Dequeue(&tempQ, &currentNomor)) {
            Enqueue(Q, currentNomor);
        }
    }
    
    if (found) {
        printf("Nomor antrian %d berhasil dibatalkan.\n", nomorAntrian);
    } else {
        printf("Nomor antrian %d tidak ditemukan.\n", nomorAntrian);
    }
}

// *** OPERASI TAMPILAN ANTRIAN ***
void TampilkanStatusAntrian(Queue Q) {
    int jumlahAntrian = NbElmtQueue(Q);
    
    printf("\n=== STATUS ANTRIAN OFFLINE ===\n");
    printf("Jumlah antrian saat ini: %d\n", jumlahAntrian);
    
    if (!isEmptyQueue(Q)) {
        printf("Nomor antrian saat ini: %d\n", Front(Q));
        printf("Nomor antrian terakhir: %d\n", Rear(Q));
    } else {
        printf("Tidak ada antrian saat ini.\n");
    }
    
    // Tampilkan seluruh antrian
    TampilQueue(Q);
}

void TampilkanEstimasiWaktu(Queue Q, int waktuLayananPerOrang) {
    if (isEmptyQueue(Q)) {
        printf("Tidak ada antrian saat ini.\n");
        return;
    }
    
    Queue tempQ = Q; // Salin queue untuk iterasi
    addressAntrean P = tempQ.First;
    int posisi = 1;
    
    printf("\n=== ESTIMASI WAKTU TUNGGU ===\n");
    printf("Waktu layanan per orang: %d menit\n", waktuLayananPerOrang);
    printf("--------------------------------------\n");
    printf("| No. Antrian | Posisi | Estimasi Tunggu |\n");
    printf("--------------------------------------\n");
    
    while (P != NULL) {
        int estimasiWaktu = (posisi - 1) * waktuLayananPerOrang;
        printf("| %-11d | %-6d | %-15d |\n", P->nomor_antrean, posisi, estimasiWaktu);
        P = P->next;
        posisi++;
    }
    
    printf("--------------------------------------\n");
    printf("Total estimasi waktu untuk menyelesaikan seluruh antrian: %d menit\n",
           HitungEstimasiSelesai(Q, waktuLayananPerOrang));
}

// *** OPERASI PEMBELIAN TIKET ***
boolean ProsesLayananTiket(Queue *Q, StackRiwayat *riwayat, struct User user, 
                          struct InformasiKereta kereta, int nomor_gerbong, int nomor_kursi) {
    int nomorAntrian;
    
    // Panggil antrian berikutnya
    if (!PanggilAntrian(Q, &nomorAntrian)) {
        return FALSE; // Tidak ada antrian
    }
    
    // Catat riwayat pembelian tiket
    CatatRiwayatPembelian(riwayat, user, kereta, nomor_gerbong, nomor_kursi);
    
    printf("Pembelian tiket untuk nomor antrian %d berhasil diproses.\n", nomorAntrian);
    printf("Detail pembelian:\n");
    printf("Nama Penumpang: %s\n", user.nama);
    printf("Kereta: %s\n", kereta.nama_kereta);
    printf("Gerbong: %d, Kursi: %d\n", nomor_gerbong, nomor_kursi);
    
    return TRUE;
}

// *** OPERASI STATISTIK ***
int HitungRataRataWaktuTunggu(Queue Q, int waktuLayananPerOrang) {
    int jumlahAntrian = NbElmtQueue(Q);
    
    if (jumlahAntrian == 0) {
        return 0;
    }
    
    // Rumus rata-rata waktu tunggu: (n-1)/2 * waktuLayananPerOrang
    // di mana n adalah jumlah antrian
    return (jumlahAntrian - 1) * waktuLayananPerOrang / 2;
}

int HitungEstimasiSelesai(Queue Q, int waktuLayananPerOrang) {
    int jumlahAntrian = NbElmtQueue(Q);
    
    // Total waktu = jumlah antrian * waktu per orang
    return jumlahAntrian * waktuLayananPerOrang;
}

// *** OPERASI FILE ***
void SimpanAntrianKeFile(Queue Q, const char *namaFile) {
    FILE *file = fopen(namaFile, "w");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", namaFile);
        return;
    }
    
    // Simpan counter nomor antrian
    fprintf(file, "%d\n", counter_nomor_antrian);
    
    // Simpan data antrian
    Queue tempQ = Q;
    addressAntrean P = tempQ.First;
    
    while (P != NULL) {
        fprintf(file, "%d\n", P->nomor_antrean);
        P = P->next;
    }
    
    fclose(file);
    printf("Data antrian berhasil disimpan ke file %s\n", namaFile);
}

void MuatAntrianDariFile(Queue *Q, const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (!file) {
        printf("File %s tidak ditemukan.\n", namaFile);
        return;
    }
    
    // Hapus antrian yang ada
    InisialisasiAntrianOffline(Q);
    
    // Baca counter nomor antrian
    if (fscanf(file, "%d\n", &counter_nomor_antrian) != 1) {
        printf("Error: Format file tidak valid.\n");
        fclose(file);
        return;
    }
    
    // Baca data antrian
    int nomorAntrian;
    while (fscanf(file, "%d\n", &nomorAntrian) == 1) {
        Enqueue(Q, nomorAntrian);
    }
    
    fclose(file);
    printf("Data antrian berhasil dimuat dari file %s\n", namaFile);
} 