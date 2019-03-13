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
	this->serialNo = serialNo;//设置
	return true;
}
int Motor::getDevices(int deviceID, std::vector<std::string> &serialNumbers, std::vector<TLI_DeviceInfo> &vecDecviceInfo)
{
	serialNumbers.clear();//初始化序列号的vector

	// Build list of connected device
	if (TLI_BuildDeviceList() == 0)//函数成功则继续执行
	{
		// get device list size 
		short n = TLI_GetDeviceListSize();
		// get LTS serial numbers
		char serialNos[250];
		TLI_GetDeviceListByTypeExt(serialNos, 250, deviceID);

		// output list of matching devices
		char *buf;//溢出缓存
		char *p = strtok_s(serialNos, ",", &buf);//分隔
		while (p != NULL)
		{
			TLI_DeviceInfo deviceInfo;//暂存设备信息的结构
			// get device info from device
			TLI_GetDeviceInfo(p, &deviceInfo);//获取设备信息
			vecDecviceInfo.push_back(deviceInfo);//将设备信息存储到vec中

			char serialNo[9];//存储设备序列号
			strncpy_s(serialNo, deviceInfo.serialNo, 8);//存储前八位，防止溢出
			serialNo[8] = '\0';//末尾添加"\0"
			// add to collection
			serialNumbers.push_back(std::string(serialNo));
			p = strtok_s(NULL, ",", &buf);//取下一个
		}
		return serialNumbers.size();//vector操作，返回元素个数
	}
	return 0;//失败则返回0，表示有0个电机
}

bool Motor::connect()
{
	const char *hMotor = serialNo.c_str();//从string类型转换位const char*类型
	
	if (_connected)//如果为true，则返回true；表示以经打开了
		return true;

	// open the device
	if (CC_Open(hMotor) == 0)//函数成功执行CC_Open()执行成功返回值为0
	{
		_connected = true;//已打开
		CC_LoadSettings(hMotor);// load the device settings,设定文件需要手动设置
		CC_StartPolling(hMotor, 200);// start the device polling at 200ms intervals
		return true;//成功打开
	}
	else
		return false;//打开失败
}

bool Motor::disconnect()
{
	const char *hMotor = serialNo.c_str();//从string类型转换位const char*类型

	if (!_connected)
	{
		return true;
	}

	//stop polling
	CC_StopPolling(hMotor);
	//close device
	CC_Close(hMotor);

	_connected = false;

	return !_connected;//成功关闭
}

int Motor::moveToHome()
{
	const char* hMotor = serialNo.c_str();//转换

	CC_ClearMessageQueue(hMotor);//清空消息队列
	CC_Home(hMotor);//移动信号发出

	//等待移动完成
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

	return pos;//返回实际位置
}

int Motor::moveToPosition(int position)
{
	const char* hMotor = serialNo.c_str();//转换

	// move to position (channel 1)//！！作用未知
	CC_ClearMessageQueue(hMotor);//清空消息队列
	CC_MoveToPosition(hMotor, position);//发送移动信号

	//等待移动完成
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

	return pos;//返回实际位置
}