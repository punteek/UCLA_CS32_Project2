#ifndef MAP_H
#define MAP_H

// Prateek Singh

#include <string>

typedef std::string KeyType;
typedef double ValueType;

class Map
{
public:
	Map();
	bool empty() const;
	int size() const;
	bool insert(const KeyType& key, const ValueType& value);
	bool update(const KeyType& key, const ValueType& value);
	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	bool erase(const KeyType& key);
	bool contains(const KeyType& key) const;
	bool get(const KeyType& key, ValueType& value) const;
	bool get(int i, KeyType& key, ValueType& value) const;
	void swap(Map& other);
	void dump() const;

	~Map();
	Map(const Map& src);
	Map& operator=(const Map& other);

private:

	struct KeyValuePair
	{
		KeyType aKey;
		ValueType aValue;
		KeyValuePair* next;
		KeyValuePair* prev;

		KeyValuePair(KeyType givenType, ValueType givenValue)
		{
			aKey = givenType;
			aValue = givenValue;
		}
	};

	KeyValuePair* head;
	KeyValuePair* tail;
	int currentSize;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);

#endif