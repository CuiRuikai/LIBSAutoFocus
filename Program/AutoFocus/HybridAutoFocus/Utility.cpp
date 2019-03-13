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
//从index开始比较清晰度，到size-1停止
int Utility::FindClearSection(std::vector<MyImg> imgVec, int & start, int & end)
{
	double max = 0;
	int maxIndex = 0;

	for (int i=0; i < imgVec.size(); i++)//迭代
	{
		if (imgVec[i].clarityScore > max)
		{
			max = imgVec[i].clarityScore;
			maxIndex = i;
		}
	}

	if (maxIndex == 0) {//Note:i会变，要用index,越界检查对鲁棒性很重要
		start = imgVec[maxIndex].position;
		end = imgVec[maxIndex + 1].position;
	}
	else if (maxIndex == imgVec.size() - 1) {
		start = imgVec[maxIndex - 1].position;
		end = imgVec[maxIndex].position;
	}
	else {
		start = imgVec[maxIndex - 1].position;
		end = imgVec[maxIndex + 1].position;
	}

	if (start < 0)
		start = 0;
	if (end > LENGTH_MAX)
		end = LENGTH_MAX;

	return end - start;//return the length of this section
}

int Utility::ployfitPos(std::vector<MyImg> imgVec)
{
	Fit fit;
	std::vector<double> x, y;
	int num = imgVec.size();
	x.resize(num);
	y.resize(num);
	for (int i = startIndex + 1; i < imgVec.size(); i++) {
		x[i] = imgVec[i].position;
		y[i] = imgVec[i].clarityScore;
	}

	int n = 3;
	fit.polyfit(x, y, n, true);

	double max = 0.0, focusedPos = 0.0;
	for (double i = imgVec[0].position; i < imgVec[imgVec.size() - 1].position; i++)
	{
		double y = fit.getY(i);
		if (y > max)
		{
			max = y;
			focusedPos = i;
		}
	}
	return focusedPos;
}

bool Utility::writeInfoToFile(std::vector<MyImg> imgVec)
{
	std::string pathName = ".\\SavedImages\\ImageInfo.txt";
	std::ofstream recordFile(pathName,std::ios::app);


	if (recordFile) 
	{
		recordFile << "Focus Round Info:" << std::endl;
		recordFile << "ImageName\t\t" << "Position\t" << "Score" << std::endl;
		for (int i = 0; i < imgVec.size(); i++)
		{
			recordFile << imgVec[i].imgName << "\t" << imgVec[i].position << "\t" << imgVec[i].clarityScore << std::endl;
		}
	}
	recordFile.close();//执行完操作后关闭文件句柄
	return true;
}
