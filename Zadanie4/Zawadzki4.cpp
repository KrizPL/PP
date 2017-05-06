//Krzysztof Zawadzki
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>


struct Data
{
	double m_time;
	double m_x;
	double m_force;
};

using namespace std;

#define REPEAT_START char jr = 0; \
	do {
#define REPEAT_END cout << "Jeszcze raz[T/N]: "; \
	cin >> jr; \
	} while (jr == 't' || jr == 'T');

void Calculate(double _T, double _A, double _phi, double _deltaTime, vector<Data>& _out);
bool SaveToFile(string _filepath, vector<Data>& _data);
int main(int argc, char **argv)
{
	string filepath = "dane.txt";
	double okres = 1.0;
	double amplituda = 1.0;
	double faza = 0.0;
	double delta = 1e6;
	double temp;
	string tempfp;
	vector<Data> wyniki;
	REPEAT_START

	cout << "Podaj wartosc okresu drgan [s]: ";
	cin >> okres;

	cout << "Podaj wartosc amplitude drgan [m]: ";
	cin >> amplituda;

	cout << "Podaj wartosc przesuniecie fazowe [rad]: ";
	cin >> faza;
	cout << "Podaj czestosc probkowania [s]: ";
	cin >> delta;

	cin.ignore(256, '\n');//czyszczenie cin
	cout << "Podaj nazwe pliku do ktorego zapisac dane: ";
	getline(cin, tempfp);
	if (cin.good()) filepath = tempfp;

	Calculate(okres, amplituda, faza, delta, wyniki);
	if (SaveToFile(filepath, wyniki))
		cout << "Zapisano to pliku " << filepath << '\n';
	else
		cout << "Nie mozna zapisac to pliku " << filepath << '\n';
	REPEAT_END
	return 0;
}

void Calculate(double _T, double _A, double _phi, double _deltaTime, vector<Data>& _out)
{
	double time = 0.0;
	Data temp;
	_out.clear();
	while (time <= _T)
	{
		temp.m_time = time;
		temp.m_x = _A*sin((((2.0*M_PI)/_T)*time) + _phi);
		temp.m_force = -temp.m_x;
		_out.push_back(temp);
		time += _deltaTime;
	}
}

bool SaveToFile(string _filepath, vector<Data>& _data)
{
	fstream out(_filepath.c_str(), ios::out | ios::trunc);
	if (!out.good()) return false;
	out << "t[s]\tx[m]\tF[N]\n";
	for (int i = 0; i < _data.size(); i++)
		out << _data[i].m_time << '\t' << _data[i].m_x << '\t' << _data[i].m_force << '\n';
	out.close();
	return true;
}
