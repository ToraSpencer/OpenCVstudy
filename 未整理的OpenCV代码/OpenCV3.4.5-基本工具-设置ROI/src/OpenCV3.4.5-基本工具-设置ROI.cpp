#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


// 设置图片的ROI区域，然后在该区域中覆盖上一个小logo图片。
void test1()
{
	Mat src = imread("lena.jpg");
	Mat logo = imread("/Users/wuhan/Downloads/GI_letters.bmp");
	Mat ROI,dst;
	if(!src.data)
	{
		printf("src is empty!",0);
		return;
	}
	if(!logo.data)
	{
		printf("logo is empty!",0);
		return;
	}

	// 定义一个Mat变量，设置为src图片中的感兴趣区域ROI；
	ROI = src(Rect(0,0,logo.rows,logo.cols));				// 用Rect()函数限定矩阵中的某一块矩形区域。
		//Mat ROI = src(Range(0,0+logo.rows),Range(0,0+logo.cols));			// 用Range()函数限定矩阵中的某一块矩形区域。

	// 将logo图片拷贝到ROI区域中，替换原有的数据。
	logo.copyTo(ROI);
	src.copyTo(dst);

	imshow("dst",dst);
	waitKey(0);


}


int main()
{
	test1();

	return 0;
}
