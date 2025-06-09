======================================================
                DATABASE BINER - OURTRAIN
======================================================

Panduan Penggunaan Database Biner pada Aplikasi OurTrain
--------------------------------------------------------

1. PENDAHULUAN
--------------
Penyimpanan database aplikasi OurTrain sekarang menggunakan format biner untuk:
- Meningkatkan keamanan data (data tidak bisa dibaca secara langsung dengan text editor)
- Mengoptimalkan ukuran penyimpanan
- Mempercepat proses baca/tulis data

File yang menggunakan format biner:
- informasi_akun_user.dat
- informasi_rekening_user.dat

2. FITUR DATABASE BINER
----------------------
- Penyimpanan data menggunakan fwrite() langsung untuk struktur Record
- Pembacaan data menggunakan fread() untuk membaca seluruh struktur Record
- Data disimpan dalam format biner yang tidak dapat dibaca langsung
- Konversi otomatis dari format teks ke format biner saat aplikasi pertama kali dijalankan

3. TOOLS TAMBAHAN
----------------
Aplikasi ini dilengkapi dengan beberapa tool untuk membantu pengelolaan database biner:

a. check_biner.exe (compile dengan compile_check_biner.bat)
   - Mengecek format database apakah sudah biner atau masih teks
   - Menampilkan informasi detail tentang file database
   - Opsi untuk mengkonversi database dari teks ke biner

b. reset_database_biner.bat
   - Menghapus semua file database yang ada
   - Menjalankan aplikasi OurTrain untuk membuat database biner baru
   - Memastikan database yang dibuat dalam format biner

4. MENGGUNAKAN DATABASE BINER
---------------------------
Database biner akan dibuat otomatis ketika:
- Aplikasi OurTrain pertama kali dijalankan
- User melakukan registrasi baru
- Database lama dikonversi dengan KonversiDatabaseKeBiner()

5. DEBUGGING DATABASE BINER
-------------------------
Jika terjadi masalah dengan database biner, Anda dapat:
1. Menjalankan check_biner.exe untuk memeriksa format database
2. Menjalankan reset_database_biner.bat untuk membuat database baru
3. Memeriksa log pesan yang ditampilkan di konsol saat program berjalan

6. INFORMASI PENTING
------------------
- Format biner TIDAK dapat dibuka atau diedit dengan text editor
- Jangan manipulasi file database .dat secara manual
- Selalu gunakan fungsi API yang disediakan dalam databases.c untuk operasi database
- Backup file database.dat secara berkala jika diperlukan

Untuk informasi lebih lanjut, hubungi pengembang aplikasi OurTrain.

======================================================
          © 2023 OurTrain - All Rights Reserved
====================================================== 