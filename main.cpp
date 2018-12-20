#include <iostream>
#include <vector>
#include <windows.h> // funkcja system("cls")
#include <cstdlib> // funkcja exit(0)
#include <fstream> //biblioteka odpowiedzialna za wspolprace z plikami
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

string nazwaPlikuTxt;

struct Adresat {
    int idAdresata = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", email = "", adres = "";
};

void wczytajAdresatowZPlikuZrodlowego(vector<Adresat> &adresaci, string &nazwaPlikuTxt);
//void wyswietlAdresatowZPlikuZrodlowego(vector<Adresat> &adresaci);
void zapiszAdresatowDoPrzekonwertowanegoPliku(vector<Adresat> &adresaci, string &nazwaPlikuTxt);

int main() {
    vector<Adresat> adresaci;

    string nazwaPlikuTxt;

    cout << "Podaj nazwe pliku zrodlowego: ";
    getline(cin, nazwaPlikuTxt);

    wczytajAdresatowZPlikuZrodlowego(adresaci, nazwaPlikuTxt);
    //wyswietlAdresatowZPlikuZrodlowego(adresaci);
    zapiszAdresatowDoPrzekonwertowanegoPliku(adresaci, nazwaPlikuTxt);

    return 0;
}

string konwersjaZIntNaString(int zmienna) {
    ostringstream ss;
    ss << zmienna;
    string str = ss.str();

    return str;
}

void wczytajAdresatowZPlikuZrodlowego(vector<Adresat> &adresaci, string &nazwaPlikuTxt) {
    Adresat osoba;
    string pojedynczaDanaAdresataZapisanaWLinii = "";
    int numerLiniiZDanaAdresata = 1;

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuTxt.c_str(), ios::in);

    if (plikTekstowy.good() == false) {
        cout << "Ksiazka adresowa jest pusta." << endl;
        cout << "Nacisnij dowolny klawisz, aby przejsc do menu glownego." << endl;
        system("pause");
    }

    while (getline(plikTekstowy, pojedynczaDanaAdresataZapisanaWLinii)) {
        switch(numerLiniiZDanaAdresata) {
        case 1:
            osoba.idAdresata = atoi(pojedynczaDanaAdresataZapisanaWLinii.c_str());
            break;
        case 2:
            osoba.imie = pojedynczaDanaAdresataZapisanaWLinii;
            break;
        case 3:
            osoba.nazwisko = pojedynczaDanaAdresataZapisanaWLinii;
            break;
        case 4:
            osoba.nrTelefonu = pojedynczaDanaAdresataZapisanaWLinii;
            break;
        case 5:
            osoba.email = pojedynczaDanaAdresataZapisanaWLinii;
            break;
        case 6:
            osoba.adres = pojedynczaDanaAdresataZapisanaWLinii;
            break;
        }

        if (numerLiniiZDanaAdresata == 6) {
            adresaci.push_back(osoba);
            numerLiniiZDanaAdresata = 1;
        } else {
            numerLiniiZDanaAdresata++;
        }

        pojedynczaDanaAdresataZapisanaWLinii = "";
    }
    plikTekstowy.close();
    plikTekstowy.clear();
}

void wyswietlAdresatowZPlikuZrodlowego(vector<Adresat> &adresaci) {
    system("cls");
    if (!adresaci.empty()) {
        for (vector<Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            cout << "ID: " << itr -> idAdresata << endl;
            cout << "Imie: " << itr -> imie << endl;
            cout << "Nazwisko: " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> nrTelefonu << endl;
            cout << "E-mail: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl;
    }
    system("pause");
}

void zapiszAdresatowDoPrzekonwertowanegoPliku(vector<Adresat> &adresaci, string &nazwaPlikuTxt) {
int dlugoscPlikuZrodlowego = nazwaPlikuTxt.length();
string nazwaPrzekonwertowanegoPlikuTxt = nazwaPlikuTxt;
nazwaPrzekonwertowanegoPlikuTxt.erase((dlugoscPlikuZrodlowego - 4), 4);
dlugoscPlikuZrodlowego = nazwaPrzekonwertowanegoPlikuTxt.length();
nazwaPrzekonwertowanegoPlikuTxt.insert(dlugoscPlikuZrodlowego, "_nowy_format.txt");

//cout << nazwaPrzekonwertowanegoPlikuTxt << endl;

string pojedynczaLiniaZDanymiAdresata = "";

    //cout << "Podaj nazwe przekonwertowanego pliku: ";
    //getline(cin, nazwaPlikuTxt);

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPrzekonwertowanegoPlikuTxt.c_str(), ios::out);

    if (plikTekstowy.good()) {
        for (vector<Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            pojedynczaLiniaZDanymiAdresata += konwersjaZIntNaString(itr -> idAdresata) + '|';
            pojedynczaLiniaZDanymiAdresata += itr -> imie + '|';
            pojedynczaLiniaZDanymiAdresata += itr -> nazwisko + '|';
            pojedynczaLiniaZDanymiAdresata += itr -> nrTelefonu + '|';
            pojedynczaLiniaZDanymiAdresata += itr -> email + '|';
            pojedynczaLiniaZDanymiAdresata += itr -> adres + '|';

            plikTekstowy << pojedynczaLiniaZDanymiAdresata << endl;
            pojedynczaLiniaZDanymiAdresata = "";
        }
        plikTekstowy.close();
    } else {
    cout << "Nie mozna otworzyc pliku tekstowego" << endl;
    }
}
