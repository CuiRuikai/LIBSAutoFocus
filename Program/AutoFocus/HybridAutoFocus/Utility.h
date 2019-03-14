#pragma once
#include"MyImg.h"
#include"stdafx.h"
#include"Fit.h"
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
	//寻找清晰范围
	int FindClearSection(std::vector<MyImg> imgVec,int &start, int &end);
	int FindClearPos(std::vector<MyImg> imgVec);
	//拟合寻找最优点
	int ployfitPos(std::vector<MyImg> imgVec);
	//将图片信息输出到文件
	bool writeInfoToFile(std::vector<MyImg> imgVec);
};