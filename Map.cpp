// Prateek Singh

#include "Map.h"
#include <iostream>
using namespace std;

// constructor for the map, no nodes
Map::Map()
{
	head = nullptr;
	tail = nullptr;
	currentSize = 0;
}

// destructor for the map
// loops through each node, deleting it as the iterator passes through the list
Map::~Map()
{
	KeyValuePair* deleteIterator = head;

	while (deleteIterator != nullptr)
	{
		KeyValuePair* tempStore = deleteIterator->next;

		delete deleteIterator;

		deleteIterator = tempStore;
	}
}

// copy constructor
// sets current size to zero, then inserts all elements from the source
Map::Map(const Map& src)
{
	currentSize = 0;

	for (int i = 0; i < src.currentSize; i++)
	{
		KeyType copyFromKey;
		ValueType copyFromValue;

		src.get(i, copyFromKey, copyFromValue);

		insert(copyFromKey, copyFromValue);
	}
}

// assignment operator
// contains similarities to both the destructor and the copy constructor
Map& Map::operator=(const Map& other)
{	
	if (this == &other)
	{
		return (*this);
	}
	else
	{
		KeyValuePair* deleteIterator = head;

		while (deleteIterator != nullptr)
		{
			KeyValuePair* tempStore = deleteIterator->next;

			delete deleteIterator;

			deleteIterator = tempStore;
		}

		head = nullptr;
		tail = nullptr; 
		currentSize = 0;

		for (int i = 0; i < other.currentSize; i++)
		{

			KeyType copyFromKey;
			ValueType copyFromValue;

			other.get(i, copyFromKey, copyFromValue);

			insert(copyFromKey, copyFromValue);
		}
	}
	return (*this);
}

// just return whether the list is empty or not
bool Map::empty() const
{
	return (currentSize == 0);
}

// just return the number of nodes in the list
int Map::size() const
{
	return currentSize;
}

bool Map::insert(const KeyType& key, const ValueType& value)	// inserting each element to the end of the list
{
	// first case: the list is empty

	if (empty())
	{
		KeyValuePair* toAdd = new KeyValuePair(key, value);
		toAdd->prev = nullptr;
		toAdd->next = nullptr;
		head = toAdd;
		tail = toAdd;
		currentSize++;
		return true;
	}

	// second case: the list has stuff, and we are adding a new node at the end of the list

	else
	{
		if (!contains(key))
		{
			KeyValuePair* toAdd = new KeyValuePair(key, value);
			
			toAdd->next = nullptr;
			toAdd->prev = tail;
			tail->next  = toAdd;
			tail = toAdd;
			currentSize++;
			return true;
		}
	}
	return false;	// this would mean that the key already exists in the list
}

// updates a value based on a given key
bool Map::update(const KeyType& key, const ValueType& value)
{
	if (contains(key))
	{
		KeyValuePair* iterator = head;
		
		while (iterator != nullptr)
		{
			if (iterator->aKey == key)
			{
				iterator->aValue = value;
				return true;
			}
			iterator = iterator->next;
		}
	}
	return false;	// the given key does not exist in the list
}
// checks whether a given key is in the current list
bool Map::contains(const KeyType& key) const
{
	KeyValuePair* iterator = head;

	while (iterator != nullptr)
	{
		if (iterator->aKey == key)
		{
			return true;
		}

		iterator = iterator->next;
	}
	return false;
}

// this will either update the value of the key based on given key, or, 
// if the key was not found, add the given key and value as a new element
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (contains(key))
	{
		update(key, value);
		return true;
	}

	else
	{
		insert(key, value);
		return true;
	}
}

