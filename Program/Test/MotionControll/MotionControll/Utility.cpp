#include "stdafx.h"
#include "Utility.h"


Utility::Utility()
{
}


Utility::~Utility()
{
}

//CStringתString
std::string Utility::toString(CString cs)
{
#ifdef _UNICODE
	//�����unicode����
	USES_CONVERSION;
	std::string str(W2A(cs));
	return str;
#else
	//����Ƕ��ֽڹ��� 
	std::string str(cs.GetBuffer());
	cs.ReleaseBuffer();
	return str;
#endif
}

//StringתCString
CString Utility::toCString(std::string str)
{
#ifdef _UNICODE
	//�����unicode����
	USES_CONVERSION; CString s(str.c_str());
	CString ans(str.c_str());
	return ans;
#else
	//����Ƕ��ֽڹ���
	CString ans;
	ans.Format("%s", str.c_str());
	return ans;
#endif 
}

CString Utility::AllocateImgName(int index,int pos, std::vector<MyImg>& ImgVec)
{
	char number[5];//��ų���Ϊ4�����Ϊ��\0��
	sprintf_s(number, "%04d", index);//int��ʽ��ת��λstring,ע�����Ҫ��\n
	number[4] = '\0';//������־
	//�洢����ǰĿ¼�����ļ���SavedImages
	std::string name = ".\\SavedImages\\Image_" + std::string(number) + ".jpg";//char * תstring���ù��캯��

	MyImg temp(name, pos, index);//��ʱ�洢��Ϣ�ı�

	ImgVec.push_back(temp);//����vector

	return toCString(ImgVec.back().imgName);//����ͼƬ����
}