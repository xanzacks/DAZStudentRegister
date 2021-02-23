// Menu Class
// Created by Jooyul Yoon and Jiayan Dong
// IDE: MSVS 2019

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "BinarySearchTree.h"
#include "Course.h"
#include "HashTable.h"
#include "BadHashTable.h"
#include "StackADT.h"

using namespace std;

// display table title
void displayTable()
{
	cout << "  CRN    Course\t\t\t  Title\t\t\t\t  time\t\t\tinstructor\t\t    location" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------\n";
}

// get CRN in a class object, passed to hash table functions
string getCRN(Course*& anItem)
{
	return anItem->getCRN();
}

// display the data of a course object Horizontally
void displayHorizontally(Course*& anItem) // display function to pass to BST traverse functions
{
	cout << " ";
	cout << right << setw(5) << anItem->getCRN() << "  "
		<< left << setw(11) << anItem->getName()
		<< left << setw(39) << anItem->getTitle()
		<< left << setw(25) << anItem->getTime()
		<< left << setw(26) << anItem->getInst()
		<< left << setw(7) << anItem->getLoc() << endl;
}

// display the data of a course object Vertically
void displayVertically(Course*& anItem)
{
	cout << "CRN: " << anItem->getCRN() << endl;
	cout << "Name: " << anItem->getName() << endl;
	cout << "Title: " << anItem->getTitle() << endl;
	cout << "Time: " << anItem->getTime() << endl;
	cout << "Instructor: " << anItem->getInst() << endl;
	cout << "Location: " << anItem->getLoc() << endl;
	cout << "\n=============================\n";
}

// Display CRN ONLY
void displayCRN(Course*& anItem) { cout << anItem->getCRN(); }

// compare CRN of a course object, compare function return -1 if left < right, return 0 if left = right, return 1 if left > right
// passed to BST and HST functions
int compareCrn(Course*& left, Course*& right) {
	if (left->getCRN() > right->getCRN())
		return 1;
	else if (left->getCRN() == right->getCRN())
		return 0;
	else
		return -1;
}

// compare name of a course object, compare function return -1 if left < right, return 0 if left = right, return 1 if left > right
// passed to BST functions
int compareName(Course*& left, Course*& right) {
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
	cout << "to the De Anza Math Course Database Program!\n\n";
}

// Display main menu
void displayMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "S - Search, Edit or Delete Course" << endl;
	cout << "L - List Course" << endl;
	cout << "A - Add New Course" << endl;
	cout << "D - Save the Data" << endl;
	cout << "U - Undo Delete" << endl;
	cout << "I - Database Information" << endl;
	cout << "E - To quit the program" << endl;
}

// Display search menu
void searchMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "C - Search, Edit or Delete by CRN" << endl;
	cout << "N - Search by Name" << endl;
	cout << "B - Back to Main Menu" << endl;
}

// Display edit Delete menu
void editDeleteMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "E - Edit" << endl;
	cout << "D - Delete" << endl;
	cout << "B - Back to search Menu" << endl;
}

// Display list menu
void listMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "U - List Unsorted Data" << endl;
	cout << "C - List data sorted by CRN" << endl;
	cout << "N - List data sorted by Name" << endl;
	cout << "T - Indented list sorted by CRN" << endl;
	cout << "B - Back to Main Menu" << endl;
}

// Display edit menu
void editMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "C - Edit CRN" << endl;
	cout << "N - Edit Name" << endl;
	cout << "T - Edit Title" << endl;
	cout << "M - Edit Time" << endl;
	cout << "I - Edit Instructor" << endl;
	cout << "L - Edit Location" << endl;
	cout << "B - Back to search Menu" << endl;
}

// Display undo menu
void undoMenu()
{
	cout << "Options Menu" << endl << endl;
	cout << "A - Add this course back and delete the course with same CRN" << endl;
	cout << "D - Delete this course" << endl;
	cout << "B - Back to Main Menu" << endl;
}

// save a course object data into an output file
// passed to hashtable functions
void saveCourse(ofstream& s, Course*& item)
{
	s << *item;
}

// delete a course object
// passed to hashtable functions
void deleteCourse(Course*& item)
{
	delete item;
}

