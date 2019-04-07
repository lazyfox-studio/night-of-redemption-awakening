#pragma once

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