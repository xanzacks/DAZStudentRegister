//
//  main.cpp
//  CIS22C GP
//
//  Created by zhaozeyu on 2019/6/5.
//  Copyright © 2019 zhaozeyu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Myhash.h"
#include "Course.h"

string Getstring(Course* a){
    return a->getCRN();
}

int main()
{
    Myhash<Course*,100> HashTable;
    const string DictionaryFileName = "DeAnza_Math_Summer.txt";
    
    ifstream fin(DictionaryFileName.c_str());
    if (!fin)
    {
        cerr << "Can't find " << DictionaryFileName << endl;
        exit(-1);
    }
    string temp;
    while (getline(fin, temp))
    {
        Course* tempobj;
        tempobj = new Course;
        size_t SpacePos = temp.find(" ");
        string CourseID = temp.substr(0, SpacePos - 5);
        tempobj -> setCRN(CourseID);
        HashTable.insert(tempobj, Getstring);
    }
    
    Course* temp1;
    temp1 = new Course;
    temp1 -> setCRN("00665");//you can change the number here to verify the find function
    temp.clear();
    cout << "Percent of hash table buckets used = " << setprecision(2) << fixed << 100 * HashTable.percentOfBucketsUsedBefore() << '%' << endl;
    HashTable.find(temp1, Getstring);
    HashTable.remove(temp1, Getstring);
    //HashTable.Printlist();
    cout << "Number of items in the HashTable = " << HashTable.size() << endl;
    cout << "Percent of hash table buckets used = " << setprecision(2) << fixed << 100 * HashTable.percentOfBucketsUsedAfter() << '%' << endl;
    cout << "Average non-empty bucket size = " << HashTable.averageNonEmptyBucketSize() << endl;
    cout << "Largest bucket size = " << HashTable.largestBucketSize() << endl;
    fin.close();
    fin.clear();
}
