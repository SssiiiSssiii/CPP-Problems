#include<iostream>
using namespace std;

void main() {

	//Ascending order

	int const numberOfElmenets = 6;
	int elements[numberOfElmenets] = { 544,22,0,6,5,1 };

	for (int i = 0; i < numberOfElmenets - 1; i++) {

		for (int j = 0; j < numberOfElmenets - i - 1; j++) {
			if (elements[j] > elements[j + 1])
				swap(elements[j], elements[j + 1]);
		}

	}

	for (int j = 0; j < numberOfElmenets; j++)
		cout << elements[j] << endl;

}