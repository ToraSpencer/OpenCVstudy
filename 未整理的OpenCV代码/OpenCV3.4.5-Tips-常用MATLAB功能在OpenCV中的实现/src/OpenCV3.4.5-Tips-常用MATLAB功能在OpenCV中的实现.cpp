#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

// 比较运算符作用于矩阵，返回元素为0、1的逻辑矩阵。
void test1()
{
	// 单通道矩阵和数（标量）做比较，返回0、1构成的矩阵
	Mat src, dst;

	double arr[] = {1,2,3,4,5,6,7,8,9};
	src = Mat(3,3,CV_64FC1,arr);

	dst = src>5;						// dst元素类型为uchar，满足表达式的元素都变成255，不满足的变成0；
	dst.convertTo(dst,CV_64FC1);		// 元素类型转换为double；
	dst = dst/255;

	cout << "dst = \n" << dst << endl;








}


int main()
{
	test1();


	return 0;
}
