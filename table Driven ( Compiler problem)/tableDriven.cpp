

#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

class State {

    string nameState;
    string type;

public:


    void setState() {
        cin >> nameState;
    }

    string getState() {
        return nameState;
    }

    void setType() {
        cin >> type;
    }

    string getType() {
        return type;
    }

};
class Characters {

    char ch;

public:
    Characters() {
        ch = 'N';
    }
    void setCh(char c) {
        ch = c;
    }

    char getCh() {
        return ch;
    }


};
class Category {

public:
    string getCategory(Characters ch) {

        if (ch.getCh() != 'N') {
            regex number("[0-9]+");
            regex alphabet("[a-z]+");

            if (regex_match(ch.getCh() + "", number))
                return "number";
            else if (regex_match(ch.getCh() + "", alphabet))
                return "alphabet";
        }
        else
            return  ch.getCh() + "";
    }

};
class Transition {
public:

    State transitionTable[10][10];
    int noOFStates;
    vector<Characters> chars;

    Transition() {}

    Transition(int st, vector<Characters> chs) {
        noOFStates = st;
        chars = chs;
    }


    void setTransitionTable() {
        for (int i = 0; i < noOFStates; i++) {
            for (int j = 0; j < chars.size(); j++) {
                transitionTable[i][j].setState();
                transitionTable[i][j].setType();
            }
        }
    }
    void getTransitionTable() {
        for (int i = 0; i < noOFStates; i++) {
            for (int j = 0; j < chars.size(); j++)
                cout << transitionTable[i][j].getState() << " ";
            cout << endl;
        }
    }

};

int getIndexOfState(State states[][10], int noOfSts, string state) {
    for (size_t i = 0; i < noOfSts; i++) {
        if (state == states[i][0].getState())
            return i;
    }
    return -1;
}

int  getIndexOfCh(vector<Characters> chs, char ch) {
    for (size_t i = 0; i < chs.size(); i++) {
        if (chs[i].getCh() == ch)
            return i;
    }
    return -1;
}

class Scanner {

    ifstream file;
    Transition transitionTable;

public:
    Scanner(string fileName, Transition t) {
        file.open(fileName);
        transitionTable = t;
    }

    string getToken() {
        char ch;
        Category category;
        string token;
        int indexOfCh;


        for (int j = 0; j < transitionTable.noOFStates; j++) {

            if (!file.get(ch))
                return "End";

            indexOfCh = getIndexOfCh(transitionTable.chars, ch);
            if (indexOfCh == -1)
                return "Error";

            token += ch;

            if (transitionTable.transitionTable[j][indexOfCh].getType() == "F")
                return token;
            else if (transitionTable.transitionTable[j][indexOfCh].getType() == "E")
                return "Error";
            else {
                j = getIndexOfState(transitionTable.transitionTable, transitionTable.noOFStates, transitionTable.transitionTable[j][indexOfCh].getState());
                j--;

                if (!file.get(ch))
                    return "Error";
                else
                    file.putback(ch);
            }
        }


        return "End";
    }


    void displayToken() {
        string token = getToken();
        while (token != "End") {
            cout << "< " << token << " > " << endl;
            token = getToken();
        }
    }
};


int main() {

    Characters a, b, c, d;//G --> (1,1)
    a.setCh('(');
    b.setCh(')');
    c.setCh(',');
    d.setCh('1');
    vector<Characters> chs = { a,b,c,d };

    Transition table(6, chs);
    table.setTransitionTable();


    Scanner sc("file.txt", table);
    sc.displayToken();

}

