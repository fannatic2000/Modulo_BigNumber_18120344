#pragma once
#include <iostream> 
#include <string>
#include "bitsManipulation.h"

using namespace std;
class Modulo
{
public:
	static unique_ptr<Modulo>& Instance();

public:

	// GCD 
	string GCD(string bnum1, string bnum2) const;
	//Phép cộng trên vành Z(n)
	string AddMod(string bnum1, string bnum2, string pri) const;
	//Phép nhân trên vành Z(n)
	string MulMod(string bnum1, string bnum2, string bm) const;
	//Phép mũ trên vành Z(n)
	string PowerMod(string bnum1, string bnum2, string bm) const;
private:
	Modulo()
	{
	}
private:
	static unique_ptr<Modulo> m_pInstance;


};

