// AsCrypt3_Rabin.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MainHeader.h"


ZZ generate_random_prime(ZZ two);
ZZ Decrypt(ZZ y, ZZ C[2], ZZ pk[3]);
int prime_test(ZZ x);
void GenerateKeyPair(ZZ public_key[3], ZZ protected_key[3]);
int jakobi(ZZ x, ZZ b, ZZ n);
ZZ Encrypt(ZZ m, ZZ C[2], ZZ pk[3]);
ZZ PowGorner(ZZ x, ZZ a, ZZ n);
ZZ Egcd(ZZ a, ZZ b, ZZ& u, ZZ& v, ZZ uv[2]);
void fastroot(ZZ p, ZZ q, ZZ y, ZZ x[4]);
ZZ Sign(ZZ m, ZZ p, ZZ q);
ZZ Verify(ZZ m, ZZ s, ZZ n);
ZZ HexToDecimal(string hex);
string DecimalToHex(ZZ hex);
ZZ zero_knowledge(string n);
ZZ deformat(ZZ xe2, ZZ n);

int main()
{
	ZZ public_key[3];
	ZZ protected_key[3];
	GenerateKeyPair(public_key, protected_key);
	ZZ C[2];
	ZZ m;
	cin >> m;
	cout << "n: " << DecimalToHex(public_key[0]) << endl;
	cout << "b: " << DecimalToHex(public_key[1]) << endl;
	cout << "m: " << DecimalToHex(m) << endl;
	ZZ y = Encrypt(m, C, public_key);
	cout << "y: " << y << endl;
	ZZ x = Decrypt(y, C, protected_key);
	cout << x<<endl;
	ZZ s = Sign(m, protected_key[0], protected_key[1]);
	ZZ ver_m = Verify(m, s, public_key[0]);
	cout << "zero protocol modulus:"<<endl;
	string mod;
	while (true)
	{
		cin >> mod;
		zero_knowledge(mod);
	}
}

ZZ generate_random_prime(ZZ two)
{
	ZZ p(1);
	ZZ n = power(ZZ(2), 130);
	ZZ n_0 = two * two;
	ZZ x;
	x = RandomBnd(n);
	x = x + n_0;
	ZZ m;
	ZZ n2 = n + n_0;
	m = x;
	if (!IsOdd(x))
	{
		m = x + 1;
	}
	if (bit(m, 1) == 0)
	{
		m = m + 2;
	}
	for (ZZ i = m; i < 2*n2; i += 4)
	{
		if (prime_test(i) == 1)
		{
			return(i);
		}
		cout << i << endl;
	}
	return generate_random_prime(two);
}

int prime_test(ZZ x)
{

	ZZ p = x;
	int s=0;
	ZZ d = p-1;
	int k = 500;
	ZZ x_;
	while (bit(d, 0) == 0)
	{
		d = RightShift(d, 1); //розкладає на 2^s та d число p-1
		s++;
	}
	//cout << d << endl;
	//cout << s << endl;
	for (int i = 0; i < k; i++)
	{
		x_ = RandomBnd(x - 1); //генерує випадкове х_,
		if (GCD(x, x_) > ZZ(1)) //якщо gcd(p ,x_) > 1 -> p - не просте
		{
			return 0;
		}
		x_ = PowerMod(x_, d , x);//взводить в степінь d
		//cout << x_ << endl; 
		if (x_ == ZZ(1))
		{
			//cout << "x = " << x<<endl;
			continue; //x_^d mod p = 1 => p - сильнопсевдопросте за основую x_, переходимо до наступної ітерації x_
		
		}
		if (x_ == ZZ(x - 1))
		{
			//cout << "x = " << x<<endl;
			continue;
		}
		for (int r=0; r <= s; r++)
		{
			x_ = SqrMod(x_, x); //взводимо x_^d*(2^r) в квадрат
			if (x_ == ZZ(x-1))
			{
				break; //псевдопросте за основою x_
			}
			if (x_ == ZZ(1))
			{
				return 0; //не просте
			}
			if (r == s)
			{
				return 0; //не просте
			}
		}
	}
	return 1;
	/*
	int k = 5000;
	for (int i = 0; i < k; i++)
	{
		if (GCD(x, RandomBnd(x)) != 1)
		{
			return 0;
		}
	}
	return 1;*/
}

