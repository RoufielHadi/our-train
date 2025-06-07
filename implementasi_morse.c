/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include "implementasi_morse.h"
#include <ctype.h>

// *** IMPLEMENTASI BARU SESUAI DENGAN PERMINTAAN USER ***

// Fungsi untuk membuat node Morse baru
HashPassword* BuatNodeMorse(char karakter) {
    HashPassword* newNode = (HashPassword*)malloc(sizeof(HashPassword));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk node Morse baru!\n");
        return NULL;
    }
    
    newNode->info = karakter;
    newNode->kiri = NULL;
    newNode->kanan = NULL;
    
    return newNode;
}

// Fungsi untuk membangun tree Morse dengan pendekatan hardcoded
void BuildMorseTree(HashPassword **root) {
    // Alokasi memori untuk root
    *root = BuatNodeMorse('\0');  // Root tidak memiliki karakter
    
    if (*root == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk tree Morse!\n");
        return;
    }
    
    // =========== LEVEL 1 ===========
    // Level 1: kiri = ".", kanan = "-"
    (*root)->kiri = BuatNodeMorse('E');
    (*root)->kanan = BuatNodeMorse('T');
    
    // =========== LEVEL 2 ===========
    // "E" cabang (kiri dari root)
    (*root)->kiri->kiri = BuatNodeMorse('I');
    (*root)->kiri->kanan = BuatNodeMorse('A');
    
    // "T" cabang (kanan dari root)
    (*root)->kanan->kiri = BuatNodeMorse('N');
    (*root)->kanan->kanan = BuatNodeMorse('M');
    
    // =========== LEVEL 3 ===========
    // "I" cabang (kiri-kiri dari root)
    (*root)->kiri->kiri->kiri = BuatNodeMorse('S');
    (*root)->kiri->kiri->kanan = BuatNodeMorse('U');
    
    // "A" cabang (kiri-kanan dari root)
    (*root)->kiri->kanan->kiri = BuatNodeMorse('R');
    (*root)->kiri->kanan->kanan = BuatNodeMorse('W');
    
    // "N" cabang (kanan-kiri dari root)
    (*root)->kanan->kiri->kiri = BuatNodeMorse('D');
    (*root)->kanan->kiri->kanan = BuatNodeMorse('K');
    
    // "M" cabang (kanan-kanan dari root)
    (*root)->kanan->kanan->kiri = BuatNodeMorse('G');
    (*root)->kanan->kanan->kanan = BuatNodeMorse('O');
    
    // =========== LEVEL 4 ===========
    // "S" cabang
    (*root)->kiri->kiri->kiri->kiri = BuatNodeMorse('H');
    (*root)->kiri->kiri->kiri->kanan = BuatNodeMorse('V');
    
    // "U" cabang
    (*root)->kiri->kiri->kanan->kiri = BuatNodeMorse('F');
    (*root)->kiri->kiri->kanan->kanan = BuatNodeMorse('a'); // Huruf kecil a
    
    // "R" cabang
    (*root)->kiri->kanan->kiri->kiri = BuatNodeMorse('L');
    (*root)->kiri->kanan->kiri->kanan = BuatNodeMorse('b'); // Huruf kecil b
    
    // "W" cabang
    (*root)->kiri->kanan->kanan->kiri = BuatNodeMorse('P');
    (*root)->kiri->kanan->kanan->kanan = BuatNodeMorse('J');
    
    // "D" cabang
    (*root)->kanan->kiri->kiri->kiri = BuatNodeMorse('B');
    (*root)->kanan->kiri->kiri->kanan = BuatNodeMorse('X');
    
    // "K" cabang
    (*root)->kanan->kiri->kanan->kiri = BuatNodeMorse('C');
    (*root)->kanan->kiri->kanan->kanan = BuatNodeMorse('Y');
    
    // "G" cabang
    (*root)->kanan->kanan->kiri->kiri = BuatNodeMorse('Z');
    (*root)->kanan->kanan->kiri->kanan = BuatNodeMorse('Q');
    
    // "O" cabang
    (*root)->kanan->kanan->kanan->kiri = BuatNodeMorse('c'); // Huruf kecil c
    (*root)->kanan->kanan->kanan->kanan = BuatNodeMorse('d'); // Huruf kecil d
    
    // =========== LEVEL 5 ===========
    // Angka dan huruf kecil
    
    // "H" cabang (huruf kecil e-f dan angka 5-4)
    (*root)->kiri->kiri->kiri->kiri->kiri = BuatNodeMorse('5');
    (*root)->kiri->kiri->kiri->kiri->kanan = BuatNodeMorse('4');
    
    // "V" cabang (huruf kecil g-j)
    (*root)->kiri->kiri->kiri->kanan->kiri = BuatNodeMorse('e'); // Huruf kecil e
    (*root)->kiri->kiri->kiri->kanan->kanan = BuatNodeMorse('3');
    
    // "F" cabang (huruf kecil k-n)
    (*root)->kiri->kiri->kanan->kiri->kiri = BuatNodeMorse('f'); // Huruf kecil f
    (*root)->kiri->kiri->kanan->kiri->kanan = BuatNodeMorse('g'); // Huruf kecil g
    
    // "a" cabang
    (*root)->kiri->kiri->kanan->kanan->kiri = BuatNodeMorse('h'); // Huruf kecil h
    (*root)->kiri->kiri->kanan->kanan->kanan = BuatNodeMorse('i'); // Huruf kecil i
    
    // "L" cabang (huruf kecil o-r)
    (*root)->kiri->kanan->kiri->kiri->kiri = BuatNodeMorse('j'); // Huruf kecil j
    (*root)->kiri->kanan->kiri->kiri->kanan = BuatNodeMorse('k'); // Huruf kecil k
    
    // "b" cabang
    (*root)->kiri->kanan->kiri->kanan->kiri = BuatNodeMorse('l'); // Huruf kecil l
    (*root)->kiri->kanan->kiri->kanan->kanan = BuatNodeMorse('m'); // Huruf kecil m
    
    // "P" cabang (huruf kecil s-v)
    (*root)->kiri->kanan->kanan->kiri->kiri = BuatNodeMorse('n'); // Huruf kecil n
    (*root)->kiri->kanan->kanan->kiri->kanan = BuatNodeMorse('o'); // Huruf kecil o
    
    // "J" cabang (untuk angka 1)
    (*root)->kiri->kanan->kanan->kanan->kiri = BuatNodeMorse('1');
    (*root)->kiri->kanan->kanan->kanan->kanan = BuatNodeMorse('p'); // Huruf kecil p
    
    // "B" cabang (untuk angka 6)
    (*root)->kanan->kiri->kiri->kiri->kiri = BuatNodeMorse('6');
    (*root)->kanan->kiri->kiri->kiri->kanan = BuatNodeMorse('q'); // Huruf kecil q
    
    // "X" cabang
    (*root)->kanan->kiri->kiri->kanan->kiri = BuatNodeMorse('r'); // Huruf kecil r
    (*root)->kanan->kiri->kiri->kanan->kanan = BuatNodeMorse('s'); // Huruf kecil s
    
    // "C" cabang
    (*root)->kanan->kiri->kanan->kiri->kiri = BuatNodeMorse('t'); // Huruf kecil t
    (*root)->kanan->kiri->kanan->kiri->kanan = BuatNodeMorse('u'); // Huruf kecil u
    
    // "Y" cabang
    (*root)->kanan->kiri->kanan->kanan->kiri = BuatNodeMorse('v'); // Huruf kecil v
    (*root)->kanan->kiri->kanan->kanan->kanan = BuatNodeMorse('w'); // Huruf kecil w
    
    // "Z" cabang (untuk angka 7)
    (*root)->kanan->kanan->kiri->kiri->kiri = BuatNodeMorse('7');
    (*root)->kanan->kanan->kiri->kiri->kanan = BuatNodeMorse('x'); // Huruf kecil x
    
    // "Q" cabang
    (*root)->kanan->kanan->kiri->kanan->kiri = BuatNodeMorse('y'); // Huruf kecil y
    (*root)->kanan->kanan->kiri->kanan->kanan = BuatNodeMorse('z'); // Huruf kecil z
    
    // "c" cabang
    (*root)->kanan->kanan->kanan->kiri->kiri = BuatNodeMorse('8');
    (*root)->kanan->kanan->kanan->kiri->kanan = BuatNodeMorse('9');
    
    // "d" cabang
    (*root)->kanan->kanan->kanan->kanan->kiri = BuatNodeMorse('0');
    (*root)->kanan->kanan->kanan->kanan->kanan = BuatNodeMorse(' '); // Spasi
    
    // =========== LEVEL 6 & SELANJUTNYA ===========
    // Simbol-simbol keyboard
    
    // Bagian simbol
    (*root)->kiri->kiri->kiri->kiri->kiri->kiri = BuatNodeMorse('.');
    (*root)->kiri->kiri->kiri->kiri->kiri->kanan = BuatNodeMorse(',');
    (*root)->kiri->kiri->kiri->kiri->kanan->kiri = BuatNodeMorse('?');
    (*root)->kiri->kiri->kiri->kiri->kanan->kanan = BuatNodeMorse('!');
    
    // Tambahan simbol
    (*root)->kiri->kiri->kiri->kanan->kiri->kiri = BuatNodeMorse('@');
    (*root)->kiri->kiri->kiri->kanan->kiri->kanan = BuatNodeMorse('#');
    (*root)->kiri->kiri->kanan->kiri->kiri->kiri = BuatNodeMorse('$');
    (*root)->kiri->kiri->kanan->kiri->kiri->kanan = BuatNodeMorse('%');
    (*root)->kiri->kiri->kanan->kanan->kiri->kiri = BuatNodeMorse('^');
    (*root)->kiri->kiri->kanan->kanan->kiri->kanan = BuatNodeMorse('&');
    
    // Lebih banyak simbol
    (*root)->kiri->kanan->kiri->kiri->kiri->kiri = BuatNodeMorse('*');
    (*root)->kiri->kanan->kiri->kiri->kiri->kanan = BuatNodeMorse('(');
    (*root)->kiri->kanan->kiri->kiri->kanan->kiri = BuatNodeMorse(')');
    (*root)->kiri->kanan->kiri->kiri->kanan->kanan = BuatNodeMorse('-');
    (*root)->kiri->kanan->kiri->kanan->kiri->kiri = BuatNodeMorse('_');
    (*root)->kiri->kanan->kiri->kanan->kiri->kanan = BuatNodeMorse('=');
    (*root)->kiri->kanan->kiri->kanan->kanan->kiri = BuatNodeMorse('+');
    (*root)->kiri->kanan->kiri->kanan->kanan->kanan = BuatNodeMorse('[');
    
    // Tambahan simbol lagi
    (*root)->kiri->kanan->kanan->kiri->kiri->kiri = BuatNodeMorse(']');
    (*root)->kiri->kanan->kanan->kiri->kiri->kanan = BuatNodeMorse('{');
    (*root)->kiri->kanan->kanan->kiri->kanan->kiri = BuatNodeMorse('}');
    (*root)->kiri->kanan->kanan->kiri->kanan->kanan = BuatNodeMorse('\\');
    (*root)->kiri->kanan->kanan->kanan->kiri->kiri = BuatNodeMorse('|');
    (*root)->kiri->kanan->kanan->kanan->kiri->kanan = BuatNodeMorse(';');
    (*root)->kiri->kanan->kanan->kanan->kanan->kiri = BuatNodeMorse(':');
    (*root)->kiri->kanan->kanan->kanan->kanan->kanan = BuatNodeMorse('\'');
    
    // Dan lebih banyak simbol
    (*root)->kanan->kiri->kiri->kiri->kiri->kiri = BuatNodeMorse('"');
    (*root)->kanan->kiri->kiri->kiri->kiri->kanan = BuatNodeMorse('<');
    (*root)->kanan->kiri->kiri->kiri->kanan->kiri = BuatNodeMorse('>');
    (*root)->kanan->kiri->kiri->kiri->kanan->kanan = BuatNodeMorse(',');
    (*root)->kanan->kiri->kiri->kanan->kiri->kiri = BuatNodeMorse('/');
    (*root)->kanan->kiri->kiri->kanan->kiri->kanan = BuatNodeMorse('?');
    (*root)->kanan->kiri->kiri->kanan->kanan->kiri = BuatNodeMorse('~');
    (*root)->kanan->kiri->kiri->kanan->kanan->kanan = BuatNodeMorse('`');
}

