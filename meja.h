#ifndef MEJA_H
#define MEJA_H

#include "boolean.h"
#include "stack.h"

typedef struct {
    int nomor;
    int kapasitas;
    boolean isTersedia;
    char jam_kosong[6];
    adr_stack stackPesanan;
    
} Meja;

#define MAX_MEJA 20
#define DURASI_RESERVASI 2 // Durasi dalam jam

void InitMeja(Meja meja[]);
void PrintMeja(Meja meja[]);
boolean CariMejaTunggal(Meja meja[], int total_orang, int *indeks);
boolean CariGabunganMeja(Meja meja[], int total_orang, int indeks_meja[], int *jumlah_meja);
void TambahPesananKeMeja(Meja *meja, Pesanan pesanan);
boolean TambahPesananKeGabunganMeja(Meja meja[], int indeks_meja[], int *jumlah_meja, Pesanan pesanan);

#endif