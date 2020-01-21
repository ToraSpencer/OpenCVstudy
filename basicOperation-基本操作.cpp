#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define eps 1e-10					//����ǳ�С��һ����epsilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// imread������ȡͼƬ
/*. BC------------------------------------------------------------------------
**	imread������ȡͼƬ
**
**	������
**			Mat cv::imread	(const String & 	filename,
**							int 	flags = IMREAD_COLOR )
**
**
**	���������
**			const String & 	filename���ļ�·��
**			int flags = IMREAD_COLOR����ȡģʽ
**					flags����ֵ��Ӧ��ImreadModes�е�ö�ٳ����������Բ�ͬ��ģʽ����ȡͼƬ�ļ������ݱ��浽Mat�����С�
**					Ĭ��ȡIMREAD_COLORö�ٳ�������ֵΪ1������ͼ�����ݱ���Ϊ��ͨ��RBG����
**
**	���������
**			Mat�� ������ͼƬ���ݵ�Mat�������
**
**
*. EC------------------------------------------------------------------------
*/
 

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
void set_fun_basicOperation_basic(void);
void start_basicOperation_basic(void);
static void test0(void);



/***************************************************************************
***************************************************************************/
// extern����
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// ��������
void set_fun_basicOperation_basic(void)
{
	pfun[0] = test0;

}


void start_basicOperation_basic(void)
{
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: UP_memory_management**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: ͼ��Ķ�ȡ����ʾ�����" << endl;


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



// test0: ͼ��Ķ�ȡ����ʾ�����
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: ͼ��Ķ�ȡ����ʾ�����" << endl;

	Mat lena = imread("lena.jpg");
	imwrite("lena_imwrited.jpg", lena);
	imshow("lena", lena);
	waitKey(0);								 		 //�ӳ�x�����رմ��ڣ����x==0��һֱ���رգ�ֱ�������������

	cout << "\tlena.depth() = " << lena.depth() << endl;
	cout << "\tlena.depth() = 0����ʾ��Ĭ�ϵ�IMREAD_COLORģʽ�����ͼ�����һ��ͨ���е�����Ԫ������Ϊ8U����unchar��" << endl;
	cout << "\tlena.type() = " << lena.type() << endl;
	cout << "\tlena.type() = 16 = (3-1)*8+0����ʾ��������ΪCV_8UC3,��׼����ͨ��RGBͼ�����" << endl;

	// flag == 0 == IMREAD_GRAYSCALE��ͼ�����ݱ��浽��ͨ�������У�������Ϊ�Ҷ�ͼ����
	Mat lena_blue = imread("lena.jpg", 0);
	imshow("lena blue", lena_blue);
	waitKey(0);
	

}
