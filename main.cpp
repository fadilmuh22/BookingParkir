#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

// untuk mengubah string ke lower case
#include <algorithm>
#include <cctype>

using namespace std;

int genId();
int hourDiff(int from, int to);
string currentDateTime(time_t time);
string toLower(string str);

struct User {
  int id;
  string nama;
  int jenisKendaraan;
  time_t mulaiParkir;
  int lama = 0;
  int idTempat;
  int tarif;

  User(){};

  // Constructor memudahkan buat inisialisasi struct
  User(string nama_, int lama_, int idTempat_) {
    id = genId();
    nama = nama_;
    mulaiParkir = time(NULL);
    lama = lama_;
    idTempat = idTempat_;
  }

  int lamaParkir() { return hourDiff((int)mulaiParkir, time(NULL)); }

  // toString memudahkan menampilkan value struct dengan me return string yang
  // sudah di format dengan value structnya
  string toString() {
    return "ID : " + to_string(id) + "\n\tNama : " + nama +
           "\n\tJenis Kendaraan : " +
           (jenisKendaraan == 0 ? "Motor" : "Mobil") +
           "\n\tMulai Parkir : " + currentDateTime(mulaiParkir) +
           "\n\tLama Parkir : " + to_string(lama) + " jam" +
           "\n\tLama Parkir (sekarang) : " + to_string(lamaParkir()) + " jam" +
           "\n\tID Tempat : " + to_string(idTempat) +
           "\n\tDengan Tarif : Rp. " + to_string(tarif) + "\n";
  }
};

struct NodeUser {
  User data;
  NodeUser *next = NULL;
};

struct TempatParkir {
  int id;
  string nama;

  // ? Kapasitas dan harga menggunakan array yang panjangnya 2 untuk membedakan
  // motor dan mobile {motor, mobil}
  int kapasitasTotal[2] = {0, 0};
  int kapasitasTersedia[2] = {0, 0};
  int hargaPerjam[2] = {0, 0};

  string lokasi;

  NodeUser *waitlist = NULL;

  TempatParkir(){};

  TempatParkir(int id_, string nama_, int kapasitasTotal1, int kapasitasTotal2,
               int hargaPerjam1, int hargaPerjam2, string lokasi_) {
    id = id_;
    nama = nama_;

    kapasitasTotal[0] = kapasitasTotal1;
    kapasitasTotal[1] = kapasitasTotal2;

    kapasitasTersedia[0] = kapasitasTotal1;
    kapasitasTersedia[1] = kapasitasTotal2;

    hargaPerjam[0] = hargaPerjam1;
    hargaPerjam[1] = hargaPerjam2;

    lokasi = lokasi_;
  };

  string toString() {
    return "ID : " + to_string(id) + "\n\tNama : " + nama +
           "\n\tKapasitas Total Motor : " + to_string(kapasitasTotal[0]) +
           " (tersedia " + to_string(kapasitasTersedia[0]) + ")" +
           "\n\tKapasitas Total Mobil : " + to_string(kapasitasTotal[1]) +
           " (tersedia " + to_string(kapasitasTersedia[1]) + ")" +
           "\n\tLokasi : " + lokasi +
           "\n\tTarif Perjam Motor : " + to_string(hargaPerjam[0]) +
           "\n\tTarif Perjam Mobil : " + to_string(hargaPerjam[1]) + "\n";
  }
};

