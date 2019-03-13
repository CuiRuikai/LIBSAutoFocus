#pragma once
#include"MyImg.h"
#include"stdafx.h"
class Utility
{
public:
	Utility();
	~Utility();

public:
	//图像编号，从0开始
	int startIndex;
	//CString转String
	std::string toString(CString cs);
	//String转CString
	CString toCString(std::string str);
	//图片名称分配函数
	CString AllocateImgName();
};

