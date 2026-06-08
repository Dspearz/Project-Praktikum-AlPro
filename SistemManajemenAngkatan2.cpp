// ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------
//                                        IF'25-SPACE
// ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <conio.h> 

using namespace std;

// ------------------------------------
// DEKLARASI VARIABLE GLOBAL DAN STRUCT
// ------------------------------------

struct Mahasiswa {
    string nim;
    string nama;
    float ipk;
    int totalSks;
    string kelompokStudi;
};

struct Kas {
    string idTransaksi;
    string nimPembayar;
    int nominal;
    char jenis; 
    string tanggal;
};

struct SuratRekomendasi {
    string idSurat;
    string nimPemohon;
    string namaEvent;
    string tingkatan; 
    int statusRekomendasi; 
    string alasanDitolak;
};

struct Aspirasi {
    string idAspirasi;
    string kategori; 
    string detailKeluhan;
    int tingkatUrgensi; 
    int statusProgres; 
};

const int MAX_DATA = 300;
const int TARGET_KAS = 100000;

Mahasiswa daftarMahasiswa[MAX_DATA];
int jumlahMahasiswa = 0;

Kas daftarKas[MAX_DATA];
int jumlahKas = 0;

SuratRekomendasi daftarSurat[MAX_DATA];
int jumlahSurat = 0;

Aspirasi daftarAspirasi[MAX_DATA];
int jumlahAspirasi = 0;

// --------------------------------------
// [TAMBAHAN]: FUNGSI UNTUK MASKING PASSWORD
// --------------------------------------
string inputPassword() {
    string pass = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { 
            if (pass.length() > 0) {
                cout << "\b \b"; 
                pass.resize(pass.length() - 1);
            }
        } else if (ch != '\n' && ch != '\t') { 
            pass += ch;
            cout << '#'; 
        }
    }
    cout << "\n";
    return pass;
}

// -------------
// LOGIN SYSTEM
// -------------

int loginSystem() {
    string user, pass;
    int chance = 3;

    do {
        cout << "\n=======================================";
        cout << "\n    LOGIN SYSTEM ANGKATAN              ";
        cout << "\n=======================================";
        cout << "\nUsername : "; cin >> user;
        cout << "Password : "; pass = inputPassword(); 

        if (user == "admin" && pass == "admin123") {
            cout << "\n[v] Login berhasil! Selamat datang Admin.\n";
            return 1;
        }
        else if (user == "anggota" && pass == "mhs123") {
            cout << "\n[v] Login berhasil! Selamat datang Anggota.\n";
            return 2;
        }
        else {
            chance--;
            cout << "[!] User/Password salah! Sisa Percobaan : " << chance << "\n";
        }
    } while (chance > 0);

    return 0; 
}
//------------------
// FUNGSI2 ALGORITMA
//------------------

void swapMhs(Mahasiswa &a, Mahasiswa &b) {
    Mahasiswa temp = a;
    a = b;
    b = temp;
}

void urutkanBerdasarkanNim() {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = 0; j < jumlahMahasiswa - i - 1; j++) {
            if (daftarMahasiswa[j].nim > daftarMahasiswa[j + 1].nim) {
                swapMhs(daftarMahasiswa[j], daftarMahasiswa[j + 1]);
            }
        }
    }
}

void quickSortIpk(int low, int high) {
    if (low < high) {
        float pivot = daftarMahasiswa[high].ipk;
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (daftarMahasiswa[j].ipk > pivot) {
                i++;
                swapMhs(daftarMahasiswa[i], daftarMahasiswa[j]);
            }
        }
        swapMhs(daftarMahasiswa[i + 1], daftarMahasiswa[high]);
        int pi = i + 1;
        quickSortIpk(low, pi - 1);
        quickSortIpk(pi + 1, high);
    }
}

int binarySearchMhs(string targetNim) {
    urutkanBerdasarkanNim(); 
    int low = 0, high = jumlahMahasiswa - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (daftarMahasiswa[mid].nim == targetNim) return mid;
        if (daftarMahasiswa[mid].nim < targetNim) low = mid + 1;
        else high = mid - 1;
    }
    return -1; 
}

int hitungTotalKasMhs(string targetNim) {
    int total = 0;
    for (int i = 0; i < jumlahKas; i++) {
        if (daftarKas[i].nimPembayar == targetNim && daftarKas[i].jenis == 'D') {
            total += daftarKas[i].nominal;
        }
    }
    return total;
}

// ----------------------
// MODUL MENU TAMBAH DATA
// ----------------------

