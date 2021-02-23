// File: list.h
#ifndef LIST_H
#define LIST_H

using namespace std;

template<typename T>
class Node {
    T data_;
    Node* next_;
    Node(const Node&); // disable copy ctor
public:
    Node();
    Node(T d, Node* n);
    const T& data() const;
    T& data();
    Node* next() const;
    Node*& next();
};

template<typename T> Node<T>::Node()
: data_(), next_(0) {
}

template<typename T> Node<T>::Node(T d, Node* n)
: data_(d), next_(n) {
}

template<typename T> const T& Node<T>::data() const {
    return data_;
}

template<typename T> T& Node<T>::data() {
    return data_;
}

template<typename T> Node<T>* Node<T>::next() const {
    return next_;
}

template<typename T> Node<T>*& Node<T>::next() {
    return next_;
}

template<typename T> ostream& operator<<(ostream& out, const Node<T>& N) {
    out << N.data();
    return out;
}

template<typename T> class List {
    Node<T>* top_;
public:
    List();
    ~List();
    void push(T object);
    T pop();
    const Node<T>* top() const;
    bool remove(T object, string CRN(T));
    const Node<T>* find(const T& object, string CRN(T)) const;
    unsigned size() const;
};

template<typename T> ostream& operator<<(ostream& out, const List<T>& L) {
    const Node<T>* ptr = L.top();
    while (ptr) {
        out << (*ptr) << endl;
        ptr = ptr -> next();
    }
    return out;
}

template<typename T> List<T>::List()
: top_(0) {
}

template<typename T> List<T>::~List() {
    Node<T>* ptr = top_;
    while (ptr) {
        top_ = top_->next();
        delete ptr;
        ptr = top_;
    }
}

template<typename T> void List<T>::push(T object) {
    Node<T>* ptr = new Node<T>(object, top_);
    top_ = ptr;
}

template<typename T> const Node<T>* List<T>::top() const {
    return top_;
}

template<typename T> T List<T>::pop() {
    Node<T>* ptr = top_;
    top_ = top_ -> next();
    T data = ptr->data();
    delete ptr;
    return data;
}

template<typename T> const Node<T>* List<T>::find(const T& object, string CRN(T)) const {
    const Node<T>* ptr = top();
    while (ptr) {
        string a = CRN(ptr->data());
        string b = CRN(object);
        if (CRN(ptr->data()) == CRN(object)) {
            return ptr;
        }
        ptr = ptr->next();
    }
    return 0;
}

template<typename T> unsigned List<T>::size() const {
    const Node<T>* ptr = top();
    unsigned sz = 0;
    while (ptr) {
        sz++;
        ptr = ptr->next();
    }
    return sz;
}

template<typename T> bool List<T>::remove(T object, string func(T)) {
    if (!find(object, func)) {
        cerr << object << " not found\n";
        return false;
    }
    Node<T>* ptr2current = top_;
    Node<T>* ptr2previous = top_;
    if (func(top_->data()) == func(object)) {
        top_ = top_ -> next();
        delete ptr2current;
        return true;
    }
    while (ptr2current) {
        ptr2current = ptr2current->next();
        if (func(ptr2current->data()) == func(object)) {
            ptr2previous->next() = ptr2current->next();
            delete ptr2current;
            return true;
        }
        ptr2previous = ptr2current;
    }
    return false;
}

#endif