// Fungsi rekursif untuk mencari path ke karakter dalam tree
boolean FindCharPath(HashPassword *root, char karakter, char *path, int *index, int depth) {
    if (root == NULL) {
        return FALSE;
    }
    
    // Jika ini node target
    if (root->info == karakter) {
        path[*index] = '\0';
        return TRUE;
    }
    
    // Cari di subpohon kiri (titik)
    if (root->kiri != NULL) {
        path[*index] = '.';
        (*index)++;
        if (FindCharPath(root->kiri, karakter, path, index, depth + 1)) {
            return TRUE;
        }
        (*index)--;
    }
    
    // Cari di subpohon kanan (strip)
    if (root->kanan != NULL) {
        path[*index] = '-';
        (*index)++;
        if (FindCharPath(root->kanan, karakter, path, index, depth + 1)) {
            return TRUE;
        }
        (*index)--;
    }
    
    return FALSE;
}

// Fungsi untuk mendapatkan Morse code berdasarkan path di tree
char* GetMorseCodeFromTree(HashPassword *root, char karakter) {
    // Alokasi memori untuk hasil (maksimal 10 karakter)
    char *result = (char*)malloc(10);
    result[0] = '\0';
    
    // Buffer untuk menyimpan path sementara (reversed)
    char tempPath[10] = {'\0'};
    int pathIndex = 0;
    
    // Cari path ke karakter dalam tree
    FindCharPath(root, karakter, tempPath, &pathIndex, 0);
    
    // Balikkan path (karena kita mencatat dari leaf ke root)
    int len = strlen(tempPath);
    for (int i = 0; i < len; i++) {
        result[i] = tempPath[len - i - 1];
    }
    result[len] = '\0';
    
    return result;
}

