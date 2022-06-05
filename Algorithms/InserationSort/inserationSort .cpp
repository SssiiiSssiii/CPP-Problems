#include<iostream>
using namespace std;

void main()
{
	int const numberOfElmenets = 5;
	int elements[numberOfElmenets] = { 1,5,2,4,3 };

	for (int j = 1; j < numberOfElmenets; j++) {

		int key = elements[j];
		int i = j - 1;

		while (i >= 0 && elements[i] > key) {

			elements[i + 1] = elements[i];
			i = i - 1;

		}
		elements[i + 1] = key;
	}

	for (int i = 0; i < numberOfElmenets; i++)
		cout << elements[i];

}