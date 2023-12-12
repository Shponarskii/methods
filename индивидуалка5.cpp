#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
const int n = 4;
double f(double x)
{
	return log(x);
}
void readfile(double*& x, double& a, double& b,int n)
{
	ifstream f("input.txt");
	f >> a >> b;
	for (int i = 0; i < n + 1; i++)
		f >> x[i];
}
int main()
{
	double* x = new double[n + 1];
	double a, b;
	double s = 0;
	readfile(x, a, b, n);
	for (int i = 0; i < n; i++)
	{
		double h = (x[i + 1] - x[i]) / float(4);
		s += ((7 * f(x[i]) + 32 * f(x[i] + h) + 12 * f(x[i] + 2 * h) + 32 * f(x[i] + 3 * h) + 7 * f(x[i] + 4 * h)) * 2 * h / float(45));
	}
	cout << fixed << setprecision(15) << s << endl;
}