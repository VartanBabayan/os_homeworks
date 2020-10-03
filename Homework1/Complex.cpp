#include "Complex.h"
#include <cmath>
#include <iostream>

Complex::Complex() {}
Complex::Complex(double a, double bi) : a(a), bi(bi) {}

Complex Complex::operator + (const Complex& num)
{
    return Complex(this->a + num.a, this->bi + num.bi);
}

Complex Complex::operator - (const Complex& num)
{
    return Complex(this->a - num.a, this->bi - num.bi);
}

void Complex::multiple_by_const(int n)
{
    a *= n;
    bi *= n;
}

double Complex::get_absolute_value()
{
    return sqrt(a * a + bi * bi);
}

void Complex::print()
{
    std::cout << a << " + " << bi << "i \n";
}
