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

// Mendapatkan string nama barang berdasarkan angka representasinya
void AmbilNamaBarang(infotype idBarang, char* namaBarang) {
    switch(idBarang) {
        case 1:
            strcpy(namaBarang, "Rinso");
            break;
        case 2:
            strcpy(namaBarang, "Susu");
            break;
        case 3:
            strcpy(namaBarang, "Beras");
            break;
        case 4:
            strcpy(namaBarang, "Gula");
            break;
        default:
            sprintf(namaBarang, "Item%d", idBarang);
            break;
    }
}

// Modul untuk mengurutkan array
void UrutkanDaftar(infotype *daftar, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (daftar[i] > daftar[j]) {
                int temp = daftar[i];
                daftar[i] = daftar[j];
                daftar[j] = temp;
            }
        }
    }
}


