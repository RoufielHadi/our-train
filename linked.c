/*
Author: Roufiel Hadi  
NIM: 241524028  
Kelas: 1A  
Prodi: Sarjana Terapan Teknik Informatika  
Jurusan: Teknik Komputer dan Informatika  
Politeknik Negeri Bandung  
*/

#include "linked.h"

// ===================== KONSTRUKTOR ===================

void CreateListUser(ListUser *L) {
    L->First = NULL;
}

void CreateListPayment(ListPayment *L) {
    L->First = NULL;
}

void CreateListKereta(ListKereta *L) {
    L->First = NULL;
}

void CreateListStasiun(ListStasiun *L) {
    L->First = NULL;
}

void CreateJadwalKereta(JadwalKereta *J) {
    J->head = NULL;
}

void DeleteListUser(ListUser *L) {
    DataUser *temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

void DeleteListPayment(ListPayment *L) {
    PaymentUser *temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

void DeleteListKereta(ListKereta *L) {
    DataInformasiKereta *temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

void DeleteListStasiun(ListStasiun *L) {
    StasiunTransit *temp;
    while (L->First != NULL) {
        temp = L->First;
        L->First = L->First->next;
        free(temp);
    }
}

// ===================== VALIDATOR =====================

boolean isEmptyUser(ListUser L) {
    return (L.First == NULL);
}

boolean isEmptyPayment(ListPayment L) {
    return (L.First == NULL);
}

boolean isEmptyKereta(ListKereta L) {
    return (L.First == NULL);
}

boolean isEmptyStasiun(ListStasiun L) {
    return (L.First == NULL);
}

boolean isEmptyJadwal(JadwalKereta J) {
    return (J.head == NULL);
}

DataUser* CreateDataUser(User userData) {
    DataUser* newNode = (DataUser*)malloc(sizeof(DataUser));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk data user baru!\n");
        return NULL;
    }

    newNode->user_info = userData;
    newNode->next = NULL;

    return newNode;
}

PaymentUser* CreateDataPayment(Payment paymentData) {
    PaymentUser* newNode = (PaymentUser*)malloc(sizeof(PaymentUser));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk data payment baru!\n");
        return NULL;
    }

    newNode->payment_info = paymentData;
    newNode->next = NULL;

    return newNode;
}

DataInformasiKereta* CreateDataKereta(InformasiKereta keretaData) {
    DataInformasiKereta* newNode = (DataInformasiKereta*)malloc(sizeof(DataInformasiKereta));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk data kereta baru!\n");
        return NULL;
    }

    newNode->kereta_info = keretaData;
    newNode->next = NULL;

    return newNode;
}

StasiunTransit* CreateStasiunTransit(char* nama_stasiun, Waktu waktu_transit) {
    StasiunTransit* newNode = (StasiunTransit*)malloc(sizeof(StasiunTransit));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk stasiun transit baru!\n");
        return NULL;
    }

    strcpy(newNode->nama_stasiun, nama_stasiun);
    newNode->waktu_transit = waktu_transit;
    newNode->next = NULL;

    return newNode;
}

// Insert pertama untuk user
void InsertFirstUser(ListUser *L, DataUser *newNode) {
    if (L == NULL) {
        printf("Error: ListUser belum diinisialisasi!\n");
        return;
    }

    if (newNode == NULL) {
        printf("Error: Node yang akan ditambahkan NULL!\n");
        return;
    }

    newNode->next = L->First;
    L->First = newNode;
}

// Insert pertama untuk payment
void InsertFirstPayment(ListPayment *L, PaymentUser *P) {
    P->next = L->First;
    L->First = P;
}

// Insert pertama untuk kereta
void InsertFirstKereta(ListKereta *L, DataInformasiKereta *P) {
    P->next = L->First;
    L->First = P;
}

// Insert pertama untuk stasiun
void InsertFirstStasiun(ListStasiun *L, StasiunTransit *P) {
    P->next = L->First;
    L->First = P;
}

