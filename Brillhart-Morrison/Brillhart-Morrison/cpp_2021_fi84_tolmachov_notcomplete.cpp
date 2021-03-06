// Brillhart-Morrison.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;
int gcd(int a, int b, int& u, int& v);

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
		1213, 1217, 1223 };
	int n;
	int u; int v;
	int vi[201][25];
	for (int i = 0; i < 201; i++)
	{
		for (int j = 0; j < 25; j++)
			vi[i][j] = 0;
	}
	int b[25];
	int b_2[25];
	int k = 1;
	cin >> n;
	double dec = sqrt(n);
	double alpha = dec;
	int a = alpha;
	int u = 0;
	int v = 1;
	int c = 1;
	int x = 0;
	int y = 0;
	int p;
	int q;
	b[0] = a;
	u = u + a * v;
	b_2[0] = (b[0] * b[0]) % n;
	if (b_2[0] > dec) { b_2[0] = b_2[0] - n; }
	if (b_2[0] < 0) { b_2[0] = b_2[0] * -1; vi[0][0] = 1; }
	while (b_2[0] != 1)
	{
		if (b_2[0] % primes[c] == 0) { vi[c][0]++; b_2[0] = b_2[0] / primes[c]; c--; }
		c++;
	}
	cout << "iter = 0" << endl;
	cout << "b = " << b[0] << ", a =" << a << ", u = " << u << ", v = " << v << endl;
	v = (n - u * u) / v;
	alpha = (dec + u) / v;
	a = alpha;
	u = a * v - u;
	b[1] = 1 + b[0] * a;
	b_2[1] = (b[1] * b[1]) % n;
	c = 1;
	if (b_2[1] > dec) { b_2[1] = b_2[1] - n; }
	if (b_2[1] < 0) { b_2[1] = b_2[1] * -1; vi[0][1] = 1; }
	while (b_2[1] != 1)
	{
		if (b_2[1] % primes[c] == 0) { vi[c][1]++; b_2[1] = b_2[1] / primes[c]; c--; }
		c++;
	}
	while (true)
	{
		cout << "iter = "<<k << endl;
		cout << "b = " << b[k] << ", a =" << a << ", u = " << u << ", v = " << v << endl;
		k++;
		c = 1;
		v = (n - u * u) / v;
		alpha = (dec + u) / v;
		a = alpha;
		u = a * v - u;
		b[k] = b[k-2] + b[k-1] * a;
		b_2[k] = (b[k] * b[k]) % n;
		if (b_2[k] > dec) { b_2[k] = b_2[k] - n; }
		if (b_2[k] < 0) { b_2[k] = b_2[k] * -1; vi[0][k] = 1; }
		while (b_2[1] != 1)
		{
			if (b_2[k] % primes[c] == 0) { vi[c][1]++; b_2[k] = b_2[k] / primes[c]; c--; }
			c++;
		}
		// Дописать решение СЛУ, нахождение Х и У, сделать так что бы находилась факторной базы размер
		//
		if (x != y)
		{
			break;
		}
	}
	int n1, n2;

	n2 = gcd((x + y)%n, n, u, v);
	n1 = gcd((x - y + n) %n, n, u, v);
	cout << n1 << "=n1, n2= " << n2;
}

int gcd(int a, int b, int& u, int& v)
{							
	if (a == 0)
	{
		u = 0; v = 1;
		return b;
	}
	int u1, v1;
	int d = gcd(b % a, a, u1, v1); 
	u = v1 - (b / a) * u1;
	v = u1; 
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
