#pragma once
#include <iostream>
#include <string>

using namespace std;

class Convert
{
public:
	// Chuyển thành dãy nhị phân thành bù 2 ( Số đối )
	void convertToBu2(string& bnum);

	//Chuyển đổi một số nguyên hệ 10 sang chuỗi nhị nhân
	string convertDecToBin(string bnum, unsigned int nbit);

	//Chuyển chuổi nhị phân sang thập phân
	string convertBinToDec(string bnum);

private:
	// Cộng 2 chuỗi nhị phân
	string add2nBinary(string num1, string num2);

	//Chia số nguyên lớn dạng chuỗi cho 2
	string devideFor2(string num);

	//Nhân số một số nguyên string với 1 số nguyên int
	string mulStringwithInt(string num1, int num2);

	//Nhân 2 số nguyên dạng chuỗi (hệ Dec)
	string mul2dString(string num1, string num2);

	//Lũy thừa một số nguyên với số mũ
	string pow(int factor, int exp);

	
private:
	Convert()
	{
	}

public:
	Convert(const Convert&) = delete;
	void operator=(const Convert&) = delete;

public:
	static unique_ptr<Convert>& Instance();

private:
	static unique_ptr<Convert> m_pInstance;
};
