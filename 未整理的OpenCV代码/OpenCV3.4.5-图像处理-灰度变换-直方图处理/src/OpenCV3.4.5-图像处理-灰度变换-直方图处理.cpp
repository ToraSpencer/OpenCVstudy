#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>


using namespace std;
using namespace cv;

//直接使用equalizeHist(src,dst)实现灰度图直方图均衡。
void test1()
{
	Mat src,dst,srchist,dsthist,srchistImage,dsthistImage;
	int dims = 1;
	int size = 256;
	int channels = 0;
	float hranges[] = {0,255};
	const float* ranges[] = {hranges};

	src = imread("/Users/wuhan/Downloads/lowContrastImage.jpg",0);
	cv::equalizeHist(src,dst);
	imshow("original image",src);
	imshow("histequalized image",dst);
	waitKey(0);
}

//直接使用equalizeHist( src, dst )实现彩色图片直方图均衡。
void test2()
{
	Mat obj = imread("/Users/wuhan/Downloads/setu.jpeg");
	Mat mat[3],dst;
	cv::split(obj,mat);
	cv::equalizeHist(mat[0],mat[0]);
	cv::equalizeHist(mat[1],mat[1]);
	cv::equalizeHist(mat[2],mat[2]);
	cv::merge(mat,3,dst);
	imshow("src",obj);
	imshow("dst",dst);
	waitKey(0);
}




int main()
{
	//test1();
	//test2();




	return 0;
}
