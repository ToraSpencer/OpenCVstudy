/*
 * 离散卷积的本质是滑动领域操作。
 *
*/

#define pi 3.14159

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace cv;

//一维滑动领域操作的底层实现
Mat sliding_block_1d(Mat src, Mat block)
{
	Mat dst;


	return dst;
}

//test1: 教学代码
void test1()
{
	 Mat srcImage = imread("lena.jpg");

	    //判断图像是否加载成功
	    if(srcImage.data)
	        cout << "图像加载成功!" << endl << endl;
	    else
	    {
	        cout << "图像加载失败!" << endl << endl;
	    }
	    namedWindow("srcImage", WINDOW_AUTOSIZE);
	    imshow("srcImage", srcImage);
	    waitKey(0);

	    Mat kern = (Mat_<char>(3,3) << 0, -1 ,0,
	                                   -1, 5, -1,
	                                   0, -1, 0);
	    Mat dstImage;
	    filter2D(srcImage,dstImage,srcImage.depth(),kern);
	    namedWindow("dstImage",WINDOW_AUTOSIZE);
	    imshow("dstImage",dstImage);
	    waitKey(0);


}

int main()
{

	uchar temp[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	uchar kernel[] = {1,2,3,4,5,6};
	Mat src = Mat(3,4,CV_8UC1,temp);
	Mat k = Mat(2,3,CV_8UC1,kernel);
	Mat dst;
	filter2D(src,dst,src.depth(),k);
	cout << "src = \n" << src << endl;
	cout << "k = \n" << k << endl;
	cout << "dst = \n" << dst << endl;




	return 0;
}
