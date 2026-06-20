#ifndef NBTREE_DYNAMIC_H
#define NBTREE_DYNAMIC_H

#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/*              DEFINISI TIPE DATA                   */
/****************************************************/

/* Tipe data untuk menyimpan informasi dalam node */
#ifndef INFOTYPE_DEFINED
#define INFOTYPE_DEFINED
typedef int infotype;
#endif

/* Tipe address adalah pointer ke Node */
typedef struct tNode* address;

/* Struktur Node untuk Non-Binary Tree Dinamis */
typedef struct tNode {
    infotype info;     // Menyimpan data (misal: karakter/nama node)
    int support;       // Support untuk Market Basket Analysis
    address ps_fs;     // Pointer ke anak pertama (first son)
    address ps_nb;     // Pointer ke saudara berikutnya (next brother)
    address ps_pr;     // Pointer ke parent (induk)
} Node;

/* Tree direpresentasikan sebagai pointer ke root */
typedef address Tree;

/****************************************************/
/*                MODUL KONSTRUKTOR                  */
/****************************************************/

/* Membuat tree kosong (root = NULL) */
void Create_tree(Tree *T);
/* I.S. T sembarang */
/* F.S. T menjadi tree kosong */

/* Mengalokasikan node baru dengan nilai X */
address Alokasi(infotype X);
/* Mengembalikan address node baru */
/* Jika gagal, mengembalikan NULL */

/****************************************************/
/*                MODUL VALIDASI                     */
/****************************************************/

/* Mengecek apakah tree kosong */
int IsEmpty(Tree T);
/* Mengembalikan 1 jika kosong, 0 jika tidak */

/****************************************************/
/*                MODUL UPDATE                      */
/****************************************************/

/* Menambahkan child sebagai anak dari parent */
void AddChild(address parent, address child);
/* I.S. parent dan child sudah dialokasi */
/* F.S. child menjadi anak dari parent */

/****************************************************/
/*                MODUL PENCARIAN                   */
/****************************************************/

/* Mencari node dengan nilai X */
int Search(Tree T, infotype X);
/* Mengembalikan 1 jika ditemukan, 0 jika tidak */

/****************************************************/
/*                MODUL ANALISIS TREE               */
/****************************************************/

/* Menghitung jumlah seluruh node */
int NbElmt(Tree T);

/* Menghitung jumlah daun (node tanpa anak) */
int NbDaun(Tree T);

/* Menghitung level node dengan nilai X */
int Level(Tree T, infotype X);
/* Root berada pada level 1 */

/* Menghitung kedalaman (height) tree */
int Depth(Tree T);

/* Mengembalikan nilai maksimum dari dua bilangan */
int Max(int a, int b);

/****************************************************/
/*                MODUL DEALOKASI                   */
/****************************************************/

/* Menghapus seluruh node dalam tree */
void DeAlokasi(Tree *T);
/* Membebaskan memori tree */

/****************************************************/
/*        MODUL MARKET BASKET ANALYSIS              */
/****************************************************/

/* Inisialisasi awal untuk struktur Trie dengan mengatur nilai default dan membuat root dummy */
void InisialisasiTrie(Tree *root);

/* Mencari anak dari suatu parent berdasarkan item tertentu, jika tidak ditemukan maka akan dibuatkan node anak baru */
address CariAtauBuatChild(address parent, infotype idBarang);

/* Memasukkan sekumpulan item dari sebuah transaksi ke dalam Trie secara rekursif untuk menghitung support kombinasi subset */
void MasukkanTransaksiKeTrie(address node, infotype *daftarBarang, int jumlahBarang);

/* Menelusuri Trie untuk mencetak pasangan itemset yang frekuensi kemunculannya mencapai atau melebihi threshold */
void CetakItemsetSering(address node, infotype *jalur, int jumlahItem, int threshold);

/* Mendapatkan string nama barang berdasarkan angka representasinya */
void AmbilNamaBarang(infotype idBarang, char* namaBarang);

/* Modul untuk mengurutkan array */
void UrutkanDaftar(infotype *daftar, int n);

/* Sub-modul untuk mengolah string transaksi (dari file atau manual) dan memasukannya ke Tries */
void ProsesStringTransaksi(Tree root, char *teksInput, int *hitungTransaksi);
/****************************************************/

#endif