// *** OPERASI DASAR MORSE CODE (DISESUAIKAN) ***
void InisialisasiMorseCode(HashPassword **morseTree) {
    // Gunakan fungsi BuildMorseTree untuk menginisialisasi tree
    BuildMorseTree(morseTree);
}

// Konversi menggunakan tree
char* KonversiKarakterKeMorse(HashPassword *morseTree, char karakter) {
    // Gunakan tree untuk mendapatkan kode Morse
    return GetMorseCodeFromTree(morseTree, karakter);
}

char KonversiMorseKeKarakter(HashPassword *morseTree, const char *morseCode) {
    if (morseTree == NULL || morseCode == NULL) {
        return '\0';
    }
    
    HashPassword *current = morseTree;
    int len = strlen(morseCode);
    
    // Traversal tree berdasarkan kode Morse
    for (int i = 0; i < len; i++) {
        if (morseCode[i] == '.') {
            if (current->kiri == NULL) {
                return '\0';  // Kode tidak valid
            }
            current = current->kiri;
        } else if (morseCode[i] == '-') {
            if (current->kanan == NULL) {
                return '\0';  // Kode tidak valid
            }
            current = current->kanan;
        } else {
            return '\0';  // Karakter kode tidak valid
        }
    }
    
    return current->info;
}

