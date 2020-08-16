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

//全局变量声明
Mat g_srcImage, g_dstImage;	 	//原始图和效果图
int g_nTrackbarNumer = 0;		//0表示腐蚀erode, 1表示膨胀dilate
int g_nStructElementSize = 3; 	//结构元素(内核矩阵)的尺寸

//腐蚀和膨胀的综合处理函数
void Process()
{
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

	//进行腐蚀或膨胀操作
	if(g_nTrackbarNumer == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	//显示效果图
	imshow("【效果图】", g_dstImage);
}

//回调函数：腐蚀和膨胀之间切换开关的回调函数
void on_TrackbarNumChange(int, void *)
{
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

//回调函数：腐蚀和膨胀操作内核改变时的回调函数
void on_ElementSizeChange(int, void *)
{
	//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

//test1: 膨胀
void test1()
{
	Mat image = imread("/Users/wuhan/Downloads/GI_letters.bmp");  //工程目录下应该有一张名为1.jpg的素材图
	//创建窗口
	namedWindow("【原始图】膨胀");
	namedWindow("【效果图】膨胀");
	//显示原始图
	imshow("【原始图】膨胀", image);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作
	morphologyEx(image, image, MORPH_DILATE, element);
	//显示效果图
	imshow("【效果图】膨胀", image);

	waitKey(0);
}

//test2：形态学综合
void test2()
{
	g_srcImage = imread("/Users/wuhan/Downloads/GI_letters.bmp");
	namedWindow("original image");
	imshow("original image", g_srcImage);

	//进行初次腐蚀操作并显示效果图
	namedWindow("operated image");
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
	erode(g_srcImage, g_dstImage, element);
	imshow("operated image", g_dstImage);

	//创建轨迹条
	createTrackbar("erode/dilate switch", "operated image", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("kernel size", "operated image", &g_nStructElementSize, 21, on_ElementSizeChange);

	//输出一些帮助信息
	cout << "\t运行成功，请调整滚动条观察图像效果~\n\n\t按下“q”键时，程序退出。\n" << endl;

	//轮询获取按键信息，若下q键，程序退出
	while(char(waitKey(1)) != 'q') {}
}

//test3: 图像闭运算：先膨胀再腐蚀
void test3()
{
	//载入原始图
	Mat image = imread("/Users/wuhan/Downloads/GI_letters.bmp");  //工程目录下应该有一张名为1.jpg的素材图
	//创建窗口
	namedWindow("original");
	namedWindow("operated");
	//显示原始图
	imshow("original", image);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行闭运算操作
	morphologyEx(image, image, MORPH_CLOSE, element);
	//显示效果图
	imshow("operated", image);
	waitKey(0);
}

int main()
{
	//test1();
	//test2();
	test3();


	return 0;

}
