#include "stdafx.h"
#include "MyImg.h"


MyImg::MyImg()
{
}


MyImg::~MyImg()
{
}

//根据图像名，寻找图象并导入，记录图像位置信息
MyImg::MyImg(std::string imgName, int pos)
{
	this->imgName = imgName;
	this->imgFile = cv::imread(this->imgName, -1);
	this->position = pos;
	this->clarityScore = calcClarityScore();
}

//计算清晰度
double MyImg::calcClarityScore()
{
	cv::Mat imageSource = cv::imread(imgName);
	cv::Mat imageGrey;

	cv::cvtColor(imageSource, imageGrey, CV_RGB2GRAY);
	cv::Mat meanValueImage;
	cv::Mat meanStdValueImage;

	//求灰度图像的标准差
	cv::meanStdDev(imageGrey, meanValueImage, meanStdValueImage);
	double meanValue = 0.0;
	meanValue = meanStdValueImage.at<double>(0, 0);
	double score = meanValue*meanValue;//方差

	return score;
}