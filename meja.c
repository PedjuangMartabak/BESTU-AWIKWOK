#include <stdio.h>
#include <string.h>
#include "meja.h"

void InitMeja(Meja meja[]) {
    int kapasitas_pattern[] = {2, 4, 6, 8};
    for (int i = 0; i < MAX_MEJA; i++) {
        meja[i].nomor = i + 1;
        meja[i].kapasitas = kapasitas_pattern[i % 4]; // Pengulangan pola
        meja[i].isTersedia = true;
        strcpy(meja[i].jam_kosong, "00:00");
        meja[i].stackPesanan = NULL; // Stack pesanan kosong
    }
}

void PrintMeja(Meja meja[]) {
    printf("\n=== Daftar Meja ===\n");
    for (int i = 0; i < MAX_MEJA; i++) {
        printf("Meja %2d: Kapasitas %d | Status: %s",
               meja[i].nomor,
               meja[i].kapasitas,
               meja[i].isTersedia ? "Tersedia" : "Terisi");
        
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
    for (int kapasitas = 8; kapasitas >= 2; kapasitas -= 2) {
        for (int i = 0; i < MAX_MEJA && total_kapasitas < total_orang; i++) {
            if (meja[i].isTersedia && meja[i].kapasitas == kapasitas) {
                indeks_meja[(*jumlah_meja)++] = i;
                total_kapasitas += meja[i].kapasitas;
                if (total_kapasitas >= total_orang) {
                    return true;
                }
            }
        }
    }
    return false;
}

void TambahPesananKeMeja(Meja *meja, Pesanan pesanan) {
	if (meja == NULL || pesanan.kategori == NULL) {
        printf("Error: Meja atau pesanan tidak valid.\n");
        return;
    }
    
	if (meja == NULL) {
        printf("Error: Meja tidak valid.\n");
        return;
    }
	
	if (meja->isTersedia) {
        printf("Error: Meja %d belum dipesan. Pesanan ditolak.\n", meja->nomor);
        return;
    }

    adr_stack current = meja->stackPesanan;
    const char* kategori = pesanan.kategori;
    
    // Cari stack kategori yang sesuai
    while (current != NULL && strcmp(current->kategoriNama, kategori) != 0) {
        current = current->next;
	}
	
	// Jika kategori belum ada, buat stack baru
    if (current == NULL) {
        Kategori newKategori;
        CreateKategori(&newKategori);
        Menu m;
        strcpy(m.namaMenu, pesanan.namaMenu);
        m.qty = pesanan.jumlah;
        pushMenu(&newKategori, m);

        // Push kategori baru ke stack meja
        adr_stack newStackNode = (adr_stack)malloc(sizeof(NodeStack));
        if (newStackNode == NULL) {
            printf("Error: Alokasi memori gagal!\n");
            return;
        }
        newStackNode->data = newKategori;
        strcpy(newStackNode->kategoriNama, kategori);
        newStackNode->next = meja->stackPesanan;
        meja->stackPesanan = newStackNode;
    } else {
        // Tambahkan menu ke kategori yang sudah ada
        Menu m;
        strcpy(m.namaMenu, pesanan.namaMenu);
        m.qty = pesanan.jumlah;
        pushMenu(&current->data, m);
    }
}


boolean TambahPesananKeGabunganMeja(Meja meja[], int indeks_meja[], int *jumlah_meja, Pesanan pesanan) {
    *jumlah_meja = 0;
    int total_kapasitas = 0;
    int total_orang = pesanan.jumlah;  // Ambil jumlah orang dari pesanan

    // Prioritaskan meja besar terlebih dahulu
    for (int kapasitas = 8; kapasitas >= 2; kapasitas -= 2) {
        for (int i = 0; i < MAX_MEJA && total_kapasitas < total_orang; i++) {
            if (meja[i].isTersedia && meja[i].kapasitas == kapasitas) {
                indeks_meja[(*jumlah_meja)++] = i;
                total_kapasitas += meja[i].kapasitas;
            }
        }
    }
    return (total_kapasitas >= total_orang);
}

