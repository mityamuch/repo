#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Polyndrom.h"



using namespace std;
int main() {
	Monom a("2xy2");
	Monom c("2x2y");
	Polynom d(a);
	Polynom e(c);
	Polynom b;
	b = d * a;
	cout << a<<endl;
	cout << c << endl;
	cout << b;
	return 0;
}



