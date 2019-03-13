#include "stdafx.h"
#include "Utility.h"


Utility::Utility()
	:startIndex(0)
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

CString Utility::AllocateImgName()
{
	char number[5];//��ų���Ϊ4�����Ϊ��\0��
	sprintf_s(number, "%04d", startIndex);//int��ʽ��ת��λstring,ע�����Ҫ��\n

	startIndex++;//���ӣ�׼���´�ʹ��
	number[4] = '\0';//������־
	//�洢����ǰĿ¼�����ļ���SavedImages
	std::string name = ".\\SavedImages\\Image_" + std::string(number) + ".jpg";//char * תstring���ù��캯��

	return toCString(name);
}
//��index��ʼ�Ƚ������ȣ���size-1ֹͣ
int Utility::FindClearSection(std::vector<MyImg> imgVec, int & start, int & end)
{
	double max = 0;
	int maxIndex = 0;

	for (int i=0; i < imgVec.size(); i++)//����
	{
		if (imgVec[i].clarityScore > max)
		{
			max = imgVec[i].clarityScore;
			maxIndex = i;
		}
	}

	if (maxIndex == 0) {//Note:i��䣬Ҫ��index,Խ�����³���Ժ���Ҫ
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
	recordFile.close();//ִ���������ر��ļ����
	return true;
}
