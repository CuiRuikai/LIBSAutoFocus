#pragma once
#include"Motor.h"
#include "MVGigE.h" 
#include "MVImage.h" 
#include"Utility.h"

class Motion
{
public:
	Motion();
	~Motion();
public:
	int MoveAndGrab(Motor motor, int stimCam, std::vector<MyImg> &ImgVec, int startPos, int endPos, int step);
};

