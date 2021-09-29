#include "generators.h"
#include "Hexcalculator.h"

field operator+(field a1, field a2)
{
	field a3;
	for (int i = 0; i < 1024; i++)
	{
		a3.m[i] = a1.m[i] ^ a2.m[i]; //xor
	}
	return a3;
};
field zero()
{
	field a1;
	return a1;
};
field multiplication(field a1, field a2)
{
	bool a[2048];
	field a3;
	for (int i = 0; i < 2048; i++)
	{
		a[i] = 0;
	}
	for (int i = 0; i < 1024; i++)
	{
		if (a1.m[i] == 1) {
			for (int j = 0; j < 1024; j++)
			{
				a[j + i] = a[j + i] ^ a2.m[j];
			}
		}
	}
	for (int i = 0; i < 444; i++)
	{
		a3.m[i] = a[i];
	}
	return a3;
}
bignum kvadrat(bignum a1)
{
	a1 = a1 * a1;
	return a1;
}
void oldi(bignum a1)  //старшая степень
{
	int* b = boolform(a1);
	int k = (a1.length) * 4 - 1;
	while (b[k] == 0)
	{
		k--;
	}
	cout << "starsha stepin:= " << k + 1 << endl;
}
int* boolform(bignum a2) //что-бы вернуть массив
{
	int* bool_a2 = new int[a2.length * 4];  //строка в булевом представлении
	int ostacha;
	for (int i = 0; i < a2.length; i++)
	{
		ostacha = a2.num[i];  //почти использовал pow
		bool_a2[4 * i] = ostacha % 2;
		ostacha = ostacha / 2;
		bool_a2[4 * i + 1] = ostacha % 2;
		ostacha = ostacha / 2;
		bool_a2[4 * i + 2] = ostacha % 2;
		ostacha = ostacha / 2;
		bool_a2[4 * i + 3] = ostacha % 2;
		ostacha = ostacha / 2;
	}
	return (bool_a2);
}
bignum uborka(bignum a1) //убирает лишнии нули перед числом
{
	int k = a1.length;
	bignum a3;
	while (a1.num[k - 1] == 0)
	{
		k = k - 1;
	}
	if (k == 0) { k = 1; }
	a3.length = k;
	a3.num = new int[a3.length];
	for (int i = 0; i < a3.length; i++)
	{
		a3.num[i] = a1.num[i];
	}
	delete[] a1.num;
	return a3;
}


bignum operator^ (bignum a1, bignum a2)
{
	bignum a3;
	a3.length = a1.length;
	a3.num = new int[a3.length];
	a3.num[0] = 1;
	for (int i = 1; i < a3.length; i++)
	{
		a3.num[i] = 0;
	}
	int* bool_a2 = boolform(a2);
	for (int i = 0; i < a2.length * 4; i++)
	{
		if (bool_a2[a2.length * 4 - i] == 1) { a3 = a3 * a1; }
		a3 = kvadrat(a3);
	}
	if (bool_a2[0] == 1) { a3 = a3 * a1; }
	return (a3);
}

bignum silentdiv (bignum a1, bignum a2)
{
	int t;
	int k = a2.length;
	bignum r, temp;
	r.length = a1.length;
	r.num = new int[r.length];
	for (int i = 0; i < r.length; i++)
	{
		r.num[i] = a1.num[i];
	}
	bignum q = zero_one(0);
	bignum two = zero_one(2);
	bignum to = zero_one(1);
	while (bigger(r, a2) >= 0)
	{
		t = r.length;
		temp.length = a2.length + (t - k);
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < temp.length - t + k; j++)
		{
			temp.num[j + t - k] = a2.num[j];
		}
		if ((bigger(r, temp) == -1) && (t - k >= 0))
		{
			delete[] temp.num;
			t = t - 1;
			temp.length = a2.length + (t - k);
			temp.num = new int[temp.length];
			for (int j = 0; j < temp.length; j++)
			{
				temp.num[j] = 0;
			}
			for (int j = 0; j < temp.length - t + k; j++)
			{
				temp.num[j + t - k] = a2.num[j];
			}
		}
		//это на всякий случай, ибо иногда у меня остача на 1 раз больше отнимается
		r = r - temp;
		q = q + (two ^ (to * (t - k) * 4));

	}
	return (q);
}
bignum zero_one(short a)
{
	bignum a3;
	a3.num = new int[a3.length];
	a3.num[0] = a;
	return a3;
}

