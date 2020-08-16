#include <opencv2/opencv.hpp>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;
using namespace cv;

//声明全局函数：
//
static void ContrastAndBright(int, void *);


//声明全局变量
int contrast; 					//对比度值
int bright; 					 //亮度值
Mat g_srcImage,g_dstImage;


int main(   )
{
	// 读入用户提供的图像
	g_srcImage = imread("lena.jpg");
	if( !g_srcImage.data ) { printf("读取g_srcImage图片错误~！ \n"); return false; }
	g_dstImage = Mat::zeros( g_srcImage.size(), g_srcImage.type() );

	//设定对比度和亮度的初值
	contrast=80;
	bright=80;

	//创建窗口
	namedWindow("output image", 1);

	//创建轨迹条
	createTrackbar("contrast: ", "output image",&contrast, 300,ContrastAndBright );
	createTrackbar("bright: ", "output image",&bright, 200,ContrastAndBright );

	//调用回调函数
	ContrastAndBright(contrast,0);
	ContrastAndBright(bright,0);

	//输出一些帮助信息
	cout << "\t运行成功，请调整滚动条观察图像效果\n\n\t按下“q”键时，程序退出\n" << endl;

		//按下“q”键时，程序退出
		while(char(waitKey(1)) != 'q') {}

	return 0;
}


static void ContrastAndBright(int, void *)
{

	// 创建窗口
	namedWindow("original image", 1);

	// 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for( int y = 0; y < g_srcImage.rows; y++ )
	{
		for( int x = 0; x < g_srcImage.cols; x++ )
		{
			for( int c = 0; c < 3; c++ )
			{
				g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (contrast*0.01)*( g_srcImage.at<Vec3b>(y,x)[c] ) + bright );
			}
		}
	}

	// 显示图像
	imshow("original image", g_srcImage);
	imshow("output image", g_dstImage);
}


