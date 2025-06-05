# OurTrain - Sistem Pemesanan Tiket Kereta Api

## Deskripsi
OurTrain adalah sistem pemesanan tiket kereta api yang dikembangkan untuk mengelola informasi rute kereta api di Pulau Jawa. Sistem ini mengimplementasikan struktur data pohon (tree) untuk merepresentasikan rute kereta dan stasiun, serta menggunakan algoritma pencarian rute terpendek untuk menemukan jalur optimal antar stasiun.

## Fitur
- Visualisasi rute kereta api di Pulau Jawa
- Pencarian stasiun terdekat dalam radius tertentu
- Pencarian jalur terpendek antar stasiun
- Pengecekan ketersediaan rute antar stasiun
- Penambahan stasiun baru ke dalam sistem
- Penambahan informasi jarak dan waktu tempuh antar stasiun
- Keamanan data dengan sistem hashing password menggunakan kode Morse

## Struktur Data yang Digunakan
- **Tree Non-Biner**: Digunakan untuk merepresentasikan jaringan stasiun kereta api di Pulau Jawa
- **Tree Biner**: Digunakan untuk implementasi sistem hashing password dengan kode Morse
- **Array Dinamis**: Digunakan untuk menyimpan informasi jarak dan waktu tempuh antar stasiun

## Cara Menjalankan Aplikasi
1. Buka Dev-C++
2. Pilih File -> Open Project
3. Pilih file OurTrain.dev
4. Kompilasi dan jalankan program (F11)

## Komponen Aplikasi
- `main.c`: Program utama dengan antarmuka menu konsol
- `tree_non_biner.h` & `tree_non_biner.c`: Implementasi struktur data pohon non-biner
- `tree_biner.h` & `tree_biner.c`: Implementasi struktur data pohon biner
- `implementasi_rute_kereta.h` & `implementasi_rute_kereta.c`: Implementasi sistem rute kereta api
- `implementasi_morse.h` & `implementasi_morse.c`: Implementasi sistem kode Morse
- `hash_password.h` & `hash_password.c`: Implementasi sistem hashing password

## Kontributor 
1. Roufiel Hadi (241524028)
- Kelas 1A
- Jurusan Teknik Komputer dan Informatika
- Politeknik Negeri Bandung 

2. Devi Maulani (241524007)
- Kelas 1A
- Jurusan Teknik Komputer dan Informatika
- Politeknik Negeri Bandung 

3. Adi Rafi (241524001)
- Kelas 1A
- Jurusan Teknik Komputer dan Informatika
- Politeknik Negeri Bandung 
