#pragma once
#include "Monom.h"
#include <list>
#include <algorithm>
using namespace std;

 class Polynom:public Tex_convertible {
private:
    list<Monom> parts;
    

    list<Monom>::iterator check(const Monom& x){
       return find_if(
           parts.begin(),
           parts.end(),
           [x](const Monom& m)
                {return (m.letters == x.letters) ? true : false;});
    }

public:
    Polynom() = default;
    template <class...Args>
    Polynom(Args... args) {                                      // конструктор от нескольких мономов
        for (const Monom& c : { args... }) {
            list<Monom>::iterator it = check(c);
            if (it == parts.end())
                parts.push_back(c);
            else
                it->k += c.k;
        }
    }


    Polynom(char* equation){}


    Polynom(Polynom& m) = default;

    Polynom& operator= (const Polynom& m) {
        parts = m.parts;
        return *this;
    }//оператор присваивания

    Polynom operator+ (const Polynom& m) {}

    Polynom& operator+= (const Polynom& m) {}

    Polynom operator- (const Polynom& m) {}

    Polynom& operator-= (const Polynom& m) {}

    Polynom operator* (const Polynom& m) {}

    Polynom& operator*= (const Polynom& m) {}

    Polynom operator/ (char dif) {}

    Polynom& operator/= (char dif) {}

    Polynom& operator/ (char* dif) {}

    Polynom& operator/= (char* dif) {}

    bool operator== (const Polynom& m) {
        if (parts.size() != m.parts.size())
            return false;
        for (const auto& c : m.parts) {

            if (check(c)==parts.end())
                return false;  
        }
        return true;
    }

    bool operator!= (const Polynom& m) {
        return !(*this == m);
    }

    friend ostream& operator<<(ostream& stream, const Polynom& m);
    friend istream& operator>>(istream& stream, Polynom& m);
    friend bool Checkuniformity(Polynom& m);
    friend bool Checkharmony(Polynom& m);
    //fromMonom
    friend Polynom operator+ (const Monom& left, const Monom& right);
    friend Polynom operator- (const Monom& left, const Monom& right);

    std::string convert() const {}
};

 Polynom operator+ (const Monom& left, const Monom& right){
     Polynom result(left);
     list<Monom>::iterator it = result.check(right);
     if (it == result.parts.end())
         result.parts.push_back(right);
     else
         it->k += right.k;
     return result;
 }

 Polynom operator- (const Monom& left, const Monom& right){
     Polynom result(left);
     list<Monom>::iterator it = result.check(right);
     if (it == result.parts.end()) {
         Monom convert_right(right);
         convert_right.k *= (-1);
         result.parts.push_back(convert_right);
     }
     else
         it->k -= right.k;
     return result;
 }

 ostream& operator<<(ostream& stream, const Polynom& m){
     for (const auto& c : m.parts) {
         stream  << c<<'+';

     }
     return stream;
 }

 istream& operator>>(istream& stream, Polynom& m){
 
 
 
 
 
 }
 
 bool Checkuniformity(Polynom& m){
     int sum=0;
     if (m.parts.empty())
         return true;

     list<Monom>::iterator it = m.parts.begin();
     for (const auto& mon : it->letters) {
         sum += mon.second;
     }
     int sumcheck;
     for (const auto& c : m.parts) {
         sumcheck = 0;
         for (const auto& mon : c.letters) {
             sumcheck += mon.second;
         }
         if (sum != sumcheck)
             return false;
     }
     return true;
 }
 bool Checkharmony(Polynom& m){
 
 }