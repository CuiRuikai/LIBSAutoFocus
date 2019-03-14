#pragma once
#include"stdafx.h"
#include"MyImg.h"
#include"Motor.h"
#include"Utility.h"
#include "MVGigE.h" 
#include "MVImage.h" 
class Motion
{
public:
	Motor motor;//�����ĵ��
	//�������������� 
	HANDLE m_hCam;
	//����ͼ������� 
	MVImage m_image;
	//���ߺ���
	Utility utility;
	//����ͼ��ʹ�õı���
	CRITICAL_SECTION m_csSaveImage;
public:
	Motion();
	Motion(Motor &motor, HANDLE &hCam, MVImage &m_image, Utility &utility);
	~Motion();

public:
	int moveAndGrabImgs(int startPos, int stopPos, int step, std::vector<MyImg> &imgVec);
	MyImg moveToPosAndGrab(int pos, std::string imgName);
};

