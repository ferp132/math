#include "stdafx.h"
#include <iostream>

using namespace std;


int main()
{
	int const length = 5;
	int ToSort[length] = { 2, 5, 1, 3, 4 };
	int Temp;

	cout << "Before sort: " << endl << endl;
	for (int j = 0; j < length; j++)\
	{
		cout << ToSort[j];
	}


	for (int i = length - 1; i > 0; i--)
	{
		for (int k = 0; k < i; k++)\
		{
			if (ToSort[k] > ToSort[k + 1])
			{
				Temp = ToSort[k];
				ToSort[k] = ToSort[k + 1];
				ToSort[k + 1] = Temp;
			}
		}
	}

	cout << endl << endl <<  "After sort: " << endl << endl;
	for (int j = 0; j < length; j++)\
	{
		cout << ToSort[j];
	}

	int wait;
	cin >> wait;
    return 0;
}

