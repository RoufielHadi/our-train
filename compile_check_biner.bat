@echo off
echo Kompilasi program check_biner.c...

:: Cek Dev-C++ path
for /f "tokens=2*" %%a in ('reg query "HKLM\SOFTWARE\Bloodshed\Dev-C++" /v "Install_Dir" 2^>nul') do set "DEVCPP_PATH=%%b"

if "%DEVCPP_PATH%"=="" (
    if exist "C:\Program Files (x86)\Dev-Cpp" (
        set "DEVCPP_PATH=C:\Program Files (x86)\Dev-Cpp"
    ) else if exist "C:\Dev-Cpp" (
        set "DEVCPP_PATH=C:\Dev-Cpp"
    ) else (
        echo Dev-C++ tidak ditemukan. Menggunakan gcc langsung...
        gcc -o check_biner.exe check_biner.c databases.c -I.
        goto CHECK_RESULT
    )
)

echo Menggunakan Dev-C++ dari: %DEVCPP_PATH%
"%DEVCPP_PATH%\bin\gcc.exe" -o check_biner.exe check_biner.c databases.c -I. -L"%DEVCPP_PATH%\lib"

:CHECK_RESULT
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Kompilasi gagal! Periksa pesan error di atas.
    pause
    exit /b
)

echo.
echo Kompilasi berhasil!
echo.
echo Menjalankan program check_biner.exe...
echo.
check_biner.exe

echo.
pause 