void GenerateKeyPair(ZZ public_key[3], ZZ protected_key[3])
{
	ZZ q(1);
	ZZ p(1);
	ZZ two(2);
	two = power(two, 64);
	ZZ two2(1);
	cout<<"not primes on way:";
	q = generate_random_prime(two);
	cout << "not primes on way:";
	cout << "gen q: " << q << endl;
	p = generate_random_prime(two);
	cout << "gen p: " << q << endl;
	ZZ n = p * q;
	cout << "gen n: " << n << endl;
	ZZ b = RandomBnd(n);
	cout << "gen b: " << b << endl;
	public_key[0] = n;
	public_key[1] = b;
	protected_key[0] = p;
	protected_key[1] = q;
	protected_key[2] = b;
}

ZZ Encrypt(ZZ m, ZZ C[2], ZZ pk[3])
{
	int l = NumBytes(pk[0]);
	ZZ two(2);
	ZZ n = pk[0];
	two = power(two, 64);
	ZZ two2(1);
	ZZ r = RandomBnd(two);
	if (!IsOdd(r))
	{
		if (r > 1)
		{
			r = r - 1;
		}
		else r++;
	}
	two2 = ZZ(255)*(power(ZZ(2), (8 * (l - 2))));
	ZZ x = r + m*two + two2;
	cout << "x:" << x << endl;
	cout << "r:" << r << endl;
	ZZ y = x*(x+pk[1]);
	C[0] = bit(((x+(pk[1]*InvMod(ZZ(2),n)))%pk[0]),0);
	C[1] = jakobi(x, pk[1], pk[0]);
	if (C[1] == ZZ(-1)) { C[1] = 0; }
	cout<<"C: " << C[0] << " " << C[1] << " ";
	return y;
}

ZZ Decrypt(ZZ y, ZZ C[2], ZZ pk[3])
{
	ZZ n = pk[0] * pk[1];
	ZZ y2 = y + ((pk[2] *InvMod(ZZ(2),n)) * (pk[2] *InvMod(ZZ(2),n)));
	ZZ x[4];
	fastroot(pk[0], pk[1], y2, x);
	ZZ xe[4];
	ZZ ja;
	ZZ xe2;
	for (int i = 0; i < 4; i++)
	{
		xe[i] = (x[i]-pk[2]*InvMod(ZZ(2),n))%n;
		//cout <<"x: "<< xe[i]<<endl;
		if ((bit(((xe[i] + (pk[2] *InvMod(ZZ(2),n))) % n), 0) == C[0]))
		{
			ja = ZZ(jakobi(xe[i], pk[2], n));
			if (ja == C[1])
			{
				xe2 = xe[i];
				//cout << "aa" << xe[i] << endl;
			}
			else 
			{
				if ((ja == ZZ(-1)) && (C[1] == 0))
				{
					xe2 = xe[i];
					//cout <<"aa"<< xe[i] <<endl;
				}
			}
		}
	}
	ZZ m = deformat(xe2, n);
	return m;
}

ZZ deformat(ZZ xe2, ZZ n)
{
	int l = NumBytes(n);
	xe2 = xe2 % n;
	ZZ r = xe2 & conv<ZZ>("18446744073709551615");
	//cout << "r:" << r << endl;
	ZZ two(2);
	two = power(two, 64);
	ZZ two2;
	//cout << "x: " << xe2 << endl;
	two2 = ZZ(255) * (power(ZZ(2), (8 * (l - 2))));
	ZZ m = ((xe2 - r - two2) / two);
	return m;
}

