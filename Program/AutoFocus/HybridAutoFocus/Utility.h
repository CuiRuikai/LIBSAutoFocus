#pragma once
#include"MyImg.h"
#include"stdafx.h"
class Utility
{
public:
	Utility();
	~Utility();

public:
	//CStringתString
	std::string toString(CString cs);
	//StringתCString
	CString toCString(std::string str);
	//ͼƬ���Ʒ��亯��
	CString AllocateImgName(int startIndex, std::vector<MyImg>& ImgVec);

	

};