// ? Inisialisasi data
// ? List tempat parkir dan List User menggunakan library vector agar dapat
// membuat array dinamis
vector<TempatParkir> listTempatParkir{
    TempatParkir(0, "Parkir Bec0", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(1, "Parkir Bec1", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(2, "Parkir Bec2", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(3, "Parkir Bec3", 1, 2, 2000, 5000, "Bandung"),
    TempatParkir(4, "Parkir Bec4", 100, 100, 2000, 5000, "Bandung"),
    TempatParkir(5, "Parkir AS0", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(6, "Parkir AS1", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(7, "Parkir AS2", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(8, "Parkir AS3", 100, 100, 4000, 10000, "Jakarta"),
    TempatParkir(9, "Parkir AS4", 100, 100, 4000, 10000, "Jakarta"),
};

vector<User> listUserParkir;

// Membuat string menjadi lower case dengan fungsi dari <cctype> tolower dan
// fungsi dari <algorithm> transform
string toLower(string str) {
  string newstr = str;
  transform(newstr.begin(), newstr.end(), newstr.begin(), ::tolower);
  return newstr;
}

// clearscr membersihkan console sesuai dengan OS
void clearscr() {
  // #ifdef WINDOWS
  // system("cls");
  // #else
  system("clear");
  // #endif
}

void pausescr() {
  cin.ignore(256, '\n');
  string dummy;
  cout << "\n\nEnter to continue...";
  getline(cin, dummy);
}

// ? input angka dengan validasi
int inputNumber(string message, int min, int max) {
  int input;
  string inputStr;
  bool inputValid = false;

  while (!inputValid) {
    cout << message;
    cin >> inputStr;

    // try-catch buat nangkep error dari stoi
    // kalo berhasil inputValid = true
    try {
      input = stoi(inputStr);
      if ((input >= min) && (input <= max)) {
        inputValid = true;
      } else {
        cout << "Inputan tidak sesuai, angka(" << min << ", " << max << ")\n";
      }
    } catch (const exception &e) {
      cout << "Inputan tidak sesuai, angka(" << min << ", " << max << ")\n";
    }
  }

  return input;
}

// currentDateTime output string tanggal dengan format
string currentDateTime(time_t time) {
  time_t now = time;
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

  return buf;
}

// hourDiff menghitung selisih jam
int hourDiff(int from, int to) { return (to - from) / 3600; }

// genId membuat ID unique dari waktu yang menggunakan detik
int genId() { return time(NULL); }

void viewNodeUser(int indexTempat) {
  if (listTempatParkir[indexTempat].waitlist != NULL) {
    NodeUser *temp;
    int count = 0;
    temp = listTempatParkir[indexTempat].waitlist;
    cout << "\n===== Data Waiting List =====" << endl;
    while (temp != NULL) {
      cout << ++count << ".\t" << temp->data.toString();
      temp = temp->next;
    }
  }
}

void insertLastNodeUser(int indexTempat, User user) {
  NodeUser *newNode;
  NodeUser *temp;
  newNode = new NodeUser;
  newNode->data = user;
  newNode->next = NULL;

  if (listTempatParkir[indexTempat].waitlist == NULL) {
    listTempatParkir[indexTempat].waitlist = newNode;
    listTempatParkir[indexTempat].waitlist->next = NULL;
  } else {
    temp = listTempatParkir[indexTempat].waitlist;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void deleteAtNodeUser(int indexTempat, User user) {
  NodeUser *prev = NULL;
  NodeUser *temp = listTempatParkir[indexTempat].waitlist;

  if (listTempatParkir[indexTempat].waitlist == NULL) {
    return;
  }

  if (listTempatParkir[indexTempat].waitlist->data.id == user.id) {
    listTempatParkir[indexTempat].waitlist = temp->next;
    delete temp;
    return;
  }

  while (temp != NULL && temp->data.id != user.id) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL)
    return;

  prev->next = temp->next;

  delete temp;
}

int getTempatIndex(int id) {
  int found = -1;
  for (int i = 0; i < listTempatParkir.size(); i++) {
    if (listTempatParkir[i].id == id) {
      found = i;
      break;
    }
  }
  return found;
}

int getUserIndex(int id) {
  int found = -1;
  for (int i = 0; i < listUserParkir.size(); i++) {
    if (listUserParkir[i].id == id) {
      found = i;
      break;
    }
  }
  return found;
}

void semuaTempat() {
  cout << "\nList Semua Tempat Parkir\n";
  for (int i = 0; i < listTempatParkir.size(); i++) {
    cout << i + 1 << ".\t" << listTempatParkir[i].toString() << "\n";
  }
}

void cariTempat() {
  string cari;
  cout << "Masukan tempat yang dicari (nama/lokasi) : ";
  cin >> cari;

  cout << "\nHasil Pencarian Tempat Parkir\n";
  for (int i = 0; i < listTempatParkir.size(); i++) {
    string lokasiNama =
        toLower(listTempatParkir[i].lokasi + listTempatParkir[i].nama);

    // string.find mencari string jika ditemukan value nya tidak sama dengan
    // string::npos (akhir dari string)
    if (lokasiNama.find(toLower(cari)) != string::npos) {
      cout << i + 1 << "\t" << listTempatParkir[i].toString() << "\n";
    }
  }
}

void daftarTempat() {
  int pilihan;
  cout << "\nDaftar tempat parkir\n";
  cout << "1.\tTampilkan Semua\n";
  cout << "2.\tCari dengan nama tempat atau lokasi\n";

  pilihan = inputNumber("Pilihan : ", 1, 2);

  switch (pilihan) {
  case 1:
    semuaTempat();
    break;
  case 2:
    cariTempat();
    break;
  default:
    return;
  }

  cout << "\nCopy ID tempat parkir untuk booking\n";
}

void bookTempat() {
  int id;
  cout << "\nMasukan ID Tempat yang ingin di book : ";
  cin >> id;

  int indexTempat = getTempatIndex(id);
  if (indexTempat == -1) {
    cout << "\nID tempat tidak ditemukan";
    return;
  }

  User newUser;
  newUser.id = genId();
  newUser.mulaiParkir = time(NULL);
  newUser.idTempat = id;

  cout << "\nMasukan nama : ";
  cin >> newUser.nama;
  newUser.jenisKendaraan =
      inputNumber("\nMasukan jenis kendaraan (motor :  0, mobil : 1) : ", 0, 1);
  newUser.lama = inputNumber("\nMasukan lama parkir (per jam) : ", 1, 12);
  newUser.tarif =
      newUser.lama *
      listTempatParkir[indexTempat].hargaPerjam[newUser.jenisKendaraan];

  // Pengecekan kapasitas parkir sesuai dengan kendaraan user
  if (listTempatParkir[indexTempat].kapasitasTersedia[newUser.jenisKendaraan] ==
      0) {
    string confirm;
    cout << "\nKapasitas Parkir di " << listTempatParkir[indexTempat].nama
         << " sudah penuh";
    cout << "\nApakah anda ingin masuk Waiting List? (y/t) ";
    cin >> confirm;
    if (toLower(confirm) == "y") {
      insertLastNodeUser(indexTempat, newUser);
      cout << "\nUser telah dimasukan ke Waiting List";
    } else {
      cout << "\nBooking parkir gagal";
    }
  } else {

    // push_back bawaan dari vector buat nambah element baru di vector
    listUserParkir.push_back(newUser);
    listTempatParkir[indexTempat].kapasitasTersedia[newUser.jenisKendaraan] =
        listTempatParkir[indexTempat]
            .kapasitasTersedia[newUser.jenisKendaraan] -
        1;

    cout << "\nBooking parkir berhasil dengan User : \n\t"
         << newUser.toString();
  }
}

void cekStatus() {
  int pilihan;
  cout << "Cek Status\n";
  cout << "1.\tTempat\n";
  cout << "2.\tID parkir User\n";

  pilihan = inputNumber("Pilihan : ", 1, 2);

  switch (pilihan) {
  case 1: {
    int id;
    cout << "\nMasukan ID Tempat Parkir : ";
    cin >> id;

    int indexTempat = getTempatIndex(id);
    if (indexTempat == -1) {
      cout << "\nID tempat tidak ditemukan";
      return;
    }

    cout << "1.\t" << listTempatParkir[indexTempat].toString();

    cout << "\nList User Parkir\n";
    for (int i = 0; i < listUserParkir.size(); i++) {
      if (listUserParkir[i].idTempat == id) {
        cout << i + 1 << ".\t" << listUserParkir[i].toString() << "\n";
      }
    }

    viewNodeUser(indexTempat);

    break;
  }
  case 2: {
    int id;
    cout << "\nMasukan ID User : ";
    cin >> id;

    int indexUser = getUserIndex(id);
    if (indexUser == -1) {
      cout << "\nID User tidak ditemukan";
      return;
    }

    cout << "\n1.\t" << listUserParkir[indexUser].toString();
    break;
  }
  default:
    return;
  }
}

void checkOut() {
  int id;
  cout << "\nMasukan ID parkir User yang ingin di Check Out : ";
  cin >> id;

  int indexUser = getUserIndex(id);
  if (indexUser == -1) {
    cout << "\nID User tidak ditemukan";
    return;
  }

  cout << "\n1.\t" << listUserParkir[indexUser].toString();

  int indexTempat = getTempatIndex(listUserParkir[indexUser].idTempat);

  // Menambah kapasitasTersedia di tempat parkir
  // Buat variable kapasitasTersediaBaru untuk memudahkan pemanggilan
  int kapasitasTersediaBaru =
      listTempatParkir[indexTempat]
          .kapasitasTersedia[listUserParkir[indexUser].jenisKendaraan] +
      1;
  listTempatParkir[indexTempat]
      .kapasitasTersedia[listUserParkir[indexUser].jenisKendaraan] =
      kapasitasTersediaBaru;

  // push_back bawaan dari vector buat hapus element di vector
  // memakai begin() + index yang ingin dihapus
  listUserParkir.erase(listUserParkir.begin() + indexUser);

  cout << "\nID parkir User dengan ID " << id << " Berhasil di Checkout!";

  if (listTempatParkir[indexTempat].waitlist != NULL) {
    NodeUser *temp = NULL;
    int count = 0;
    temp = listTempatParkir[indexTempat].waitlist;
    while (temp != NULL && count < kapasitasTersediaBaru) {
      ++count;
      listUserParkir.push_back(temp->data);

      deleteAtNodeUser(indexTempat, temp->data);
      listTempatParkir[indexTempat]
          .kapasitasTersedia[listUserParkir[indexUser].jenisKendaraan] =
          kapasitasTersediaBaru - 1;
      temp = temp->next;
    }

    cout << "\n"
         << count
         << " User di Waiting List berhasil dipindahkan ke list booking";
  }
}

void pilihMenu() {
  int pilihanMenu;

  clearscr();
  cout << "\n\n=============================\n";
  cout << "\nBooking Parkir - Kelompok 1 - 2B";
  cout << "\nDiwa Prasetyo – 2103802";
  cout << "\nGenthur Teges A – 2100176";
  cout << "\nMuhamad Fadil – 2109994";
  cout << "\nRifki Fauzifazr – 2107481";
  cout << "\n\nPilih Menu (1-5)";
  cout << "\n1. Daftar Tempat\n2. Book Tempat\n3. Cek Out\n4. Cek Status\n5. "
          "Keluar\n";
  pilihanMenu = inputNumber("Pilihan : ", 1, 5);
  cin.ignore(256, '\n');
  cout << "\n=============================\n\n";

  clearscr();

  switch (pilihanMenu) {
  case 1:
    daftarTempat();
    break;
  case 2:
    bookTempat();
    break;
  case 3:
    checkOut();
    break;
  case 4:
    cekStatus();
    break;
  default:
    return;
  }

  pausescr();

  pilihMenu();
}

int main() { pilihMenu(); }
