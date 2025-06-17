#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "struk.h"
#include "pesanan.h"


void buatFolderStruk() {
    struct stat st = {0};
    if (stat(FOLDER_STRUK, &st) == -1) {
        mkdir(FOLDER_STRUK);
    }
}

void buatStruk(Pelanggan p){
    buatFolderStruk();

    char filename[100];
    snprintf(filename, sizeof(filename), "%s/%s.txt", FOLDER_STRUK, p.namaPelanggan);

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuat struk untuk %s\n", p.namaPelanggan);
        return;
    }

    // Hitung jam selesai (HH:MM + DURASI_RESERVASI)
    int jam, menit;
    sscanf(p.jam_kedatangan, "%d:%d", &jam, &menit);
    jam = (jam + DURASI_RESERVASI) % 24;
    char jam_selesai[6];
    snprintf(jam_selesai, sizeof(jam_selesai), "%02d:%02d", jam, menit);

    //Header struk
    fprintf(file, "=== STRUK RESTO ===\n");
    fprintf(file, "Nama Pelanggan: %s\n", p.namaPelanggan);
    fprintf(file, "No. Telepon: ");
    for (int i = 0; i < 15 && p.noTelp[i] != 0; i++) {
        fprintf(file, "%d", p.noTelp[i]);
    }
    fprintf(file, "\nJam Reservasi: %s\n", p.jam_kedatangan);
    fprintf(file, "Selesai: %s\n", jam_selesai);
    fprintf(file, "------------------\n");
    fprintf(file, "Pesanan:\n");
    adr_pesanan current = p.listPesanan;
    while (current != NULL) {
        fprintf(file, "- %s \t(%d x Rp%d) = Rp%d\n",
                current->data.namaMenu,
                current->data.jumlah,
                current->data.hargaSatuan,
                current->data.jumlah * current->data.hargaSatuan);
        current = current->next;
    }

    // Tulis total harga
    fprintf(file, "------------------\n");
    fprintf(file, "TOTAL: Rp%d\n", countTotalHarga(p.listPesanan));
    fclose(file);

    printf("Struk untuk %s berhasil dibuat di %s\n", p.namaPelanggan, filename);

}

//buat cari nama pelanggan di queue
Pelanggan* cariPelangganByNama(PriorityQueue *Q, const char *nama) {
    address current = Q->front;
    while (current != NULL) {
        if (strcmp(current->dataPelanggan.namaPelanggan, nama) == 0) {
            return &(current->dataPelanggan);
        }
        current = current->next;
    }
    return NULL;
}