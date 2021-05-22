#pragma once
#ifndef _MultiStack_
#define _MultiStack_

#include <iostream>
#include <math.h>

#include "TListIter.h"

using namespace std;

template <class T>
class TMultiStack
{
protected:
    int length; //размер массива стеков
    T* data; //массив одного стека 
    int stackCount; //количество стеков
    TStack<T>* stacks; //массив стеков 

    T** oldData; //массив старых начал (индексов)

    void StackRelocation(int index); //перепаковка мультистека, принимает индекс стека, в котором кончилось место

public:
    TMultiStack(int _size = 1, int _stackcount = 1);
    TMultiStack(const TMultiStack<T>& S);
    virtual ~TMultiStack();

    TMultiStack<T>& operator =(const TMultiStack<T>& S);
    bool operator ==(const TMultiStack<T>& S) const;
    bool operator !=(const TMultiStack<T>& S) const;

    void Push(T dannye, int i); //положить
    T Get(int i); //взять из вершины и удалить, либо посмотреть и удалить вершину

    bool IsEmpty(int i) const;
    bool IsFull(int i) const;

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TMultiStack<T1>& S);
    template <class T1>
    friend istream& operator>> (istream& istr, TMultiStack<T1>& S);

    int GetLength();

    void Resize(int _size = 1, int _stackcount = 1);
};

template<class T>
inline void TMultiStack<T>::StackRelocation(int index)
{
    int freeSize = 0;
    for (int i = 0; i < stackCount; i++)
        freeSize += stacks[i].GetLength() - stacks[i].GetInd();

    if (freeSize == 0)
        throw exception();

    int count = int(floor(double(freeSize) / stackCount)); //количество перераспределенных элементов для каждого стека
    int* sizes = new int[this->stackCount]; //массив новых размеров стеков
    for (int i = 0; i < stackCount - 1; i++) //делим равномерно между всеми стеками, в последний записываем с остатком
    {
        sizes[i] = stacks[i].GetLength()/*было Length*/ + count; //перераспределяем размер каждого стека (количество занятых + количество свободных перераспределенных)
    }
    int c = stacks[stackCount - 1].GetInd();
    sizes[this->stackCount - 1] = c + (freeSize - (count * (this->stackCount - 1))); //размер последнего стека

    T** newData = new T * [stackCount]; //массив новых начал (индексов)
    int k = 0; //номер элемента с которого начинается стек
    for (int i = 0; i < stackCount; i++) //перераспределяем размеры стеков
    {
        newData[i] = &(data[k]); //сохраняем индексы начал стеков
        k += sizes[i];
    }

    for (int i = 0; i < stackCount; i++)
    {
        if (newData[i] == oldData[i]) //когда совпадают индексы, изменяем размеры без перепаковки
        {
            stacks[i].SetData(newData[i], sizes[i], stacks[i].GetInd());
        }

        if (newData[i] < oldData[i]) //новое начало меньше старого начала, сдвигаем данные влево
        {
            for (int j = 0; j < stacks[i].GetInd(); j++)
            {
                newData[i][j] = oldData[i][j];
            }
            stacks[i].SetData(newData[i], sizes[i], stacks[i].GetInd());
        }

        if (newData[i] > oldData[i]) //новое начало больше старого начала
        {
            int k = i; //индекс последнего стека, у которого выполняется данное правило
            for (; k < stackCount; k++)
            {
                if (newData[k] > oldData[k])
                    continue;
                else break;
            }
            k--; //уменьшаем индекс k, так как он указывает либо на стек, у которого данное правило не выполняется, либо за границу массива стеков 

            for (int s = k; s < i; s--)
            {
                for (int j = stacks[s].GetInd() - 1; j >= 0; j--) //начиная с крайнего элемента в s-том стеке до нуля
                {
                    newData[s][j] = oldData[s][j];
                }
                stacks[s].SetData(newData[s], sizes[s], stacks[s].GetInd());
            }
        }
    }

    T** buf = oldData;
    this->oldData = newData;
    delete[] buf;
    delete[] sizes;
}