void tambahMahasiswa() {
    if (jumlahMahasiswa >= MAX_DATA) {
        cout << "\n[!] ERROR: Database mahasiswa penuh!\n"; return;
    }
    string inputNim;
    cout << "\n==== REGISTRASI MAHASISWA BARU ====";
    cout << "\nNIM : "; cin >> inputNim;
    if (binarySearchMhs(inputNim) != -1) {
        cout << "[!] ERROR: NIM sudah terdaftar! Registrasi dibatalkan.\n"; return;
    }
    daftarMahasiswa[jumlahMahasiswa].nim = inputNim;
    cout << "Nama : "; cin.ignore(); getline(cin, daftarMahasiswa[jumlahMahasiswa].nama);
    cout << "IPK : "; cin >> daftarMahasiswa[jumlahMahasiswa].ipk;
    cout << "Total SKS : "; cin >> daftarMahasiswa[jumlahMahasiswa].totalSks;
    cout << "Kelompok Studi : "; cin.ignore(); getline(cin, daftarMahasiswa[jumlahMahasiswa].kelompokStudi);
    jumlahMahasiswa++;
    cout << "\n[v] Berhasil menambahkan data mahasiswa!\n";
}

void tampilkanAnalytics() {
    if (jumlahMahasiswa == 0) { cout << "\n[!] Belum ada data mahasiswa di sistem!\n"; return; }
    
    int pilihanSort;
    cout << "\nPilih metode pengurutan tampilan:\n";
    cout << "1. Berdasarkan NIM (A-Z)\n";
    cout << "2. Berdasarkan Peringkat IPK (Tertinggi ke Terendah)\n";
    cout << "Pilihan (1/2): "; cin >> pilihanSort;

    if (pilihanSort == 1) urutkanBerdasarkanNim();
    else if (pilihanSort == 2) quickSortIpk(0, jumlahMahasiswa - 1);
    else urutkanBerdasarkanNim();

    float totalIpk = 0;
    cout << "\n============================================================================================================\n";
    cout << "No.\tNIM\t\tIPK\tSKS\tKelompok Studi (KSM)\t\tNama\n";
    cout << "============================================================================================================\n";
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << i + 1 << ".\t" << daftarMahasiswa[i].nim << "\t" << daftarMahasiswa[i].ipk << "\t"
             << daftarMahasiswa[i].totalSks << "\t" << daftarMahasiswa[i].kelompokStudi;
        
        int len = daftarMahasiswa[i].kelompokStudi.length();
        if (len < 8) cout << "\t\t\t\t"; 
        else if (len < 16) cout << "\t\t\t";
        else if (len < 24) cout << "\t\t";
        else cout << "\t";
        
        cout << daftarMahasiswa[i].nama << "\n";
        totalIpk += daftarMahasiswa[i].ipk;
    }
    cout << "============================================================================================================\n";
    cout << "Rata-rata IPK Angkatan : " << totalIpk / jumlahMahasiswa << "\n";
}

void cariMahasiswa() {
    if (jumlahMahasiswa == 0) { 
        cout << "\n[!] Belum ada data mahasiswa di sistem!\n"; return; 
    }

    string keyword;
    cout << "\n==== PENCARIAN DATA MAHASISWA ====";
    cout << "\nMasukkan Nama Panggilan / Bagian NIM yang dicari: ";
    cin.ignore();
    getline(cin, keyword);

    string keyLower = keyword;
    transform(keyLower.begin(), keyLower.end(), keyLower.begin(), ::tolower); 

    bool ketemu = false;
    cout << "\n--- Hasil Pencarian ---\n";
    for (int i = 0; i < jumlahMahasiswa; i++) {
        string namaLower = daftarMahasiswa[i].nama;
        string nimLower = daftarMahasiswa[i].nim;
        transform(namaLower.begin(), namaLower.end(), namaLower.begin(), ::tolower);
        transform(nimLower.begin(), nimLower.end(), nimLower.begin(), ::tolower);

        if (namaLower.find(keyLower) != string::npos || nimLower.find(keyLower) != string::npos) {
            cout << "NIM      : " << daftarMahasiswa[i].nim << "\n";
            cout << "Nama     : " << daftarMahasiswa[i].nama << "\n";
            cout << "IPK      : " << daftarMahasiswa[i].ipk << "\n";
            cout << "SKS      : " << daftarMahasiswa[i].totalSks << "\n";
            cout << "KSM      : " << daftarMahasiswa[i].kelompokStudi << "\n";
            cout << "--------------------------------------\n";
            ketemu = true;
        }
    }

    if (!ketemu) {
        cout << "[-] Mahasiswa dengan kata kunci '" << keyword << "' tidak ditemukan.\n";
    }
}

