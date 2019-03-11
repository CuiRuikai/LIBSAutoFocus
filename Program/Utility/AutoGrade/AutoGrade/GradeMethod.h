#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

class GradeMethod
{
public:
	GradeMethod();
	~GradeMethod();
public:
	vector<double> meanValueMethod(int startIndex, int endIndex, string imgType) {
		vector<double> vec;
		int i = startIndex;
		while (i <= endIndex)
		{
			stringstream ss;//int转string
			ss << i;
			string s1 = ss.str();
			std::string s;
			if (i++ < 10) {//控制格式
				s = ".\\Pics\\Image_000" + s1 + imgType;
			}
			else {
				s = ".\\Pics\\Image_00" + s1 + imgType;
			}
			Mat imageSource = imread(s);
			Mat imageGrey;

			cvtColor(imageSource, imageGrey, CV_RGB2GRAY);
			Mat meanValueImage;
			Mat meanStdValueImage;

			//求灰度图像的标准差
			meanStdDev(imageGrey, meanValueImage, meanStdValueImage);
			double meanValue = 0.0;
			meanValue = meanStdValueImage.at<double>(0, 0);

			//double to string
			stringstream meanValueStream;
			string meanValueString;
			meanValueStream << meanValue*meanValue;
			meanValueStream >> meanValueString;

			vec.push_back(meanValue*meanValue);
		}
		return vec;
	}
};