char* KonversiStringKeMorse(HashPassword *morseTree, const char *teks) {
    if (morseTree == NULL || teks == NULL) {
        return NULL;
    }
    
    // Alokasi memori untuk hasil (perkiraan ukuran maksimal)
    int maxLen = strlen(teks) * 7; // Perkiraan 7 karakter per huruf (termasuk spasi)
    char *result = (char*)malloc(maxLen + 1);
    result[0] = '\0';
    
    for (int i = 0; teks[i] != '\0'; i++) {
        char *morseCode = KonversiKarakterKeMorse(morseTree, teks[i]);
        
        if (strlen(morseCode) > 0) {
            if (i > 0) {
                strcat(result, " "); // Tambahkan spasi antar karakter
            }
            strcat(result, morseCode);
        }
        
        free(morseCode);
    }
    
    return result;
}

// Fungsi untuk menghitung jumlah karakter dalam tree
int HitungKarakterDalamTree(HashPassword *root) {
    if (root == NULL) {
        return 0;
    }
    
    // Jika node memiliki karakter (bukan placeholder)
    int count = (root->info != '\0') ? 1 : 0;
    
    // Hitung rekursif untuk anak-anaknya
    count += HitungKarakterDalamTree(root->kiri);
    count += HitungKarakterDalamTree(root->kanan);
    
    return count;
}

