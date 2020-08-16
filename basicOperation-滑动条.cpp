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
int contrast; 					    //�Աȶ�ֵ
int bright; 					     //����ֵ
Mat src,dst;





/***************************************************************************
***************************************************************************/
// extern����
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// ��������
static void onContrastAndBright(int, void *);               // �ص��������������ȡ��Աȶ�

void set_fun_basicOperation_trackbar(void);
void start_basicOperation_trackbar(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);



/***************************************************************************
***************************************************************************/
// extern����
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// ��������

static void onContrastAndBright(int, void *)
{
// �ص������̶���ʽ�� static void onParameter(int, void*)
// 		int parameterΪ�ص����������룬Ҳ�ǻ������ϻ���λ�ö�Ӧ�����֣��ص������������Ϊ������ʾ�Ľ����

	// ��������
	namedWindow("original image", 1);

	// ����forѭ����ִ������ g_dstImage(i,j) = a*g_srcImage(i,j) + b
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

	// ��ʾͼ��
	imshow("original image", src);
	imshow("output image", dst);
}


void set_fun_basicOperation_trackbar(void)
{
	pfun[0] = test0;

}


void start_basicOperation_trackbar(void)
{
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: �������������ߡ���������**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0��ʹ�û���������ͼƬ�����ȡ��Աȶ�" << endl;


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



// test0: ʹ�û���������ͼƬ�����ȡ��Աȶȡ�
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: ʹ�û���������ͼƬ�����ȡ��Աȶ�" << endl;

    // �����û��ṩ��ͼ��
	src = imread("image/lena.jpg");
	//if( !src.data ) { printf("��ȡg_srcImageͼƬ����~�� \n"); return -1; }
	dst = Mat::zeros( src.size(), src.type() );

	//�趨�ԱȶȺ����ȵĳ�ֵ
	contrast=80;
	bright=80;

	//��������
	namedWindow("output image", 1);

	//����������
	createTrackbar("contrast: ", "output image", &contrast, 300,onContrastAndBright );
	createTrackbar("bright: ", "output image", &bright, 200,onContrastAndBright );

	//���ûص�����
	onContrastAndBright(contrast,0);
	onContrastAndBright(bright,0);


	cout << "\t���гɹ���������������۲�ͼ��Ч��\n\n\t���¡�q����ʱ�������˳�\n" << endl;
		//���¡�q����ʱ�������˳�
		while(char(waitKey(1)) != 'q') {}
 
	

}
