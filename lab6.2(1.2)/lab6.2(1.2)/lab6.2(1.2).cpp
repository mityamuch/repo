#include <iostream>
#include <memory.h>
#include <map>
using namespace std;
//класс Monom
class Monom {
private:
    map<char, int> letters;
    int k;
public:
    Monom()=default; //конструктор без параметров
    Monom(char* equation) {
        int l=sscanf(equation, "%d", k);
       
     
    }//конструктор с параметрами
    Monom(const Monom& m) {
        k = m.k;
        letters = m.letters;
    }//копирующий конструктор
    ~Monom(); //деструктор

    Monom operator= (const Monom& m);   //оператор сложения
    Polynom operator+ (const Monom& m);//оператор присваивания
    Polynom operator+= (const Monom& m);
    Polynom operator- (const Monom& m);
    Polynom operator-= (const Monom& m);
    Monom operator* (const Monom& m);
    Monom operator*= (const Monom& m);
    Monom operator/ (char dif);
    Monom operator/= (char dif);
    Monom operator== (const Monom& m);
    Monom operator!= (const Monom& m);
    friend ostream& operator<<(ostream& stream, const Monom& m);
    friend istream& operator>>(istream& stream,Monom& m);
};


