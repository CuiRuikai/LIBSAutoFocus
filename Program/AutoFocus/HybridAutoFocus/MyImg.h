#pragma once
#include<string>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc.hpp>
#include <opencv2\imgproc\types_c.h>

class MyImg
{
public:
	int index;
	std::string imgName;//图像名称
	cv::Mat imgFile;//存储图像的变量
	int position;//拍摄所在的位置
	double clarityScore;//清晰度得分

public:
	MyImg();
	~MyImg();
	//根据图像名，寻找图象并导入，记录图像位置信息
	MyImg(std::string imgName, int pos,int index);
	int setPosition(int pos);
private:
	//计算清晰度
	double calcClarityScore();
};