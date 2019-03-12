#pragma once
#include<string>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc.hpp>
#include <opencv2\imgproc\types_c.h>

class MyImg
{
public:
	int index;
	std::string imgName;//ͼ������
	cv::Mat imgFile;//�洢ͼ��ı���
	int position;//�������ڵ�λ��
	double clarityScore;//�����ȵ÷�

public:
	MyImg();
	~MyImg();
	//����ͼ������Ѱ��ͼ�󲢵��룬��¼ͼ��λ����Ϣ
	MyImg(std::string imgName, int pos,int index);
	int setPosition(int pos);
private:
	//����������
	double calcClarityScore();
};