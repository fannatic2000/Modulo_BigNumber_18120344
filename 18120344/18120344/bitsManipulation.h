#pragma once

#include <string>
#include <memory>
#include "Convert.h"

using namespace std;
#define MAX_BIT 1024

class bitsManipulation
{
public:
	// Chuẩn hóa dãy bit thành nbit
	void standardizeNBinary(string& bnum, int nbit);

	//Đảo chuỗi bits
	void ReverseBits(string& bits);

	//Cộng nhị phân 2 dãy bits
	string add2BNum(string bits1, string bits2);

	//Thực hiện trừ 2 dãy bits
	string sub2BNum(string bits1, string bits2);

	// dịch trai
	string SLL(string bnum, int nbit) const;

	//dinh phải
	string SLR(string bnum, int nbit) const;

	//so sanh 2 chuoi so
	int Compare(string num1, string num2) const;

	//trừ 2 chuỗi string
	string Sub(string num1, string num2) const;

	//nhan 2 string bit
	string Mul(string num1, string num2) const;

private:
	bitsManipulation()
	{
	}

public:
	static unique_ptr<bitsManipulation>& Instance();

private:
	static unique_ptr<bitsManipulation> m_pInstance;
};