string trim(string s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (string::npos == first) return s;
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

void cariBakatFilter() {
    if (jumlahMahasiswa == 0) { 
        cout << "\n[!] Belum ada data mahasiswa di sistem!\n"; return; 
    }

    string namaLomba, cariKs; 
    float minIpk;
    
    cout << "\n==== PENCARIAN KANDIDAT DELEGASI LOMBA ====";
    cout << "\nNama Lomba / Kompetisi : "; 
    cin.ignore(); 
    getline(cin, namaLomba);

    cout << "Bidang KSM yang Dicari : "; 
    getline(cin, cariKs);
    cariKs = trim(cariKs);

    cout << "Standar IPK Minimum    : "; 
    cin >> minIpk;

    cout << "\n=======================================================================\n";
    cout << "              KANDIDAT DELEGASI UNTUK: " << namaLomba << "\n";
    cout << "          Kriteria: KSM " << cariKs << " | Minimal IPK: " << minIpk << "\n";
    cout << "=======================================================================\n";
    cout << "No.\tNIM\t\tIPK\tNama Mahasiswa\n";
    cout << "-----------------------------------------------------------------------\n";
    
    bool ketemu = false;
    int hitung = 0;
    
    quickSortIpk(0, jumlahMahasiswa - 1);

    for (int i = 0; i < jumlahMahasiswa; i++) {
        string kelompokTersimpan = trim(daftarMahasiswa[i].kelompokStudi);
        if (kelompokTersimpan == cariKs && daftarMahasiswa[i].ipk >= minIpk) {
            hitung++;
            cout << hitung << ".\t" << daftarMahasiswa[i].nim << "\t" << daftarMahasiswa[i].ipk << "\t" << daftarMahasiswa[i].nama << "\n";
            ketemu = true;
        }
    }
    
    if (!ketemu) cout << "\t[-] Tidak ada mahasiswa yang memenuhi kriteria delegasi.\n";
    else {
        cout << "-----------------------------------------------------------------------\n";
        cout << "[v] Total ditemukan " << hitung << " kandidat potensial untuk diberangkatkan.\n";
    }
}

void inputCatatanKas() {
    if (jumlahKas >= MAX_DATA) { cout << "\n[!] ERROR: Log transaksi penuh!\n"; return; }
    string inputNim;
    cout << "\n==== INPUT TRANSAKSI KAS ====";
    cout << "\nNIM Pembayar/Penerima : "; cin >> inputNim;
    if (binarySearchMhs(inputNim) == -1) {
        cout << "[!] ERROR: NIM tidak ditemukan di sistem.\n"; return;
    }
    daftarKas[jumlahKas].idTransaksi = "KAS-" + to_string(jumlahKas + 1);
    daftarKas[jumlahKas].nimPembayar = inputNim;
    cout << "Nominal Uang : Rp "; cin >> daftarKas[jumlahKas].nominal;
    cout << "Jenis Transaksi (D = Masuk, K = Keluar) : "; cin >> daftarKas[jumlahKas].jenis;
    cout << "Tanggal (DD-MM-YYYY) : "; cin >> daftarKas[jumlahKas].tanggal;
    jumlahKas++;
    cout << "\n[v] Transaksi kas berhasil dicatat!\n";
}

void cekTunggakanKas() {
    urutkanBerdasarkanNim();
    cout << "\n======================================================\n";
    cout << "            DAFTAR TUNGGAKAN KAS MAHASISWA            \n";
    cout << "======================================================\n";
    cout << "NIM\t\tSisa Tunggakan\tNama\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < jumlahMahasiswa; i++) {
        int terbayar = hitungTotalKasMhs(daftarMahasiswa[i].nim);
        int sisa = TARGET_KAS - terbayar;
        if (sisa > 0) cout << daftarMahasiswa[i].nim << "\tRp " << sisa << "\t\t" << daftarMahasiswa[i].nama << "\n";
    }
}

void ajukanSuratRekomendasi() {
    if (jumlahSurat >= MAX_DATA) { cout << "\n[!] ERROR: Antrean surat penuh!\n"; return; }
    string cekNim;
    cout << "\n==== PENGAJUAN SURAT REKOMENDASI HIMPUNAN ====";
    cout << "\nMasukkan NIM Pemohon : "; cin >> cekNim;

    int indeksMhs = binarySearchMhs(cekNim);
    if (indeksMhs == -1) { cout << "[!] ERROR: NIM tidak terdaftar dalam database.\n"; return; }

    daftarSurat[jumlahSurat].idSurat = "SR-" + to_string(jumlahSurat + 1);
    daftarSurat[jumlahSurat].nimPemohon = cekNim;
    cout << "Nama Event / Organisasi Luar : "; cin.ignore(); getline(cin, daftarSurat[jumlahSurat].namaEvent);
    cout << "Tingkatan (Universitas/Nasional/Internasional) : "; cin >> daftarSurat[jumlahSurat].tingkatan;

    int totalBayar = hitungTotalKasMhs(cekNim);
    int sisaHutangKas = TARGET_KAS - totalBayar;

    if (daftarMahasiswa[indeksMhs].ipk < 3.0) {
        daftarSurat[jumlahSurat].statusRekomendasi = -1;
        daftarSurat[jumlahSurat].alasanDitolak = "IPK kurang dari standar (3.0)";
    } else if (sisaHutangKas > 50000) {
        daftarSurat[jumlahSurat].statusRekomendasi = -1;
        daftarSurat[jumlahSurat].alasanDitolak = "Tunggakan kas angkatan > 50.000";
    } else {
        daftarSurat[jumlahSurat].statusRekomendasi = 1;
        daftarSurat[jumlahSurat].alasanDitolak = "-";
    }

    if (daftarSurat[jumlahSurat].statusRekomendasi == 1) cout << "\n[v] SURAT REKOMENDASI APPROVED!\n";
    else cout << "\n[X] REKOMENDASI REJECTED! Alasan: " << daftarSurat[jumlahSurat].alasanDitolak << "\n";
    
    jumlahSurat++;
}

