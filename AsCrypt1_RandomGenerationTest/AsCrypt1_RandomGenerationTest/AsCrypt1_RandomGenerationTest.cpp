// AsCrypt1_RandomGenerationTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "generators.h"
#include "Hexcalculator.h"
int main()
{
	int XiData[256][12];
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			XiData[i][j] = 0;
		}
	}
	binaryNum a;
	a.num[0] = 1;
	a.num[16] = 1;
	int c = 119;
	binaryNum c1 = intTobN(c);	//для лемана

	int temp[89];  //для L20, L89, wolf
	int x_L20[20];
	int x_L89[89];
	int r_Wolf[32];
	Random_starter(x_L20, 20);
	Random_starter(x_L89, 89);
	Random_starter(r_Wolf, 32);

	int x_i[20];
	int y_i[20];
	int s_i[20];
	int z_i[20];
	Random_starter(x_i, 20);
	Random_starter(y_i, 20);
	Random_starter(s_i, 20);

	binaryNum x0 = intTobN((rand()% 2147483647)+1);
	binaryNum x1 = intTobN((rand() % 2147483647) + 1);
	
	string p = "CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3";
	string a_ = "5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356";
	string q = "675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1";
	bignum p1; p1 = cnum16(p, p1);
	bignum q1; q1 = cnum16(q, q1);
	bignum a1; a1 = cnum16(a_, a1);
	
	/*bignum k2; k2 = cnum16("2", k2);
	k2=multiply_errorfix(k2, k2, k2);
	cout16(k2);

	k2 = multiply_errorfix(k2, k2, k2);
	cout16(k2);*/
	bignum mu1 = mu(p1);
	bignum T; T = copy_randomise(T, p1);
	string p_2 ="D5BBB96D30086EC484EBA3D7F9CAEB07";
	string q_2 = "425D2B9BFDB25B9CF6C416CC6E37B59C1F";
	bignum p2; p2 = cnum16(p_2, p2);
	bignum q2; q2 = cnum16(q_2, q2);
	bignum n; n = p2 * q2;
	bignum mu2 = mu(n);
	bignum T1; T1 = copy_randomise(T1, p2);
	Librarian(r_Wolf, XiData);

	for (int i = 0; i < 268435456; i++)
	{
		baserand(XiData);
		x0 = LehmerLow(x0, a, c1, XiData);
		x1 = LehmerHigh(x1, a, c1, XiData);
		L20(x_L20, XiData, temp);
		L89(x_L89, XiData, temp);
		Wolfram(r_Wolf, XiData, temp);
		geffee(x_i, y_i, s_i, z_i, temp, XiData);
		//BBSbite(T1, n, mu2, XiData);
		//BMbit(T, p1, q1, a1, mu1, XiData);  //было трудно урегулировать утечку памяти
	}

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
