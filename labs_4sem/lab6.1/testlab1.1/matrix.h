#pragma once
#include "tex_convertible.h"
#ifndef EPS 
#define EPS 1e-6
#endif
using namespace std;

template <typename T>
class Matrix :public Tex_convertible
{
private:
    T** M; // матрица(указатель на место в пам€ти)
    int m{ 0 }; // количество строк
    int n{ 0 }; // количество столбцов
    void clear() {
        if (n > 0)
        {
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0)
            delete[] M;
    }
public:
    //по умолчанию
    Matrix() = default;
    Matrix(int _m, int _n)
    {
        m = _m;
        n = _n;

        M = (T**) new T * [m];
        // ¬ыделить пам€ть дл€ каждого указател€
        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];
        // заполнить массив M нул€ми
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }

    //  онструктор копировани€
    Matrix(const Matrix& _M)
    {

        m = _M.m;
        n = _M.n;
        M = (T**) new T * [m];

        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];
        //fill
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
    }

    // методы доступа к €чейке
    T GetMij(int i, int j)
    {
        if ((i - 1 < 0) || (i - 1 >= m) || (j - 1 < 0) || (j - 1 >= n)) {
            throw logic_error("Out of memory range");
            return 0;
        }
        else if ((m > 0) && (n > 0))
            return M[i - 1][j - 1];
    }

    void SetMij(int i, int j, T value)
    {
        if ((i < 0) || (i >= m))
            throw logic_error("Out of memory range");
        if ((j < 0) || (j >= n))
            throw logic_error("Out of memory range");
        M[i][j] = value;
    }

    // метод, вывод€щий матрицу


    // оператор копировани€ 
    Matrix& operator=(const Matrix& _M)
    {
        clear();
        //  опирование данных M <= _M
        m = _M.m;
        n = _M.n;

        // ¬ыделить пам€ть дл€ M оп€ть
        M = (T**) new T * [m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];

        // заполнить значени€ми
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
        return *this;
    }
    //ƒеструктор
    ~Matrix()
    {
        clear();
    }

    Matrix operator+(Matrix& b) const
    {
        return Matrix<T>(*this) += b;
    }

    Matrix& operator+=(Matrix& b)
    {
        if (m != b.m || n != b.n)
            throw logic_error("Incompatible matrixes");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                M[i][j] += b.M[i][j];
        }
        return *this;
    }

    Matrix operator-() const {
        Matrix <T> result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                result.M[i][j] = -M[i][j];
        }
        return result;
    }

    Matrix operator-(Matrix& b) const
    {
        Matrix<T> result(*this);
        result -= b;
        return result;

    }
    Matrix& operator-=(Matrix& b) const
    {
        if (m != b.m || n != b.n)
            throw logic_error("Incompatible matrixes");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                M[i][j] -= b.M[i][j];
        }
        return *this;

    }

    Matrix operator*(Matrix& b) const
    {
        if (n != b.m)
            throw logic_error("Incompatible matrixes");
        Matrix<T> result(m, b.n);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < b.n; ++j)
            {
                result.M[i][j] = 0;
                for (int k = 0; k < n; k++)
                    result.M[i][j] += M[i][k] * b.M[k][j];
            }
        }
        return result;
    }

    Matrix operator* (T x)const
    {
        Matrix<T> result(m, n);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                result.M[i][j] = M[i][j] * x;
        return result;
    }

    bool operator== (const Matrix& b) const
    {
        if (m != b.m || n != b.n)
            return false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                if (fabs(M[i][j] - b.M[i][j]) > EPS)
                    return false;
        }
        return true;
    }


    std::string convert() const {
        std::string answer;
        answer += "\\begin{pmatrix}";
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                answer += std::to_string(M[i][j]) + "&";
            answer += "\\\\";
        }


        answer += "\\end{ pmatrix }";
        return answer;
    }

    template <class U>
    friend U findtrace(Matrix<U>& m);
    template <class U>
    friend U findD(Matrix<U>& m);
    template <class U>
    friend Matrix<U> transpose(Matrix<U>& m);
    template <class U>
    friend Matrix<U> reverse(Matrix<U>& m);
    template <class U>
    friend Matrix<U> Matrixexp(Matrix<U>& m);
    template <class U>
    friend ostream& operator<<(ostream& stream, const Matrix<U>& m);
    template <class U>
    friend Matrix<U> operator* (U x, const Matrix<U>& m);
    template <class U>
    friend istream& operator>>(istream& stream, Matrix<U>& m);
};
template <class T>
ostream& operator<<(ostream& stream, const Matrix<T>& m)
{
    for (int i = 0; i < m.m; i++)
    {
        for (int j = 0; j < m.n; j++)
            stream << m.M[i][j] << "\t";
        stream << endl;
    }
    stream << "---------------------" << endl << endl;
    return stream;
}

template <class T>
istream& operator>>(istream& stream, Matrix<T>& m) {
    int  height, width;
    stream >> height;
    stream >> width;
    m.clear();
    m.m = height;
    m.n = width;
    m.M = (T**) new T * [height];
    for (int i = 0; i < m.m; i++)
    {
        m.M[i] = (T*) new T[width];
        for (int j = 0;j < m.n;++j) {
            stream >> m.M[i][j];
        }
    }



    return stream;
}

template <class T>
Matrix<T> operator* (T x, const Matrix<T>& m)
{
    return m * x;
}