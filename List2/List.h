#pragma once
#include<iostream>
#include <ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "___________________________________________"

///////////////////////////////////////////////////////////////////
//////////////////			CLASS DECLARATION (���������� ������)
/////////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/////////////

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	} *Head, * Tail;
	unsigned int size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();

		bool operator ==(const ConstBaseIterator& other)const;
		bool operator !=(const ConstBaseIterator& other)const;

		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};

	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	//Constructors:
	List();
	List(const std::initializer_list<T> il);
	List(const List<T>& other);
	~List();

	//Operators
	List<T>& operator=(const List<T>& other);

	//Adding elements
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);
	//Removing elements
	void pop_front();

	void pop_back();

	//Methods
	void print()const;
	void reverse_print()const;
};
/////////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/////////////
//////////////////			CLASS DECLARATION END
///////////////////////////////////////////////////////////////////
template <typename T>List<T> operator+ (const List<T>& left, const List<T>& right);