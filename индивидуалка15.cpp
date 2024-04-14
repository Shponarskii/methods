#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void readfile(double& a, double& b, double& h, double& u0, double &u1)
{
	fstream f("input.txt");
	f >> a >> b;
	f >> h;
	f >> u0;
	f >> u1;
}
double funcp(double x)
{
	return 0;
}
double funcq(double x)
{
	return 1;
}
double funcf(double x)
{
	return 1;
}
double tfunc(double x)
{
	return cos(x) + 1;
}
double* S(double* A, double* B, double* C, double* y, int n)
{
    double* x = new double[n];
    double* alpha = new double[n];
    alpha[0] = 0;
    double* beta = new double[n + 1];
    beta[0] = 0;
    for (int i = 1; i < n; i++)
    {
        alpha[i] = -C[i - 1] / (alpha[i - 1] * A[i - 1] + B[i - 1]);
        beta[i] = (y[i - 1] - beta[i - 1] * A[i - 1]) / (alpha[i - 1] * A[i - 1] + B[i - 1]);
    }
    beta[n] = (y[n - 1] - beta[n - 1] * A[n - 1]) / (alpha[n - 1] * A[n - 1] + B[n - 1]);
    x[n - 1] = beta[n];
    for (int i = n - 2; i >= 0; i--)
        x[i] = alpha[i + 1] * x[i + 1] + beta[i + 1];
    return x;
}
void f(double* a, int n)
{
	for (int i = 0; i < n; i++)
		a[i] = 0;
}
int main()
{
	setlocale(LC_ALL, "rus");
	ofstream o("output.txt");
	o.clear();
	double a, b, h, u0, u1;
	readfile(a, b, h, u0, u1);
	int n = int((b - a) / h) + 1;
	double* y = new double[n];
	f(y, n);
	double* mass = new double[n];
	for (int i = 0; i < n; i++)
		mass[i] = a + h * i;
	y[0] = u0;
	double* A = new double[n - 1];
	double* B = new double[n - 1];
	double* F = new double[n - 1];
	f(A, n - 1), f(B, n - 1), f(F, n - 1);
	double* C = new double[n - 2];
	f(C, n - 2);
	if (n > 1)
	{
		A[0] = 0;
		for (int i = 1; i < n - 2; i++)
			A[i] = 2 - funcp(mass[i + 1]) * h;
		A[n - 2] = (-4 + 4 * funcp(mass[n - 2]) * h - 2 * funcq(mass[n - 2]) * h * h) / (2 - funcp(mass[n - 2]) * h);
		for (int i = 0; i < n - 2; i++)
			B[i] = -4 + 2 * funcq(mass[i + 1]) * h * h;
		B[n - 2] = (4 - 4 * funcp(mass[n - 2]) * h) / (2 - funcp(mass[n - 2]) * h);
		for (int i = 0; i < n - 2; i++)
			C[i] = 2 + funcp(mass[i + 1]) * h;
		F[0] = 2 * funcf(mass[1]) * h * h - y[0] * (2 - funcp(mass[1]) * h);
		for (int i = 1; i < n - 2; i++)
			F[i] = 2 * funcf(mass[i + 1]) * h * h;
		F[n - 2] = 2 * u1 * h - (2 * funcf(mass[n - 2]) * h * h) / (2 - funcp(mass[n - 2]) * h);
		double* res = S(A, B, C, F, n - 1);

		o << mass[0] << ' ' << y[0] << endl;
		for (int i = 1; i < n; i++)
			o << mass[i] << ' ' << res[i - 1] << endl;
		double Max = -1;
		for (int i = 0; i < n - 1; i++)
			if (abs(res[i] - tfunc(mass[i + 1])) > Max)
				Max = abs(res[i] - tfunc(mass[i + 1]));
		cout << "Невязка:" << endl;
		cout << fixed << setprecision(15) << Max << endl;
	}
}
