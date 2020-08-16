#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

//test1：
void test1()
{
	cout << "" << endl << endl;
	Mat_<double> ones = Mat_<double>::ones(2,3);
	MatSize size1((int*)NULL);
	size1 = ones.size;
	cout << "" << size1 << endl;
}

//test2:
void test2()
{
}


int main(int argc, char** argv)
{
	test1();
	//test2();

    return 0;
}
