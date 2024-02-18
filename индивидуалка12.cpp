#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
double accur = 1e-9;
double accur1 = 1e-15;
const int amount = 1000;
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
double* S(double** a, double* y, int n)
{
    double* x = new double[n];
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
double* Solution(int size,int q4,double **A)
{
    double* x0 = new double[size];
    for (int i = 0; i < size; i++)
        x0[i] = 1;
    double lambda = q4 - accur;
    bool flag1 = 1;
    double* y0 = new double[size];
    for (int i = 0; i < size; i++)
        y0[i] = 0;
    while (flag1 == 1)
    {
        double** B = new double* [size];
        for (int i = 0; i < size; i++)
            B[i] = new double[size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                    B[i][j] = A[i][j] - lambda;
                else B[i][j] = A[i][j];
            }

        double* res = S(B, x0, size);

        double Maximum = -1;
        for (int i = 0; i < size; i++)
        {
            if (abs(res[i]) > Maximum)
                Maximum = abs(res[i]);
        }
        for (int i = 0; i < size; i++)
            x0[i] = res[i] / Maximum;

        double Maximum1 = -1;
        for (int i = 0; i < size; i++)
            if (abs(abs(x0[i]) - abs(y0[i])) > Maximum1)
                Maximum1 = abs(abs(x0[i]) - abs(y0[i]));
        if (Maximum1 < accur)
            flag1 = 0;
        for (int i = 0; i < size; i++)
            y0[i] = x0[i];
    }
    return x0;
}
double* N(int size, double** A, double* x0, double z)
{
    double* w = new double[size];
    for (int i = 0; i < size; i++)
        w[i] = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                w[i] += (A[i][j] - z) * x0[j];
            else w[i] += A[i][j] * x0[j];
        }
    return w;
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
    double* q = new double[size];
    for (int i = 0; i < size; i++)
        q[i] = 0;
    bool flag = 1;
    bool fl = 1;
    int u = 0;
    double q2 = 0;
    double qn = 0;
    int p = 0;
    int p1 = 0;
    while (flag == 1 && fl == 1)
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
            if (Max2 < accur1)
            {
                double Max3 = -1;
                for (int i = 0; i < size; i++)
                    if (abs(q1[i]) > Max3)
                    {
                        Max3 = abs(q1[i]);
                        p = i;
                    }
                cout << "Старшее по модулю собственное число:" << endl;
                q2 = q1[p];
                cout << fixed << setprecision(15) << q2 << endl;
                Max3 = -1;
                for (int i = 0; i < size; i++)
                {
                    if (abs(q1[i]) > Max3 && abs(q1[i]) < abs(q1[p]))
                    {
                        Max3 = abs(q1[i]);
                        p1 = i;
                    }
                }
                qn = q1[p1];

                fl = 0;
            }
            else 
            {
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

                flag = 0;
            }
        }

        u++;
        if (u >= amount)
        {
            cout << "Метод не сходится к наибольшему по модулю собственному числу" << endl;
            return 0;
        }
    }

    double* ynew = new double[size];
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        ynew[i] = rand() % 100;

    double M = -1;
    for (int i = 0; i < size; i++)
        if (abs(ynew[i]) > M)
            M = abs(ynew[i]);
    for (int i = 0; i < size; i++)
        ynew[i] /= M;

    double* ynew1 = new double[size];
    for (int i = 0; i < size; i++)
    {
        double s = 0;
        for (int j = 0; j < size; j++)
            s += A[i][j] * ynew[j];
        ynew1[i] = s;
    }

    for (int i = 0; i < size; i++)
        ynew1[i] /= M;

    double* ynew2 = new double[size];
    int r = 0;
    while (r < 10)
    {
        for (int i = 0; i < size; i++)
        {
            double s1 = 0;
            for (int j = 0; j < size; j++)
                s1 += A[i][j] * ynew1[j];
            ynew2[i] = s1;
        }

        for (int i = 0; i < size; i++)
        {
            ynew[i] = ynew1[i];
            ynew1[i] = ynew2[i];
        }
        r++;
    }

    for (int i = 0; i < size; i++)
    {
        double s1 = 0;
        for (int j = 0; j < size; j++)
            s1 += A[i][j] * ynew1[j];
        ynew2[i] = s1;
    }

    double* q3 = new double[size];
    for (int i = 0; i < size; i++)
        q3[i] = 0;
    int kol = 0;
    for (int i = 0; i < size; i++)
    {
        if (abs(ynew1[i] - q2 * ynew[i]) > accur)
        {
            kol++;
            q3[i] = (ynew2[i] - q2 * ynew1[i]) / (ynew1[i] - q2 * ynew[i]);
        }
    }

    double q4 = 0;
    for (int i = 0; i < size; i++)
        q4 += q3[i];
    q4 = q4 / double(kol);

    if (flag == 0)
    {
        double* x0 = Solution(size, q2, A);
        cout << "Собственный вектор, соответствующий старшему по модулю собственному числу:";
        cout << endl;
        for (int i = 0; i < size; i++)
            cout << x0[i] << ' ';
        cout << endl;

        double* w0 = N(size, A, x0, q2);
        cout << "Невязка:" << endl;
        for (int i = 0; i < size; i++)
            cout << w0[i] << ' ';
        cout << endl;

        cout << endl;
        cout << "Следующее старшее по модулю собственное число:" << endl;
        cout << fixed << setprecision(15) << q4 << endl;

        double* x01 = Solution(size, q4, A);
        cout << "Собственный вектор, соответствующий следующему старшему по модулю собственному числу:";
        cout << endl;
        for (int i = 0; i < size; i++)
            cout << x01[i] << ' ';
        cout << endl;

        double* w01 = N(size, A, x01, q4);
        cout << "Невязка:" << endl;
        for (int i = 0; i < size; i++)
            cout << w01[i] << ' ';
        cout << endl;
    }

    if (fl == 0)
    {
        cout << "Собственный вектор, соответствующий старшему по модулю собственному числу:";
        cout << endl;
        double* w = new double[size];
        for (int i = 0; i < size; i++)
            w[i] = 0;
        w[p] = 1;
        for (int i = 0; i < size; i++)
            cout << fixed << setprecision(15) << w[i] << ' ';

        double* w01 = N(size, A, w, q2);
        cout << endl;
        cout << "Невязка:" << endl;
        for (int i = 0; i < size; i++)
            cout << w01[i] << ' ';
        cout << endl;

        cout << endl;
        cout << "Следующее старшее по модулю собственное число:" << endl;
        cout << qn << endl;

        cout << "Собственный вектор, соответствующий следующему старшему по модулю собственному числу:";
        cout << endl;
        for (int i = 0; i < size; i++)
            w[i] = 0;
        w[p1] = 1;
        for (int i = 0; i < size; i++)
            cout << fixed << setprecision(15) << w[i] << ' ';

        w01 = N(size, A, w, qn);
        cout << endl;
        cout << "Невязка:" << endl;
        for (int i = 0; i < size; i++)
            cout << w01[i] << ' ';
        cout << endl;
    }
}
