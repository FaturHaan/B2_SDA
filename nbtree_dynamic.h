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

//Traversal
void PreOrder(Tree T);
void InOrder(Tree T);
void PostOrder(Tree T);
void LevelOrder(Tree T);

//Search
int Search(Tree T, infotype X);

//Dealokasi
void DeAlokasi(Tree *T);

void InisialisasiTrie(Tree *root);

address CariAtauBuatChild(address parent, infotype idBarang);

void MasukkanTransaksiKeTrie(address node, infotype *daftarBarang, int jumlahBarang);

void CetakItemsetSering(address node, infotype *jalur, int jumlahItem, int threshold);

void AmbilNamaBarang(infotype idBarang, char* namaBarang);

void UrutkanDaftar(infotype *daftar, int n);

void ProsesStringTransaksi(Tree root, char *teksInput, int *hitungTransaksi);

#endif