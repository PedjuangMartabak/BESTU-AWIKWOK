#ifndef STRUK_H
#define STRUK_H

#include "queue.h"
#include <stdbool.h>

#define FOLDER_STRUK "struk"
#define DURASI_RESERVASI 2

void buatStruk(Pelanggan p, PriorityQueue *Q);
Pelanggan* cariPelangganByNama(PriorityQueue *Q, const char *nama);

#endif