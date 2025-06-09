@echo off
echo Reset Database
echo ----------------------------------

REM Hapus semua file database yang ada
echo Menghapus file database yang ada...

if exist "informasi_akun_user.dat" del "informasi_akun_user.dat"
if exist "informasi_akun_user.bak" del "informasi_akun_user.bak"
if exist "informasi_rekening_user.dat" del "informasi_rekening_user.dat"
if exist "informasi_rekening_user.bak" del "informasi_rekening_user.bak"
if exist "informasi_kereta.dat" del "informasi_kereta.dat"
if exist "informasi_kereta.bak" del "informasi_kereta.bak"
if exist "jadwal_kereta.dat" del "jadwal_kereta.dat"
if exist "jadwal_kereta.bak" del "jadwal_kereta.bak"
if exist "kursi_kereta.dat" del "kursi_kereta.dat"
if exist "kursi_kereta.bak" del "kursi_kereta.bak"
if exist "rute_kereta.dat" del "rute_kereta.dat"
if exist "rute_kereta.bak" del "rute_kereta.bak"
if exist "riwayat_pembelian.dat" del "riwayat_pembelian.dat"
if exist "riwayat_pembelian.bak" del "riwayat_pembelian.bak"

echo Semua file database berhasil dihapus.
echo.
echo Database telah di-reset. Jalankan program untuk membuat database baru.

pause 