bignum operator* (bignum a1, int a)  //умножаю на инт, немного оптимизировал в обратную сторону ибо что-то пошло не так
{
	bignum a3;
	a3.length = a1.length + 1;
	a3.num = new int[a3.length];
	a3.num[a3.length - 1] = 0;
	for (int i = 0; i < a1.length; i++) { a3.num[i] = a1.num[i] * a; }
	for (int i = 0; i < a3.length - 1; i++)
	{
		while (a3.num[i] >= 16) {a3.num[i] = a3.num[i] - 16; a3.num[i + 1]++; }
	}
	return a3;
}
bignum operator* (bignum a1, bignum a2) //умножаю
{
	bignum a3, temp;
	a3.length = a1.length + a2.length;
	a3.num = new int[a3.length];
	for (int i = 0; i < a3.length; i++)
	{
		a3.num[i] = 0;
	}
	for (int i = 0; i < a2.length; i++) //в этой функции по сути добавляю то же умножение но на порядок выше. По аналогии с
	{								//десятиричным исчислением типо 15*12 = 15*2 + 150*1 (я его даже в тетрадку записал когда придумать пытался)
		temp.length = a1.length + i;
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < a1.length; j++)
		{
			temp.num[j + i] = a1.num[j];
		}
		a3 = a3 + (temp * a2.num[i]); //вот тут эти самые 15*2 и 150*1 и их сумма и происходят
		delete[] temp.num;
	}
	/*int k = a3.length;
	while (a3.num[k - 1] == 0) //в процессе оптимизация затраченной памяти
	{

	}*/
	a3 = uborka(a3);
	return a3;
}
bignum operator+ (bignum a1, bignum a2)  //суммирую
{
	bignum a3;
	int l_max, l_min;
	if (a1.length >= a2.length) { l_max = a1.length; l_min = a2.length; }
	else { l_max = a2.length; l_min = a1.length; }
	a3.length = l_max + 1;
	a3.num = new int[a3.length];
	a3.num[l_max] = 0;
	if (a1.length >= a2.length)
	{
		for (int i = 0; i < a1.length; i++) { a3.num[i] = a1.num[i]; }
		for (int i = 0; i < a2.length; i++) { a3.num[i] = a3.num[i] + a2.num[i]; }
	}
	else
	{
		for (int i = 0; i < a2.length; i++) { a3.num[i] = a2.num[i]; }
		for (int i = 0; i < a1.length; i++) { a3.num[i] = a3.num[i] + a1.num[i]; }
	}
	for (int i = 0; i < a3.length; i++) { if (a3.num[i] >= 16) { a3.num[i] = a3.num[i] - 16; a3.num[i + 1]++; } }
	a3 = uborka(a3);
	return a3;
}

int bigger(bignum a1, bignum a2) //сравниваю
{
	int b = 0;
	if (a1.length > a2.length) { b = 1; }
	else
	{
		if (a2.length > a1.length) { b = -1; }
		else {
			int i = a1.length - 1;
			while ((a1.num[i] == a2.num[i]) && (i > 0))
			{
				i--;
			}
			if (a1.num[i] == a2.num[i]) { b = 0; }
			else {
				if (a1.num[i] > a2.num[i]) { b = 1; }
				if (a2.num[i] > a1.num[i]) { b = -1; }
			}
		}
	}
	return b;
}