template <class T>
inline TMultiStack<T>::TMultiStack(int _size, int _stackcount)
{
    if (_size < 0 || _stackcount < 0)
        throw exception();

    this->length = _size;
    this->stackCount = _stackcount;
    this->data = new T[length];
    for (int i = 0; i < length; i++)
        this->data[i] = 0;

    int count = int(floor(double(_size) / stackCount)); //округление к низу, получаем целую часть от деления
    int* sizes = new int[this->stackCount]; //массив размеров стеков
    for (int i = 0; i < stackCount - 1; i++) //делим равномерно между всеми стеками, в последний записываем с остатком
    {
        sizes[i] = count;
    }
    sizes[stackCount - 1] = _size - (count * (stackCount - 1)); //размер последнего стека

    this->oldData = new T* [stackCount];

    this->stacks = new TStack<T>[stackCount]; //слздаем массив стеков длины количества стеков

    int k = 0; //номер элемента с которого начинается стек
    for (int i = 0; i < stackCount; i++) //перераспределяем размеры стеков
    {
        this->stacks[i].SetData(&(data[k]), sizes[i], 0);
        this->oldData[i] = &(data[k]); //сохраняем индексы начал стеков
        k += sizes[i];
    }
}

template <class T>
inline TMultiStack<T>::TMultiStack(const TMultiStack<T>& S)
{
    this->length = S.length;
    this->stackCount = S.stackCount;

    this->data = new T[length];
    for (int i = 0; i < length; i++)
        this->data[i] = S.data[i];
     
    this->oldData = new T * [stackCount];
    this->stacks = new TStack<T>[stackCount];
    for (int i = 0; i < stackCount; i++)
    {
        this->stacks[i] = S.stacks[i]; //вызов конструктора копирования стеков
        this->oldData[i] = S.oldData[i];
    }

}

template <class T>
inline TMultiStack<T>::~TMultiStack()
{
    this->length = 0;
    this->stackCount = 0;
  
    if (data != NULL)
    {
        delete[] data;
    }
    data = NULL;

    if (stacks != NULL)
    {
        delete[] stacks; //вызовется деструктор стеков
    }
}

template <class T>
inline TMultiStack<T>& TMultiStack<T>::operator =(const TMultiStack<T>& S)
{
    if (this == &S)
        return *this;
    if (length != S.length)
    {
        delete[] data;
        delete[] stacks;
        this->data = new T[S.length];
        this->stacks = new TStack<T>[stackCount];
    }
    this->length = S.length;
    this->ind = S.ind;

    for (int i = 0; i < length; i++)
        data[i] = S.data[i];

    for (int i = 0; i < stackCount; i++)
        this->stacks[i] = S.stacks[i];

    return *this;
}

template<class T>
inline bool TMultiStack<T>::operator==(const TMultiStack<T>& S) const
{
    if (length != S.length || ind != S.ind)
        return false;
    for (int i = 0; i < ind; i++)
        if (data[i] != S.data[i])
            return false;
    return true;
}

template<class T>
inline bool TMultiStack<T>::operator!=(const TMultiStack<T>& S) const
{
    if (length != S.length || ind != S.ind)
        return true;
    for (int i = 0; i < ind; i++)
        if (data[i] != S.data[i])
            return true;
    return false;
}

template<class T>
inline void TMultiStack<T>::Push(T dannye, int i)
{
    if (i < 0 || i >= stackCount)
        throw exception();
    if (this->stacks[i].IsFull())
        StackRelocation(i);
    this->stacks[i].Push(dannye);
}

template<class T>
inline T TMultiStack<T>::Get(int i)
{
    if (i < 0 || i >= stackCount)
        throw exception();
    if (this->stacks[i].IsEmpty())
        throw exception();
    T d = stacks[i].Get();;
    return d;
}

template<class T>
inline bool TMultiStack<T>::IsEmpty(int i) const
{
    if (i < 0 || i >= stackCount)
        throw exception();
        
    return stacks[i].IsEmpty();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int i) const
{
    if (i < 0 || i >= stackCount)
        throw exception();

    return stacks[i].IsFull();
}

template <class T1>
ostream& operator<< (ostream& ostr, const TMultiStack<T1>& S) 
{
    for (int i = 0; i < S.stackCount; i++)
    {

        ostr << S.stacks[i] << "  ";
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TMultiStack<T1>& S) 
{
    if (S.IsFull())
        throw "Stack is full";
    int stCount = 0;
    istr >> stCount; //количество элементов, которое хотим положить
    int size = 0;
    istr >> size;
    S.Resize(size, stCount);
   /* if (S.ind + stCount > S.length)
        throw exception();*/
    for (int i = 0; i < stCount; i++)
    {
        istr >> S.stacks[i];
    }
    return istr;
}

template <class T>
int TMultiStack<T>::GetLength()
{
    return length;
}

template<class T>
inline void TMultiStack<T>::Resize(int _size, int _stackcount)
{
    this->stacks[_stackcount].Resize(_size);
}

#endif //_MultiStack_