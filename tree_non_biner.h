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

//Maksimal node yang dapat ditampung dalam array
#define jml_maks 200

//Arah traversal
#define kebawah 1
#define keatas 2
#define kekanan 3
#define nil 0

/***************************/
/* Type data */
/***************************/
/* Indeks dalam bahasa C dimulai dengan 0; tetapi indeks 0 tidak
   dipakai */
/* Kamus */
typedef const char* infotype;
typedef int address;
typedef struct {
    infotype info;
    address ps_fs, ps_nb, ps_pr;
} nbtree;
typedef nbtree Isi_Tree[jml_maks+1];

/***************************/
/* S P E S I F I K A S I */
/***************************/
void Create_tree(Isi_Tree X, int Jml_Node);
// Create Non Binary Tree sebanyak Jml_Node
// Tujuan mengentrykan Non Binary Tree ke array Isi_Tree dengan polLevel Order
// Jml Node adalah banyaknya elemen dalam Tree yang menjadi parameter input

boolean IsEmpty (Isi_Tree P);
/* Mengirimkan true jika Isi_Tree KOSONG */

/***** Helper Functions *****/
void RecursePreOrder(Isi_Tree P, int idx);
/* Helper function for PreOrder traversal */

void RecurseInOrder(Isi_Tree P, int idx);
/* Helper function for InOrder traversal */

void RecursePostOrder(Isi_Tree P, int idx);
/* Helper function for PostOrder traversal */

void RecurseDelete(Isi_Tree P, int i);
/* Helper function for DeleteNode */

/***** Traversal *****/
void PreOrder (Isi_Tree P);
/* Traversal PreOrder */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah ditampilkan secara PreOrder : Parent, fs, nb */

void InOrder (Isi_Tree P);
/* Traversal InOrder */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah ditampilkan secara InOrder : fs, Parent, Sisa anak lain */

void PostOrder (Isi_Tree P);
/* Traversal PostOrder */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah ditampilkan secara PostOrder : fs, nb, Parent */

void Level_order(Isi_Tree X, int Maks_node);
/* Traversal LevelOrder */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah ditampilkan secara Level Order */

void PrintTree (Isi_Tree P);
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah ditulis ke layar */

/***** Search *****/
boolean Search (Isi_Tree P, infotype X);
/* Mengirimkan true jika ada node dari P yang bernilai X */

/***** Fungsi Lain *****/
int nbElmt (Isi_Tree P);
/* Mengirimkan banyak elemen (node) di pohon non biner P */

int nbDaun (Isi_Tree P);
/* Mengirimkan banyak daun (node) pohon non biner P */

int Level (Isi_Tree P, infotype X);
/* Mengirimkan level dari node X yang merupakan salah satu simpul */
/* dr pohon P. Akar (P) levelnya adalah 0. Pohon tidak kosong */

int Depth (Isi_Tree P);
/* Pohon Biner mungkin Kosong, mengirimkan 'depth' yaitu tinggi dari Pohon */
/* Basis : Pohon Kosong, tingginya Nol */

int Max (int Data1, int Data2);
/* Mengirimkan Nilai terbesar dari dua data */

/***** Fungsi Tambahan *****/
void InsertNode(Isi_Tree P, infotype info, int parent_idx);
/* Menambahkan simpul baru ke dalam tree */
/* IS : P terdefinisi, terdapat slot kosong dalam array */
/* FS : Menambahkan simpul baru dengan nilai info sebagai anak dari parent_idx */

void DeleteNode(Isi_Tree P, int idx);
/* Menghapus node dari tree beserta seluruh subtree-nya */
/* IS : P terdefinisi, idx adalah indeks simpul yang akan dihapus */
/* FS : Menghapus simpul idx dan semua anak-anaknya */

int GetParent(Isi_Tree P, int idx);
/* Mencari parent dari node */
/* IS : P terdefinisi */
/* FS : Mengembalikan indeks parent dari simpul idx, atau -1 jika root */

int GetChild(Isi_Tree P, int idx, int k);
/* Mencari anak ke-k dari node */
/* IS : P terdefinisi */
/* FS : Mengembalikan indeks anak ke-k dari simpul idx */

boolean IsLeaf(Isi_Tree P, int idx);
/* Mengecek apakah simpul adalah daun (tidak memiliki anak) */
/* IS : P terdefinisi */
/* FS : Mengembalikan true jika simpul idx adalah daun */

boolean IsRoot(Isi_Tree P, int idx);
/* Mengecek apakah simpul adalah root */
/* IS : P terdefinisi */
/* FS : Mengembalikan true jika simpul idx adalah root */

void CopyTree(Isi_Tree P, Isi_Tree Q);
/* Menyalin seluruh isi tree P ke tree Q */
/* IS : P terdefinisi */
/* FS : Mengisi Q sebagai salinan dari P secara identik */

boolean CompareTrees(Isi_Tree P1, Isi_Tree P2);
/* Membandingkan dua tree apakah identik */
/* IS : P1 dan P2 terdefinisi */
/* FS : Mengembalikan true jika kedua tree identik (struktur dan nilai) */

int Degree(Isi_Tree P, int idx);
/* Menghitung jumlah anak langsung dari suatu node */
/* IS : P terdefinisi */
/* FS : Mengembalikan banyaknya anak langsung dari simpul idx */

#endif