void lihatLogSurat() {
    if (jumlahSurat == 0) { cout << "\n[!] Belum ada pengajuan surat.\n"; return; }
    cout << "\n=======================================================\n";
    cout << "               LOG SURAT REKOMENDASI HIMPUNAN           \n";
    cout << "=======================================================\n";
    for (int i = 0; i < jumlahSurat; i++) {
        cout << "[" << daftarSurat[i].idSurat << "] NIM: " << daftarSurat[i].nimPemohon << " | Event: " << daftarSurat[i].namaEvent;
        if (daftarSurat[i].statusRekomendasi == 1) cout << " | STATUS: APPROVED\n";
        else cout << " | STATUS: REJECTED (" << daftarSurat[i].alasanDitolak << ")\n";
    }
}

void isiKotakAspirasi() {
    if (jumlahAspirasi >= MAX_DATA) { cout << "\n[!] ERROR: Kotak aspirasi penuh!\n"; return; }
    cout << "\n==== KOTAK ASPIRASI & KELUH KESAH ANGKATAN ====";
    daftarAspirasi[jumlahAspirasi].idAspirasi = "ASP-" + to_string(jumlahAspirasi + 1);
    cout << "\nKategori Keluhan (Fasilitas/Dosen/Internal) : "; cin >> daftarAspirasi[jumlahAspirasi].kategori;
    cout << "Detail Keluhan / Aspirasi : "; cin.ignore(); getline(cin, daftarAspirasi[jumlahAspirasi].detailKeluhan);
    cout << "Tingkat Urgensi Masalah (1=Rendah, 2=Sedang, 3=Darurat) : "; cin >> daftarAspirasi[jumlahAspirasi].tingkatUrgensi;
    daftarAspirasi[jumlahAspirasi].statusProgres = 0;

    jumlahAspirasi++;
    cout << "\n[v] Aspirasi berhasil ditampung secara anonim!\n";
}

void prosesAspirasiAdvokasi() {
    if (jumlahAspirasi == 0) { cout << "\n[!] Kotak aspirasi masih kosong!\n"; return; }

    for (int i = 0; i < jumlahAspirasi - 1; i++) {
        int idxMaks = i;
        for (int j = i + 1; j < jumlahAspirasi; j++) {
            if (daftarAspirasi[j].tingkatUrgensi > daftarAspirasi[idxMaks].tingkatUrgensi) {
                idxMaks = j;
            }
        }
        Aspirasi temp = daftarAspirasi[i];
        daftarAspirasi[i] = daftarAspirasi[idxMaks];
        daftarAspirasi[idxMaks] = temp;
    }

    cout << "\n=======================================================\n";
    cout << "          TRIAGE ADVOKASI KELUHAN                        \n";
    cout << "=======================================================\n";
    for (int i = 0; i < jumlahAspirasi; i++) {
        cout << "[" << daftarAspirasi[i].idAspirasi << "] Urgensi: " << daftarAspirasi[i].tingkatUrgensi;
        cout << " | Kategori: " << daftarAspirasi[i].kategori << "\nKeluhan: \"" << daftarAspirasi[i].detailKeluhan << "\"\n";
        cout << "Status Progres: ";
        if (daftarAspirasi[i].statusProgres == 0) cout << "Ditampung\n";
        else if (daftarAspirasi[i].statusProgres == 1) cout << "Mediasi Kampus\n";
        else cout << "Selesai\n";
        cout << "-------------------------------------------------------\n";
    }
}

