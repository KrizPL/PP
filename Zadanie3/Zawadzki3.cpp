//Krzysztof Zawadzki
#include <iostream>
#include <string>

using namespace std;

#define REPEAT_START char jr = 0; \
	do {
#define REPEAT_END cout << "Jeszcze raz[T/N]: "; \
	cin >> jr; \
	} while (jr == 't' || jr == 'T');

string convert(int _value, int _base, const string _dirct[]);

int main(int argc, char **argv)
{
	string dictionary[] = { "0","1","2","3","4","5","6","7","8",
		"9","A","B","C","D","E","F" };
	int value;
	int base;
	REPEAT_START
		do
		{
			cout << "Wpisz liczbe to konwersji(>=0)\n";
			cin >> value;
		} while (value < 0);

		do
		{
			cout << "Wpisz podstawe systemu(2, 8 lub 16)\n";
			cin >> base;
		} while (base != 2 && base != 8 && base != 16);
		cout << "Liczba w systemie " << base << " to " << convert(value, base, dictionary) << '\n';
	REPEAT_END
	return 0;
}

string convert(int _value, int _base, const string _dirct[])
{

	if (_value == 1)
		return "1";
	else
	{
		int mumber = _value%_base;
		if((_value / _base) != 0)
			return convert(_value/_base,_base,_dirct)+_dirct[mumber];
		else return _dirct[mumber];
	}
	
}
