#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int sizeM()
{
    string l;
    ifstream f("input.txt");
    if (f.is_open())
        getline(f, l);
    f.close();
    int numberOfSpaces = 0;
    for (int i = 0; i < l.size(); i++)
        if (l[i] == ' ')
            numberOfSpaces++;
    return numberOfSpaces + 1;
}
void readfile(double** A, double* y, int n)
{
    ifstream f("input.txt");
    if (f.is_open())
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f >> A[i][j];
        for (int i = 0; i < n; i++)
            f >> y[i];
    }
    f.close();
}
void printM(double** m, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}
void printA(double* a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << std::endl;
}
void t(double** &c, int n)
{
    c = new double* [n];
    for (int i = 0; i < n; i++)
        c[i] = new double[n];
}
int LU(double** &l, double** &u, double** a, int n)
{
    int i = 0, j = 0;
    while (i < n)
    {
        for (int i1 = i; i1 < n; i1++)
        {
            double s1 = 0;
            for (int k = 0; k < j; k++)
                s1 += l[i1][k] * u[k][j];
            l[i1][j] = a[i1][j] - s1;
        }
        j++;
        if (j == n) break;
        for (int j1 = j; j1 < n; j1++)
        {
            double s2 = 0;
            for (int k = 0; k < i; k++)
                s2 += l[i][k] * u[k][j1];
            if (l[i][i] == 0)
            {
                cout << "Разложение невозможно или матрица вырожденна";
                return -1;
            }
            u[i][j1] = (a[i][j1] - s2) / l[i][i];
        }
        i++;
    }
    return 1;
}
int main()
{
    setlocale(LC_ALL, "rus");
    int size = sizeM();
    double** A, ** L, ** U;
    t(A, size), t(L, size), t(U, size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            L[i][j] = 0;
            U[i][j] = 0;
            if (i == j) U[i][j] = 1;
        }
    double* y = new double[size];
    readfile(A, y, size);
    int flag = LU(L, U, A, size);
    if (flag == 1)
    {
        cout << "Матрица L:" << endl;
        printM(L, size);
        cout << endl;
        cout << "Матрица U:" << endl;
        printM(U, size);
        cout << endl;
        double* b = new double[size];
        for (int i = 0; i < size; i++)
        {
            double p = 0;
            for (int k = 0; k < i; k++)
                p += L[i][k] * b[k];
            b[i] = (y[i] - p) / L[i][i];
        }
        double* x = new double[size];
        for (int i = size - 1; i >= 0; i--)
        {
            double r = 0;
            for (int k = i + 1; k < size; k++)
                r += U[i][k] * x[k];
            x[i] = b[i] - r;
        }
        cout << "Решение:" << endl;
        printA(x, size);
    }
    return 0;
}