void editTriageAdvokasi() {
    if (jumlahAspirasi == 0) { cout << "\n[!] Kotak aspirasi masih kosong!\n"; return; }
    
    string cariId;
    cout << "\n==== EDIT STATUS TRIAGE ASPIRASI ====";
    cout << "\nMasukkan ID Aspirasi (Contoh: ASP-1) : "; cin >> cariId;

    bool ketemu = false;
    for (int i = 0; i < jumlahAspirasi; i++) {
        if (daftarAspirasi[i].idAspirasi == cariId) {
            cout << "\nKategori : " << daftarAspirasi[i].kategori;
            cout << "\nDetail Keluhan : " << daftarAspirasi[i].detailKeluhan;
            cout << "\nStatus Saat Ini : " << daftarAspirasi[i].statusProgres << " (0=Ditampung, 1=Mediasi, 2=Selesai)";
            
            cout << "\nUbah Status Menjadi : "; cin >> daftarAspirasi[i].statusProgres;
            cout << "\n[v] Status Aspirasi berhasil diupdate!\n";
            ketemu = true;
            break;
        }
    }
    
    if (!ketemu) {
        cout << "\n[!] ERROR: ID Aspirasi " << cariId << " tidak ditemukan!\n";
    }
}

void exportAspirasiCSV() {
    ofstream fileCsv("advokasi_darurat.csv");
    fileCsv << "ID_Aspirasi,Kategori,Detail_Keluhan,Urgensi\n";
    int counter = 0;
    for (int i = 0; i < jumlahAspirasi; i++) {
        if (daftarAspirasi[i].tingkatUrgensi == 3) {
            fileCsv << daftarAspirasi[i].idAspirasi << "," << daftarAspirasi[i].kategori << "," 
                    << daftarAspirasi[i].detailKeluhan << "," << daftarAspirasi[i].tingkatUrgensi << "\n";
            counter++;
        }
    }
    fileCsv.close();
    cout << "\n[!] Berhasil mengeksport " << counter << " keluhan darurat ke file 'advokasi_darurat.csv'\n";
}

// ---------------------------------
// MENU CREATE, READ, UPDATE, DELETE
// ---------------------------------

void editMahasiswa() {
    if (jumlahMahasiswa == 0) { cout << "\n[!] Database mahasiswa kosong!\n"; return; }
    string inputNim;
    cout << "\n==== EDIT DATA MAHASISWA ====";
    cout << "\nMasukkan NIM yang akan diedit : "; cin >> inputNim;
    
    int idx = binarySearchMhs(inputNim);
    if (idx == -1) {
        cout << "[!] ERROR: Mahasiswa dengan NIM " << inputNim << " tidak ditemukan!\n"; return;
    }
    
    cout << "\nData ditemukan: " << daftarMahasiswa[idx].nama << "\n";
    cout << "Nama Baru : "; cin.ignore(); getline(cin, daftarMahasiswa[idx].nama);
    cout << "IPK Baru : "; cin >> daftarMahasiswa[idx].ipk;
    cout << "Total SKS Baru : "; cin >> daftarMahasiswa[idx].totalSks;
    cout << "Kelompok Studi Baru : "; cin.ignore(); getline(cin, daftarMahasiswa[idx].kelompokStudi);
    cout << "\n[v] Berhasil mengupdate data mahasiswa!\n";
}

void hapusMahasiswa() {
    if (jumlahMahasiswa == 0) { cout << "\n[!] Database mahasiswa kosong!\n"; return; }
    string inputNim;
    cout << "\n==== HAPUS DATA MAHASISWA ====";
    cout << "\nMasukkan NIM yang akan dihapus : "; cin >> inputNim;
    
    int idx = binarySearchMhs(inputNim);
    if (idx == -1) {
        cout << "[!] ERROR: Mahasiswa dengan NIM " << inputNim << " tidak ditemukan!\n"; return;
    }
    
    for (int i = idx; i < jumlahMahasiswa - 1; i++) {
        daftarMahasiswa[i] = daftarMahasiswa[i + 1];
    }
    jumlahMahasiswa--;
    cout << "\n[v] Berhasil menghapus data mahasiswa!\n";
}

int cariIndeksKas(string id) {
    for(int i = 0; i < jumlahKas; i++) {
        if(daftarKas[i].idTransaksi == id) return i;
    }
    return -1;
}

void editKas() {
    if (jumlahKas == 0) { cout << "\n[!] Data kas kosong!\n"; return; }
    string id;
    cout << "\n==== EDIT TRANSAKSI KAS ====";
    cout << "\nMasukkan ID Transaksi (Contoh: KAS-1): "; cin >> id;
    
    int idx = cariIndeksKas(id);
    if (idx == -1) { cout << "[!] Transaksi tidak ditemukan!\n"; return; }
    
    cout << "NIM Pembayar/Penerima Baru : "; cin >> daftarKas[idx].nimPembayar;
    cout << "Nominal Baru : Rp "; cin >> daftarKas[idx].nominal;
    cout << "Jenis Transaksi Baru (D/K) : "; cin >> daftarKas[idx].jenis;
    cout << "Tanggal Baru (DD-MM-YYYY) : "; cin >> daftarKas[idx].tanggal;
    cout << "\n[v] Transaksi berhasil diupdate!\n";
}

