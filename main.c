#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistemresto.h"

void MainMenuDisplay() {
    printf("======= APLIKASI RESTORAN ======\n");
    printf("1. Tambah Reservasi\n");
    printf("2. Proses Kedatangan\n");
    printf("3. Proses Pengantaran Makanan\n");
    printf("4. Cetak Bills\n");
    printf("5. Tinjau Ulang Antrean\n");
    printf("6. Manage Menu\n");
    printf("7. Keluar\n");
    printf("Pilihan: ");
}

int main() {
    int opt;

    // inisialisasi semua struktur data

    treeAddress menuroot;
    menuroot = File_LoadTree("menu.txt");
    if (menuroot == Nil) {
        printf("Gagal memindai file menu ke tree.\n");
    }

    PriorityQueue antreanReservasi;
    CreatePriorityQueue(&antreanReservasi);

    adr_pesanan listOrderan = Nil;

    adr_stack stackAntar;
    CreateStack(&stackAntar);

    Meja tables[MAX_MEJA];
    InitMeja(tables);

    do {
        MainMenuDisplay();
        scanf("%d", &opt);
        getchar();

        switch (opt) {
            case 1:
            	printf("Tambah Reservasi\n");
                inputReservasi(menuroot, &antreanReservasi, tables, &listOrderan);
                break;
            case 2:
            	printf("Proses Kedatangan\n");
                prosesKedatangan(&antreanReservasi, &stackAntar, tables);
                break;
            case 3:
            	printf("Proses Pengantaran Makanan\n");
            	prosesPengantaran(tables);
                break;
            case 4:
            	printf("Cetak Bills\n");
                break;
            case 5: 
            	printAllQueue(antreanReservasi);
                break;
            case 6:
                ManageMenu(menuroot);
                break;
            case 7:
                printf("Kerja bagus. Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid, coba lagi.\n");
        }

    } while (opt != 6);
    return 0;
}