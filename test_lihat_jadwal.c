/*
Test program untuk fitur Lihat Jadwal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dashboard_lihat_jadwal.h"
#include "implementasi_akun_user.h"
#include "clear.h"

int main() {
    // Buat user dummy untuk testing
    User user_dummy;
    strcpy(user_dummy.email, "test@example.com");
    strcpy(user_dummy.nama, "Test User");
    strcpy(user_dummy.alamat, "Test Address");
    strcpy(user_dummy.nomor_telepon, "081234567890");
    strcpy(user_dummy.password, "password");
    user_dummy.is_admin = 0; // User biasa, bukan admin
    
    // Jalankan menu lihat jadwal
    MenuLihatJadwal(user_dummy);
    
    return 0;
} 