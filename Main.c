#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nbtree_dynamic.h"

int main() {
    Tree root;
    int pilihan;
    int totalTransaksi = 0;
    int nomorTransaksi;
    char inputBarang[256];
    int jumlahTransaksi;
    int totalSebelum;
    
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
        
    } 
    else {
        printf("Pilihan tidak tersedia. Program berhenti.\n");
        return 1;
    }
    
    return 0;
}