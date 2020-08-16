#include "cv.h"
#include "highgui.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

//test1()：显示图像基本信息。
void test1(Mat& lena)
{
	cout << "显示图像基本信息：" << endl << endl;

	cout << "图像的尺寸为：" << lena.size << endl;
	cout << "图像通道数为：" << lena.channels() << endl;
	cout << "图像一个通道的位深：" << 8*lena.elemSize1() << endl;
	cout << "图像为3通道256色RGB图像。" << endl;

	imshow("lena",lena);
	waitKey(0);
	cout << endl;

}

//test2():color reduce:减少图像颜色数。256色变为64色
void test2(Mat& lena, int div = 64)
{
	cout << "test2():color reduce:减少图像位深。将每通道色彩数由256减少到256/8 = 32。" << endl << endl;

	int nr= lena.rows;
	int nc= lena.cols * lena.channels();			//每行的总元素数。
	for (int j=0; j<nr; j++)
	{
		uchar* data= lena.ptr<uchar>(j); 			//.ptr返回第i行的首地址
	    for (int i=0; i<nc; i++) {*data++= *data/div*div + div/2;}
	}
	cout << "图像每通道的位深" << 8*lena.elemSize1() << endl;

}

//test3():图像通道分离、融合
void test3(Mat& lena)
{
	cout << "test3():图像通道分离" << endl;

	Mat lena_sc[3];
	split(lena,lena_sc);

	Mat& blue_lena = lena_sc[0];
	Mat& green_lena = lena_sc[1];
	Mat& red_lena = lena_sc[2];

	Mat lena_merged;
	vector<Mat> v;
	v.push_back(blue_lena);
	v.push_back(green_lena);
	v.push_back(red_lena);

	merge(v,lena_merged);

	imshow("original lena",lena);
	waitKey(0);
	imshow("blue lena",blue_lena);
	waitKey(0);
	imshow("green lena",green_lena);
	waitKey(0);
	imshow("red lena",red_lena);
	waitKey(0);
	imshow("lena merged",lena_merged);
	waitKey(0);

	cout << "lena.type() = " << lena.type() << endl;
	cout << "lena_merged.type() = " << lena_merged.type() << endl;
}

//test4()：
void test4()
{
}


//test5():图像边界扩张——copyMakeBorder()
void test5(Mat& lena)
{
	cout << "test5():图像边界扩张——copyMakeBorder()" << endl;
	cout << "单通道图像边界扩张，延扩部分补0。将600✖551的lena图扩张到700✖700" << endl;
	vector<Mat> v;
	split(lena,v);
	Mat& blue_lena = v[0];
	Mat blue_lena_extended(lena.rows,lena.cols,CV_8UC1);
	int bottom_extended = 700-lena.rows;
	int right_extended = 700-lena.cols;

	copyMakeBorder(blue_lena,blue_lena_extended,0,bottom_extended,0,right_extended,BORDER_CONSTANT, Scalar::all(0));
	imshow("blue lena extended",blue_lena_extended);
	waitKey(0);







	cout << endl;
}

int main(int argc, char** argv)
{
	Mat lena = imread("lena.jpg");

	//test1(lena);
	//test2(lena);
	test3(lena);
	//test4()
	//test5(lena);

    return 0;
}
