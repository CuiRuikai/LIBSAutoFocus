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
	bool connect();
	//�Ͽ�����
	bool disconnect();
	//�ƶ���home
	int moveToHome();
	//�ƶ���ָ��λ��
	int moveToPosition(int position);
};