// used to delete one node
bool Map::erase(const KeyType& key)
{
	if (empty())
	{
		return false;
	}

	if (head->aKey == key)
	{
		if (currentSize == 1)	// this means erasing would leave us with an empty list
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			currentSize--;
			return true;
		}

		else
		{
			KeyValuePair* temp = head->next;
			delete head;
			head = temp;
			head->prev = nullptr;
			currentSize--;
			return true;
		}
	}

	KeyValuePair* iterator = head;

	while (iterator != nullptr)
	{
		if (iterator->next != nullptr && iterator->next->aKey == key)
		{
			break;
		}
		iterator = iterator->next;
	}

	// at this point, the iterator points to the node right above the one we would like to delete
	// or, if the key was not found, the iterator points to nullptr

	if (iterator != nullptr)
	{
		// we need to check here if the iterator is at the last node
		
		if (iterator->next == tail)
		{
			KeyValuePair* killMe = tail;
			iterator->next = nullptr;
			delete killMe;
			tail = iterator;
			currentSize--;
			return true;
		}

		// this is if the node is not the last one in the list

		KeyValuePair* killMe = iterator->next;
		
		iterator->next = killMe->next;
		killMe->next->prev = iterator;
		delete killMe;
		currentSize--;
		return true;
	}
	// the key is never found in the map
	return false;
}

// used to find the value of a certain key in the list
bool Map::get(const KeyType& key, ValueType& value) const
{
	KeyValuePair* iterator = head;

	while (iterator != nullptr)
	{
		if (iterator->aKey == key)
		{
			value = iterator->aValue;
			return true;
		}

		iterator = iterator->next;
	}
	return false;
}

// used to find both the key and value of a certain given index of the list
bool Map::get(int i, KeyType& key, ValueType& value) const
{
	KeyValuePair* iterator = head;

	if (i >= 0 && i < currentSize)
	{
		KeyValuePair* iterator = head;
		for (int k = 1; k <= i; k++)
		{
			iterator = iterator->next;
		}

		// at this point, iterator points to the node we want to "get"

		key = iterator->aKey;
		value = iterator->aValue;
		return true;
	}
	return false;
}

// used to swap two lists, done by simply switching head and tail pointers and size values
void Map::swap(Map& other)
{
	// switch sizes

	int tempSize = currentSize;
	currentSize = other.currentSize;
	other.currentSize = tempSize;

	KeyValuePair* thisHead = head;
	KeyValuePair* thisTail = tail;

	head = other.head;
	tail = other.tail;

	other.head = thisHead;
	other.tail = thisTail;
}

// combines two maps according to given specification
bool combine(const Map& m1, const Map& m2, Map& result)
{
	if (m1.empty())
	{
		result = m2;
		return true;
	}

	if (m2.empty())
	{
		result = m1;
		return true;
	}
	
	// clears any values that result may previously have had
	result = m1;

	KeyType resultKey;
	ValueType resultValue;

	KeyType m2Key;
	ValueType m2Value;

	// used to keep track of whether a key with different values was ever compared, in this case the function must return false
	int keyMatchNotValue = 0;

	for (int i = 0; i < m2.size(); i++)
	{
		m2.get(i, m2Key, m2Value);

		if (!result.contains(m2Key))
		{
			result.insert(m2Key, m2Value);
		}

		else 
		{
			resultKey = m2Key;

			result.get(resultKey, resultValue);
			
			if (resultValue != m2Value)
			{
				result.erase(m2Key);
				keyMatchNotValue++;
			}
		}
	}

	if (keyMatchNotValue != 0)
	{
		return false;
	}
	return true;
}

/* 
  from specifications:
  When this function returns, result must contain a copy of all the pairs in m1
  whose keys don't appear in m2; it must not contain any other pairs. (You must
  not assume result is empty when it is passed in to this function; it may not be.)
*/

void subtract(const Map& m1, const Map& m2, Map& result)
{
	result = m1;

	KeyType m2Key;
	ValueType m2Value;

	for (int i = 0; i < m2.size(); i++)
	{
		m2.get(i, m2Key, m2Value);

		if (result.contains(m2Key))
		{
			result.erase(m2Key);
		}
	}
}

// this function is for my own purposes
// simply to print out the values of a given map
// does not change the state of the map that calls it
void Map::dump() const
{
	for (int i = 0; i < size(); i++)
	{
		KeyType keyPrint;
		ValueType valuePrint;

		get(i, keyPrint, valuePrint);

		cerr << " Pair " << i << " is: " << keyPrint << " " << valuePrint << endl;
	}
}