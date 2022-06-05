

#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int numberOfRules;
string productionsRules[100];

// solve this problem A -> T and T -> A
set<string> solveInfiniteRecursion(string NonT1, string NonT2);

//get any string
string getString(string currentRule, int stratFrom) {
	string terminal;
	for (int i = stratFrom; i < currentRule.size(); i++)
	{
		if (isspace(currentRule[i]))
			break;
		terminal += currentRule[i];
	}
	return terminal;
}

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
		for (int rule = 0; rule < numberOfRules; rule++) {
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
	for (int rule = 0; rule < numberOfRules; rule++) {
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
				set<string>save = firstTerminal(currentRule, productionsRules);
				firstSet.insert(save.begin(), save.end());
			}

		}
	}

	if (hasEpsilon)
		firstSet.insert("$");

	return firstSet;
}

//Get the Followirst Set
set<string> getFollowSet(string NonTerminal, string Rules[]) {
	string currentRule;
	set<string> followSet;

	for (int rule = 0; rule < numberOfRules; rule++) {
		if (Rules[rule].find(NonTerminal) != Rules[rule].npos) { //match the nonTerminal at each string in a each rule
			currentRule = Rules[rule];

			if (Rules[0].substr(0, Rules[rule].find('-') - 1) == NonTerminal)// for start symbol "adding of file" 
				followSet.insert("-|");

			int indexOfTheFirstLetterAfterArrow = currentRule.find('>') + 2;

			for (int letter = indexOfTheFirstLetterAfterArrow; letter < currentRule.size(); letter++) {
				string str = getString(currentRule, letter);
				letter += str.size();

				if (str == NonTerminal) {

					letter++;

					//case1 : end of rule
					if (str.back() == currentRule.back()) {// check if str "X" is in the end of rule ** A -> "X"
						string t;
						for (int v = currentRule.size() - 1; !isspace(currentRule[v]); v--)
							t += currentRule[v];

						reverse(t.begin(), t.end());

						if (t == NonTerminal && t != Rules[rule].substr(0, Rules[rule].find('-') - 1)) {
							set<string> save = solveInfiniteRecursion(NonTerminal, Rules[rule].substr(0, Rules[rule].find('-') - 1));  //get the new FollowSet and store it in the previous FollowFirst
							followSet.insert(save.begin(), save.end());
						}
					}
					//case2 :   the follow string is NonTerminal
					else if (isupper(currentRule[letter])) {

						if (getNonTerminal(currentRule, letter) != NonTerminal) {
							set<string> save = getFirstSet(getNonTerminal(currentRule, letter));

							if (save.count("$") != 0) {
								save.erase("$");
								set<string> save2 = getFollowSet(getNonTerminal(currentRule, letter), Rules); //get the new FollowSet and store it in the previous FollowFirst
								save.insert(save2.begin(), save2.end());
							}

							followSet.insert(save.begin(), save.end());
							letter += getNonTerminal(currentRule, letter).size() + 1;
						}
						else {

							set<string> save = getFirstSet(getNonTerminal(currentRule, letter)); //get the new FollowSet and store it in the previous FollowFirst
							save.erase("$");
							followSet.insert(save.begin(), save.end());
							--letter;
						}

					}
					//case3 :   the follow string is Terminal
					else if (!isupper(currentRule[letter])) {
						followSet.insert(getTerminal(currentRule, letter));
						letter += getTerminal(currentRule, letter).size() + 1;
					}


				}

			}
		}
	}
	return followSet;
}

// solve this problem A -> T and T -> A
set<string> solveInfiniteRecursion(string NonT1, string NonT2) {

	string tempProductionsRules[100];
	int j = 0;

	for (int rule = 0; rule < numberOfRules; rule++) {
		string t;


		for (int v = productionsRules[rule].size() - 1; !isspace(productionsRules[rule][v]); v--) {
			t += productionsRules[rule][v];
		}
		if (productionsRules[rule].substr(0, productionsRules[rule].find('-') - 1) == NonT1 && t == NonT2) {
			continue;
		}
		else {
			tempProductionsRules[j] = productionsRules[rule];
			++j;
		}

	}
	return getFollowSet(NonT2, tempProductionsRules);

}


