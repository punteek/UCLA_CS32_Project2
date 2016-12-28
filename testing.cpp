// Prateek Singh
// test cases

#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	// testing empty, size, insert, erase, and contains

	Map something;

	assert(something.empty() == true && something.size() == 0);

	something.insert("what", 17);
	something.insert("yay", 34);
	something.insert("i hope this works", 45);
	
	assert(something.empty() == false && something.size() == 3);
	assert(something.contains("what") && something.contains("yay") && something.contains("i hope this works"));

	something.erase("what");
	something.erase("yay");
	something.erase("i hope this works");

	assert(something.empty() == true && something.size() == 0);
	assert(!(something.contains("what") && something.contains("yay") && something.contains("i hope this works")));

	// test insert and insertOrUpdate

	something.insert("hello", 78);
	something.insert("omg", 99);

	assert(something.empty() == false && something.size() == 2);

	something.insertOrUpdate("hello", 345);

	assert(something.size() == 2);

	something.dump();
	cout << endl;

	// test update

	something.update("hello", 234);
	something.update("omg", 573);

	something.dump();
	cout << endl;

	// test copy constructor

	Map oneMap(something);

	oneMap.dump();

	assert(oneMap.empty() == false && oneMap.size() == 2);

	// copy constructor copied with nothing

	Map twoMap;

	Map threeMap(twoMap);

	twoMap.dump();
	cout << endl;
	threeMap.dump();
	cout << endl;

	assert(twoMap.empty() == true && threeMap.empty() == true && twoMap.size() == 0 && threeMap.size() == 0);

	// test assignment operator

	Map fourthMap;

	fourthMap.insert("hi", 4);
	fourthMap.insert("every", 235);
	fourthMap.insert("bye", 87);
	fourthMap.insert("cheese", 23);
	fourthMap.insert("sure", 284);

	Map fifthMap;

	fifthMap.insert("ok", 653);
	fifthMap.insert("yup", 75);

	fifthMap = fourthMap;

	fourthMap.dump();
	cout << endl;

	fifthMap.dump();
	cout << endl;

	assert(fourthMap.size() == 5 && fifthMap.size() == 5);

	// test assignment operator for assigning to an empty list

	Map sixthMap;

	Map seventhMap;

	seventhMap = sixthMap;

	// more testing of copy constructor (aliasing)

	seventhMap = fourthMap;

	cout << "seventhMap for the first time" << endl;
	seventhMap.dump();
		cout << endl;
	

	assert(seventhMap.empty() == false && seventhMap.size() == fourthMap.size());

	// actual testing of assignment operator for aliasing

	seventhMap = seventhMap;
	cout << "seventhMap for the second time" << endl;
	seventhMap.dump();
	cout << endl;

	// test swap

	Map map8;

	map8 = fourthMap;

	Map map9 = something;

	map9.swap(map8);

	map8.dump();
	cout << endl;

	map9.dump();
	cout << endl;

	assert(map9.size() == 5 && map8.size() == 2);

	// test combine with nothing in result

	Map result;

	combine(map8, map9, result);

	result.dump();

	assert(result.size() == 7);

	// test combine with starting with something in result

	Map map10;

	map10.insert("h", 1);
	map10.insert("e", 45);
	map10.insert("a", 86);
	map10.insert("r", 90);
	map10.insert("t", 865);
	
	Map map11;

	map11.insert("heaven", 356);

	Map end;

	end.insert("heaven", 356);

	combine(map10, map11, end);

	end.dump();

	assert(end.size() == 6);

	// test combine with nothing in first map

	Map map12;
	Map map13(something);
	Map finalMap;
	combine(map12, map13, finalMap);

	finalMap.dump();
	cout << endl;

	assert(finalMap.size() == 2 && finalMap.empty() == false);

	// test subtract

	Map map14;
	Map map15;

	map14.insert("ha", 1);
	map14.insert("haha", 2);
	map14.insert("haha", 3);
	map14.insert("hahaha", 4);
	
	map15.insert("ha", 1);
	map15.insert("hahaha", 4);

	subtract(map14, map15, finalMap);

	finalMap.dump();
	cout << endl;

	assert(finalMap.size() == 1 && finalMap.empty() == false);

	cout << "Passed all tests" << endl;
}