// Insert pertama untuk jadwal kereta
void InsertFirstJadwal(JadwalKereta *J, StasiunTransit *P) {
    P->next = J->head;
    J->head = P;
}

// Insert terakhir untuk user
void InsertLastUser(ListUser *L, DataUser *newNode) {
    if (L == NULL) printf("Debug: ListUser adalah NULL sebelum pemanggilan InsertLastUser!\n");
    if (newNode == NULL) printf("Debug: newNode adalah NULL sebelum pemanggilan InsertLastUser!\n");
    
    if (L == NULL || newNode == NULL) {
        printf("Error: ListUser atau newNode NULL dalam InsertLastUser!\n");
        return;
    }

    if (L->First == NULL) {
        L->First = newNode;
        return;
    }

    DataUser *temp = L->First;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Insert terakhir untuk payment
void InsertLastPayment(ListPayment *L, PaymentUser *P) {
    if (L->First == NULL) {
        L->First = P;
    } else {
        PaymentUser *temp = L->First;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = P;
    }
}

// Insert terakhir untuk kereta
void InsertLastKereta(ListKereta *L, DataInformasiKereta *P) {
    if (L->First == NULL) {
        L->First = P;
    } else {
        DataInformasiKereta *temp = L->First;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = P;
    }
}

// Insert terakhir untuk stasiun
void InsertLastStasiun(ListStasiun *L, StasiunTransit *P) {
    if (L->First == NULL) {
        L->First = P;
    } else {
        StasiunTransit *temp = L->First;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = P;
    }
}

// Insert terakhir untuk jadwal kereta
void InsertLastJadwal(JadwalKereta *J, StasiunTransit *P) {
    if (J->head == NULL) {
        J->head = P;
    } else {
        StasiunTransit *temp = J->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = P;
    }
}

// Menyisipkan setelah elemen tertentu
void InsertAfterUser(DataUser *pBef, DataUser *PNew) {
    if (pBef == NULL) {
        printf("Error: Node sebelum tidak boleh NULL!\n");
        return;
    }

    if (PNew == NULL) {
        printf("Error: Node baru tidak boleh NULL!\n");
        return;
    }

    PNew->next = pBef->next;
    pBef->next = PNew;
}

void InsertAfterPayment(PaymentUser *pBef, PaymentUser *PNew) {
    if (pBef != NULL) {
        PNew->next = pBef->next;
        pBef->next = PNew;
    }
}

void InsertAfterKereta(DataInformasiKereta *pBef, DataInformasiKereta *PNew) {
    if (pBef != NULL) {
        PNew->next = pBef->next;
        pBef->next = PNew;
    }
}

void InsertAfterStasiun(StasiunTransit *pBef, StasiunTransit *PNew) {
    if (pBef != NULL) {
        PNew->next = pBef->next;
        pBef->next = PNew;
    }
}

// Hapus elemen pertama
void DeleteFirstUser(ListUser *L) {
    if (L->First != NULL) {
        DataUser *temp = L->First;
        L->First = temp->next;
        free(temp);
    }
}

void DeleteFirstPayment(ListPayment *L) {
    if (L->First != NULL) {
        PaymentUser *temp = L->First;
        L->First = temp->next;
        free(temp);
    }
}

void DeleteFirstKereta(ListKereta *L) {
    if (L->First != NULL) {
        DataInformasiKereta *temp = L->First;
        L->First = temp->next;
        free(temp);
    }
}

void DeleteFirstStasiun(ListStasiun *L) {
    if (L->First != NULL) {
        StasiunTransit *temp = L->First;
        L->First = temp->next;
        free(temp);
    }
}

void DeleteFirstJadwal(JadwalKereta *J) {
    if (J->head != NULL) {
        StasiunTransit *temp = J->head;
        J->head = temp->next;
        free(temp);
    }
}

// Hapus elemen terakhir
void DeleteLastUser(ListUser *L) {
    if (L->First != NULL) {
        DataUser *temp = L->First, *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            L->First = NULL;
        } else {
            prev->next = NULL;
        }
        free(temp);
    }
}

