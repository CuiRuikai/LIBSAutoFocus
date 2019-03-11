#include "stdafx.h"
#include "MyImg.h"


MyImg::MyImg()
{
}


MyImg::~MyImg()
{
}

//����ͼ������Ѱ��ͼ�󲢵��룬��¼ͼ��λ����Ϣ
MyImg::MyImg(std::string imgName, int pos)
{
	this->imgName = imgName;
	this->imgFile = cv::imread(this->imgName, -1);
	this->position = pos;
	this->clarityScore = calcClarityScore();
}

//����������
double MyImg::calcClarityScore()
{
	cv::Mat imageSource = cv::imread(imgName);
	cv::Mat imageGrey;

	cv::cvtColor(imageSource, imageGrey, CV_RGB2GRAY);
	cv::Mat meanValueImage;
	cv::Mat meanStdValueImage;

	//��Ҷ�ͼ��ı�׼��
	cv::meanStdDev(imageGrey, meanValueImage, meanStdValueImage);
	double meanValue = 0.0;
	meanValue = meanStdValueImage.at<double>(0, 0);
	double score = meanValue*meanValue;//����

	return score;
}