from datetime import date, timedelta

# Konfigurasi
JUMLAH_GERBONG = 8
NAMA_FILE_JADWAL = "jadwal_kereta.txt"
NAMA_FILE_OUTPUT = "kursi_kereta.txt"

# Jumlah kursi per baris huruf (A, B, C, D)
BARIS_KURSI = ['A', 'B', 'C', 'D']
KURSI_PER_BARIS = 20  # A1–A20, B1–B20, ..., D1–D20
TOTAL_KURSI_PER_GERBONG = len(BARIS_KURSI) * KURSI_PER_BARIS

# Fungsi membaca data dari file jadwal_kereta.txt
def baca_jadwal(nama_file):
    try:
        with open(nama_file, "r", encoding="utf-8") as f:
            return [baris.strip() for baris in f.readlines() if baris.strip()]
    except FileNotFoundError:
        print(f"❌ File '{nama_file}' tidak ditemukan.")
        return []

# Fungsi membuat data kursi per gerbong
def buat_kursi_per_gerbong(id_kereta, jumlah_segmennya, tanggal, nomor_gerbong):
    kursi_list = []
    for huruf in BARIS_KURSI:
        for no in range(1, KURSI_PER_BARIS + 1):
            kode_kursi = f"{huruf}{no}"
            status_kursi = ','.join(['True'] * jumlah_segmennya)
            kursi_list.append(f"{kode_kursi} = '{status_kursi}'")
    return f"ID_Kereta = '{id_kereta}' | Gerbong = 'G{nomor_gerbong}' | Tanggal = '{tanggal}' | " + " | ".join(kursi_list)

# Fungsi utama membuat database kursi selama 3 hari ke depan
def buat_database_kursi():
    jadwal = baca_jadwal(NAMA_FILE_JADWAL)
    if not jadwal:
        return

    hasil = []

    for hari_ke in range(1, 4):  # Hari ke-1 sampai ke-3 dari hari ini
        tanggal_hari = (date.today() + timedelta(days=hari_ke)).strftime('%Y-%m-%d')

        for baris in jadwal:
            try:
                bagian = baris.strip().split('|')
                id_kereta = bagian[0]
                daftar_stasiun = bagian[1].split(',')
                jumlah_segmennya = len(daftar_stasiun) - 1

                for g in range(1, JUMLAH_GERBONG + 1):  # G1 sampai G8
                    hasil.append(buat_kursi_per_gerbong(id_kereta, jumlah_segmennya, tanggal_hari, g))

            except IndexError:
                print(f"⚠️ Baris rusak atau tidak lengkap: {baris}")
                continue

    # Simpan ke file
    with open(NAMA_FILE_OUTPUT, "w", encoding="utf-8") as f:
        for baris in hasil:
            f.write(baris + "\n")

    print(f"✅ Database kursi berhasil dibuat di '{NAMA_FILE_OUTPUT}' untuk 3 hari ke depan.")

# Jalankan
if __name__ == "__main__":
    buat_database_kursi()
