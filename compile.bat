@echo off
echo Kompilasi OurTrain dengan MinGW dari Dev-C++...

REM Cek lokasi Dev-C++
set DEVCPP_PATH=C:\Program Files (x86)\Dev-Cpp
set MINGW_PATH=C:\MinGW

if exist "%DEVCPP_PATH%\MinGW64\bin\g++.exe" (
    echo Menggunakan Dev-C++ di %DEVCPP_PATH%
    set PATH=%PATH%;%DEVCPP_PATH%\MinGW64\bin
) else if exist "%MINGW_PATH%\bin\g++.exe" (
    echo Menggunakan MinGW di %MINGW_PATH%
    set PATH=%PATH%;%MINGW_PATH%\bin
) else (
    echo Dev-C++ atau MinGW tidak ditemukan di jalur standar.
    echo Silakan instal Dev-C++ atau MinGW, atau sesuaikan jalur dalam compile.bat
    pause
    exit /b 1
)

REM Kompilasi satu file sebagai tes
echo Mengompilasi databases.c sebagai tes...
g++ -c databases.c -o databases.o -std=c++11 -D_CRT_SECURE_NO_WARNINGS

if %ERRORLEVEL% == 0 (
    echo Kompilasi test berhasil!
    echo Menghapus file test...
    del databases.o
    
    REM Kompilasi seluruh program
    echo Mengompilasi OurTrain...
    mingw32-make -f Makefile.win
) else (
    echo Kompilasi test gagal dengan kode error %ERRORLEVEL%.
)

pause 