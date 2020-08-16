/*
*/


#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace cv;

//声明全局变量
Mat src;
Mat dst;
int alpha; 					//亮度缩放因子。

//亮度缩放的回调函数
void on_brightnessZoom(int, void*)
{
	double beta = double(alpha)/100.0;
	src.convertTo(dst, src.type(), beta);
	imshow("opeated image",dst);
	cout << "当前亮度缩放" << alpha << "%" << endl;
}

//test1: convertTo()实现的亮度缩放。
void test1()
{
	cout << "test1: convertTo()实现的亮度缩放。" << endl << endl;
	src = imread("lena.jpg");

	namedWindow("original image");
	imshow("original image", src);

	namedWindow("operated image");
	createTrackbar("brightness zoom", "operated image", &alpha, 200, on_brightnessZoom);
	on_brightnessZoom(100,nullptr);

	while(char(waitKey(1)) != 'q') {}				//按下q键退出窗口。

}

int main()
{
	test1();

	return 0;
}
