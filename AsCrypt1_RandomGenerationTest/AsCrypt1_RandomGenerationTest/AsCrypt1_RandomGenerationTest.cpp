// AsCrypt1_RandomGenerationTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "generators.h"
#include "Hexcalculator.h"
#include <string>

int main()
{
	int r = 12;
	int XiData[256][12];
	double alpha[3] = { 0.01, 0.05, 0.1 };
	double quantil[3] = { 2.327, 1.645 , 1.285 };

	double Xi1[3];
	double Xi2[3];
	double Xi3[3];
	for (int i = 0; i < 3; i++)
	{
		Xi1[i] = quantil[i] * sqrt(255 * 2) + 255;
		Xi2[i] = quantil[i] * sqrt(255*255*2) + 255*255;
		Xi3[i] = quantil[i] * sqrt(255 * 2 * (r-1)) + 255*(r-1);
	}

	double Xi2_1[12];
	double Xi2_2[12];
	double Xi2_3[12];

	for (int i = 0; i < 12; i++)
	{
		Xi2_1[i] = 0;
		Xi2_2[i] = 0;
		Xi2_3[i] = 0;
	}

	int*** XiDataN = new int**[256];
	for (int i = 0; i < 256; i++) 
	{
		XiDataN[i] = new int*[256];
		for (int j = 0; j < 256; j++)
		{
			XiDataN[i][j] = new int [12];
		}

	}

	int*** XiData3 = new int** [256];
	for (int i = 0; i < 256; i++)
	{
		XiData3[i] = new int* [12];
			for (int k = 0; k < 12; k++)
			{
				XiData3[i][k] = new int [r+1];
			}
	}

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			XiData[i][j] = 0;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		for (int k = 0; k < 256; k++) 
		{
			for (int j = 0; j < 12; j++)
			{
				XiDataN[i][k][j] = 0;
			}
		}
	}

	for (int i = 0; i < 256; i++)
	{
		for (int k = 0; k < r; k++)
		{
			for (int j = 0; j < 12; j++)
			{
				XiData3[i][j][k] = 0;
			}
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
	int k1[3] = { 0,0,0 }; //Для теста знаков
	int k2[3] = { 0,0,0 };
	int k3[3] = { 0,0,0 };
	int k4[3] = { 0,0,0 };
	int k5[3] = { 0,0,0 };
	int k6[3] = { 0,0,0 };
	int k7[3] = { 0,0,0 };
	int k8[3] = { 0,0,0 };
	int k9[3] = { 0,0,0 };
	int k10[3] = { 0,0,0 };
	int k11[3] = { 0,0,0 };
	int k12[3] = { 0,0,0 };
	

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

	ZZ BSSn = conv<ZZ>("284100283511244958272321698211826428679") * conv<ZZ>("22582480853028265529707582510375286184991");
	ZZ TBite = RandomBnd(BSSn);
	double m = 1048576 / 256; //4194304
	int m2 = 1048576 / 2;
	int m3 = 1048576 / r;

	Librarian(r_Wolf, XiData, XiDataN, k8, XiData3, m3);
	int r_count = 0;
	int r2 = 0;
	/*for (int i = 0; i < 1048576; i++)
	{
		if (r_count == m3) 
		{
			r_count = 0;
			r2++;
		}
		baserand(XiData, XiDataN,k1, XiData3, r2);
		x0 = LehmerLow(x0, a, c1, XiData, XiDataN,k2, XiData3, r2);
		x1 = LehmerHigh(x1, a, c1, XiData, XiDataN,k3, XiData3, r2);
		L20(x_L20, XiData, temp, XiDataN,k4, XiData3, r2);
		L89(x_L89, XiData, temp, XiDataN, k5, XiData3, r2);
		Wolfram(r_Wolf, XiData, temp, XiDataN, k7, XiData3, r2);
		geffee(x_i, y_i, s_i, z_i, temp, XiData, XiDataN, k6, XiData3, r2);
		//BMbit(T, p1, q1, a1, mu1, XiData);  //было трудно урегулировать утечку памяти
		r_count++;
	}*/
	for (int i = 0; i < 200000; i++)
	{
		TBite = BBSbite(TBite, BSSn, XiData, XiDataN, k12);
	}
	Xi2_R(XiData, Xi2_1, m);
	Xi2_N(XiDataN, Xi2_2, m2);
	Xi2_O(XiData3, Xi2_3, m3, r);

	string stroka = "; ";
	string stroka2 = "; ";
	ofstream file4;
	file4.open("table.csv");
	file4 << "alpha: ; a1; a2; a3; \n";
	for (int i = 0; i < 3; i++)
	{
		stroka2 = stroka2 + to_string(alpha[i]) + ";";
	}
	file4 << stroka2 + "\n";
	for (int i = 0; i < 3; i++)
	{
		stroka = stroka + to_string(Xi1[i])+";";
	}
	file4 << "E: ; X^2_1-a1; X^2_1-a2; X^2_1-a3; \n";
	file4 << stroka+ "\n";
	stroka = "; ";
	stroka2 = "; ";	
	for (int i = 0; i < 3; i++)
	{
		stroka = stroka + to_string(Xi2[i]) + ";";
	}
	file4 << "I: ; X^2_1-a1; X^2_1-a2; X^2_1-a3; \n";

	file4 << stroka +"\n";
	stroka = "; ";
	for (int i = 0; i < 3; i++)
	{
		stroka = stroka + to_string(Xi3[i]) + ";";
	}
	file4 << "U: ; X^2_1-a1; X^2_1-a2; X^2_1-a3; \n";
	file4 << stroka+ "\n";
	stroka = "; ";

	for (int i = 0; i < 3; i++)
	{
		stroka2 = "a = :" + to_string(alpha[i]) + "; equal; independance; uniform; \n";
		file4 << stroka2;
		for (int j = 7; j < 8; j++)
		{
			stroka = to_string(j) +"; ";
			cout << "alpha: " << alpha[i] << ", generator = " << j << ", t = " << Xi2_1[j]<<" ";
			if (Xi1[i]>Xi2_1[j]) 
			{
				cout << "t<Xi^2, generator passsed equal signs test" << endl;
				stroka += "+;";
			}
			else
			{
				cout << "t>Xi^2, generator have not passed equal signs test" << endl;
				stroka += "-;";
			}
			cout<<" t = " << Xi2_2[j] << ", ";
			if (Xi2[i] > Xi2_2[j])
			{
				cout << "t<Xi^2, generator passsed independant signs test" << endl;
				stroka += "+;";
			}
			else
			{
				cout << "t>Xi^2, generator have not passed independant signs test" << endl;
				stroka += "-;";
			}			
			cout << " t = " << Xi2_3[j] << ", ";
			if (Xi3[i] > Xi2_3[j])
			{
				cout << "t<Xi^2, generator passsed uniformity test" << endl;
				stroka += "+;";
			}
			else
			{
				cout << "t>Xi^2, generator have not uniformity test" << endl;
				stroka += "-;";
			}
			stroka += "\n";
			file4 << stroka;
		}
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
