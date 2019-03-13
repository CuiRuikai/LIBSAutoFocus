#include "stdafx.h"
#include "Utility.h"


Utility::Utility()
	:startIndex(0)
{
}


Utility::~Utility()
{
}

//CString转String
std::string Utility::toString(CString cs)
{
#ifdef _UNICODE
	//如果是unicode工程
	USES_CONVERSION;
	std::string str(W2A(cs));
	return str;
#else
	//如果是多字节工程 
	std::string str(cs.GetBuffer());
	cs.ReleaseBuffer();
	return str;
#endif
}

//String转CString
CString Utility::toCString(std::string str)
{
#ifdef _UNICODE
	//如果是unicode工程
	USES_CONVERSION; CString s(str.c_str());
	CString ans(str.c_str());
	return ans;
#else
	//如果是多字节工程
	CString ans;
	ans.Format("%s", str.c_str());
	return ans;
#endif 
}

CString Utility::AllocateImgName()
{
	char number[5];//编号长度为4，最后为‘\0’
	sprintf_s(number, "%04d", startIndex);//int格式化转换位string,注意最后不要有\n

	startIndex++;//增加，准备下次使用
	number[4] = '\0';//结束标志
	//存储到当前目录的子文件夹SavedImages
	std::string name = ".\\SavedImages\\Image_" + std::string(number) + ".jpg";//char * 转string，用构造函数

	return toCString(name);
}