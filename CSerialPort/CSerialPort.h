#pragma

#if defined(_WIN32)
#include <windows.h>
#endif
#include <string>
#include "CBasePort.h"
typedef std::vector<uint8_t> vec8_t;

class CSerialPort :public CBasePort
{
public:
	CSerialPort();
	virtual	~CSerialPort();
	/*�û��̳к��ڴ˴���ӳ�ʼ������*/
	//virtual void Init() {};
	void SetSerialPort(const uint8_t portID,bool recSt=false);
	/**��ʼ����������
	* @param device ��������COM%d
	* @param baud ������
	* @param parity ��żУ��
	* @param data_bit λ��4~8
	* @param stop_bit ֹͣλ��ʶ
	* @return true ���óɹ�
	*/
	bool InitSerial(const char* device,
		int baud, char parity, int data_bit,
		int stop_bit);
	/**��ʼ����������
* @param portID ���ں�
* @param baud ������
* @param parity ��żУ��
* @param data_bit λ��4~8
* @param stop_bit ֹͣλ��ʶ
* @return true ���óɹ�
*/
	bool InitSerial(const uint8_t portID,
		int baud, char parity, int data_bit,
		int stop_bit);
	/**�����豸���ӣ�ʹ��ǰӦ��ִ��InitSerial
	*@return 0 ���ӳɹ� -1ʧ��
	*/
	int Connect();

	void Close();

	/*��������
	* @param req ������ʼ��ַ
	* @param req_length ���ݳ���
	*/
	int send(const uint8_t* req, int req_length);
	int send(vec8_t& reqvec);
	/*��������
	* @return ���յ����ݳ���
	*/
	EPortMsg read(int max_len, const struct timeval* tv = NULL);
	EPortMsg read(vec8_t& rec, const struct timeval* tv = NULL);
private:

#if defined(_WIN32)
#if !defined(ENOTSUP)
#define ENOTSUP WSAEOPNOTSUPP
#endif

	/* WIN32: struct containing serial handle and a receive buffer */
#define PY_BUF_SIZE 512
	struct win32_ser {
		win32_ser() :fd(INVALID_HANDLE_VALUE), n_bytes(NULL) {}
		/* File handle */
		HANDLE fd;
		/* Receive buffer */
		uint8_t buf[PY_BUF_SIZE];
		/* Received chars */
		DWORD n_bytes;
	};
#endif /* _WIN32 */

	/* Device: "/dev/ttyS0", "/dev/ttyUSB0" or "/dev/tty.USA19*" on Mac OS X. */
	std::string  device;
	/* Bauds: 9600, 19200, 57600, 115200, etc */
	int baud;
	/* Data bit */
	uint8_t data_bit;
	/* Stop bit */
	uint8_t stop_bit;
	/* Parity: 'N', 'O', 'E' */
	char parity;
#if defined(_WIN32)
	struct win32_ser w_ser;
	DCB old_dcb;
#endif
	/* To handle many slaves on the same link */
	int confirmation_to_ignore;
};

