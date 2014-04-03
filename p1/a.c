#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>
#include<string.h>
#include<math.h>

int isallnum(char *s)
{
	char *i;
	for (i = s; *i; i++) {
		if (!(isdigit(*i) || *i == '.' || tolower(*i) == 'e')) {
			return 0;
		}
	}
	return 1;
}

int nice[256];
int dnice[256];

double calc(char *);
double advanced_calc(char *s)
{
	int i;
	double val;
	if (tolower(s[0]) == 's') {
		s += 4;
		s[strlen(s) - 1] = 0;
		return sin(calc(s));
	} else if (tolower(s[0]) == 'c') {
		s += 4;
		s[strlen(s) - 1] = 0;
		return cos(calc(s));
	} else if (tolower(s[0]) == 't') {
		s += 4;
		s[strlen(s) - 1] = 0;
		return tan(calc(s));
	} else {
		assert(0);
	}
}

int isoutb(char *s)
{
	int tz = 0;
	if (*s != '(')
		return 0;
	for (; *s; s++) {
		tz += dnice[*s];
		if (tz == 0 && s[1])
			return 0;
	}
	return 1;
}

int ishsmath(char *s)
{
	return isalpha(s[0]) && isalpha(s[1]) && isalpha(s[2])
	    && isoutb(s + 3);
}

double calc(char *str)
{
	int i, p = 0, minp = INT_MAX, minpk;
	char op;
	while (isoutb(str)) {
		str++;
		str[strlen(str) - 1] = 0;
	}
	if (isallnum(str)) {
		double v;
		sscanf(str, "%lf", &v);
		return v;
	}
	if (ishsmath(str)) {
		return advanced_calc(str);
	}
	for (i = 0; str[i]; i++) {
		p += dnice[str[i]];
		if (p + nice[str[i]] <= minp && nice[str[i]]) {
			minp = p + nice[str[i]];
			minpk = i;
		}
	}
	op = str[minpk];
	str[minpk] = 0;
	double a = calc(str);
	double b = calc(str + minpk + 1);
	if (op == '+') {
		return a + b;
	} else if (op == '-') {
		return a - b;
	} else if (op == '*') {
		return a * b;
	} else if (op == '/') {
		return a / b;
	} else if (op == '^') {
		return pow(a, b);
	} else {
		assert(0);
	}
}

int main()
{
	char s[256];
	nice['+'] = nice['-'] = 5;
	nice['*'] = nice['/'] = 10;
	nice['^'] = 15;
	dnice['('] = 500;
	dnice[')'] = -500;
	fgets(s, 256, stdin);
	s[strlen(s) - 1] = 0;
	printf("%.3lf\n", calc(s));
	return 0;
}
