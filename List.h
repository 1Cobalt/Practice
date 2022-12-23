#pragma once
#include <stdexcept>
#include <iostream>

template <typename T>
class List
{
private:

	template<typename T>
	class Node {
	public:
		T data;
		Node *pNext, *pPrev;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) 
		{ 
		this->data = data; 
		this->pNext = pNext; 
		this->pPrev = pPrev;
		}
	};	

	size_t Size;
	Node<T> *head, *tail;
public:
	List();
	List(size_t size, T baseData = T());
	List(const List& L);
	~List();

	size_t getSize() { return this->Size; };
	void insert(T data, size_t index = 0);

	void push_front(T data);
	void push_back(T data);

	void remove(size_t index);

	void hello() { std::cout << "Hello world" << std::endl; }
	
	void print_all();
	void remove_all();
	T get(size_t index);
};

template<typename T>
List<T>::List() {
	this->Size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

template<typename T>
List<T>::List(size_t size, T baseData) {
	this->Size = 0;
	this->head = nullptr;
	this->tail = nullptr;
	while (Size < size) {
		this->push_back(baseData);
	}
}

template<typename T>
List<T>::List(const List& other)
{
	this->head = this->tail = nullptr;
	Size = 0;

	Node* temp = other.head;
	// Пока не конец списка
	while (temp != 0)
	{
		// Передираем данные
		push_front(temp->data);
		temp = temp->next;
	}
}

template<typename T>
void List<T>::push_front(T data) {
	Node<T>* temp = new Node<T>();
	temp->pPrev = nullptr;
	temp->data = data;
	temp->next = head;

	if (head != nullptr)
		head->pPrev = temp;

	if (Size == 0)
		this->head = this->tail = temp;
	else
		this->head = temp;

	this->Size++;
}
template<typename T>
void List<T>::push_back(T data) {
	Node<T>* temp = new Node<T>();

	temp->pNext = 0;
	temp->data = data;
	temp->pPrev = this->tail;

	if (this->tail != nullptr)
		this->tail->pNext = temp;

	// Если элемент первый, то он одновременно и голова и хвост
	if (this->Size == 0)
		this->head = this->tail = temp;
	else
		// иначе новый элемент - хвостовой
		this->tail = temp;

	this->Size++;
}
template<typename T>
void List<T>::insert(T data, size_t index) {
	try {
		if (index < 0 || index > this->Size + 1)
		{
			throw std::out_of_range("Insert() -> wrong index");
		}


		if (index == this->Size + 1)
		{
			this->push_back(data);
			return;
		}
		else if (index == 0)
		{
			this->push_front(data);
			return;
		}

		int bufInt = 1;

		Node<T>* bufInsert = this->head;

		while (bufInt < index)
		{
			bufInsert = bufInsert.pNext;
			bufInt++;
		}

		Node<T>* bufPrev = bufInsert->prev;

		Node<T>* temp = new Node<T>();
		temp.data = data;

		if (bufPrev != 0 && this->Size != 1)
			bufPrev.next = temp;

		temp.pNext = bufInsert;
		temp.pPrev = bufPrev;
		bufInsert.pPrev = temp;

		this->Size++;
	}
	catch (const std::out_of_range&) {
		std::cerr << "insert() -> wrong index" << "\n";
	}
}

template<typename T>
void List<T>::print_all() {
	if (this->Size != 0)
	{
		Node<T>* temp = this->head;
		std::cout << "( ";
		while (temp.pNext != nullptr)
		{
			std::cout << temp.data << ", ";
			temp = temp.pNext;
		}

		std::cout << temp.data << " )\n";
	}
}

template<typename T>
T List<T>::get(size_t index) {
	if (Size != 0)
	{
		Node<T>* temp = this->head;
		for (size_t i = 0; i < index; i++) {
			temp = temp.pNext;
		}
		return temp.data;

	}
	else
		return 0;
}



template<typename T>
void List<T>::remove(size_t index) {

	if (index < 1 || index > this->Size)
	{
		// Неверная позиция
		std::cerr << "WRONG\n";
		return;
	}

	// Счетчик
	int i = 1;

	Node<T>* Del = this->head;

	while (i < index)
	{
		// Доходим до элемента, 
		// который удаляется
		Del = Del->pNext;
		i++;
	}

	Node<T>* PrevDel = Del->pPrev;
	// Доходим до элемента, который следует за удаляемым
	Node<T>* AfterDel = Del->pNext;

	// Если удаляем не голову
	if (PrevDel != 0 && this->Size != 1)
		PrevDel->pNext = AfterDel;
	// Если удаляем не хвост
	if (AfterDel != 0 && this->Size != 1)
		AfterDel->pPrev = PrevDel;

	// Удаляются крайние?
	if (index == 1)
		this->head = AfterDel;
	if (index == this->Size)
		this->tail = PrevDel;

	// Удаление элемента
	delete Del;

	this->Size--;
}

template<typename T>
void List<T>::remove_all() {
	while (this->Size != 0)
		this->remove(1);
}

template<typename T>
List<T>::~List() {
	this->remove_all();
}


