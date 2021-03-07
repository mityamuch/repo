#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Polyndrom.h"



using namespace std;
int main() {
	Monom a("100x3y3");
	Monom c("2x2y2");
	Polynom d(a,c);
	Polynom e(c);
	Polynom b;
	Monom be;
	b = d * e;
	if (Checkharmony(b)==true);
	{
		cout << "true" << endl;
	}
	cout << a<<endl;
	cout << c << endl;
	cout << b<<endl;
	return 0;
}



