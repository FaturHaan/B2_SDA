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

// Mencari anak dari suatu parent berdasarkan item tertentu, jika tidak ditemukan maka akan dibuatkan node anak baru
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

// Memasukkan sekumpulan item dari sebuah transaksi ke dalam Trie secara rekursif untuk menghitung support kombinasi subset
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

// Menelusuri Trie untuk mencetak pasangan itemset yang frekuensi kemunculannya mencapai atau melebihi threshold
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

// Sub-modul untuk mengolah string transaksi (dari file atau manual) dan memasukannya ke Tries
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
