#include "stdafx.h"
#include <iostream>

using namespace std;


int main()
{
	int const length = 10;
	int ToSort[length] = { 2, 5, 1, 3, 4, 6, 7, 8, 3, 5 };
	int InspectedElem = 0;
	int TempForSwap = 0;
	//int step = 1;

	cout << "Before sort: " << endl << endl;
	for (int j = 0; j < length; j++)\
	{
		cout << ToSort[j];
	}



	for (int elementsSorted = 0; elementsSorted < length - 1; elementsSorted++)
	{
		InspectedElem = elementsSorted + 1;
		for (int lastsorted = elementsSorted; lastsorted >= 0; lastsorted--)
		{
			
			// It is at the right position
			if (ToSort[InspectedElem] > ToSort[lastsorted])
			{
				break;
			}
			else
			{
				TempForSwap = ToSort[lastsorted];
				ToSort[lastsorted] = ToSort[InspectedElem];
				ToSort[InspectedElem] = TempForSwap;
				InspectedElem--;
			}


			/*
			if (InspectedElem <= ToSort[lastsorted])
			{
				TempForSwap = ToSort[lastsorted];
				ToSort[lastsorted] = ToSort[lastsorted + 1];
				ToSort[lastsorted + 1] = TempForSwap;
				

			}
			else
			{
				ToSort[i] = ToSort[InspectedElem];
			}
			*/
		}
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

