#include "ABheader.h";

void GenerateKeyPair()
{
	ZZ n0, n1;
	ZZ p, q, p1, q1;
	p = 0;
	q = 0;
	q1 = 0;

	for (int i = 0; i < 32; i++)
	{
		p = p + (rand()%256)*256^i;
		q = q + (rand() % 256) * 256 ^ i;
		p1 = p1 + (rand() % 256) * 256 ^ i;
		q1 = q1 + (rand() % 256) * 256 ^ i;
	}
};
void Encrypt();
void Decrypt();
void Sign();
void Verify();
void SendKey();
void ReceiveKey();

void TestPrime(ZZ p)
{
	p = p-1;

}