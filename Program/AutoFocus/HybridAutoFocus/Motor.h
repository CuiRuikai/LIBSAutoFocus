#pragma once
#include"stdafx.h"
#include<Thorlabs.MotionControl.TCube.DCServo.h>

class Motor
{
public:
	std::string serialNo;//������к�
	bool _connected = false;//���ӱ�־
public:
	Motor();
	Motor(std::string serialNo);
	~Motor();
	//�������к�
	bool setSerialNo(std::string serialNo);
	//��ȡ���е���ı��
	int getDevices(int deviceID, std::vector<std::string> &serialNumbers, std::vector<TLI_DeviceInfo> &vecDecviceInfo);
	//���ӵ��
	bool connect(std::string strSerialNo);
	//�Ͽ�����
	bool disconnect(std::string strSerialNo);
	//�ƶ���home
	int moveToHome(std::string strSerialNo);
	//�ƶ���ָ��λ��
	int moveToPosition(std::string strSerialNo, int position);
};

