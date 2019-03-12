// MotionControll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"MyImg.h"
#include"Utility.h"

using namespace std;

int main()
{
	Utility utility;
	vector<MyImg> imgVec;
	int index = 0;
	for (int i = index; i < 5; i++) {
		CString name = utility.AllocateImgName(i, i * 1000, imgVec);
		string sname = utility.toString(name);
		cout << sname << endl;
	}

    return 0;
}

