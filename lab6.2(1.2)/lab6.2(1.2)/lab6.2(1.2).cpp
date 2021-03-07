#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Polyndrom.h"



using namespace std;
int main() {
	Monom a("2xy2u200");
	cout << a << endl;
	Monom b;
	b = a / ('u');
	cout << b;
	return 0;
}



