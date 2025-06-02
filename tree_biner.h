/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#ifndef TREE_H
#define TREE_H
#include "boolean.h"

//Arah traversal
#define kebawah 1
#define keatas 2
#define kekanan 3
#define nil 0

/***************************/
/* Tipe data */
/***************************/
typedef char infotype;
typedef struct HashPassword {
    infotype info;         /* karakter */
    struct HashPassword* kiri;     /* pointer ke left child */
    struct HashPassword* kanan;    /* pointer ke right child */
} HashPassword;

// Definisi alias untuk pointer HashPassword
typedef HashPassword* addressHash;

/***************************/
/* S P E S I F I K A S I */
/***************************/

void CreateHashTree(HashPassword **root, int Jml_Node);
/* Tujuan : Membuat Binary Tree sebanyak Jml_Node */
/* IS      : root belum terdefinisi */
/* FS      : root terdefinisi dengan Jml_Node simpul */

boolean IsEmptyHash(HashPassword *root);
/* Tujuan : Memeriksa apakah tree kosong */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan true jika root adalah NULL */

void PreOrderHash(HashPassword *root);
/* Tujuan : Melakukan traversal PreOrder */
/* IS      : root terdefinisi */
/* FS      : Semua simpul root sudah ditampilkan secara PreOrder: Parent, Left, Right */

void InOrderHash(HashPassword *root);
/* Tujuan : Melakukan traversal InOrder */
/* IS      : root terdefinisi */
/* FS      : Semua simpul root sudah ditampilkan secara InOrder: Left, Parent, Right */

void PostOrderHash(HashPassword *root);
/* Tujuan : Melakukan traversal PostOrder */
/* IS      : root terdefinisi */
/* FS      : Semua simpul root sudah ditampilkan secara PostOrder: Left, Right, Parent */

void Level_orderHash(HashPassword *root);
/* Tujuan : Melakukan traversal LevelOrder */
/* IS      : root terdefinisi */
/* FS      : Semua simpul root sudah ditampilkan secara Level Order */

void PrintHashTree(HashPassword *root);
/* Tujuan : Menampilkan isi tree ke layar */
/* IS      : root terdefinisi */
/* FS      : Semua simpul root sudah ditulis ke layar */

// Helper function for recursive tree printing
void printHashTreeRecursive(HashPassword *root, int level);
/* Tujuan : Menampilkan tree secara rekursif dengan indentasi */
/* IS      : root terdefinisi, level adalah level saat ini untuk indentasi */
/* FS      : Tree ditampilkan secara rekursif dengan indentasi */

/***** Search *****/
boolean SearchHash(HashPassword *root, infotype X);
/* Tujuan : Mencari nilai X pada tree */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan true jika ada node dari tree yang bernilai X */

/***** Fungsi Lain *****/
int nbElmtHash(HashPassword *root);
/* Tujuan : Menghitung jumlah elemen dalam tree */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan banyak elemen (node) di pohon biner root */

int nbDaunHash(HashPassword *root);
/* Tujuan : Menghitung jumlah daun dalam tree */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan banyak daun (node) pohon biner root */

int LevelHash(HashPassword *root, infotype X);
/* Tujuan : Menentukan level dari node X */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan level dari node X yang merupakan salah satu simpul dari pohon biner root. Akar levelnya adalah 0 */

int DepthHash(HashPassword *root);
/* Tujuan : Menghitung kedalaman tree */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan 'depth' yaitu tinggi dari pohon biner root */

/***** Fungsi Tambahan *****/
HashPassword* findHashNode(HashPassword *root, infotype info);
/* Tujuan : Mencari node dengan info tertentu */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan pointer ke node yang dicari atau NULL jika tidak ditemukan */

void InsertHashNode(HashPassword **root, infotype info, addressHash parent);
/* Tujuan : Menambahkan simpul baru ke dalam pohon biner */
/* IS      : root terdefinisi */
/* FS      : Menambahkan simpul baru dengan nilai info sebagai anak dari parent */

void DeleteHashNode(HashPassword **root, addressHash node);
/* Tujuan : Menghapus node dari tree beserta seluruh subtree-nya */
/* IS      : root terdefinisi */
/* FS      : Menghapus simpul node dan semua anak-anaknya */

int GetHashParent(HashPassword *root, addressHash node);
/* Tujuan : Mencari parent dari node */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan parent dari simpul node */

int GetHashChild(HashPassword *root, addressHash node, int k);
/* Tujuan : Mencari anak ke-k dari node */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan anak ke-k dari simpul node */

boolean IsHashLeaf(HashPassword *root, addressHash node);
/* Tujuan : Mengecek apakah simpul adalah daun */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan true jika simpul node adalah daun */

boolean IsHashRoot(HashPassword *root, addressHash node);
/* Tujuan : Mengecek apakah simpul adalah root */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan true jika simpul node adalah root */

void CopyHashTree(HashPassword *root, HashPassword **dest);
/* Tujuan : Menyalin seluruh isi tree */
/* IS      : root terdefinisi */
/* FS      : Mengisi dest sebagai salinan dari root */

boolean CompareHashTrees(HashPassword *root1, HashPassword *root2);
/* Tujuan : Membandingkan dua tree */
/* IS      : root1 dan root2 terdefinisi */
/* FS      : Mengembalikan true jika kedua tree identik (struktur dan nilai) */

int HashDegree(HashPassword *root, addressHash node);
/* Tujuan : Menghitung jumlah anak langsung dari suatu node */
/* IS      : root terdefinisi */
/* FS      : Mengembalikan banyaknya anak langsung dari simpul node */

/***** Fungsi Khusus untuk Hashing Password *****/
char* EncodeToMorse(HashPassword *root, char character);
/* Tujuan : Mengkodekan karakter menjadi kode Morse berdasarkan tree */
/* IS      : root terdefinisi, character adalah karakter yang akan dikodekan */
/* FS      : Mengembalikan string kode Morse untuk karakter tersebut */

char* HashPassword(HashPassword *root, const char* password);
/* Tujuan : Menghasilkan hash dari password menggunakan kode Morse */
/* IS      : root terdefinisi, password adalah string yang akan di-hash */
/* FS      : Mengembalikan string hash dari password */

#endif

