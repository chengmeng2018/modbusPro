/**************************************
*��������ȡ�����б�ӿڣ��������嵥�������ַ���������
*������win7~win10 VS2019�¿��� x86  unicode
*
*���ߣ�cmm
*���ڣ�2021��3��10��
* �汾��Ver.1.0.0
***************************************/
#pragma once


#include <string>
#include <vector>
class  CSetupAPI
{
public:
	CSetupAPI();
	virtual ~CSetupAPI();
	/**ˢ�´����嵥
	*	@return ���ڵ�����
	*	@note �������Զ���ȡ�����������ڱ��
	*/
	uint16_t UpData();
	/**��ȡ��ǰ�Ĵ�������
	* @param nUpdata ��ʶ���´����б���ٻ������
	* @return ���ڵĴ�������
	*/
	uint16_t GetComNumber(bool nUpdata = false);
	/**��ȡ��ǰ�Ĵ����б�
	* @param nUpdata ��ʶ���´����б���ٻ������
	* @return ���ڵĴ����б�
	*/
	const std::vector<std::wstring>& GetComNameVec(bool nUpdata = false);
	/**���ݴ����б�˳�� ��ö�Ӧ���ں�
	* @param idx �����б�˳��
	* @return ����ID��
	*/
	uint16_t GetComID(uint16_t idx);
	/**���ݴ������� ��������Ӧ���ں�
	* @param idx ��������
	* @return ����ID��
	*/
	uint16_t GetComID(std::wstring& nComName);
	/**���ݴ���˳�� ��ô�������
	* @param idx ����˳��
	* @return ��������
	*/
	std::wstring GetComName(uint16_t idx);
private:
	std::vector<std::wstring> m_ComName;
};


