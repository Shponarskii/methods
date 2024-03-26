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
	return -u * tan(t) + 1 / cos(t);
}
double tfunc(double t)
{
	return sin(t);
}
int main()
{
	setlocale(LC_ALL, "rus");
	fstream o("output.txt");
	o.clear();
	double a, b, h, u0;
	readfile(a, b, h, u0);
	int n = int((b - a) / h) + 1;
	double* y = new double[n];
	for (int i = 0; i < n; i++)
		y[i] = 0;
	double* mass = new double[n];
	for (int i = 0; i < n; i++)
		mass[i] = a + h * i;
	y[0] = u0;
	double k1 = func(mass[0], y[0]);
	double k2 = func(mass[0] + h / 3, y[0] + h * k1 / 3);
	if (n > 2) 
	{
		y[1] = y[0] + h * (k1 + 3 * func(mass[0] + 2 * h / 3, y[0] + 2 * h / 3 * k2)) / float(4);
		k1 = func(mass[1], y[1]);
		k2 = func(mass[1] + h / 3, y[1] + h * k1 / 3);
		y[2] = y[1] + h * (k1 + 3 * func(mass[1] + 2 * h / 3, y[1] + 2 * h / 3 * k2)) / float(4);
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
