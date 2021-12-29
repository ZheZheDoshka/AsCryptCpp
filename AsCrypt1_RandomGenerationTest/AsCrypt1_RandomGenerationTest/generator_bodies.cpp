#include "generators.h";

void baserand(int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	int j = rand() % 256;
	XiData[j][0]++;
	XiData3[j][0][section]++;
	if (kk[2] == 1) 
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][0]++;
	}
	else 
	{ 
		kk[1] = j; 
	}
	kk[2] = (kk[2] + 1) % 2;
}

binaryNum Lehmer(binaryNum x0, binaryNum a, binaryNum c)
{
	binaryNum x1 = ((x0 * a) + c);
	return x1;
}

binaryNum LehmerLow(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	x0 = Lehmer(x0, a, c);
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		j += x0.num[i] * k;
		k = k * 2;
	}
	XiData[j][1]++;
	XiData3[j][1][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][1]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return x0;
}

binaryNum LehmerHigh(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	x0 = Lehmer(x0, a, c);
	int j = 0; int k = 1;
	for (int i = 24; i < 32; i++)
	{
		j += x0.num[i] * k;
		k = k * 2;
	}
	XiData[j][2]++;
	XiData3[j][2][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][2]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return x0;
}

void L20(int x[], int XiData[256][12], int temp[], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		x[i + 20] = (x[i + 17] + x[i + 15] + x[i + 11] + x[i])%2;
		j += x[i] * k;
		k = k * 2;
	}
	XiData[j][3]++;
	XiData3[j][3][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][3]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	for (int i = 0; i<20; i++)
	{
		temp[i] = x[i+8];
	}
	for (int i = 0; i < 20; i++)
	{
		x[i] = temp[i];
	}
}

void L89(int x[], int XiData[256][12], int temp[], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++)
	{
		x[89 + i] = (x[i] + x[i + 51])%2;
		j += x[i] * k;
		k = k * 2;
	}
	XiData[j][4]++;

	XiData3[j][4][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][4]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	for (int i = 0; i < 89; i++)
	{
		temp[i] = x[i + 8];
	}
	for (int i = 0; i < 89; i++)
	{
		x[i] = temp[i];
	}
}

void geffee(int x[], int y[], int s[], int z[], int temp[], int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section)
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
	XiData3[j][5][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][5]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
}

void Wolfram(int r[32], int XiData[256][12], int temp[], int*** XiDataN, int kk[3], int*** XiData3, int section)
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
	XiData3[q][6][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = q;
		XiDataN[kk[0]][kk[1]][6]++;
	}
	else
	{
		kk[1] = q;
	}
	kk[2] = (kk[2] + 1) % 2;
}

void Librarian(int x[], int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	ofstream file2("junk.txt");
	ifstream file("text2.txt");
	int r=0;
	int r_count=0;
	int n=0;
	for (char c; file.get(c); file2.put(c)) {
		n++;
		if (r_count == 5150722/12)
		{
			r_count = 0;
			r++;
		}
		XiData[int(c)][7]++;
		XiData3[int(c)][7][r]++;
		if (kk[2] == 1)
		{
			kk[0] = kk[1];
			kk[1] = int(c);
			XiDataN[kk[0]][kk[1]][7]++;
		}
		else
		{
			kk[1] = int(c);
		}
		kk[2] = (kk[2] + 1) % 2;
		r_count++;
	}

}


bignum BMbit(bignum T, bignum p, bignum q, bignum a, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3])
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
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][4]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return T;
}



bignum BMbite(bignum T, bignum p, bignum q, bignum a, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3])
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
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][4]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return T;
}

bignum BBSbit(bignum T, bignum n, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3])
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
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][4]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return T;
}

bignum BBSbite(bignum T, bignum n, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3])
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

ZZ BBSbite(ZZ T, ZZ n, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section )
{
	int j = 0; int k = 1;
	T = (T * T) % n;
	ZZ T1 = T % ZZ(256);
	j = conv<int>(T1);
	XiData[j][11]++;
	XiData3[j][11][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][9]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return T;
}

ZZ BBSbit(ZZ T, ZZ n, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section)
{
	int j = 0; int k = 1;
	for (int i = 0; i < 8; i++) {
		T = (T * T) % n;
		j = j + pow(2, i) * bit(T, 0);
	}
	XiData[j][10]++;
	XiData3[j][10][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][10]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return T;
}

ZZ BMbite(ZZ T, ZZ p, ZZ a, ZZ q, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section )
{
	int x = 0;
	int j = 0; int k = 1;
	ZZ T1;
	T1 = PowerMod(a, T, p);
	T = T1;
	j = conv<int>((T1 * ZZ(256)) / (p - 1));
	XiData[j][9]++;

	XiData3[j][9][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][9]++;

	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
	return T;
}

ZZ BMbit(ZZ T, ZZ n, ZZ a, ZZ q, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section )
{
	int x = 0;
	int j = 0; int k = 1;
	ZZ T1;
	for (int i = 0; i < 8; i++)
	{
		T1 = PowerMod(a, T, n);
		if (T1 > q)
		{
			x = 1;
		}
		else
		{
			x = 0;
		}
		j += x * k;
		k = k * 2;
		T = T1;
	}
	XiData[j][8]++;
	XiData3[j][8][section]++;
	if (kk[2] == 1)
	{
		kk[0] = kk[1];
		kk[1] = j;
		XiDataN[kk[0]][kk[1]][8]++;
	}
	else
	{
		kk[1] = j;
	}
	kk[2] = (kk[2] + 1) % 2;
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

void Xi2_R(int XiData[256][12], double Xi2[12], double m)
{
	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 256; i++)
		{
			Xi2[j] += (double(XiData[i][j] - m) * (XiData[i][j] - m) / m);
		}
	}
}

void Xi2_N(int*** XiDataN, double Xi2[12], int m)
{
	int vj = 0;
	int aj = 0;
	for (int k = 0; k < 12; k++) {
		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < 256; j++)
			{
				vj = 0; aj = 0;
				for (int j2 = 0; j2 < 256; j2++)
				{
					vj = vj + XiDataN[i][j2][k];
					aj = aj + XiDataN[j2][j][k];
				}


				if ((vj != 0) && (aj != 0))
				{
					Xi2[k] += (double(XiDataN[i][j][k]) * double(XiDataN[i][j][k]) / ((vj)* double(aj)));
				}
			}
		}
		Xi2[k] = (Xi2[k] - 1) * m;
	}
}

void Xi2_O(int*** XiDataN, double Xi2[12], int m, int r)
{
	int vj = 0;
	int aj = 0;
	for (int k = 0; k < 12; k++) 
	{
		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < r; j++)
			{
				vj = 0; aj = m;
				for (int j2 = 0; j2 < r; j2++)
				{
					vj = vj + XiDataN[i][k][j2];
				}
				if ((vj != 0) && (aj != 0)) 
				{
					Xi2[k] += (double(XiDataN[i][k][j]) * (XiDataN[i][k][j]) / ((double(vj) * aj)));
				}
			}
		}
		Xi2[k] = (Xi2[k] - 1) * m*r;
	}
}