#pragma once
#ifndef _Stack_
#define _Stack_

#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
    int length;
    T* data;
    int ind; //вершина стека
    bool IsHaveData; //принадлежат ли данные стеку
public:
    TStack() {};
    TStack(int _size, bool _f = true);
    TStack(const TStack<T>& S);
    virtual ~TStack();

    TStack<T>& operator =(const TStack<T>& S);
    bool operator ==(const TStack<T>& S) const;
    bool operator !=(const TStack<T>& S) const;

    void Push(T dannye); //положить
    T Get(); //взять из вершины и удалить, либо посмотреть  и удалить вершину
    void SetData(T* _x, int _size, int _ind); //добавить данные снаружи

    bool IsEmpty(void) const;
    bool IsFull(void) const;

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TStack<T1>& S);
    template <class T1>
    friend istream& operator>> (istream& istr, TStack<T1>& S);

    int GetLength();
    int GetInd();

    void Resize(int _size);
};

template <class T>
inline TStack<T>::TStack(int _size, bool _f)
{
    if (_size < 0)
        throw exception();

    this->length = _size;
    this->IsHaveData = _f;
    if (IsHaveData)
    {
        data = new T[length];
        for (int i = 0; i < length; i++)
            data[i] = 0;
    }
    this->ind = 0;
}

template <class T>
inline TStack<T>::TStack(const TStack<T>& S)
{
    this->length = S.length;
    this->ind = S.ind;
    this->IsHaveData = S.IsHaveData;
    if (IsHaveData)
    {
        data = new T[length];
        for (int i = 0; i < length; i++)
            data[i] = S.data[i];
    }
    else this->data = S.data;
}

template <class T>
inline TStack<T>::~TStack()
{
    this->length = 0;
    this->ind = 0;
    if (IsHaveData)
    {
        if (data != NULL)
            delete[] data;
        else throw exception();
        data = NULL;
    }
}


template <class T>
inline TStack<T>& TStack<T>::operator =(const TStack<T>& S)
{
    if (this == &S)
        return *this;
   
    this->IsHaveData = S.IsHaveData;
    if (IsHaveData)
    {
        if (length != S.length)
        {
            delete[] data;
            data = new T[S.length];
        }
        this->length = S.length;
        for (int i = 0; i < length; i++)
            data[i] = S.data[i];
    }
    else this->data = S.data;

    this->ind = S.ind;
   
    return *this;
}

template<class T>
inline bool TStack<T>::operator==(const TStack<T>& S) const
{
    if (length != S.length || ind != S.ind)
        return false;
    for (int i = 0; i < ind; i++)
        if (data[i] != S.data[i])
            return false;
    return true;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack<T>& S) const
{
    if (length != S.length || ind != S.ind)
        return true;
    for (int i = 0; i < ind; i++)
        if (data[i] != S.data[i])
            return true;
    return false;
}

template<class T>
inline void TStack<T>::Push(T dannye)
{
    if (this->IsFull())
        throw exception();
    this->data[ind] = dannye;
    ind++;
}

template<class T>
inline T TStack<T>::Get()
{
    if (this->IsEmpty())
        throw exception();
    T d = data[ind - 1];
    ind--;
    return d;
}

template<class T>
inline void TStack<T>::SetData(T* _x, int _size, int _ind)
{
  /*  if (IsHaveData)
        if (data!=NULL)
            delete[] data;*/
    this->length = _size;
    this->IsHaveData = false;
    this->data = _x;
    this->ind = _ind;
}

template<class T>
inline bool TStack<T>::IsEmpty(void) const
{
    if (ind == 0)
        return true;
    else return false;
}

template<class T>
inline bool TStack<T>::IsFull(void) const
{
    if (ind >= length)
        return true;
    else return false;
}

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1>& S) 
{
    for (int i = 0; i < S.ind; i++)
    {
        ostr << S.data[i] << " ";
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1>& S) 
{
    if (S.IsFull())
        throw "Stack is full";
    int count;
    istr >> count; //количество элементов, которое хотим положить
    if (S.ind + count > S.length)
        throw exception();
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        S.Push(d);
    }
    return istr;
}

template <class T>
int TStack<T>::GetLength()
{
    return length;
}

template <class T>
int TStack<T>::GetInd()
{
    return ind;
}

template<class T>
inline void TStack<T>::Resize(int _size)
{
    if (_size <= 0)
        throw exception();

    if (data == NULL)
    {
        delete[] data;
        this->data = new T[_size];
    }
    else
    {
        T* d = new T[_size];
        for (int i = 0; i < this->GetInd(); i++)
            d[i] = Get();
        delete[] data;
        this->data = new T[_size];
        for (int i = 0; i < 1; i++)
            this->data[i] = d[i];
    }
}

#endif //_Stack_