bignum cnum16(string a, bignum n16)
{
	n16.length = a.length();
	n16.num = new int[n16.length];
	for (int i = 0; i < n16.length; i++)
	{
		switch (a[n16.length - i - 1])
		{
		case '1': {n16.num[i] = 1; break; }
		case '2': {n16.num[i] = 2; break; }
		case '3': {n16.num[i] = 3; break; }
		case '4': {n16.num[i] = 4; break; }
		case '5': {n16.num[i] = 5; break; }
		case '6': {n16.num[i] = 6; break; }
		case '7': {n16.num[i] = 7; break; }
		case '8': {n16.num[i] = 8; break; }
		case '9': {n16.num[i] = 9; break; }
		case '0': {n16.num[i] = 0; break; }
		case 'A': {n16.num[i] = 10; break; }
		case 'B': {n16.num[i] = 11; break; }
		case 'C': {n16.num[i] = 12; break; }
		case 'D': {n16.num[i] = 13; break; }
		case 'E': {n16.num[i] = 14; break; }
		case 'F': {n16.num[i] = 15; break; }
		default: {cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; break; }
		}
	}
	return n16;
};

bignum GCD(bignum a1, bignum a2)
{
	bignum d = zero_one(1);
	bignum z = zero_one(0);
	bignum t1 = zero_one(0);
	bignum a3 = zero_one(0); bignum a4 = zero_one(0);
	bignum r = zero_one(1);
	bignum r1 = zero_one(1);
	if (bigger(a2, a1) >= 0)
	{
		delete[] r1.num;
		r1.length = a1.length;
		r1.num = new int[a1.length];
		for (int i = 0; i < r.length; i++)
		{
			r1.num[i] = a1.num[i];
		}
	}
	else {
		delete[] r1.num;
		r1.length = a2.length;
		r1.num = new int[a2.length];
		for (int i = 0; i < r.length; i++)
		{
			r1.num[i] = a2.num[i];
		}
	}
	while (true)
	{
		if (bigger(a1, a2) >= 0)
		{
			r = divr(a1, a2);
			if (bigger(r, z) == 0) { break; }
			else {
				delete[] a1.num;
				a1.length = r.length;
				a1.num = new int[a1.length];
				for (int i = 0; i < r.length; i++)
				{
					a1.num[i] = r.num[i];
				}
				if (bigger(a2, a1) >= 0)
				{
					delete[] r1.num;
					r1.length = a1.length;
					r1.num = new int[a1.length];
					for (int i = 0; i < r.length; i++)
					{
						r1.num[i] = a1.num[i];
					}
				}
				else {
					delete[] r1.num;
					r1.length = a2.length;
					r1.num = new int[a2.length];
					for (int i = 0; i < r.length; i++)
					{
						r1.num[i] = a2.num[i];
					}
				}
			}
		}
		else
		{
			r = divr(a2, a1); if (bigger(r, z) == 0) { break; }
			else {
				delete[] a2.num;
				a2.length = r.length;
				a2.num = new int[a2.length];
				for (int i = 0; i < r.length; i++)
				{
					a2.num[i] = r.num[i];
				}
				if (bigger(a2, a1) >= 0)
				{
					delete[] r1.num;
					r1.length = a1.length;
					r1.num = new int[a1.length];
					for (int i = 0; i < r.length; i++)
					{
						r1.num[i] = a1.num[i];
					}
				}
				else {
					delete[] r1.num;
					r1.length = a2.length;
					r1.num = new int[a2.length];
					for (int i = 0; i < r.length; i++)
					{
						r1.num[i] = a2.num[i];
					}
				}
			}
		}
	}
	/*while ((a1.num[0] % 2 == 0) && (a2.num[0] % 2 == 0))
	{
		a1 = div2(a1);
		a2 = div2(a2);
		d = d * 2;
	}
	while (a1.num[0] % 2 == 0)
	{
		a1 = div2(a1);
	}

	while ((a2.length >= 1) && (a2.num[0] > 0))
	{
		while ((a1.num[0] % 2 == 0) && (a2.num[0] % 2 == 0))
		{
			a1 = div2(a1);
			a2 = div2(a2);
			d = d * 2;
		}
		while (a1.num[0] % 2 == 0)
		{
			a1 = div2(a1);
		}
		while (a2.num[0] % 2 == 0)
		{
			a2 = div2(a2);
		}
		if (bigger(a1, a2) >= 0)
		{
			delete[] t1.num;
			t1.length = a2.length;
			t1.num = new int[t1.length];
			for (int j = 0; j < t1.length; j++)
			{
				t1.num[j] = a2.num[j];
			}
		}
		else
		{
			delete[] t1.num;
			t1.length = a1.length;
			t1.num = new int[t1.length];
			for (int j = 0; j < t1.length; j++)
			{
				t1.num[j] = a1.num[j];
			}
		} //а3 и а4
		{
			delete[] a3.num;
			a3.length = a1.length;
			if (a3.length == 0) { a3.length = 1; }
			a3.num = new int[a3.length];
			for (int j = 0; j < a3.length; j++)
			{
				a3.num[j] = a1.num[j];
			}
			delete[] a4.num;
			a4.length = a2.length;
			if (a4.length == 0) { a4.length = 1; }
			a4.num = new int[a4.length];
			for (int j = 0; j < a4.length; j++)
			{
				a4.num[j] = a2.num[j];
			}
		} //а3 и а4
		a2 = absminus(a3, a4);
		delete[] a1.num;
		a1.length = t1.length;
		a1.num = new int[a1.length];
		for (int j = 0; j < t1.length; j++)
		{
			a1.num[j] = t1.num[j];
		}
	}
	d = t1*d;*/
	return r1;
}

