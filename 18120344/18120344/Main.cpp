#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>

#include "bitsManipulation.h"
#include "Convert.h"
#include "Modulo.h"
#include "generateBigNumber.h"

using namespace std;




// Hàm tách chuỗi
vector<string> Parse(string line, string seperator)
{
	vector<string> tokens;

	int startPos = 0;
	size_t foundPos = line.find(seperator, startPos);

	while (foundPos != string::npos)
	{
		int count = foundPos - startPos;
		string token = line.substr(startPos, count);
		tokens.push_back(token);

		startPos = foundPos + seperator.length();

		foundPos = line.find(seperator, startPos);
	}

	int count = line.length() - startPos;
	string token = line.substr(startPos, count);
	tokens.push_back(token);

	return tokens;
}

// Hàm thực thi
void ExecuteModule()
{
	clock_t start, end;
	double cpu_time_used;
	double avg = double(0);

	vector<string> arrMod = { "GCD","AddMod","MulMod","PowMod" };

	string x, y, m;
	string seperator = " ";
	vector<string> arrBit = { "64","128","256","512","1024" };

	
	for (int i = 0; i < arrBit.size(); i++)
	{

		string fname_testcase = "testCase_Binary_" + arrBit[i] + "bits.txt";
		string line;

		fstream ftestCase, fMod, fTime;
		ftestCase.open(fname_testcase, ios::in);
		if (ftestCase.fail())
		{
			cout << "Load file input fail !!!" << endl;
			return;
		}

		while (getline(ftestCase, line))
		{
			vector<string> tokens = Parse(line, seperator);
			int bits;
			if (i == 0)
			{
				bits = 64;
			}
			else if (i == 1)
			{
				bits = 128;
			}
			else if (i == 2)
			{
				bits = 256;
			}
			else if (i == 3)
			{
				bits = 512;
			}
			else if (i == 4)
			{
				bits = 1024;
			}
			//x = Convert::Instance()->convertDecToBin(tokens[0], bits);
			//y = Convert::Instance()->convertDecToBin(tokens[1], bits);
			//m = Convert::Instance()->convertDecToBin(tokens[2], bits);
			
			x = tokens[0];
			y = tokens[1];
			m = tokens[2];

			for (int j = 0; j < arrMod.size(); j++)
			{
				
				fMod.open("result_" + arrMod[j] + "_" + arrBit[i] + "bits.txt", ios::out | ios::app);
				fTime.open("time_" + arrMod[j] + "_" + arrBit[i] + "bits.txt", ios::out | ios::app);

				if (fMod.fail() || fTime.fail())
				{
					cout << "Load file output fail !!!" << endl;
					return;
				}

				string temp;
				switch (j)
				{
				case 0:
					start = clock();
					temp = Modulo::Instance()->GCD(x, y);
					end = clock();
					break;
				case 1:
					start = clock();
					temp = Modulo::Instance()->AddMod(x, y,m);
					end = clock();
					break;
				case 2:
					start = clock();
					temp = Modulo::Instance()->MulMod(x, y,m);
					end = clock();
					break;
				case 3:
					start = clock();
					temp = Modulo::Instance()->PowerMod(x, y, m);
					end = clock();
					break;
				default:
					break;
				}
				
				cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
				avg += cpu_time_used;
				fMod << temp << endl;
				fTime << cpu_time_used << endl;
				
			}
			
			fMod.close();
			fTime.close();	
		}
		cout <<"Average : "<<avg / double(100) << endl;
		ftestCase.close();
	}
}

int main()
{	
	//ExecuteModule();
	//generateTestCase();
	
}