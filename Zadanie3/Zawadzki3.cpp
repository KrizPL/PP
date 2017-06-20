//Krzysztof Zawadzki
#include <iostream>
#include <string>

using namespace std;

#define REPEAT_START char jr = 0; \
	do {
#define REPEAT_END cout << "Jeszcze raz[T/N]: "; \
	cin >> jr; \
	} while (jr == 't' || jr == 'T');

void convert(int _value, int _base);

int main(int argc, char **argv)
{

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
		cout << "Liczba w systemie " << base << " to "; convert(value, base); cout << '\n';
	REPEAT_END
	return 0;
}

void convert(int _value, int _base)
{
    if(_value/_base != 0)
        convert(_value/_base,_base);
    int b= _value%_base;
    if(b < 10) cout << b;
        else
        {
            switch(b)
            {
            case 10:
                cout << 'a';
                break;
            case 11:
                cout << 'b';
                break;
            case 12:
                cout << 'c';
                break;
            case 13:
                cout << 'd';
                break;
            case 14:
                cout << 'e';
                break;
            case 15:
                cout << 'f';
                break;
            }
        }
}
