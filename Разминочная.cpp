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
        if (l[i] != ' ')
            numberOfSpaces++;
    return numberOfSpaces;
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
double* S(double** a, double* y, int n)
{
    double* x = new double[n];
    const double accur = 0.000001;
    double max;
    int k = 0, index;
    while (k < n - 1)
    {
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        if (max < accur) 
        {
            cout << "Решение не может быть найдено из-за нулевого столбца";
            return nullptr;
        }
        swap(a[k], a[index]);
        swap(y[k], y[index]);
        double t;
        for (int i = k + 1; i < n; i++) 
        {
            t = a[i][k] / a[k][k];
            if (t == 0) continue;
            for (int j = k; j < n; j++)
                a[i][j] -= a[k][j] * t;
            y[i] -= y[k] * t;
        }
        k++;
    }
    double* y1 = new double[n];
    for (int i = 0; i < n; i++)
        y1[i] = y[i];
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y1[k] / a[k][k];
        for (int i = 0; i < k; i++)
            y1[i] -= a[i][k] * x[k];
    }
    return x;
}
int main() 
{
    setlocale(LC_ALL, "rus");
    int size = sizeM();
    double** A = new double* [size];
    for (int i = 0; i < size; i++)
        A[i] = new double[size];
    double* y = new double[size];
    readfile(A, y, size);
    printM(A, size);
    printA(y, size);
    double* res = S(A, y, size);
    cout << endl << "Полученное решение: ";
    printA(res, size);
    cout << endl << "Полученная матрица: " << endl;
    printM(A, size);
    cout << endl;
    printA(y, size);
    return 0;
}