void fastroot(ZZ p, ZZ q, ZZ y, ZZ x[4])
{
	ZZ uv[2];
	ZZ n = p * q;
	ZZ u; ZZ v;
	Egcd(p, q, u, v, uv);
	ZZ s1 = PowGorner(y, ((p + 1) / 4), p);
	ZZ s2 = PowGorner(y, ((q + 1) / 4), q);
	//cout << uv[0] << " " << uv[1] << " "<<n;

	x[0] = (uv[0] * p * s2 + uv[1] * q * s1 + n*n) % n;
	x[1] = (uv[0] * p * s2 - uv[1] * q * s1 + n*n ) % n;
	x[2] = (-uv[0] * p * s2 + uv[1] * q * s1 + n*n ) % n;
	x[3] = (-uv[0] * p * s2 - uv[1] * q * s1 +n*n ) % n;
}

ZZ Sign(ZZ m, ZZ p, ZZ q)
{
	ZZ n = p * q;
	int l = NumBytes(n);
	ZZ two(2);
	two = power(two, 64);
	ZZ two2(1);
	ZZ r;
	ZZ x;
	while (true) {
		r = RandomBnd(two);
		if (!IsOdd(r))
		{
			if (r > 1)
			{
				r = r - 1;
			}
			else r++;
		}
		two2 = ZZ(255) * (power(ZZ(2), (8 * (l - 2))));
		x = r + m * two + two2;
		if ((jakobi(x, ZZ(0), q) == 1) && (jakobi(x, ZZ(0), p) == 1))
		{
			break;
		}
	}
	ZZ xi[4];
	fastroot(p, q, x, xi);

	ZZ s = xi[rand() % 4];
	cout << "s:" << s << endl;
	return(s);
}

ZZ Verify(ZZ m, ZZ s, ZZ n)
{
	ZZ x = s * s % n;
	ZZ m_ = deformat(x,n);
	if (m == m_)
	{
		cout << "Verification succeeded" << endl;

			}
	else {
		cout << "Verification failed" << endl;
	}
	return m_;
}

ZZ PowGorner(ZZ x, ZZ a, ZZ n)
{
	ZZ xa(1);
	for (int i = NumBits(a)-1; i >= 1; i--)
	{
		//cout << bit(a, i) << " ";
		if (bit(a, i) == 1)
		{
			xa = MulMod(xa,x,n);
		}
		xa = SqrMod(xa, n);
		//cout << xa<<" ";
	}
	if (bit(a, 0) == 1)
	{
		xa = MulMod(xa, x, n);
	}
	return xa;
}

ZZ zero_knowledge(string n)
{
	ZZ modulus = HexToDecimal(n);
	ZZ x;
	ZZ y;
	string sqr;
	ZZ tt;
	while (true) 
	{
		x = RandomBnd(modulus);
		y = x * x % modulus;
		cout << "y:" << DecimalToHex(y)<<endl;
		cin >> sqr;
		tt = HexToDecimal(sqr);
		if (tt != x)
			break;
	}
	ZZ u, v, uv[2];
	ZZ p = GCD((tt + x), modulus);
	cout << "p:" << DecimalToHex(p) << endl;
	ZZ q = modulus/p;
	cout << "q:" << DecimalToHex(q) << endl;
	cout << "m:" << DecimalToHex(p*q) << endl;
	return p;
}

