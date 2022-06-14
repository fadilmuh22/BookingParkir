#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "util.hpp"
#include "data.hpp"

using namespace std;

// ? Inisialisasi data
// ? List tempat parkir dan List User menggunakan library vector agar dapat
// membuat array dinamis
vector<TempatParkir> listTempatParkir;
vector<User> listUserParkir;

void checkWaitlist(int indexTempat, int jenisKendaraan)
{
	if (listTempatParkir[indexTempat].waitlist != NULL)
	{
		NodeUser *temp = NULL;
		temp = listTempatParkir[indexTempat].waitlist;
		while (temp != NULL)
		{
			listUserParkir.push_back(temp->data);

			deleteAtNodeUser(&listTempatParkir[indexTempat], temp->data);
			listTempatParkir[indexTempat].kapasitasTersedia[jenisKendaraan] = listTempatParkir[indexTempat].kapasitasTersedia[jenisKendaraan] - 1;
			temp = temp->next;
		}

		cout << "\n User di Waiting List " << listTempatParkir[indexTempat].nama << " berhasil dipindahkan ke list booking";
	}
}

int getTempatIndex(int id)
{
	int found = -1;
	for (int i = 0; i < listTempatParkir.size(); i++)
	{
		if (listTempatParkir[i].id == id)
		{
			found = i;
			break;
		}
	}
	return found;
}

int getUserIndex(int id)
{
	int found = -1;
	for (int i = 0; i < listUserParkir.size(); i++)
	{
		if (listUserParkir[i].id == id)
		{
			found = i;
			break;
		}
	}
	return found;
}

void semuaTempat()
{
	cout << "\nList Semua Tempat Parkir\n";
	for (int i = 0; i < listTempatParkir.size(); i++)
	{
		cout << i + 1 << ".\t" << listTempatParkir[i].toString() << "\n";
	}
}

void cariTempat()
{
	string cari;
	cout << "Masukan tempat yang dicari (nama/lokasi) : ";
	cin >> cari;

	cout << "\nHasil Pencarian Tempat Parkir\n";
	for (int i = 0; i < listTempatParkir.size(); i++)
	{
		string lokasiNama =
			toLower(listTempatParkir[i].lokasi + listTempatParkir[i].nama);

		// string.find mencari string jika ditemukan value nya tidak sama dengan
		// string::npos (akhir dari string)
		if (lokasiNama.find(toLower(cari)) != string::npos)
		{
			cout << i + 1 << "\t" << listTempatParkir[i].toString() << "\n";
		}
	}
}

void daftarTempat()
{
	int pilihan;
	cout << "\nDaftar tempat parkir\n";
	cout << "1.\tTampilkan Semua\n";
	cout << "2.\tCari dengan nama tempat atau lokasi\n";

	pilihan = inputNumber("Pilihan : ", 1, 2);

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

	cout << "\nCopy ID tempat parkir untuk booking\n";
}

