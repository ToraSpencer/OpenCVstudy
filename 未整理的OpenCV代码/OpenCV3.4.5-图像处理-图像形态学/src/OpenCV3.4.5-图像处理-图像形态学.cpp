#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace cv;

//全局变量声明
Mat src,dst;
int switchFlag = 0;		// 确定操作是腐蚀还是膨胀的整数，注意回调函数不能传布尔量，只能传整形
int kernelSize = 0; 	// 结构元素(内核矩阵)的尺寸



//回调函数：动态调节：1.形态学滤波核尺寸；2.选择执行膨胀或腐蚀的开关。
void onSwitchFlagAndKernelSize(int, void *)
{
	// 根据传入的核尺寸参数，生成形态学滤波核
	Mat kernel = getStructuringElement(MORPH_RECT,Size(2*kernelSize+1, 2*kernelSize+1));

	// 根据传入的选择参数，执行相应的形态学滤波操作：
	if(switchFlag==0)		// 执行腐蚀
	{erode(src,dst,kernel);}
	else					// 执行膨胀
	{dilate(src,dst,kernel);}

	// 显示输出图像：
	imshow("operated image", dst);
}

//test1: 图像膨胀/膨胀
void test1()
{
	src = imread("/Users/wuhan/Downloads/GI_letters.bmp");
	dst = Mat::zeros(src.size(),src.type());

	// 生成输出窗口
	namedWindow("operated image");

	// 创建滑动条
	createTrackbar("switchFlag", "operated image", &switchFlag, 1, onSwitchFlagAndKernelSize);
	createTrackbar("kernelSize", "operated image", &kernelSize, 10, onSwitchFlagAndKernelSize);

	// 调用回调函数：有两个动态调节参数，所以要分别调用两次。
	onSwitchFlagAndKernelSize(switchFlag, 0);
	onSwitchFlagAndKernelSize(kernelSize, 0);

	waitKey(0);
}





// 全局变量声明
int morphType = 0;

// 回调函数：动态调节：1.形态学滤波核尺寸；2.选择执行八种形态学操作的整数。
void onMorphTypeAndKernelSize(int, void*)
{
	// 根据传入的核尺寸参数，生成形态学滤波核
	Mat kernel = getStructuringElement(MORPH_RECT,Size(2*kernelSize+1,2*kernelSize+1));

	// 根据传入的选择参数，执行相应的形态学滤波操作。
	morphologyEx(src, dst, morphType, kernel);

	// 显示输出图像：
	imshow("operated image", dst);
}

/* test2: 使用morphologyEx()执行任意形态学滤波：
 * 				形态学操作枚举常量：
 * 						int op == { MORPH_ERODE == 0,		腐蚀
 * 									MORPH_DILATE == 1,		膨胀
 * 									MORPH_OPEN == 2,		开运算，先腐蚀再膨胀。open(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)=dilate(erode(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝))
 * 									MORPH_CLOSE == 3,		闭运算，先膨胀再腐蚀。close(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)=erode(dilate(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝))
 * 									MORPH_GRADIENT == 4,	形态学梯度，morph_grad(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝) 	=dilate(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)−erode(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)
 * 									MORPH_TOPHAT == 5, 		顶帽操作，tophat(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)=𝚜𝚛𝚌−open(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)
 * 									MORPH_BLACKHAT == 6, 	黑帽操作，𝚍𝚜𝚝=blackhat(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)=close(𝚜𝚛𝚌,𝚎𝚕𝚎𝚖𝚎𝚗𝚝)−𝚜𝚛𝚌
 * 									MORPH_HITMISS == 7,
										}
 */

void test2()
{
	src = imread("/Users/wuhan/Downloads/GI_letters.bmp");
	dst = Mat::zeros(src.size(),src.type());

	// 生成输出窗口
	namedWindow("operated image");

	// 创建滑动条
	createTrackbar("morphType", "operated image", &morphType, 7, onMorphTypeAndKernelSize);
	createTrackbar("kernelSize", "operated image", &kernelSize, 10, onMorphTypeAndKernelSize);

	// 调用回调函数：有两个动态调节参数，所以要分别调用两次。
	onMorphTypeAndKernelSize(morphType, 0);
	onMorphTypeAndKernelSize(kernelSize, 0);

	waitKey(0);

}





int main()
{
	//test1();
	test2();



	return 0;
}
