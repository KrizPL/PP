//Krzysztof Zawadzki
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
	ListNode* prev;
};

struct TwoWaysList
{
	ListNode* head;
	ListNode* tail;
};

ListNode* CreateOneWayList(int _min, int _max, int _elementsCount);
float Averange(ListNode* _list);
TwoWaysList CreateTwoWaysList(ListNode* _odList, float _avg);
void DisplayList(ListNode* _list);
void DeleteList(ListNode* _list);
void Insert(ListNode* _list, int _value, int& _listSize);
ListNode* DeleteNegative(ListNode* _list);
bool Find(TwoWaysList _list, int value);

int main(int argc, char **argv)
{
	srand(time(0));
	int n = 0;
	do
	{
		cout << "Wprodzac liczbe elementow listy(>0): ";
		cin >> n;
	} while (n < 1);
	int findValue;
	float avg;
	ListNode *OWlist = CreateOneWayList(-100, 100, n);
	cout << "Lista wylosowanych wartosci:\n";
	DisplayList(OWlist);
	avg = Averange(OWlist);
	TwoWaysList TWlist = CreateTwoWaysList(OWlist, avg);
	cout << "\nSrednia z wartosci na liscie: " << avg << '\n';
	Insert(OWlist, n, n);
	cout << "\nLista wartosci wiekszych od sredniej:\n";
	DisplayList(TWlist.head);
	cout << "\nLista jednokierunkowa po zmianach (4):\n";
	DisplayList(OWlist);
	OWlist = DeleteNegative(OWlist);
	cout << "\nLista jednokierunkowa po zmianach (5):\n";
	DisplayList(OWlist);
	cout << "\nJakiej wartosci szukasz w liscie dwukierunkowej: ";
	cin >> findValue;
	if (Find(TWlist, findValue))
		cout << "Znaleziono taki element\n";
	else
		cout << "Nie ma takiego elementu\n";
	DeleteList(OWlist);
	DeleteList(TWlist.head);
	OWlist = 0;
	system("pause");
	return 0;
}

ListNode * CreateOneWayList(int _min, int _max, int _elementsCount)
{
	int range = _max - _min + 1;
	ListNode * const start = new ListNode;
	ListNode* iterator = start;
	start->value = (rand() % range) + _min;
	start->next = 0;
	start->prev = 0;
	for (int i = 1; i < _elementsCount; i++)
	{
		iterator->next = new ListNode;
		iterator = iterator->next;
		iterator->value = (rand() % range) + _min;
		iterator->next = 0;
		iterator->prev = 0;
	}
	return start;
}

float Averange(ListNode * _list)
{
	if (_list == 0) return -1.f;
	float sum = 0.f;
	float elementsCount = 0.0;
	ListNode* iterator = _list;
	do
	{
		sum += iterator->value;
		elementsCount += 1.f;
	} while ((iterator = iterator->next) != 0);
	return sum/elementsCount;
}

TwoWaysList CreateTwoWaysList(ListNode * _odList, float _avg)
{
	if (_odList == 0)
		return TwoWaysList{ 0,0 };
	ListNode* const start = new ListNode;
	TwoWaysList result;
	result.head = start;
	ListNode* iterator = 0;
	do
	{
		if (_odList->value > _avg)
			if (!iterator)
			{
				start->value = _odList->value;
				start->prev = 0;
				start->next = 0;
				iterator = start;
			}
			else
			{
				iterator->next = new ListNode;
				iterator->next->value = _odList->value;
				iterator->next->prev = iterator;
				iterator = iterator->next;
				iterator->next = 0;
			}
		else;
	}while ((_odList = _odList->next) != 0);
	result.tail = iterator;
	return result;
}

void DisplayList(ListNode * _list)
{
	if (_list == 0) return;
	cout << _list->value;
	while ((_list = _list->next) != 0)
	{
		cout << ((_list->prev == 0) ? "--->" : "<--->") << '(' << _list->value << ')';
	}
	cout << '\n';
}

void DeleteList(ListNode * _list)
{
	ListNode* prev;
	ListNode* temp = _list;
	while (temp->next != 0)
	{
		prev = temp;
		temp = prev->next;
		delete prev;
	} 
	if (temp != 0)
		delete temp;
	
}

void Insert(ListNode* _list, int _value, int& _listSize)
{
	if (!_list) return;
	for (int i = 0; i < _listSize - 2; i++)
		_list = _list->next;
	ListNode* temp = _list->next;
	_list->next = new ListNode;
	//_list->next = _list;
	_list = _list->next;
	_list->value = _value;
	_list->next = temp;
	_list->prev = 0;
	_listSize++;
}

ListNode* DeleteNegative(ListNode * _list)
{
	ListNode* const start = _list;
	if (!_list) return _list;
	ListNode* temp = _list;
	if (_list->value < 0)
	{
		temp = _list->next;
		delete _list;
		return temp;
	}
	while (_list->next->value >= 0)
		_list = _list->next;
	temp = _list;
	_list = _list->next;
	ListNode* temp2 = _list->next;
	delete _list;
	temp->next = temp2;
	return start;
}

bool Find(TwoWaysList _list, int value)
{
	ListNode *temp = _list.head;
	while (temp)
		if (temp->value == value)
			return true;
		else
			temp = temp->next;
	return false;
}