void bookTempat()
{
	int id;
	cout << "\nMasukan ID Tempat yang ingin di book : ";
	cin >> id;

	int indexTempat = getTempatIndex(id);
	if (indexTempat == -1)
	{
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
		0)
	{
		string confirm;
		cout << "\nKapasitas Parkir di " << listTempatParkir[indexTempat].nama
			 << " sudah penuh";
		cout << "\nApakah anda ingin masuk Waiting List? (y/t) ";
		cin >> confirm;
		if (toLower(confirm) == "y")
		{
			insertLastNodeUser(&listTempatParkir[indexTempat], newUser);
			cout << "\nUser telah dimasukan ke Waiting List";
		}
		else
		{
			cout << "\nBooking parkir gagal";
		}
	}
	else
	{

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

void cekStatus()
{
	int pilihan;
	cout << "Cek Status\n";
	cout << "1.\tTempat\n";
	cout << "2.\tID parkir User\n";

	pilihan = inputNumber("Pilihan : ", 1, 2);

	switch (pilihan)
	{
	case 1:
	{
		int id;
		cout << "\nMasukan ID Tempat Parkir : ";
		cin >> id;

		int indexTempat = getTempatIndex(id);
		if (indexTempat == -1)
		{
			cout << "\nID tempat tidak ditemukan";
			return;
		}

		cout << "1.\t" << listTempatParkir[indexTempat].toString();

		cout << "\nList User Parkir\n";
		for (int i = 0; i < listUserParkir.size(); i++)
		{
			if (listUserParkir[i].idTempat == id)
			{
				cout << i + 1 << ".\t" << listUserParkir[i].toString() << "\n";
			}
		}

		viewNodeUser(&listTempatParkir[indexTempat]);

		break;
	}
	case 2:
	{
		int id;
		cout << "\nMasukan ID User : ";
		cin >> id;

		int indexUser = getUserIndex(id);
		if (indexUser == -1)
		{
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

void checkOut()
{
	int id;
	cout << "\nMasukan ID parkir User yang ingin di Check Out : ";
	cin >> id;

	int indexUser = getUserIndex(id);
	if (indexUser == -1)
	{
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

	checkWaitlist(indexTempat, listUserParkir[indexUser].jenisKendaraan);
}

void pindahParkir()
{
	bool isWaitlist = false;
	int idUser;
	cout << "\nMasukan ID parkir User yang ingin di Check Out : ";
	cin >> idUser;

	int indexUser = getUserIndex(idUser);
	if (indexUser == -1)
	{
		cout << "\nID User tidak ditemukan";
		return;
	}
	User *userParkir = &listUserParkir[indexUser];
	cout << "\n1.\t" << userParkir->toString();

	int indexTempat = getTempatIndex(userParkir->idTempat);
	TempatParkir *parkirLama = &listTempatParkir[indexTempat];
	vector<int> destinasiBaru = pindahParkirData.cariPindah(indexTempat);

	if (destinasiBaru.size() == 0)
	{
		cout << "\nTidak ada tempat parkir lain yang dapat dituju\n";
		return;
	}

	cout << "\nList tempat parkir yang dapat dituju\n";
	int countTempatBaru = 0;
	for (int i = 0; i < listTempatParkir.size(); i++)
	{
		if (find(destinasiBaru.begin(), destinasiBaru.end(), listTempatParkir[i].id) != destinasiBaru.end())
		{
			cout << ++countTempatBaru << ".\t" << listTempatParkir[i].toString() << "\n";
		}
	}

	int idTempat = inputNumberFromArray("\nMasukan ID Tempat parkir baru : ", destinasiBaru);

	int indexTempatBaru = getTempatIndex(idTempat);
	if (indexTempatBaru == -1)
	{
		cout << "\nID tempat tidak ditemukan";
		return;
	}

	TempatParkir *parkirBaru = &listTempatParkir[indexTempatBaru];
	if (parkirLama->kapasitasTersedia[userParkir->jenisKendaraan] == 0)
	{

		string confirm;
		cout << "\nKapasitas Parkir di " << parkirBaru->nama
			 << " sudah penuh ";
		cout << "\nApakah anda ingin masuk Waiting List? (y/t) ";
		cin >> confirm;
		if (toLower(confirm) == "y")
		{
			insertLastNodeUser(parkirBaru, *userParkir);
			cout << "\nUser telah dimasukan ke Waiting List";
		}
		else
		{
			cout << "\nBooking parkir gagal";
		}

		parkirLama->kapasitasTersedia[userParkir->jenisKendaraan] = parkirLama->kapasitasTersedia[userParkir->jenisKendaraan] + 1;
	}
	else
	{
		parkirBaru->kapasitasTersedia[userParkir->jenisKendaraan] = parkirBaru->kapasitasTersedia[userParkir->jenisKendaraan] - 1;

		userParkir->id = genId();
		userParkir->mulaiParkir = time(NULL);
		userParkir->idTempat = idTempat;

		checkWaitlist(indexTempat, userParkir->jenisKendaraan);

		cout << "\nPindah Tempat parkir berhasil dengan User : \n\t"
			 << userParkir->toString();

		parkirLama->kapasitasTersedia[userParkir->jenisKendaraan] = parkirLama->kapasitasTersedia[userParkir->jenisKendaraan] + 1;
	}
}

void initData()
{
	listTempatParkir = {
		TempatParkir(0, "Parkir Lapangan A", 2, 1, 2000, 5000, "UPI Cibiru"),
		TempatParkir(1, "Parkir Lapangan B", 30, 10, 2000, 5000, "UPI Cibiru"),
		TempatParkir(2, "Parkir Lapangan C", 20, 10, 2000, 5000, "UPI CIBIRU"),
		TempatParkir(3, "Parkir Pohon Rindang A", 10, 5, 2000, 5000, "UPI Cibiru"),
		TempatParkir(4, "Parkir Pohon Rindang B", 10, 5, 2000, 5000, "UPI Cibiru"),
		TempatParkir(5, "Parkir Pohon Rindang C", 10, 5, 2000, 5000, "UPI Cibiru"),
		TempatParkir(6, "Parkir Mahasiswa", 50, 10, 2000, 5000, "UPI Cibiru"),
		TempatParkir(7, "Parkir Dosen", 50, 10, 2000, 5000, "UPI Cibiru"),
		TempatParkir(8, "Parkir Tamu A", 20, 5, 2000, 5000, "UPI Cibiru"),
		TempatParkir(9, "Parkir Tamu B", 20, 5, 2000, 5000, "UPI Cibiru"),
	};

	pindahParkirData.initPindahParkir();
}

void pilihMenu()
{
	int pilihanMenu;

	clearscr();
	cout << "\n\n=============================\n";
	cout << "\nBooking Parkir - Kelompok 1 - 2B\n";
	cout << "\nDiwa Prasetyo - 2103802";
	cout << "\nGenthur Teges A - 2100176";
	cout << "\nMuhamad Fadil - 2109994";
	cout << "\nRifki Fauzifazr - 2107481";
	cout << "\n\nPilih Menu (1-5)";
	cout << "\n1. Daftar Tempat\n2. Book Tempat\n3. Cek Out\n4. Cek Status\n5. Pindah Parkir\n6. Keluar\n";
	pilihanMenu = inputNumber("Pilihan : ", 1, 6);
	cin.ignore(256, '\n');
	cout << "\n=============================\n\n";

	clearscr();

	switch (pilihanMenu)
	{
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
	case 5:
		pindahParkir();
		break;
	default:
		return;
	}

	pausescr();

	pilihMenu();
}

int main()
{
	initData();
	pilihMenu();
}