#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
const double accur = 1e-7;

double f(double x) 
{
	return sin(x) - cos(x); // x*x*x-x [-1.5;1.5] // x*x-7 [-4;5] // sin(x)-cos(x) [0;4] // x*x+2*x+2 [-15;20] // cos(x) - log(x) [1;3]
}

double derivative(double x, int k) 
{
	double d = accur;
	return k * (f(x + d * k) - f(x)) / d;
}

double q(double a, double b)
{
	return max(abs(derivative(a, 1)), abs(derivative(b, -1)));
}

double f1(double x, double qq)
{
	return x - f(x) / ((qq > 1) ? (qq) : (1));
}

int Vegstein(double q1, double* x, double e, double t)
{
	int k = 0;
	double qq = q1;
	if (q1 > 1)
		q1 = 1 - 1 / q1;
	x[0] = t;
	x[1] = x[0];
	x[2] = f1(x[0], qq);
	x[3] = x[2];
	do {
		k++;
		if (k > 1000)
			return -1;
		x[4] = f1(x[3], qq);
		if (abs(x[4] - x[3]) <= e * (1 - q1) / q1)
			break;
		double y = x[3];
		x[3] = (x[4] * x[1] - x[2] * y) / (x[4] + x[1] - x[2] - y);
		x[0] = x[2];
		x[1] = y;
		x[2] = x[4];
	} while (true);
	return 1;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double a, b;
	cin >> a >> b;
	double* x = new double[5];
	double* y = new double[5];
	for (int i = 0; i < 5; i++)
		x[i] = 0;
	x[4] = a;
	for (int i = 0; i < 5; i++)
		y[i] = x[i];
	y[4] = a;
	int flag1 = 0, flag2 = 1;
	double t = 0;
	while (y[4]+t <= b && Vegstein(q(a, b), x, accur, y[4]+t) == 1)
	{
		if (x[4]<=b && x[4]>=a && abs(x[4]-y[4]) > 10*accur)
		{
			cout << flag2 << "-й корень с точностью 1e-7 равен " << setprecision(8) << fixed << x[4] << endl;
			y[4] = x[4];
			flag2++;
		}
		flag1++;
		t += accur*0.1 * flag1;
	}
	if (flag2 == 1)
		cout << "Действительных корней на отрезке нет";
	return 0;
}