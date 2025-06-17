#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistemresto.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void toLowercase (char *hasil, const char *input) {
	if (input == NULL || hasil == NULL) return;
    strncpy(hasil, input, 49);  // Batasi panjang maksimal 49 karakter
    hasil[49] = '\0';           // Pastikan null-terminated
    int i = 0;
    while (input[i]) {
        hasil[i] = tolower(input[i]);
        i++;
    }
    hasil[i] = '\0';
}

boolean cekIsiKata (const char* kalimat, const char *kataIsi) {
	if (kalimat == NULL || kataIsi == NULL || strlen(kalimat) == 0 || strlen(kataIsi) == 0) {
        return false;
    }
    
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
    findMatch (node->nb, input, hasil, count, maxCount);
}

treeAddress inputItem (treeAddress root) {
	
	if (root == NULL) {
        printf("Menu kosong atau tidak ditemukan.\n");
        return NULL;
    }
    
    char input[50];
    printf("\nMasukkan nama menu (sebagian atau lengkap): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Hapus newline

    // Jika input kosong, kembalikan NULL
    if (strlen(input) == 0) {
        printf("Input tidak valid.\n");
        return NULL;
    }

    treeAddress match[10];
    int matchCount = 0;
    findMatch(root, input, match, &matchCount, 10);
    
    if (matchCount == 0) {
        printf("Menu tidak ditemukan.\n");
        return NULL;
    } else if (matchCount == 1) {
        printf("Menu ditemukan: %s (Rp%.2f)\n", match[0]->name, match[0]->price);
        return match[0];
    } else {
        printf("Ditemukan beberapa menu:\n");
        for (int i = 0; i < matchCount; i++) {
            printf("%d. %s (Rp%.2f)\n", i + 1, match[i]->name, match[i]->price);
        }
        
        int choice;
        printf("Pilih nomor menu (1-%d): ", matchCount);
        if (scanf("%d", &choice) != 1) {  // Cek jika input bukan angka
            clearInputBuffer();
            printf("Input tidak valid. Harap masukkan angka.\n");
            return NULL;
        }
        clearInputBuffer();
        
        if (choice < 1 || choice > matchCount) {
            printf("Pilihan tidak valid.\n");
            return NULL;
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
    printf("%s (%d) ditambahkan ke pesanan.\n", menuItem->name, qty);
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
        clearInputBuffer();
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
        printf("%s (%d) ditambahkan ke daftar pesanan.\n", p.namaMenu, p.jumlah);
        printf("Tambah menu lagi? (1 = ya, 0 = tidak): ");
        scanf("%d", &tambah);
        clearInputBuffer();
    }
    printf("\nRekap Pesanan:\n");
    printPesananList(*listPesanan);
}

void inputReservasi (treeAddress root, PriorityQueue *Q, Meja meja[], adr_pesanan *ListP) {
    Pelanggan p;
    char nomorHp[20];
    int indeksTunggal = -1, jumlahGabungan = 0, indeksGabungan[MAX_MEJA];

    // input info pelanggan
    printf("=== Input Reservasi ===\n");
    clearInputBuffer();
    printf("Nama pelanggan: ");
    fgets(p.namaPelanggan, sizeof(p.namaPelanggan), stdin);
    p.namaPelanggan[strcspn(p.namaPelanggan, "\n")] = '\0';
    
    // Validasi nomor telepon
    int valid = 0;
    while (!valid) {
        printf("No. Telepon (minimal 12 digit angka): ");
        fgets(nomorHp, sizeof(nomorHp), stdin);
        nomorHp[strcspn(nomorHp, "\n")] = '\0';

        // Cek panjang minimal 12 digit
        if (strlen(nomorHp) < 12) {
            printf("Nomor telepon harus minimal 12 digit.\n");
            continue;
        }

        // Cek semua karakter adalah angka
        valid = 1;
        for (int i = 0; i < strlen(nomorHp); i++) {
            if (!isdigit(nomorHp[i])) {
                valid = 0;
                printf("Nomor telepon hanya boleh berisi angka.\n");
                break;
            }
        }

        if (valid) {
            // Konversi ke array integer
            for (int i = 0; i < 15 && nomorHp[i] != '\0'; i++) {
                p.noTelp[i] = nomorHp[i] - '0';
            }
        }
    }
    
    printf("Jumlah orang: ");
    scanf("%d", &p.total_orang);
    clearInputBuffer();
    printf("Jam kedatangan (HH:MM): ");
    fgets(p.jam_kedatangan, sizeof(p.jam_kedatangan), stdin);
    p.jam_kedatangan[strcspn(p.jam_kedatangan, "\n")] = '\0';

    // input daftar pesanan
    p.listPesanan = Nil;
    printf("=== Input Pesanan ===\n");
    getOrder(root, &p.listPesanan);

    // cek dan assign meja
    printf("Mencari meja untuk %d orang...\n", p.total_orang);
    int jam, menit;
    sscanf(p.jam_kedatangan, "%d:%d", &jam, &menit);
    jam = (jam + DURASI_RESERVASI) % 24;
    char jamKosongStr[6];
    sprintf(jamKosongStr, "%02d:%02d", jam, menit);
    p.jmlMeja = 0;
    if (CariMejaTunggal(meja, p.total_orang, &indeksTunggal)) {
    	printf("Meja tunggal #%d dialokasikan.\n", meja[indeksTunggal].nomor);
    	meja[indeksTunggal].isTersedia = false;
    	strcpy(meja[indeksTunggal].jam_kosong, jamKosongStr);
    	p.no_meja[0] = meja[indeksTunggal].nomor;
    	p.jmlMeja = 1;
	} else if (CariGabunganMeja(meja, p.total_orang, indeksGabungan, &jumlahGabungan)) {
		printf("Gabungan meja dialokasikan: ");
		for (int i = 0; i < jumlahGabungan; i++) {
			printf("#%d ", meja[indeksGabungan[i]].nomor);
            meja[indeksGabungan[i]].isTersedia = false;
            strcpy(meja[indeksGabungan[i]].jam_kosong, jamKosongStr);
            p.no_meja[i] = meja[indeksGabungan[i]].nomor;
		}
		printf("\n");
		p.jmlMeja = jumlahGabungan;
	} else {
		printf("Tidak tersedia meja untuk %d orang saat ini.\n", p.total_orang);
        return;
	}
    
    enqueue(Q, p);
    printf("Reservasi berhasil masuk antrian.\n");
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

void printAllQueue(PriorityQueue Q) {
	
	address current = Q.front;
	int i = 1;
	printf("\n=== Daftar Semua Antrean ===\n");
	
	if (current == NULL) {
        printf("Belum ada antrean.\n");
        return;
    }
	while (current != Nil) {
		Pelanggan p = current->dataPelanggan;
		printf("%d. %s (Jam: %s, %d orang)\n", i++, p.namaPelanggan, p.jam_kedatangan, p.total_orang);
		printf("   Pesanan:\n");
		printPesananList(p.listPesanan);
		printf("\n");
		current = current->next;
	}
	if (i == 1) {
        printf("Antrean kosong.\n");
    }
}

Kategori clonePesananStack (Kategori original) {
	Kategori temp;
	CreateKategori(&temp);
	Kategori reversed;
	CreateKategori(&reversed);
	adr_menu current = original.top;
	while (current != Nil) {
		pushMenu(&reversed, current->info);
		current = current->next;
	}
	current = reversed.top;
	while (current != Nil) {
		pushMenu(&temp, current->info);
		current = current->next;
	}
	return temp;
}

adr_stack cloneStack (adr_stack src) {
	adr_stack head = Nil, tail = Nil;
	
	adr_stack reversed = Nil;
    while (src != Nil) {
        Kategori copied = clonePesananStack(src->data);
        adr_stack newNode = (adr_stack)malloc(sizeof(NodeStack));
        newNode->data = copied;
        strcpy(newNode->kategoriNama, src->kategoriNama);
        newNode->next = reversed;
        reversed = newNode;
        src = src->next;
    }
    while (reversed != Nil) {
        adr_stack next = reversed->next;
        adr_stack newNode = (adr_stack)malloc(sizeof(NodeStack));
        newNode->data = clonePesananStack(reversed->data);
        strcpy(newNode->kategoriNama, reversed->kategoriNama);
        newNode->next = head;
        head = newNode;
        free(reversed);
        reversed = next;
    }
	return head;
}

void prosesKedatangan(PriorityQueue *Q, adr_stack *stackP, Meja meja[]) {
	printQueue(*Q);
	if (Q->front == Nil) return;
	int choice;
	clearInputBuffer();
	printf("Pilih nomor pelanggan yang datang: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    address prev = Nil;
    address	current = Q->front;
    int i = 1;
    while (current != Nil && i < choice) {
    	prev = current;
    	current = current->next;
    	i++;
	}
	if (current == Nil) {
		printf("Nomor tidak ditemukan.\n");
        return;
	}
	Pelanggan selected = current->dataPelanggan;
	masukkanListKeStack(selected.listPesanan, stackP);
	printf("\nDEBUG: Isi stackP setelah konversi dari list, sebelum clone ke meja:\n");
	printAllPesanan(*stackP);
	printf("Pesanan atas nama '%s' telah masuk daftar antar.\n", selected.namaPelanggan);
	for (int i = 0; i < selected.jmlMeja; i++) {
    	int idx = selected.no_meja[i] - 1;
    	if (!meja[idx].isTersedia && meja[idx].stackPesanan == Nil) {
        meja[idx].stackPesanan = cloneStack(*stackP);
        printf("DEBUG: Stack berhasil disalin ke meja %d\n", meja[idx].nomor);
    	}
	}
	
	for (int i = 0; i < selected.jmlMeja; i++) {
        int idx = selected.no_meja[i] - 1;
        if (!meja[idx].isTersedia && meja[idx].stackPesanan == NULL) {
            adr_stack clonedStack = cloneStack(*stackP);
            if (clonedStack != NULL) {
                meja[idx].stackPesanan = clonedStack;
            } else {
                printf("Gagal mengalokasikan stack untuk meja %d\n", meja[idx].nomor);
            }
        }
    }
}

void printSemuaStackMeja(Meja meja[], PriorityQueue Q) {
	printf("DEBUG: Status meja sebelum print stack:\n");
	for (int i = 0; i < MAX_MEJA; i++) {
	    printf("Meja %d - tersedia: %d, jam_kosong: %s, stack NULL: %d\n",
	        meja[i].nomor,
	        meja[i].isTersedia,
	        meja[i].jam_kosong,
	        meja[i].stackPesanan == Nil);
	}
    printf("\nPesanan Per Meja:\n");
    for (int i = 0; i < MAX_MEJA; i++) {
        if (!meja[i].isTersedia && meja[i].stackPesanan != NULL) {
            printf("\nMeja #%d:\n", meja[i].nomor);
            // Cari info pelanggan terkait meja ini agar tahu apakah gabungan
            address current = Q.front;
            Pelanggan *relatedPelanggan = NULL;

            while (current != Nil) {
                for (int j = 0; j < current->dataPelanggan.jmlMeja; j++) {
                    if (current->dataPelanggan.no_meja[j] == meja[i].nomor) {
                        relatedPelanggan = &current->dataPelanggan;
                        break;
                    }
                }
                if (relatedPelanggan != NULL) break;
                current = current->next;
            }

            // Tampilkan daftar gabungan meja jika ada
            if (relatedPelanggan != NULL && relatedPelanggan->jmlMeja > 1) {
                printf("Gabungan meja: ");
                for (int j = 0; j < relatedPelanggan->jmlMeja; j++) {
                    printf("#%d ", relatedPelanggan->no_meja[j]);
                }
                printf("\n");
                printf("Atas nama: %s\n", relatedPelanggan->namaPelanggan);
            }
            printAllPesanan(meja[i].stackPesanan);
        }
    }
}

void prosesPengantaran(Meja meja[], PriorityQueue Q) {
    if (meja == NULL || Q.front == NULL) {
        printf("Error: Meja atau antrean tidak valid.\n");
        return;
    }
    
    int jumlahMeja, noMeja;
    int yes;
    char slctKategori[20];
    printSemuaStackMeja(meja, Q);
    
    printf("\nLakukan pengantaran? (Ya = 1, tidak = 0): ");
    scanf("%d", &yes);
    clearInputBuffer();
    if (yes == 0) return;
    
    printf("\nMasukkan jumlah meja yang akan diantar: ");
    scanf("%d", &jumlahMeja);
    clearInputBuffer();
    
    for (int i = 0; i < jumlahMeja; i++) {
        printf("\nMasukkan nomor meja ke-%d: ", i+1);
        scanf("%d", &noMeja);
        clearInputBuffer();      
        
        if (noMeja < 1 || noMeja > MAX_MEJA || meja[noMeja - 1].isTersedia || meja[noMeja - 1].stackPesanan == NULL) {
            printf("Meja tidak valid atau tidak memiliki pesanan.\n");
            continue;
        }
        
        // Cetak kategori yang tersedia dengan format yang jelas
        adr_stack current = meja[noMeja - 1].stackPesanan;
        printf("\nKategori tersedia di meja #%d:\n", noMeja);
        while (current != NULL) {
            printf("- %s (asli: %s)\n", current->kategoriNama, current->kategoriNama);
            current = current->next;
        }
        
        printf("Masukkan kategori yang telah diantar (tepat sesuai yang ditampilkan): ");
        fgets(slctKategori, sizeof(slctKategori), stdin);
        slctKategori[strcspn(slctKategori, "\n")] = '\0';
        
        // Cari kategori yang sesuai (tanpa mengubah case)
        adr_stack *prev = &meja[noMeja - 1].stackPesanan;
        current = *prev;
        while (current != NULL) {
            if (strcmp(current->kategoriNama, slctKategori) == 0) {
                break;
            }
            prev = &current->next;
            current = current->next;
        }
        
        if (current == NULL) {
            printf("Kategori '%s' tidak ditemukan di meja tersebut.\n", slctKategori);
            printf("Pastikan mengetik persis seperti yang ditampilkan (termasuk huruf besar/kecil).\n");
            continue;
        }
        
        // Hapus kategori dari stack
        *prev = current->next;
        
        // Kosongkan stack kategori
        while (!isKategoriEmpty(current->data)) {
            MenuStack item = popMenu(&current->data);
            printf("Mengantar: %s (%d)\n", item.info.namaMenu, item.info.qty);
        }
        
        free(current);
        printf("Makanan kategori %s sudah diantar ke meja #%d.\n", slctKategori, noMeja);
        
        if (meja[noMeja - 1].stackPesanan == NULL) {
            meja[noMeja - 1].isTersedia = true;
            strcpy(meja[noMeja - 1].jam_kosong, "00:00");
            printf("Semua pesanan untuk meja #%d sudah selesai.\n", noMeja);
        }
    }
}