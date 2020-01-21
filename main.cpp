#include <opencv2/opencv.hpp>


#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>


#define PI  3.14159


using namespace std;
using namespace cv;



/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
void(*pfun[100])(void) = { nullptr };
int inputTag;							// 菜单界面中判断输入是否有效的标识符。
int inputNum;							// 菜单界面中用户输入的整数
int interfaceLevel;						// 当前菜单界面的层级，主菜单是一级。




/***************************************************************************
***************************************************************************/
// extern变量


/***************************************************************************
***************************************************************************/
// 函数声明




/***************************************************************************
***************************************************************************/
// extern函数
extern void reset_pfun(void);
extern void traverse_pfun(void);

extern void set_fun_basicOperation_basic(void);
extern void set_fun_dataType_Mat(void);
extern void set_fun_pictureprocessing_GIF(void);

extern void start_basicOperation_basic(void);
extern void start_dataType_Mat(void);
extern void start_pictureprocessing_GIF(void);


/***************************************************************************
***************************************************************************/
// 函数定义
int main(int argc, char** argv)
{
	inputNum = 99;
	inputTag = 0;
	interfaceLevel = 1;


	reset_pfun();

	// 主界面循环——选择章节
	while (1 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MAIN MENU**********************" << endl;
		cout << "Please input a number to choose a function setting plan:" << endl;
		cout << "0. OpenCV基本操作和工具" << endl;
		cout << "1. OpenCV数据类型" << endl;
		cout << "2. OpenCV库函数" << endl;
		cout << "3. OpenCV图像处理" << endl;
		cout << "-1. Quit" << endl;


		inputTag = scanf("%d", &inputNum);


		// 若输入值不是整数，重新输入。
		if (0 == inputTag)
		{
			cout << "Invalid input. Please input again:" << endl;
			setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
											// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
			continue;
		}



		// 对主界面输入值的响应：
		switch (inputNum)
		{
		case -1:											// 退出程序
		{
			interfaceLevel = 0;
			break;
		}

		case 0:												// 0. 基本操作章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************BASIC OPERATION MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. 基本工具——基本操作" << endl;

				inputTag = scanf("%d", &inputNum);



				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
															// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_basicOperation_basic();
					start_basicOperation_basic();
					break;
				
				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}

		case 1:												// 1. 数据类型章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************DATA TYPE MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0.  数据类型——Mat类" << endl;

				inputTag = scanf("%d", &inputNum);



				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_dataType_Mat();
					start_dataType_Mat();
					break;

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}

		case 2:												// 2. 库函数章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************LIBRARY FUNCTION MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0." << endl;

				inputTag = scanf("%d", &inputNum);



				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					// set_fun_basicOperation_basicOperation();
					// start_basicOperation_basicOperation();
					break;

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}

		case 3:												// 3. 图像处理章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************PICTURE PROCESSING MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. 图像处理——GIF的处理" << endl;

				inputTag = scanf("%d", &inputNum);



				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_pictureprocessing_GIF();
					start_pictureprocessing_GIF();
					break;

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}


		default:											// default. 不合法的整数输入：
		{
			cout << "Invalid input. Please input again:" << endl;
			break;
		}

		}


	}


	getchar();


	return 0;




}
