#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct OneWayNode
{
    int value;
    OneWayNode *next;
};
struct TwoWayNode
{
    int value;
    TwoWayNode *prev, *next;
};

OneWayNode* CreateList(int _min, int _max, unsigned int _n);
TwoWayNode* CreateList(OneWayNode* _list, float _avg);

float Averange(OneWayNode * _list);

void Insert(OneWayNode* _list, int _pos, int _value);

void DeleteFirstNegative(TwoWayNode * _list);

void DeleteList(OneWayNode* _list);
void DeleteList(TwoWayNode* _list);

void Display(OneWayNode* _list);
void Display(TwoWayNode* _list);

bool Find(TwoWayNode* _list, int _value); 

inline TwoWayNode* GoToStart(TwoWayNode* _list);



int main(int argc, char **argv)
{
    int n = 0;
    OneWayNode* jednokierunkowa = 0;
    TwoWayNode* dwukierunkowa = 0;
    float srednia;
    srand(time(0));
    do
    {
        cout << "Wprowadz liczbe elementow listy jednokierunkowej(>0): ";
        cin >> n;
    }while(n <= 0);

    //Tworzenie listy jednokierunkowej
    jednokierunkowa = CreateList(-100,100,n);
    cout << "Lista jednokierunkowa przed modywikacja\n";
    Display(jednokierunkowa);
    //Wyznaczanie sredniej
    srednia = Averange(jednokierunkowa);
    cout << "Srednia: " << srednia << endl;

    //Tworzenie listy dwukierunkowej
    dwukierunkowa = CreateList(jednokierunkowa, srednia);
    cout << "Lista dwukierunkowa przed modywikacja\n";
    Display(dwukierunkowa);

    //Dodawanie rozmiaru listy na przedostadnie miejsce
    Insert(jednokierunkowa,n-1,n);
    cout << "Lista jednokierunkowa po modywikacji\n";
    Display(jednokierunkowa);
    //Usuwanie pierwszej ujemnej wartosci
    DeleteFirstNegative(dwukierunkowa);
    cout << "Lista dwukierunkowa po modywikacji\n";
    Display(dwukierunkowa);
    cout << "Jakiego element chcesz znalezc na liscie dwukierunkowej: ";
    cin >> n;
    //Szukanie elementu
    if(Find(dwukierunkowa, n))
        cout << "Znaleziono element\n";
    else
        cout << "Nie ma takiego elementu\n";
    //kasowanie list z pamieci
    DeleteList(jednokierunkowa);
    DeleteList(dwukierunkowa);
    jednokierunkowa = 0;
    dwukierunkowa = 0;
    return 0;
}

OneWayNode* CreateList(int _min, int _max, unsigned int _n)
{
    if(_n == 0) return 0;
    int range = _max - _min + 1;
	OneWayNode * const start = new OneWayNode;
	OneWayNode* iter = start;
	start->value = (rand() % range) + _min;
	for (unsigned int i = 1; i < _n; i++)
	{
		iter->next = new OneWayNode;
		iter = iter->next;
		iter->value = (rand() % range) + _min;
	}
	iter->next = 0;
	return start;
}
float Averange(OneWayNode * _list)
{
	if (_list == 0) return -1.f;
	float sum = 0.f;
	float elementsCount = 0.0;
	OneWayNode* iter = _list;
	do
	{
		sum += iter->value;
		elementsCount += 1.f;
	} while ((iter = iter->next) != 0);
	return sum/elementsCount;
}

TwoWayNode* CreateList(OneWayNode* _list, float _avg)
{
    if (_list == 0)
		return 0;
	TwoWayNode* const start = new TwoWayNode;
	TwoWayNode* iter = 0;
	do
	{
		if (_list->value > _avg)
			if (!iter)
			{
				start->value = _list->value;
				start->prev = 0;
				iter = start;
			}
			else
			{
				iter->next = new TwoWayNode;
				iter->next->value = _list->value;
				iter->next->prev = iter;
				iter = iter->next;
			}
		else;
	}while ((_list = _list->next) != 0);
	iter->next = 0;
	return start;
}
void Insert(OneWayNode* _list, int _pos, int _value)
{
	if (!_list) return;
	//przechodzimy do elementu podanego w arkumencie _pos
	for (int i = 1; i < _pos; i++)
		_list = _list->next;

	OneWayNode* temp = _list->next;
	_list->next = new OneWayNode;
	_list = _list->next;
	_list->value = _value;
	_list->next = temp;
}
void DeleteFirstNegative(TwoWayNode * _list)
{

	if (!_list) return;
	TwoWayNode* const start = GoToStart(_list);
	TwoWayNode* temp;
	//Jezeli pierwszy element listy jest ujemny
	if (start->value < 0)
	{
		temp = _list->next;
		delete _list;
		temp->prev = 0;
		_list = temp;
	}
	_list = start;
    while (_list->value >= 0 && (_list->next))
       _list = _list->next;
    //Jezeli petla zostala przerwana przez drugi warunek (_list->next == 0)
    if(_list->value >= 0) return;
    //Jezeli petla zostala przerwana przez pierwszy warunek list->value < 0)
	temp = _list->prev;
	TwoWayNode* temp2 = _list->next;
	delete _list;
	if(temp2)
    {
        temp2->prev = temp;

    }
    temp->next = temp2;
    _list = start;
}
void DeleteList(OneWayNode* _list)
{
    if(!_list) return;
    OneWayNode* prev;
	OneWayNode* temp = _list;
	while (temp->next != 0)
	{
		prev = temp;
		temp = prev->next;
		delete prev;
	}
	if (temp != 0)
		delete temp;
}
void DeleteList(TwoWayNode* _list)
{
    if(!_list) return;
    _list = GoToStart(_list);
    TwoWayNode* prev;
	TwoWayNode* temp = _list;
	while (temp->next != 0)
	{
		prev = temp;
		temp = prev->next;
		delete prev;
	}
	if (temp != 0)
		delete temp;
}
void Display(OneWayNode* _list)
{
    if (_list == 0) return;
	cout << '('<<_list->value<< ')';
	while ((_list = _list->next) != 0)
	{
		cout << "--->" << '(' << _list->value << ')';
	}
	cout << '\n';
}

bool Find(TwoWayNode* _list, int _value)
{
    if(!_list) return false;
    do
        if(_list->value == _value) return true;
    while((_list = _list->next) != 0);
    return false; 
}

void Display(TwoWayNode* _list)
{
    if (_list == 0) return;
    _list = GoToStart(_list);
	cout << '('<<_list->value<< ')';
	while ((_list = _list->next) != 0)
	{
		cout << "<===>" << '(' << _list->value << ')';
	}
	cout << '\n';
}
inline TwoWayNode* GoToStart(TwoWayNode* _list)
{
    while(_list->prev != 0) _list = _list->prev;
    return _list;
}
