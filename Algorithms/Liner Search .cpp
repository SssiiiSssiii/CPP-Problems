#include<iostream>
using namespace std;

void main() {

	int const numberOfElmenets = 5;
	int elements[numberOfElmenets] = { 1,6,1,3,2 }, i = 0;

	int key;
	cin >> key;

	while (i <= numberOfElmenets && key != elements[i])
		i++;

	if (i <= numberOfElmenets)
		cout << "Found";
	else
		cout << "Not Found";

}