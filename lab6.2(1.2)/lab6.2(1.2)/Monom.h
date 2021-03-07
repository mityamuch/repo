#pragma once

#include <stdio.h>
#include "Tex_convertible.h"
#include <iostream>
#include <map>
using namespace std;
class Monom :public Tex_convertible{
private:
    std::map<char,unsigned int> letters;
    int  k{ 1 };
public:
    Monom() = default; //конструктор без параметров
    Monom(const char* equation) {
        sscanf(equation, "%d", &k);
        int l=0;
        while (isdigit(equation[l])||equation[l]=='-') {
            l++;
        }
        for (int i = l;equation[i]!='\0';) {
            char per;int ind{ 1 };
            per = equation[i++];
            sscanf(&equation[i], "%d", &ind);
            while (isdigit(equation[i])) 
                i++;
            
            pair < map<char, unsigned int>::iterator, bool > check =letters.emplace(per,ind);
            if (check.second == false)
                throw logic_error("Duplicated items");


       }

    }//конструктор с параметрами
    Monom(const Monom& m) = default;

    Monom& operator= (const Monom& m) {
        k = m.k;
        letters = m.letters;
    }
    
    Monom operator* (const Monom& m) const {
        Monom result(*this);
        return result *= m;
         
    }
    Monom& operator*= (const Monom& m) {
        k *= m.k;
        for (const auto& c : m.letters) {
            pair < map<char, unsigned int>::iterator,bool > check = letters.insert(c);
            if (check.second == false)
                (check.first)->second += c.second;

        }


    }
    Monom operator/ (char dif) const {
        Monom result(*this);
        return result /= dif;
    
    }
    Monom& operator/= (char dif) {
        map<char, unsigned int>::iterator it = letters.find(dif);
        if (it == letters.end())
        {
            letters.clear();
            k = 0;
        }
        else if (it->second == 1) {
            letters.erase(it->first);

        }
        else {
            k *= it->second;
            it->second--;
        }
        return *this;
    }
    bool operator== (const Monom& m) {
        if (k == m.k && letters == m.letters)
            return true;
        return false;
    }
    bool operator!= (const Monom& m) {
        return !(*this == m);
    }

    friend ostream& operator<<(ostream& stream, const Monom& m);
    friend istream& operator>>(istream& stream, Monom& m);
    std::string convert() const {
        return   "";
    }
};
ostream& operator<<(ostream& stream, const Monom& m) {
    stream << m.k;
    for (const auto& c : m.letters) {
        stream <<'*'<< c.first << "^" << c.second;

    }

}
istream& operator>>(istream& stream, Monom& m) {
    string equation;
    getline(stream,equation);
    Monom result(equation.c_str());
    m = result;
}