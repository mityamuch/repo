#include <iostream>
#include "matrix.h"
using namespace std;
template <typename T>


T findtrace(Matrix<T>& m) {
    T result = 1;
    if (m.m != m.n)
        throw logic_error("matrix is not square");
    for (int i = 0,j=0; i < m.m; i++,j++) 
    {
            result *= m.M[i][j];
    }
    return result;
}

template <typename T>
void GetMatr(T** mas, double** p, int i, int j, int m) {
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}

template <typename T>
T findD(Matrix<T>& matrix) {
    if (matrix.m != matrix.n)
        throw logic_error("matrix is not square");

    int i, j, k, n;
    T d;
    double** p;
    p = new double* [matrix.m];
    for (i = 0; i < matrix.m; i++)
        p[i] = new double[matrix.m];
    j = 0; d = 0;
    k = 1; //(-1) в степени i
    n = matrix.m - 1;
    if (matrix.m < 1) cout << "Определитель вычислить невозможно!";
    if (matrix.m == 1) {
        d = matrix.M[0][0];
        return(d);
    }
    if (matrix.m == 2) {
        d = matrix.M[0][0] * matrix.M[1][1] - ( matrix.M[1][0] * matrix.M[0][1]);
        return(d);
    }
    if (matrix.m > 2) {
        for (i = 0; i < matrix.m; i++) {
            GetMatr(matrix.M, p, i, 0, matrix.m);
            cout << matrix.M[i][j] << endl;
            Matrix<T>newmatrix(n, n);
            d = d + k * matrix.M[i][0] * findD(newmatrix);
            k = -k;
        }
    }
    return(d);
}



template <class T>
Matrix<T> transpose(Matrix<T>& m) {
    
    Matrix<T> result(m.n,m.m);
    for (int i = 0; i < m.m; i++)
        for (int j = 0; j < m.n; j++)
            result.M[i][j] = m.M[j][i];

    return result;
}

template <class T>
Matrix<T> reverse(Matrix<T>& m) //доделать обратную
{
    cout << "Start..." << endl;
    if (m.m != m.n)
        throw logic_error("matrix is not square");
    Matrix<T> result(m.m,2*m.n);
    for (int i = 0; i < m.m; i++)
        for (int j = 0; j < m.n; j++)
            result.M[i][j] = m.M[i][j];

    T  a;
    int i, j, k;
   
    for (i = 0; i < result.m; i++)
    {
        for (j = result.m; j < result.n; j++)
        {
            if (i == (j - result.m))
                result.M[i][j] = 1;
            else
                result.M[i][j] = 0;
        }
       
    }


    for (i = 0; i < result.m; i++)
    {
        for (j = result.n-1; j >= i; j--)
        {
            if (fabs(result.M[i][i]) < EPS)
                throw logic_error("det(m) == 0! No reverse matrix!");
            result.M[i][j] /= result.M[i][i];
            for (k = i+1; k < result.m; k++)
            {
                result.M[k][j] -= result.M[k][i] * result.M[i][j];
            }
        }
    }


    for (i = result.m - 1; i > 0; i--)
    {
        for (k = 0; k < i; k++)
        {
            a = result.M[k][i];
            for (j = i-1; j < result.n; j++)
            {
                result.M[k][j] -= a * result.M[i][j];
            }
        }
    }
    Matrix<T> answer(m.m, m.n);
    for (int i = 0; i < m.m; i++)
        for (int j = 0,k=m.n; j < m.n,k<result.n; j++,  k++)
            answer.M[i][j] = result.M[i][k];


    return answer;
}

template <class T>
Matrix<T> Matrixexp(Matrix<T>& m)//доделать матричную экспоненту
{
    T n=1;
    
    Matrix<T> E(m.m, m.n);
    if (m.m != m.n)
        throw logic_error("matrix is not square");
    //заполнение единичной матрицы
    for (int i = 0,j=0; i < m.m,j<m.n; i++,j++)
            E.M[i][j] =1;
    Matrix<double> akkum(E);
    Matrix<double> result(E);
    for (;;) {

        akkum =(1/n)* akkum*m ;
        n += 1;
        for (int i = 0; i < m.m; i++) {
            for (int j = 0; j < m.n; j++) {
                if (akkum.M[i][j] < EPS) { return result; }
            }
        }
        result += akkum;
    }
}


int main()
{
    try {
        Matrix<double> first;
        cerr << "enter first operand"<<endl;
        cin >> first;
        string oper;
        cerr << "enter operator" << endl;
        cin >> oper;
        if (oper == "+") {
            Matrix<double> second ;
            cerr << "enter second operand" << endl;;
            cin >> second;
            cout << first.convert() << " + " << second.convert() << (first + second).convert();
        }
        else if (oper == "-"){
            Matrix<double> second;
            cerr << "enter second operand" << endl;;
            cin >> second;
            cout << first.convert() << " - " << second.convert() << (first + second).convert();
        }
        else if (oper == "*"){
            Matrix<double> second;
            cerr << "enter second operand" << endl;;
            cin >> second;
            cout << first.convert() << " * " << second.convert() << (first + second).convert();
        }
        else if (oper == "*x") {
            double second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " * " << second << (first * second).convert();
        }
        else if (oper == "x*") {
            double second;
            cerr << "enter second operand" << endl;;
            cin >> second;
            cout << second << " * " << first.convert() << ( second * first).convert();
        }
        else if (oper == "=="){
            Matrix<double> second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " == " << second.convert() << "\t"; (first == second) ? cout<<"true":cout<<"false";
        }
        else if (oper == "!="){
            Matrix<double> second;
            cerr << "enter second operand" << endl;
            cin >> second;
            cout << first.convert() << " != " << second.convert() << "\t"; (first == second) ? cout << "false" : cout << "true";
        }
        else if (oper == "D"){
            cout << first.convert() << " Determenant = " << findD(first);
        }
        else if (oper == "reverse"){
            cout << first.convert() << " Reversed = " << (reverse(first)).convert();
        }
        else if (oper == "transpose"){
            cout << first.convert() << " Transposed = " << (transpose(first)).convert();
        }
        else if (oper == "exp") {
            cout << first.convert() << " exp = " << (Matrixexp(first)).convert();
        }
        else if (oper == "trace"){
            cout << first.convert() << " trace = " << findtrace(first);
        }
        return 0;
    }
    catch (std::exception a) {
        std::cerr << "We caught an exception :" << a.what() << '\n';
    }
}





