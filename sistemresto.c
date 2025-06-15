#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistemresto.h"

void toLowercase (char *hasil, const char *input) {
    int i = 0;
    while (input[i]) {
        hasil[i] = tolower(input[i]);
        i++;
    }
    hasil[i] = '\0';
}

boolean cekIsiKata (const char* kalimat, const char *kataIsi) {
    char lowerKalimat[100], lowerIsi[100];
    toLowercase(lowerKalimat, kalimat);
    toLowercase(lowerIsi, kataIsi);
    return strstr(lowerKalimat, lowerIsi) != Nil;
}

void findMatch (treeAddress node, const char* input, treeAddress hasil[], int *count, int maxCount) {
    if (node == Nil || *count >= maxCount) return;
    if (node->isItem && cekIsiKata(node->name, input)) {
        hasil[*count] = node;
        (*count)++;
    }
    findMatch (node->fs, input, hasil, count, maxCount);
    findMatch (node->fs, input, hasil, count, maxCount);
}

treeAddress inputItem (treeAddress root) {
    char input[50];
    printf("\nMasukkan nama menu (sebagian atau lengkap): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    treeAddress match[10];
    int matchCount = 0;
    findMatch(root, input, match, &matchCount, 10);
    if (matchCount == 0) {
        printf("Menu tidak ditemukan.\n");
        return Nil;
    } else if (matchCount == 1) {
        return match[0];
    } else {
        printf("Ditemukan beberapa menu:\n");
        for (int i = 0; i < matchCount; i++) {
            printf("%d. %s (Rp%.2f)\n", i + 1, match[i]->name, match[i]->price);
        }
        int choice;
        printf("Pilih nomor menu: ");
        scanf("%d", &choice);
        getchar();
        if (choice < 1 || choice > matchCount) {
            printf("Pilihan tidak valid.\n");
            return Nil;
        }
        return match[choice - 1];
    }
}

void PushCategory (adr_stack *orders, treeAddress menuItem, int qty) {
    treeAddress parent = menuItem->pr;
    while (parent != Nil && !parent->isItem) {
        parent = parent->pr;
    }
    if (parent == Nil || menuItem == Nil) {
        printf("Gagal mengkategorikan item %s.\n", menuItem ? menuItem->name : "Nil");
        return;
    }
    const char* foundKategori = parent->name;
    adr_stack current = *orders;
    while (current != Nil && strcmp(current->kategoriNama, foundKategori) != 0) {
        current = current->next;
    }
    if (current == Nil) {
        Kategori newKategori;
        CreateKategori(&newKategori);
        pushMenu(&newKategori, (Menu){.qty = qty});
        strcpy(newKategori.top->info.namaMenu, menuItem->name);
        push(orders, newKategori, foundKategori);
    } else {
        Menu m;
        strcpy(m.namaMenu, menuItem->name);
        m.qty = qty;
        pushMenu(&current->data, m);
    }
    printf("✓ %s (%d) ditambahkan ke pesanan.\n", menuItem->name, qty);
}

void getOrder (treeAddress root, adr_pesanan *listPesanan) {
    if (root == Nil) {
        printf("Menu kosong.\n");
        return;
    }
    int tambah = 1;
    while (tambah) {
        PrintTree (root, 0);
        treeAddress selectedItem = inputItem(root);
        if (selectedItem == Nil) continue;

        int qty;
        printf("Masukkan jumlah: ");
        scanf("%d", &qty);
        getchar();
        if (qty <= 0) {
            printf("Jumlah tidak valid.\n");
            continue;
        }
        Pesanan p;
        strcpy(p.namaMenu, selectedItem->name);
        strcpy(p.kategori, selectedItem->pr->name); 
        p.jumlah = qty;
        p.hargaSatuan = (int) selectedItem->price;
        addPesanan(listPesanan, p);
        printf("✓ %s (%d) ditambahkan ke daftar pesanan.\n", p.namaMenu, p.jumlah);
        printf("Tambah menu lagi? (1 = ya, 0 = tidak): ");
        scanf("%d", &tambah);
        getchar();
    }
    printf("\nRekap Pesanan:\n");
    printPesananList(*listPesanan);
}

void inputReservasi (treeAddress root, PriorityQueue *Q, Meja meja[]) {
    Pelanggan p;
    char nomorHp[20];
    int indeksTunggal = -1, jumlahGabungan = 0, indeksGabungan[MAX_MEJA];

    // input info pelanggan
    printf("=== Input Reservasi ===\n");
    printf("Nama pelanggan: ");
    fgets(p.namaPelanggan, sizeof(p.namaPelanggan), stdin);
    p.namaPelanggan[strcspn(p.namaPelanggan, "\n")] = '\0';
    printf("No. Telepon: ");
    fgets(nomorHp, sizeof(nomorHp), stdin);
    for (int i = 0; i < 15 && nomorHp[i] != '\0'; i++) {
        if (isdigit(nomorHp[i])) {
            p.noTelp[i] = nomorHp[i] - '0';
        } else {
            p.noTelp[i] = 0;
        }
    }
    printf("Jumlah orang: ");
    scanf("%d", &p.total_orang);
    getchar();
    printf("Jam kedatangan (HH:MM): ");
    fgets(p.jam_kedatangan, sizeof(p.jam_kedatangan), stdin);
    p.jam_kedatangan[strcspn(p.jam_kedatangan, "\n")] = '\0';

    // input daftar pesanan
    p.listPesanan = Nil;
    printf("=== Input Pesanan ===\n");
    getOrder(root, &p.listPesanan);

    // cek dan assign meja
    printf("Mencari meja untuk %d orang...\n", p.total_orang);
    if (CariMejaTunggal(meja, p.total_orang, &indeksTunggal)) {
        printf("✓ Meja tunggal #%d dialokasikan.\n", meja[indeksTunggal].nomor);
        meja[indeksTunggal].isTersedia = false;
    } else if (CariGabunganMeja(meja, p.total_orang, indeksGabungan, &jumlahGabungan)) {
        printf("✓ Gabungan meja dialokasikan: ");
        for (int i = 0; i < jumlahGabungan; i++) {
            printf("#%d ", meja[indeksGabungan[i]].nomor);
            meja[indeksGabungan[i]].isTersedia = false;
        }
        printf("\n");
    } else {
        printf("✗ Tidak tersedia meja untuk %d orang saat ini.\n", p.total_orang);
        return;
    }
    enqueue(Q, p);
    printf("✓ Reservasi berhasil masuk antrian.\n");
}

void masukkanListKeStack (adr_pesanan listP, adr_stack *stackP) {
    while (listP != Nil) {
        Menu m;
        strcpy(m.namaMenu, listP->data.namaMenu);
        m.qty = listP->data.jumlah;
        const char *k = listP->data.kategori;
        adr_stack current = *stackP;
        while (current != Nil && strcmp(current->kategoriNama, k) != 0) {
            current= current->next;
        }
        if (current == Nil) {
            Kategori newKategori;
            CreateKategori(&newKategori);
            pushMenu(&newKategori, m);
            push(stackP, newKategori, k);
        } else {
            pushMenu(&current->data, m);
        }
        listP = listP->next;
    }
}