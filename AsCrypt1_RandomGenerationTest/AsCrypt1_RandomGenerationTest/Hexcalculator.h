#pragma once

#include <string.h>
using namespace std;

struct bignum
{
	int* num;
	int length = 1;
};

bignum cnum16(string num16, bignum n16);
bignum operator+ (bignum a1, bignum a2);
bignum operator- (bignum a1, bignum a2);
bignum operator* (bignum a1, int a);
bignum operator* (bignum a1, bignum a2);
bignum kvadrat(bignum a1);
bignum operator/ (bignum a1, bignum a2);
bignum GCD(bignum a1, bignum a2);
bignum zero_one(short a);
bignum uborka(bignum a1);
bignum div2(bignum a1);
bignum silentdiv(bignum a1, bignum a2);
bignum mu(bignum a1);
bignum modn(bignum a2, bignum a1, bignum mu);
bignum msum(bignum a2, bignum a3, bignum a1);
bignum msub(bignum a2, bignum a3, bignum a1);
bignum mmul(bignum a2, bignum a3, bignum a1, bignum m);
bignum mpow(bignum a1, bignum a2, bignum n, bignum m);
bignum mmulcopy(bignum a2, bignum a3, bignum a1, bignum m);
bignum diver2(bignum a1, bignum a2);
int bigger(bignum a1, bignum a2);
int* boolform(bignum a2);
void oldi(bignum a1);
bignum divr(bignum a1, bignum a2);
using namespace std;
bignum LCM(bignum a1, bignum a2);
bignum sqr(bignum a1);
bignum mulproof(bignum a1);
bignum copy(bignum T, bignum p);

bignum operator^ (bignum a1, bignum a2);

struct field
{
	bool m[1024];
	field()
	{
		for (int i = 0; i < 1024; i++)
		{
			m[i] = 0;
		}
	}
};

field operator+(field a1, field a2);
field zero();
field multiplication(field a1, field a2);
bignum modnfix(bignum a2, bignum a1, bignum mu);
bignum multiply_errorfix(bignum a1, bignum a2, bignum a4);
bignum mmulcopyfix(bignum a2, bignum a3, bignum a1, bignum m);

bignum mpowfix(bignum a1, bignum a2, bignum n, bignum m);

void cout16(bignum a);
