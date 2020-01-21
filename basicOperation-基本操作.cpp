#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define eps 1e-10					//定义非常小的一个量epsilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// imread——读取图片
/*. BC------------------------------------------------------------------------
**	imread——读取图片
**
**	描述：
**			Mat cv::imread	(const String & 	filename,
**							int 	flags = IMREAD_COLOR )
**
**
**	输入参数：
**			const String & 	filename：文件路径
**			int flags = IMREAD_COLOR：读取模式
**					flags整数值对应着ImreadModes中的枚举常量，决定以不同的模式来提取图片文件的数据保存到Mat对象中。
**					默认取IMREAD_COLOR枚举常量，其值为1，即将图像数据保存为三通道RBG矩阵。
**
**	输出参数：
**			Mat： 保存了图片数据的Mat矩阵对象。
**
**
*. EC------------------------------------------------------------------------
*/
 

/***************************************************************************
***************************************************************************/
// 全局变量、类型定义





/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_basicOperation_basic(void);
void start_basicOperation_basic(void);
static void test0(void);



/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_basicOperation_basic(void)
{
	pfun[0] = test0;

}


void start_basicOperation_basic(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: UP_memory_management**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: 图像的读取、显示、输出" << endl;


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



// test0: 图像的读取、显示、输出
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: 图像的读取、显示、输出" << endl;

	Mat lena = imread("lena.jpg");
	imwrite("lena_imwrited.jpg", lena);
	imshow("lena", lena);
	waitKey(0);								 		 //延迟x毫秒后关闭窗口，如果x==0则一直不关闭，直到按下任意键。

	cout << "\tlena.depth() = " << lena.depth() << endl;
	cout << "\tlena.depth() = 0，表示用默认的IMREAD_COLOR模式保存的图像矩阵一个通道中的数据元素类型为8U，即unchar。" << endl;
	cout << "\tlena.type() = " << lena.type() << endl;
	cout << "\tlena.type() = 16 = (3-1)*8+0，表示矩阵类型为CV_8UC3,标准的三通道RGB图像矩阵。" << endl;

	// flag == 0 == IMREAD_GRAYSCALE：图像数据保存到单通道矩阵中，即保存为灰度图矩阵。
	Mat lena_blue = imread("lena.jpg", 0);
	imshow("lena blue", lena_blue);
	waitKey(0);
	

}
