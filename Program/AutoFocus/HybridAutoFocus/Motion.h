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
	Motor motor;//操作的电机
	//定义相机句柄对象 
	HANDLE m_hCam;
	//定义图像处理对象 
	MVImage m_image;
	//工具函数
	Utility utility;
	//保存图像使用的变量
	CRITICAL_SECTION m_csSaveImage;
public:
	Motion();
	Motion(Motor &motor, HANDLE &hCam, MVImage &m_image, Utility &utility);
	~Motion();

public:
	int moveAndGrabImgs(int startPos, int stopPos, int step, std::vector<MyImg> &imgVec);
	MyImg moveToPosAndGrab(int pos, std::string imgName);
};

