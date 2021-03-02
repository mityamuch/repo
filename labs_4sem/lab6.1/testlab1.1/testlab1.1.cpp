#include <iostream>
#include <string>
#ifndef EPS 
#define EPS 1e-6
#endif
using namespace std;

 class Tex_convertible
{
public:
    virtual  string convert() const  = 0;
};

template <typename T>
class Matrix :public Tex_convertible
{
private:
    T** M; // матрица(указатель на место в памяти)
    int m; // количество строк
    int n; // количество столбцов
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
    Matrix()
    {
        n = m = 0;
        M = nullptr;
    }
    Matrix(int _m, int _n)
    {
        m = _m;
        n = _n;

        M = (T**) new T * [m]; 
        // Выделить память для каждого указателя
        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];
        // заполнить массив M нулями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }

    // Конструктор копирования
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

    // методы доступа к ячейке
    T GetMij(int i, int j)
    {
        if ((i-1 < 0) || (i-1 >= m) || (j-1 < 0) || (j-1 >= n)) {
            throw logic_error("Out of memory range");
            return 0;
        }
        else if ((m > 0) && (n > 0))
            return M[i-1][j-1];
    }

    void SetMij(int i, int j, T value)
    {
        if ((i < 0) || (i >= m))
            throw logic_error("Out of memory range");
        if ((j < 0) || (j >= n))
            throw logic_error("Out of memory range");
        M[i][j] = value;
    }

    // метод, выводящий матрицу
    

    // оператор копирования 
    Matrix operator=(const Matrix& _M)
    {
        clear();
        // Копирование данных M <= _M
        m = _M.m;
        n = _M.n;

        // Выделить память для M опять
        M = (T**) new T * [m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];

        // заполнить значениями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
        return *this;
    }
    //Деструктор
    ~Matrix()
    {
        clear();
    }

    Matrix operator+( Matrix& b) const
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
        Matrix <T> result(m,n);
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
        if ( n != b.m)
            throw logic_error("Incompatible matrixes");
        Matrix<T> result(m, b.n);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < b.n; ++j)
            {
                result.M[i][j]  = 0;
                for (int k = 0; k < n; k++)
                    result.M[i][j] += M[i][k] * b.M[k][j];
            }
        }
        return result;
    }

    Matrix operator* ( T x)const 
    {
        Matrix<T> result(m,n);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
               result.M[i][j]= M[i][j] *x;
        return result;
    }

    bool operator== (const Matrix& b) const
    {
        if (m != b.m || n != b.n)
            return false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                if (fabs(M[i][j] - b.M[i][j])>EPS)
                    return false;
        }
        return true;
    }

    void Print(const char* ObjName)
    {
        cout << "Object: " << ObjName << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cout << M[i][j] << "\t";
            cout << endl;
        }
        cout << "---------------------" << endl << endl;
    }

    
   
    string convert() const{
        string answer;
        answer += "\\begin{pmatrix}";
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                answer+=to_string( M[i][j])+"&";
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
    m.m= height;
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
Matrix<T> operator* (T x,const Matrix<T>& m)
{
    return m*x;
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
    result.Print("matr");
    Matrix<T> answer(m.m, m.n);
    for (int i = 0; i < m.m; i++)
        for (int j = 0,k=m.n; j < m.n,k<result.n; j++,  k++)
            answer.M[i][j] = result.M[i][k];


    answer.Print("MATR2");
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





