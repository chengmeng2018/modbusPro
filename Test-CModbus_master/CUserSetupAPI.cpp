#include "CUserSetupAPI.h"
#include <sstream> 
#include <iostream>
void CUserSetupAPI::Test()
{
	/*��ȡ�����б�*/
	CSetupAPI mCom;
	uint16_t num = mCom.GetComNumber();
	auto nComName = mCom.GetComNameVec();
	std::wstringstream ss;
	ss << "��⵽����������" << mCom.GetComNumber() << std::endl;
	for (auto& var : nComName)
	{
		ss << "���ƣ�" << var << std::endl;
		ss << "ID��" << mCom.GetComID(var) << std::endl;
	}
	std::wcout << ss.str() << std::endl;
}
