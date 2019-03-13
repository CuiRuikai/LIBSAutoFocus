#include "stdafx.h"
#include "Motor.h"


Motor::Motor()
{
}

Motor::Motor(std::string serialNo)
	:serialNo(serialNo)
{
}

Motor::~Motor()
{
}

bool Motor::setSerialNo(std::string serialNo) {
	this->serialNo = serialNo;//����
	return true;
}
int Motor::getDevices(int deviceID, std::vector<std::string> &serialNumbers, std::vector<TLI_DeviceInfo> &vecDecviceInfo)
{
	serialNumbers.clear();//��ʼ�����кŵ�vector

	// Build list of connected device
	if (TLI_BuildDeviceList() == 0)//�����ɹ������ִ��
	{
		// get device list size 
		short n = TLI_GetDeviceListSize();
		// get LTS serial numbers
		char serialNos[250];
		TLI_GetDeviceListByTypeExt(serialNos, 250, deviceID);

		// output list of matching devices
		char *buf;//�������
		char *p = strtok_s(serialNos, ",", &buf);//�ָ�
		while (p != NULL)
		{
			TLI_DeviceInfo deviceInfo;//�ݴ��豸��Ϣ�Ľṹ
			// get device info from device
			TLI_GetDeviceInfo(p, &deviceInfo);//��ȡ�豸��Ϣ
			vecDecviceInfo.push_back(deviceInfo);//���豸��Ϣ�洢��vec��

			char serialNo[9];//�洢�豸���к�
			strncpy_s(serialNo, deviceInfo.serialNo, 8);//�洢ǰ��λ����ֹ���
			serialNo[8] = '\0';//ĩβ���"\0"
			// add to collection
			serialNumbers.push_back(std::string(serialNo));
			p = strtok_s(NULL, ",", &buf);//ȡ��һ��
		}
		return serialNumbers.size();//vector����������Ԫ�ظ���
	}
	return 0;//ʧ���򷵻�0����ʾ��0�����
}

bool Motor::connect()
{
	const char *hMotor = serialNo.c_str();//��string����ת��λconst char*����
	
	if (_connected)//���Ϊtrue���򷵻�true����ʾ�Ծ�����
		return true;

	// open the device
	if (CC_Open(hMotor) == 0)//�����ɹ�ִ��CC_Open()ִ�гɹ�����ֵΪ0
	{
		_connected = true;//�Ѵ�
		CC_LoadSettings(hMotor);// load the device settings,�趨�ļ���Ҫ�ֶ�����
		CC_StartPolling(hMotor, 200);// start the device polling at 200ms intervals
		return true;//�ɹ���
	}
	else
		return false;//��ʧ��
}

bool Motor::disconnect()
{
	const char *hMotor = serialNo.c_str();//��string����ת��λconst char*����

	if (!_connected)
	{
		return true;
	}

	//stop polling
	CC_StopPolling(hMotor);
	//close device
	CC_Close(hMotor);

	_connected = false;

	return !_connected;//�ɹ��ر�
}

int Motor::moveToHome()
{
	const char* hMotor = serialNo.c_str();//ת��

	CC_ClearMessageQueue(hMotor);//�����Ϣ����
	CC_Home(hMotor);//�ƶ��źŷ���

	//�ȴ��ƶ����
	WORD messageType;
	WORD messageId;
	DWORD messageData;
	CC_WaitForMessage(hMotor, &messageType, &messageId, &messageData);
	while (messageType != 2 || messageId != 1)
	{
		CC_WaitForMessage(hMotor, &messageType, &messageId, &messageData);
	}

	// get actual poaition
	int pos = CC_GetPosition(hMotor);

	return pos;//����ʵ��λ��
}

int Motor::moveToPosition(int position)
{
	const char* hMotor = serialNo.c_str();//ת��

	// move to position (channel 1)//��������δ֪
	CC_ClearMessageQueue(hMotor);//�����Ϣ����
	CC_MoveToPosition(hMotor, position);//�����ƶ��ź�

	//�ȴ��ƶ����
	WORD messageType;
	WORD messageId;
	DWORD messageData;
	CC_WaitForMessage(hMotor, &messageType, &messageId, &messageData);
	while (messageType != 2 || messageId != 1)
	{
		CC_WaitForMessage(hMotor, &messageType, &messageId, &messageData);
	}

	// get actual poaition
	int pos = CC_GetPosition(hMotor);

	return pos;//����ʵ��λ��
}