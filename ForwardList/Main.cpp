#include<iostream>
#include <ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class ConstIterator;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	
};

unsigned int Element::count = 0;//Статическую переменную можно проинициализировать только за пределами класса

class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const ConstIterator& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
protected:
	Element* Head;//Указатель на начальный элемент списка
	//Голова является точкой входа в список
	unsigned int size;
public:
	ConstIterator begin()
	{
		return Head;
	}
	ConstIterator end()
	{
		return nullptr;
	}
	// Constructors
	ForwardList() :Head(nullptr), size(0)
	{
		//Конструктор по умолчанию создает пустой список
		//Если голова указфвает на 0 то список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il):ForwardList()
	{
		cout << typeid(il.begin()).name()<<endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		
		/*for (int i : il)
		{
			this->push_back(i);
		}*/
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;//Из конструктора копирования вызываем оператор присваивания
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);//функция std::move вызывает MoveAssignment
		cout << "MoveConstructor:\t" << this << endl;
	}
	
	~ForwardList()
	{
		while (Head)pop_front();
		/*Element* Temp = Head;
		Element* box = Temp;

		while (Temp)
		{
			Temp = Temp->pNext;
			delete box;
			box = Temp;
		}*/
		cout << "LDestructor:\t" << this << endl;
	}
	//Operators

	ForwardList& operator =(const ForwardList& other)
	{
		if (this == &other)return *this;//Проверяем, что принимаемый списко другой
		while (Head)pop_front();//проверяем, что получающий список пустой
		//deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//Adding elements
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		////10 Создаем новый элемент
		//Element* New = new Element(Data);
		////2) Пристыковываем новый элемент к началу списка
		//New->pNext = Head;
		////3) Переводим голову на новый элемент
		//Head = New;// Имя массива - ссылка на его первый элемент
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//Теперь Итератор указывает на последний элемент списка
		//и к нему можно пристуковать новый элемент
		Temp->pNext = new Element(Data);
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
		//Element* New = new Element(Data);
		//Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)if (Temp->pNext)Temp = Temp->pNext;
		//Включаем новый элемент в список
		//New->pNext = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
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

	//Methods

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head; //Temp - итератор
		//Итератор - указатель, при помощи которого можно получить доступ к элементам структуры данных
		//while (Temp)
		//{
		//	Temp = Temp->pNext;//Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Head->count << endl;
	}
	void reverse()
	{
		ForwardList reverse;
		while(Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		this->Head = reverse.Head;
		this->size = reverse.size;
		reverse.Head = nullptr;
	}
	/*ForwardList reverse()
	{
		ForwardList box{};
		Element* Temp = Head;
		while (Temp)
		{
			box.push_front(Temp->Data);
			Temp = Temp->pNext;
		}
		*this = box;
		return *this;
	}*/
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};



ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;//CopyConstructor
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}



//#define BASE_CHECK
//#define COUNT_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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
	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента:"; cin >> index;
	cout << "Введите значение:"; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индект удаляемого элемента:"; cin >> index;
	list.erase(index);
	list.print();*/
	ForwardList list1;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list1.push_back(rand() % 1000);
	}
	list1.print();
	cout << "__________________________" << endl;
	ForwardList list3 = list + list1;
	cout << "__________________________" << endl;
	list3.print();
#endif // BASE_CHECK
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	/*list1.reverse();
	list1.print();*/

#endif // COUNT_CHECK
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof arr[0]; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
	//range-based for (for для диапазона, то есть для контейнера)
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY
#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif //RANGE_BASED_FOR_LIST
#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	cout << "List created, loading data..." << endl;
	time_t start = time(NULL);//time(NULL) получает текущее время в миллисекундах
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	time_t end = time(NULL);
	cout << "Data load complete" << endl;
	cout << "Spent time: " << end - start << endl;
	//list.print();
	cout << "Start copying" << endl;
	start = time(NULL);
	ForwardList list2 = list;
	end = time(NULL);
	cout << "End copying" << endl;
	cout << "Spent time:" << end - start << endl;
	//list2.print();  
#endif // PERFORMANCE_CHECK

}