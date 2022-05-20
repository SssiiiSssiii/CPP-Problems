

#include <iostream>
#include <cctype>
#include <string>
#include <set>
using namespace std;

string productionsRules[100];
int numberOfRules;

//Get string
string getString(string currentRule, int startFrom) {
	string str;
	for (int letter = startFrom; letter < currentRule.size(); letter++) {
		if (isspace(currentRule[letter]))//store letters till see a space.
			break;
		str += currentRule[letter];
	}
	return str;
}

//Get FirstTerminal
set<string> getFirstTerminal(string currentRule, string productionsRules[]) {

	set<string>firstSet;
	int indexOfTheFirstLetterAfterArrow = currentRule.find('>') + 2;
	char letter = currentRule[indexOfTheFirstLetterAfterArrow];

	if (!isupper(letter)) {

		firstSet.insert(getString(currentRule, indexOfTheFirstLetterAfterArrow));
		return firstSet;
	}
	else {
		string nonTerminal = getString(currentRule, indexOfTheFirstLetterAfterArrow);

		for (int rule = 0; rule < numberOfRules; rule++) {

			int indexOfTheLetterPerviousDash = productionsRules[rule].find("-") - 1;// GOAL -> B *****  index Of 'L'.
			string nonTerminal2 = productionsRules[rule].substr(0, indexOfTheLetterPerviousDash);

			if (nonTerminal2 == nonTerminal) {
				currentRule = productionsRules[rule];
				set<string> save = getFirstTerminal(currentRule, productionsRules);
				firstSet.insert(save.begin(), save.end());
			}
		}
		return firstSet;
	}
}


//Get FirstSet
set<string> getFirstSet(string nonTerminal) {
	string currentRule;
	set<string> firstSet;
	bool hasEpsilon = true;

	for (int rule = 0; rule < numberOfRules; rule++) {

		int indexOfTheLetterPerviousDash = productionsRules[rule].find("-") - 1;
		string nonTerminal2 = productionsRules[rule].substr(0, indexOfTheLetterPerviousDash);

		if (nonTerminal == nonTerminal2) {
			currentRule = productionsRules[rule];

			if (getFirstTerminal(currentRule, productionsRules).count("$")) {
				int indexOfTheFirstLetterAfterArrow = currentRule.find(">") + 2;
				char letter = currentRule[indexOfTheFirstLetterAfterArrow];

				for (int i = indexOfTheFirstLetterAfterArrow; i < currentRule.size(); i++) {

					letter = currentRule[i];

					if (!isupper(letter)) {
						firstSet.insert(getString(currentRule, i));
						hasEpsilon = false;
						break;
					}
					else {
						set<string> save = getFirstSet(getString(currentRule, i));
						firstSet.insert(save.begin(), save.end());

						if (firstSet.count("$"))
							firstSet.erase("$");
						else {
							hasEpsilon = false;
							break;
						}

						i += getString(currentRule, i).size();

					}
				}

			}
			else {
				set<string> save = getFirstTerminal(currentRule, productionsRules);
				firstSet.insert(save.begin(), save.end());
				hasEpsilon = false;
			}

		}
	}

	if (hasEpsilon)
		firstSet.insert("$");

	return firstSet;
}
int main() {

	cin >> numberOfRules;
	cin.ignore();

	for (int i = 0; i < numberOfRules; i++)
		getline(cin, productionsRules[i]);

	set<string>visited;

	for (int rule = 0; rule < numberOfRules; rule++) {

		string currentRule = productionsRules[rule];
		string nonTerminal = getString(currentRule, 0);
		set<string> firstSet;

		visited.insert(nonTerminal);

		//to know if the rule has been visited or not
		if (visited.count(nonTerminal) == 1) {

			firstSet = getFirstSet(nonTerminal);
			cout << "  first set(" << nonTerminal << ") = ";
			for (auto it : firstSet)
				cout << it << " ";
			cout << endl;
		}
	}

}