bignum div2(bignum a1)
{
	int t;
	bignum two = zero_one(2);
	int k = two.length;
	bignum r, temp;
	r.length = a1.length;
	r.num = new int[r.length];
	for (int i = 0; i < r.length; i++)
	{
		r.num[i] = a1.num[i];
	}
	bignum q = zero_one(0);
	bignum to = zero_one(1);
	while (bigger(r, two) >= 0)
	{
		t = r.length;
		temp.length = two.length + (t - k);
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < temp.length - t + k; j++)
		{
			temp.num[j + t - k] = two.num[j];
		}
		if ((bigger(r, temp) == -1) && (t - k >= 0))
		{
			delete[] temp.num;
			t = t - 1;
			temp.length = two.length + (t - k);
			temp.num = new int[temp.length];
			for (int j = 0; j < temp.length; j++)
			{
				temp.num[j] = 0;
			}
			for (int j = 0; j < temp.length - t + k; j++)
			{
				temp.num[j + t - k] = two.num[j];
			}

		}
		r = r - temp;
		q = q + (two ^ (to * (t - k) * 4)) * (temp.num[temp.length - 1] / 2);

	}
	return (q);
} //деление на 2.
bignum divr(bignum a1, bignum a2)
{
	int t;
	int k = a2.length;
	bignum r, temp;
	r.length = a1.length;
	r.num = new int[r.length];
	for (int i = 0; i < r.length; i++)
	{
		r.num[i] = a1.num[i];
	}
	bignum q = zero_one(0);
	bignum two = zero_one(2);
	bignum to = zero_one(1);
	while (bigger(r, a2) >= 0)
	{
		t = r.length;
		temp.length = a2.length + (t - k);
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < temp.length - t + k; j++)
		{
			temp.num[j + t - k] = a2.num[j];
		}
		if ((bigger(r, temp) == -1) && (t - k >= 0))
		{
			delete[] temp.num;
			t = t - 1;
			temp.length = a2.length + (t - k);
			temp.num = new int[temp.length];
			for (int j = 0; j < temp.length; j++)
			{
				temp.num[j] = 0;
			}
			for (int j = 0; j < temp.length - t + k; j++)
			{
				temp.num[j + t - k] = a2.num[j];
			}
		}
		//это на всякий случай, ибо иногда у меня остача на 1 раз больше отнимается
		r = r - temp;
		q = q + (two ^ (to * (t - k) * 4));

	}
	return (r);
}
bignum mu(bignum a1)
{
	bignum mu;
	bignum b;
	b.length = a1.length * 2 + 1;
	b.num = new int[b.length];
	for (int i = 0; i < b.length; i++)
	{
		b.num[i] = 0;
	}

	b.num[b.length - 1] = 1;
	mu = silentdiv(b, a1);
	return mu;
}
bignum modn(bignum a2, bignum a1, bignum mu)
{
	bignum a1_1;
	if (bigger(a2, a1) == -1) { return a2; }
	a1_1 = copy(a1_1, a1);
	bignum q, q1;
	bignum r;

	if (a2.length < 2 * a1.length) {
		r.length = a1.length * 2;
		r.num = new int[r.length];
		for (int i = a1.length; i < r.length; i++)
		{
			r.num[i] = 0;
		}
		for (int i = 0; i < a2.length; i++)
		{
			r.num[i] = a2.num[i];
		}
	}
	else {
		r.length = a2.length;
		r.num = new int[a2.length];
		for (int i = 0; i < a2.length; i++)
		{
			r.num[i] = a2.num[i];
		}
	}

	q.length = r.length - a1.length + 1;
	q.num = new int[q.length];
	for (int i = 0; i < q.length; i++)
	{
		q.num[i] = r.num[i + a1.length - 1];
	}
	bignum q2; q2 = q * mu;
	q1.length = q2.length - a1.length - 1;
	q1.num = new int[q1.length];
	for (int i = 0; i < q1.length; i++)
	{
		q1.num[i] = q2.num[i + a1.length + 1];
	}
	r = r - (q1 * a1_1);

	while (bigger(r, a1) >= 0)
	{
		r = r - a1_1;
	}
	delete[] a1_1.num;
	delete[] a2.num;
	delete[] q2.num;	//память(
	return(r);
}
bignum msum(bignum a2, bignum a3, bignum a1)
{
	bignum a4 = a3 + a2;
	bignum m;
	m = mu(a1);
	a4 = modn(a4, a1, m);
	return a4;
}

