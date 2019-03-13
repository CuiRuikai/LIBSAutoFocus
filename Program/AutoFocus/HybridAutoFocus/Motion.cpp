#include "stdafx.h"
#include "Motion.h"


Motion::Motion()
{
	InitializeCriticalSection(&m_csSaveImage);//��ʼ���ٽ���
}

Motion::Motion(Motor &motor, HANDLE &hCam, MVImage &m_image, Utility &utility)
	:motor(motor),
	m_hCam(hCam),
	m_image(m_image),
	utility(utility)
{
	InitializeCriticalSection(&m_csSaveImage);//��ʼ���ٽ���
}


Motion::~Motion()
{
}

//����ͼ����ʼ���
int Motion::moveAndGrabImgs(int startPos, int stopPos, int step, std::vector<MyImg>& imgVec)
{
	int starIndex = utility.startIndex;//ͼ��ʼ���
	int stepLength = (stopPos - startPos) / step;//����ÿ���ƶ�����

	int pos = motor.moveToPosition(startPos);//�ƶ�����ʼλ��
	//ͣ��
	CTime t1 = CTime::GetCurrentTime();
	while ((CTime::GetCurrentTime() - t1) < 2);

	for (int i = 0; i < step + 1; i++)
	{
		//�ɼ�ͼ�񲢴洢
		CString imgName = utility.AllocateImgName();
		MVImage tImage;

		EnterCriticalSection(&m_csSaveImage);//�����ٽ���
		tImage.Create(m_image.GetWidth(), m_image.GetHeight(), m_image.GetBPP());
		memcpy(tImage.GetBits(), m_image.GetBits(), tImage.GetPitch()*tImage.GetHeight());
		LeaveCriticalSection(&m_csSaveImage);//�˳��ٽ���
		tImage.Save(imgName);

		tImage.Destroy();

		std::string strImgName = utility.toString(imgName);
		//�洢��imgVec
		MyImg tImg(strImgName, pos);
		imgVec.push_back(tImg);

		//������һ������
		pos = pos + stepLength;
		if (pos > LENGTH_MAX)
			pos = LENGTH_MAX;

		pos = motor.moveToPosition(pos);
		//ͣ��
		CTime t1 = CTime::GetCurrentTime();
		while ((CTime::GetCurrentTime() - t1) < 2);
	}
	return starIndex;
}