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

// Tabel kode Morse untuk semua karakter yang didukung
static MorseCode morseTable[] = {
    // Huruf besar
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."},
    
    // Huruf kecil (kode sama dengan huruf besar)
    {'a', ".-"}, {'b', "-..."}, {'c', "-.-."}, {'d', "-.."}, {'e', "."},
    {'f', "..-."}, {'g', "--."}, {'h', "...."}, {'i', ".."}, {'j', ".---"},
    {'k', "-.-"}, {'l', ".-.."}, {'m', "--"}, {'n', "-."}, {'o', "---"},
    {'p', ".--."}, {'q', "--.-"}, {'r', ".-."}, {'s', "..."}, {'t', "-"},
    {'u', "..-"}, {'v', "...-"}, {'w', ".--"}, {'x', "-..-"}, {'y', "-.--"},
    {'z', "--.."},
    
    // Angka
    {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
    
    // Tanda baca dan simbol
    {'.', ".-.-.-"}, {',', "--..--"}, {'?', "..--.."}, {'\'', ".----."}, {'!', "-.-.--"},
    {'/', "-..-."}, {'(', "-.--."}, {')', "-.--.-"}, {'&', ".-..."}, {':', "---..."},
    {';', "-.-.-."}, {'=', "-...-"}, {'+', ".-.-."}, {'-', "-....-"}, {'_', "..--.-"},
    {'"', ".-..-."}, {'$', "...-..-"}, {'@', ".--.-."},
    
    // Karakter spesial
    {' ', "/"}  // Spasi direpresentasikan sebagai / dalam kode Morse
};

static int morseTableSize = sizeof(morseTable) / sizeof(morseTable[0]);

// *** IMPLEMENTASI BARU SESUAI DENGAN GITHUB REPOSITORY ***

// Fungsi untuk membangun tree Morse dengan pendekatan baru
void BuildMorseTree(HashPassword **root) {
    // Alokasi memori untuk root
    *root = (HashPassword*)malloc(sizeof(HashPassword));
    if (*root == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk tree Morse!\n");
        return;
    }
    
    // Inisialisasi root
    (*root)->info = '\0';  // Root tidak memiliki karakter
    (*root)->kiri = NULL;
    (*root)->kanan = NULL;
    
    // Masukkan semua karakter ke dalam tree
    for (int i = 0; i < morseTableSize; i++) {
        InsertIntoMorseTree(root, morseTable[i].character, morseTable[i].morseCode);
    }
}

// Fungsi untuk menyisipkan karakter ke dalam tree berdasarkan kode Morse
void InsertIntoMorseTree(HashPassword **root, char character, const char *code) {
    if (*root == NULL) {
        return;
    }
    
    HashPassword *current = *root;
    int len = strlen(code);
    
    // Traversal tree berdasarkan kode Morse
    for (int i = 0; i < len; i++) {
        if (code[i] == '.') {
            // Jika belum ada node kiri, buat node baru
            if (current->kiri == NULL) {
                current->kiri = (HashPassword*)malloc(sizeof(HashPassword));
                current->kiri->info = '\0';
                current->kiri->kiri = NULL;
                current->kiri->kanan = NULL;
            }
            current = current->kiri;
        } else if (code[i] == '-') {
            // Jika belum ada node kanan, buat node baru
            if (current->kanan == NULL) {
                current->kanan = (HashPassword*)malloc(sizeof(HashPassword));
                current->kanan->info = '\0';
                current->kanan->kiri = NULL;
                current->kanan->kanan = NULL;
            }
            current = current->kanan;
        }
    }
    
    // Simpan karakter di node terakhir
    current->info = character;
}

// Fungsi untuk traversal tree Morse berdasarkan kode Morse
char TraverseMorseTree(HashPassword *root, const char *code) {
    if (root == NULL || code == NULL) {
        return '\0';
    }
    
    HashPassword *current = root;
    int len = strlen(code);
    
    // Traversal tree berdasarkan kode Morse
    for (int i = 0; i < len; i++) {
        if (code[i] == '.') {
            if (current->kiri == NULL) {
                return '\0';  // Kode tidak valid
            }
            current = current->kiri;
        } else if (code[i] == '-') {
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

// *** OPERASI DASAR MORSE CODE (DISESUAIKAN) ***
void InisialisasiMorseCode(HashPassword **morseTree) {
    // Gunakan fungsi BuildMorseTree untuk menginisialisasi tree
    BuildMorseTree(morseTree);
}

char* KonversiKarakterKeMorse(HashPassword *morseTree, char karakter) {
    // Cari kode Morse dari tabel
    for (int i = 0; i < morseTableSize; i++) {
        if (morseTable[i].character == karakter) {
            char* result = (char*)malloc(strlen(morseTable[i].morseCode) + 1);
            strcpy(result, morseTable[i].morseCode);
            return result;
        }
    }
    
    // Karakter tidak ditemukan
    return strdup("");
}

char KonversiMorseKeKarakter(HashPassword *morseTree, const char *morseCode) {
    if (morseTree == NULL || morseCode == NULL) {
        return '\0';
    }
    
    // Gunakan fungsi TraverseMorseTree untuk konversi
    return TraverseMorseTree(morseTree, morseCode);
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
                // Konversi kode ke karakter menggunakan TraverseMorseTree
                char c = TraverseMorseTree(morseTree, tempMorseCode);
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
        char c = TraverseMorseTree(morseTree, tempMorseCode);
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

// *** OPERASI PEMBANTU ***
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

MorseCode* GetMorseTable() {
    return morseTable;
}

int GetMorseTableSize() {
    return morseTableSize;
}

void TampilkanTabelMorse() {
    printf("======== TABEL KODE MORSE ========\n");
    printf("| Karakter | Kode Morse |\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < morseTableSize; i++) {
        if (morseTable[i].character == ' ') {
            printf("|  Spasi   | %-10s |\n", morseTable[i].morseCode);
        } else {
            printf("|    %c     | %-10s |\n", morseTable[i].character, morseTable[i].morseCode);
        }
    }
    
    printf("================================\n");
} 