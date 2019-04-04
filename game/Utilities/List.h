#pragma once

template <class T>
class ListItem
{
public:
	T* value;
	ListItem<T>* next;

	ListItem();
	ListItem(T*);
};

template <class T>
class List
{
public:
	ListItem<T>* head;
	List();
	List(List<T>&);
	//List(T*, T);
	~List();

	void add(T*);                    // place value-pointer in item and join to end (not copy)
	void add(List<T>&);              // join list to end
	void delete_all();               // delete all items and valuable objects
	void remove(T*);                 // find item by value-pointer and delete it
	void drop(T*);                   // remove item without valuable object deletion
	void remove(ListItem<T>*);       // find item by item-pointer and delete it
	int len() const;
	List<T>& operator=(List<T>&);

	void foreach(void(T::*func)());
	//void foreach(void(T::*func)(List& list));
};

template <class T>
ListItem<T>::ListItem()
{
	next = nullptr;
}

template <class T>
ListItem<T>::ListItem(T* _value)
{
	value = _value;
	next = nullptr;
}

template <class T>
List<T>::List()
{
	head = nullptr;
}

template <class T>
List<T>::List(List<T>& l)
{
	head = nullptr;
	add(l);
}

template <class T>
List<T>::~List()
{
	delete_all();
}

template <class T>
void List<T>::add(T* value)
{
	if (!head) 
	{
		head = new ListItem<T>();
		head->value = value;
	}
	else
	{
		ListItem<T>* i = head;
		for (i = head; i->next; i = i->next);
		i->next = new ListItem<T>();
		i->next->value = value;
	}
}

template <class T>
void List<T>::add(List<T>& l)
{
	if (l.head)
	{
		if (head)
		{
			ListItem* i = head;
			for (i = head; i->next; i = i->next);
			for (ListItem<T>* j = l.head; j; j = j->next)
			{
				i->next = new ListItem<T>(j->value);
				i = i->next;
			}
		}
		else
		{
			head = new ListItem<T>(l.head->value);
			if (head->next)
			{
				ListItem<T>*i, *j;
				for (i = head, j = l.head->next; j; i = i->next, j = j->next)
				{
					i->next = new ListItem<T>(j->value);
				}
			}
		}
	}
}

template <class T>
void List<T>::delete_all()
{
	if (!head)
		return;
	ListItem<T>* i = head;
	ListItem<T>* del = i;
	while (i)
	{
		i = i->next;
		//delete del->value;
		delete del;
		del = i;
	}
}

template<class T>
void List<T>::remove(T* elem)
{
	if (!head)
		return;
	if (head->value == elem)
	{
		delete elem;
		ListItem<T>* del = head;
		if (head->next)
			head = head->next;
		else
			head = nullptr;
		delete del;
		return;
	}
	for(ListItem<T>* i = head; i->next; i = i->next)
		if (i->next->value == elem)
		{
			ListItem<T>* tnext = i->next->next;
			delete elem;
			delete i->next;
			i->next = tnext;
			break;
		}
}

template<class T>
void List<T>::drop(T* elem)
{
	if (!head)
		return;
	if (head->value == elem)
	{
		ListItem<T>* del = head;
		if (head->next)
			head = head->next;
		else
			head = nullptr;
		delete del;
		return;
	}
	for (ListItem<T>* i = head; i->next; i = i->next)
		if (i->next->value == elem)
		{
			ListItem<T>* tnext = i->next->next;
			delete i->next;
			i->next = tnext;
			break;
		}
}

template<class T>
inline void List<T>::remove(ListItem<T>* item)
{
	if (!head)
		return;
	if (head == item)
	{
		delete item->value;
		ListItem<T>* del = head;
		if (head->next)
			head = head->next;
		else
			head = nullptr;
		delete del;
		return;
	}
	for (ListItem<T>* i = head; i->next; i = i->next)
		if (i->next == item)
		{
			ListItem<T>* tnext = i->next->next;
			delete i->next->value;
			delete i->next;
			i->next = tnext;
			break;
		}
}

template <class T>
int List<T>::len() const
{
	if (!head)
		return 0;
	int k = 0;
	for (ListItem<T>* i = head; i; i = i->next)
		k++;
	return k;
}

template <class T>
List<T>& List<T>::operator=(List<T>& l)
{
	if (this == &l)
		return *this;
	delete_all();
	add(l);
	return *this;
}

template<class T>
void List<T>::foreach(void (T::*func)())
{
	if (!head)
		return;
	for (ListItem<T>* i = head; i; i = i->next)
		(i->value->*func)();
}