

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
    void setCh(char c) {
        ch = c;
    }

    char getCh() {
        return ch;
    }

};
//class Category {
//  
//public:
//    string getCategory(Token token) {
//
//        if (token.getType() == "ND") {
//            regex number("[0-9]+");
//            regex alphabet("[a-z]+");
//
//            if (regex_match(token.getToken(), number))
//                return "number";
//            else if (regex_match(token.getToken(), alphabet))
//                return "alphabet";
//        }
//        else
//            return  token.getToken();
//    }
//};
class Transition {
public:

    State transitionTable[10][10];
    vector<State> states;
    vector<Characters> chars;

    Transition() {}

    Transition(vector<State> st, vector<Characters> chs) {
        states = st;
        chars = chs;
    }


    void setTransitionTable() {
        for (int i = 0; i < states.size(); i++) {
            for (int j = 0; j < chars.size(); j++) {
                transitionTable[i][j].setState();
                transitionTable[i][j].setType();


            }
        }
    }
    void getTransitionTable() {
        for (int i = 0; i < states.size(); i++) {
            for (int j = 0; j < chars.size(); j++)
                cout << transitionTable[i][j].getState() << " ";
            cout << endl;
        }
    }

};

int getIndexOfState(vector<State> states, string state) {
    for (size_t i = 0; i < states.size(); i++) {
        if (state == states[i].getState())
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
        //Category category;
        string token;
        int indexOfCh;



        for (int j = 0; j < transitionTable.states.size(); j++) {

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
                j = getIndexOfState(transitionTable.states, transitionTable.transitionTable[j][indexOfCh].getState());
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

    Characters a, b;
    a.setCh('a');
    b.setCh('b');
    vector<Characters> chs = { a,b };

    State q0, q1, F, E;
    q0.setState();
    q1.setState();
    E.setState();
    F.setState();
    vector<State> states = { q0,q1,F,E };

    Transition table(states, chs);
    table.setTransitionTable();


    Scanner sc("file.txt", table); sc.displayToken();

}

