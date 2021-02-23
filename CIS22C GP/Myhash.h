// File: Myhash.h

#ifndef HASH_H
#define HASH_H

#include "list.h"
#include <iostream>

template <typename T, unsigned buckets >
class Myhash
{
    List<T>* array;
    // hash function borrowed from: Thomas Wang https://gist.github.com/badboy/6267743
    unsigned hash(string key) const
    {
        unsigned TKey = stoi(key);
        int c2 = 0x27d4eb2d; // a prime or an odd constant
        TKey = (TKey ^ 61) ^ (TKey >> 16);
        TKey = TKey + (TKey << 3);
        TKey = TKey ^ (TKey >> 4);
        TKey = TKey * c2;
        TKey = TKey ^ (TKey >> 15);
        return TKey % buckets;
    }
    unsigned size_; // number of values stored in the hash table
public:
    Myhash();
    ~Myhash();

    unsigned size() const
    {
        return size_;
    }
    bool insert(T value, string func(T));//insert new node to linked list
    bool remove(T value, string func(T));//remove a node from hash table
    void find(T value, string func(T)) const;//return true if found
    unsigned bucketSize(unsigned bucket) const;//return the size of hash table
    void printoutputfile() const;
    float percentOfBucketsUsed() const;//return load factor
    float percentOfBucketsUsedBefore() const;
    float percentOfBucketsUsedAfter() const;
    float averageNonEmptyBucketSize() const;//give the average non-empty bucket size
    unsigned largestBucket() const;//give the position in hash table of the lagest bucket
    unsigned largestBucketSize() const;//return the bucket size of the latgest bucket
    void Printlist() const;
};

template <typename T, unsigned buckets>
Myhash<T, buckets>::Myhash() : size_(0), array(new List<T>[buckets]){}
template <typename T, unsigned buckets>
Myhash<T, buckets>::~Myhash(){ delete [] array; }

template <typename T, unsigned buckets>
bool Myhash<T, buckets>::insert(T value, string func(T))
{
    string convert = func(value);
    if(array[hash(convert)].find(value, func) == 0){
        array[hash(convert)].push(value);
    }
    else{
        return false;
    }
    size_++;
    return true;
}

template <typename T, unsigned buckets>
bool Myhash<T, buckets>::remove(T value, string func(T))
{
    string convert = func(value);
    array[hash(convert)].remove(value, func);
    return true;
}


template <typename T, unsigned buckets>
void Myhash<T, buckets>::find(T value,  string func(T)) const
{
    string convert = func(value);
    if(array[hash(convert)].find(value, func) != 0){
        cout << "Data found at " << hash(convert) << endl;
        cout << *array[hash(convert)].find(value, func) << endl;
    }
    else{
        cout << "I did not find it" << endl;;
    }
}

template <typename T, unsigned buckets>
unsigned Myhash<T, buckets>::bucketSize(unsigned bucket) const
{
    return array[bucket].size();
}

template <typename T, unsigned buckets>
void Myhash<T, buckets>::printoutputfile() const
{
    static ofstream fout("buckets_contents.txt");
    for (unsigned i = 0; i < buckets; i++) {
        if(array[i].size() != 0){
            fout << array[i];
        }
    }
    fout.close();
}

template <typename T, unsigned buckets>
float Myhash<T, buckets>::averageNonEmptyBucketSize() const
{
    unsigned nonEmptyBuckets = 0;
    float sum = 0;
    for (unsigned i = 0; i < buckets; i++) {
        if (bucketSize(i)) {
            nonEmptyBuckets++;
            sum += bucketSize(i);
        }
    }
    return sum / nonEmptyBuckets;
}

template <typename T, unsigned buckets>
float Myhash<T, buckets>::percentOfBucketsUsed() const
{
    static ofstream fout("bucket_contents_nums.txt");
    unsigned numberOfBucketsUsed = 0;
    for (unsigned i = 0; i < buckets; i++) {
            fout << i << ' ' << bucketSize(i) << endl;
        if (bucketSize(i)) numberOfBucketsUsed++;
    }
    fout.close();
    return static_cast<float> (numberOfBucketsUsed) / buckets;
}

template <typename T, unsigned buckets>
float Myhash<T, buckets>::percentOfBucketsUsedBefore() const
{
    static ofstream fout("bucket_contents_before.txt");
    unsigned numberOfBucketsUsed = 0;
    for (unsigned i = 0; i < buckets; i++) {
        if(array[i].size() != 0){
            fout << array[i];
        }
        if (bucketSize(i)) numberOfBucketsUsed++;
    }
    fout.close();
    return static_cast<float> (numberOfBucketsUsed) / buckets;
}

template <typename T, unsigned buckets>
float Myhash<T, buckets>::percentOfBucketsUsedAfter() const
{
    static ofstream fout("bucket_contents_after.txt");
    unsigned numberOfBucketsUsed = 0;
    for (unsigned i = 0; i < buckets; i++) {
        if(array[i].size() != 0){
            fout << array[i];
        }
        if (bucketSize(i)) numberOfBucketsUsed++;
    }
    fout.close();
    return static_cast<float> (numberOfBucketsUsed) / buckets;
}

template <typename T, unsigned buckets>
unsigned Myhash<T, buckets>::largestBucket() const
{
    unsigned largestBucket = 0;
    unsigned largestBucketSize = 0;
    for (unsigned i = 0; i < buckets; i++) {
        if (bucketSize(i) > largestBucketSize) {
            largestBucketSize = bucketSize(i);
            largestBucket = i;
        }
    }
    return largestBucket;
}

template <typename T, unsigned buckets>
unsigned Myhash<T, buckets>::largestBucketSize() const
{
    return bucketSize(largestBucket());
}

template <typename T, unsigned buckets>
void Myhash<T, buckets>::Printlist() const
{
    for(unsigned i = 0; i < buckets; i++){
        cout << "The data at postition " << i << endl;
        if(array[i].size() != 0){
            cout << array[i] << endl;
        }
        else{
            cout << endl;
        }
    }
}

#endif
