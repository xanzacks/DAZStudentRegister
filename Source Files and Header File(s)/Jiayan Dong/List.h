// the Linked List class
// Created by Zeyu Zhao
// Modified by: Jiayan Dong
// IDE: MSVS 2019

#ifndef LIST_H
#define LIST_H

using namespace std;

//compare function return -1 if left < right, return 0 if left = right, return 1 if left > right
template <class T>
class List
{
private:
	//linked list node
    struct ListNode{
        T value;
        ListNode *next;
    };
    ListNode *head; // sentinel node
    int count; // number of data stored in linked lis
    
public:
    //Constructor
	List() { head = new ListNode; head->next = head; count = 0; }
    
    // Linked list operations
	//Compare function return -1 is left < right, return 1 is left > right, return 0 is left = right
	// insert a node at the end
    bool insertNode(T, int compare(T&, T&));
	// find and then remove a node
	bool deleteNode(T, int compare(T&, T&));
	// find a target node
	bool searchList( T, T&, int compare(T&, T&));

	// save the data into a output file
	void saveList(ofstream&, void save(ofstream&, T&));

	// display all data in Linked list
	void printList(void visit(T&));

	// return the number of the data in linked list
    int getCount() {return count;}
    
    //Destructor
	~List();
};

//Destructor
template <class T>
List<T>::~List()
{
	ListNode* currNode, * nextNode;

	currNode = head->next;

	while (currNode != head && currNode != NULL)
	{
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	delete head;
}

// insert a node at the end
template <class T>
bool List<T>::insertNode(T item, int compare(T&, T&))
{	
	ListNode *currNode, *preNode;
	preNode = head;
	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		if (compare(item, currNode->value) == 0)
			return false;
		preNode = currNode;
		currNode = currNode->next;
	}

	ListNode* newNode = new ListNode;
	newNode->value = item;
	newNode->next = NULL;
	if (currNode == head)
		head->next = newNode;
	else
		preNode->next = newNode;
	count++;

	return true;
}

// find and then remove a node
template <class T>
bool List<T>::deleteNode(T item, int compare(T&, T&))
{
	ListNode* currNode, * preNode;

	preNode = head;
	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		if (compare(item, currNode->value) == 0)
		{
			preNode->next = currNode->next;
			delete currNode;
			count--;
			return true;
		}
		preNode = currNode;
		currNode = currNode->next;
	}

	return false;
}

// find a target node
template <class T>
bool List<T>::searchList( T item, T& returnItem, int compare(T&, T&))
{
	ListNode* currNode, * preNode;

	preNode = head;
	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		if (compare(item, currNode->value) == 0)
		{
			returnItem = currNode->value;
			return true;
		}
		preNode = currNode;
		currNode = currNode->next;
	}
	return false;
}

// save the data into a output file
template <class T>
void List<T>::saveList(ofstream& s, void save(ofstream&, T&))
{
	ListNode* currNode;

	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		T item = currNode->value;
		save(s, item);
		currNode = currNode->next;
	}
}

// display all data in Linked list
template <class T>
void List<T>::printList(void visit(T&))
{
	ListNode* currNode;

	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		T item = currNode->value;
		visit(item);
		currNode = currNode->next;
	}
}
#endif