void hapusKas() {
    if (jumlahKas == 0) { cout << "\n[!] Data kas kosong!\n"; return; }
    string id;
    cout << "\n==== HAPUS TRANSAKSI KAS ====";
    cout << "\nMasukkan ID Transaksi (Contoh: KAS-1): "; cin >> id;
    
    int idx = cariIndeksKas(id);
    if (idx == -1) { cout << "[!] Transaksi tidak ditemukan!\n"; return; }
    
    for (int i = idx; i < jumlahKas - 1; i++) {
        daftarKas[i] = daftarKas[i + 1];
    }
    jumlahKas--;
    cout << "\n[v] Transaksi berhasil dihapus!\n";
}

int cariIndeksSurat(string id) {
    for(int i = 0; i < jumlahSurat; i++) {
        if(daftarSurat[i].idSurat == id) return i;
    }
    return -1;
}

void hapusSurat() {
    if (jumlahSurat == 0) { cout << "\n[!] Data surat kosong!\n"; return; }
    string id;
    cout << "\n==== HAPUS SURAT REKOMENDASI ====";
    cout << "\nMasukkan ID Surat (Contoh: SR-1): "; cin >> id;
    
    int idx = cariIndeksSurat(id);
    if (idx == -1) { cout << "[!] Surat tidak ditemukan!\n"; return; }
    
    for (int i = idx; i < jumlahSurat - 1; i++) {
        daftarSurat[i] = daftarSurat[i + 1];
    }
    jumlahSurat--;
    cout << "\n[v] Surat rekomendasi berhasil dihapus!\n";
}

int cariIndeksAspirasi(string id) {
    for(int i = 0; i < jumlahAspirasi; i++) {
        if(daftarAspirasi[i].idAspirasi == id) return i;
    }
    return -1;
}

void hapusAspirasi() {
    if (jumlahAspirasi == 0) { cout << "\n[!] Data aspirasi kosong!\n"; return; }
    string id;
    cout << "\n==== HAPUS ASPIRASI ====";
    cout << "\nMasukkan ID Aspirasi (Contoh: ASP-1): "; cin >> id;
    
    int idx = cariIndeksAspirasi(id);
    if (idx == -1) { cout << "[!] Aspirasi tidak ditemukan!\n"; return; }
    
    for (int i = idx; i < jumlahAspirasi - 1; i++) {
        daftarAspirasi[i] = daftarAspirasi[i + 1];
    }
    jumlahAspirasi--;
    cout << "\n[v] Aspirasi berhasil dihapus!\n";
}

// ------------------------------------------
// SUBMENU MENU CREATE, READ, UPDATE, DELETE
// ------------------------------------------

void submenuMahasiswa() {
    int pil;
    do {
        cout << "\n======================================";
        cout << "\n    SUBMENU KELOLA DATA MAHASISWA     ";
        cout << "\n======================================";
        cout << "\n1. Registrasi Mahasiswa Baru";
        cout << "\n2. Edit Data Mahasiswa";
        cout << "\n3. Hapus Data Mahasiswa";
        cout << "\n4. Kembali ke Menu Utama";
        cout << "\nMasukkan pilihan menu : ";
        if (!(cin >> pil)) { cin.clear(); cin.ignore(10000, '\n'); pil = -1; }
        
        switch (pil) {
            case 1: tambahMahasiswa(); break;
            case 2: editMahasiswa(); break;
            case 3: hapusMahasiswa(); break;
            case 4: break;
            default: cout << "\n[!] Pilihan invalid!\n";
        }
    } while (pil != 4);
}

void submenuKas() {
    int pil;
    do {
        cout << "\n======================================";
        cout << "\n        SUBMENU TRANSAKSI KAS         ";
        cout << "\n======================================";
        cout << "\n1. Input Log Transaksi Kas";
        cout << "\n2. Edit Log Transaksi Kas";
        cout << "\n3. Hapus Log Transaksi Kas";
        cout << "\n4. Kembali ke Menu Utama";
        cout << "\nMasukkan pilihan menu : ";
        if (!(cin >> pil)) { cin.clear(); cin.ignore(10000, '\n'); pil = -1; }
        
        switch (pil) {
            case 1: inputCatatanKas(); break;
            case 2: editKas(); break;
            case 3: hapusKas(); break;
            case 4: break;
            default: cout << "\n[!] Pilihan invalid!\n";
        }
    } while (pil != 4);
}

void submenuSurat() {
    int pil;
    do {
        cout << "\n======================================";
        cout << "\n    SUBMENU BIROKRASI & SURAT         ";
        cout << "\n======================================";
        cout << "\n1. Pengajuan Surat (Auto-Vetting)";
        cout << "\n2. Hapus Surat Rekomendasi";
        cout << "\n3. Kembali ke Menu Utama";
        cout << "\nMasukkan pilihan menu : ";
        if (!(cin >> pil)) { cin.clear(); cin.ignore(10000, '\n'); pil = -1; }
        
        switch (pil) {
            case 1: ajukanSuratRekomendasi(); break;
            case 2: hapusSurat(); break;
            case 3: break;
            default: cout << "\n[!] Pilihan invalid!\n";
        }
    } while (pil != 3);
}