// check if the integer is prime, if it's prime return true, else return false
bool isPrime(int num)
{
	bool isPrime = true;
	int i;
	for (i = 2; i <= num / 2; ++i)
	{
		if (num % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

/**********************************************************************
 Farewell information
 **********************************************************************/
void printDone(void)
{
	cout << "\n\n\t *~~*~~* THE END *~~*~~*\n"
		<< "     Thank you for using this program! \n\n";
}

// Menu Class, contain 2 BST, 2 HST and a linked list
class Menu
{
private:
	int hashTableSize; // hashtable size
	int count; // the number of data
	
	HashTable<Course*> hst; // hashtable
	BadHashTable<Course*> badHst; // bad hashtable
	BinarySearchTree<Course*> crnBst; // crn Binary search tree
	BinarySearchTree<Course*> nameBst; // name Binary search tree
	Stack<Course*> deletedList; // linked list store deleted data
	const string filename = "DeAnza_Math_Summer.txt"; // input and output filename

public:
	//Constructor: bulid 2 BST, 2 HST
	Menu();
	//Destructor: delete all course object and ADTs
	~Menu();
	//Main menu manager
	void manager();
	//search menu manager
	void searchManager();
	//search by CRN
	void searchByCRN();
	//search by name
	void searchByName();
	//edit Delete menu manager
	void editDeleteManager(Course*&);
	//edit manager
	void editManager(Course*&);
	//delete manager
	void deleteManager(Course*&);
	//list menu manager
	void listManager();
	//insert a new data manager
	void insertManager();
	//rewrite the txt file to save the data
	void saveTheData();
	//display database information and two HST information
	void printDatabaseInformation();
	//undo delete
	void undo();
	//reHash if the load factor is larger than 0.75
	void reHash();
};

//Constructor: bulid 2 BST, 2 HST
Menu::Menu()
{
	ifstream infile;
	string temp;

	infile.open(filename);
	if (!infile)
	{
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}
	infile >> count;

	hashTableSize = count * 2;
	while (!isPrime(hashTableSize))
		hashTableSize++;
	hst.setSize(hashTableSize);
	badHst.setSize(hashTableSize);
	getline(infile, temp, '\n');
	while (!infile.eof())
	{
		Course* pCourse = new Course;
		infile >> *pCourse;

		hst.insert(pCourse, getCRN, compareCrn);
		badHst.insert(pCourse, getCRN, compareCrn);
		crnBst.insert(pCourse, compareCrn);
		nameBst.insert(pCourse, compareName);
	}
	infile.close();
}

//Destructor: delete all course object and ADTs
Menu::~Menu()
{
	Course* temp;
	hst.printTable(deleteCourse);
	while (!deletedList.isEmpty())
	{
		deletedList.pop(temp);
		deleteCourse(temp);
	}
}

//Main menu manager
void Menu::manager()
{
	char choice;
	printWelcome();

	do
	{
		displayMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (toupper(choice))
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'S':
			system("cls");
			searchManager();
			break;
		case 'L':
			system("cls");
			listManager();
			break;
		case 'A':
			system("cls");
			insertManager();
			break;
		case 'D':
			system("cls");
			saveTheData();
			cout << "Data Saved" << endl;
			break;
		case 'U':
			system("cls");
			undo();
			break;
		case 'I':
			system("cls");
			printDatabaseInformation();
			break;
		case 'E':
			saveTheData();
			cout << "Thank you~" << endl;
			break;
		}
	} while (toupper(choice) != 'E');
}

//search menu manager
void Menu::searchManager()
{
	char choice;

	do
	{
		searchMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (toupper(choice))
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'C':
			system("cls");
			searchByCRN();
			break;
		case 'N':
			system("cls");
			searchByName();
			break;
		case 'B':
			system("cls");
			break;
		}
	} while (toupper(choice) != 'B');
}

//search by CRN
void Menu::searchByCRN()
{
	string crn;

	Course temp;
	Course* pTemp = &temp;
	Course* returnItem;

	cout << "Please enter CRN: ";
	cin.ignore();
	cin >> crn;
	pTemp->setCRN(crn);
	try
	{
		if (hst.search(pTemp, returnItem, getCRN, compareCrn))
		{
			editDeleteManager(returnItem);
		}
		else
			cout << "The Math Course with CRN " << crn << " is not in the DataBase." << endl;
	}
	catch (invalid_argument)
	{
		cout << "Invaild Input for CRN" << endl;
	}
	catch (out_of_range)
	{
		cout << "Invaild Input for CRN" << endl;
	}

}

//search by name
void Menu::searchByName()
{
	string name;
	cout << "Please enter Name: ";
	cin.ignore();
	getline(cin, name);
	Course temp;
	Course* pTemp = &temp;
	pTemp->setName(name);
	displayTable();
	nameBst.findVisit(pTemp, compareName, displayHorizontally);
}

//edit Delete menu manager
void Menu::editDeleteManager(Course*& item)
{
	char choice;

	do
	{
		displayVertically(item);
		editDeleteMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (toupper(choice))
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'E':
			system("cls");
			editManager(item);
			break;
		case 'D':
			system("cls");
			deleteManager(item);
			break;
		case 'B':
			system("cls");
			break;
		}
	} while (toupper(choice) != 'B' && toupper(choice) != 'D');
}

