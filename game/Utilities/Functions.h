#pragma once
#include <cstdlib>
#include <ctime>

// Возвращает указатель на строку, полученную из заданного числа
const char* stringify(int n)
{
	int n2, digits = 0, i, sign;
	if (n == 0)
	{
		char* s = new char[2];
		s[0] = '0';
		s[1] = 0;
		return s;
	}
	if (n > 0)
	{
		n2 = n;
		sign = 0;
	}
	else
	{
		n2 = n = n * (-1);
		sign = 1;
	}
	while (n2 > 0)
	{
		digits++;
		n2 /= 10;
	}
	char* s = new char[sign + digits + 1];
	s[sign + digits] = 0;
	i = sign + digits - 1;
	while (n > 0)
	{
		int digit = n % 10;
		s[i--] = '0' + digit;
		n /= 10;
	}
	if (sign)
		s[0] = '-';
	return s;
}

// Возвращает случайное число в заданном диапазоне
int random(int min = 0, int max = INT_MAX)
{
	return rand() % (max - min + 1) + min;
}

float random(float min = 0.f, float max = float(INT_MAX))
{
	int _max = (int)max, _min = (int)min;
	return (float)(rand() % (_max - _min + 1) + _min);
}

// НОД
int GCD(int n1, int n2)
{
	int rem;
	if (n1 < n2)
	{
		int tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
	while (rem = n1 % n2)
	{
		n1 = n2;
		n2 = rem;
	}
	return n2;
}