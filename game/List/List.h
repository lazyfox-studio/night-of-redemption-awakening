#pragma once

template <class T>
class ListItem
{
public:
	T value;
	ListItem<T>* next;
	ListItem<T>();
	ListItem<T>(T&);
};

template <class T>
class List
{
	ListItem<T>* head;
public:
	List<T>();
	List<T>(List<T>&);
	//List<T>(T*, T);
	~List<T>();

	// ��������� ������� � �������� ��������� � ����� ������
	void add(T&);
	// ������������ �������� ���������� ������ � �����
	void add(List<T>&);
	// ������� ��� �������� ������
	void delete_all();
	// ���� ������ ������� � �������� ���������
	ListItem<T>* search(T&) const;
	//  ���� ord-� ������� � �������� ���������
	ListItem<T>* search(T&, int) const;
	// �������� ������� ����� ������� ��������, ����������� �������� �������� (�������� int ����� ������� int)
	int insert_after(T&, int);
	// �������� ������� ����� ord-�� ��������, ����������� �������� �������� (�������� int ����� int, ���������� int-�)
	int insert_after(T&, T&, int);
	// ��������� ������� ����� ��������
	int insert_after(ListItem<T>*, ListItem<T>*);
	// �������� ������� ����� ������ ���������, ���������� �������� �������� (�������� int ����� ������ int)
	int insert_before(T&, int);
	// �������� ������� ����� ord-� ���������, ���������� �������� �������� (�������� int ����� int, ��������� int-�)
	int insert_before(T&, T&, int);
	// ������� ��� �������� � �������� ���������
	int remove(T&);
	// ������� ord-� ������� � �������� ���������
	int remove(T&, int);
	// ��������� �������� ������ � �������� �������
	void reverse();
	// ������� ������ �� ��������� ������
	int* array();
	// ���������� ���������� ��������� ������
	int len() const;

	// [���������� =]  �������� �������� �� ������� ������
	List<T>& operator=(List<T>&);
	// [���������� ==] ���������� �������� �������
	bool operator==(List<T>&);
	// [���������� +]  ���������� �������� ������� � ����
	List<T>& operator+(List<T>&);
	// [���������� +=] ������������ �������� ������ � �����
	List<T>& operator+=(List<T>&);
	// [���������� +]  ��������� ������� � ����� ������
	List<T>& operator+(T&);
	// [���������� +=] ��������� ������� � ����� ������
	List<T>& operator+=(T&);
	// [���������� -]  ������� ��� ��������, ���������� �������� ��������
	List<T>& operator-(T&);
	// [���������� -=] ������� ��� ��������, ���������� �������� ��������
	List<T>& operator-=(T&);
	// [���������� ()] ��������� ������� � ������
	void operator()(T&);
	// [���������� tc] ���������, �������� �� ������ ��������
	operator bool();
	// [���������� tc] ���������� ���������� ��������� ������
	operator int();
};

template <class T>
ListItem<T>::ListItem()
{
	next = nullptr;
}

