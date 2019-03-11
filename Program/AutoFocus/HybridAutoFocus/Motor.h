#pragma once
#include"stdafx.h"
#include<Thorlabs.MotionControl.TCube.DCServo.h>

class Motor
{
public:
	std::string serialNo;//电机序列号
	bool _connected = false;//连接标志
public:
	Motor();
	Motor(std::string serialNo);
	~Motor();
	//设置序列号
	bool setSerialNo(std::string serialNo);
	//获取所有电机的编号
	int getDevices(int deviceID, std::vector<std::string> &serialNumbers, std::vector<TLI_DeviceInfo> &vecDecviceInfo);
	//连接电机
	bool connect(std::string strSerialNo);
	//断开连接
	bool disconnect(std::string strSerialNo);
	//移动到home
	int moveToHome(std::string strSerialNo);
	//移动到指定位置
	int moveToPosition(std::string strSerialNo, int position);
};

