#include<iostream>
#include"GradeMethod.h"

using namespace std;
using namespace cv;

int main()
{
	GradeMethod instance;

	vector<double> vec = instance.meanValueMethod(1, 26, ".bmp");

	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;
	return 0;
}
