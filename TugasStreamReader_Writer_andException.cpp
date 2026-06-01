#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <exception>

using namespace std;

// Struktur data untuk mempermudah manajemen barang di file/gudang
struct Barang {
    string id;
    string nama;
    string harga;
};

class TokoElektronik {
private:
    // 1. Atribut Private: array berkapasitas 3 elemen (Enkapsulasi)
    array<string, 3> etalase;

public:
    // Constructor: Mengisi data awal ke etalase secara otomatis
    TokoElektronik() {
        etalase = {"Laptop Asus", "Smartphone Samsung", "Smart TV LG"};
    }

    // Method Public untuk mengambil produk berdasarkan nomorRak
    string ambilProduk(size_t nomorRak) {
        try {
            // Menggunakan .at() sesuai ketentuan untuk memicu out_of_range jika indeks ngawur
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            // 2. Melemparkan kembali (throw) pesan error kustom jika melewati batas
            throw string("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

// fungsi-fungsi utama

// Tampilkan Semua Data dari File (Read)
void tampilkanGudang() {
    ifstream infile;
    infile.open("gudang.txt");
    
    cout << "\n=== DAFTAR BARANG DI GUDANG ===" << endl;
    if (infile.is_open()) {
        string baris;
        int nomor = 1;
        bool adaData = false;
        
        // Membaca file baris demi baris seperti di contoh StreamReaderandWriter.jpg
        while (getline(infile, baris)) {
            if (!baris.empty()) {
                cout << nomor << ". " << baris << endl;
                nomor++;
                adaData = true;
            }
        }
        
        if (!adaData) {
            cout << "[Gudang Kosong / Belum ada data]" << endl;
        }
        infile.close();
    } else {
        // Jika file belum ada, otomatis dianggap kosong
        cout << "[Gudang Kosong / File belum dibuat]" << endl;
    }
    cout << "===============================" << endl;
}

// Tambah Barang Baru ke File (Create)
void tambahBarang() {
    ofstream outfile;
    // Membuka dengan mode app (append) supaya data baru tertulis di bawahnya, tidak menimpa data lama
    outfile.open("gudang.txt", ios::app);
    
    if (outfile.is_open()) {
        string namaBarang, hargaBarang, idBaris;
        
        cout << "\n--- Tambah Barang Baru ---" << endl;
        cout << "Masukkan ID Barang   : ";
        cin >> idBaris;
        cin.ignore(); // Membersihkan buffer sebelum getline
        
        cout << "Masukkan Nama Barang : ";
        getline(cin, namaBarang);
        
        cout << "Masukkan Harga       : ";
        getline(cin, hargaBarang);
        
        // Format simpan simpel: ID | Nama | Harga
        outfile << idBaris << " | " << namaBarang << " | Rp." << hargaBarang << endl;
        
        cout << "=> Barang berhasil ditambahkan ke gudang.txt!" << endl;
        outfile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

// Update Data Barang di File (Update)
void updateBarang() {
    tampilkanGudang();
    
    ifstream infile("gudang.txt");
    if (!infile.is_open()) {
        cout << "Gagal membuka file atau gudang masih kosong!" << endl;
        return;
    }
    
    string daftarBaris[100];
    int jumlahBaris = 0;
    
    while (getline(infile, daftarBaris[jumlahBaris])) {
        if (!daftarBaris[jumlahBaris].empty()) {
            jumlahBaris++;
        }
    }
    infile.close();
    
    if (jumlahBaris == 0) {
        cout << "Tidak ada data yang bisa diubah." << endl;
        return;
    }
    
    int pilihanNomor;
    cout << "Masukkan nomor urut barang yang ingin DIUBAH: ";
    cin >> pilihanNomor;
    cin.ignore();
    
    if (pilihanNomor < 1 || pilihanNomor > jumlahBaris) {
        cout << "Nomor barang tidak valid!" << endl;
        return;
    }
    
    // Input data baru
    string namaBaru, hargaBaru, idBaru;
    cout << "\n--- Masukkan Data Baru ---" << endl;
    cout << "Masukkan ID Baru   : ";
    cin >> idBaru;
    cin.ignore();
    cout << "Masukkan Nama Baru : ";
    getline(cin, namaBaru);
    cout << "Masukkan Harga Baru: ";
    getline(cin, hargaBaru);
    
    // FIX: Sekarang sudah pakai operator + untuk gabungin string harganya
    daftarBaris[pilihanNomor - 1] = idBaru + " | " + namaBaru + " | Rp." + hargaBaru;
    
    // Tulis ulang seluruh data dari array sementara ke file (menimpa file lama)
    ofstream outfile("gudang.txt", ios::out);
    for (int i = 0; i < jumlahBaris; i++) {
        outfile << daftarBaris[i] << endl;
    }
    outfile.close();
    
    cout << "=> Data barang nomor " << pilihanNomor << " berhasil diperbarui!" << endl;
}

// Hapus Data Barang dari File (Delete)
void hapusBarang() {
    tampilkanGudang();
    
    ifstream infile("gudang.txt");
    if (!infile.is_open()) {
        cout << "Gagal membuka file atau gudang masih kosong!" << endl;
        return;
    }
    
    string daftarBaris[100];
    int jumlahBaris = 0;
    
    while (getline(infile, daftarBaris[jumlahBaris])) {
        if (!daftarBaris[jumlahBaris].empty()) {
            jumlahBaris++;
        }
    }
    infile.close();
    
    if (jumlahBaris == 0) {
        cout << "Tidak ada data yang bisa dihapus." << endl;
        return;
    }
    
    int pilihanNomor;
    cout << "Masukkan nomor urut barang yang ingin DIHAPUS: ";
    cin >> pilihanNomor;
    
    if (pilihanNomor < 1 || pilihanNomor > jumlahBaris) {
        cout << "Nomor barang tidak valid!" << endl;
        return;
    }
    
    // Tulis ulang data ke file KECUALI nomor baris yang dihapus
    ofstream outfile("gudang.txt", ios::out);
    for (int i = 0; i < jumlahBaris; i++) {
        if (i != (pilihanNomor - 1)) {
            outfile << daftarBaris[i] << endl;
        }
    }
    outfile.close();
    
    cout << "=> Data barang nomor " << pilihanNomor << " berhasil dihapus dari gudang!" << endl;
}

// Simulasi Etalase Toko untuk testing Exception Handling
void simulasiEtalase(TokoElektronik& toko) {
    cout << "\n=== SIMULASI PENGUJIAN EXCEPTION HANDLING ===" << endl;
    
    // Skenario 1: Pengambilan barang di rak indeks ke-1 (Harus Sukses)
    cout << "[Skenario 1] Mencoba mengambil barang di rak indeks ke-1..." << endl;
    try {
        string barang = toko.ambilProduk(1);
        cout << "Hasil: Sukses mengambil -> " << barang << endl;
    }
    catch (const string& pesanError) {
        cout << "Hasil: Catch string error -> " << pesanError << endl;
    }
    
    cout << "--------------------------------------------------" << endl;
    
    // Skenario 2: Pengambilan barang di rak indeks ke-5 (Harus Gagal)
    cout << "[Skenario 2] Mencoba mengambil barang di rak indeks ke-5..." << endl;
    try {
        string barang = toko.ambilProduk(5);
        cout << "Hasil: Sukses mengambil -> " << barang << endl; 
    }
    catch (const string& pesanError) {
        // Menangkap string pesan error kustom yang dilempar dari method ambilProduk
        cout << "Hasil: Tangkap Error Kustom -> " << pesanError << endl;
    }
    cout << "====================================================\n" << endl;
}