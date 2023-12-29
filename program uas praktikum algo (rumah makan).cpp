#include <iostream>
#include <iomanip> // Include for setprecision
#include <string>

#define MAX_ITEMS 50
#define MAX_NAME_LENGTH 50

using namespace std;

// fungsi struct
struct MenuItem {
    string nama;
    float harga;
    int jumlah;
};

// fungsi untuk menambahkan menu  
void tambahkanMenuItem(MenuItem *menu, int &numItems, const string &kategori) {
    cin.ignore();
    cout << "Masukkan nama " << kategori << ": ";
    getline(cin, menu[numItems].nama);

    cout << "Masukkan harga " << kategori << ": ";
    cin >> menu[numItems].harga;

    numItems++;
}

// fungsi untuk menampilkan menu
void tampilkanMenu(MenuItem *menu, int numItems, const string &kategori) {
    cout << "\n======== Daftar " << kategori << " ========" << endl;
    for (int i = 0; i < numItems; i++) {
        cout << i + 1 << ". " << menu[i].nama << " - Rp " << fixed << setprecision(2) << menu[i].harga << endl;
    }
    cout << "================================" << endl;
}

// fungsi untuk mencari menu
void cariMenu(MenuItem *menu, int numItems, const string &kategori) {
    cin.ignore(); // Ignore newline left in the buffer
    string cariNama;
    cout << "Masukkan nama " << kategori << " yang ingin dicari: ";
    getline(cin, cariNama);

    bool found = false;
    cout << "=========== Hasil Pencarian ============ " << kategori << " ==============" << endl;
    for (int i = 0; i < numItems; i++) {
        if (menu[i].nama.find(cariNama) != string::npos) {
            cout << menu[i].nama << " ditemukan! Harganya: Rp " << fixed << setprecision(2) << menu[i].harga << endl;
            found = true;
        }
    }

    if (!found) {
        cout << kategori << " '" << cariNama << "' tidak ditemukan.\n";
    }

    cout << "================================================\n";
}

