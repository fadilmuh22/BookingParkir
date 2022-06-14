#ifndef util_hpp
#define util_hpp

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <algorithm>
#include <cctype>

using namespace std;

// Membuat string menjadi lower case dengan fungsi dari <cctype> tolower dan
// fungsi dari <algorithm> transform
string toLower(string str)
{
    string newstr = str;
    transform(newstr.begin(), newstr.end(), newstr.begin(), ::tolower);
    return newstr;
}

// clearscr membersihkan console sesuai dengan OS
void clearscr()
{
    // #ifdef WINDOWS
    // system("cls");
    // #else
    system("clear");
    // #endif
}

void pausescr()
{
    cin.ignore(256, '\n');
    string dummy;
    cout << "\n\nEnter to continue...";
    getline(cin, dummy);
}

// ? input angka dengan validasi
int inputNumber(string message, int min, int max)
{
    int input;
    string inputStr;
    bool inputValid = false;

    while (!inputValid)
    {
        cout << message;
        cin >> inputStr;

        // try-catch buat nangkep error dari stoi
        // kalo berhasil inputValid = true
        try
        {
            input = stoi(inputStr);
            if ((input >= min) && (input <= max))
            {
                inputValid = true;
            }
            else
            {
                cout << "Inputan tidak sesuai, angka(" << min << ", " << max << ")\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Inputan tidak sesuai, angka(" << min << ", " << max << ")\n";
        }
    }

    return input;
}

int inputNumberFromArray(string message, vector<int> cons)
{
    int input;
    string inputStr;
    bool inputValid = false;

    while (!inputValid)
    {
        cout << message;
        cin >> inputStr;

        // try-catch buat nangkep error dari stoi
        // kalo berhasil inputValid = true
        try
        {
            input = stoi(inputStr);
            if (find(cons.begin(), cons.end(), input) != cons.end())
            {
                inputValid = true;
            }
            else
            {
                cout << "Inputan tidak sesuai, angka(";
                for (auto di : cons)
                {
                    cout << di << ", ";
                }
                cout << ")\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Inputan tidak sesuai, angka(";
            for (auto di : cons)
            {
                cout << di << ", ";
            }
            cout << ")\n";
        }
    }

    return input;
}

// currentDateTime output string tanggal dengan format
string currentDateTime(time_t time)
{
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

#endif