#pragma once
#include "../CSerialPort/CBasePort.h"

typedef enum class enumFunCode
{
	//������
	Enum_BroadCast = 0x00,
	//bit
	Enum_ROStat = 0x01,/*�������״̬*/
	Enum_RIDis = 0x02,/*��������ɢ��*/
	Enum_WSOut = 0x05,/*д���������*/
	Enum_WMOut = 0x0F,/*д��������*/
	//byte
	Enum_RIReg = 0x04,/*������Ĵ���*/
	Enum_ROReg = 0x03,/*������Ĵ���*/
	Enum_WSReg = 0x06,/*д�����Ĵ���*/
	Enum_WMReg = 0x10,/*д����Ĵ���*/
	//Enum_RWReg = 0x17,/*�� / д�Ĵ���*/
	Enum_MWReg = 0x16,/*����д�Ĵ���*/
	//Other
	Enum_GCECout = 0x0B,/*��ȡͨ���¼�����*/
	Enum_Exception=0x07,/*��ȡ�쳣״̬*/
} EModbusCmd;
enum class ERecMsg :char
{
	E_OK,
	E_Unknown,
	E_chcekErr,
	E_TimeOut,
	E_NOPORT,
	E_Err01,
	E_Err02,
	E_Err03,
	E_Err04
};

class CModbus_master
{
public:
	CModbus_master() :pPort(NULL), m_tv({0,100}) {};
	CModbus_master(CBasePort* nPort);
	virtual ~CModbus_master();
public:
	void SetBasePort(CBasePort* pPort) { this->pPort = pPort; }
	CBasePort* GetBasePort() { return pPort; }
	void SetReadDelayTime(timeval& ntv) { m_tv = ntv; }
	ERecMsg ReadAndAnaylse(vec8_t& nRec);
	/*����Ķ�����
	* @param nDriveId �ӻ��豸��ַ1~247
	* @param cmd �ٿ�����
	* @param AddressSt ��ʼ��ַ0x0000~0xffff
	* @param number ��Ȧ����1~2000
	* @return ��EReMsg
	*/
	void OperatingAddNum(uint8_t& nDriveId, EModbusCmd cmd, uint16_t& AddressSt, uint16_t& number, vec8_t& nRec);
	/*��ȡ������Ϣ(δ����)*/
	int GetLastError(std::string& nError) {};
	/*������ 01����Ȧ
	* @param nDriveId �ӻ��豸��ַ1~247
	* @param AddressSt ��ʼ��ַ0x0000~0xffff
	* @param number ��Ȧ����1~2000
	* @return ��EReMsg
	*/
	ERecMsg readOutputBit(uint8_t nDriveId, uint16_t AddressSt, uint16_t number, vec8_t& nRec);
	/*������ 02��������ɢ��
	* @param nDriveId �ӻ��豸��ַ1~247
	* @param AddressSt ��ʼ��ַ0x0000~0xffff
	* @param number ��ɢ����������1~2000
	* @return ��EReMsg
	*/
	ERecMsg readInputBit(uint8_t nDriveId, uint16_t AddressSt, uint16_t number, vec8_t& nRec);

	/*������ 03�����ּĴ���
	* @param nDriveId �ӻ��豸��ַ1~247
	* @param AddressSt ��ʼ��ַ0x0000~0xffff
	* @param number �Ĵ�������1~125
	* @return ��EReMsg
	*/
	ERecMsg readHoldRegister(uint8_t nDriveId, uint16_t AddressSt, uint16_t number, vec8_t& nRec);

	/*������ 04������Ĵ���
	* @param nDriveId �ӻ��豸��ַ1~247
	* @param AddressSt ��ʼ��ַ0x0000~0xffff
	* @param number �Ĵ�������1~125
	* @return ��EReMsg
	*/
	ERecMsg readInputRegister(uint8_t nDriveId, uint16_t AddressSt, uint16_t number, vec8_t& nRec);
	/*������ 05д������Ȧ
	* @param nDriveId �ӻ��豸��ַ1~247
	* @param AddressSt ��ʼ��ַ0x0000~0xffff
	* @param value ����0xFF00 0x0000
	* @return ��EReMsg
	*/
	ERecMsg writeSinglebit(uint8_t nDriveId, uint16_t AddressSt, uint16_t value, vec8_t& nRec);
	/*������ 06д�����Ĵ���
		* @param nDriveId �ӻ��豸��ַ1~247
		* @param AddressSt ��ʼ��ַ0x0000~0xffff
		* @param value �Ĵ�������
		* @return ��EReMsg
		*/
	ERecMsg writeSingleRegister(uint8_t nDriveId, uint16_t AddressSt, uint16_t value, vec8_t& nRec);
	/*������ 07��ȡ�쳣״̬�������ڴ�����·
	* @param nDriveId �ӻ��豸��ַ1~247
	* @return ��EReMsg
	*/
	ERecMsg readException(uint8_t nDriveId, vec8_t& nRec);
	/*������ 0B��ȡ�쳣״̬�������ڴ�����·
	* @param nDriveId �ӻ��豸��ַ1~247
	* @return ��EReMsg
	*/
	ERecMsg getCommunicationEventCount(uint8_t nDriveId, vec8_t& nRec);
protected:
	//RTUģʽ
 //����ַ���������롿����������������1��������������n����CRC���ֽڡ���CRC���ֽڡ�
	static	void crc16(vec8_t& nDataVec);
	static	uint16_t crc16(const uint8_t* buffer, uint16_t buffer_length);
	static ERecMsg checkCrc16(const vec8_t& nDataVec);
private:
	/*read DelayTime*/
	timeval m_tv;
	/*ͨ�Žӿ�*/
	CBasePort* pPort;
};
