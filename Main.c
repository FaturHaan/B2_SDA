#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nbtree_dynamic.h"

int main() {
    Tree root;              // Root dummy untuk struktur trie
    int pilihan;            // Menyimpan pilihan metode input
    int totalTransaksi = 0; // Menghitung jumlah transaksi yang sukses diproses
    int nomorTransaksi;     // Perulangan input transaksi manual
    char inputBarang[256];  // Buffer untuk menampung string input transaksi
    int jumlahTransaksi;    // Menyimpan jumlah transaksi yang ingin dimasukkan user
    char namaFile[100];     // Buffer untuk menampung nama file txt dari user
    int totalSebelum;       // Penanda jumlah transaksi sebelum diproses untuk validasi
    int threshold;          // Batas minimum support
    infotype jalur[20];     // Array bantu untuk mencatat jalur item yang sedang ditelusuri saat traversal
    
    InisialisasiTrie(&root);
    
    printf("==========================================\n");
    printf("  MARKET BASKET ANALYSIS PROGRAM DINAMIS  \n");
    printf("==========================================\n");
    printf("Pilih metode input transaksi:\n");
    printf("1. Input Manual oleh User\n");
    printf("2. Baca dari File TXT\n");
    printf("Pilihan (1/2): ");
    
    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid!\n");
        return 1;
    }
    while (getchar() != '\n');
    
    if (pilihan == 1) {
        printf("\nMasukkan jumlah transaksi yang ingin diinput: ");
        scanf("%d", &jumlahTransaksi);
        while (getchar() != '\n');
        
        printf("\n=== Daftar Item ===\n");
        printf("1: Rinso\n2: Susu\n3: Beras\n4: Gula\n");
        printf("===================\n");
        printf("Format pengisian : Masukkan angka item dipisahkan dengan spasi (Contoh: 1 3 4)\n");
        printf("Tekan ENTER setelah selesai mengetik satu transaksi.\n\n");
        
        for (nomorTransaksi = 1; nomorTransaksi <= jumlahTransaksi; nomorTransaksi++) {
            printf("Input Transaksi T%d : ", nomorTransaksi);

            if (fgets(inputBarang, sizeof(inputBarang), stdin) != NULL) {
                totalSebelum = totalTransaksi;
                ProsesStringTransaksi(root, inputBarang, &totalTransaksi);
                
                if (totalTransaksi == totalSebelum) {
                    printf("Transaksi kosong atau format salah. Silakan ulangi.\n");
                    nomorTransaksi--; 
                }
            }
        }
    }
    else if (pilihan == 2) {
        printf("\nMasukkan nama file (beserta ekstensinya, contoh: transaksi.txt): ");
        if (fgets(namaFile, sizeof(namaFile), stdin) != NULL) { 
            namaFile[strcspn(namaFile, "\n")] = 0;
            FILE *fp = fopen(namaFile, "r");
            if (fp == NULL) {
                printf("Gagal membuka file '%s'. Pastikan file berada di folder yang sama dengan program.\n", namaFile);
                return 1;
            }
            
            printf("\nMembaca isi file...\n");
            while (fgets(inputBarang, sizeof(inputBarang), fp) != NULL) {
                ProsesStringTransaksi(root, inputBarang, &totalTransaksi);
            }
            fclose(fp);
        }
    } 
    else {
        printf("Pilihan tidak tersedia. Program berhenti.\n");
        return 1;
    }
    
    if (totalTransaksi == 0) {
        printf("\nTidak ada satupun transaksi yang berhasil diproses!\n");
        return 1;
    }
    
    printf("\nTotal %d transaksi sukses diproses ke dalam Trie!\n", totalTransaksi);
    printf("\nMasukkan nilai Threshold (Minimum Support): ");
    scanf("%d", &threshold);
    printf("\n==========================================\n");
    printf("                Pasangan Barang           \n");
    printf("==========================================\n");
    printf("Menampilkan itemset (>= 2 item) dengan support >= %d:\n\n", threshold);
    
    CetakItemsetSering(root, jalur, 0, threshold);
    printf("\n==========================================\n");
    printf("Selesai.\n");
    
    DeAlokasi(&root);
    
    return 0;
}