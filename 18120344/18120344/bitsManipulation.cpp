#include "bitsManipulation.h"


unique_ptr<bitsManipulation> bitsManipulation::m_pInstance(nullptr);


void bitsManipulation::standardizeNBinary(string& bnum, int nbit)
{
	unsigned int i = bnum.size();
	char bit = '0';

	if (bnum[0] == '1')
	{
		bit = '1';
		
	}

	// nếu vượt quá thì cắt bớt
	if (i > nbit)
	{
		unsigned int numErase = i - nbit;
		bnum.erase(0, numErase);
		return;
	}
	
	// chưa vượt thì thêm vào
	while (i < nbit)
	{
		bnum.insert(bnum.begin(), bit);
		i++;
	}
}


void bitsManipulation::ReverseBits(string& bits)
{
	for (int i = 0; i < bits.size(); i++)
	{
		if (bits[i] == '0')
		{
			bits[i] = '1';
		}
		else
		{
			bits[i] = '0';
		}
	}
}

string bitsManipulation::add2BNum(string num1, string num2)
{
	size_t found;
	string str = "";
	int temp = 0;
	int Sum;

	found = num1.find("1");
	if (found != string::npos && found > 1)
	{
		num1 = num1.substr(found - 2, num1.length() - found + 2);
	}
	int q1Len = num1.length();

	found = num2.find("1");
	if (found != string::npos && found > 1)
	{
		num2 = num2.substr(found - 2, num2.length() - found + 2);
	}
	int q2Len = num2.length();
	int maxLen;
	maxLen = (q1Len > q2Len) ? q1Len : q2Len;

	bitsManipulation::Instance()->standardizeNBinary(num1, maxLen);
	bitsManipulation::Instance()->standardizeNBinary(num2, maxLen);

	
	for (int i = maxLen - 1; i > 0; i--)
	{
		Sum = ((int)num1[i] - 48) + ((int)num2[i] - 48) + temp;
		if (Sum == 1)
		{
			num1[i] = '1';
			temp = 0;
		}
		else
		{
			if (Sum == 0)
			{
				num1[i] = '0';
				temp = 0;
			}
			else
			{
				if (Sum == 2)
				{
					num1[i] = '0';
					temp = 1;
				}
				else
				{
					if (Sum == 3)
					{
						num1[i] = '1';
						temp = 1;
					}
				}
			}
		}
	}
	str = num1;

	return str;
}

string bitsManipulation::sub2BNum(string bits1, string bits2)
{
	Convert::Instance()->convertToBu2(bits2);
	string result = bitsManipulation::add2BNum(bits1, bits2);
	return result;
}

string bitsManipulation::SLL(string str, int nbit) const
{
	for (int i = 0; i <= str.length() - 1 - nbit; i++)
	{
		str[i] = str[i + nbit];
	}
	for (int i = str.length() - nbit; i < str.length(); i++)
	{
		str[i] = '0';
	}
	return str;
}

string bitsManipulation::SLR(string str, int nbit) const
{
	for (int i = str.length() - 1; i >= nbit; i--)
	{
		str[i] = str[i - nbit];
	}
	for (int i = 0; i < nbit; i++)
	{
		str[i] = '0';
	}
	return str;
}

string bitsManipulation::Sub(string num1, string num2) const
{
	Convert::Instance()->convertToBu2(num2);
	string temp = bitsManipulation::Instance()->add2BNum(num1, num2);
	return temp;
}

string bitsManipulation::Mul(string num1, string num2) const
{
	string count = "1";
	string temp = num1;
	bitsManipulation::Instance()->standardizeNBinary(count, num1.length());
	string start = count;
	while (Compare(start, num2) != 0)
	{
		num1 = bitsManipulation::Instance()->add2BNum(num1, temp);
		start = bitsManipulation::Instance()->add2BNum(start, count);
	}

	return num1;
}

int bitsManipulation::Compare(string num1, string num2) const
{
	size_t found;

	found = num1.find("1");
	if (found != string::npos && found != 0)
	{
		num1 = num1.substr(found - 1, num1.length() - found + 1);
	}
	int q1Len = num1.length();

	found = num2.find("1");
	if (found != string::npos && found != 0)
	{
		num2 = num2.substr(found - 1, num2.length() - found + 1);
	}
	int q2Len = num2.length();
	int maxLen;
	maxLen = (q1Len > q2Len) ? q1Len : q2Len;

	bitsManipulation::Instance()->standardizeNBinary(num1, maxLen);
	bitsManipulation::Instance()->standardizeNBinary(num2, maxLen);

	if (num1[0] != num2[0])
	{
		return (num1[0] != '1') ? 1 : -1;
	}
	else
	{
		for (int i = 1; i < maxLen; i++)
		{
			if (num1[i] > num2[i])
			{
				return 1;
			}
			if (num1[i] < num2[i])
			{
				return -1;
			}
		}
	}
	return 0;
}

unique_ptr<bitsManipulation>& bitsManipulation::Instance()
{
	if (m_pInstance.get() == nullptr)
	{
		m_pInstance.reset(new bitsManipulation());
	}
	return m_pInstance;
}


