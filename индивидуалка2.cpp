#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const double accur = 1e-6;

int sizeM()
{
    string l;
    ifstream t("input.txt");
    if (t.is_open())
        getline(t, l);
    t.close();
    int numberOfSpaces = 0;
    for (int i = 0; i < l.size(); i++)
        if (l[i] == ' ')
            numberOfSpaces++;
    return numberOfSpaces;
}

void readfile(double* x, double* f, int n)
{
    ifstream t("input.txt");
    if (t.is_open())
    {
        for (int i = 0; i < n; i++)
            t >> x[i];
        for (int i = 0; i < n; i++)
            t >> f[i];
    }
    t.close();
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
    double max;
    int k = 0, index;
    while (k < n)
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
    double* x = new double[size + 1];
    double* f = new double[size + 1];
    double* h = new double[size];

    readfile(x, f, size + 1);

    for (int i = 0; i < size; i++)
        h[i] = x[i + 1] - x[i];

    double* a = new double[size + 1];
    for (int i = 0; i < size + 1; i++)
        a[i] = f[i];

    double** A = new double* [size - 1];
    for (int i = 0; i < size - 1; i++)
        A[i] = new double[size - 1];
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - 1; j++)
            A[i][j] = 0;
    for (int i = 0; i < size - 1; i++)
    {
        A[i][i] = 2 * (h[i] + h[i + 1]);
        if (i != size - 2)
        {
            A[i][i + 1] = h[i + 1];
            A[i + 1][i] = h[i + 1];
        }
    }

    double* y = new double[size - 1];
    for (int i = 0; i < size - 1; i++)
        y[i] = 6 * ((f[i + 2] - f[i + 1]) / h[i + 1] - (f[i + 1] - f[i]) / h[i]);
    
    double* c = new double[size];
    c = S(A, y, size - 1);
    c[size - 1] = 0;

    double* d = new double[size];
    d[0] = c[0] / h[0];
    for (int i = 1; i < size; i++)
        d[i] = (c[i] - c[i-1]) / h[i];

    double* b = new double[size];
    for (int i = 0; i < size; i++)
        b[i] = h[0] * c[i] / 2 - h[i] * h[i] * d[i] / 6 + (f[i + 1] - f[i]) / h[i];

    //for (int i = 1; i < size + 1; i++)
    //    cout << a[i] << ' ';
    //cout << endl;
    //printA(b, size);
    //for (int i = 0; i < size; i++)
    //    cout << c[i] / 2 << ' ';
    //cout << endl;
    //for (int i = 0; i < size; i++)
    //    cout << d[i] / 6 << ' ';
    //cout << endl;

    //cout << endl;
    int n = 10;
    cout << x[0] << ' ' << a[0] << endl;
    for (int i = 0; i < size; i++)
        for (double l = x[i] + h[i] / n; l <= x[i + 1] + accur; l += h[i] / n)
        {
            cout << l << ' ' << a[i + 1] + b[i] * (l - x[i + 1]) + c[i] * (l - x[i + 1]) * (l - x[i + 1]) / 2 + d[i] * (l - x[i + 1]) * (l - x[i + 1]) * (l - x[i + 1]) / 6;
            cout << endl;
        }
    return 0;
}