bignum msub(bignum a2, bignum a3, bignum a1)
{
	bignum a4;
	bignum m;
	m = mu(a1);
	if (bigger(a2, a3) >= 0) { a4 = a2 - a3; a4 = modn(a4, a1, m); }
	else { while (bigger(a2, a3) < 0) { a2 = a2 + a1; } a4 = a2 - a3; }

	return a4;
}

bignum mmul(bignum a2, bignum a3, bignum a1, bignum m)
{
	bignum a4, a2_1, a3_1;
	a2_1 = modn(a2, a1, m);
	a3_1 = modn(a3, a1, m);
	a4 = a2_1 * a3_1;
	a4 = modn(a4, a1, m);
	return a4;
}

bignum mmulcopy(bignum a2, bignum a3, bignum a1, bignum m) //обычное умножение возможно память ломает
{
	bignum a4, a2_1, a3_1;
	a2_1 = modn(a2, a1, m);
	a3_1 = modn(a3, a1, m);
	a4 = modn(a2_1 * a3_1, a1, m);
	return a4;
}

bignum mpow(bignum a1, bignum a2, bignum n, bignum m)
{
	bignum a3;
	bignum a1_1;
	a1_1.length = a1.length;
	a1_1.num = new int[a1_1.length];
	for (int i = 1; i < a1.length; i++)
	{
		a1_1.num[i] = a1.num[i];
	}
	a3.length = a1.length;
	a3.num = new int[a3.length];
	a3.num[0] = 1;
	for (int i = 1; i < a3.length; i++)
	{
		a3.num[i] = 0;
	}
	int* bool_a2 = boolform(a2);
	for (int i = 0; i < a2.length * 4; i++)
	{
		if (bool_a2[a2.length * 4 - i] == 1) { a3 = mmulcopy(a3, a1_1, n, m); }
		mulproof(a3);
		a3 = modn(a3, n, m);
	}
	if (bool_a2[0] == 1) { a3 = mmulcopy(a3, a1_1, n, m); }
	delete[] bool_a2;
	delete[] a1_1.num;
	delete[] a2.num;
	return (a3);
}

