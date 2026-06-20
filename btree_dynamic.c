#include "nbtree_dynamic.h"
#include <string.h>

// Mengalokasikan node baru dengan nilai X
address Alokasi(infotype X) {
    address P = (address)malloc(sizeof(Node));
    if (P != NULL) {
        P->info = X;
        P->support = 0;
        P->ps_fs = NULL;
        P->ps_nb = NULL;
        P->ps_pr = NULL;
    }
    return P;
}

// Menghapus seluruh node dalam tree
void DeAlokasi(Tree *T) {
    if (*T != NULL) {
        DeAlokasi(&((*T)->ps_fs));
        DeAlokasi(&((*T)->ps_nb));
        free(*T);
        *T = NULL;
    }
}

// Inisialisasi awal untuk struktur Trie dengan mengatur nilai default dan membuat root dummy
void InisialisasiTrie(Tree *root) {
    *root = Alokasi(-1); // Nilai default untuk Trie
}


