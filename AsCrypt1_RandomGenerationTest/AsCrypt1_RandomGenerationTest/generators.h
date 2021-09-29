#pragma once
#include <iostream>
#include <conio.h>
#include "BinaryHexCalculator.h"
#include <fstream>
#include "Hexcalculator.h"

using namespace std;

void baserand(int XiData[256][12]);
binaryNum Lehmer(binaryNum x0, binaryNum a, binaryNum c);
binaryNum LehmerLow(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12]);
binaryNum LehmerHigh(binaryNum x0, binaryNum a, binaryNum c, int XiData[256][12]);
void L20(int x[], int XiData[256][12], int temp[]);
void L89(int x[], int XiData[256][12], int temp[]);
void Wolfram(int r[32], int XiData[256][12], int temp[]);
void geffee(int x[], int y[], int s[], int z[], int temp[], int XiData[256][12]);
void Librarian(int x[], int XiData[256][12]);

bignum BMbit(bignum T, bignum p, bignum q, bignum a, bignum mu, int XiData[256][12]);
bignum BBSbite(bignum T, bignum n, bignum mu, int XiData[256][12]);
bignum BBSbit(bignum T, bignum n, bignum mu, int XiData[256][12]);
void Random_starter(int x[], int n);
bignum copy_randomise(bignum T, bignum p);