bignum sqr(bignum a1)
{
	int a;
	int* s = boolform(a1);
	field sb;
	field sb2;
	field check;
	field c;
	field sqrt;
	a = 1024;
	int q = 0;
	if (a1.length * 4 < 1024) { a = a1.length; }
	for (int i = 1; i < a; i = i++)
	{
		sb.m[i] = s[i];
	}
	int* sqqr = new int[1024];
	for (int i = 1; i < 512; i = i + 2)
	{
		q = 1023;
		for (int j = 0; j <= i; j++)
		{
			check.m[j] = 1;
			sb2.m[j] = s[j];
			sb2.m[i + j] = s[i + j];
		}
		c = multiplication(check, check);
		while ((sb2.m[i] == c.m[i]) && (q > 0))
		{
			q--;
		}
		if (check.m[q] == 1)
		{
			sqrt.m[int(i / 2)] = 1;
		}
	}
	bignum a2;
	a2.length = 1024 / 4;
	a2.num = new int[a2.length];
	for (int i = 0; i < a2.length; i++)
	{
		a2.num[i] = 0;
	}
	bignum two = zero_one(2);;
	for (int i = 0; i < 1024 / 4; i++)
	{
		a2.num[i] = a2.num[i] + 1 * sqrt.m[4 * i];
		a2.num[i] = a2.num[i] + 2 * sqrt.m[4 * i + 1];
		a2.num[i] = a2.num[i] + 4 * sqrt.m[4 * i + 2];
		a2.num[i] = a2.num[i] + 8 * sqrt.m[4 * i + 3];
	}
	a2 = uborka(a2);
	delete[] a1.num;
	delete[] s;
	delete[] sqqr;
	return a2;
}

bignum mulproof (bignum a1) //умножаю
{
	bignum a3, temp;
	a3.length = a1.length + a1.length;
	a3.num = new int[a3.length];
	for (int i = 0; i < a3.length; i++)
	{
		a3.num[i] = 0;
	}
	for (int i = 0; i < a1.length; i++) //в этой функции по сути добавляю то же умножение но на порядок выше. По аналогии с
	{								//десятиричным исчислением типо 15*12 = 15*2 + 150*1 (я его даже в тетрадку записал когда придумать пытался)
		temp.length = a1.length + i;
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < a1.length; j++)
		{
			temp.num[j + i] = a1.num[j];
		}
		a3 = a3 + (temp * a1.num[i]); //вот тут эти самые 15*2 и 150*1 и их сумма и происходят
		delete[] temp.num;
	}
	delete[] a1.num;
	a3 = uborka(a3);
	return a3;
}

bignum modnproof(bignum a2, bignum a1, bignum mu)
{
	bignum q, q1;
	bignum x, r;
	if (bigger(a2, a1) == -1) { return a2; }
	if (a2.length < 2 * a1.length) {
		x.length = a1.length * 2;
		x.num = new int[x.length];
		for (int i = a1.length; i < x.length; i++)
		{
			x.num[i] = 0;
		}
		for (int i = 0; i < a2.length; i++)
		{
			x.num[i] = a2.num[i];
		}
	}
	else {
		x = a2;
	}
	q.length = x.length - a1.length + 1;
	q.num = new int[q.length];
	for (int i = 0; i < q.length; i++)
	{
		q.num[i] = x.num[i + a1.length - 1];
	}
	q1.length = q.length - a1.length - 1;
	q1.num = new int[q1.length];
	for (int i = 0; i < q1.length; i++)
	{
		q1.num[i] = q.num[i + a1.length + 1];
	}
	r = x - q1 * a1;
	while (bigger(r, a1) >= 0)
	{
		//	cout16(mu);
		//	cout16(r);
		//	cout16(a1);
		//	cout << endl;
		r = r - a1;
	}
	return(r);
}