// fungsi untuk menampilkan menu termahal
void tampilkanMenuTermahal(MenuItem *menu, int numItems, const string &kategori) {
    if (numItems == 0) {
        cout << "Tidak ada data " << kategori << ".\n";
        return;
    }

// fungsi bubble sorting berdasarkan harga
    for (int i = 0; i < numItems - 1; i++) {
        for (int j = 0; j < numItems - i - 1; j++) {
            if (menu[j].harga < menu[j + 1].harga) {
                MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }

    cout << "==== " << kategori << " dengan Harga Termahal =====\n";
    for (int i = 0; i < numItems; i++) {
        cout << i + 1 << ". " << menu[i].nama << " - Rp " << fixed << setprecision(2) << menu[i].harga << endl;
    }
    cout << "----------------------------------------\n";
}

// fungsi untuk memesan menu
float pesanMenu(MenuItem *menu, int numItems, const string &kategori) {
    int jumlah;
    float totalHarga = 0.0;

    cout << "\n======== Daftar " << kategori << " ========\n";
    for (int i = 0; i < numItems; i++) {
        cout << i + 1 << ". " << menu[i].nama << " - Rp " << fixed << setprecision(2) << menu[i].harga << endl;
    }
    cout << "================================\n";

    cout << "Masukkan nomor " << kategori << " yang ingin dipesan: ";
    int nomorPesanan;
    cin >> nomorPesanan;

    if (nomorPesanan >= 1 && nomorPesanan <= numItems) {
        cout << "Anda memesan '" << menu[nomorPesanan - 1].nama << "' seharga Rp " << fixed << setprecision(2) << menu[nomorPesanan - 1].harga << ".\n";

        cout << "Berapa jumlah " << kategori << " yang ingin dipesan? ";
        cin >> jumlah;

        menu[nomorPesanan - 1].jumlah = jumlah;
        totalHarga = menu[nomorPesanan - 1].harga * jumlah;
        cout << "Total Harga Pesanan: Rp " << fixed << setprecision(2) << totalHarga << endl;
    } else {
        cout << "Nomor yang dimasukkan tidak valid. Pesanan tidak dapat diproses.\n";
    }

    return totalHarga;
}

// fungsi untuk menampilkan menu
void tampilkanPesan(MenuItem *menu, int numItems, const string &kategori) {
    cout << "\n===== Daftar " << kategori << " yang Dipesan =====\n";
    for (int i = 0; i < numItems; i++) {
        if (menu[i].jumlah > 0) {
            cout << menu[i].nama << " - Jumlah: " << menu[i].jumlah << " - Total Harga: Rp " << fixed << setprecision(2) << menu[i].harga * menu[i].jumlah << endl;
        }
    }
    cout << "===================================\n";
}

// fungsi untuk menghapus menu
void hapusMenuItem(MenuItem *menu, int &numItems, const string &kategori) {
    int nomorHapus;
    cout << "Masukkan nomor " << kategori << " yang ingin dihapus: ";
    cin >> nomorHapus;

    if (nomorHapus >= 1 && nomorHapus <= numItems) {
        cout << "'" << menu[nomorHapus - 1].nama << "' telah dihapus.\n";

        // Shift elements after the deleted element
        for (int i = nomorHapus - 1; i < numItems - 1; i++) {
            menu[i] = menu[i + 1];
        }

        numItems--;
    } else {
        cout << "Nomor yang dimasukkan tidak valid. Penghapusan tidak dapat dilakukan.\n";
    }
}

// fungsi untuk menampilkan semua menu (makanan & minuman)
void tampilkanSemuaMenu(MenuItem *makanan, int numItemMakanan, MenuItem *minuman, int numItemMinuman) {
    tampilkanMenu(makanan, numItemMakanan, "Makanan");
    tampilkanMenu(minuman, numItemMinuman, "Minuman");
}

int main() {
    struct MenuItem makanan[MAX_ITEMS];
    struct MenuItem minuman[MAX_ITEMS];
    int numItemMakanan = 0;
    int numItemMinuman = 0;
    float totalharga = 0.0;
    int pilihan;

    do {
        cout << ".________________________________________________________." << endl;
        cout << "|================= RUMAH MAKAN PADANG ===================|" << endl;
        cout << "|============= * Program Manajemen Menu *  ==============|" << endl;
        cout << "|                                                        |" << endl;
        cout << "| 1. Entri Nama dan Harga Makanan                        |" << endl;
        cout << "| 2. Entri Nama dan Harga Minuman                        |" << endl;
        cout << "| 3. Lihat Daftar Nama dan Harga Makanan                 |" << endl;
        cout << "| 4. Lihat Daftar Nama dan Harga Minuman                 |" << endl;
        cout << "| 5. Cari Menu                                           |" << endl;
        cout << "| 6. Lihat Makanan atau Minuman dengan Harga Termahal    |" << endl;
        cout << "| 7. Pesan Makanan atau Minuman                          |" << endl;
        cout << "| 8. Keluar dari Program                                 |" << endl;
        cout << "|________________________________________________________|" << endl;
        
        cout << "\nPilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahkanMenuItem(makanan, numItemMakanan, "Makanan");
                break;
            case 2:
                tambahkanMenuItem(minuman, numItemMinuman, "Minuman");
                break;
            case 3:
                tampilkanMenu(makanan, numItemMakanan, "Makanan");
                break;
            case 4:
                tampilkanMenu(minuman, numItemMinuman, "Minuman");
                break;
            case 5:
                cout << "\n===== Cari Menu =====" << endl;
                cout << "1. Cari Nama Makanan\n" << endl;
                cout << "2. Cari Nama Minuman\n" << endl;
                int cariPilihan;
                cout << "Pilihan Anda: ";
                cin >> cariPilihan;

                if (cariPilihan == 1) {
                    cariMenu(makanan, numItemMakanan, "Makanan");
                } else if (cariPilihan == 2) {
                    cariMenu(minuman, numItemMinuman, "Minuman");
                } else {
                    cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 6:
                cout << "\n======== Lihat Harga Termahal ========" << endl;
                tampilkanMenuTermahal(makanan, numItemMakanan, "Makanan");
                tampilkanMenuTermahal(minuman, numItemMinuman, "Minuman");
                break;
            case 7:
                cout << "\n===== Pesan Makanan atau Minuman =====" << endl;
                cout << "1. Pesan Makanan\n" << endl;
                cout << "2. Pesan Minuman\n" << endl;
                cout << "3. Pesan Keduanya\n" << endl;
                int orderPilihan;
                cout << "Pilihan Anda: ";
                cin >> orderPilihan;

                switch (orderPilihan) {
                    case 1:
                        totalharga += pesanMenu(makanan, numItemMakanan, "Makanan");
                        break;
                    case 2:
                        totalharga += pesanMenu(minuman, numItemMinuman, "Minuman");
                        break;
                    case 3:
                        totalharga += pesanMenu(makanan, numItemMakanan, "Makanan");
                        totalharga += pesanMenu(minuman, numItemMinuman, "Minuman");
                        break;
                    default:
                        cout << "Pilihan tidak valid. Pesanan tidak dapat diproses." << endl;
                        break;
                }
                break;
            case 8:
                cout << "\n===== Keluar dari Program =====" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan !=8);

    return 0;
}