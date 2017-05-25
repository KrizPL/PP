//Krzysztof Zawadzki
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Lek
{
	char nazwa[11];
	float cena;
	int ilosc;
};
struct Zamowienie
{
	char nazwa[11];
	int ilosc_min;
	int ile_zamowic;
};
struct Dane
{
	char nazwa[11];
	int ilosc;
	float cena_sz;
	float cena;
};
template <typename T>
struct ListNode
{
	T value;
	ListNode* next;
};

template <typename T> void DeleteList(ListNode<T> * _list);
ListNode<Lek>* LoadFromFile(const char* _filepath);
template<typename T> ListNode<T>* AddRange(T _values[], int size);
ListNode<Dane>* Calculate(ListNode<Lek>* _leki, ListNode<Zamowienie>* _zamo);
bool findByName(ListNode<Lek>* _leki, char name[], Lek& _result);
bool saveToFile(const char* _filepath, ListNode<Dane>* _data);


void Display(ListNode<Lek>* _a);
void Display(ListNode<Zamowienie>* _b);
void Display(ListNode<Dane>* _c);


int main(int argc, char **argv)
{
	ListNode<Lek>* leki = LoadFromFile("pl6.txt");
	if (leki == NULL)
	{
		cout << "Nie mozna wczytac pliku pl6.txt\n";
		return 0;
	}
	cout << "Leki w magazynie\n";
	Display(leki);
	Zamowienie temp[] = { { "Magne-b6",10,200 },
		{ "Allegra",20,150 },  { "WitaminaB",50, 30 },
		{ "Polopir",50, 30 } };
	ListNode<Zamowienie>* zamowienia = AddRange(temp, 4);
	ListNode<Dane>* doZamowienia = Calculate(leki,zamowienia);
	if(!saveToFile("pl2.txt", doZamowienia))
		cout << "Nie mozna zapisac do pliku pl2.txt\n";
	else
		cout << "Zapisano do pliku pl2.txt dane do zamowienia\n";
	cout << "Zamowienie\n";
	Display(zamowienia);
	cout << "Informacje o zamowieniu\n";
	Display(doZamowienia);
	DeleteList(leki);
	DeleteList(zamowienia);
	DeleteList(doZamowienia);
	leki = 0;
	zamowienia = 0;
	doZamowienia = 0;
	system("PAUSE");
	return 0;
}


ListNode<Lek>* LoadFromFile(const char* _filepath)
{
	ifstream in(_filepath);
	if (!in.good())
		return NULL;
	ListNode<Lek>* start = 0;
	ListNode<Lek>* iterator = 0;
	while (in)
	{
		if (!start)
		{
			start = new ListNode<Lek>;
			iterator = start;
		}
		else
		{
			iterator->next = new ListNode<Lek>;
			iterator = iterator->next;

		}
		iterator->next = 0;
		in.get(iterator->value.nazwa, 11, '\t');
		in >> iterator->value.cena >> iterator->value.ilosc;
		in.ignore();
	}
	return start;
}
ListNode<Dane>* Calculate(ListNode<Lek>* _leki, ListNode<Zamowienie>* _zamo)
{
	ListNode<Dane> *start = 0, *iterator = 0;
	Lek findResult;
	int needCount;
	while (_zamo != 0)
	{
		if (findByName(_leki, _zamo->value.nazwa,findResult))
		{
			if (!start)
			{
				start = new ListNode<Dane>;
				iterator = start;
			}
			else
			{
				iterator->next = new ListNode<Dane>;
				iterator = iterator->next;
			}
			iterator->next = 0;
			strcpy(iterator->value.nazwa, findResult.nazwa);

			needCount = _zamo->value.ile_zamowic - findResult.ilosc;
			if (needCount <= 0)
				needCount = iterator->value.ilosc = 0;
			else
				needCount = iterator->value.ilosc = needCount >= _zamo->value.ilosc_min ?
					needCount : _zamo->value.ilosc_min;
			iterator->value.cena_sz = findResult.cena;
			iterator->value.cena = needCount * findResult.cena;
		}
		_zamo = _zamo->next;
	}

	return start;
}
bool findByName(ListNode<Lek>* _leki, char name[], Lek& _result)
{
	while (_leki != 0)
	{
		if (strcmp(_leki->value.nazwa, name) == 0)
		{
			_result = _leki->value;
			return true;
		}
		_leki = _leki->next;
	}
	return false;

}
void Display(ListNode<Lek>* _a)
{
	cout << setw(14) << "Nazwa\t" << "|Cena" << "\t|Ilosc\n";
	cout << setw(42) << setfill('-') << '\n' << setfill((char)32);
	do
	{
		cout << setw(14) << _a->value.nazwa <<"\t|"<< _a->value.cena <<"\t|"<< _a->value.ilosc << endl;
		_a = _a->next;
	} while (_a != 0);
}
void Display(ListNode<Zamowienie>* _b)
{
	cout << setw(14) << "Nazwa\t" << "|Ilosc min" << "\t|Zamowic\n";
	cout << setw(42) << setfill('-') << '\n' << setfill((char)32);
	do
	{
		cout << setw(14) << _b->value.nazwa << "\t|" << _b->value.ilosc_min << "\t|" << _b->value.ile_zamowic << endl;
		_b = _b->next;
	} while (_b != 0);
}

void Display(ListNode<Dane>* _b)
{
	cout << setw(14) << "Nazwa\t" << "|Do Zam." << "\t|Cena/szt\t|Cena\n";
	cout << setw(42) << setfill('-') << '\n' << setfill((char)32);
	do
	{
		cout << setw(14) << _b->value.nazwa << "\t|" << _b->value.ilosc << "\t|" << _b->value.cena_sz << "\t|"<< _b->value.cena << endl;
		_b = _b->next;
	} while (_b != 0);
}

template <typename T>
void DeleteList(ListNode<T> * _list)
{
	ListNode<T>* prev;
	ListNode<T>* temp = _list;
	while (temp->next != 0)
	{
		prev = temp;
		temp = prev->next;
		delete prev;
	}
	if (temp != 0)
		delete temp;

}

bool saveToFile(const char* _filepath, ListNode<Dane>* _data)
{
	if(_data == 0) return false;
	fstream out(_filepath, ios::out | ios::trunc);
	if(!(out.good())) return false;
	out << "Nazwa\tIlosc\tCena_za_sztk\tCena" << endl;
	do
	{
		out << _data->value.nazwa << '\t' << _data->value.ilosc << '\t' << _data->value.cena_sz << '\t' << _data->value.cena;
		out << endl;
	}while((_data = _data->next) != 0);
	out.close();
	return true;
}

template<typename T>
ListNode<T>* AddRange(T _values[], int size)
{
	ListNode<T>* start = 0;
	ListNode<T>* iterator = 0;
	for (int i = 0; i < size; i++)
	{
		if (!start)
		{
			start = new ListNode<T>;
			iterator = start;
		}
		else
		{
			iterator->next = new ListNode<T>;
			iterator = iterator->next;
		}
		iterator->value = _values[i];
		iterator->next = NULL;
	}
	return start;
}
