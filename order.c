#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "order.h"

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
    return strstr(lowerKalimat, lowerIsi) != NULL;
}

void findMatch (treeAddress node, const char* input, treeAddress hasil[], int *count, int maxCount) {
    if (node == NULL || *count >= maxCount) return;
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
        return NULL;
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
            return NULL;
        }
        return match[choice - 1];
    }
}

void PushCategory (adr_stack *orders, treeAddress menuItem, int qty) {
    treeAddress parent = menuItem->pr;
    while (parent != NULL && !parent->isItem) {
        parent = parent->pr;
    }
    if (parent == NULL || menuItem == NULL) {
        printf("Gagal mengkategorikan item %s.\n", menuItem ? menuItem->name : "NULL");
        return;
    }
    const char* foundKategori = parent->name;
    adr_stack current = *orders;
    while (current != NULL && strcmp(current->kategoriNama, foundKategori) != 0) {
        current = current->next;
    }
    if (current == NULL) {
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

void getOrder (treeAddress root, adr_stack orders) {
    if (root == NULL) {
        printf("Menu kosong.\n");
        return;
    }
    int tambah = 1;
    while (tambah) {
        PrintTree (root, 0);
        treeAddress selectedItem = inputItem(root);
        if (selectedItem == NULL) continue;

        int qty;
        printf("Masukkan jumlah: ");
        scanf("%d", &qty);
        getchar();
        if (qty <= 0) {
            printf("Jumlah tidak valid.\n");
            continue;
        }
        PushCategory(&orders, selectedItem, qty);
        printf("Tambah menu lagi? (1 = ya, 0 = tidak): ");
        scanf("%d", &tambah);
        getchar();
    }
    printf("\nRekap Pesanan:\n");
    printAllPesanan(orders);
}

