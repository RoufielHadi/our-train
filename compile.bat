@echo off
echo Kompilasi Program OurTrain...

cd "C:\Users\ritah\Downloads\Penting\Program OurTrain(5)\Program OurTrain(5)"

REM Hentikan proses OurTrain.exe jika sedang berjalan
taskkill /F /IM OurTrain.exe 2>nul || echo Program tidak sedang berjalan

REM Kompilasi semua file .c
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c tree_non_biner.c -o tree_non_biner.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c tree_biner.c -o tree_biner.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_morse.c -o implementasi_morse.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c hash_password.c -o hash_password.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_rute_kereta.c -o implementasi_rute_kereta.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_akun_user.c -o implementasi_akun_user.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_pembayaran.c -o implementasi_pembayaran.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_jadwal_kereta.c -o implementasi_jadwal_kereta.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_informasi_kereta.c -o implementasi_informasi_kereta.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c array.c -o array.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c clear.c -o clear.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_antrian_offline.c -o implementasi_antrian_offline.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_kursi_kereta.c -o implementasi_kursi_kereta.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_rekapitulasi_keuntungan.c -o implementasi_rekapitulasi_keuntungan.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_riwayat.c -o implementasi_riwayat.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c linked.c -o linked.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c queue.c -o queue.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c stack.c -o stack.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c time.c -o time.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c databases.c -o databases.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_authentication.c -o dashboard_authentication.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_user.c -o dashboard_user.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_admin.c -o dashboard_admin.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_cashier.c -o dashboard_cashier.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_machine.c -o dashboard_machine.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_manajemen_kereta.c -o dashboard_manajemen_kereta.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_manajemen_jadwal.c -o dashboard_manajemen_jadwal.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_lihat_jadwal.c -o dashboard_lihat_jadwal.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_tiket_saya.c -o dashboard_tiket_saya.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c implementasi_tiket_saya.c -o implementasi_tiket_saya.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_manajemen_rute.c -o dashboard_manajemen_rute.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_manajemen_kasir.c -o dashboard_manajemen_kasir.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_manajemen_mesin.c -o dashboard_manajemen_mesin.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_manajemen_user.c -o dashboard_manajemen_user.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_akun_saya.c -o dashboard_akun_saya.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c dashboard_rekening_saya.c -o dashboard_rekening_saya.o
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -c main.c -o main.o

REM Link semua file .o menjadi executable
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -o OurTrain.exe main.o tree_non_biner.o tree_biner.o implementasi_morse.o hash_password.o implementasi_rute_kereta.o implementasi_akun_user.o implementasi_pembayaran.o implementasi_jadwal_kereta.o implementasi_informasi_kereta.o array.o clear.o implementasi_antrian_offline.o implementasi_kursi_kereta.o implementasi_rekapitulasi_keuntungan.o implementasi_riwayat.o linked.o queue.o stack.o time.o databases.o dashboard_authentication.o dashboard_user.o dashboard_admin.o dashboard_cashier.o dashboard_machine.o dashboard_manajemen_kereta.o dashboard_manajemen_jadwal.o dashboard_lihat_jadwal.o dashboard_tiket_saya.o implementasi_tiket_saya.o dashboard_manajemen_rute.o dashboard_manajemen_user.o dashboard_akun_saya.o dashboard_rekening_saya.o dashboard_manajemen_mesin.o dashboard_manajemen_kasir.o -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib" -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib" -static-libgcc

if %errorlevel% equ 0 (
  echo Kompilasi berhasil! Program OurTrain.exe telah dibuat.
  dir OurTrain.exe
) else (
  echo Kompilasi gagal. Silakan periksa pesan error di atas.
)

pause 