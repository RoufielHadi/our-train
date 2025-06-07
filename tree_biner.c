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
#include "tree_biner.h"
#include "boolean.h"

void CreateHashTree(HashPassword **root, int Jml_Node) {
    *root = NULL;
    int i;
    infotype temp;
    char choice;
    HashPassword *current, *parent;

    for (i = 1; i <= Jml_Node; i++) {
        printf("Masukkan info node ke-%d: ", i);
        scanf(" %c", &temp);
        
        HashPassword *newNode = (HashPassword*)malloc(sizeof(HashPassword));
        newNode->info = temp;
        newNode->kiri = newNode->kanan = NULL;
        
        if (*root == NULL) {
            *root = newNode; // Simpul pertama sebagai root
        } else {
            current = *root;
            while (1) {
                printf("Masukkan node %c sebagai anak kiri/kanan dari %c? (L/R): ", temp, current->info);
                scanf(" %c", &choice);
                
                if (choice == 'L' || choice == 'l') {
                    if (current->kiri == NULL) {
                        current->kiri = newNode;
                        break;
                    } else {
                        printf("Apakah ingin melanjutkan ke node %c? (Y/N): ", current->kiri->info);
                        scanf(" %c", &choice);
                        if (choice == 'Y' || choice == 'y') {
                            current = current->kiri;
                        } else {
                            current->kiri = newNode;
                            break;
                        }
                    }
                } else if (choice == 'R' || choice == 'r') {
                    if (current->kanan == NULL) {
                        current->kanan = newNode;
                        break;
                    } else {
                        printf("Apakah ingin melanjutkan ke node %c? (Y/N): ", current->kanan->info);
                        scanf(" %c", &choice);
                        if (choice == 'Y' || choice == 'y') {
                            current = current->kanan;
                        } else {
                            current->kanan = newNode;
                            break;
                        }
                    }
                }
            }
        }
    }
}

boolean IsEmptyHash(HashPassword *root) {
    return root == NULL;
}

void PreOrderHash(HashPassword *root) {
    if (root == NULL) return;
    printf("%c ", root->info);
    PreOrderHash(root->kiri);
    PreOrderHash(root->kanan);
}

void InOrderHash(HashPassword *root) {
    if (root == NULL) return;
    InOrderHash(root->kiri);
    printf("%c ", root->info);
    InOrderHash(root->kanan);
}

void PostOrderHash(HashPassword *root) {
    if (root == NULL) return;
    PostOrderHash(root->kiri);
    PostOrderHash(root->kanan);
    printf("%c ", root->info);
}

// Queue structure for level order traversal
typedef struct QNodeHash {
    HashPassword *data;
    struct QNodeHash *next;
} QNodeHash;

typedef struct {
    QNodeHash *front, *rear;
} QueueHash;

void initQueueHash(QueueHash *q) {
    q->front = q->rear = NULL;
}

void enqueueHash(QueueHash *q, HashPassword *data) {
    QNodeHash *newNode = (QNodeHash*)malloc(sizeof(QNodeHash));
    newNode->data = data;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    
    q->rear->next = newNode;
    q->rear = newNode;
}

HashPassword* dequeueHash(QueueHash *q) {
    if (q->front == NULL) return NULL;
    
    QNodeHash *temp = q->front;
    HashPassword *data = temp->data;
    
    q->front = q->front->next;
    
    if (q->front == NULL) q->rear = NULL;
    
    free(temp);
    return data;
}

void Level_orderHash(HashPassword *root) {
    if (root == NULL) return;
    
    QueueHash q;
    initQueueHash(&q);
    
    enqueueHash(&q, root);
    
    while (q.front != NULL) {
        HashPassword *current = dequeueHash(&q);
        printf("%c ", current->info);
        
        if (current->kiri != NULL)
            enqueueHash(&q, current->kiri);
        
        if (current->kanan != NULL)
            enqueueHash(&q, current->kanan);
    }
}

