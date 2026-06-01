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