#pragma once

struct binaryNum
{
	int num[64];
	binaryNum()
	{
		for (int i = 0; i < 64; i++)
		{
			num[i] = 0;
		}
	}
};

binaryNum operator+ (binaryNum num1, binaryNum num2);
binaryNum operator* (binaryNum num1, int num2);
binaryNum operator* (binaryNum num1, binaryNum num2);

binaryNum intTobN(int c);