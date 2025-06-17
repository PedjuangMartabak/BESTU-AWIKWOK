z# Sistem Reservasi Restoran Fine Dining

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C Version](https://img.shields.io/badge/C-99%2F11-yellowgreen)

Sistem manajemen reservasi restoran berbasis C dengan ADT Linked List, Stack, dan Priority Queue.

## Fitur Utama
- 📅 **Reservasi Otomatis** dengan prioritas waktu kedatangan
- 🪑 **Alokasi Meja** cerdas (tunggal/gabungan)
- 🍽️ **Manajemen Pesanan** per kategori (Appetizer, Main Course, Dessert)
- 🧾 **Generasi Struk** otomatis dalam format `.txt`
- 📊 **Tracking Pesanan** berbasis stack LIFO

## Struktur Proyek
```bash
restoran/
├── src/
│ ├── queue.[ch] # ADT Priority Queue
│ ├── stack.[ch] # ADT Stack pesanan
│ ├── meja.[ch] # Manajemen meja
│ ├── struk.[ch] # Pembuatan struk
│ └── main.c # Program utama
├── docs/ # Dokumentasi
├── samples/ # Contoh output
└── Makefile # Build system
```


## Prasyarat
- Compiler C (GCC/MinGW)
- Sistem operasi Windows/Linux
- GNU Make (untuk build otomatis)

## Instalasi
```bash
git clone https://github.com/username/reservasi-restoran.git
cd reservasi-restoran
make
```

## Penggunaan
```bash
./restoran
```

## Menu Utama
```bash
=== APLIKASI RESTORAN ===
1. Tambah Reservasi
2. Proses Kedatangan
3. Proses Kedatangan Makanan
4. Cetak Bills
5. Tinjau Ulang Antrean
6. Manage Menu
7. Keluar
```

## Spesifikasi Teknis
Komponen ADT Digunakan File Terkait
```bash
Antrian	Priority ______________Queue                queue.[ch]
Pesanan	Linked_________________List                 pesanan.[ch]
Pengantaran____________________Stack                stack.[ch]
Meja___________________________Array of Struct      meja.[ch]
```




