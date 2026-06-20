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

void Create_tree(Tree *T) {
    *T = NULL;
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

void PreOrder(Tree T) {
    if (T == NULL) return;
    printf("%d ", T->info);
    PreOrder(T->ps_fs);
    PreOrder(T->ps_nb);
}

void InOrder(Tree T) {
    if (T == NULL) return;
    InOrder(T->ps_fs);
    printf("%d ", T->info);
    InOrder(T->ps_nb);
}

void PostOrder(Tree T) {
    if (T == NULL) return;
    PostOrder(T->ps_fs);
    PostOrder(T->ps_nb);
    printf("%d ", T->info);
}

void LevelOrder(Tree T) {
    if (T == NULL) return;

    int capacity = 16;
    int count = 0;
    int head = 0;
    address *queue = (address *)malloc(capacity * sizeof(address));
    if (queue == NULL) return;

    queue[count++] = T;
    while (head < count) {
        address current = queue[head++];
        printf("%d ", current->info);

        address child = current->ps_fs;
        while (child != NULL) {
            if (count >= capacity) {
                capacity *= 2;
                address *newQueue = (address *)realloc(queue, capacity * sizeof(address));
                if (newQueue == NULL) {
                    free(queue);
                    return;
                }
                queue = newQueue;
            }
            queue[count++] = child;
            child = child->ps_nb;
        }
    }

    free(queue);
}

int Search(Tree T, infotype X) {
    if (T == NULL) return 0;
    if (T->info == X) return 1;
    if (Search(T->ps_fs, X)) return 1;
    if (Search(T->ps_nb, X)) return 1;
    return 0;
}

// Inisialisasi awal untuk struktur Trie dengan mengatur nilai default dan membuat root dummy
void InisialisasiTrie(Tree *root) {
    *root = Alokasi(-1); // Nilai default untuk Trie
}

address CariAtauBuatChild(address parent, infotype idBarang) {
    if (parent == NULL)
        return NULL;
    
    address child = parent->ps_fs;
    address prev = NULL;
    
    while (child != NULL) {
        if (child->info == idBarang) {
            return child;
        }
        prev = child;
        child = child->ps_nb;
    }
    
    address newNode = Alokasi(idBarang);
    newNode->ps_pr = parent;
    
    if (prev == NULL) {
        parent->ps_fs = newNode;
    } else {
        prev->ps_nb = newNode;
    }
    
    return newNode;
}

void MasukkanTransaksiKeTrie(address node, infotype *daftarBarang, int jumlahBarang) {
    int i;
    if (node == NULL)
        return;
    for (i = 0; i < jumlahBarang; i++) {
        address child = CariAtauBuatChild(node, daftarBarang[i]);
        child->support++;
        // Rekursif masukkan sisa subset kombinasi
        MasukkanTransaksiKeTrie(child, daftarBarang + i + 1, jumlahBarang - i - 1);
    }
}

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

void CetakItemsetSering(address node, infotype *jalur, int jumlahItem, int threshold) {
    int i;
    if (node == NULL)
        return;

    if (node->info != -1) { // Jika bukan root dummy
        jalur[jumlahItem] = node->info;
        jumlahItem++;
        
        // Cetak jika panjang jalur >= 2 (sebuah asosiasi/pasangan) dan support >= threshold
        if (jumlahItem >= 2 && node->support >= threshold) {
            for (i = 0; i < jumlahItem; i++) {
                char namaBarang[20];
                AmbilNamaBarang(jalur[i], namaBarang);
        
                if (i == jumlahItem - 1) {
                    printf("%s", namaBarang);
                } else {
                    printf("%s, ", namaBarang);
                }
            }
            printf("\n");
        }
    }
    
    address child = node->ps_fs;
    while (child != NULL) {
        CetakItemsetSering(child, jalur, jumlahItem, threshold);
        child = child->ps_nb;
    }
}

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

void ProsesStringTransaksi(Tree root, char *teksInput, int *hitungTransaksi) {
    infotype daftarBarang[20];
    int jumlah = 0;
    int valid = 1;
    int i, idBarang, duplikat;
    
    // Memisahkan input berdasarkan spasi atau koma
    char *token = strtok(teksInput, " \n\r,");
    while (token != NULL) {
        idBarang = atoi(token);
        if (idBarang >= 1 && idBarang <= 4) {
            // Mencegah duplikat idBarang dalam 1 transaksi
            duplikat = 0;
            for (i = 0; i < jumlah; i++) {
                if (daftarBarang[i] == idBarang) {
                    duplikat = 1; 
                    break;
                }
            }
            if (!duplikat) {
                daftarBarang[jumlah++] = idBarang;
            }
        } else {
            // Jika ada idBarang yang tidak valid (misal 5, huruf, dst.), tandai tidak valid
            valid = 0;
            break;
        }
        token = strtok(NULL, " \n\r,");
    }
    
    if (valid && jumlah > 0) {
        // Urutkan idBarang (Himpunan harus konsisten terurut)
        UrutkanDaftar(daftarBarang, jumlah);

        // Masukkan ke Trie
        MasukkanTransaksiKeTrie(root, daftarBarang, jumlah);
        (*hitungTransaksi)++; // Increment transaksi sukses
    }
}
