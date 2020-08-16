#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define eps 1e-10					//定义非常小的一个量epsilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


 
/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
int contrast; 					    //对比度值
int bright; 					     //亮度值
Mat src,dst;





/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
static void onContrastAndBright(int, void *);               // 回调函数：调节亮度、对比度

void set_fun_basicOperation_trackbar(void);
void start_basicOperation_trackbar(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);



/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 函数定义

static void onContrastAndBright(int, void *)
{
// 回调函数固定格式： static void onParameter(int, void*)
// 		int parameter为回调函数的输入，也是滑动条上滑块位置对应的数字，回调函数的输出即为窗口显示的结果。

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


void set_fun_basicOperation_trackbar(void)
{
	pfun[0] = test0;

}


void start_basicOperation_trackbar(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: 基本操作、工具——滑动条**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0：使用滑动条调节图片的亮度、对比度" << endl;


		inputTag = scanf("%d", &inputNum);


		// 若输入值不是整数，重新输入。
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// 对三级界面输入值的响应。
		switch (inputNum)
		{
		case -2:
			traverse_pfun();
			break;

		case -1:
			interfaceLevel = 2;
			break;

		case 0:
			(*pfun[0])();
			break;


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: 使用滑动条调节图片的亮度、对比度。
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: 使用滑动条调节图片的亮度、对比度" << endl;

    // 读入用户提供的图像
	src = imread("image/lena.jpg");
	//if( !src.data ) { printf("读取g_srcImage图片错误~！ \n"); return -1; }
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
 
	

}
