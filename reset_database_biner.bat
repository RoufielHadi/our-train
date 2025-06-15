@echo off
echo ===================================================
echo RESET DATABASE DAN MEMBUAT DATABASE BINER
echo ===================================================
echo.

echo [1] Menghapus semua file database lama...
if exist informasi_akun_user.dat del /f informasi_akun_user.dat
if exist informasi_rekening_user.dat del /f informasi_rekening_user.dat
if exist informasi_akun_user.bak del /f informasi_akun_user.bak
if exist informasi_rekening_user.bak del /f informasi_rekening_user.bak
if exist informasi_akun_user.text.bak del /f informasi_akun_user.text.bak
if exist informasi_rekening_user.text.bak del /f informasi_rekening_user.text.bak
if exist informasi_akun_user.bin.tmp del /f informasi_akun_user.bin.tmp
if exist informasi_rekening_user.bin.tmp del /f informasi_rekening_user.bin.tmp
if exist informasi_akun_user.tmp del /f informasi_akun_user.tmp
if exist informasi_rekening_user.tmp del /f informasi_rekening_user.tmp

echo Semua file database lama telah dihapus.

echo.
echo [2] Menjalankan aplikasi OurTrain...
echo Silahkan register user baru untuk membuat database biner.
echo.
echo Tekan enter untuk melanjutkan...
pause > nul

start "" OurTrain.exe

echo.
echo Program berjalan di window terpisah.
echo.
echo Setelah register user baru, jalankan check_biner.exe
echo untuk memastikan database sudah dalam format biner.
echo.
pause 