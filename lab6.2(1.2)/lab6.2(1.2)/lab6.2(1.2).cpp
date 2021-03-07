#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Polyndrom.h"



using namespace std;
int main() {
    try {
        Polynom first;
        cerr << "enter first operand" << endl;
        cin >> first;
        string oper;
        cerr << "enter operator" << endl;
        cin >> oper;
        if (oper == "+") {
            Polynom second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " + " << second.convert() <<'='<< (first + second).convert();
        }
        else if (oper == "-") {
            Polynom second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " - " << second.convert() << '=' << (first - second).convert();
        }
        else if (oper == "*") {
            Polynom second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " * " << second.convert() << '=' << (first * second).convert();
        }
        else if (oper == "==") {
            Polynom second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " == " << second.convert() << "\t"; (first == second) ? cout << "true" : cout << "false";
        }
        else if (oper == "!=") {
            Polynom second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " != " << second.convert() << "\t"; (first != second) ? cout << "true" : cout << "false";
        }
        else if (oper == "/") {
            string second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " / " <<'('<<second<<')'  << '=' << (first / (second.c_str())).convert();
        }
        else if (oper == "uniformity") {
            cout << first.convert() << " uniformity is"  << "\t"; (Checkuniformity(first)) ? cout << "true" : cout << "false";
        }
        else if (oper == "harmony") {
            cout << first.convert() << " harmony is" << "\t"; (Checkharmony(first)) ? cout << "true" : cout << "false";
        }
    }
    catch (std::exception a) {
        std::cerr << "We caught an exception :" << a.what() << '\n';
    }
	return 0;
}