void DeleteLastPayment(ListPayment *L) {
    if (L->First != NULL) {
        PaymentUser *temp = L->First, *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            L->First = NULL;
        } else {
            prev->next = NULL;
        }
        free(temp);
    }
}

void DeleteLastKereta(ListKereta *L) {
    if (L->First != NULL) {
        DataInformasiKereta *temp = L->First, *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            L->First = NULL;
        } else {
            prev->next = NULL;
        }
        free(temp);
    }
}

void DeleteLastStasiun(ListStasiun *L) {
    if (L->First != NULL) {
        StasiunTransit *temp = L->First, *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            L->First = NULL;
        } else {
            prev->next = NULL;
        }
        free(temp);
    }
}

void DeleteLastJadwal(JadwalKereta *J) {
    if (J->head != NULL) {
        StasiunTransit *temp = J->head, *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            J->head = NULL;
        } else {
            prev->next = NULL;
        }
        free(temp);
    }
}

// Hapus elemen setelah node tertentu
void DeleteAfterUser(DataUser *pBef) {
    if (pBef != NULL && pBef->next != NULL) {
        DataUser *temp = pBef->next;
        pBef->next = temp->next;
        free(temp);
    }
}

void DeleteAfterPayment(PaymentUser *pBef) {
    if (pBef != NULL && pBef->next != NULL) {
        PaymentUser *temp = pBef->next;
        pBef->next = temp->next;
        free(temp);
    }
}

void DeleteAfterKereta(DataInformasiKereta *pBef) {
    if (pBef != NULL && pBef->next != NULL) {
        DataInformasiKereta *temp = pBef->next;
        pBef->next = temp->next;
        free(temp);
    }
}

void DeleteAfterStasiun(StasiunTransit *pBef) {
    if (pBef != NULL && pBef->next != NULL) {
        StasiunTransit *temp = pBef->next;
        pBef->next = temp->next;
        free(temp);
    }
}

// Dealokasi memori
void DeAlokasiUser(DataUser **P) {
    free(*P);
    *P = NULL;
}

void DeAlokasiPayment(PaymentUser **P) {
    free(*P);
    *P = NULL;
}

void DeAlokasiKereta(DataInformasiKereta **P) {
    free(*P);
    *P = NULL;
}

void DeAlokasiStasiun(StasiunTransit **P) {
    free(*P);
    *P = NULL;
}

