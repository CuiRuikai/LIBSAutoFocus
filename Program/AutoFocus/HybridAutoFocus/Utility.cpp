#include "stdafx.h"
#include "Utility.h"


Utility::Utility()
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

CString Utility::AllocateImgName(int startIndex, std::vector<MyImg>& ImgVec)
{
	char number[5];//编号长度为4，最后为‘\0’
	sprintf_s(number, "%04d", startIndex);//int格式化转换位string,注意最后不要有\n
	number[4] = '\0';//结束标志
					 //存储到当前目录的子文件夹SavedImages
	std::string name = ".\\SavedImages\\Image_" + std::string(number) + ".jpg";//char * 转string，用构造函数

	MyImg temp;//临时存储信息的变
	temp.index = startIndex;//编号
	temp.imgName = name;//名字

	ImgVec.push_back(temp);//存入vector

	return toCString(ImgVec.back().imgName);//返回图片名称
	return CString();
}



/*
 *图片名称分配函数
 *Note:需要使用引用
 */
//CString Utility::AllocateImgName(int position,int startIndex,std::vector<MyImg> &ImgVec)
//{
//	char number[5];//编号长度为4，最后为‘\0’
//	sprintf_s(number, "%04d", startIndex);//int格式化转换位string,注意最后不要有\n
//	number[4] = '\0';//结束标志
//					 //存储到当前目录的子文件夹SavedImages
//	std::string name = ".\\SavedImages\\Image_" + std::string(number) + ".jpg";//char * 转string，用构造函数
//
//	MyImg temp;//临时存储信息的变
//	temp.index = startIndex;//编号
//	temp.imgName = name;//名字
//	temp.position = position;
//
//	ImgVec.push_back(temp);//存入vector
//
//	return toCString(ImgVec.back().imgName);//返回图片名称
//}
