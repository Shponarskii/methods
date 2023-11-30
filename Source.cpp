#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int n = 3;
const double accur = 1e-8;
double function(int j, double* x)
{
    switch (j)
    {
    case 0:
        return x[0] * x[0] - x[1] * x[2] * x[2] + pow(x[1] - 1, 3);
    case 1:
        return sin(x[0] * x[0] + x[2]) + cos(x[1]) * cos(x[1]) - 1;
    case 2:
        return 2 * exp(x[0] * pow(x[1], 3)) + sin(x[2] * x[2] - 1) - 2;
    }
}
double derivative(double* x, int i, int j)
{
	double r = function(j, x);
	x[i] += accur;
    double s = (function(j, x) - r) / accur;
    x[i] -= accur;
    return s;
}

double* S(double** a, double* y, int n)
{
    double** w = new double* [n * n];
    for (int i = 0; i < n; i++)
        w[i] = new double[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            w[i][j] = a[i][j];
    double* x = new double[n];
    double max;
    int k = 0, index;
    while (k < n - 1)
    {
        max = abs(w[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
            if (abs(w[i][k]) > max)
            {
                max = abs(w[i][k]);
                index = i;
            }
        if (max < accur)
        {
            cout << "Решение не может быть найдено из-за нулевого столбца";
            return nullptr;
        }
        swap(w[k], w[index]);
        swap(y[k], y[index]);
        double t;
        for (int i = k + 1; i < n; i++)
        {
            t = w[i][k] / w[k][k];
            if (t == 0) continue;
            for (int j = k; j < n; j++)
                w[i][j] -= w[k][j] * t;
            y[i] -= y[k] * t;
        }
        k++;
    }
    double* y1 = new double[n];
    for (int i = 0; i < n; i++)
        y1[i] = y[i];
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y1[k] / w[k][k];
        for (int i = 0; i < k; i++)
            y1[i] -= w[i][k] * x[k];
    }
    return x;
}

int main()
{
    setlocale(LC_ALL, "rus");
    double* F1, ** F2;
    F1 = new double[n];
    F2 = new double* [n * n];
    for (int i = 0; i < n; i++)
        F2[i] = new double[n];
	double* x = new double[n];
    ifstream f("input.txt");
    for (int i = 0; i < n; i++)
        f >> x[i];
	double Max = -DBL_MAX;
	for (int i = 0; i < n; i++)
		if (x[i] > Max)
			Max = x[i];
	while (abs(Max) > accur)
	{
        double* res;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                F2[i][j] = derivative(x, j, i);
        for (int l = 0; l < 2; l++)
        {
            for (int i = 0; i < n; i++)
                F1[i] = -function(i, x);
            res = S(F2, F1, n);
            if (res == nullptr)
            {
                cout << "Последовательность не сходится к решению системы" << endl;
                return -1;
            }
            for (int i = 0; i < n; i++)
                x[i] += res[i];
        }
        Max = -DBL_MAX;
        for (int i = 0; i < n; i++)
        {
            double q = function(i, x);
            if (q > Max)
                Max = q;
        }
        //cout << Max << endl;
        //for (int i = 0; i < n; i++)
        //{
        //    for (int j = 0; j < n; j++)
        //        cout << F2[i][j] << ' ';
        //    cout << endl;
        //}
        //cout << endl;
        //for (int i = 0; i < n; i++)
        //    cout << F1[i] << ' ';
        //cout << endl << endl;
        //for (int i = 0; i < n; i++)
        //    cout << x[i] << ' ';
        //cout << endl << endl;
	}
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(30) << x[i] << ' ';
    cout << endl << endl;
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(40) << function(i, x) << ' ';
}