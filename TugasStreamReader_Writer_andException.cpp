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