//edit manager
void Menu::editManager(Course*& item)
{

	char choice;
	string crn;
	string tempCrn;
	string name;
	string title;
	string time;
	string instructor;
	string location;
	bool goodCrn = false;
	Course* temp;

	do
	{
		displayVertically(item);
		editMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (toupper(choice))
		{
		default:
			cout << "Invalid input." << endl;
			cin.ignore(1024, '\n');
			break;
		case 'C':
			system("cls");
			do
			{
				tempCrn = item->getCRN();
				cout << "Enter CRN(End by ';'): ";
				cin.ignore();
				getline(cin, crn, ';');
				hst.remove(item, getCRN, compareCrn);
				badHst.remove(item, getCRN, compareCrn);
				crnBst.remove(item, compareCrn);
				item->setCRN(crn);
				try
				{
					if (!hst.search(item, temp, getCRN, compareCrn))
					{
						hst.insert(item, getCRN, compareCrn);
						badHst.insert(item, getCRN, compareCrn);
						goodCrn = true;
					}
					else
						cout << "Course with CRN " << crn << " already exists in the Database" << endl;
				}
				catch (invalid_argument)
				{
					cout << "Invaild Input for CRN" << endl;
					item->setCRN(tempCrn);
				}
			} while (!goodCrn);
			
			crnBst.insert(item, compareCrn);
			break;
		case 'N':
			system("cls");
			cin.ignore();
			cout << "Enter Name(End by ';'): ";
			getline(cin, name, ';');
			nameBst.remove(item, compareName);
			item->setName(name);
			nameBst.insert(item, compareName);
			break;
		case 'T':
			system("cls");
			cin.ignore();
			cout << "Enter Title(End by ';'): ";
			getline(cin, title, ';');
			item->setTitle(title);
			break;
		case 'M':
			system("cls");
			cin.ignore();
			cout << "Enter Time(End by ';'): ";
			getline(cin, time, ';');
			item->setTime(time);
			break;
		case 'I':
			system("cls");
			cin.ignore();
			cout << "Enter Instructor(End by ';'): ";
			getline(cin, instructor, ';');
			item->setInst(instructor);
			break;
		case 'L':
			system("cls");
			cin.ignore();
			cout << "Enter Location(End by Press Enter): ";
			getline(cin, location, '\n');
			item->setLoc(location);
			break;
		case 'B':
			system("cls");
			break;
		}
	} while (toupper(choice) != 'B');



}

//delete manager
void Menu::deleteManager(Course*& item)
{
	hst.remove(item, getCRN, compareCrn);
	badHst.remove(item, getCRN, compareCrn);
	crnBst.remove(item, compareCrn);
	nameBst.remove(item, compareName);

	deletedList.push(item);
	cout << "Course Deleted." << endl;
}

//list menu manager
void Menu::listManager()
{
	char choice;

	do
	{
		listMenu();
		cout << "Please enter your choice: ";
		cin >> choice;
		switch (toupper(choice))
		{
		default:
			cout << "Invalid input." << endl;;
			cin.ignore(1024, '\n');
			break;
		case 'U':
			system("cls");
			displayTable();
			hst.printTable(displayHorizontally);
			break;
		case 'C':
			system("cls");
			displayTable();
			crnBst.inOrder(displayHorizontally);
			break;
		case 'N':
			system("cls");
			displayTable();
			nameBst.inOrder(displayHorizontally);
			break;
		case 'T':
			system("cls");
			crnBst.printTree(displayCRN);
			break;
		case 'B':
			system("cls");
			break;
		}
	} while (toupper(choice) != 'B');
}

