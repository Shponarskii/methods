#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void readfile(double& a, double& b, double& h, double& u0, double& u1)
{
	fstream f("input.txt");
	f >> a >> b;
	f >> h;
	f >> u0;
	f >> u1;
}
double function(int j, double u2,double u3, double t)
{
	switch (j)
	{
	case 0:
		return u2 * u2 / (2 * u3) - u3 / 2 + 1 / (2 * u3);
	case 1:
		return u2 + u3;
	}
}
double t1func(double t)
{
	return -1 + (t + 1) / float(2) - (t + 1) * (t + 1) / float(4);
}
double t2func(double t)
{
	return (t + 1) * (t + 1) / float(4) + 1;
}
int main()
{
	setlocale(LC_ALL, "rus");
	ofstream o1("output1.txt"), o2("output2.txt");
	o1.clear(), o2.clear();
	double a, b, h, u0, u1;
	readfile(a, b, h, u0, u1);
	int n = int((b - a) / h) + 1;
	double* y1 = new double[n];
	double* y2 = new double[n];
	for (int i = 0; i < n; i++)
		y1[i] = 0;
	for (int i = 0; i < n; i++)
		y2[i] = 0;
	double* mass = new double[n];
	for (int i = 0; i < n; i++)
		mass[i] = a + h * i;
	y1[0] = u0;
	y2[0] = u1;
	double k11 = function(0, y1[0], y2[0], mass[0]);
	double k12 = function(1, y1[0], y2[0], mass[0]);
	double k21 = function(0, y1[0] + h * k11 / 3, y2[0] + h * k12 / 3, mass[0] + h / 3);
	double k22 = function(1, y1[0] + h * k11 / 3, y2[0] + h * k12 / 3, mass[0] + h / 3);
	if (n > 2)
	{
		y1[1] = y1[0] + h * (k11 + 3 * function(0, y1[0] + 2 * h / 3 * k21, y2[0] + 2 * h / 3 * k22, mass[0] + 2 * h / 3)) / float(4);
		y2[1] = y2[0] + h * (k12 + 3 * function(1, y1[0] + 2 * h / 3 * k21, y2[0] + 2 * h / 3 * k22, mass[0] + 2 * h / 3)) / float(4);
		k11 = function(0, y1[1], y2[1], mass[1]);
		k12 = function(1, y1[1], y2[1], mass[1]);
		k21 = function(0, y1[1] + h * k11 / 3, y2[1] + h * k12 / 3, mass[1] + h / 3);
		k22 = function(1, y1[1] + h * k11 / 3, y2[1] + h * k12 / 3, mass[1] + h / 3);
		y1[2] = y1[1] + h * (k11 + 3 * function(0, y1[1] + 2 * h / 3 * k21, y2[1] + 2 * h / 3 * k22, mass[1] + 2 * h / 3)) / float(4);
		y2[2] = y2[1] + h * (k12 + 3 * function(1, y1[1] + 2 * h / 3 * k21, y2[1] + 2 * h / 3 * k22, mass[1] + 2 * h / 3)) / float(4);
	}
	for (int i = 3; i < n; i++)
	{
		y1[i] = y1[i - 1] + h * (23 * function(0, y1[i - 1], y2[i - 1], mass[i - 1]) - 16 * function(0, y1[i - 2], y2[i - 2], mass[i - 2]) + 5 * function(0, y1[i - 3], y2[i - 3], mass[i - 3])) / float(12);
		y2[i] = y2[i - 1] + h * (23 * function(1, y1[i - 1], y2[i - 1], mass[i - 1]) - 16 * function(1, y1[i - 2], y2[i - 2], mass[i - 2]) + 5 * function(1, y1[i - 3], y2[i - 3], mass[i - 3])) / float(12);
	}
	for (int i = 0; i < n; i++)
	{
		o1 << mass[i] << ' ' << y1[i] << endl;
		o2 << y2[i] << endl;
	}
	double Max1 = -1;
	for (int i = 0; i < n; i++)
		if (abs(y1[i] - t1func(mass[i])) > Max1)
			Max1 = abs(y1[i] - t1func(mass[i]));
	cout << "Невязка1:" << endl;
	cout << fixed << setprecision(15) << Max1 << endl;
	double Max2 = -1;
	for (int i = 0; i < n; i++)
		if (abs(y2[i] - t2func(mass[i])) > Max2)
			Max2 = abs(y2[i] - t2func(mass[i]));
	cout << "Невязка2:" << endl;
	cout << fixed << setprecision(15) << Max2 << endl;
}

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//using namespace std;
//void readfile(double& a, double& b, double& h, double& u0, double& u1, double& u2)
//{
//	fstream f("input.txt");
//	f >> a >> b;
//	f >> h;
//	f >> u0;
//	f >> u1;
//	f >> u2;
//}
//double function(int j, double u3, double u4, double u5, double t)
//{
//	switch (j)
//	{
//	case 0:
//		return -3 * u3 + 4 * u4 - 2 * u5;
//	case 1:
//		return u3 + u5;
//	case 2:
//		return 6 * u3 - 6 * u4 + 5 * u5;
//	}
//}
//double t1func(double t)
//{
//	return 2 * exp(t) + 2 * exp(-t);
//}
//double t2func(double t)
//{
//	return 2 * exp(t) + exp(2 * t);
//}
//double t3func(double t)
//{
//	return 2 * exp(2 * t) - 2 * exp(-t);
//}
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	ofstream o1("output1.txt"), o2("output2.txt"), o3("output3.txt");
//	o1.clear(), o2.clear(), o3.clear();
//	double a, b, h, u0, u1, u2;
//	readfile(a, b, h, u0, u1, u2);
//	int n = int((b - a) / h) + 1;
//	double* y1 = new double[n];
//	double* y2 = new double[n];
//	double* y3 = new double[n];
//	for (int i = 0; i < n; i++)
//		y1[i] = 0;
//	for (int i = 0; i < n; i++)
//		y2[i] = 0;
//	for (int i = 0; i < n; i++)
//		y3[i] = 0;
//	double* mass = new double[n];
//	for (int i = 0; i < n; i++)
//		mass[i] = a + h * i;
//	y1[0] = u0;
//	y2[0] = u1;
//	y3[0] = u2;
//	double k11 = function(0, y1[0], y2[0], y3[0], mass[0]);
//	double k12 = function(1, y1[0], y2[0], y3[0], mass[0]);
//	double k13 = function(2, y1[0], y2[0], y3[0], mass[0]);
//	double k21 = function(0, y1[0] + h * k11 / 3, y2[0] + h * k12 / 3, y3[0] + h * k13 / 3, mass[0] + h / 3);
//	double k22 = function(1, y1[0] + h * k11 / 3, y2[0] + h * k12 / 3, y3[0] + h * k13 / 3, mass[0] + h / 3);
//	double k23 = function(2, y1[0] + h * k11 / 3, y2[0] + h * k12 / 3, y3[0] + h * k13 / 3, mass[0] + h / 3);
//	if (n > 2)
//	{
//		y1[1] = y1[0] + h * (k11 + 3 * function(0, y1[0] + 2 * h / 3 * k21, y2[0] + 2 * h / 3 * k22, y3[0] + 2 * h / 3 * k23, mass[0] + 2 * h / 3)) / float(4);
//		y2[1] = y2[0] + h * (k12 + 3 * function(1, y1[0] + 2 * h / 3 * k21, y2[0] + 2 * h / 3 * k22, y3[0] + 2 * h / 3 * k23, mass[0] + 2 * h / 3)) / float(4);
//		y3[1] = y3[0] + h * (k13 + 3 * function(2, y1[0] + 2 * h / 3 * k21, y2[0] + 2 * h / 3 * k22, y3[0] + 2 * h / 3 * k23, mass[0] + 2 * h / 3)) / float(4);
//		k11 = function(0, y1[1], y2[1],y3[1], mass[1]);
//		k12 = function(1, y1[1], y2[1], y3[1], mass[1]);
//		k13 = function(2, y1[1], y2[1], y3[1], mass[1]);
//		k21 = function(0, y1[1] + h * k11 / 3, y2[1] + h * k12 / 3, y3[1] + h * k13 / 3, mass[1] + h / 3);
//		k22 = function(1, y1[1] + h * k11 / 3, y2[1] + h * k12 / 3, y3[1] + h * k13 / 3, mass[1] + h / 3);
//		k23 = function(2, y1[1] + h * k11 / 3, y2[1] + h * k12 / 3, y3[1] + h * k13 / 3, mass[1] + h / 3);
//		y1[2] = y1[1] + h * (k11 + 3 * function(0, y1[1] + 2 * h / 3 * k21, y2[1] + 2 * h / 3 * k22, y3[1] + 2 * h / 3 * k23, mass[1] + 2 * h / 3)) / float(4);
//		y2[2] = y2[1] + h * (k12 + 3 * function(1, y1[1] + 2 * h / 3 * k21, y2[1] + 2 * h / 3 * k22, y3[1] + 2 * h / 3 * k23, mass[1] + 2 * h / 3)) / float(4);
//		y3[2] = y3[1] + h * (k13 + 3 * function(2, y1[1] + 2 * h / 3 * k21, y2[1] + 2 * h / 3 * k22, y3[1] + 2 * h / 3 * k23, mass[1] + 2 * h / 3)) / float(4);
//	}
//	for (int i = 3; i < n; i++)
//	{
//		y1[i] = y1[i - 1] + h * (23 * function(0, y1[i - 1], y2[i - 1], y3[i - 1], mass[i - 1]) - 16 * function(0, y1[i - 2], y2[i - 2], y3[i - 2], mass[i - 2]) + 5 * function(0, y1[i - 3], y2[i - 3], y3[i - 3], mass[i - 3])) / float(12);
//		y2[i] = y2[i - 1] + h * (23 * function(1, y1[i - 1], y2[i - 1], y3[i - 1], mass[i - 1]) - 16 * function(1, y1[i - 2], y2[i - 2], y3[i - 2], mass[i - 2]) + 5 * function(1, y1[i - 3], y2[i - 3], y3[i - 3], mass[i - 3])) / float(12);
//		y3[i] = y3[i - 1] + h * (23 * function(2, y1[i - 1], y2[i - 1], y3[i - 1], mass[i - 1]) - 16 * function(2, y1[i - 2], y2[i - 2], y3[i - 2], mass[i - 2]) + 5 * function(2, y1[i - 3], y2[i - 3], y3[i - 3], mass[i - 3])) / float(12);
//	}
//	for (int i = 0; i < n; i++)
//	{
//		o1 << mass[i] << ' ' << y1[i] << endl;
//		o2 << y2[i] << endl;
//		o3 << y3[i] << endl;
//	}
//	double Max1 = -1;
//	for (int i = 0; i < n; i++)
//		if (abs(y1[i] - t1func(mass[i])) > Max1)
//			Max1 = abs(y1[i] - t1func(mass[i]));
//	cout << "Невязка1:" << endl;
//	cout << fixed << setprecision(15) << Max1 << endl;
//	double Max2 = -1;
//	for (int i = 0; i < n; i++)
//		if (abs(y2[i] - t2func(mass[i])) > Max2)
//			Max2 = abs(y2[i] - t2func(mass[i]));
//	cout << "Невязка2:" << endl;
//	cout << fixed << setprecision(15) << Max2 << endl;
//	double Max3 = -1;
//	for (int i = 0; i < n; i++)
//		if (abs(y3[i] - t3func(mass[i])) > Max3)
//			Max3 = abs(y3[i] - t3func(mass[i]));
//	cout << "Невязка3:" << endl;
//	cout << fixed << setprecision(15) << Max3 << endl;
//}
