#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define eps 1e-10					//����ǳ�С��һ����epsilon�������������������ֵʱ����Ϊ0
#define PI 3.14159

 

/***************************************************************************
***************************************************************************/
// ȫ�ֱ��������Ͷ���





/***************************************************************************
***************************************************************************/
// extern����
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;





/***************************************************************************
***************************************************************************/
// ��������
void set_fun_basicOperation_GIF(void);
void start_basicOperation_GIF(void);
static void test0(void);




/***************************************************************************
***************************************************************************/
// extern����
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// ��������
void set_fun_basicOperation_GIF(void)
{
	pfun[0] = test0;

}




void start_basicOperation_GIF(void)
{
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: basicOperation_GIF**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0.  " << endl;


		inputTag = scanf("%d", &inputNum);


		// ������ֵ�����������������롣
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// ��������������ֵ����Ӧ��
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



// test0:  
static void test0(void)
{
 


}
