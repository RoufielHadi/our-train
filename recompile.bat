@echo off
echo Recompiling all source files...

gcc -c array.c -o array.o
gcc -c check_biner.c -o check_biner.o
gcc -c clear.c -o clear.o
gcc -c dashboard_admin.c -o dashboard_admin.o
gcc -c dashboard_akun_saya.c -o dashboard_akun_saya.o
gcc -c dashboard_authentication.c -o dashboard_authentication.o
gcc -c dashboard_cashier.c -o dashboard_cashier.o
gcc -c dashboard_kursi_kereta.c -o dashboard_kursi_kereta.o
gcc -c dashboard_lihat_jadwal.c -o dashboard_lihat_jadwal.o
gcc -c dashboard_machine.c -o dashboard_machine.o
gcc -c dashboard_manajemen_jadwal.c -o dashboard_manajemen_jadwal.o
gcc -c dashboard_manajemen_kereta.c -o dashboard_manajemen_kereta.o
gcc -c dashboard_manajemen_rute.c -o dashboard_manajemen_rute.o
gcc -c dashboard_manajemen_user.c -o dashboard_manajemen_user.o
gcc -c dashboard_pembayaran.c -o dashboard_pembayaran.o
gcc -c dashboard_rekening_saya.c -o dashboard_rekening_saya.o
gcc -c dashboard_tiket_saya.c -o dashboard_tiket_saya.o
gcc -c dashboard_user.c -o dashboard_user.o
gcc -c databases.c -o databases.o
gcc -c hash_password.c -o hash_password.o
gcc -c implementasi_akun_user.c -o implementasi_akun_user.o
gcc -c implementasi_antrian_offline.c -o implementasi_antrian_offline.o
gcc -c implementasi_informasi_kereta.c -o implementasi_informasi_kereta.o
gcc -c implementasi_jadwal_kereta.c -o implementasi_jadwal_kereta.o
gcc -c implementasi_kursi_kereta.c -o implementasi_kursi_kereta.o
gcc -c implementasi_morse.c -o implementasi_morse.o
gcc -c implementasi_pembayaran.c -o implementasi_pembayaran.o
gcc -c implementasi_pembelian_tiket.c -o implementasi_pembelian_tiket.o
gcc -c implementasi_rekapitulasi_keuntungan.c -o implementasi_rekapitulasi_keuntungan.o
gcc -c implementasi_riwayat.c -o implementasi_riwayat.o
gcc -c implementasi_rute_kereta.c -o implementasi_rute_kereta.o
gcc -c implementasi_tiket_saya.c -o implementasi_tiket_saya.o
gcc -c linked.c -o linked.o
gcc -c main.c -o main.o
gcc -c queue.c -o queue.o
gcc -c stack.c -o stack.o
gcc -c time.c -o time.o
gcc -c tree_biner.c -o tree_biner.o
gcc -c tree_non_biner.c -o tree_non_biner.o

echo Recompilation complete!
echo.
echo Now run: mingw32-make -f Makefile.win 