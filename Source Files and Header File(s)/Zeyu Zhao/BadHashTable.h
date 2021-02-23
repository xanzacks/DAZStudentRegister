// Hash Table ADT
// Created by Zeyu Zhao
// Modified by: Jiayan Dong
// IDE: MSVS 2019
#ifndef BAD_HASH_TABLE_H
#define BAD_HASH_TABLE_H

#include"List.h"
#include <string>

//compare function return -1 if left < right, return 0 if left = right, return 1 if left > right
//get fucntion get the value in data as hash key
template <class T>
class BadHashTable
{
	List<T>* array;
	// hash function
	int hash(string key) const
	{
		key = key.substr(4);
		int TKey = stoi(key);
		return TKey % size;
	}
	int size;  // hash table size
	int count; // number of data stored in the hash table
public:
	//Constructor
	BadHashTable() { size = 100; count = 0; array = new List<T>[size]; }
	BadHashTable(int s) { size = s; count = 0; array = new List<T>[size]; }

	// Destructor
	~BadHashTable() { delete[] array; }

	// Clear the data in hash table and then reset hash table size
	void setSize(int s);

	// insert a node at the correct location
	bool insert(T value, string get(T&), int compare(T&, T&));//insert new node to linked list
	// find and then remove a node
	bool remove(T value, string get(T&), int compare(T&, T&));//remove a node from hash table
	// find a target node
	bool search(T value, T& returnvalue, string get(T&), int compare(T&, T&));//return true if found

	// save the data into a output file
	void saveTable(ofstream&, void save(ofstream&, T&));

	// display all data in hash table
	void printTable(void visit(T&)) const;

	// return hash table size
	int getSize() const { return size; }

	//return the number of data in hash table
	int getCount() const { return count; }

	//return the number of getCollisions in hash table
	int getCollisions() const;

	//return the load factor of hash table
	double getLoadFactor() const;
};

// Clear the data in hash table and then reset hash table size
template <class T>
void BadHashTable<T>::setSize(int s)
{
	delete[] array;
	count = 0;
	size = s;
	array = new List<T>[s];
}

// insert a node at the correct location
template <class T>
bool BadHashTable<T>::insert(T item, string get(T&), int compare(T&, T&))
{
	string key = get(item);
	int hashValue = hash(key);
	if (array[hashValue].insertNode(item, compare))
	{
		count++;
		return true;
	}
	else
		return false;
}

// find and then remove a node
template <class T>
bool BadHashTable<T>::remove(T item, string get(T&), int compare(T&, T&))
{
	string key = get(item);
	int hashValue = hash(key);
	if (array[hashValue].deleteNode(item, compare))
	{
		count--;
		return true;
	}
	else
		return false;
}

// find a target node
template <class T>
bool BadHashTable<T>::search(T item, T& returnValue, string get(T&), int compare(T&, T&))
{
	string key = get(item);
	int hashValue = hash(key);
	if (array[hashValue].searchList(item, returnValue, compare))
		return true;
	else
		return false;
}

// save the data into a output file
template <class T>
void BadHashTable<T>::saveTable(ofstream& s, void visit(ofstream&, T&))
{
	for (int i = 0; i < size; i++)
		array[i].saveList(s, visit);
}

// display all data in hash table
template <class T>
void BadHashTable<T>::printTable(void visit(T&)) const
{
	for (int i = 0; i < size; i++)
		array[i].printList(visit);
}

//return the number of getCollisions in hash table
template <class T>
int BadHashTable<T>::getCollisions() const
{
	int collision = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i].getCount() > 1)
			collision += array[i].getCount() - 1;
	}
	return collision;
}

//return the load factor of hash table
template <class T>
double BadHashTable<T>::getLoadFactor() const
{
	double load = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i].getCount() > 0)
			load++;
	}
	return load / size;
}
#endif
