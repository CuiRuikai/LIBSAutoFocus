#include "stdafx.h"
#include "Motion.h"


Motion::Motion()
{
	InitializeCriticalSection(&m_csSaveImage);//初始化临界区
}

Motion::Motion(Motor &motor, HANDLE &hCam, MVImage &m_image, Utility &utility)
	:motor(motor),
	m_hCam(hCam),
	m_image(m_image),
	utility(utility)
{
	InitializeCriticalSection(&m_csSaveImage);//初始化临界区
}


Motion::~Motion()
{
}

//返回图像起始编号
int Motion::moveAndGrabImgs(int startPos, int stopPos, int step, std::vector<MyImg>& imgVec)
{
	int starIndex = utility.startIndex;//图像开始编号
	int stepLength = (stopPos - startPos) / step;//计算每次移动长度

	int pos = motor.moveToPosition(startPos);//移动到初始位置
	//停稳
	CTime t1 = CTime::GetCurrentTime();
	while ((CTime::GetCurrentTime() - t1) < 2);

	for (int i = 0; i < step + 1; i++)
	{
		//采集图像并存储
		CString imgName = utility.AllocateImgName();
		MVImage tImage;

		EnterCriticalSection(&m_csSaveImage);//进入临界区
		tImage.Create(m_image.GetWidth(), m_image.GetHeight(), m_image.GetBPP());
		memcpy(tImage.GetBits(), m_image.GetBits(), tImage.GetPitch()*tImage.GetHeight());
		LeaveCriticalSection(&m_csSaveImage);//退出临界区
		tImage.Save(imgName);

		tImage.Destroy();

		std::string strImgName = utility.toString(imgName);
		//存储到imgVec
		MyImg tImg(strImgName, pos);
		imgVec.push_back(tImg);

		//移向下一采样点
		pos = pos + stepLength;
		if (pos > LENGTH_MAX)
			pos = LENGTH_MAX;

		pos = motor.moveToPosition(pos);
		//停稳
		CTime t1 = CTime::GetCurrentTime();
		while ((CTime::GetCurrentTime() - t1) < 2);
	}
	return starIndex;
}