// Helper function to get tree height
int getHeightHash(HashPassword *root) {
    if (root == NULL) return 0;
    int leftHeight = getHeightHash(root->kiri);
    int rightHeight = getHeightHash(root->kanan);
    
    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

// Function to print spaces
void printSpacesHash(int count) {
    int i;
    for (i = 0; i < count; i++)
        printf(" ");
}

// Improved PrintTree implementation
void PrintHashTree(HashPassword *root) {
    if (root == NULL) return;
    
    printf("    %c\n", root->info);
    
    if (root->kiri != NULL || root->kanan != NULL) {
        printf("   / \\\n");
        
        // Print left and right children
        if (root->kiri != NULL && root->kanan != NULL) {
            printf("  %c   %c\n", root->kiri->info, root->kanan->info);
        } else if (root->kiri != NULL) {
            printf("  %c    \n", root->kiri->info);
        } else {
            printf("      %c\n", root->kanan->info);
        }
        
        // Print left-left and left-right grandchildren
        if (root->kiri != NULL && (root->kiri->kiri != NULL || root->kiri->kanan != NULL)) {
            printf(" / \\\n");
            
            if (root->kiri->kiri != NULL && root->kiri->kanan != NULL) {
                printf("%c   %c", root->kiri->kiri->info, root->kiri->kanan->info);
            } else if (root->kiri->kiri != NULL) {
                printf("%c    ", root->kiri->kiri->info);
            } else if (root->kiri->kanan != NULL) {
                printf("    %c", root->kiri->kanan->info);
            }
            
            // Print right-left and right-right grandchildren
            if (root->kanan != NULL && (root->kanan->kiri != NULL || root->kanan->kanan != NULL)) {
                printf("   / \\\n");
                
                if (root->kanan->kiri != NULL && root->kanan->kanan != NULL) {
                    printf("        %c   %c\n", root->kanan->kiri->info, root->kanan->kanan->info);
                } else if (root->kanan->kiri != NULL) {
                    printf("        %c    \n", root->kanan->kiri->info);
                } else if (root->kanan->kanan != NULL) {
                    printf("            %c\n", root->kanan->kanan->info);
                }
            } else {
                printf("\n");
            }
        } else if (root->kanan != NULL && (root->kanan->kiri != NULL || root->kanan->kanan != NULL)) {
            printf("      / \\\n");
            
            if (root->kanan->kiri != NULL && root->kanan->kanan != NULL) {
                printf("     %c   %c\n", root->kanan->kiri->info, root->kanan->kanan->info);
            } else if (root->kanan->kiri != NULL) {
                printf("     %c    \n", root->kanan->kiri->info);
            } else if (root->kanan->kanan != NULL) {
                printf("         %c\n", root->kanan->kanan->info);
            }
        }
    }
    
    printf("\nNote: This is a simplified view of the top of the tree.\n");
    printf("Full traversal of the tree structure:\n\n");
    
    // Also print full hierarchical view
    printHashTreeRecursive(root, 0);
}

// Helper function for recursive tree printing
void printHashTreeRecursive(HashPassword *root, int level) {
    if (root == NULL) return;
    
    int i;
    for (i = 0; i < level; i++) {
        printf("    ");
    }
    
    printf("%c", root->info);
    
    if (root->kiri != NULL || root->kanan != NULL) {
        printf(" → ");
        if (root->kiri != NULL) {
            printf("L: %c", root->kiri->info);
        }
        if (root->kiri != NULL && root->kanan != NULL) {
            printf(", ");
        }
        if (root->kanan != NULL) {
            printf("R: %c", root->kanan->info);
        }
    }
    printf("\n");
    
    printHashTreeRecursive(root->kiri, level + 1);
    printHashTreeRecursive(root->kanan, level + 1);
}

boolean SearchHash(HashPassword *root, infotype X) {
    if (root == NULL) return false;
    if (root->info == X) return true;
    return SearchHash(root->kiri, X) || SearchHash(root->kanan, X);
}

int nbElmtHash(HashPassword *root) {
    if (root == NULL) return 0;
    return 1 + nbElmtHash(root->kiri) + nbElmtHash(root->kanan);
}

int nbDaunHash(HashPassword *root) {
    if (root == NULL) return 0;
    if (root->kiri == NULL && root->kanan == NULL) return 1;
    return nbDaunHash(root->kiri) + nbDaunHash(root->kanan);
}

int LevelHash(HashPassword *root, infotype X) {
    if (root == NULL) return -1; // Not found
    
    if (root->info == X) return 0; // Found at root level
    
    int leftLevel = LevelHash(root->kiri, X);
    if (leftLevel >= 0) return leftLevel + 1; // Found in left subtree
    
    int rightLevel = LevelHash(root->kanan, X);
    if (rightLevel >= 0) return rightLevel + 1; // Found in right subtree
    
    return -1; // Not found
}

int DepthHash(HashPassword *root) {
    if (root == NULL) return 0;
    int leftDepth = DepthHash(root->kiri);
    int rightDepth = DepthHash(root->kanan);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// Helper function to find a node
HashPassword* findHashNode(HashPassword *root, infotype info) {
    if (root == NULL) return NULL;
    if (root->info == info) return root;
    
    HashPassword *leftResult = findHashNode(root->kiri, info);
    if (leftResult) return leftResult;
    
    return findHashNode(root->kanan, info);
}

void InsertHashNode(HashPassword **root, infotype info, addressHash parent) {
    if (*root == NULL && parent == NULL) {
        // Create root if empty
        *root = (HashPassword*)malloc(sizeof(HashPassword));
        (*root)->info = info;
        (*root)->kiri = (*root)->kanan = NULL;
        return;
    }
    
    if (parent == NULL) return; // Invalid parent
    
    // Create new node
    HashPassword *newNode = (HashPassword*)malloc(sizeof(HashPassword));
    newNode->info = info;
    newNode->kiri = newNode->kanan = NULL;
    
    // Insert as left or right child based on availability
    if (parent->kiri == NULL) {
        parent->kiri = newNode;
    } else if (parent->kanan == NULL) {
        parent->kanan = newNode;
    } else {
        printf("Parent already has two children. Cannot insert node.\n");
        free(newNode);
    }
}

void freeHashNode(HashPassword *node) {
    if (node == NULL) return;
    
    // Recursively free all children first
    freeHashNode(node->kiri);
    freeHashNode(node->kanan);
    
    free(node);
}

void DeleteHashNode(HashPassword **root, addressHash node) {
    if (*root == NULL || node == NULL) return;
    
    // Special case: deleting the root
    if (*root == node) {
        freeHashNode(*root);
        *root = NULL;
        return;
    }
    
    // Find the parent of the node to delete
    HashPassword *current = *root;
    HashPassword *parent = NULL;
    
    QueueHash q;
    initQueueHash(&q);
    enqueueHash(&q, current);
    
    while (q.front != NULL) {
        current = dequeueHash(&q);
        
        if (current->kiri == node) {
            parent = current;
            freeHashNode(current->kiri);
            current->kiri = NULL;
            return;
        }
        
        if (current->kanan == node) {
            parent = current;
            freeHashNode(current->kanan);
            current->kanan = NULL;
            return;
        }
        
        if (current->kiri != NULL)
            enqueueHash(&q, current->kiri);
        
        if (current->kanan != NULL)
            enqueueHash(&q, current->kanan);
    }
}

// Helper function to find parent of a node
HashPassword* findHashParent(HashPassword *root, HashPassword *node) {
    if (root == NULL || node == NULL || root == node) return NULL;
    
    if ((root->kiri == node) || (root->kanan == node))
        return root;
    
    HashPassword *parent = findHashParent(root->kiri, node);
    if (parent != NULL) return parent;
    
    return findHashParent(root->kanan, node);
}

int GetHashParent(HashPassword *root, addressHash node) {
    if (root == NULL || node == NULL || root == node) return 0;
    
    HashPassword *parent = findHashParent(root, node);
    if (parent != NULL) return parent->info;
    
    return 0; // Return 0 if no parent found
}

int GetHashChild(HashPassword *root, addressHash node, int k) {
    if (node == NULL) return 0;
    
    if (k == 1 && node->kiri != NULL)
        return node->kiri->info;
    
    if (k == 2 && node->kanan != NULL)
        return node->kanan->info;
    
    return 0; // Return 0 if no such child exists
}

boolean IsHashLeaf(HashPassword *root, addressHash node) {
    return (node == NULL) ? false : (node->kiri == NULL && node->kanan == NULL);
}

boolean IsHashRoot(HashPassword *root, addressHash node) {
    return (root == node);
}

void CopyHashTree(HashPassword *root, HashPassword **dest) {
    if (root == NULL) {
        *dest = NULL;
        return;
    }
    
    *dest = (HashPassword*)malloc(sizeof(HashPassword));
    (*dest)->info = root->info;
    
    if (root->kiri != NULL) {
        CopyHashTree(root->kiri, &((*dest)->kiri));
    } else {
        (*dest)->kiri = NULL;
    }
    
    if (root->kanan != NULL) {
        CopyHashTree(root->kanan, &((*dest)->kanan));
    } else {
        (*dest)->kanan = NULL;
    }
}

boolean CompareHashTrees(HashPassword *root1, HashPassword *root2) {
    if (root1 == NULL && root2 == NULL) return true;
    if (root1 == NULL || root2 == NULL) return false;
    return (root1->info == root2->info) && 
           CompareHashTrees(root1->kiri, root2->kiri) && 
           CompareHashTrees(root1->kanan, root2->kanan);
}

int HashDegree(HashPassword *root, addressHash node) {
    if (node == NULL) return 0;
    int degree = 0;
    if (node->kiri != NULL) degree++;
    if (node->kanan != NULL) degree++;
    return degree;
}

/***** Fungsi Khusus untuk Hashing Password *****/

// Fungsi rekursif untuk mendapatkan kode Morse dari tree
void getMorseCodeRecursive(HashPassword *root, char target, char *path, char *result, boolean *found) {
    if (root == NULL || *found) return;
    
    if (root->info == target) {
        strcpy(result, path);
        *found = true;
        return;
    }
    
    int len = strlen(path);
    char leftPath[100], rightPath[100];
    
    strcpy(leftPath, path);
    strcat(leftPath, "X"); // X untuk titik dalam kode Morse
    
    strcpy(rightPath, path);
    strcat(rightPath, "O"); // O untuk strip dalam kode Morse
    
    getMorseCodeRecursive(root->kiri, target, leftPath, result, found);
    getMorseCodeRecursive(root->kanan, target, rightPath, result, found);
}

char* EncodeToMorse(HashPassword *root, char character) {
    if (root == NULL) return NULL;
    
    char path[100] = "";
    char *result = (char*)malloc(100 * sizeof(char));
    result[0] = '\0'; // Empty string
    
    boolean found = false;
    getMorseCodeRecursive(root, character, path, result, &found);
    
    if (!found) {
        strcpy(result, ""); // Character not found in tree
    }
    
    return result;
}

char* GenerateHashFromPassword(HashPassword *root, const char* password) {
    if (root == NULL || password == NULL) return NULL;
    
    int len = strlen(password);
    char *hashResult = (char*)malloc(1000 * sizeof(char)); // Cukup besar untuk menampung hash
    hashResult[0] = '\0'; // Empty string
    
    for (int i = 0; i < len; i++) {
        char *morseCode = EncodeToMorse(root, password[i]);
        
        if (morseCode != NULL && strlen(morseCode) > 0) {
            strcat(hashResult, morseCode);
            strcat(hashResult, "S"); // S sebagai pemisah antar karakter
            free(morseCode);
        }
    }
    
    // Hapus S terakhir jika ada
    int hashLen = strlen(hashResult);
    if (hashLen > 0 && hashResult[hashLen-1] == 'S') {
        hashResult[hashLen-1] = '\0';
    }
    
    return hashResult;
}

