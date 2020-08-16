#include "cv.h"
#include "highgui.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
using namespace cv;

//类定义位置：core/include/opencv2/core.hpp


//test1():使用RNG对象产生随机数
void test1()
{
	cout << "test1():使用RNG对象产生随机数" << endl << endl;

	RNG rng;

	cout << "产生0到10之间离散均匀分布的随机int" << rng.uniform(0,10) << endl;
	cout << "产生0到1之间连续均匀分布的随机double：" << rng.uniform(0.0,1.0) << endl;


	cout << endl;

}

//test2():使用RNG对象产生的随机数填充矩阵
void test2()
{
	cout << "使用RNG对象产生的随机数填充矩阵：" << endl << endl;

	RNG rng;

	Mat_<double> M = Mat_<double>::zeros(5,5);
	rng.fill(M, RNG::UNIFORM, 0, 1000);
	cout << "M =\n" << M << endl;

	cout << endl;
}

int main(int argc, char** argv)
{
	test1();
	test2();

    return 0;
}