void submenuAspirasi() {
    int pil;
    do {
        cout << "\n======================================";
        cout << "\n       SUBMENU KOTAK ASPIRASI         ";
        cout << "\n======================================";
        cout << "\n1. Isi Kotak Aspirasi & Keluh Kesah";
        cout << "\n2. Hapus Data Aspirasi";
        cout << "\n3. Kembali ke Menu Utama";
        cout << "\nMasukkan pilihan menu : ";
        if (!(cin >> pil)) { cin.clear(); cin.ignore(10000, '\n'); pil = -1; }
        
        switch (pil) {
            case 1: isiKotakAspirasi(); break;
            case 2: hapusAspirasi(); break;
            case 3: break;
            default: cout << "\n[!] Pilihan invalid!\n";
        }
    } while (pil != 3);
}

// -------------
// FILE HANDLING
// -------------

void simpanKeFile() {
    ofstream outMhs("database_mahasiswa.txt");
    for (int i = 0; i < jumlahMahasiswa; i++) {
        outMhs << daftarMahasiswa[i].nim << "|" << daftarMahasiswa[i].nama << "|" 
               << daftarMahasiswa[i].ipk << "|" << daftarMahasiswa[i].totalSks << "|" 
               << daftarMahasiswa[i].kelompokStudi << "\n";
    } outMhs.close();

    ofstream outKas("database_kas.txt");
    for (int i = 0; i < jumlahKas; i++) {
        outKas << daftarKas[i].idTransaksi << "|" << daftarKas[i].nimPembayar << "|"
               << daftarKas[i].nominal << "|" << daftarKas[i].jenis << "|"
               << daftarKas[i].tanggal << "\n";
    } outKas.close();

    ofstream outSurat("database_surat.txt");
    for (int i = 0; i < jumlahSurat; i++) {
        outSurat << daftarSurat[i].idSurat << "|" << daftarSurat[i].nimPemohon << "|"
                 << daftarSurat[i].namaEvent << "|" << daftarSurat[i].tingkatan << "|"
                 << daftarSurat[i].statusRekomendasi << "|" << daftarSurat[i].alasanDitolak << "\n";
    } outSurat.close();

    ofstream outAsp("database_aspirasi.txt");
    for (int i = 0; i < jumlahAspirasi; i++) {
        outAsp << daftarAspirasi[i].idAspirasi << "|" << daftarAspirasi[i].kategori << "|"
               << daftarAspirasi[i].detailKeluhan << "|" << daftarAspirasi[i].tingkatUrgensi << "|"
               << daftarAspirasi[i].statusProgres << "\n";
    } outAsp.close();

    cout << "\n[Backup] Seluruh data berhasil diamankan ke sistem database.\n";
}

