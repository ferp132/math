#include "stdafx.h"
#include <iostream>

using namespace std;


int main()
{
	int const length = 5;
	int ToSort[length] = { 2, 5, 1, 3, 4 };
	int Temp = 0;
	int biggest = 0;
	int last = 0;

	cout << "Before sort: " << endl << endl;
	for (int j = 0; j < length; j++)\
	{
		cout << ToSort[j];
	}


	for (int i = length - 1; i > 0; i--)
	{
		for (int k = 0; k < i; k++)
		{
			if (ToSort[k] > Temp)
			{
				biggest = k;
				Temp = ToSort[k];
			}
			last = k+1;
		}
		Temp = ToSort[biggest];
		ToSort[biggest] = ToSort[last];
		ToSort[last] = Temp;
		Temp = 0;
	}

	cout << endl << endl << "After sort: " << endl << endl;
	for (int j = 0; j < length; j++)\
	{
		cout << ToSort[j];
	}

	int wait;
	cin >> wait;
	return 0;
}

