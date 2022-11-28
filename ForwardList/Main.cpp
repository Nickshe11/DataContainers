#include<iostream>
using namespace std;
#define tab "\t"
class Element
{
	int Data; //Значение элемента
	Element* pNext; //Адрес следующего элемента
	static unsigned int count;//Количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator +(ForwardList& list1, ForwardList& list2);
};

unsigned int Element::count = 0;//Статическую переменную можно проинициализировать только за пределами класса

class ForwardList
{
protected:
	Element* Head;//Указатель на начальный элемент списка
	//Голова является точкой входа в список
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0)
	{
		//Конструктор по умолчанию создает пустой список
		//Если голова указфвает на 0 то список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		Element* Temp = Head;
		Element* box = Temp;
		int i = 0;
		while (Temp)
		{
			Temp = Temp->pNext;
			delete box;
			box = Temp;
			cout << "Deleted element # " << i << endl;
			i++;
		}

		cout << "LDestructor:\t" << this << endl;
	}
	//Adding elements
	void push_front(int Data)
	{
		//10 Создаем новый элемент
		Element* New = new Element(Data);
		//2) Пристыковываем новый элемент к началу списка
		New->pNext = Head;
		//3) Переводим голову на новый элемент
		Head = New;// Имя массива - ссылка на его первый элемент
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//Теперь Итератор указывает на последний элемент списка
		//и к нему можно пристуковать новый элемент
		Temp->pNext = New;
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		//Создаем новый элемент 
		Element* New = new Element(Data);
		//Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)if(Temp->pNext)Temp = Temp->pNext;
		//Включаем новый элемент в список
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	//Removing elements
	void pop_front()
	{
		//Слхраняем адрес удаляемого элемента
		Element* erased = Head;
		//Исключаемэлемент из списка
		Head = Head->pNext;
		//Удаляем элемент из памяти
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
			//Доходим до предпоследнего элемента списка
			Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//Удаляем последнийц элемент из памяти
		delete Temp->pNext;
		//Зануляем указатель на следующий элемент
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (Index == size)return pop_back();
		Element* erased = nullptr;
		Element* Temp = Head;
		for (int i = 0; i < Index - 2; i++)
		{
			Temp = Temp->pNext;
		}
		erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
	}
	/*ForwardList operator +(ForwardList& list1)
	{
		ForwardList Temp1;
		Element* Temp = this->Head;
		while (Temp->pNext)
		{
			Temp1.push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		Temp = list1.Head;
		while (Temp->pNext)
		{
			Temp1.push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		return Temp1;
	}*/
	ForwardList operator =(ForwardList& list1)
	{
		this->Head=list1.Head;
		return *this;
	}
	//Methods
	
	void print()const
	{
		Element* Temp = Head; //Temp - итератор
		//Итератор - указатель, при помощи которого можно получить доступ к элементам структуры данных
		cout << "Head:\t" << Head << endl;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Head->count << endl;
	}
	friend ForwardList operator +(ForwardList& list1, ForwardList& list2);
};
/*ForwardList operator +(ForwardList& list1, ForwardList& list2)
{
	ForwardList Temp1;
	Element* Temp = list1.Head;
	while (Temp->pNext)
	{
		Temp1.push_back(Temp.Data);
		Temp = Temp->pNext;
	}
	Temp = list1.Head;
	while (Temp->pNext)
	{
		Temp1.push_back(Temp->Data);
		Temp = Temp->pNext;
	}
	return Temp1;
}*/

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*cout << "__________________________" << endl;
	list.push_back(123);
	list.print();
	list.pop_back();*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента:"; cin >> index;
	cout << "Введите значение:"; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индект удаляемого элемента:"; cin >> index;
	list.erase(index);
	list.print();
	//ForwardList list1;
	//for (int i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	list1.push_back(rand() % 1000);
	//}
	//list1.print();
	//cout << "__________________________" << endl;
	//ForwardList list3 = list + list1;
	//cout << "__________________________" << endl;
	//list3.print();

}