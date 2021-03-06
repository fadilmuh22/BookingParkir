#ifndef data_hpp
#define data_hpp

#include <iostream>

#include "util.hpp"

using namespace std;

struct User
{
    int id;
    string nama;
    int jenisKendaraan;
    time_t mulaiParkir;
    int lama = 0;
    int idTempat;
    int tarif;

    User(){};

    // Constructor memudahkan buat inisialisasi struct
    User(string nama_, int lama_, int idTempat_)
    {
        id = genId();
        nama = nama_;
        mulaiParkir = time(NULL);
        lama = lama_;
        idTempat = idTempat_;
    }

    int lamaParkir() { return hourDiff((int)mulaiParkir, time(NULL)); }

    // toString memudahkan menampilkan value struct dengan me return string yang
    // sudah di format dengan value structnya
    string toString()
    {
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

struct NodeUser
{
    User data;
    NodeUser *next = NULL;
};

struct TempatParkir
{
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
                 int hargaPerjam1, int hargaPerjam2, string lokasi_)
    {
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

    string toString()
    {
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

NodeUser *getNodeUser(TempatParkir *tp, int idUser)
{
    if (tp->waitlist != NULL)
    {
        NodeUser *temp;
        temp = tp->waitlist;
        while (temp != NULL)
        {
            if (temp->data.id == idUser)
            {
                return temp;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    return NULL;
}

void viewNodeUser(TempatParkir *tp)
{
    if (tp->waitlist != NULL)
    {
        NodeUser *temp;
        int count = 0;
        temp = tp->waitlist;
        cout << "\n===== Data Waiting List =====" << endl;
        while (temp != NULL)
        {
            cout << ++count << ".\t" << temp->data.toString();
            temp = temp->next;
        }
    }
}

void insertLastNodeUser(TempatParkir *tp, User user)
{
    NodeUser *newNode;
    NodeUser *temp;
    newNode = new NodeUser;
    newNode->data = user;
    newNode->next = NULL;

    if (tp->waitlist == NULL)
    {
        tp->waitlist = newNode;
        tp->waitlist->next = NULL;
    }
    else
    {
        temp = tp->waitlist;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void deleteAtNodeUser(TempatParkir *tp, User user)
{
    NodeUser *prev = NULL;
    NodeUser *temp = tp->waitlist;

    if (tp->waitlist == NULL)
    {
        return;
    }

    if (tp->waitlist->data.id == user.id)
    {
        tp->waitlist = temp->next;
        delete temp;
        return;
    }

    while (temp != NULL && temp->data.id != user.id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    delete temp;
}

struct PindahParkir
{
	int vertex;
	int edge;
	int *visited;
	int **adj;

	void buatgraph(int v, int e)
	{
		vertex = v;
		edge = e;

		visited = new int[v];
		adj = new int *[v];

		for (int i = 0; i < v; i++)
		{
			visited[i] = 0;
		}

		for (int baris = 0; baris < v; baris++)
		{
			adj[baris] = new int[v];

			for (int kolom = 0; kolom < e; kolom++)
			{
				adj[baris][kolom] = 0;
			}
		}
	}

	void tambahedge(int c, int r)
	{
		adj[c][r] = 1;
	}

	void dfs(int c)
	{
		cout << c << " ";

		visited[c] = 1;

		for (int i = 0; i < vertex; i++)
		{
			if (adj[c][i] == 1 && visited[i] == 0)
			{
				dfs(i);
			}
		}
	}

	vector<int> cariPindah(int u)
	{
		vector<int> destinasiBaru;

		for (int i = 0; i < vertex; i++)
		{
			if (adj[u][i] == 1)
			{
				destinasiBaru.push_back(i);
			}
		}

		return destinasiBaru;
	}

	int initPindahParkir()
	{
		int v = 13;
		int e = 13;

		buatgraph(v, e);

		tambahedge(0, 2);
		tambahedge(0, 3);
		tambahedge(0, 4);
		tambahedge(1, 2);
		tambahedge(1, 3);
		tambahedge(2, 1);
		tambahedge(2, 3);
		tambahedge(3, 2);
		tambahedge(5, 7);
		tambahedge(6, 7);
		tambahedge(7, 6);
		tambahedge(8, 9);

		return 0;
	}
};

PindahParkir pindahParkirData;


#endif