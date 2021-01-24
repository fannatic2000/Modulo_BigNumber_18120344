#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <fstream>
#include <vector>
#include "Convert.h"
using namespace std;

#define SO_LUONG 100

string generate(int nbit);

//Des: Tạo file chứa n bộ (x,y,m) số nguyên lớn (hệ thập phân) nbit
void generateBigInt(string fname, int n, int nbit);


void generateTestCase();

