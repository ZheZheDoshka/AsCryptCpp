#include "generators.h";

void baserand(int XiData[256][12])
{
	XiData[rand() % 256][0]++;
}

binaryNum Lehmer(binaryNum x0, binaryNum a, binaryNum c)
{
	binaryNum x1 = ((x0 * a) + c);
	return x1;
}

binaryNum LehmerLow(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12])
{
	x0 = Lehmer(x0, a, c);
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		j += x0.num[i] * k;
		k = k * 2;
	}
	XiData[j][1]++;
	return x0;
}

binaryNum LehmerHigh(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12])
{
	x0 = Lehmer(x0, a, c);
	int j = 0; int k = 1;
	for (int i = 24; i < 32; i++)
	{
		j += x0.num[i] * k;
		k = k * 2;
	}
	XiData[j][2]++;
	return x0;
}

void L20(int x[], int XiData[256][12], int temp[])
{
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		x[i + 20] = (x[i + 17] + x[i + 15] + x[i + 11] + x[i])%2;
		j += x[i] * k;
		k = k * 2;
	}
	XiData[j][3]++;
	for (int i = 0; i<20; i++)
	{
		temp[i] = x[i+8];
	}
	for (int i = 0; i < 20; i++)
	{
		x[i] = temp[i];
	}
}

void L89(int x[], int XiData[256][12], int temp[])
{
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		x[89 + i] = (x[i] + x[i + 51])%2;
		j += x[i] * k;
		k = k * 2;
	}
	XiData[j][4]++;
	for (int i = 0; i < 89; i++)
	{
		temp[i] = x[i + 8];
	}
	for (int i = 0; i < 89; i++)
	{
		x[i] = temp[i];
	}
}

void geffee(int x[], int y[], int s[], int z[], int temp[], int XiData[256][12])
{
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		x[i + 11] = (x[i] ^ x[i + 2]);
		y[i + 9] = (y[i] ^ y[i + 1] ^ y[i + 3] ^ y[i + 4]);
		s[i + 10] = (s[i] ^ s[i + 3]);
	}
	for (int i = 0; i < 8; i++)
	{
		z[i] = (s[i] * x[i]) ^ ((1 ^ s[i]) * y[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		z[i] = (s[i] * x[i]) ^ ((1 ^ s[i]) * y[i]);
	}
	for (int i = 0; i < 12; i++)
	{
		temp[i] = x[i+8];
	}
	for (int i = 0; i < 20; i++)
	{
		x[i] = temp[i];
	}
	for (int i = 0; i < 12; i++)
	{
		temp[i] = y[i + 8];
	}
	for (int i = 0; i < 20; i++)
	{
		y[i] = temp[i];
	}
	for (int i = 0; i < 12; i++)
	{
		temp[i] = s[i + 8];
	}
	for (int i = 0; i < 20; i++)
	{
		s[i] = temp[i];
	}
	for (int i = 0; i < 8; i++)
	{
		j += z[i] * k;
		k = k * 2;
	}
	XiData[j][5]++;
}

void Wolfram(int r[32], int XiData[256][12], int temp[])
{
	int x = 0;
	int q = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			temp[j] = r[j];
		}
		for (int j = 0; j < 32; j++)
		{
			r[j] = (temp[(j + 31) % 32] + (temp[j] || temp[(j + 1) % 32])) % 2;
		}
		x = r[0];
		q += x * k;
		k = k * 2;
	}
	XiData[q][6]++;
}

void Librarian(int x[], int XiData[256][12])
{
	ofstream file2("junk.txt");
	ifstream file("text2.txt");
	for (char c; file.get(c); file2.put(c)) {
		XiData[int(c)][7]++;
	}
}


bignum BMbit(bignum T, bignum p, bignum q, bignum a, bignum mu, int XiData[256][12])
{
	int x = 0;
	int j = 0; int k = 1;
	bignum T1;
	for (int i = 0; i < 8; i++)
	{
		T1 = mpowfix(a, T, p, mu);
		if (bigger(T, q) == -1)
		{
			x = 1;
		}
		else
		{
			x = 0;
		}
		j += x * k;
		k = k * 2;
		T = copy(T, T1);
		delete[] T1.num;
	}
	XiData[j][8]++;
	return T;
}

bignum BMbite(bignum T, bignum p, bignum q, bignum a, bignum mu, int XiData[256][12])
{
	int x = 0;
	int j = 0; int k = 1;
	bignum T1;
	T1 = mpowfix(a, T, p, mu);
	if (bigger(T, q) == -1)
	{
			x = 1;
	}
	else
	{
			x = 0;
	}
	j += x * k;
	k = k * 2;
	T = copy(T, T1);
	delete[] T1.num;
	XiData[j][9]++;
	return T;
}

bignum BBSbit(bignum T, bignum n, bignum mu, int XiData[256][12])
{
	int j = 0;
	int k = 1;
	bignum T1;
	for (int i = 0; i < 8; i++)
	{
		T=multiply_errorfix(T, T, T);
		T1 = modnfix(T, n, mu);
		j = j + k * T1.num[0] % 2; k = k * 2;
		T = copy(T, T1);
		delete[] T1.num;
	}
	XiData[j][10]++;
	return T;
}

bignum BBSbite(bignum T, bignum n, bignum mu, int XiData[256][12])
{
	int j = 0; int k = 1;
	bignum T1;
	T = multiply_errorfix(T, T, T);
    T1 = modnfix(T, n, mu);
	j = j + k*T1.num[0]%2;
	T = copy(T, T1);
	delete[] T1.num;
	XiData[j][11]++;
	return T;
}

void Random_starter(int x[], int n)
{
	for (int i = 0; i < n; i++)
	{
		x[i] = rand() % 2;
	}
}

bignum copy_randomise(bignum T, bignum p)
{
	T.length = p.length;
	T.num = new int[T.length];
	for (int i = 0; i < T.length-1; i++)
	{
		T.num[i] = rand() % 16;
	}
	T.num[T.length - 1] = rand() % (p.num[T.length - 1] - 1);
	return T;
}