//insert a new data manager
void Menu::insertManager()
{
	string crn = "N/A";
	string name = "N/A";
	string title = "N/A";
	string time = "N/A";
	string instructor = "N/A";
	string location = "N/A";
	Course* temp;
	bool goodCrn = false;

	Course* pCourse = new Course;
	system("cls");
	do 
	{

		cout << "Enter CRN(End by ';'): ";
		cin.ignore();
		getline(cin, crn, ';');
		pCourse->setCRN(crn);
		try
		{
			if (!hst.search(pCourse, temp, getCRN, compareCrn))
			{
				hst.insert(pCourse, getCRN, compareCrn);
				badHst.insert(pCourse, getCRN, compareCrn);
				goodCrn = true;
			}
			else
				cout << "Course with CRN " << crn << " already exists in the Database" << endl;
		}
		catch (invalid_argument)
		{
			cout << "Invaild Input for CRN" << endl;
		}
		catch (out_of_range)
		{
			cout << "Invaild Input for CRN" << endl;
		}
	} while (!goodCrn);

	cout << "Enter Course(End by ';'): ";
	cin.ignore();
	getline(cin, name, ';');
	pCourse->setName(name);
	cout << "Enter Title(End by ';'): ";
	cin.ignore();
	getline(cin, title, ';');
	pCourse->setTitle(title);
	cout << "Enter Time(End by ';'): ";
	cin.ignore();
	getline(cin, time, ';');
	pCourse->setTime(time);
	cout << "Enter Instructor(End by ';'): ";
	cin.ignore();
	getline(cin, instructor, ';');
	pCourse->setInst(instructor);
	cout << "Enter location(End by Press Enter): ";
	cin.ignore();
	getline(cin, location, '\n');
	pCourse->setLoc(location);

	
	displayVertically(pCourse);


	crnBst.insert(pCourse, compareCrn);
	nameBst.insert(pCourse, compareName);

	reHash();
}

//rewrite the txt file to save the data
void Menu::saveTheData()
{
	system("cls");
	ofstream courseListOut(filename, ios::out);
	courseListOut << hst.getCount();
	hst.saveTable(courseListOut, saveCourse);
	courseListOut.close();
}

//undo delete
void Menu::undo()
{
	char choice;
	Course* deleted;
	Course* temp;
	system("cls");
	if (deletedList.isEmpty())
		cout << "No course has been deleted" << endl;
	else
	{
		deletedList.pop(deleted);
		displayVertically(deleted);
		if (hst.search(deleted, temp, getCRN, compareCrn))
		{
			do
			{
				cout << "You have added a course with the same CRN" << endl << endl;
			 
				undoMenu();
				cin >> choice;
				switch (toupper(choice))
				{
				default:
					cout << "Invalid input." << endl;;
					cin.ignore(1024, '\n');
					break;
				case 'A':
					deleteCourse(temp);
					hst.insert(deleted, getCRN, compareCrn);
					badHst.insert(deleted, getCRN, compareCrn);
					crnBst.insert(deleted, compareCrn);
					nameBst.insert(deleted, compareCrn);
					break;
				case 'D':
					deleteCourse(deleted);
					break;
				case 'B':
					system("cls");
					break;
				}
			} while (toupper(choice) != 'B');
		}
		else
		{
			hst.insert(deleted, getCRN, compareCrn);
			badHst.insert(deleted, getCRN, compareCrn);
			crnBst.insert(deleted, compareCrn);
			nameBst.insert(deleted, compareCrn);
		}
		reHash();
		cout << "Undo Delete Finished" << endl;
	}
}

//display database information and two HST information
void Menu::printDatabaseInformation()
{
	system("cls");
	cout << "Total " << hst.getCount() << " Math Course in the Database." << endl << endl;
	cout << "Good Hash Table" << endl;
	cout << "Hash Table Size: " << hst.getSize() << endl;
	cout << "The number of collision in the Hash Table: " << hst.getCollisions() << endl;
	cout << "Load factor of the Hash Table: " << hst.getLoadFactor() << endl << endl;

	cout << "Bad Hash Table" << endl;
	cout << "Hash Table Size: " << badHst.getSize() << endl;
	cout << "The number of collision in the Hash Table: " << badHst.getCollisions() << endl;
	cout << "Load factor of the Hash Table: " << badHst.getLoadFactor() << endl << endl;

	cout << "Developer Name: Jiayan Dong, Juyeol Yoon and Zeyu Zhao" << endl << endl;
}

//reHash if the load factor is larger than 0.75
void Menu::reHash()
{
	if (hst.getLoadFactor() < 0.75)
		return;
	saveTheData();
	int newSize = count * 2;
	while (!isPrime(newSize))
		newSize++;

	ifstream infile;
	string temp;
	infile.open(filename);
	if (!infile)
	{
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}
	hst.setSize(newSize);
	badHst.setSize(newSize);

	getline(infile, temp, '\n');
	while (!infile.eof())
	{
		Course* pCourse = new Course;
		infile >> *pCourse;

		hst.insert(pCourse, getCRN, compareCrn);
		badHst.insert(pCourse, getCRN, compareCrn);
	}
	infile.close();

	hashTableSize = newSize;
}

#endif // !MENU_H