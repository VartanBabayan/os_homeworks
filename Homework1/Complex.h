#pragma once
class Complex
{
public:
	double a;
	double bi;

	Complex();
	Complex(double a, double bi);

	Complex operator + (const Complex& num);
	Complex operator - (const Complex& num);

	void multiple_by_const(int n);
	double get_absolute_value();
	void print();
};

