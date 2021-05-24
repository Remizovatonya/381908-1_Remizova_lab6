#pragma once
#include <fstream>
#include "iostream"
#include "TListIter.h"
using namespace std;
template <class T>
class TList
{
protected:
    T* data;
    int* links;
    int count;
    int size;
    int root;
public:
    explicit TList(int _size = 1);
    TList(int _size, int _count);
    TList(TList<T>& _v);
    ~TList();

    TList<T>& operator =(TList<T>& _v);

    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TListIterator<T> iter, T d);

    bool IsEmpty(void) const;
    bool IsFull(void) const;
    int GetCount(void) const;

    T GetFirst();
    T GetLast();

    void DelFirst();
    void DelLast();
    void Del(TListIterator<T> iter);

    TList<int>& multiplesToK(int k);

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TList<T1>& A);
    template <class T1>
    friend istream& operator>> (istream& istr, TList<T1>& A);

    static TList<T>& load(const char* name);
    void save(const char* name);

    typedef TListIterator<T> iterator;
    iterator begin() {
        return TListIterator<T>(this->root, this->links, this->data);
    };
    iterator end() {
        return TListIterator<T>(-1, this->links, this->data);
    };


};


template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1>& A) {
    int last_elem = A.root;
    while (A.links[last_elem] != -1) {
        ostr << A.data[last_elem] << " ";
        last_elem = A.links[last_elem];
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1>& A) {
    for (int i = 0; i < A.count; i++)
    {
        T1 d;
        istr >> d;
        A.InsLast(d);
    }
    return istr;
}

template<class T>
TList<T>::TList(int _size)
{
    if (_size <= 0)
        throw std::range_error("Wrong list size");
    this->size = _size;
    this->data = new T[_size];
    this->links = new int[_size];
    for (int i = 0; i < _size; ++i) {
        this->links[i] = -2;
    }
    this->count = 0;
    this->root = -1;
}
template<class T>
TList<T>::TList(int _size, int _count)
{
    if (_size <= 0)
        throw std::range_error("Wrong list size");

    this->size = _size;
    this->data = new T[_size];
    this->links = new int[_size];
    for (int i = 0; i < _size; ++i) {
        this->links[i] = -2;
    }
    this->count = _count;
    this->root = -1;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
    this->size = _v.size;
    this->count = _v.count;
    this->root = _v.root;
    this->data = new T[this->size];
    this->links = new int[this->size];
    for (int i = 0; i < this->size; ++i) {
        this->links[i] = _v.links[i];
        this->data[i] = _v.data[i];
    }
}
template <class T>
TList<T>::~TList()
{
    if (this->data != 0) {
        delete[] this->data;
        delete[] this->links;
        this->data = 0;
        this->links = 0;
        this->count = 0;
        this->size = 0;
    }
}

template <class T>
TList<T>& TList<T>::operator =(TList<T>& _v)
{
    if (this == &_v)
        return *this;

    if (this->size != _v.size) {
        delete[] this->data;
        delete[] this->links;
        this->data = new T[_v.size];
        this->links = new int[_v.size];
    }
    this->size = _v._size;
    this->count = _v.count;
    this->root = _v.root;


    for (int i = 0; i < this->size; ++i) {
        this->links[i] = _v.links[i];
        this->data[i] = _v.data[i];
    }

    return *this;
}

template<class T>
inline void TList<T>::InsFirst(T d)
{
    if (this->IsFull())
        throw std::overflow_error("List overflow");

    int i = 0;
    while (i != this->size) {
        if (this->links[i] == -2)
            break;
        i++;
    }
    this->data[i] = d;
    this->links[i] = this->root;
    this->root = i;
    this->count++;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
    if (this->IsFull())
        throw std::overflow_error("List overflow");

    if (this->IsEmpty()) {
        this->root = 0;
        this->data[0] = d;
        this->links[0] = -1;
        this->count++;
        return;
    }

    int free_slot = 0;
    while (free_slot != this->size) {
        if (this->links[free_slot] == -2)
            break;
        free_slot++;
    }

    int last_elem = this->root;
    while (this->links[last_elem] != -1) {
        last_elem = this->links[last_elem];
    }

    this->data[free_slot] = d;
    this->links[free_slot] = -1;
    this->links[last_elem] = free_slot;
    this->count++;
}

template<class T>
inline void TList<T>::Ins(TListIterator<T> iter, T d)
{
    if (this->IsFull())
        throw std::overflow_error("List overflow");
    int index = iter.index;

    int free_slot = 0;
    while (free_slot != this->size) {
        if (this->links[free_slot] == -2)
            break;
        free_slot++;
    }

    this->links[free_slot] = this->links[index];
    this->links[index] = free_slot;
    this->data[free_slot] = d;
    this->count++;
}

template<class T>
inline bool TList<T>::IsEmpty(void) const
{
    return this->count == 0;
}

template<class T>
inline bool TList<T>::IsFull(void) const
{
    return this->count >= this->size;
}

template<class T>
inline T TList<T>::GetFirst()
{
    return this->data[this->root];
}

template<class T>
inline T TList<T>::GetLast()
{
    for (int i = 0; i < this->size; ++i) {
        if (this->links[i] == -1) {
            return this->data[i];
        }
    }
}

template<class T>
inline void TList<T>::DelFirst()
{
    if (this->IsEmpty())
        throw std::overflow_error("List is empty");
    int deleting_element = this->root;
    this->root = this->links[this->root];
    this->links[deleting_element] = -2;
    this->count--;
}

template<class T>
inline void TList<T>::DelLast()
{
    if (this->IsEmpty())
        throw std::overflow_error("List is empty");

    if (this->root == 1) {
        this->links[this->root] = -2;
        this->root = 1;
    }
    else {
        int before_last_elem = this->root;
        int last_elem = this->links[this->root];
        while (this->links[last_elem] != -1) {
            before_last_elem = last_elem;
            last_elem = this->links[last_elem];
        }

        this->links[before_last_elem] = -1;
        this->links[last_elem] = -2;
    }
    this->count--;
}

template<class T>
inline void TList<T>::Del(TListIterator<T> iter)
{
    if (this->IsEmpty())
        throw std::overflow_error("List is empty");
    if (iter.index == this->root) {
        this->DelFirst();
        return;
    }
    int index = iter.index;
    int before_delete_element = this->root;
    while (this->links[before_delete_element] != index) {
        before_delete_element = this->links[before_delete_element];
    }
    this->links[before_delete_element] = this->links[index];
    this->links[index] = -2;
    this->count--;
}

template<class T>
inline int TList<T>::GetCount() const
{
    return this->count;
}

template<class T>
TList<T>& TList<T>::load(const char* name) {
    std::ifstream file;
    file.open(name, std::fstream::in);
    if (!file.is_open())
        throw "Cant open such file";
    int size; int count;
    file >> size; file >> count;
    char* list = new TList(size, count);
    file >> list;
    file.close();
    return *list;
}

template<class T>
void TList<T>::save(const char* name) {
    fstream file;
    file.open(name, fstream::out);
    if (!file.is_open())
        throw "Cant open such file";
    file << this->size << " " << this->count << "\n" << *this;
    file.close();
}

template<class T>
TList<int>& TList<T>::multiplesToK(int k) {
    TList<int>* c = new TList(this->size);
    iterator i = this->begin();
    while (i != this->end()) {
        if (*i % k == 0) {
            c->InsLast(*i);
        }
        i++;
    }
    return *c;
}