bignum diver2(bignum a1, bignum a2)
{
	int t; int koef;
	int k = a2.length;
	bignum r, temp, temp2;
	r.length = a1.length;
	r.num = new int[r.length];
	for (int i = 0; i < r.length; i++)
	{
		r.num[i] = a1.num[i];
	}
	bignum q = zero_one(0);
	bignum two = zero_one(2);
	bignum to = zero_one(1);
	while (bigger(r, a2) >= 0)
	{
		t = r.length;
		temp.length = a2.length + (t - k);
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < temp.length - t + k; j++)
		{
			temp.num[j + t - k] = a2.num[j];
		}
		if ((bigger(r, temp) == -1) && (t - k >= 0))
		{
			t = t - 1;
			temp2.length = a2.length + (t - k);
			temp2.num = new int[temp.length];
			for (int j = 0; j < temp.length; j++)
			{
				temp2.num[j] = 0;
			}
			for (int j = 0; j < temp.length - t + k; j++)
			{
				temp2.num[j + t - k] = a2.num[j];
			}
			while (bigger(r, temp) == -1) { temp = temp - temp2; }
		}
		//это на всякий случай, ибо иногда у меня остача на 1 раз больше отнимается
		r = r - temp;
		q = q + (two ^ (to * (t - k) * 4));
		delete[] temp.num;
	}
	return (q);
}
bignum operator- (bignum a1, bignum a2) //отнимание
{
	bignum a3;
	if (a1.length > a2.length)
	{
		for (int i = 0; i < a2.length; i++) { a1.num[i] = a1.num[i] - a2.num[i]; }
		for (int i = 0; i < a1.length; i++) { if (a1.num[i] < 0) { a1.num[i] = a1.num[i] + 16; a1.num[i + 1]--; } }
		a3 = a1;
	}
	if (a1.length < a2.length) //типо делаю вид что вычетание работает просто поменяв местами цифры
	{
		for (int i = 0; i < a1.length; i++) { a2.num[i] = a2.num[i] - a1.num[i]; }
		for (int i = 0; i < a2.length; i++) { if (a2.num[i] < 0) { a2.num[i] = a2.num[i] + 16; a2.num[i + 1]--; } }
		a3 = a2;
		cout << "-";
	}
	if (a1.length == a2.length)
	{
		int i = a1.length - 1;
		while (a1.num[i] == a2.num[i]) //нахожу старший бит в котором есть отличия
		{
			i--;
		}
		if (i < 0) { i = 0; }
		if (a1.num[i] >= a2.num[i])
		{
			for (int i = 0; i < a2.length; i++) { a1.num[i] = a1.num[i] - a2.num[i]; }
			for (int i = 0; i < a1.length; i++) { if (a1.num[i] < 0) { a1.num[i] = a1.num[i] + 16; a1.num[i + 1]--; } }
			a3 = a1;
		}
		else  //типо делаю вид что вычетание работает просто поменяв местами цифры
		{
			for (int i = 0; i < a1.length; i++) { a2.num[i] = a2.num[i] - a1.num[i]; }
			for (int i = 0; i < a2.length; i++) { if (a2.num[i] < 0) { a2.num[i] = a2.num[i] + 16; a2.num[i + 1]--; } }
			a3 = a2;
			cout << "-";
		}
	}
	a3 = uborka(a3);
	return a3;
}

bignum multiply_errorfix(bignum a1, bignum a2, bignum a4) //умножаю
{
	bignum a3, temp;
	a3.length = a1.length + a2.length;
	a3.num = new int[a3.length];
	for (int i = 0; i < a3.length; i++)
	{
		a3.num[i] = 0;
	}
	for (int i = 0; i < a2.length; i++) //в этой функции по сути добавляю то же умножение но на порядок выше. По аналогии с
	{								//десятиричным исчислением типо 15*12 = 15*2 + 150*1 (я его даже в тетрадку записал когда придумать пытался)
		temp.length = a1.length + i;
		temp.num = new int[temp.length];
		for (int j = 0; j < temp.length; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < a1.length; j++)
		{
			temp.num[j + i] = a1.num[j];
		}
		a3 = a3 + (temp * a2.num[i]); //вот тут эти самые 15*2 и 150*1 и их сумма и происходят
		delete[] temp.num;
	}
	delete[] a4.num;
	a3 = uborka(a3);
	return a3;
}