// Fungsi untuk visualisasi tree
void VisualisasiTreeMorse(HashPassword *root, int level, char *path) {
    if (root == NULL) {
        return;
    }
    
    // Tampilkan karakter jika ada (bukan node kosong)
    if (root->info != '\0') {
        // Tampilkan indentasi sesuai level
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        
        // Tentukan kategori karakter
        const char* kategori = "";
        if (root->info == ' ') {
            kategori = "[SPASI]";
        } else if (root->info >= 'A' && root->info <= 'Z') {
            kategori = "[KAPITAL]";
        } else if (root->info >= 'a' && root->info <= 'z') {
            kategori = "[KECIL]";
        } else if (root->info >= '0' && root->info <= '9') {
            kategori = "[ANGKA]";
        } else if (root->info < 32 || root->info > 126) {
            kategori = "[ASCII]";
        } else {
            kategori = "[SIMBOL]";
        }
        
        // Tampilkan karakter dan jalur Morse-nya
        if (root->info == ' ') {
            printf("[SPASI] \t= %s\n", path);
        } else if (root->info < 32 || root->info > 126) {
            printf("[ASCII %d] \t= %s\n", root->info, path);
        } else {
            printf("'%c' %s\t= %s\n", root->info, kategori, path);
        }
    }
    
    // Siapkan jalur untuk traversal berikutnya
    char leftPath[100], rightPath[100];
    strcpy(leftPath, path);
    strcpy(rightPath, path);
    strcat(leftPath, ".");   // Kiri = tambahkan titik
    strcat(rightPath, "-");  // Kanan = tambahkan strip
    
    // Traversal ke kiri (titik)
    VisualisasiTreeMorse(root->kiri, level + 1, leftPath);
    
    // Traversal ke kanan (strip)
    VisualisasiTreeMorse(root->kanan, level + 1, rightPath);
}

char* KonversiMorseKeString(HashPassword *morseTree, const char *morseCode) {
    if (morseTree == NULL || morseCode == NULL) {
        return NULL;
    }
    
    // Alokasi memori untuk hasil
    int maxLen = strlen(morseCode); // Maksimal satu karakter per kode
    char *result = (char*)malloc(maxLen + 1);
    result[0] = '\0';
    
    // Pecah kode Morse berdasarkan spasi
    char tempMorseCode[100]; // Buffer sementara
    int resultIndex = 0;
    int tempIndex = 0;
    
    for (int i = 0; morseCode[i] != '\0'; i++) {
        if (morseCode[i] == ' ') {
            // Spasi menandakan akhir kode untuk satu karakter
            tempMorseCode[tempIndex] = '\0';
            
            if (tempIndex > 0) {
                // Konversi kode ke karakter
                char c = KonversiMorseKeKarakter(morseTree, tempMorseCode);
                if (c != '\0') {
                    result[resultIndex++] = c;
                }
                tempIndex = 0;
            }
        } else if (morseCode[i] == '/') {
            // Slash menandakan spasi
            result[resultIndex++] = ' ';
            tempIndex = 0;
        } else {
            // Tambahkan ke buffer sementara
            tempMorseCode[tempIndex++] = morseCode[i];
        }
    }
    
    // Proses kode terakhir jika ada
    if (tempIndex > 0) {
        tempMorseCode[tempIndex] = '\0';
        char c = KonversiMorseKeKarakter(morseTree, tempMorseCode);
        if (c != '\0') {
            result[resultIndex++] = c;
        }
    }
    
    result[resultIndex] = '\0';
    return result;
}

