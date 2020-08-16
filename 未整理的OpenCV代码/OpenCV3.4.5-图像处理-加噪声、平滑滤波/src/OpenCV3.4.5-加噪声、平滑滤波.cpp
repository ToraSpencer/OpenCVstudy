/*
*/

#define pi 3.14159

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>
#include <random>

using namespace std;
using namespace cv;

//产生高斯噪声的函数：
double generateGaussianNoise(double mu, double sigma)
{
	//定义小值
	const double epsilon = numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假构造高斯随机变量X
	if (!flag)
		return z1 * sigma + mu;

	double u1, u2;
	//构造随机变量
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	}
	while (u1 <= epsilon);
	//flag为真构造高斯随机变量
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
	return z0*sigma + mu;
}



//test1:图片加噪声：
void test1()
{
	cout << "test1:图片加噪声：" << endl << endl;
	Mat src = imread("lena.jpg");
	imshow("原图",src);
	waitKey(0);

	cout << "添加高斯噪声：" << endl;
	Mat dst = src.clone();
		int channels = dst.channels();
		int rowsNumber = dst.rows;
		int colsNumber = dst.cols*channels;
		//？？？判断图像的连续性
		if (dst.isContinuous())
		{
			colsNumber *= rowsNumber;
			rowsNumber = 1;
		}
		for (int i = 0; i < rowsNumber; i++)
		{
			for (int j = 0; j < colsNumber; j++)
			{
				//添加高斯噪声
				int val = dst.ptr<uchar>(i)[j] +
					generateGaussianNoise(2, 0.8) * 32;
				if (val < 0)
					val = 0;
				if (val>255)
					val = 255;
				dst.ptr<uchar>(i)[j] = (uchar)val;
			}
		}
    imshow("高斯噪声污染的图片",dst);
    waitKey(0);

}



//test2：算数均值滤波：
void test2()
{
	Mat src = imread("lena.jpg");


	cout << "src.channels() = " << src.channels() << endl;
	cout << "src.depth() = " << src.depth() << endl;
	imshow("original image",src);
	waitKey(0);


	cout << "添加高斯噪声：" << endl;
	Mat dst = src.clone();
		int channels = dst.channels();
		int rowsNumber = dst.rows;
		int colsNumber = dst.cols*channels;
		//？？？判断图像的连续性
		if (dst.isContinuous())
		{
			colsNumber *= rowsNumber;
			rowsNumber = 1;
		}
		for (int i = 0; i < rowsNumber; i++)
		{
			for (int j = 0; j < colsNumber; j++)
			{
				//添加高斯噪声
				int val = dst.ptr<uchar>(i)[j] +
					generateGaussianNoise(2, 0.8) * 32;
				if (val < 0)
					val = 0;
				if (val>255)
					val = 255;
				dst.ptr<uchar>(i)[j] = (uchar)val;
			}
		}

	imshow("added gaussian noise",dst);
	waitKey(0);


	cout << "boxFilter()实现的算数均值滤波：" << endl;
	Mat dst_box;
	boxFilter( dst, dst_box, -1,Size(5, 5));
	imshow("filtered by boxFilter()",dst_box);
	waitKey(0);


	cout << "blur()函数实现的均值滤波" << endl;
	Mat dst_blur;
	blur( dst, dst_blur, Size(7, 7));
	imshow("filtered by blur()",dst_blur);
	waitKey(0);


	cout << "filter2D()普适滑动邻域操作实现的均值滤波" << endl;
	/*
		普适滑动领域操作，即二维离散卷积
		void cv::filter2D	(src,dst,
						int 	ddepth,
						InputArray 	kernel,
						Point 	anchor = Point(-1,-1),
						double 	delta = 0,
						int 	borderType = BORDER_DEFAULT)
	*/
	Mat dst_fil;
	Mat kernel = Mat::ones(5,5,CV_8UC1);
	kernel = (Mat_<double>)kernel;
	kernel = kernel/25;
	filter2D(dst,dst_fil,src.depth(),kernel);
	imshow("filtered by filter2D()", dst_fil);
	waitKey(0);
}



int main()
{
	//test1();
	test2();



    return 0;
}
