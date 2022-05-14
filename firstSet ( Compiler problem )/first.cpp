

#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

string productionsRules[1000];
int nubmerOfRules;

//Get Terminal
string getTerminal(string currentRule, int stratFrom) {
	string terminal;
	for (int letter = stratFrom; letter < currentRule.size(); letter++) {
		if (isupper(currentRule[letter])) {
			cout << "PLEASE FOLLOW THER RULES.\n"; exit(0);
		}
		if (isspace(currentRule[letter]))//store letters till see a space.
			break;
		terminal += currentRule[letter];
	}
	return terminal;
}

//Get NonTerminal
string getNonTerminal(string currentRule, int stratFrom) {
	string nonTerminal;
	for (int letter = stratFrom; letter < currentRule.size(); letter++) {
		if (islower(currentRule[letter])) {
			cout << "PLEASE FOLLOW THE RULES.\n"; exit(0);
		}
		if (isspace(currentRule[letter]))//store letters till see a space.
			break;
		nonTerminal += currentRule[letter];
	}
	return nonTerminal;
}

//Get First Terminal
set<string> firstTerminal(string currentRule, string productionsRules[]) {
	set<string> firstSet;//using set to avoid repetition.
	int indexOfTheFirstLetterAfterArrow = currentRule.find('>') + 2;
	char TerminalOrNonTerminal = currentRule[indexOfTheFirstLetterAfterArrow];//get first char after arrow and then check if is it Terminal or not.

	if (!isupper(TerminalOrNonTerminal)) { //that's mean is a Terminal
		firstSet.insert(getTerminal(currentRule, indexOfTheFirstLetterAfterArrow));//get the wohle string and store it.
		return firstSet;
	}
	else {
		string nonTerminal = getNonTerminal(currentRule, indexOfTheFirstLetterAfterArrow);
		//get the firstSet of the NonTerminal at all Rules.
		for (int rule = 0; rule < nubmerOfRules; rule++) {
			int indexOfTheLetterPreviousDash = productionsRules[rule].find('-') - 1;// GOAL -> B *****  index Of 'L'
			string anotherNonTerminal = productionsRules[rule].substr(0, indexOfTheLetterPreviousDash);//get the whole string **** "GOAL"

			if (nonTerminal == anotherNonTerminal) {
				currentRule = productionsRules[rule];
				set<string> save = firstTerminal(currentRule, productionsRules);//get the new FirstSet and store it in the previous FirstSet
				firstSet.insert(save.begin(), save.end());
			}
		}
		return firstSet;
	}
	return firstSet;
}

//Get the First Set
set<string> getFirstSet(string NonTerminal) {
	string currentRule;
	set<string> firstSet;
	bool hasEpsilon = true;
	for (int rule = 0; rule < nubmerOfRules; rule++) {
		int indexOfTheLetterPreviousDash = productionsRules[rule].find('-') - 1;// GOAL -> B *****  index Of 'L'.
		string anotherNonTerminal = productionsRules[rule].substr(0, indexOfTheLetterPreviousDash);

		if (NonTerminal == anotherNonTerminal) { // match the first NonTerminal at each rule.
			currentRule = productionsRules[rule];

			//No repetition
			if (firstTerminal(currentRule, productionsRules).count("$")) {
				int indexOfTheFirstLetterAfterArrow = currentRule.find('>') + 2;
				char TerminalOrNonTerminal = currentRule[indexOfTheFirstLetterAfterArrow];

				for (int letter = indexOfTheFirstLetterAfterArrow; letter < currentRule.size(); letter++) {
					if (!isspace(TerminalOrNonTerminal)) {
						if (!isupper(TerminalOrNonTerminal)) {

							firstSet.insert(getTerminal(currentRule, letter));
							hasEpsilon = false;
							break;
						}
						else {

							//to save from override
							set<string> save = getFirstSet(getNonTerminal(currentRule, letter));
							firstSet.insert(save.begin(), save.end());

							if (firstSet.count("$"))
								firstSet.erase("$");
							else {
								hasEpsilon = false;
								break;
							}
							letter += getNonTerminal(currentRule, letter).size();
							if (letter < currentRule.size())
								TerminalOrNonTerminal = currentRule[letter + 1];
						}
					}
				}
			}

			else {
				hasEpsilon = false;
				set<string> save = firstTerminal(currentRule, productionsRules);
				firstSet.insert(save.begin(), save.end());
			}

		}
	}

	if (hasEpsilon)
		firstSet.insert("$");

	return firstSet;
}
int main()
{
	cin >> nubmerOfRules;
	cin.ignore();

	//get productions rules
	for (int i = 0; i < nubmerOfRules; i++)
		getline(cin, productionsRules[i]);

	multiset<string>visited;
	for (int rule = 0; rule < nubmerOfRules; rule++) {
		string currentRule = productionsRules[rule];
		string nonTerminal = getNonTerminal(currentRule, 0);
		visited.insert(nonTerminal);
		set<string> firstSet;

		//o know if the rule has been visited or no
		if (visited.count(nonTerminal) == 1) {
			firstSet = getFirstSet(nonTerminal);
			cout << "  first set(" << nonTerminal << ") = ";
			for (auto it : firstSet)
				cout << it << " ";
			cout << endl;
		}
	}
}
