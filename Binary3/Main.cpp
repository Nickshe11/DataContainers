#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n____________________________________________\n"

class Tree
{
protected:
	class Element
	{
		int Data; //Значение элемента
		Element* pLeft, * pRight; // Адреса потомков
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		bool isLeaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
private:
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
	void erase(int Data, Element* Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
						erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int minValue(Element* Root) const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}

	int sum(Element* Root) const
	{
		/*if (Root == nullptr)return 0;
		return (Root->Data + sum(Root->pLeft) + sum(Root->pRight));*/
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (depth(Root->pLeft) < depth(Root->pRight))return depth(Root->pRight) + 1;
		else return depth(Root->pLeft)+1;*/
		int left_depth = depth(Root->pLeft) + 1;
		int right_depth = depth(Root->pRight) + 1;
		return left_depth > right_depth ? left_depth : right_depth;

		/*return 
			!Root ? 0 : 
			depth(Root->pLeft) > depth(Root->pRight) ? 
			depth(Root->pLeft) + 1 :
			depth(Root->pRight) + 1;*/
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
		cout << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.clear();
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов в дереве: " << tree.sum() << endl;
	cout << "Среднее арифметическое значение: " << tree.avg() << endl;
	cout << "Глубина дерева: " << tree.depth() << endl;

	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		unique_tree.insert(rand() % 100);
	}
	unique_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << unique_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << unique_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << unique_tree.count() << endl;
	cout << "Сумма элементов в дереве: " << unique_tree.sum() << endl;
	cout << "Среднее арифметическое значение: " << unique_tree.avg() << endl;
	cout << "Глубина дерева: " << unique_tree.depth() << endl;
#endif // BASE_CHECK
	Tree my_tree = { 50, 25, 75, 16, 32, 58, 85, 48, 49, 64, 91 };
	my_tree.print();
	cout << "Глубина дерева: " << my_tree.depth() << endl;
	cout << "Минимальное значение в дереве: " << my_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << my_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << my_tree.count() << endl;
	cout << "Сумма элементов в дереве: " << my_tree.sum() << endl;
	cout << "Среднее арифметическое значение: " << my_tree.avg() << endl;
	cout << "Глубина дерева: " << my_tree.depth() << endl;

	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	//my_tree.erase(value);
	my_tree.print();
}