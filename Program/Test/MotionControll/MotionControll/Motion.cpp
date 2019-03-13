#include "stdafx.h"
#include "Motion.h"


Motion::Motion()
{
}


Motion::~Motion()
{
}

int Motion::MoveAndGrab(Motor motor, int stimCam, std::vector<MyImg>& ImgVec,int startPos,int endPos,int step)
{
	motor.moveToPosition(startPos);

	return 0;
}
