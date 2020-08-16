#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
using namespace std;
using namespace cv;

//全局变量声明：
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;//存储图片的Mat类型
int g_nBoxFilterValue=3;  //方框滤波参数值
int g_nMeanBlurValue=3;  //均值滤波参数值
int g_nGaussianBlurValue=3;  //高斯滤波参数值


//自定义全局函数：
//		on_BoxFilter( )：方框滤波操作的回调函数
static void on_BoxFilter(int, void *)
{
	//方框滤波操作
	boxFilter( g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	//显示窗口
	imshow("【<1>方框滤波】", g_dstImage1);
}

//		on_MeanBlur( )：均值滤波操作的回调函数
static void on_MeanBlur(int, void *)
{
	//均值滤波操作
	blur( g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1,-1));
	//显示窗口
	imshow("【<2>均值滤波】", g_dstImage2);
}

//		ContrastAndBright( )：高斯滤波操作的回调函数
static void on_GaussianBlur(int, void *)
{
	//高斯滤波操作
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), 0, 0);
	//显示窗口
	imshow("【<3>高斯滤波】", g_dstImage3);
}





//test1: blur()
void test1()
{
	//【1】载入原始图
	Mat srcImage=imread("lena.jpg");

	//【2】显示原始图
	imshow( "均值滤波【原图】", srcImage );
	waitKey(0);

	//【3】进行均值滤波操作
	Mat dstImage;
	blur( srcImage, dstImage, Size(7, 7));

	imshow( "均值滤波【效果图】" ,dstImage );

	waitKey( 0 );
}

//test2: BoxFilter()
void test2()
{
	// 载入原图
	Mat image=imread("lena.jpg");

	//创建窗口
	namedWindow( "方框滤波【原图】" );
	namedWindow( "方框滤波【效果图】");

	//显示原图
	imshow( "方框滤波【原图】", image );
	waitKey(0);

	//进行方框滤波操作
	Mat out;
	boxFilter( image, out, -1,Size(5, 5));

	//显示效果图
	imshow( "方框滤波【效果图】" ,out );

	waitKey( 0 );


}

//test3: GaussianBlur()
void test3()
{	// 载入原图
	Mat image=imread("1.jpg");

	//创建窗口
	namedWindow( "高斯滤波【原图】" );
	namedWindow( "高斯滤波【效果图】");

	//显示原图
	imshow( "高斯滤波【原图】", image );

	//进行高斯滤波操作
	Mat out;
	GaussianBlur( image, out, Size( 5, 5 ), 0, 0 );

	//显示效果图
	imshow( "高斯滤波【效果图】" ,out );

	waitKey( 0 );

}

//test4: 一堆线性滤波的实例：
void test4()
{
	//改变console字体颜色
		system("color 5F");

		// 载入原图
		g_srcImage = imread( "1.jpg", 1 );

		//克隆原图到三个Mat类型中
		g_dstImage1 = g_srcImage.clone( );
		g_dstImage2 = g_srcImage.clone( );
		g_dstImage3 = g_srcImage.clone( );

		//显示原图
		namedWindow("【<0>原图窗口】", 1);
		imshow("【<0>原图窗口】",g_srcImage);


		//=================【<1>方框滤波】==================
		//创建窗口
		namedWindow("【<1>方框滤波】", 1);
		//创建轨迹条
		createTrackbar("内核值：", "【<1>方框滤波】", &g_nBoxFilterValue, 40, on_BoxFilter);
		on_BoxFilter(g_nBoxFilterValue, 0);
		//================================================

		//=================【<2>均值滤波】==================
		//创建窗口
		namedWindow("【<2>均值滤波】", 1);
		//创建轨迹条
		createTrackbar("内核值：", "【<2>均值滤波】",&g_nMeanBlurValue, 40,on_MeanBlur );
		on_MeanBlur(g_nMeanBlurValue,0);
		//================================================

		//=================【<3>高斯滤波】=====================
		//创建窗口
		namedWindow("【<3>高斯滤波】", 1);
		//创建轨迹条
		createTrackbar("内核值：", "【<3>高斯滤波】",&g_nGaussianBlurValue, 40,on_GaussianBlur );
		on_GaussianBlur(g_nGaussianBlurValue,0);
		//================================================


		//输出一些帮助信息
		cout <<"\t运行成功，请调整滚动条观察图像效果~\n\n \t按下“q”键时，程序退出。\n" << endl;

		//按下“q”键时，程序退出
		while(char(waitKey(1)) != 'q') {}

}

//test5: medianBlur()中值滤波
void test5()
{
	// 载入原图
		Mat image=imread("1.jpg");

		//创建窗口
		namedWindow( "中值滤波【原图】" );
		namedWindow( "中值滤波【效果图】");

		//显示原图
		imshow( "中值滤波【原图】", image );

		//进行中值滤波操作
		Mat out;
		medianBlur ( image, out, 7);

		//显示效果图
		imshow( "中值滤波【效果图】" ,out );

		waitKey( 0 );

}

//test6: 双边滤波bilateralFilter()
void test6()
{// 载入原图
	Mat image=imread("1.jpg");

	//创建窗口
	namedWindow( "双边滤波【原图】" );
	namedWindow( "双边滤波【效果图】");

	//显示原图
	imshow( "双边滤波【原图】", image );

	//进行双边滤波操作
	Mat out;
	bilateralFilter ( image, out, 25, 25*2, 25/2 );

	//显示效果图
	imshow( "双边滤波【效果图】" ,out );

	waitKey( 0 );


}

//test7: 微分滤波
void test7()
{
	//载入原始图
	Mat srcImage = imread("lena.jpg");
	Mat srcImage1=srcImage.clone();
	imshow("original", srcImage);

	//转成灰度图，降噪，用canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，得到彩色的边缘图
	Mat dstImage,edge,grayImage;

	// 【1】创建与src同类型和大小的矩阵(dst)
	dstImage.create( srcImage1.size(), srcImage1.type() );
	// 【2】将原图像转换为灰度图像
	cvtColor( srcImage1, grayImage, COLOR_BGR2GRAY );
	// 【3】先用使用 3x3内核来降噪
	blur( grayImage, edge, Size(3,3) );
	// 【4】运行Canny算子
	Canny( edge, edge, 3, 9,3 );
	//【5】将g_dstImage内的所有元素设置为0
	dstImage = Scalar::all(0);
	//【6】使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷到目标图g_dstImage中
	srcImage1.copyTo( dstImage, edge);
	//【7】显示效果图
	imshow("operated", dstImage);
	waitKey(0);


}

int main()
{
	//test1();
	//test2();
	test7();


	return 0;
}
