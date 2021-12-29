﻿// AsCrypt2_RSA.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
	int primes[201] = { -1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
		31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,
		97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
		151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
		211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269,
		271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337,
		347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
		409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
		467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
		557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
		617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677,
		683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757,
		761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
		839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
		919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
		997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051,
		1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117,
		1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201,
		1213, 1217, 2083 };
	cout << "Vvedit n" << endl;
	long temp = 0;
	long temp2 = 0;
	long rrr = 0;
	ZZ n;
	string q;
	ZZ p[255];
	ZZ a;
	ZZ b;
	int pr = 1;
	ZZ l[255];
	for (int i = 0; i < 255; i++)
	{
		l[i] = ZZ(0);
	}
	ZZ r[255][255];
	ZZ y[255];

	for (int i = 0; i < 255; i++)
	{
		y[i] = ZZ(0);
	}
	ZZ x[255];
	int pi(0), pj(0);
	ZZ z;
	cin >> n;
	ZZ n2 = n-1;
	cout << "Razlozhenie n (chislo, colichestwo)" << endl;
	while (n2>1)
	{
		if (n2 % primes[pr] == 0)
		{
			n2 = n2 / primes[pr];
			p[pi] = primes[pr];
			l[pi]++;
		}
		else
		{
			pr++;
			if (l[pi] > 0)
				pi++;
		}
	}
	ZZ nl;
	//for (int i = 0; i < 255; i++)
//	{
	//	cout<<p[i]<<" ";
	//}
	cout << "Vvedit a, b" << endl;
	cin >> a;
	cin >> b;
	for (int i = 0; i <= pi; i++)
	{
		for (int j = 0; j < p[i]; j++)
		{
			r[i][j] = PowerMod(a, ((n * j) / p[i]), n);
		}
		cout << endl;
	}
	for (int i = 0; i <= pi; i++)
	{
		if (l[i] == 1)
		{
			//cout << p[i]<<" ";
			//cout << a << " " << (n - 1);
				z = (PowerMod(b, (n - 1)/p[i], n));
	
			for (int j = 0; j < p[i]; j++)
			{
				if (r[i][j] == z)
				{
					y[i] = j;
				}
			}
		}
		else
		{
			nl = b;
			for (int k = 0; k < l[i]; k++)
			{
				
				z = PowerMod(nl, (n - 1) / power(p[i],k+1), n);
				for (int j = 0; j < p[i]; j++)
				{
					if (r[i][j] == z)
					{
						x[k] = j;
					}
				}
				cout << nl << " " << (n - 1) / power(p[i], k + 1) << " " << x[k] << endl;
				if (x[k] > 0) {
					conv(temp, x[k]);
					conv(temp2, p[i]);
					rrr = temp * (pow(temp2, k));
					//cout << "rr = " << rrr << endl;
					nl = (nl * InvMod(power(a, rrr)%n, n))%n;
				}
				if (k >= 2) {
					y[i] = y[i] + x[k] * power(p[i], k);
				}
				else { if (k == 1) {y[i] = y[i] + x[k]*p[i];
				} else { y[i] = y[i] + x[k]; } }
			}
			conv(temp, l[i]);
			y[i] = y[i]% power(p[i], temp);
		}
	}
	ZZ M = n-1;
	ZZ xt(0);
	ZZ ai(0);
	ZZ mi(1);

	for (int i = 0; i <= pi; i++)
	{
		cout << y[i] << " ";
	}
	cout << endl;
	for (int i = 0; i <= pi; i++)
	{
		ai = PowerMod(p[i], l[i], n);
		mi = (M / ai);
		xt = xt + y[i] * mi * InvMod(mi%ai, ai);
	}
	cout << xt%(n-1);
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