void loadDariFile() {
    ifstream inMhs("database_mahasiswa.txt");
    if (inMhs) {
        while (jumlahMahasiswa < MAX_DATA && getline(inMhs, daftarMahasiswa[jumlahMahasiswa].nim, '|')) {
            getline(inMhs, daftarMahasiswa[jumlahMahasiswa].nama, '|');
            inMhs >> daftarMahasiswa[jumlahMahasiswa].ipk; inMhs.ignore(); 
            inMhs >> daftarMahasiswa[jumlahMahasiswa].totalSks; inMhs.ignore(); 
            getline(inMhs, daftarMahasiswa[jumlahMahasiswa].kelompokStudi); 
            jumlahMahasiswa++;
        }
        inMhs.close();
    }

    ifstream inKas("database_kas.txt");
    if (inKas) {
        while (jumlahKas < MAX_DATA && getline(inKas, daftarKas[jumlahKas].idTransaksi, '|')) {
            getline(inKas, daftarKas[jumlahKas].nimPembayar, '|');
            inKas >> daftarKas[jumlahKas].nominal; inKas.ignore();
            inKas >> daftarKas[jumlahKas].jenis; inKas.ignore();
            getline(inKas, daftarKas[jumlahKas].tanggal);
            jumlahKas++;
        }
        inKas.close();
    }

    ifstream inSurat("database_surat.txt");
    if (inSurat) {
        while (jumlahSurat < MAX_DATA && getline(inSurat, daftarSurat[jumlahSurat].idSurat, '|')) {
            getline(inSurat, daftarSurat[jumlahSurat].nimPemohon, '|');
            getline(inSurat, daftarSurat[jumlahSurat].namaEvent, '|');
            getline(inSurat, daftarSurat[jumlahSurat].tingkatan, '|');
            inSurat >> daftarSurat[jumlahSurat].statusRekomendasi; inSurat.ignore();
            getline(inSurat, daftarSurat[jumlahSurat].alasanDitolak);
            jumlahSurat++;
        }
        inSurat.close();
    }

    ifstream inAsp("database_aspirasi.txt");
    if (inAsp) {
        while (jumlahAspirasi < MAX_DATA && getline(inAsp, daftarAspirasi[jumlahAspirasi].idAspirasi, '|')) {
            getline(inAsp, daftarAspirasi[jumlahAspirasi].kategori, '|');
            getline(inAsp, daftarAspirasi[jumlahAspirasi].detailKeluhan, '|');
            inAsp >> daftarAspirasi[jumlahAspirasi].tingkatUrgensi; inAsp.ignore();
            inAsp >> daftarAspirasi[jumlahAspirasi].statusProgres; inAsp.ignore(); 
            jumlahAspirasi++;
        }
        inAsp.close();
    }
}
// ---------
// MAIN MENU
// ---------
int main() {
    loadDariFile();
    
    int role = loginSystem();
    if (role == 0) {
        cout << "\n[!] Akses Ditolak. Program berhenti.\n";
        return 0;
    }

    int men;
    // MENU ADMIN
    if (role == 1) {
        do {
            cout << "\n======================================================";
            cout << "\n        DASHBOARD PENGURUS ANGKATAN-25          ";
            cout << "\n======================================================";
            cout << "\n[MODUL MAHASISWA]";
            cout << "\n1. Kelola Data Mahasiswa";
            cout << "\n2. Tampilkan Data Angkatan";
            cout << "\n3. Cari Bakat Delegasi Lomba";
            cout << "\n4. Cari Mahasiswa";
            cout << "\n[MODUL KEUANGAN]";
            cout << "\n5. Kelola Log Transaksi Kas";
            cout << "\n6. Cek Daftar Tunggakan Uang Kas";
            cout << "\n[MODUL BIROKRASI]";
            cout << "\n7. Kelola Pengajuan Surat Rekomendasi";
            cout << "\n8. Tampilkan Log Surat Rekomendasi";
            cout << "\n[MODUL ADVOKASI]";
            cout << "\n9. Kelola Kotak Aspirasi";
            cout << "\n10. Proses Triage Advokasi";
            cout << "\n11. Edit Status Triage Advokasi";
            cout << "\n12. Export Keluhan DARURAT ke Excel";
            cout << "\n------------------------------------------------------";
            cout << "\n13. Simpan Data & Keluar";
            cout << "\nMasukkan pilihan menu : ";
            
            if (!(cin >> men)) {
                cin.clear();
                cin.ignore(10000, '\n');
                men = -1;
            }

            switch (men) {
                case 1: submenuMahasiswa(); break;
                case 2: tampilkanAnalytics(); break;
                case 3: cariBakatFilter(); break;
                case 4: cariMahasiswa(); break;
                case 5: submenuKas(); break;
                case 6: cekTunggakanKas(); break;
                case 7: submenuSurat(); break;
                case 8: lihatLogSurat(); break;
                case 9: submenuAspirasi(); break;
                case 10: prosesAspirasiAdvokasi(); break;
                case 11: editTriageAdvokasi(); break;
                case 12: exportAspirasiCSV(); break;
                case 13: simpanKeFile(); break;
                default: cout << "\n[!] Pilihan invalid!\n";
            }
        } while (men != 13);
    } 
    // ================= MENU KHUSUS ANGGOTA =================
    else if (role == 2) {
        do {
            cout << "\n======================================================";
            cout << "\n      PORTAL MAHASISWA INFORMATIKA ANGKATAN-25      ";
            cout << "\n======================================================";
            cout << "\n1. Tampilkan Data Mahasiswa";
            cout << "\n2. Cari Mahasiswa";
            cout << "\n3. Pengajuan Surat Rekomendasi Himpunan";
            cout << "\n4. Lihat Status Surat Rekomendasi Saya";
            cout << "\n5. Isi Kotak Aspirasi & Keluh Kesah";
            cout << "\n6. Lihat Antrean Advokasi Aspirasi";
            cout << "\n------------------------------------------------------";
            cout << "\n7. Simpan Input & Keluar";
            cout << "\nMasukkan pilihan menu : ";
            
            if (!(cin >> men)) {
                cin.clear();
                cin.ignore(10000, '\n');
                men = -1;
            }

            switch (men) {
                case 1: tampilkanAnalytics(); break;
                case 2: cariMahasiswa(); break;
                case 3: ajukanSuratRekomendasi(); break;
                case 4: lihatLogSurat(); break;
                case 5: isiKotakAspirasi(); break;
                case 6: prosesAspirasiAdvokasi(); break;
                case 7: simpanKeFile(); break;
                default: cout << "\n[!] Pilihan invalid!\n";
            }
        } while (men != 7);
    }

    return 0;
}