// Menghitung jumlah elemen dalam list
int NbElmtUser(ListUser L) {
    int count = 0;
    DataUser *P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

int NbElmtPayment(ListPayment L) {
    int count = 0;
    PaymentUser *P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

int NbElmtKereta(ListKereta L) {
    int count = 0;
    DataInformasiKereta *P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

int NbElmtStasiun(ListStasiun L) {
    int count = 0;
    StasiunTransit *P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

int NbElmtJadwal(JadwalKereta J) {
    int count = 0;
    StasiunTransit *P = J.head;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

// Mencari elemen berdasarkan email user
DataUser* SearchUserByEmail(ListUser L, char *email) {
    DataUser *P = L.First;
    while (P != NULL) {
        if (strcmp(P->user_info.email, email) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Mencari elemen berdasarkan email payment
PaymentUser* SearchPaymentByEmail(ListPayment L, char *email) {
    PaymentUser *P = L.First;
    while (P != NULL) {
        if (strcmp(P->payment_info.email, email) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Mencari elemen berdasarkan ID kereta
DataInformasiKereta* SearchKeretaById(ListKereta L, char *id_Kereta) {
    DataInformasiKereta *P = L.First;
    while (P != NULL) {
        if (strcmp(P->kereta_info.id_Kereta, id_Kereta) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Mencari elemen berdasarkan nama stasiun
StasiunTransit* SearchStasiunByNama(ListStasiun L, char *nama_stasiun) {
    StasiunTransit *P = L.First;
    while (P != NULL) {
        if (strcmp(P->nama_stasiun, nama_stasiun) == 0) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Menampilkan semua elemen dalam list
void PrintUser(ListUser L) {
    DataUser *P = L.First;
    while (P != NULL) {
        printf("Nama: %s\n", P->user_info.nama);
        printf("Email: %s\n", P->user_info.email);
        printf("Alamat: %s\n", P->user_info.alamat);
        printf("No.Telp: %s\n", P->user_info.nomor_telepon);
        printf("Status Admin: %s\n", P->user_info.is_admin ? "Ya" : "Tidak");
        printf("-------------------------\n");
        P = P->next;
    }
}

void PrintPayment(ListPayment L) {
    PaymentUser *P = L.First;
    while (P != NULL) {
        printf("Email: %s\n", P->payment_info.email);
        printf("No.Rekening: %s\n", P->payment_info.no_rekening);
        printf("Saldo: Rp%d\n", P->payment_info.saldo);
        printf("-------------------------\n");
        P = P->next;
    }
}

void PrintKereta(ListKereta L) {
    DataInformasiKereta *P = L.First;
    while (P != NULL) {
        printf("ID: %s\n", P->kereta_info.id_Kereta);
        printf("Nama: %s\n", P->kereta_info.nama_kereta);
        printf("Jenis Layanan: %s\n", P->kereta_info.jenis_layanan);
        printf("Harga: Rp%.2f\n", P->kereta_info.harga_tiket);
        printf("Jumlah Gerbong: %s\n", P->kereta_info.jumlah_gerbong);
        printf("-------------------------\n");
        P = P->next;
    }
}

void PrintStasiun(ListStasiun L) {
    StasiunTransit *P = L.First;
    while (P != NULL) {
        printf("Stasiun: %s\n", P->nama_stasiun);
        PrintWaktu(P->waktu_transit);
        printf("\n-------------------------\n");
        P = P->next;
    }
}

void PrintJadwal(JadwalKereta J) {
    StasiunTransit *P = J.head;
    int i = 1;
    while (P != NULL) {
        printf("Stasiun %d: %s\n", i++, P->nama_stasiun);
        printf("Waktu: ");
        PrintWaktu(P->waktu_transit);
        printf("\n-------------------------\n");
        P = P->next;
    }
}

// Membalik urutan elemen dalam list
ListUser BalikListUser(ListUser L) {
    ListUser newL;
    newL.First = NULL;
    DataUser *P = L.First;
    while (P != NULL) {
        DataUser *temp = P;
        P = P->next;
        temp->next = newL.First;
        newL.First = temp;
    }
    return newL;
}

ListPayment BalikListPayment(ListPayment L) {
    ListPayment newL;
    newL.First = NULL;
    PaymentUser *P = L.First;
    while (P != NULL) {
        PaymentUser *temp = P;
        P = P->next;
        temp->next = newL.First;
        newL.First = temp;
    }
    return newL;
}

ListKereta BalikListKereta(ListKereta L) {
    ListKereta newL;
    newL.First = NULL;
    DataInformasiKereta *P = L.First;
    while (P != NULL) {
        DataInformasiKereta *temp = P;
        P = P->next;
        temp->next = newL.First;
        newL.First = temp;
    }
    return newL;
}

ListStasiun BalikListStasiun(ListStasiun L) {
    ListStasiun newL;
    newL.First = NULL;
    StasiunTransit *P = L.First;
    while (P != NULL) {
        StasiunTransit *temp = P;
        P = P->next;
        temp->next = newL.First;
        newL.First = temp;
    }
    return newL;
}

JadwalKereta BalikJadwalKereta(JadwalKereta J) {
    JadwalKereta newJ;
    newJ.head = NULL;
    StasiunTransit *P = J.head;
    while (P != NULL) {
        StasiunTransit *temp = P;
        P = P->next;
        temp->next = newJ.head;
        newJ.head = temp;
    }
    return newJ;
}
