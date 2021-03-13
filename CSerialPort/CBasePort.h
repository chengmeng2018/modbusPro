#pragma once
#include <vector>
#include <winsock.h>
typedef std::vector<uint8_t> vec8_t;
enum class EPortMsg :char
{
	E_Busy,
	E_Ok,
	E_Timeout,
	E_ReadErr
};
class CBasePort
{
public:
	CBasePort();
	virtual~CBasePort();
	/*�û��̳к��ڴ˴���ӳ�ʼ������*/
	virtual void Init() {};
	/**�����豸���ӣ�ʹ��ǰӦ��ִ��InitSerial
	*@return 0 ���ӳɹ� -1ʧ��
	*/
	virtual int Connect() = 0;

	virtual void Close() = 0;

	/*��������
	* @param req ������ʼ��ַ
	* @param req_length ���ݳ���
	*/
	virtual int send(vec8_t& reqvec) = 0;
	/*��������
	* @return ���յ����ݳ���
	*/
	virtual EPortMsg read(vec8_t& rec, const struct timeval* tv = NULL) = 0;
private:

};
