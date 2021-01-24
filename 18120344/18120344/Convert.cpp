#include <algorithm>

#include "Convert.h"

#include "bitsManipulation.h"


string Convert::convertDecToBin(string num, unsigned int nbit)
{
	string result;
	unsigned int index = 0;
	bool negative = num[0] == '-';
	
	size_t found = num.find("-");
	if (found != string::npos)
	{
		num = num.substr(found + 1, num.length() - 1);
	}
	
	while (num != "0")
	{
		char c = ((num[num.length() - 1] - '0') % 2) + 48;
		result.insert(result.begin(),c);
		num = devideFor2(num);
	}

	result.insert(result.begin(), '0');

	if (negative)
	{
		convertToBu2(result);
	}
	
	bitsManipulation::Instance()->standardizeNBinary(result, nbit);

	return result;
}

string Convert::convertBinToDec(string bnum)
{
	
	int index = 0;
	string decResult ;
	
	bool isNegative = false;
	
	if (bnum[0] == '1')
	{
		isNegative = true;
	}
		
	if (isNegative)
	{
		convertToBu2(bnum);
	}

	size_t found = bnum.find("1");
	index = found;

	int length = bnum.length();

	while (index < length)
	{
		int exp = length - 1 - index;
		if (bnum[index] == '1') {
				
				decResult = add2nBinary(decResult,pow(2, exp));
				
		}
		index++;
	}

    if (isNegative)
	{
		decResult.insert(0, "-");
	}

	return decResult;
}

void Convert::convertToBu2(string& bits)
{
	bitsManipulation::Instance()->ReverseBits(bits);
	bits = bitsManipulation::Instance()->add2BNum(bits, "0001");
}

string Convert::add2nBinary(string num1, string num2)
{
	string result = "";
	int reminder = 0;
	int pointerNum1 = num1.length() - 1;
	int pointerNum2 = num2.length() - 1;
	int resultOfAddingTwoNum = 0;

	while (pointerNum1 >= 0 && pointerNum2 >= 0)
	{
		resultOfAddingTwoNum = num1[pointerNum1] + num2[pointerNum2] + reminder - 2 * 48;

		reminder = resultOfAddingTwoNum / 10;
		resultOfAddingTwoNum %= 10;

		string s = "";
		s += resultOfAddingTwoNum + 48;

		result.insert(0, s);
		resultOfAddingTwoNum = 0;
		pointerNum1--;
		pointerNum2--;

	}

	while (pointerNum1 >= 0)
	{
		resultOfAddingTwoNum = num1[pointerNum1] - 48 + reminder;

		reminder = resultOfAddingTwoNum / 10;
		resultOfAddingTwoNum %= 10;

		string s = "";
		s += resultOfAddingTwoNum + 48;

		result.insert(0, s);
		resultOfAddingTwoNum = 0;
		pointerNum1--;
	}

	while (pointerNum2 >= 0)
	{
		resultOfAddingTwoNum = num2[pointerNum2] - 48 + reminder;

		reminder = resultOfAddingTwoNum / 10;
		resultOfAddingTwoNum %= 10;

		string s = "";
		s += resultOfAddingTwoNum + 48;

		result.insert(0, s);
		resultOfAddingTwoNum = 0;
		pointerNum2--;
	}

	if (reminder != 0)
	{
		string s = "";
		s += reminder + 48;

		result.insert(0, s);
	}

	return result;
}

string Convert::devideFor2(string num)
{
	unsigned int index = 0;
	if (num[0] == '-' || num[0] == '+')
	{
		index++;
	}

	unsigned int dividendNum = 0;
	unsigned int surplus = 0;
	unsigned int resultTemp = 0;
	string resultStr = "";

	while (index < num.length())
	{
		dividendNum = (dividendNum * 10) + num[index] - '0';
		resultTemp = dividendNum / 2;
		surplus = dividendNum % 2;

		if (surplus != 0)
		{
			dividendNum = surplus;
		}
		else
		{
			dividendNum = 0;
		}
		resultStr += to_string(resultTemp);
		index++;
	}

	if (resultStr[0] == '0' && resultStr.length() > 1)
	{
		resultStr.erase(0, 1);
	}

	return resultStr;
}

string Convert::mulStringwithInt(string num1, int num2)
{
	int r = 0;
	string q = "";

	for (int i = num1.length() - 1; i >= 0; i--)
	{
		int k = (int)(num1[i] - '0');
		int temp = (k * num2) + r;

		if (temp > 9)
		{
			r = temp / 10;
			temp = temp % 10;
			q = to_string(temp) + q;
		}
		else
		{
			q = to_string(temp) + q;
			r = 0;
		}
	}
	if (r > 0)
		q = to_string(r) + q;

	return string(q);
}

string Convert::mul2dString(string num1, string num2)
{
	string re = "";
	string zero = "";
	for (int i = num1.length() - 1; i >= 0; i--)
	{
		int k = (int)(num1[i] - '0');

		string temp = Convert::mulStringwithInt(num2, k) + zero;

		zero = zero + "0";

		re = add2nBinary(re, temp);

	}
	return string(re);
}

string Convert::pow(int factor, int exp)
{
	string result = "1";

	for (int i = 0; i < exp; i++)
	{
		result = mulStringwithInt(result, factor);
	}
	return result;
}

unique_ptr<Convert> Convert::m_pInstance(nullptr);

unique_ptr<Convert>& Convert::Instance()
{
	if (m_pInstance.get() == nullptr)
	{
		m_pInstance.reset(new Convert());
	}
	return m_pInstance;
}




