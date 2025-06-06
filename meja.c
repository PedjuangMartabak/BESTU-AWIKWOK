#include <stdio.h>
#include <string.h>
#include "meja.h"

void InitMeja(Meja meja[]) {
    for (int i = 0; i < MAX_MEJA; i++) {
        meja[i].nomor = i + 1;
        // Atur kapasitas meja: 2, 4, atau 6 kursi
        meja[i].kapasitas = 2 + (i % 3) * 2;
        meja[i].isTersedia = true;
        strcpy(meja[i].jam_kosong, "00:00");
    }
}

void PrintMeja(Meja meja[]) {
    printf("\n=== Daftar Meja ===\n");
    for (int i = 0; i < MAX_MEJA; i++) {
        printf("Meja %2d: Kapasitas %d, Status: %s", 
               meja[i].nomor, meja[i].kapasitas,
               meja[i].isTersedia ? "Tersedia" : "Dipesan");
        
        if (!meja[i].isTersedia) {
            printf(" (Sampai jam %s)", meja[i].jam_kosong);
        }
        printf("\n");
    }
}

boolean CariMejaTunggal(Meja meja[], int total_orang, int *indeks) {
    for (int i = 0; i < MAX_MEJA; i++) {
        if (meja[i].isTersedia && meja[i].kapasitas >= total_orang) {
            *indeks = i;
            return true;
        }
    }
    return false;
}

boolean CariGabunganMeja(Meja meja[], int total_orang, int indeks_meja[], int *jumlah_meja) {
    int total_kapasitas = 0;
    *jumlah_meja = 0;
    
    for (int i = 0; i < MAX_MEJA && total_kapasitas < total_orang; i++) {
        if (meja[i].isTersedia) {
            indeks_meja[(*jumlah_meja)++] = i;
            total_kapasitas += meja[i].kapasitas;
        }
    }
    
    return (total_kapasitas >= total_orang);
}