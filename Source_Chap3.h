#include <iostream>
#include <algorithm>
using namespace std;

/*Figure 3.5 Erasing*/
template <typename Container>
void removeEveryOtherItem(Container &lst)
{
	auto itr = lst.begin();

	while (itr != lst.end())
	{
		itr = lst.erase(itr);
		if (itr != ist.end())
			++itr;
	}
}

/*Figure 3.6 Printing*/
template<typename Container>
void print(const Container &c, ostream &out = cout)
{
	if (c.empty())
		out << "empty" << endl;
	else
	{
		auto itr = begin(c);

		out << "[" << *itr++;

		while (itr != end(c))
			out << "," << *itr++;
		out << "]" << endl;
	}
}

/*Implementation of "Vector"*/
template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize = 0): theSize {initSize},
		theCapacity{initSize + SPARE_CAPACITY}
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector &rhs) : theSize{ rhs.theSize },
		theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = rhs.objects[k];
	}

	Vector & operator= (const Vector & rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector()
	{
		delete[] objects;
	}

	Vector(Vector && rhs) : theSize{ rhs.theSize },
		theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector & operator= (Vector && rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;
		
		Objects *newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; ++k)
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}
	
	Object& operator[](int index)
	{
		return objects[index];
	}

	const Object & operator[](int index) const
	{
		return objects[index];
	}

	bool empty() const
	{
		return size() == 0; 
	}

	int size() const
	{
		return theSize;
	}

	int capacity() const
	{
		return theCapacity;
	}

	void push_back(const Object & x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}

	void push_back(Object && x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}

	void pop_back()
	{
		--theSize;
	}

	const Object & back() const
	{
		return objects[theSize - 1];
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const
	{
		return &objects[size()];
	}

	static const int SPARE_CAPACITY = 16;

private:
	int theSize;
	int theCapacity;
	Object * objects;
};

/*Implementation of "List"*/
template <typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node *prev;
		Node *next;

		Node( const Object &  d = Object{}, Node * p = nullptr, Node * n = nullptr)
			:data{ d }, prev{ p }, next{ n } { }
		Node(Object && d, Node * p = nullptr, Node * n = nullptr)
			:data{ std::move(d) }, prev{ p }, next{ n } { }
	}; 

public:
	class const_iterator
	{
	public:
		const_iterator(): current{ nullptr } { }

		const Object & operator*() const
		{
			return retrieve();
		}
		const_iterator & operator++()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}

		bool operator==(const const_iterator & rhs) const
		{
			return current == rhs.current;
		}
		bool operator!=(const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		Node *current;
		Object & retrieve() const
		{
			return  current->data;
		}
		const_iterator(Node *p) :current{p} { }

		friend class List<Object>;
	};


};