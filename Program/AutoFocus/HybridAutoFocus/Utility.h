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
	//ͼ���ţ���0��ʼ
	int startIndex;
	//CStringתString
	std::string toString(CString cs);
	//StringתCString
	CString toCString(std::string str);
	//ͼƬ���Ʒ��亯��
	CString AllocateImgName();
	//Ѱ��������Χ
	int FindClearSection(std::vector<MyImg> imgVec,int &start, int &end);
	int FindClearPos(std::vector<MyImg> imgVec);
	//���Ѱ�����ŵ�
	int ployfitPos(std::vector<MyImg> imgVec);
	//��ͼƬ��Ϣ������ļ�
	bool writeInfoToFile(std::vector<MyImg> imgVec);
};