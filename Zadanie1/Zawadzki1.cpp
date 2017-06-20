//Krzysztof Zawadzki
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

const double g = 9.81;

void Calculate(double _v0, double _alpha, int _count, double _out[][3]);
bool WriteToFile(const char* _filepath, double _data[][3], int _size);

int main()
{
	double Data[200][3];
	double angle = -1.0, v;
	string filepath;
	char jr = 0;
	do
	{
		do
		{
			cout << "Wpisz kat poczatkowy z przedzialu 0-180: ";
			cin >> angle;
		} while (!(angle >= 0.0 && angle < 180.0));
		cout << "Wpisz predkosc poczatkowa[m/s]: ";
		cin >> v;
		Calculate(v, angle, 200, Data);
		cin.ignore(256,'\n');//czyszczenie cin
		cout << "Podaj nazwe pliku w ktorym dane zostana zapisane: ";
		getline(cin, filepath);
		//cin.ignore(INT_MAX);//czyszczenie cin
        cin.sync();
		if (!WriteToFile(filepath.c_str(), Data, 200))
			cout << "Nie mozna utworzyc pliku "<<filepath<<'\n';
		else
			cout << "Dane zapisane to pliku " << filepath << '\n';
		cout << "Jeszcze raz[T/N]: ";
		cin >> jr;
	} while (jr == 't' || jr == 'T');
	return 0;
}

void Calculate(double _v0, double _alpha, int _count, double _out[][3])
{
	_alpha *= (M_PI / 180.0);
	double sin_a = sin(_alpha);
	double cos_a = cos(_alpha);
	double deltaT = (2 * _v0*sin_a) / (g*(_count-1));
	double time = 0.0;
	for (int i = 0; i < _count; i++)
	{
		time = deltaT*i;
		_out[i][0] = time;
		_out[i][1] = _v0 * time * cos_a;
		_out[i][2] = (_v0 * time * sin_a) - (0.5*g*time*time);
	}
}

bool WriteToFile(const char * _filepath, double _data[][3], int _size)
{
	fstream out(_filepath, ios::out | ios::trunc);
	if (!out.good()) return false;
	out << "T\tx\ty\n";
	for (int i = 0; i < _size; i++)
		out << _data[i][0] << '\t' << _data[i][1] << '\t' << _data[i][2] << '\n';
	out.close();
	return true;
}
