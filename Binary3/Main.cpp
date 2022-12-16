#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n____________________________________________\n"

class Tree
{
	class Element
	{
		int Data; //Значение элемента
		Element* pLeft, * pRight; // Адреса потомков
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	int minValue(Element* Root) const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		if (Root->pRight == nullptr)return Root->Data;
		maxValue(Root->pRight);
	}
	int sum(Element* Root) const
	{
		if (Root == nullptr)return 0;
		return (Root->Data + sum(Root->pLeft) + sum(Root->pRight));
	}
	/*void erase(int value, Element* Root)
	{
		
		if (Root->Data == value)
		{
			delete this->Root;
			insert(Root->pLeft->Data, Root);
		}
		return;
	}	*/
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Минимальное значение: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Сумма элементов: " << tree.sum(tree.getRoot()) << endl;
	/*int value;
	cout << "Введите удаляемое значение "; cin >> value;
	tree.erase(value, tree.getRoot());
	tree.print(tree.getRoot());*/
}