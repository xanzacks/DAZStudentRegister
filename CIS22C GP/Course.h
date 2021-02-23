// Specification file for the Course class
// Written By: Jiayan Dong
// IDE: MSVS 2019

#ifndef COURSE_H
#define COURSE_H

#include <iostream>

using std::string;

class Course
{
private:
	string CRN;
	string name;
	string instructor;
	int capacity;
	string location;
	string dateTime;

public:
	// Constructors
	Course() = default;
    Course(string crn, string n, string i, int cap, string l, string d);// I set the data type of crn to string, since we have some crn started with 0 such as mosh's 1D: 00665

	// Setters
	void setCRN(string crn) { CRN = crn; }
	void setName(string n) { name = n; }
	void setInstructor(string i) { instructor = i; }
	void setCapacity(int cap) { capacity = cap; }
	void setLocation(string l) { location = l; }
	void setDateTime(string d) { dateTime = d; }


	// Getters
	string getCRN() const { return CRN; }
	string getName() const { return name; }
	string getInstructor() const { return instructor; }
	int getCapacity() const { return capacity; }
	string getLocation() const { return location; }
	string getDatTime() const { return dateTime; }
    bool operator==(const Course&) const;
    friend ostream& operator<<(ostream&, const Course&);
    operator unsigned() const;
    
};
ostream& operator<<(ostream& out, const Course& a){
    out << a.CRN << a.name << a.instructor;
    return out;
}

bool Course::operator==(const Course& a) const{
    if(CRN == a.CRN){
        return true;
    }
    else{
        return false;
    }
}

#endif
