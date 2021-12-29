#pragma once
#include <iostream>
#include <conio.h>
#include "BinaryHexCalculator.h"
#include <fstream>
#include "Hexcalculator.h"
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

void baserand(int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);
binaryNum Lehmer(binaryNum x0, binaryNum a, binaryNum c);
binaryNum LehmerLow(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);
binaryNum LehmerHigh(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);
void L20(int x[], int XiData[256][12], int temp[], int*** XiDataN, int kk[3], int*** XiData3, int section);
void L89(int x[], int XiData[256][12], int temp[], int*** XiDataN, int kk[3], int*** XiData3, int section);
void Wolfram(int r[32], int XiData[256][12], int temp[], int*** XiDataN, int kk[3], int*** XiData3, int section);
void geffee(int x[], int y[], int s[], int z[], int temp[], int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);
void Librarian(int x[], int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);

bignum BMbit(bignum T, bignum p, bignum q, bignum a, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3]);
bignum BBSbite(bignum T, bignum n, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3]);
bignum BBSbit(bignum T, bignum n, bignum mu, int XiData[256][12], int*** XiDataN, int kk[3]);


ZZ BBSbite(ZZ T, ZZ n, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);
ZZ BBSbit(ZZ T, ZZ n, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);

ZZ BMbite(ZZ T, ZZ p, ZZ a, ZZ q, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);
ZZ BMbit(ZZ T, ZZ n, ZZ a, ZZ q, int XiData[256][12], int*** XiDataN, int kk[3], int*** XiData3, int section);



void Xi2_R(int XiData[256][12], double Xi2[12], double m);
void Xi2_N(int*** XiDataN, double Xi2[12], int m);
void Xi2_O(int*** XiDataN, double Xi2[12], int m, int r);

void Random_starter(int x[], int n);
bignum copy_randomise(bignum T, bignum p);

