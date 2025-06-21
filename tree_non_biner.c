/*
Author: Roufiel Hadi
NIM: 241524028
Kelas: 1A
Prodi: Sarjana Terapan Teknik Informatika
Jurusan: Teknik Komputer dan Informatika
Politeknik Negeri Bandung
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_non_biner.h"

void Create_tree(Isi_Tree X, int Jml_Node) {
    int i;
    char temp[100];
    for (i = 1; i <= jml_maks; i++) {
        X[i].info = NULL;
        X[i].ps_fs = 0;
        X[i].ps_nb = 0;
        X[i].ps_pr = 0;
    }

    for (i = 1; i <= Jml_Node; i++) {
        printf("Masukkan nama stasiun ke-%d: ", i);
        scanf(" %[^\n]", temp);
        X[i].info = strdup(temp); // Menggunakan strdup untuk alokasi string

        if (i == 1) {
            X[i].ps_pr = 0;
        } else {
            printf("Masukkan parent dari stasiun %s (indeks): ", temp);
            int parent;
            scanf("%d", &parent);
            X[i].ps_pr = parent;
            if (X[parent].ps_fs == 0) {
                X[parent].ps_fs = i;
            } else {
                int sibling = X[parent].ps_fs;
                while (X[sibling].ps_nb != 0) {
                    sibling = X[sibling].ps_nb;
                }
                X[sibling].ps_nb = i;
            }
        }
    }
}

boolean IsEmpty(Isi_Tree P) {
    return P[1].info == NULL;
}

// Helper function for PreOrder traversal
void RecursePreOrder(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == NULL) return;
    printf("%s ", P[idx].info);
    RecursePreOrder(P, P[idx].ps_fs);
    RecursePreOrder(P, P[idx].ps_nb);
}

void PreOrder(Isi_Tree P) {
    RecursePreOrder(P, 1);
    printf("\n");
}

// Helper function for InOrder traversal
void RecurseInOrder(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == NULL) return;
    int child = P[idx].ps_fs;
    if (child != 0) {
        RecurseInOrder(P, child);
    }
    printf("%s ", P[idx].info);
    if (child != 0) {
        child = P[child].ps_nb;
        while (child != 0) {
            RecurseInOrder(P, child);
            child = P[child].ps_nb;
        }
    }
}

void InOrder(Isi_Tree P) {
    RecurseInOrder(P, 1);
    printf("\n");
}

// Helper function for PostOrder traversal
void RecursePostOrder(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == NULL) return;
    int child = P[idx].ps_fs;
    while (child != 0) {
        RecursePostOrder(P, child);
        child = P[child].ps_nb;
    }
    printf("%s ", P[idx].info);
}

void PostOrder(Isi_Tree P) {
    RecursePostOrder(P, 1);
    printf("\n");
}

void Level_order(Isi_Tree X, int Maks_node) {
    if (IsEmpty(X)) return;
    
    int i;
    for (i = 1; i <= Maks_node; i++) {
        if (X[i].info != NULL) {
            printf("%s ", X[i].info);
        }
    }
    printf("\n");
}

void PrintTree(Isi_Tree P) {
    // No longer needed since this is handled in halaman.c's print_tree function
    // The formatting is now handled in the print_tree function in halaman.c
}

boolean Search(Isi_Tree P, infotype X) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != NULL && strcmp(P[i].info, X) == 0) return TRUE;
    }
    return FALSE;
}

int nbElmt(Isi_Tree P) {
    int count = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != NULL) count++;
    }
    return count;
}

int nbDaun(Isi_Tree P) {
    int count = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != NULL && P[i].ps_fs == 0) count++;
    }
    return count;
}

int Level(Isi_Tree P, infotype X) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != NULL && strcmp(P[i].info, X) == 0) {
            int level = 0;
            int pr = P[i].ps_pr;
            while (pr != 0) {
                level++;
                pr = P[pr].ps_pr;
            }
            return level;
        }
    }
    return -1;
}

int Depth(Isi_Tree P) {
    int maxDepth = 0;
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != NULL) {
            int depth = 0;
            int pr = P[i].ps_pr;
            while (pr != 0) {
                depth++;
                pr = P[pr].ps_pr;
            }
            if (depth > maxDepth) maxDepth = depth;
        }
    }
    return maxDepth;
}

int Max(int Data1, int Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}

int FindEmptySlot(Isi_Tree P) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info == NULL) return i;
    }
    return 0;
}

void InsertNode(Isi_Tree P, infotype info, int parent_idx) {
    int idx = FindEmptySlot(P);
    if (idx == 0) return;

    P[idx].info = strdup(info);
    P[idx].ps_pr = parent_idx;
    P[idx].ps_fs = 0;
    P[idx].ps_nb = 0;

    if (P[parent_idx].ps_fs == 0) {
        P[parent_idx].ps_fs = idx;
    } else {
        int sibling = P[parent_idx].ps_fs;
        while (P[sibling].ps_nb != 0) {
            sibling = P[sibling].ps_nb;
        }
        P[sibling].ps_nb = idx;
    }
}

// Helper function for DeleteNode
void RecurseDelete(Isi_Tree P, int i) {
    if (i == 0 || P[i].info == NULL) return;
    int child = P[i].ps_fs;
    while (child != 0) {
        int next = P[child].ps_nb;
        RecurseDelete(P, child);
        child = next;
    }
    free((void*)P[i].info); // Bebaskan memori untuk string dengan cast eksplisit
    P[i].info = NULL;
    P[i].ps_fs = 0;
    P[i].ps_nb = 0;
    P[i].ps_pr = 0;
}

void DeleteNode(Isi_Tree P, int idx) {
    int parent = P[idx].ps_pr;
    if (parent != 0) {
        if (P[parent].ps_fs == idx) {
            P[parent].ps_fs = P[idx].ps_nb;
        } else {
            int curr = P[parent].ps_fs;
            while (curr != 0 && P[curr].ps_nb != idx) {
                curr = P[curr].ps_nb;
            }
            if (curr != 0) P[curr].ps_nb = P[idx].ps_nb;
        }
    }
    RecurseDelete(P, idx);
}

int GetParent(Isi_Tree P, int idx) {
    return P[idx].ps_pr == 0 ? -1 : P[idx].ps_pr;
}

int GetChild(Isi_Tree P, int idx, int k) {
    int child = P[idx].ps_fs;
    int i;
    for (i = 1; i < k && child != 0; i++) {
        child = P[child].ps_nb;
    }
    return child;
}

boolean IsLeaf(Isi_Tree P, int idx) {
    return (P[idx].ps_fs == 0);
}

boolean IsRoot(Isi_Tree P, int idx) {
    return (P[idx].ps_pr == 0);
}

void CopyTree(Isi_Tree P, Isi_Tree Q) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != NULL) {
            Q[i].info = strdup(P[i].info);
        } else {
            Q[i].info = NULL;
        }
        Q[i].ps_fs = P[i].ps_fs;
        Q[i].ps_nb = P[i].ps_nb;
        Q[i].ps_pr = P[i].ps_pr;
    }
}

boolean CompareTrees(Isi_Tree P1, Isi_Tree P2) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        // Periksa jika salah satu NULL dan yang lain tidak
        if ((P1[i].info == NULL && P2[i].info != NULL) || 
            (P1[i].info != NULL && P2[i].info == NULL)) {
            return FALSE;
        }
        // Jika keduanya tidak NULL, bandingkan string
        if (P1[i].info != NULL && P2[i].info != NULL && 
            strcmp(P1[i].info, P2[i].info) != 0) {
            return FALSE;
        }
        // Bandingkan pointer
        if (P1[i].ps_fs != P2[i].ps_fs ||
            P1[i].ps_nb != P2[i].ps_nb ||
            P1[i].ps_pr != P2[i].ps_pr) {
            return FALSE;
        }
    }
    return TRUE;
}

int Degree(Isi_Tree P, int idx) {
    int count = 0;
    int child = P[idx].ps_fs;
    while (child != 0) {
        count++;
        child = P[child].ps_nb;
    }
    return count;
}
