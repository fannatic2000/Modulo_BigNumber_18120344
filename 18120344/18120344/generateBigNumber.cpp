#include "generateBigNumber.h"

string units = "01";

// tạo số nguyên lớn nbit dưới dạng nhị phân
string generate(int nbit)
{
	string bigNum;
	for (int i = 1; i < nbit; i++)
	{
		int unit = rand() % (1 + 1);
		bigNum += units[unit];
	}
	bigNum.insert(bigNum.begin(), '0');
	cout << bigNum << endl;
	return bigNum;
}


//Des: Tạo file chứa n bộ (x,y,m) số nguyên lớn (hệ thập phân) nbit
//Input: fname: tên file xuất ; n: số lượng, nbit: số lượng bit
//Output: file filename.txt chứa các bộ số nguyên lớn (hệ thập phân)
void generateBigInt(string fname, int n, int nbit)
{
	fstream f, fb;
	f.open(fname,ios::out);

	if (f.fail())
	{
		cout << "Open file testCase fail !!!" << endl;
		return;
	}

	string x, y, m;
	for (int i = 0; i < n; i++)
	{
		//x = Convert::Instance()->convertBinToDec(generate(nbit));
		x = generate(nbit);
		//y = Convert::Instance()->convertBinToDec(generate(nbit));
		y = generate(nbit);
		//m = Convert::Instance()->convertBinToDec(generate(nbit));
		m = generate(nbit);
		f << x << " " << y << " " << m << endl;
	}

	f.close();
}

void generateTestCase()
{
	vector<string> arrBit = { "64","128","256","512","1024" };
	for(int i = 0; i<arrBit.size(); i++)
	{
		int bits;
		switch (i)
		{
		case 0:
			bits = 64;
			break;
		case 1: 
			bits = 128;
			break;
		case 2:
			bits = 256;
			break;
		case 3:
			bits = 512;
			break;
		case 4:
			bits = 1024;
			break;
		default:
			break;
		}

		cout << "testCase_Binary_" + arrBit[i] + "bits.txt" << endl;
		generateBigInt("testCase_Binary_" + arrBit[i] + "bits.txt", SO_LUONG, bits);
	}
}