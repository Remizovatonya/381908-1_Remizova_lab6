#include <iostream>
#include "Stack.h"
#include "MultiStack.h"

int main()
{
	int k, n;

	TMultiStack<int>a(3, 3);
	TMultiStack<int>a(9, 3);
	a.Push(1, 0);
	a.Push(2, 2);
	a.Push(2, 0);
	a.Push(3, 1);
	a.Push(4, 1);
	a.Push(5, 2);
	a.Push(6, 0);
	a.Push(7, 0);
	cout << a;
	a.Push(8, 0);
	cout << a;
	a.Push(9, 0);
	cout << a;
	return 0;
	//cin >> k; //ввести размер стека
	//TStack<int> S(k);
	//cout << S.GetInd() << " - ind " << S.IsEmpty() << " and " << S.IsFull() << endl;
	//cin >> n; //ввести элемент который необходимо положить в стек
	//S.Push(n);
	//cout << S.GetInd() << " - ind " <<  S.IsEmpty() << " and " << S.IsFull() << endl;
	//cin >> S; //ввести количество элементов и сам стек
	//cout << S.GetInd() << " - ind " << S.IsEmpty() << " and " << S.IsFull() << endl;
	//cout << S.Get() << endl;
	//cout << S << endl << endl;

	TStack<int> S(5);
	S.Push(3);
	S.Push(2);
	S.Push(1);
	TStack<int> K(S);

	cout << K << endl << endl;
	cout << S << endl << endl;


	//cin >> k; //ввести размер стека мультистеков
	//cin >> n; //ввести количество стеков в мультистеке
	//TMultiStack<int> MS(k, n);
	//cout << MS << endl;
	//cout << MS.GetLength() << " - size of stacks " << MS.IsEmpty(1) << " and " << MS.IsFull(1) << endl;

	//MS.Push(1, 0);
	//MS.Push(6, 1);
	//MS.Push(7, 1);
	//MS.Push(2, 1);
	//MS.Push(3, 2);
	//MS.Push(4, 2);

	//cout << MS << endl;
	//cout << MS.GetLength() << " - size of stacks " << MS.IsEmpty(1) << " and " << MS.IsFull(1) << endl;


}