ZZ HexToDecimal(string hex)
{
	ZZ d(0);
	for (int i = 0; i < hex.size(); i++)
	{
		switch (hex[hex.size()-i-1])
		{
		case'0':
		{
			break;
		}
		case '1':
		{
			d = d + ZZ(1) * (power(ZZ(16), i));
			break;
		}

		case '2':
		{
			d = d + ZZ(2) * (power(ZZ(16), i));
			break;
		}

		case '3':
		{
			d = d + ZZ(3) * (power(ZZ(16), i));
			break;
		}

		case '4':
		{
			d = d + ZZ(4) * (power(ZZ(16), i));
			break;
		}

		case '5':
		{
			d = d + ZZ(5) * (power(ZZ(16), i));
			break;
		}

		case '6':
		{
			d = d + ZZ(6) * (power(ZZ(16), i));
			break;
		}
		case '7':
		{
			d = d + ZZ(7) * (power(ZZ(16), i));
			break;
		}

		case '8':
		{
			d = d + ZZ(8) * (power(ZZ(16), i));
			break;
		}

		case '9':
		{
			d = d + ZZ(9) * (power(ZZ(16), i));
			break;
		}

		case 'A':
		{
			d = d + ZZ(10) * (power(ZZ(16), i));
			break;
		}
		case 'B':
		{
			d = d + ZZ(11) * (power(ZZ(16), i));
			break;
		}
		case 'C':
		{
			d = d + ZZ(12) * (power(ZZ(16), i));
			break;
		}
		case 'D':
		{
			d = d + ZZ(13) * (power(ZZ(16), i));
			break;
		}
		case 'E':
		{
			d = d + ZZ(14) * (power(ZZ(16), i));
			break;
		}
		case 'F':
		{
			d = d + ZZ(15) * (power(ZZ(16), i));
			break;
		}
		}
	}
	return d;
}

string DecimalToHex(ZZ hex)
{
	ZZ d = hex;
	int pain=0;
	ZZ pain2;
	char c;
	string h = "";
	while (d != 0)
	{
		pain2 = d % 16;
		conv(pain, pain2);
		d = d / 16;
		if (pain < 10)
		{
			c = (pain + '0');
		}
		else 
		{
			switch (pain)
			{
			case 10:
			{
				c = 'A';
				break;
			}
			case 11:
			{
				c = 'B';
				break;
			}
			case 12:
			{
				c = 'C';
				break;
			}
			case 13:
			{
				c = 'D';
				break;
			}
			case 14:
			{
				c = 'E';
				break;
			}
			case 15:
			{
				c = 'F';
				break;
			}
			}
		}
		h+=(c);
	}
	reverse(h.begin(), h.end());
	return h;
}

int jakobi(ZZ x, ZZ b, ZZ n)
{
	int ja(1);
	ZZ y = x + (b *InvMod(ZZ(2),n));
	y = y % n;
	ZZ temp2 = n;
	int j = 0;
	ZZ temp;
	ZZ temp3;
	while (temp2 > 1) {
		j = 0;
		//cout << temp2<<" "<< y << endl;
		while (bit(y, 0) == 0)
		{
			y = RightShift(y, 1); //розкладає на 2^s та d число p-1
			j++;
		}
		j = j % 2;
		if (j == 1)
		{
			temp = ((temp2 * temp2) - 1) / 8;
			if (temp % 2 != 0)
			{
				ja = ja*(-1);
			}
		}
		temp = (y - 1) * (temp2 - 1) / 4;
		temp3 = y;
		y = temp2 % y;
		temp2 = temp3;
		if (temp % 2 != 0)
		{
			ja = ja * (-1);
		}
	}
	return ja;
}

ZZ Egcd(ZZ a, ZZ b, ZZ& u, ZZ& v, ZZ uv[2])
{							//почему и н*Ц879368247
	if (a == ZZ(0))
	{
		u = ZZ(0); v = ZZ(1);
		return b;
	}
	ZZ u1, v1;
	ZZ d = Egcd(b % a, a, u1, v1, uv); //а, понял. Не нравится мне это
	u = v1 - (b / a) * u1; //все, понял, это завуалированный обратный ход.
	v = u1; //страшная штука
	uv[0] = u; uv[1] = v;
	//cout << "up + vq = " << u *a + v *b<<endl;
	return d;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
