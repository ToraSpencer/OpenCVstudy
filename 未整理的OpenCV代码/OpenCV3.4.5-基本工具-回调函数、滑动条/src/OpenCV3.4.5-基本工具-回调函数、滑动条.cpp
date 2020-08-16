#include <opencv2/opencv.hpp>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;
using namespace cv;

//声明全局变量
int contrast; 					//对比度值
int bright; 					 //亮度值
Mat src,dst;

// 回调函数固定格式： static void onParameter(int parameter, void*)
// 		parameter为回调函数的输入，也是滑动条上滑块位置对应的数字，回调函数的输出即为窗口显示的结果。
static void onContrastAndBright(int, void *)
{

	// 创建窗口
	namedWindow("original image", 1);

	// 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for( int y = 0; y < src.rows; y++ )
	{
		for( int x = 0; x < src.cols; x++ )
		{
			for( int c = 0; c < 3; c++ )
			{
				dst.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((contrast*0.01)*( src.at<Vec3b>(y,x)[c] ) + bright );
			}
		}
	}

	// 显示图像
	imshow("original image", src);
	imshow("output image", dst);
}


int main(   )
{
	// 读入用户提供的图像
	src = imread("lena.jpg");
	if( !src.data ) { printf("读取g_srcImage图片错误~！ \n"); return -1; }
	dst = Mat::zeros( src.size(), src.type() );

	//设定对比度和亮度的初值
	contrast=80;
	bright=80;

	//创建窗口
	namedWindow("output image", 1);

	//创建滑动条
	createTrackbar("contrast: ", "output image", &contrast, 300,onContrastAndBright );
	createTrackbar("bright: ", "output image", &bright, 200,onContrastAndBright );

	//调用回调函数
	onContrastAndBright(contrast,0);
	onContrastAndBright(bright,0);


	cout << "\t运行成功，请调整滚动条观察图像效果\n\n\t按下“q”键时，程序退出\n" << endl;
		//按下“q”键时，程序退出
		while(char(waitKey(1)) != 'q') {}

	return 0;
}




