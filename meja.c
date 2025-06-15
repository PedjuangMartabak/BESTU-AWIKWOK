#include <stdio.h>
#include <string.h>
#include "meja.h"

void InitMeja(Meja (*meja)[MAX_MEJA]) {
    int kapasitas_pattern[] = {2, 4, 6, 8};
    for (int i = 0; i < MAX_MEJA; i++) {
        (*meja)[i].nomor = i + 1;
        (*meja)[i].kapasitas = kapasitas_pattern[i % 4];
        (*meja)[i].isTersedia = true;
        strcpy((*meja)[i].jam_kosong, "00:00");
        (*meja)[i].stackPesanan = NULL;
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
    
    // Prioritaskan meja besar terlebih dahulu
    for (int i = 0; i < MAX_MEJA; i++) {
        for (int j = 0; j < MAX_MEJA; j++) {
            if (meja[j].isTersedia && meja[j].kapasitas == (8 - i*2)) {
                indeks_meja[(*jumlah_meja)++] = j;
                total_kapasitas += meja[j].kapasitas;
                if (total_kapasitas >= total_orang) {
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

void TambahPesananKeMeja(Meja *meja, Pesanan pesanan) {
    if (!meja->isTersedia) {
        adr_stack current = meja->stackPesanan;
        const char* kategori = pesanan.kategori;  // Misal: "Appetizer"
        while (current != NULL && strcmp(current->kategoriNama, kategori) != 0) {
            current = current->next;
        }
        
        //Error Handle Buat stack baru jika kategori belum ada
        if (current == NULL) {
            Kategori newKategori;
            CreateKategori(&newKategori);
            pushMenu(&newKategori, (Menu){.qty = pesanan.jumlah});
            strcpy(newKategori.top->info.namaMenu, pesanan.namaMenu);
            push(&meja->stackPesanan, newKategori, kategori);
        } else {
            Menu m;
            strcpy(m.namaMenu, pesanan.namaMenu);
            m.qty = pesanan.jumlah;
            pushMenu(&current->data, m);
        }
    }
}


void TambahPesananKeGabunganMeja(Meja meja[], int indeks_meja[], int jumlah_meja, Pesanan pesanan) {
    for (int i = 0; i < jumlah_meja; i++) {
        TambahPesananKeMeja(&meja[indeks_meja[i]], pesanan);
    }
}
