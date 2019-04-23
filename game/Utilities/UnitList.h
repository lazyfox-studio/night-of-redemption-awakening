#pragma once
#include "../Headers/Unit.h"

class UnitListItem
{
public:
	Unit* value;
	UnitListItem* next;
	UnitListItem();
	UnitListItem(Unit*);
};

class UnitList
{
	UnitListItem* head;
public:
	UnitList();
	UnitList(UnitList&);
	//UnitList(Unit*, Unit);
	~UnitList();

	void add(Unit*);            // place value-pointer in item and join to end (not copy)
	void add(UnitList&);        // join list to end
	void delete_all();          // delete all items and valuable objects
	void remove(Unit*);         // find item by value-pointer and delete it
	void drop(Unit*);           // remove item without valuable object deletion
	void remove(UnitListItem*); // find item by item-pointer and delete it
	int len() const;
	UnitList& operator=(UnitList&);
};

UnitListItem::UnitListItem()
{
	next = nullptr;
}

UnitListItem::UnitListItem(Unit* _value)
{
	value = _value;
	next = nullptr;
}

UnitList::UnitList()
{
	head = nullptr;
}

UnitList::UnitList(UnitList& l)
{
	head = nullptr;
	add(l);
}

UnitList::~UnitList()
{
	delete_all();
}

void UnitList::add(Unit* value)
{
	if (!head) 
	{
		head = new UnitListItem();
		head->value = value;
	}
	else
	{
		UnitListItem* i = head;
		for (i = head; i->next; i = i->next);
		i->next = new UnitListItem();
		i->next->value = value;
	}
}

void UnitList::add(UnitList& l)
{
	if (l.head)
	{
		if (head)
		{
			UnitListItem* i = head;
			for (i = head; i->next; i = i->next);
			for (UnitListItem* j = l.head; j; j = j->next)
			{
				i->next = new UnitListItem(j->value);
				i = i->next;
			}
		}
		else
		{
			head = new UnitListItem(l.head->value);
			if (head->next)
			{
				UnitListItem*i, *j;
				for (i = head, j = l.head->next; j; i = i->next, j = j->next)
				{
					i->next = new UnitListItem(j->value);
				}
			}
		}
	}
}

void UnitList::delete_all()
{
	if (!head)
		return;
	UnitListItem* i = head;
	UnitListItem* del = i;
	while (i)
	{
		i = i->next;
		delete del->value;
		delete del;
		del = i;
	}
}

void UnitList::remove(Unit* elem)
{
	if (!head)
		return;
	if (head->value == elem)
	{
		delete elem;
		UnitListItem* del = head;
		if (head->next)
			head = head->next;
		else
			head = nullptr;
		delete del;
		return;
	}
	for(UnitListItem* i = head; i->next; i = i->next)
		if (i->next->value == elem)
		{
			UnitListItem* tnext = i->next->next;
			delete elem;
			delete i->next;
			i->next = tnext;
			break;
		}
}

void UnitList::drop(Unit* elem)
{
	if (!head)
		return;
	if (head->value == elem)
	{
		UnitListItem* del = head;
		if (head->next)
			head = head->next;
		else
			head = nullptr;
		delete del;
		return;
	}
	for (UnitListItem* i = head; i->next; i = i->next)
		if (i->next->value == elem)
		{
			UnitListItem* tnext = i->next->next;
			delete i->next;
			i->next = tnext;
			break;
		}
}

inline void UnitList::remove(UnitListItem* item)
{
	if (!head)
		return;
	if (head == item)
	{
		delete item->value;
		UnitListItem* del = head;
		if (head->next)
			head = head->next;
		else
			head = nullptr;
		delete del;
		return;
	}
	for (UnitListItem* i = head; i->next; i = i->next)
		if (i->next == item)
		{
			UnitListItem* tnext = i->next->next;
			delete i->next->value;
			delete i->next;
			i->next = tnext;
			break;
		}
}

int UnitList::len() const
{
	if (!head)
		return 0;
	int k = 0;
	for (UnitListItem* i = head; i; i = i->next)
		k++;
	return k;
}

UnitList& UnitList::operator=(UnitList& l)
{
	if (this == &l)
		return *this;
	delete_all();
	add(l);
	return *this;
}