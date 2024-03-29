#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
double accur = 1e-8;
const int p = 1000;
int sizeM()
{
    string l;
    fstream t("input.txt");
    getline(t, l);
    int number = 0;
    for (int i = 0; i < l.size(); i++)
        if (l[i] == ' ')
            number++;
    return number + 1;
}
void readfile(double** A, int n)
{
    fstream t("input.txt");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            t >> A[i][j];
}
int main()
{
    setlocale(LC_ALL, "rus");
    int size = sizeM();
    double** A = new double* [size];
    for (int i = 0; i < size; i++)
        A[i] = new double[size];
    readfile(A, size);

    double* y = new double[size];
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        y[i] = rand() % 100;

    double Max = -1;
    for (int i = 0; i < size; i++)
        if (abs(y[i]) > Max)
            Max = abs(y[i]);
    for (int i = 0; i < size; i++)
        y[i] /= Max;
    //for (int i = 0; i < size; i++)
    //    cout << y[i] << ' ';
    double* q = new double[size];
    for (int i = 0; i < size; i++)
        q[i] = 0;
    bool flag = 1;
    int u = 0;
    while (flag == 1)
    {
        double* y1 = new double[size];
        for (int i = 0; i < size; i++)
        {
            double s = 0;
            for (int j = 0; j < size; j++)
                s += A[i][j] * y[j];
            y1[i] = s;
        }

        double* q1 = new double[size];
        for (int i = 0; i < size; i++)
            q1[i] = 0;
        for (int i = 0; i < size; i++)
            if (abs(y[i]) > accur)
                q1[i] = y1[i] / y[i];

        double Max1 = -1;
        for (int i = 0; i < size; i++)
            if (abs(y1[i]) > Max1)
                Max1 = abs(y1[i]);
        for (int i = 0; i < size; i++)
            y1[i] /= Max1;

        double Max2 = -1;
        for (int i = 0; i < size; i++)
            if (abs(q1[i] - q[i]) > Max2)
                Max2 = abs(q1[i] - q[i]);

        for (int i = 0; i < size; i++)
        {
            y[i] = y1[i];
            q[i] = q1[i];
        }

        if (Max2 < accur)
        {
            double q2 = 0;
            int r = 0;
            for (int i = 0; i < size; i++)
            {
                if (q1[i] == 0) r++;
                q2 += q1[i];
            }
            int size1 = size - r;
            q2 /= size1;
            cout << "Старшее по модулю собственное число:" << endl;
            cout << fixed << setprecision(15) << q2 << endl;
            cout << "Собственный вектор, соответствующий собственному числу:";
            cout << endl;
            for (int i = 0; i < size; i++)
                cout << fixed << setprecision(15) << y1[i] << ' ';
            cout << endl;
            double* w = new double[size];
            for (int i = 0; i < size; i++)
                w[i] = 0;
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                {
                    if (i == j)
                        w[i] += (A[i][j] - q2) * y1[j];
                    else w[i] += A[i][j] * y1[j];
                }
            cout << "Невязка:" << endl;
            for (int i = 0; i < size; i++)
                cout << fixed << setprecision(15) << w[i] << ' ';
            flag = 0;
        }

        u++;
        if (u >= p)
        {
            flag = 0;
            cout << "Метод не сходится к наибольшему по модулю собственному числу" << endl;
        }
    }
}
