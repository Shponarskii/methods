#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void readfile(double &a,double &b,double &h,double &u0)
{
	fstream f("input.txt");
	f >> a >> b;
	f >> h;
	f >> u0;
}
double func(double t,double u)
{
	return 1 / (t + 1);
}
double tfunc(double t)
{
	return log(t + 1);
}
int main()
{
	setlocale(LC_ALL, "rus");
	fstream o("output.txt");
	o.clear();
	double a, b, h, u0;
	readfile(a, b, h, u0);
	int n = int(b / h) + 1;
	double* y = new double[n];
	for (int i = 0; i < n; i++)
		y[i] = 0;
	double* mass = new double[n];
	for (int i = 0; i < n; i++)
		mass[i] = h * i;
	y[0] = u0;
	double k1 = func(mass[0], y[0]);
	if (n > 2) 
	{
		y[1] = y[0] + 0.5 * h * (k1 + func(mass[0] + h, y[0] + h * k1));
		k1 = func(mass[1], y[1]);
		y[2] = y[1] + 0.5 * h * (k1 + func(mass[1] + h, y[1] + h * k1));
	}
	for (int i = 3; i < n; i++)
	{
		y[i] = y[i - 1] + h * (23 * func(mass[i - 1], y[i - 1]) - 16 * func(mass[i - 2], y[i - 2]) + 5 * func(mass[i - 3], y[i - 3])) / float(12);
	}
	for (int i = 0; i < n; i++)
		o << mass[i] << ' ' << y[i] << endl;
	double Max = -1;
	for (int i = 0; i < n; i++)
		if (abs(y[i] - tfunc(mass[i])) > Max)
			Max = abs(y[i] - tfunc(mass[i]));
	cout << "Невязка:" << endl;
	cout << fixed << setprecision(15) << Max << endl;
}
