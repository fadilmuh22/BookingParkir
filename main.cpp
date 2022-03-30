#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

int genId();

struct TempatParkir {
    int id;
    string nama;
    int kapasitasTotal[2] = {0, 0};
    int kapasitasTersedia[2] = {0, 0};
    int hargaPerjam[2] = {0, 0};
    string lokasi;

    TempatParkir(){};

	TempatParkir(int id_, string nama_, int kapasitasTotal1, int kapasitasTotal2, int hargaPerjam1, int hargaPerjam2, string lokasi_) {
		id = id_;
        nama = nama_;
        
        kapasitasTotal[0] = kapasitasTotal1;
        kapasitasTotal[1] = kapasitasTotal2;
        
        kapasitasTersedia[0] = kapasitasTotal1;
        kapasitasTersedia[1] = kapasitasTotal2;
        
        hargaPerjam[0] = hargaPerjam1;
        hargaPerjam[1] = hargaPerjam2;
        
        lokasi = lokasi_;
	}
};

struct User {
    int id;
    string nama;
    int jenisKendaraan;
    int lama;
    int idTempat;

    User(){};

    User(int id_, string nama_, int lama_, int idTempat_) {
        id = id_;
        nama = nama_;
        lama = lama_;
        idTempat = idTempat_;
    }
};

vector<TempatParkir> listTempatParkir {
    TempatParkir(genId(), "Parkir Bec0", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(genId(), "Parkir Bec1", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(genId(), "Parkir Bec2", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(genId(), "Parkir Bec3", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(genId(), "Parkir Bec4", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(genId(), "Parkir AS0", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(genId(), "Parkir AS1", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(genId(), "Parkir AS2", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(genId(), "Parkir AS3", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(genId(), "Parkir AS4", 100, 100, 4000, 10000, "Jakarta"),
};

vector<User> listUser;

void clearscr() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

void pausescr() {
    cin.ignore(256, '\n');
    string dummy;
    cout << "\n\nEnter to continue...";
    getline(cin, dummy);
}

// input angka
int inputNumber(string message, int min, int max) {
    int input;
    string inputStr;
    bool inputValid = false;

    while (!inputValid) {
        cout << message;
        cin >> inputStr;

        try {
            input = stoi(inputStr);
            if ((input >= min) && (input <= max)) {
                inputValid = true;
            } else {
                cout << "Inputan tidak sesuai, angka(" << min << ", " << max << ")\n";
            }
        }catch (const exception& e) {
            cout << "Inputan tidak sesuai, angka(" << min << ", " << max << ")\n";
        }
    }

    return input;
}

const string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int genId() {
    return time(NULL);
}

void semuaTempat() {
    
}

void cariTempat() {
    
}

void daftarTempat() {
    int pilihan;
    cout << "Daftar tempat parkir\n";
    cout << "1.\tTampilkan Semua\n";
    cout << "2.\tCari dengan nama tempat atau lokasi\n";
    
    pilihan = inputNumber("Pilihan : ", 1, 3);

    switch (pilihan)
    {
    case 1:
        semuaTempat();
        break;
    case 2:
        cariTempat();
        break;
    default:
        return;
    }
}


void cekStatus() {
    
}

void pilihMenu()
{
    int pilihanMenu;

    clearscr();
    cout << "\n\n=============================\n";
    cout << "Muhamad Fadil – 2109994 – 2B\n\n";
    cout << "Pilih Menu (1-2)\n";
    cout << "1. Daftar Tempat\n2. Cek Status\n3. Keluar\n";
    pilihanMenu = inputNumber("Pilihan : ", 1, 3);
    cin.ignore(256, '\n');
    cout << "\n=============================\n\n";

    clearscr();

    switch (pilihanMenu)
    {
    case 1:
        daftarTempat();
        break;
    case 2:
        cekStatus();
        break;
    default:
        return;
    }

    pausescr();

    pilihMenu();
}

int main() {
    srand (time(NULL));
    pilihMenu();
}