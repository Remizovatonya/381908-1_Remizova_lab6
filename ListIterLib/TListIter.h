#pragma once
#include "iostream"
template<class T>
class TListIterator {
protected:
    int index;
    int* links;
    T* data;
public:
    TListIterator(int index, int* links, T* data);

    T& operator*(void);
    TListIterator<T>& operator++(int);
    TListIterator<T>& operator++();
    TListIterator<T>& operator=(const TListIterator<T>& _v);
    bool operator==(const TListIterator<T>& _iter);
    bool operator!=(const TListIterator<T>& _iter);

    ~TListIterator() = default;
    template <class T1>
    friend class TList;
};

template <class T>
TListIterator<T>::TListIterator(int index, int* links, T* data) {
    this->index = index;
    this->links = links;
    this->data = data;
}
template<class T>
T& TListIterator<T>::operator*() {
    return this->data[this->index];
}

template<class T>
TListIterator<T>& TListIterator<T>::operator++(int) {
    if (this->index >= 0) {
        this->index = this->links[this->index];
    }
    return *this;
}

template<class T>
TListIterator<T>& TListIterator<T>::operator++() {
    if (this->index >= 0) {
        this->index = this->links[this->index];
    }
    return *this;
}

template<class T>
bool TListIterator<T>::operator==(const TListIterator<T>& _iter) {
    return (this->index == _iter.index && this->links == _iter.links && this->data == _iter.data);
}

template<class T>
bool TListIterator<T>::operator!=(const TListIterator<T>& _iter) {
    return (this->index != _iter.index || this->links != _iter.links || this->data != _iter.data);
}

template<class T>
TListIterator<T>& TListIterator<T>::operator=(const TListIterator<T>& _v) {
    if (this != &_v) {
        return *this;
    }
    this->index = _v;
    this->data = _v.data;
    this->links = _v.data;
    return *this;
}