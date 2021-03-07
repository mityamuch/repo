#pragma once
#include "Monom.h"
#include <list>
using namespace std;


class Polynom:public Tex_convertible {
private:
    list<Monom> parts;

public:
    ~Polynom();
    Polynom operator+ (const Monom& m) {}//оператор присваивания
    Polynom& operator+= (const Monom& m) {}
    Polynom operator- (const Monom& m) {}
    Polynom& operator-= (const Monom& m) {}
    //fromMonom
    Polynom& operator= (const Polynom& m) {}
    Polynom operator+ (const Polynom& m) {}//оператор присваивания
    Polynom& operator+= (const Polynom& m) {}
    Polynom operator- (const Polynom& m) {}
    Polynom& operator-= (const Polynom& m) {}
    Polynom operator* (const Polynom& m) {}
    Polynom& operator*= (const Polynom& m) {}
    Polynom operator/ (char dif) {}
    Polynom& operator/= (char dif) {}
    Polynom& operator/ (char* dif) {}
    Polynom& operator/= (char* dif) {}
    Polynom& operator== (const Polynom& m) {}
    Polynom& operator!= (const Polynom& m) {}
    friend ostream& operator<<(ostream& stream, const Polynom& m);
    friend istream& operator>>(istream& stream, Polynom& m);
    friend bool Checkuniformity(Polynom& m);
    friend bool Checkharmony(Polynom& m);
    std::string convert() const {}
};