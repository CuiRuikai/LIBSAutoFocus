#pragma once
#include"MyImg.h"
#include"stdafx.h"
class Utility
{
public:
	Utility();
	~Utility();

public:
	//ͼ���ţ���0��ʼ
	int startIndex;
	//CStringתString
	std::string toString(CString cs);
	//StringתCString
	CString toCString(std::string str);
	//ͼƬ���Ʒ��亯��
	CString AllocateImgName();
};

