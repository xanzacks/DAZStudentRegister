#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "BinarySearchTree.h"
#include "Course.h"
#include "HashTable.h"

using namespace std;

void displayTable()
{
	cout << "  CRN    Course    Title\t\t\t\t\t  time\t\t instructor\t\t location" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------\n";
}

string getCRN(Course*& anItem)
{
	return anItem->getCRN();
}

void displayHorizonal(Course*& anItem) // display function to pass to BST traverse functions
{
	cout << " ";
	cout << right << setw(5) << anItem->getCRN() << "   "
		<< left << setw(9) << anItem->getName()
		<< left << setw(39) << anItem->getTitle()
		<< left << setw(24) << anItem->getTime()
		<< left << setw(26) << anItem->getInst()
		<< left << setw(7) << anItem->getLoc() << endl;
}

void displayVertical(Course*& anItem)
{
	cout << "CRN: " << anItem->getCRN() << endl;
	cout << "Title: " << anItem->getTitle() << endl;
	cout << "Time: " << anItem->getTime() << endl;
	cout << "Instructor: " << anItem->getInst() << endl;
	cout << "Location: " << anItem->getLoc() << endl;
	cout << "\n=============================\n";
}

void displayCourse(Course*& anItem) { cout << anItem->getCRN() << endl; } // Display CRN ONLY

int compareCrn(Course*& left, Course*& right)
{
	if (left->getCRN() > right->getCRN())
		return 1;
	else if (left->getCRN() == right->getCRN())
		return 0;
	else
		return -1;
}

int compareName(Course*& left, Course*& right)
{
	if (left->getName() > right->getName())
		return 1;
	else if (left->getName() == right->getName())
		return 0;
	else
		return -1;
}

/*********************************************************************
 Welcome function
 *********************************************************************/
void printWelcome()
{
	cout << "\n\n\t *~~*~~* WELCOME *~~*~~*\n\n";
	cout << "\tto the De Anza Math Course Database Program!\n\n";
}

void menu()
{
	cout << "Options Menu" << endl << endl;
	cout << "S - Search Course" << endl;
	cout << "L - List Course" << endl;
	cout << "A - Add New Course" << endl;
	cout << "D 每 Save the Data" << endl;
	cout << "I 每 Database Information" << endl;
	cout << "E 每 To quit the program" << endl;
}

void searchMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "C - Search by CRN" << endl;
	cout << "N - Search by Name" << endl;
	cout << "B 每 Back to Main Menu" << endl;
}

void editMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "E - Edit" << endl;
	cout << "D - Delete" << endl;
	cout << "B 每 Back to search Menu" << endl;
}

void listMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "U - List Unsorted Data" << endl;
	cout << "C - List data sorted by CRN" << endl;
	cout << "N 每 List data sorted by Name" << endl;
	cout << "B 每 Back to Main Menu" << endl;
}

void saveCourse(ofstream& s, Course*& item)
{
	s << *item;
}

void deleteCourse(Course*& item)
{
	delete item;
}

/**********************************************************************
 Farewell information
 **********************************************************************/
void printDone(void)
{
	cout << "\n\n\t *~~*~~* THE END *~~*~~*\n"
		<< "     Thank you for using this program! \n\n";
}


class Menu
{
private:
	const int HASH_TABLE_SIZE = 61;
	
	HashTable<Course*> hst = HashTable<Course*>(HASH_TABLE_SIZE);
	BinarySearchTree<Course*> crnBst;
	BinarySearchTree<Course*> nameBst;
	const string filename = "DeAnza_Math_Summer.txt";

public:
	Menu();
	~Menu();
	void manager();
	void searchManager();
	void searchByCRN();
	void searchByName();
	void editDeleteManager(Course*&);
	void editManager(Course*&);
	void deleteManager(Course*&);
	void listManager();
	void insertManager();
	void saveTheData();
	void printDatabaseInformation();

};


Menu::Menu()
{
	ifstream infile;

	Course* pCourse;
	infile.open(filename);
	if (!infile)
	{
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}
	infile.seekg(2);
	while (!infile.eof())
	{
		pCourse = new Course;
		infile >> *pCourse;
		hst.insert(pCourse, getCRN, compareCrn);
		crnBst.insert(pCourse, compareCrn);
		nameBst.insert(pCourse, compareName);
	}
	infile.close();
}

void Menu::manager()
{
	char choice;
	printWelcome();

	do
	{
		menu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'S':
			searchManager();
			break;
		case 'L':
			listManager();
			break;
		case 'A':
			insertManager();
			break;
		case 'D':
			saveTheData();
			break;
		case 'I':
			printDatabaseInformation();
			break;
		case 'E':
//			bst.clear();
			break;
		}
	} while (choice != 'E');
}

void Menu::searchManager()
{
	char choice;

	do
	{
		searchMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'C':
			searchByCRN();
			break;
		case 'N':
			searchByName();
			break;
		case 'B':
			break;
		}
	} while (choice != 'B');
}

void Menu::searchByCRN()
{
	string crn;
	cout << "Please enter CRN: ";
	cin.ignore();
	cin >> crn;
	Course temp;
	Course* pTemp = &temp;
	Course* returnItem;
	pTemp->setCRN(crn);
	if (hst.search(pTemp, returnItem, getCRN, compareCrn))
	{
		displayVertical(returnItem);
		editManager(returnItem);
	}
	else
		cout << "The Math Course with CRN " << crn << " is not in the DataBase." << endl;
}
//
void Menu::searchByName()
{

}

void Menu::editDeleteManager(Course*& item)
{
	char choice;

	do
	{
		editMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'E':
			editManager(item);
			break;
		case 'D':
			deleteManager(item);
			break;
		case 'B':
			break;
		}
	} while (choice != 'B');
}
//
void Menu::editManager(Course*& item)
{
	
}

void Menu::deleteManager(Course*& item)
{
	hst.remove(item, getCRN, compareCrn);
	crnBst.remove(item, compareCrn);
	nameBst.remove(item, compareName);

	delete item;
	cout << "Course Deleted." << endl;
}

void Menu::listManager()
{
	char choice;

	do
	{
		listMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'U':
			displayTable();
			hst.printTable(displayHorizonal);
			break;
		case 'C':
			displayTable();
			crnBst.inOrder(displayHorizonal);
			break;
		case 'N':
			displayTable();
			nameBst.inOrder(displayHorizonal);
			break;
		case 'B':
			break;
		}
	} while (choice != 'B');
}

void Menu::insertManager()
{

}

void Menu::saveTheData()
{
	ofstream courseListOut(filename, ios::out);
	hst.saveTable(courseListOut, saveCourse);
	courseListOut.close();
}

void Menu::printDatabaseInformation()
{
	cout << "Total " << hst.getCount() << " Math Course in the Database." << endl;
	cout << "Hash Table Size: " << hst.getSize() << endl;
	cout << "The number of collision in the Hash Table: " << hst.getCollisions() << endl;
	cout << "Load factor of the Hash Table: " << hst.getLoadFactor() << endl << endl;

	cout << "Developer Name: Jiayan Dong, Juyeol Yoon and Zeyu Zhao" << endl;
}

Menu::~Menu()
{
	hst.printTable(deleteCourse);
}


#endif