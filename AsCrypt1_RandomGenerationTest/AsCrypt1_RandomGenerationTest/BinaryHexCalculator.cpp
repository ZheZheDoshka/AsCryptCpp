#include "BinaryHexCalculator.h";

binaryNum operator+ (binaryNum num1, binaryNum num2) 
{
	binaryNum num;
	for (int i = 0; i < 64; i++) 
	{
		num.num[i] = num1.num[i];
	}
	for (int i = 0; i < 64; i++) 
	{
		num.num[i] = num.num[i] + num2.num[i];
	}
	for (int i = 0; i < 32; i++) 
	{
		if (num.num[i] >= 2) 
		{
			num.num[i] = num.num[i] - 2; num.num[i + 1]++;
		}
	}
	num.num[32] = 0;
	return num;
}


binaryNum operator* (binaryNum num1, int num2) 
{
	binaryNum num;
	for (int i = 0; i < 64; i++)
	{
		num.num[i] = num1.num[i];
	}
	for (int i = 0; i < 64; i++) 
	{
		num.num[i] = num.num[i] * num2;
	}
	for (int i = 0; i < 63; i++) 
	{
		while (num.num[i] >= 2)
		{
			num.num[i] = -2;
			num.num[i + 1]++;
		}
	}
	for (int i = 32; i < 64; i++) 
	{
		num.num[i] = 0;
	}
	return num;
}

binaryNum operator* (binaryNum num1, binaryNum num2)
{
	binaryNum temp;
	binaryNum num;
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			temp.num[j] = 0;
		}
		for (int j = 0; j < 64-i; j++)
		{
			temp.num[j + i] = num1.num[j];
		}
		num = num + (temp * num2.num[i]);
	}
	return num;
}

binaryNum intTobN(int c)
{
	binaryNum bN;
	int i = 0;
	while (c != 0)
	{
		bN.num[i] = c % 2;
		c = c / 2;
		i++;
	}
	return bN;
}