//get the Rule ( which can obtain a specific  terminal)
string getRule(string nonT, string T) {

	string rule;
	string t;
	bool isExist = false;

	for (int i = 0; i < numberOfRules; i++) {
		for (int j = productionsRules[i].find('>') + 2; j < productionsRules[i].size(); j++) {
			if (productionsRules[i].substr(0, productionsRules[i].find('-') - 1) == nonT) {

				t = getString(productionsRules[i], j);
				j += t.size();

				if (t == T)
					return productionsRules[i];
				else
					break;
			}
		}

	}

	for (int i = 0; i < numberOfRules; i++) {
		if (productionsRules[i].substr(0, productionsRules[i].find('-') - 1) == nonT) {
			if (isupper(productionsRules[i][productionsRules[i].find('>') + 2])) {
				if (getFirstSet(getNonTerminal(productionsRules[i], productionsRules[i].find('>') + 2)).count(T) == 1)
					return productionsRules[i];
				else if (getFirstSet(getNonTerminal(productionsRules[i], productionsRules[i].find('>') + 2)).count("$") == 1) {
					if (getFollowSet(getNonTerminal(productionsRules[i], productionsRules[i].find('>') + 2), productionsRules).count(T) == 1)
						return productionsRules[i];
				}
			}

		}
	}
	return "- 1";

}
int main()
{
	cin >> numberOfRules;
	cin.ignore();

	//get productions rules
	for (int i = 0; i < numberOfRules; i++)
		getline(cin, productionsRules[i]);

	set<string> terminals;
	set<string> nonTerminals;

	///////construct Parsing Table

	//get all terminals & nonTerminals
	for (size_t i = 0; i < numberOfRules; i++) {
		for (int j = 0; j < productionsRules[i].size(); j++) {
			if (!isupper(productionsRules[i][j]) && productionsRules[i][j] != '-' && productionsRules[i][j] != '>' && !isspace(productionsRules[i][j]) && productionsRules[i][j] != '$') {
				terminals.insert(getTerminal(productionsRules[i], j));
				j += getTerminal(productionsRules[i], j).size();
			}
			else if (isupper(productionsRules[i][j])) {
				nonTerminals.insert(getNonTerminal(productionsRules[i], j));
				j += getNonTerminal(productionsRules[i], j).size();
			}

		}
	}

	//end of file.
	terminals.insert("-|");

	int numberOfTerminals = terminals.size();
	int numberOfNonTerminals = nonTerminals.size();


	string parsingTable[100][100] = { " " };
	auto it = terminals.begin();

	for (size_t i = 1; i < numberOfTerminals + 1; i++) {
		parsingTable[0][i] = *it;
		++it;
	}

	it = nonTerminals.begin();

	for (size_t i = 1; i < numberOfNonTerminals + 1; i++) {
		parsingTable[i][0] = *it;
		++it;
	}


	cout << '\n' << "Predict   Expression\n";

	//display parsing table
	for (size_t i = 1; i < numberOfNonTerminals + 1; i++) {
		for (size_t j = 1; j < numberOfTerminals + 1; j++) {
			if (getFirstSet(parsingTable[i][0]).count(parsingTable[0][j]) == 1) {
				cout << parsingTable[0][j] << "         from " << getRule(parsingTable[i][0], parsingTable[0][j]) << "\n";
			}

		}
		if (getFirstSet(parsingTable[i][0]).count("$") == 1) {
			set<string> fSet = getFollowSet(parsingTable[i][0], productionsRules);

			for (auto it : fSet) {
				cout << it << "         from " << getRule(parsingTable[i][0], "$") << '\n';
			}
		}
	}
}





