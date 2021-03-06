#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

using namespace std;

/* Deque interface */
template<typename T>
class Deque 
{
private:
	struct Node {
		T data;
		Node* next;
	};
	Node* front;
	Node* rear;
	int counter;
	int counter2;

public:
	class Iterator;

	Deque() : front(NULL), rear(NULL), counter(0), counter2(0) {}
	~Deque() {};

	inline bool isEmpty() { return (!counter) ;}
	inline int size() { return counter; }

	void addFirst(T item);
	void addLast(T item);

	T removeFirst();
	T removeLast();	

	Iterator iterator();

	void setCounter2(int c) { counter2 = c; }
	int getCounter2() const { return counter2; }
};


/* Iterator interface */
template<typename T>
class Deque<T> :: Iterator
{
private:
	inline void shiftNode(Node* node); //point to the next node
	Node *elem;
public:
	Iterator() : elem(NULL) {}
	~Iterator() {};

	Iterator(const Deque<T>& p);
	Iterator(Node&);

	T& operator*();	//overload the dereference operator
	T* operator->();

	T& operator*() const;
	T* operator->() const;

	Iterator& operator++();	//overload the ++ operator
	Iterator operator++(int);

	Iterator& operator--();
	Iterator operator--(int);
};


/* Deque implementation*/

template<typename T>
void Deque<T>::addFirst(T item)
{
	Node* tmp = new Node;
	tmp->data = item;
	if (counter != 0)
	{
		tmp->next = front;
		front = tmp;
		counter++;
	}
	else
	{
		rear = tmp;
		front = tmp;
		counter++;
	}
}

template<typename T>
void Deque<T>::addLast(T item)
{
	Node* tmp = new Node;
	tmp->data = item;
	tmp->next = NULL;
	if (counter != 0)
	{
		rear->next = tmp;
		rear = tmp;
		counter++;
	}
	else 
	{
		rear = tmp;
		front = tmp;
		counter++;
	}
}

template<typename T>
T Deque<T>::removeFirst()
{
	if (isEmpty()) { throw runtime_error("Remove from empty deque");}
	Node* tmp = new Node;
	tmp = front;
	T item = front->data;
	front = front->next;
	delete tmp;
	counter--;
	return item;	
}

template<typename T>
T Deque<T>::removeLast()
{
	if (isEmpty()) { throw runtime_error("Remove from empty deque");}
	T item = rear->data;
	Node* tmp = new Node;
	tmp = front;
	if ( counter == 1) { counter--; return item; }
	while (tmp->next != rear)
	{
		tmp = tmp->next;
	}
	rear = tmp;
	delete tmp->next;
	counter--;
	return item;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::iterator()
{
	return Iterator(*(front));
}

/* Iterator implememtation */

template <typename T>
Deque<T>::Iterator::Iterator(Deque<T>::Node& n) : elem(&n)
{

}

template <typename T>
T& Deque<T>::Iterator::operator*()
{
	//if(!elem) { throw runtime_error("No iterator!"); }
	return elem->data;

}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator++()
{
	//if(!elem) { throw runtime_error("No iterator!"); }
	shiftNode(elem->next);
	return *this;

}

template<typename T>
inline void Deque<T>::Iterator::shiftNode(Deque<T>::Node* node)
{
	if(node)
	{
		elem = node;
	}
	
}

#endif