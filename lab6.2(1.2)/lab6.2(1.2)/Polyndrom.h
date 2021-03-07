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


    Polynom(const char* equation){
        string str(equation);
        string token;
        for (const auto& c : str) {
            if (c!='+')
                token += c;
            else {
                if (!token.empty()) {
                    parts.push_back(Monom(token.c_str()));
                }
                token.clear();
            }
        }
        if (!token.empty())
            parts.push_back(Monom(token.c_str()));
    }


    Polynom(const Polynom& m) = default;

    Polynom& operator= (const Polynom& m) {
        parts = m.parts;
        return *this;
    }//оператор присваивания

    Polynom operator+ (const Polynom& m) {

        Polynom result(*this);
        return result += m;
    }

    Polynom& operator+= (const Polynom& m) {
        
        for (const auto& c : m.parts) {
            list<Monom>::iterator it = check(c);
            if (it == parts.end())
                parts.push_back(c);
            else
                it->k += c.k;
        }
        return *this;
    }

    Polynom operator- (const Polynom& m) {
    
        Polynom result(*this);
        return result -= m;
    }

    Polynom& operator-= (const Polynom& m) {
    
        for (const auto& c : m.parts) {
            list<Monom>::iterator it = check(c);
            if (it == parts.end()) {
                Monom newmon(c);
                newmon.k *= (-1);
                parts.push_back(newmon);
            }
            else
                it->k -= c.k;
        }
        return *this;
    }

    Polynom operator* (const Monom& m) {

        Polynom result(*this);
        return result *= m;
    }

    Polynom& operator*= (const Monom& m) {
        for (list<Monom>::iterator it = parts.begin();it != parts.end();it++) {
            (*it) *= m;
        }
        return *this;
    }

    Polynom operator* (const Polynom& m) {
        Polynom result(*this);
        return result *= m;
    }

    Polynom& operator*= (const Polynom& m) {
            for (const auto& right_monom : m.parts) {
                (*this) *= right_monom;
            }
        
        return *this;
    }

    Polynom operator/ (const char dif) const {
        Polynom result(*this);
        return result /= dif;
    }

    Polynom& operator/= (const char dif) {
        for (list<Monom>::iterator it = parts.begin();it != parts.end();) {
            (*it) /= dif;
            if (it->k == 0)
                it = parts.erase(it);
            else
                it++;
        }
        return *this;
    }

    Polynom operator/ ( const char* dif) {
        Polynom result(*this);
        return result /= dif;
    
    }

    Polynom& operator/= (const char* dif) {
        for (int i = 0;dif[i] != '\0';i++) {
            (*this) /= dif[i];
        }
        return *this;
    }

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

    std::string convert() const {
        string result;
        bool flag = true;
        for (const auto& c : parts) {
            result += ((flag) ? "" : "+") + c.convert();
            flag = false;
        }
        return result;
    }
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
     bool flag=true;
     for (const auto& c : m.parts) {
         stream <<((flag)? "":"+") << c;
         flag = false;
     }
     return stream;
 }

 istream& operator>>(istream& stream, Polynom& m){
     string equation;
     stream >> equation;
     Polynom result(equation.c_str());
     m = result;
     return stream;
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
     Polynom newm(m);
     if (newm.parts.empty())
         return true;
     string dif;
     for (const auto& c : newm.parts) {
         for (const auto& u : c.letters) {
             if (dif.find(u.first) == string::npos) {
                 dif += u.first;
             }
             else
                 continue;
         }
     }
     //вытащили в строку все имена переменных из полинома
     newm /= (dif.c_str());
     newm /= (dif.c_str());
     if (newm.parts.empty())
     {
         return true;
     }
     else
     {
         return false;
     }

 }