template <class T>
ListItem<T>::ListItem(T& _value)
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
void List<T>::add(T& value)
{
	if (!head)
		head = new ListItem(value);
	else
	{
		ListItem* i = head;
		for (i = head; i->next; i = i->next);
		i->next = new ListItem(value);
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
			for (ListItem* j = l.head; j; j = j->next)
			{
				i->next = new ListItem(j->value);
				i = i->next;
			}
		}
		else
		{
			head = new ListItem(l.head->value);
			if (head->next)
			{
				ListItem *i, *j;
				for (i = head, j = l.head->next; j; i = i->next, j = j->next)
				{
					i->next = new ListItem(j->value);
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
	ListItem* i = head;
	ListItem* del = i;
	while (i)
	{
		i = i->next;
		delete del;
		del = i;
	}
}

template <class T>
ListItem<T>* List<T>::search(T& v) const
{
	if (!head)
		return nullptr;
	for (ListItem* i = head; i; i = i->next)
		if (i->value == v)
			return i;
	return nullptr;
}

template <class T>
ListItem<T>* List<T>::search(T& v, int ord) const
{
	if (!head)
		return nullptr;
	int current_ord = 1;
	for (ListItem* i = head; i; i = i->next)
		if (i->value == v)
			if (current_ord++ == ord)
				return i;
	return nullptr;
}

template <class T>
int List<T>::insert_after(T& v, int after)
{
	if (!head)
		return 0;
	int inserted = 0;
	ListItem* tnext;
	for (ListItem* i = head; i; i = tnext)
	{
		tnext = i->next;
		if (i->value == after)
		{
			i->next = new ListItem(v);
			i->next->next = tnext;
			inserted++;
		}
	}
	return inserted;
}

template <class T>
int List<T>::insert_after(T& v, T& after, int ord)
{
	if (!head)
		return 0;
	int inserted = 0;
	int current_ord = 1;
	ListItem* tnext;
	for (ListItem* i = head; i; i = tnext)
	{
		tnext = i->next;
		if (i->value == after)
		{
			if (current_ord++ == ord)
			{
				i->next = new ListItem(v);
				i->next->next = tnext;
				inserted++;
			}
		}
	}
	return inserted;
}

template<class T>
int List<T>::insert_after(ListItem<T>* v, ListItem<T>* after)
{
	if (v == after)
		return 0;
	v->next = after->next;
	after->next = v;
	return 1;
}

template <class T>
int List<T>::insert_before(T& v, int before)
{
	if (!head)
		return 0;
	int inserted = 0;
	ListItem* tprev = head;
	for (ListItem* i = head; i; i = i->next)
	{
		if (i->value == before)
		{
			if (tprev == i)
			{
				tprev = new ListItem(v);
				tprev->next = i;
				head = tprev;
			}
			else
			{
				tprev->next = new ListItem(v);
				tprev->next->next = i;
			}
			inserted++;
		}
		tprev = i;
	}
	return inserted;
}

template <class T>
int List<T>::insert_before(T& v, T& before, int ord)
{
	if (!head)
		return 0;
	int inserted = 0, current_ord = 1;
	ListItem* tprev = head;
	for (ListItem* i = head; i; i = i->next)
	{
		if (i->value == before)
		{
			if (current_ord++ == ord)
			{
				if (tprev == i)
				{
					tprev = new ListItem(v);
					tprev->next = i;
					head = tprev;
				}
				else
				{
					tprev->next = new ListItem(v);
					tprev->next->next = i;
				}
				inserted++;
			}
		}
		tprev = i;
	}
	return inserted;
}

template <class T>
int List<T>::remove(T& v)
{
	if (!head)
		return 0;
	int deleted = 0;
	ListItem* i = head;
	ListItem *tprev = head, *tnext;
	for (; i; i = tnext)
	{
		tnext = i->next;
		if (i->value == v)
		{
			if (i == head)
				head = tnext;
			else
				tprev->next = tnext;
			delete i;
			deleted++;
		}
		else
			tprev = i;
	}
	return deleted;
}

template <class T>
int List<T>::remove(T& v, int ord)
{
	if (!head)
		return 0;
	int deleted = 0;
	ListItem* i = head;
	ListItem *tprev = head, *tnext;
	int current_ord = 1;
	for (; i; i = tnext)
	{
		tnext = i->next;
		if (i->value == v)
		{
			if (current_ord++ == ord)
			{
				if (i == head)
					head = tnext;
				else
					tprev->next = tnext;
				delete i;
				deleted++;
			}
			else
				tprev = i;
		}
		else
			tprev = i;
	}
	return deleted;
}

template <class T>
void List<T>::reverse()
{
	if (!head)
		return;
	ListItem *tprev = 0, *tnext;
	for (ListItem* i = head; i; i = tnext)
	{
		tnext = i->next;
		i->next = tprev;
		tprev = i;
	}
	head = tprev;
}

template <class T>
int* List<T>::array()
{
	if (!head)
		return nullptr;
	int* arr = new int[len()];
	int k = 0;
	for (ListItem* i = head; i; i = i->next)
		arr[k++] = i->value;
	return arr;
}

template <class T>
int List<T>::len() const
{
	if (!head)
		return 0;
	int k = 0;
	for (ListItem* i = head; i; i = i->next)
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

template <class T>
bool List<T>::operator==(List<T>& l)
{
	if (!head && !l.head)
		return true;
	if ((head && !l.head) || (!head && l.head))
		return false;
	ListItem *i = head, *j = l.head;
	for (; i || j; i = i->next, j = j->next)
	{
		if (((!i->next && j->next) || (i->next && !j->next)) || (i->value != j->value))
			return false;
	}
	return true;

}

template <class T>
List<T>& List<T>::operator+(List<T>& l)
{
	List* result = new List(*this);
	result->add(l);
	return *result;
}

template <class T>
List<T>& List<T>::operator+=(List<T>& l)
{
	this->add(l);
	return *this;
}

template <class T>
List<T>& List<T>::operator+(T& n)
{
	List* result = new List(*this);
	result->add(n);
	return *result;
}

template <class T>
List<T>& List<T>::operator+=(T& n)
{
	this->add(n);
	return *this;
}

template <class T>
List<T>& List<T>::operator-(T& n)
{
	List* result = new List(*this);
	result->remove(n);
	return *result;
}

template <class T>
List<T>& List<T>::operator-=(T& n)
{
	this->remove(n);
	return *this;
}

template <class T>
void List<T>::operator()(T& n)
{
	add(n);
}

template <class T>
List<T>::operator bool()
{
	return head != nullptr;
}

template <class T>
List<T>::operator int()
{
	return len();
}