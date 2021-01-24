#include "Modulo.h"



unique_ptr<Modulo> Modulo::m_pInstance(nullptr);

unique_ptr<Modulo>& Modulo::Instance()
{
	if (m_pInstance.get() == nullptr)
	{
		m_pInstance.reset(new Modulo());
	}
	return m_pInstance;
}

string Modulo::GCD(string num1, string num2) const
{
	size_t found;

	found = num1.find("1");
	if (found != string::npos && found >= 2)
	{
		num1 = num1.substr(found - 2, num1.length() - found + 2);
	}
	int q1Len = num1.length();

	found = num2.find("1");
	if (found != string::npos && found >= 2)
	{
		num2 = num2.substr(found - 2, num2.length() - found + 2);
	}
	int q2Len = num2.length();
	int maxLen;
	maxLen = (q1Len > q2Len) ? q1Len : q2Len;

	bitsManipulation::Instance()->standardizeNBinary(num1, maxLen);
	bitsManipulation::Instance()->standardizeNBinary(num2, maxLen);

	string result = "1"; 
	bitsManipulation::Instance()->standardizeNBinary(result, maxLen);
	string num_zero = "0";
	bitsManipulation::Instance()->standardizeNBinary(num_zero, maxLen);
	string temp;


	if (bitsManipulation::Instance()->Compare(num1, num2) == 0)
	{
		bitsManipulation::Instance()->standardizeNBinary(num1, MAX_BIT);
		return num1;
	}
	if (bitsManipulation::Instance()->Compare(num1, num_zero) == 0)
	{
		bitsManipulation::Instance()->standardizeNBinary(num2, MAX_BIT);
		return num2;
	}
	if (bitsManipulation::Instance()->Compare(num2, num_zero) == 0)
	{
		bitsManipulation::Instance()->standardizeNBinary(num1, MAX_BIT);
		return num1;
	}

	if (num1[num1.length()-1] == '0') {
        if (num2[num2.length()-1] == '1')
            return GCD(bitsManipulation::Instance()->SLR(num1,1), num2); 
        else 
            return bitsManipulation::Instance()->SLL(GCD(bitsManipulation::Instance()->SLR(num1,1), bitsManipulation::Instance()->SLR(num2,1)),1); // Identity 2

    } else { 
        if (num2[num2.length()-1] == '0') 
            return GCD(num1, bitsManipulation::Instance()->SLR(num2,1)); 
        if (bitsManipulation::Instance()->Compare(num1,num2))
            return GCD(bitsManipulation::Instance()->SLR(bitsManipulation::Instance()->Sub(num1,num2),1),num2);
        else
            return GCD(bitsManipulation::Instance()->SLR(bitsManipulation::Instance()->Sub(num2, num1), 1), num1);
    }
}

string Modulo::AddMod(string num1, string num2, string pri) const
{
	size_t found;

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

	found = pri.find("1");
	if (found != string::npos && found > 1)
	{
		pri = pri.substr(found - 2, pri.length() - found + 2);
	}
	int pLen = pri.length();

	int maxLen = (q1Len > q2Len) ? q1Len : q2Len;
	maxLen = (maxLen > pLen) ? maxLen : pLen;

	bitsManipulation::Instance()->standardizeNBinary(pri, maxLen);
	bitsManipulation::Instance()->standardizeNBinary(num1, maxLen);
	bitsManipulation::Instance()->standardizeNBinary(num2, maxLen);

	while (bitsManipulation::Instance()->Compare(num1, pri) != -1) {
		num1 = bitsManipulation::Instance()->Sub(num1, pri);
		bitsManipulation::Instance()->standardizeNBinary(num1, maxLen);

	}

	while (bitsManipulation::Instance()->Compare(num2, pri) != -1) {
		num2 = bitsManipulation::Instance()->Sub(num2, pri);
		bitsManipulation::Instance()->standardizeNBinary(num2, maxLen);

	}

	string Res = bitsManipulation::Instance()->add2BNum(num1, num2);

	found = Res.find("1");
	if (found != string::npos)
	{
		Res = Res.substr(found - 1, Res.length() - found + 1);
	}
	int resLen = Res.length();

	maxLen = (maxLen > resLen) ? maxLen : resLen;

	bitsManipulation::Instance()->standardizeNBinary(Res, maxLen);
	while (bitsManipulation::Instance()->Compare(Res, pri) != -1) {
		Res = bitsManipulation::Instance()->Sub(Res, pri);
		bitsManipulation::Instance()->standardizeNBinary(Res, maxLen);
	}
	bitsManipulation::Instance()->standardizeNBinary(Res, MAX_BIT);
	return Res;
}

string Modulo::MulMod(string num1, string num2, string num_Mod) const
{
	string st1 = num1;
	string st2 = num2;
	string str = "";
	size_t found;
	found = st1.find("1");
	if (found != string::npos && found > 7)
	{
		st1 = st1.substr(found - 8, st1.length() - found + 8);
	}

	found = st2.find("1");
	if (found != string::npos && found > 7)
	{
		st2 = st2.substr(found - 8, st2.length() - found + 8);
	}
	int maxLen;
	maxLen = (st1.length() > st2.length()) ? st1.length() : st2.length();
	bitsManipulation::Instance()->standardizeNBinary(st1, maxLen);
	bitsManipulation::Instance()->standardizeNBinary(st2, maxLen);

	int i = st1.length() - 1;
	if (st2[st2.length() - 1] > '0') str = st1;
	i--;
	for (; i >= 0; i--) {
		st1 = st1 + '0';
		if (st2[i] == '1') str = AddMod(str, st1, num_Mod);
	}
	bitsManipulation::Instance()->standardizeNBinary(str, MAX_BIT);
	return str;
	
}

string Modulo::PowerMod(string num1, string num2, string num_Mod) const
{
	string zero = "0";
	bitsManipulation::Instance()->standardizeNBinary(zero, MAX_BIT);
	string result = "1";
	bitsManipulation::Instance()->standardizeNBinary(result, MAX_BIT);
	if (num2 == zero)
	{
		return result;
	}
	string str2 = num2;
	string A = num1;
	size_t found;
	found = str2.find("1");
	if (found != string::npos && found > 0)
	{
		str2 = str2.substr(found - 1 , str2.length() - found + 1);
	};
	if (str2[str2.length() - 1] == '1')
	{
		result = num1;
	}
	for (int i = str2.length() - 2; i >= 0; i--)
	{
		A = MulMod(A, A, num_Mod);
		if (str2[i] == '1')
		{
			result = MulMod(A, result, num_Mod);
		}
	}
	return result;
}