bignum modnfix(bignum a2, bignum a1, bignum mu)
{
	bignum q, q1;
	bignum r;
	if (bigger(a2, a1) == -1) { return a2; }
	if (a2.length < 2 * a1.length) {
		r.length = a1.length * 2;
		r.num = new int[r.length];
		for (int i = a1.length; i < r.length; i++)
		{
			r.num[i] = 0;
		}
		for (int i = 0; i < a2.length; i++)
		{
			r.num[i] = a2.num[i];
		}
	}
	else {
		r.length = a2.length;
		r.num = new int[r.length];
		for (int i = 0; i < a2.length; i++)
		{
			r.num[i] = a2.num[i];
		}
	}
	q.length = r.length - a1.length + 1;
	q.num = new int[q.length];
	for (int i = 0; i < q.length; i++)
	{
		q.num[i] = r.num[i + a1.length - 1];
	}
	q = multiply_errorfix(q, mu, q);

	q1.length = q.length - a1.length - 1;
	q1.num = new int[q1.length];
	for (int i = 0; i < q1.length; i++)
	{
		q1.num[i] = q.num[i + a1.length + 1];
	}
	q1 = multiply_errorfix(q1, a1, q1);
	r = r - q1;
	r = uborka(r);
	while (bigger(r, a1) >= 0)
	{
		r = r - a1;
	}
	delete[] q.num;
	delete[] q1.num;
	return(r);
}


bignum mmulcopyfix(bignum a2, bignum a3, bignum a1, bignum m) //обычное умножение возможно память ломает
{
	bignum a4, a2_1, a3_1;
	a2_1 = modnfix(a2, a1, m);
	a3_1 = modnfix(a3, a1, m);
	a4 = modn(multiply_errorfix(a2_1, a3_1, a2_1), a1, m);
	return a4;
}

bignum mpowfix(bignum a1, bignum a2, bignum n, bignum m)
{
	bignum a3;
	bignum a1_1;
	a1_1.length = a1.length;
	a1_1.num = new int[a1_1.length];
	for (int i = 1; i < a1.length; i++)
	{
		a1_1.num[i] = a1.num[i];
	}
	a3.length = a1.length;
	a3.num = new int[a3.length];
	a3.num[0] = 1;
	for (int i = 1; i < a3.length; i++)
	{
		a3.num[i] = 0;
	}
	int* bool_a2 = boolform(a2);
	for (int i = 0; i < a2.length * 4; i++)
	{
		if (bool_a2[a2.length * 4 - i] == 1) { a3 = mmulcopyfix(a3, a1_1, n, m); }
		multiply_errorfix(a3, a3, a3);
		a3 = modnfix(a3, n, m);
	}
	if (bool_a2[0] == 1) { a3 = mmulcopyfix(a3, a1_1, n, m); }
	delete[] bool_a2;
	delete[] a1_1.num;
	delete[] a2.num;
	return (a3);
}

bignum copy(bignum T, bignum p)
{
	T.length = p.length;
	T.num = new int[T.length];
	for (int i = 0; i < T.length; i++)
	{
		T.num[i] = p.num[i];
	}
	return T;
}

void cout16(bignum a) //вывод
{
	int k = a.length - 1;
	/*while (a.num[k]==0)  больше не нужно, спасибо уборке, но оставлю тут на память
	{
		k--;
	}*/
	for (int i = k; i >= 0; i--)
	{
		switch (a.num[i])
		{
		case 1: {cout << "1"; break; }
		case 2: {cout << "2"; break; }
		case 3: {cout << "3"; break; }
		case 4: {cout << "4"; break; }
		case 5: {cout << "5"; break; }
		case 6: {cout << "6"; break; }
		case 7: {cout << "7"; break; }
		case 8: {cout << "8"; break; }
		case 9: {cout << "9"; break; }
		case 0: {cout << "0"; break; }
		case 10: {cout << "A"; break; }
		case 11: {cout << "B"; break; }
		case 12: {cout << "C"; break; }
		case 13: {cout << "D"; break; }
		case 14: {cout << "E"; break; }
		case 15: {cout << "F"; break; }
		default: {cout << a.num[i]; break; }
		}
	}
}