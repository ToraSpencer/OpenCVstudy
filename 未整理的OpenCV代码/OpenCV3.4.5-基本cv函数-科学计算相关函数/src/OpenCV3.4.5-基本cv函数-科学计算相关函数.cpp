#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


using namespace std;
using namespace cv;


// randu()————矩阵元素随机化
// void cv::randu(src, InputArray low, InputArray high)

// sum()————矩阵按通道求所有元素的和
// Scalar cv::sum(src)

// mean()————矩阵按通道求所有元素的均值
// Scalar cv::mean(src, InputArray mask = noArray())

// reduce()——矩阵按行/列求：和、均值、最值
//
void test1()
{
	Mat m(3,4,CV_64FC3), result;
	randu(m,0,1);

	cout <<"m = \n" <<  m << endl;
	cout << "sum(m) = " << sum(m) << endl;
	cout << "mean(m)" << mean(m) << endl;

	reduce(m, result, 1, CV_REDUCE_MAX);
	cout << "每行最大值为：\n" << result << endl;

}





int main()
{
	test1();


	return 0;

}
