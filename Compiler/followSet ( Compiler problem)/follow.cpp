

#include <iostream>
#include <cctype>
#include <string>
#include <set>
using namespace std;

string productionsRules[100];
int numberOfRules;

//solve Recursion
set<string> solveR(string nonT1, string nonT2);

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

//Get FollowSet
set<string> getFollowSet(string nonTerminal, string rules[]) {
	string currentRule;
	set<string> followSet;

	for (int rule = 0; rule < numberOfRules; rule++) {
		if (rules[rule].find(nonTerminal) != rules[rule].npos) {
			currentRule = rules[rule];

			int indexOfTheLetterAfterArrow = currentRule.find(">") + 2;

			for (int letter = indexOfTheLetterAfterArrow; letter < currentRule.size(); letter++) {
				string nonTerminal2 = getString(currentRule, letter);
				letter += nonTerminal2.size();

				if (rules[0].substr(0, rules[rule].find('-') - 1) == nonTerminal)
					followSet.insert("-|");

				if (nonTerminal == nonTerminal2) {
					letter++;

					// case 1 : end of rule
					if (nonTerminal2.back() == currentRule.back()) {
						string temp;
						for (int v = currentRule.size() - 1; !isspace(currentRule[v]); v--)
							temp += currentRule[v];

						reverse(temp.begin(), temp.end());

						if (temp == nonTerminal && currentRule.substr(0, currentRule.find('-') - 1) != temp) {
							set<string>save = solveR(nonTerminal, getString(currentRule, 0));
							followSet.insert(save.begin(), save.end());
						}

					}
					//case 2 : Terminal
					else if (!isupper(currentRule[letter])) {
						followSet.insert(getString(currentRule, letter));
						letter += getString(currentRule, letter).size();
					}
					//case 3 : nonTerminal
					else if (isupper(currentRule[letter]) && nonTerminal2.back() != currentRule.back()) {
						set<string>save = getFirstSet(getString(currentRule, letter));

						if (save.count("$")) {
							save.erase("$");

							if (nonTerminal != getString(currentRule, letter)) {
								set<string>save2 = getFollowSet(getString(currentRule, letter), rules);
								save.insert(save2.begin(), save2.end());
							}
						}

						followSet.insert(save.begin(), save.end());
						--letter;
					}
				}
			}
		}
	}
	return followSet;
}

set<string> solveR(string nonT1, string nonT2) {

	string tempRules[100];
	int j = 0;

	for (int rule = 0; rule < numberOfRules; rule++) {
		string str;

		for (int letter = productionsRules[rule].size() - 1; !isspace(productionsRules[rule][letter]); letter--)
			str += productionsRules[rule][letter];

		if (str == nonT2 && productionsRules[rule].substr(0, productionsRules[rule].find('-') - 1) == nonT1)
			continue;
		else {
			tempRules[j] = productionsRules[rule];
			j++;
		}
	}
	return getFollowSet(nonT2, tempRules);
}

int main() {

	cin >> numberOfRules;
	cin.ignore();

	for (int i = 0; i < numberOfRules; i++)
		getline(cin, productionsRules[i]);

	multiset<string>visited;
	for (int rule = 0; rule < numberOfRules; rule++) {
		string currentRule = productionsRules[rule];
		string nonTerminal = getString(currentRule, 0);
		visited.insert(nonTerminal);

		set<string> followSet;

		////to know if the rule has been visited or not
		if (visited.count(nonTerminal) == 1) {
			followSet = getFollowSet(nonTerminal, productionsRules);

			cout << "  follow set(" << nonTerminal << ") = ";
			for (auto it : followSet)
				cout << it << " ";
			cout << endl;
		}
	}
}


