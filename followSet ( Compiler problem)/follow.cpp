

#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int theNubmerOfRules;
string productionsRules[1000];
set<string> solveInfiniteR(string NonT1, string NonT2);
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
//FirstFunction
string getTerminal(string currentRule, int stratFrom) {
	string terminal;
	for (int i = stratFrom; i < currentRule.size(); i++)
	{
		if (isupper(currentRule[i])) {
			cout << "PLEASE FOLLOW THER RULeES.\n"; exit(0);
		}
		if (isspace(currentRule[i]))
			break;
		terminal += currentRule[i];
	}
	return terminal;
}
string getNonTerminal(string currentRule, int stratFrom) {
	string nonTerminal;
	for (int i = stratFrom; i < currentRule.size(); i++)
	{
		if (islower(currentRule[i])) {
			cout << "PLEASE FOLLOW THE RULES.\n"; exit(0);
		}
		if (isspace(currentRule[i]))
			break;
		nonTerminal += currentRule[i];
	}
	return nonTerminal;
}
string firstTerminal(string currentRule, string productionsRules[]) {
	string firstSet = "";
	char TerminalOrNonTerminal = currentRule[currentRule.find('>') + 2];
	int  IndexOfTerminalOrNonTerminal = currentRule.find('>') + 2;

	if (!isupper(TerminalOrNonTerminal)) {
		//to guarantee epsilon in the correct pos.
		if (currentRule.back() != '$' && TerminalOrNonTerminal == '$') {
			cout << "YOU CAN'T PUT $ HERE"; exit(0);
		}

		firstSet = getTerminal(currentRule, IndexOfTerminalOrNonTerminal);
		return firstSet;
	}
	else {
		string nonTerminal = getNonTerminal(currentRule, IndexOfTerminalOrNonTerminal);

		for (int rule = 0; rule < theNubmerOfRules; rule++) {
			string anotherNonTerminal = productionsRules[rule].substr(0, productionsRules[rule].find('-') - 1);

			if (nonTerminal == anotherNonTerminal) {
				currentRule = productionsRules[rule];
				firstSet += firstTerminal(currentRule, productionsRules) + " ";
			}
		}

		return firstSet;
	}
	return firstSet;
}
set<string> getFirstSet(string NonTerminal) {
	string currentRule;
	set<string> firstSet;

	bool hasEpsilon = true;
	for (int j = 0; j < theNubmerOfRules; j++) {
		string anotherNonTerminal = productionsRules[j].substr(0, productionsRules[j].find('-') - 1);
		if (NonTerminal == anotherNonTerminal) {
			currentRule = productionsRules[j];

			//No repetition
			if (firstTerminal(currentRule, productionsRules).find("$") != firstTerminal(currentRule, productionsRules).npos) {
				char TerminalOrNonTerminal = currentRule[currentRule.find('>') + 2];
				int  IndexOfTerminalOrNonTerminal = currentRule.find('>') + 2;
				for (int i = IndexOfTerminalOrNonTerminal; i < currentRule.size(); i++) {
					if (!isspace(TerminalOrNonTerminal)) {
						if (!isupper(TerminalOrNonTerminal)) {
							if (firstSet.count(getTerminal(currentRule, i)) == 0)
								firstSet.insert(getTerminal(currentRule, i));
							hasEpsilon = false;
							i += getTerminal(currentRule, i).size();
							TerminalOrNonTerminal = currentRule[i];
							break;
						}
						else {
							//to save from override
							set<string> save = getFirstSet(getNonTerminal(currentRule, i));
							firstSet.insert(save.begin(), save.end());
							if (firstSet.count("$") != 0)
								firstSet.erase("$");
							else {

								hasEpsilon = false;
								break;
							}
							i += getNonTerminal(currentRule, i).size();
							if (i < currentRule.size())
								TerminalOrNonTerminal = currentRule[i + 1];
						}
					}

				}
			}

			else {
				hasEpsilon = false;
				firstSet.insert(firstTerminal(currentRule, productionsRules));
			}

		}
	}

	if (hasEpsilon)
		firstSet.insert("$");

	return firstSet;

}
set<string> getFollowSet(string NonTerminal , string Rules []) {
	string currentRule;
	set<string> followSet;

	for (int i = 0; i < theNubmerOfRules; i++) {
		if ( Rules[i].find( NonTerminal ) != Rules[i].npos ) {
			currentRule = Rules[i];

			if (  Rules[0].substr(0, Rules[i].find('-') - 1)  == NonTerminal )
					followSet.insert("$");

			for (int j = currentRule.find('>') + 2; j < currentRule.size(); j++) {
				string str = getString(currentRule, j);
				j += str.size();

				//cout << j << " " << str <<  endl;
				if ( str == NonTerminal ) {
					j++;

					if ( str.back() == currentRule.back() ) {
						string t;
					    for ( int v = currentRule.size()-1; !isspace(currentRule[v]); v-- ){
							t += currentRule[v];
						}
						if ( t == NonTerminal && t != Rules[i].substr(0, Rules[i].find('-') - 1) ) {
			            set<string> save = solveInfiniteR(NonTerminal , Rules[i].substr(0, Rules[i].find('-') - 1));
						followSet.insert(save.begin(), save.end());
						}
					}
					else if (isupper(currentRule[j])) {
		
						 if (getNonTerminal(currentRule, j) != NonTerminal) {
							 set<string> save = getFirstSet(getNonTerminal(currentRule, j));
							 if (save.count("$") != 0) {
								 save.erase("$");
								 set<string> save2 = getFollowSet(getNonTerminal(currentRule, j),Rules);
								 save.insert(save2.begin(), save2.end());
							 }
							 followSet.insert(save.begin(), save.end());
							 j += getNonTerminal(currentRule, j).size() + 1;
						 }
						 else
							 --j;

					}
					else if ( !isupper(currentRule[j])) {
						followSet.insert(getTerminal(currentRule, j));
						j += getTerminal(currentRule, j).size()+1;
					}
					

				}

			}
		}
	}
	return followSet;
}
set<string> solveInfiniteR(string NonT1, string NonT2) {

	string tempProductionsRules[1000];
	int n = 1000;
	int j = 0;
			//cout << NonT1 << " " << NonT2 << endl;
	for (int i = 0; i < theNubmerOfRules; i++) {
		string t;
		

		for ( int v = productionsRules[i].size() - 1; !isspace(productionsRules[i][v]); v-- ) {
			t += productionsRules[i][v];
		}
		if (productionsRules[i].substr(0, productionsRules[i].find('-') - 1) == NonT1 && t == NonT2) {
			continue;
		}
		else {
			tempProductionsRules[j] = productionsRules[i];
			++j;
		}

	}
	return getFollowSet(NonT2, tempProductionsRules);

}
int main()
{
	cin >> theNubmerOfRules;
	cin.ignore();
	//get productions rules
	for (int i = 0; i < theNubmerOfRules; i++)
		getline(cin, productionsRules[i]);

	multiset<string>visited;
	for (int rule = 0; rule < theNubmerOfRules; rule++) {
		string currentRule = productionsRules[rule];
		string nonTerminal = getNonTerminal(currentRule, 0);
		visited.insert(nonTerminal);

		set<string> followSet;

		////to know if the rule has been visited or not
		if (visited.count(nonTerminal) == 1) {
				followSet = getFollowSet(nonTerminal,productionsRules);
		
			cout << "  follow set(" << nonTerminal << ") = ";
			for (auto it : followSet)
				cout << it << " ";
			cout << endl;
		}
	}
}