// *** OPERASI ENCODING/DECODING KHUSUS ***
char* EncodeMorse(const char *morseCode) {
    if (morseCode == NULL) {
        return NULL;
    }
    
    int len = strlen(morseCode);
    char *result = (char*)malloc(len + 1);
    
    for (int i = 0; i < len; i++) {
        if (morseCode[i] == '.') {
            result[i] = 'X';  // Titik menjadi X
        } else if (morseCode[i] == '-') {
            result[i] = 'O';  // Strip menjadi O
        } else if (morseCode[i] == ' ') {
            result[i] = 'S';  // Spasi menjadi S
        } else if (morseCode[i] == '/') {
            result[i] = 'S';  // Slash (untuk spasi) juga menjadi S
        } else {
            result[i] = morseCode[i];  // Karakter lain tetap sama
        }
    }
    
    result[len] = '\0';
    return result;
}

char* DecodeMorse(const char *encodedMorse) {
    if (encodedMorse == NULL) {
        return NULL;
    }
    
    int len = strlen(encodedMorse);
    char *result = (char*)malloc(len + 1);
    
    for (int i = 0; i < len; i++) {
        if (encodedMorse[i] == 'X') {
            result[i] = '.';  // X menjadi titik
        } else if (encodedMorse[i] == 'O') {
            result[i] = '-';  // O menjadi strip
        } else if (encodedMorse[i] == 'S') {
            result[i] = ' ';  // S menjadi spasi
        } else {
            result[i] = encodedMorse[i];  // Karakter lain tetap sama
        }
    }
    
    result[len] = '\0';
    return result;
}

// Fungsi untuk menghitung jumlah karakter per kategori
void HitungKarakterPerKategori(HashPassword *root, int *kapital, int *kecil, int *angka, int *simbol, int *lainnya) {
    if (root == NULL) {
        return;
    }
    
    // Hitung berdasarkan kategori
    if (root->info != '\0') {
        if (root->info >= 'A' && root->info <= 'Z') {
            (*kapital)++;
        } else if (root->info >= 'a' && root->info <= 'z') {
            (*kecil)++;
        } else if (root->info >= '0' && root->info <= '9') {
            (*angka)++;
        } else if (root->info == ' ' || (root->info >= 33 && root->info <= 126)) {
            (*simbol)++;
        } else {
            (*lainnya)++;
        }
    }
    
    // Rekursif untuk anak-anaknya
    HitungKarakterPerKategori(root->kiri, kapital, kecil, angka, simbol, lainnya);
    HitungKarakterPerKategori(root->kanan, kapital, kecil, angka, simbol, lainnya);
}

// *** OPERASI PEMBANTU ***
void TampilkanTabelMorse(HashPassword *root) {
    printf("======== KODE MORSE DARI BINARY TREE ========\n");
    
    // Tampilkan statistik jumlah karakter
    int jumlahKarakter = HitungKarakterDalamTree(root);
    printf("Total karakter dalam tree: %d\n", jumlahKarakter);
    
    // Hitung per kategori
    int kapital = 0, kecil = 0, angka = 0, simbol = 0, lainnya = 0;
    HitungKarakterPerKategori(root, &kapital, &kecil, &angka, &simbol, &lainnya);
    
    printf("Detail per kategori:\n");
    printf("- Huruf kapital : %d\n", kapital);
    printf("- Huruf kecil   : %d\n", kecil);
    printf("- Angka         : %d\n", angka);
    printf("- Simbol        : %d\n", simbol);
    printf("- Lainnya       : %d\n\n", lainnya);
    
    printf("Karakter\tKode Morse\n");
    printf("----------------------------------\n");
    
    // Menggunakan VisualisasiTreeMorse untuk menampilkan karakter dan kodenya
    char path[100] = "";
    VisualisasiTreeMorse(root, 0, path);
    
    printf("===========================================\n");
} 