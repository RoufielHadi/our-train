@echo off
echo ======================================================
echo            OURTRAIN - CLEANUP UTILITY
echo ======================================================
echo.
echo Membersihkan file sementara dan hasil kompilasi...
echo.

echo [1] Menghapus file hasil kompilasi (.o)...
del /f /q *.o 2>nul
echo Selesai.

echo [2] Menghapus file executable sementara (.exe)...
:: Hapus semua executable kecuali OurTrain.exe utama
for %%F in (*.exe) do (
    if /i not "%%F"=="OurTrain.exe" del /f /q "%%F" 2>nul
)
echo Selesai.

echo [3] Menghapus file batch (.bat) yang sudah tidak digunakan...
if exist compile_fix.bat del /f compile_fix.bat
if exist compile_new.bat del /f compile_new.bat
if exist clean_build.bat del /f clean_build.bat
if exist compile_simple.bat del /f compile_simple.bat
if exist force_close_ourtrain.bat del /f force_close_ourtrain.bat
if exist devc_fix.bat del /f devc_fix.bat
if exist modify_output_file.bat del /f modify_output_file.bat
if exist emergency_fix.bat del /f emergency_fix.bat
if exist compile_check.bat del /f compile_check.bat
if exist test_register.bat del /f test_register.bat
if exist test_login.bat del /f test_login.bat
if exist convert_to_binary.bat del /f convert_to_binary.bat
if exist devcpp_compile.bat del /f devcpp_compile.bat
if exist compile_fix2.bat del /f compile_fix2.bat
if exist force_compile.bat del /f force_compile.bat
if exist fix_permission.bat del /f fix_permission.bat
if exist compile_all_options.bat del /f compile_all_options.bat
if exist clean_compile.bat del /f clean_compile.bat
echo Selesai.

echo [4] Menghapus file C sementara untuk pengujian...
if exist check_password.c del /f check_password.c
if exist check_database.c del /f check_database.c
if exist test_lihat_jadwal.c del /f test_lihat_jadwal.c
echo Selesai.

echo [5] Menghapus file dokumentasi yang sudah tidak digunakan...
if exist panduan_lengkap.txt del /f panduan_lengkap.txt
if exist fix_penyimpanan.txt del /f fix_penyimpanan.txt
if exist ringkasan_solusi.txt del /f ringkasan_solusi.txt
if exist panduan_kompilasi.txt del /f panduan_kompilasi.txt
if exist missing_files.txt del /f missing_files.txt
if exist dev_files.txt del /f dev_files.txt
if exist all_files.txt del /f all_files.txt
if exist dev_content.txt del /f dev_content.txt
if exist add_files.txt del /f add_files.txt
echo Selesai.

echo [6] Menghapus file backup database yang tidak diperlukan...
if exist *.bak del /f *.bak 2>nul
if exist *.tmp del /f *.tmp 2>nul
echo Selesai.

echo.
echo ======================================================
echo              PEMBERSIHAN SELESAI
echo ======================================================
echo.
echo File yang dipertahankan:
echo  - OurTrain.exe (file utama)
echo  - *.c dan *.h (file kode sumber dan header)
echo  - *.dat (file database)
echo  - Makefile.win (file konfigurasi kompilasi)
echo  - compile.bat (script kompilasi utama)
echo  - reset_database.bat (reset database)
echo  - reset_database_biner.bat (reset database dalam format biner)
echo  - compile_check_biner.bat (kompilasi utility database biner)
echo  - README_DATABASE_BINER.txt (dokumentasi database biner)
echo  - cleanup.bat (file ini)
echo.
echo Pembersihan selesai! Tekan tombol apa saja untuk keluar.
pause > nul 