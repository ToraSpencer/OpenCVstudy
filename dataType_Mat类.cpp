#include <opencv2/opencv.hpp>
 

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace cv;
 
#define eps 1e-10					//定义非常小的一个量epsilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// OpenCV数据类型——Mat类、以及相关的MatSize类、
/*
**
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
void set_fun_dataType_Mat(void);
void start_dataType_Mat(void);


static void test0(void);



/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_dataType_Mat(void)
{
	pfun[0] = test0;

}


void start_dataType_Mat(void)
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
		cout << "0. test0: Mat类的常用构造函数  " << endl;


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


// test0: Mat类的常用构造函数
static void test0(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: Mat类的常用构造函数" << endl << endl;

	// 无参构造：
	cout << "\tMat() 无参构造函数构造的空矩阵：" << endl;
	Mat emptyMatrix = Mat();
	cout << "\ta = \n" << " " << emptyMatrix << endl << endl;

	// Mat(int rows, int cols, type)：
	cout << "\tMat(int rows, int cols, type) 构造元素初始值全为0的矩阵：" << endl;
	Mat M1(3, 4, CV_8UC1);
	cout << "\tM1 = \n" << format(M1, Formatter::FMT_MATLAB) << endl << endl;


	// 输入Size对象构造：
	cout << "\tMat(sz,type) 利用Size对象规定的尺寸来构造矩阵：" << endl;
	Size sz = Size(5, 6);
	Mat M2 = Mat(sz, CV_8UC1);
	cout << "\tM2 = \n" << format(M2, Formatter::FMT_MATLAB) << endl << endl;


	// 输入Scalar对象构造：
	cout << "\t利用Scalar对象构造多通道图像的矩阵:" << endl;
	Mat fourChanelMatrix = Mat(3, 3, CV_32FC4, Scalar(1, 2, 3, 4));
	cout << "\tfourChanelMatrix = \n" << format(fourChanelMatrix, Formatter::FMT_MATLAB) << endl << endl;


	// 输入一维array构造：
	cout << "\t读取一维array数据构造矩阵：" << endl;
	double a[] = { 1,2,3,4,5,6,7,8,9 };
	Mat M_array(3, 3, CV_64FC1, a);
	cout << "\tM_array = \n" << M_array << endl;


	// 输入二维array构造：
	cout << "\t输入二维array构造：" << endl;
	double aa[2][3] = { {1,2,3},{4,5,6} };
	Mat M_array2(2, 3, CV_64FC1, aa);
	cout << "\tM_array2 = \n" << M_array2 << endl << endl;


	// 输入vector对象构造：
	cout << "\t输入vector对象构造列向量矩阵：" << endl;
	vector<double> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	Mat M_vector(v);
	cout << "\tM_vector = \n" << M_vector << endl << endl;


	cout << endl << endl;
}


//test1:生成其他特殊的矩阵的Mat类成员方法
static void test1(void)
{
	cout << "test3：生成其他特殊的矩阵：" << endl;

	//Mat::zeros()
	Mat zerosM = Mat::zeros(3, 4, CV_8UC1);
	cout << "生成全零矩阵：" << endl;
	cout << "zerosM = \n" << format(zerosM, Formatter::FMT_MATLAB) << endl;


	//Mat::oens()
	Mat onesM = Mat::ones(3, 4, CV_8UC1);
	cout << "生成全一矩阵：" << endl;
	cout << "onesM = \n" << format(onesM, Formatter::FMT_MATLAB) << endl;


	//Mat::eye()
	cout << "生成单位矩阵：" << endl;
	Mat eyeM = Mat::eye(4, 4, CV_8UC1);
	cout << "eyeM = \n" << format(eyeM, Formatter::FMT_MATLAB) << endl;


	//
	cout << "生成第三维维数很大的三维矩阵：" << endl;
	Mat multipleChanelM(3, 4, CV_32FC(5));			//通道数，即第三维维数大于4时，数字要写在括号内。
	cout << "multipleChanelM = \n" << format(multipleChanelM, Formatter::FMT_MATLAB) << "\n通道数最多为CV_CN_MAX = 512" << endl;
	cout << endl;


	//cv::randu()
	cout << "生成均匀分布的随机矩阵——randu(dst,low,high)" << endl;
	Mat Mrand1(3, 3, CV_32FC1);
	randu(Mrand1, 0, 1);
	cout << "Mrand1 = \n" << Mrand1 << endl;

	Mat Mrand2(3, 3, CV_8UC1);
	randu(Mrand2, 0, 100);
	cout << "Mrand2 = \n" << Mrand2 << endl;

	Mat_<Vec3f> Mrand3(2, 2);
	randu(Mrand3, Scalar(0, 100, 200), Scalar(50, 150, 250));
	cout << "Mrand3 = \n" << Mrand3 << endl;

	cout << endl << endl;
}

//test2：Mat类的public成员数据。
static void test2(void)
{
	cout << "test4：矩阵对象的属性（Mat类的成员）：" << endl << endl;

	Mat MU(3, 4, CV_8UC1);
	Mat MF(3, 4, CV_32FC1);
	Mat MFF(3, 4, CV_32FC3);

	cout << "矩阵的维度为MU.dims = " << MU.dims << endl << endl;

	cout << "矩阵的行数为MU.rows = " << MU.rows << endl;
	cout << "矩阵的列数为MU.cols = " << MU.cols << endl;
	cout << "矩阵的尺寸为MU.size = " << MU.size << endl << endl;

	cout << endl << endl;
}

//test3：获取矩阵属性的方法。
static void test3(void)
{
	cout << "test5：获取矩阵属性的方法：" << endl;

	Mat MU(3, 4, CV_8UC1);
	Mat MF(3, 4, CV_32FC1);
	Mat MFF(3, 4, CV_32FC3);

	cout << "返回矩阵通道数：MFF.channels() = " << MFF.channels() << endl << endl;

	cout << "elemSize1()：返回一个矩阵元素一个通道分量所占的字节数：" << endl;
	cout << "MU.elemSize1() = " << MU.elemSize1() << "		//uchar矩阵一个元素一个通道分量占1个byte，位深为8位。" << endl;
	cout << "MFF.elemSize1() = " << MFF.elemSize1() << "		//32float矩阵一个元素一个通道分量占4byte，位深为32位。" << endl;
	cout << endl;

	cout << "elemSize()：返回一个矩阵元素所占的字节数：" << endl;
	cout << "MU.elemSize() = " << MU.elemSize() << endl;
	cout << "MFF.elemSize() = " << MFF.elemSize() << endl;
	cout << endl;

	cout << "返回一个表示矩阵元素类型的整形数，MU.depth() = " << MU.depth() << endl;
	cout << "深度列表：uchar(8U) = 0, short(8S) = 1, unsigned(16U) = 2, short int(16S) = 3, int(32S) = 4, float(32F) = 5, double(64F) = 6 " << endl;
	cout << "返回一个表示矩阵元素类型和通道数的整形数, MFF.type() = " << MFF.type() << endl;
	cout << "M.type() = 8*(M.channels()-1)+M.depth()" << endl;
	cout << endl;

	cout << endl;
}

//test4：矩阵运算、常用cv函数：
static void test4(void)
{
	cout << "test6：矩阵运算、常用函数：" << endl;
	Mat_<double> Ma = (Mat_<double>(2, 2) << 1, 2, 3, 4);
	Mat_<double> Mb = (Mat_<double>(2, 2) << 5, 5, 6, 6);
	Mat_<double> Va = (Mat_<double>(1, 4) << 1, 2, 3, 4);
	Mat_<double> Vb = (Mat_<double>(1, 4) << 5, 5, 6, 6);
	Mat Ma3 = Mat::ones(2, 2, CV_64FC3);
	Mat_<double> temp;


	cout << "Ma = \n" << Ma << endl;
	cout << "Mb = \n" << Mb << endl;
	cout << "Va = \n" << Va << endl;
	cout << "Vb = \n" << Vb << endl;
	cout << endl;

	cout << "实数与矩阵相乘：" << endl;
	cout << "3.0*Ma = \n" << 3.0 * Ma << endl;
	cout << endl;

	cout << "矩阵除以实数：" << endl;
	cout << "Ma/8 = \n" << Ma / 8 << endl;
	cout << endl;

	cout << "矩阵乘法：" << endl;
	cout << "Ma*Mb = \n" << Ma * Mb << endl;
	cout << endl;

	cout << "矩阵按元素相乘：" << endl;
	cout << "Ma.mul(Mb) = \n" << Ma.mul(Mb) << endl;
	cout << endl;

	cout << "矩阵内积（矩阵拉成向量求内积）：" << endl;
	cout << "Ma.dot(Mb) = " << Ma.dot(Mb) << endl;
	cout << endl;

	cout << "void exp(输入矩阵，输出矩阵)：" << endl;
	exp(Ma, temp);
	cout << "exp(Ma,temp); temp = \n" << temp << endl;
	cout << endl;


	//reshape()：矩阵整形
	cout << "Mat reshape(int cn,int rows = 0) :" << endl;
	//第一个参数是整形后的通道数，取0的话通道数不改变。
	//第二个是整形后的行数，取0的话表示不改变。
	Mat Ma31 = Ma3.reshape(0, 4);
	cout << "Ma3 = \n" << Ma3 << endl;
	cout << "Ma31 = Ma3.reshape(1,4); Ma31 =  \n" << Ma31 << endl;
	cout << "Ma31.channels() = " << Ma31.channels() << endl;
	cout << endl;


	//矩阵串联和并联：
	//vconcat(src1,src2,dst)
	//vconcat(vector<Mat> v, dst)
	cout << "矩阵串联和并联：vconcat(),hconcat()" << endl;
	Mat_<double> Mc;
	vconcat(Ma, Mb, Mc);
	cout << "vconcat(Ma,Mb,Mc); Mc = \n" << Mc << endl;
	vector<Mat> v;
	v.push_back(Ma);
	v.push_back(Mb);
	vconcat(v, Mc); 										// @suppress("Invalid arguments")
	cout << "vconcat(v,Mc); Mc = \n" << Mc << endl;


	//使用Range()提取矩阵的一部分。
	cout << "Range()提取矩阵的一部分：" << endl;
	Mat M61 = Ma(Range(0, 1), Range::all());				//提取矩阵的第0行到第1行（不包括第1行）。
	cout << "Mat M61 = Ma(Range(0,1),Range::all()); M61 = \n" << M61 << endl;


	//minMaxIdx()获取矩阵最大值最小值，及其索引：
	cout << "minMaxIdx()获取矩阵最大值最小值，及其索引：" << endl;
	double minVal;
	double maxVal;
	int minIdx[2];
	int maxIdx[2];
	minMaxIdx(Ma, &minVal, &maxVal, minIdx, maxIdx);
	cout << minVal << endl;
	cout << maxVal << endl;
	cout << minIdx[0] << ", " << minIdx[1] << endl;
	cout << maxIdx[0] << ", " << maxIdx[1] << endl;


	//repeat()复制扩张矩阵
	//void repeat(InputArray src, int ny, int nx, OutputArray dst)
	//Mat repeat(const Mat& src, int ny, int nx)
	cout << "repeat()复制扩张矩阵" << endl;
	Mat_<double> Mrepeat1;
	repeat(Ma, 2, 1, Mrepeat1);
	cout << "Mrepeat1 = \n" << Mrepeat1 << endl;
	Mat_<double> Mrepeat2 = repeat(Ma, 1, 2);
	cout << "Mrepeat = \n" << Mrepeat2 << endl;
	cout << endl;


	//mean()求均值
	//Scalar mean(InputArray src, InputArray mask = noArray())
	cout << "mean()求均值：" << endl;
	Mat_<Vec4d> M(4, 4, Scalar(1, 2, 3, 4));
	Scalar S_mean = mean(M);
	cout << "S_mean = " << S_mean << endl;
	cout << endl;

	//sum()求矩阵所有元素和
	//Scalar sum(InputArray src)
	cout << "sum()求矩阵所有元素和" << endl;
	cout << "M = \n" << M << endl;
	Scalar S_sum = sum(M);
	cout << "S_sum = " << S_sum << endl;
	cout << "Ma = \n" << Ma << endl;
	double Ma_sum = sum(M)(0);
	cout << "Ma_sum = sum(M)(0) = " << Ma_sum << endl;
	cout << endl;

	//reduce()矩阵按行/列求和、求均值、求最大值、求最小值
	//void reduce(InputArray src, OutputArray dst, int dim, nt rtype, int dtype = -1 )
	//		int dim：0为输出行向量，1为输出列向量。
	//		rtype: CV_REDUCE_SUM = 0; CV_REDUCE_AVG = 1; CV_REDUCE_MAX = 2; CV_REDUCE_MIN = 3;
	cout << "reduce()矩阵按行/列求和、求均值、求最大值、求最小值" << endl;
	Mat_<Vec4d> Msum;
	reduce(M, Msum, 0, 0);
	cout << "Msum = \n" << Msum << endl;
	Mat_<Vec4d> Mavg;
	reduce(M, Mavg, 1, 1);
	cout << "Mavg = \n" << Mavg << endl;


	//transpose()矩阵转置
	//void transpose(InputArray src, OutputArray dst)
	cout << "transpose()矩阵转置" << endl;
	cout << "Ma = \n" << Ma << endl;
	transpose(Ma, Ma);
	cout << "transpose(Ma,Ma); Ma = \n" << Ma << endl;
	cout << endl;




	cout << endl;
}

//test5：矩阵元素的访问——获取元素的指针、引用、迭代器
static void test5(void)
{
	cout << "test7：矩阵元素的访问——获取元素的指针、引用、迭代器：" << endl << endl;
	Mat MU(3, 4, CV_8UC1);
	Mat MF(3, 4, CV_32FC1);
	Mat MFF(3, 4, CV_32FC3);

	// ptr()返回矩阵元素的指针。
	cout << "使用.ptr<_Tp>()获取矩阵元素指针：" << endl;		//ptr()的重载：ptr(row)返回某行的首指针； ptr(row,col)返回某行某列的元素。
	uchar* dataU20 = MU.ptr<uchar>(2);
	float* dataF20 = MF.ptr<float>(2);
	Vec3f* dataFF22 = MFF.ptr<Vec3f>(2, 2);
	Vec3f* dataFF23 = MFF.ptr<Vec3f>(2, 3);
	*dataU20 = 1;
	*dataF20 = 1.33;
	*dataFF22 = 3.1;
	*dataFF23 = 1.66;
	cout << "MU = \n" << MU << endl;
	cout << "MF = \n" << MF << endl;
	cout << "MFF = \n" << MFF << endl;
	cout << "注意：用cout输出uchar数据输出的是ASCII码，有些ASCII码是隐藏的不对窗口显示，所以需要转换为int类型再输出。" << endl;
	cout << endl;

	// 使用指针遍历矩阵中的元素；
	cout << "使用指针遍历矩阵中的元素；" << endl;
	Mat m;
	uchar* p = nullptr;
	uchar arr[] = { 1,2,3,4,5,6,7,8,9 };

	m = Mat(3, 3, CV_8SC1, arr);
	p = m.ptr<uchar>(0, 0);

	cout << "m = \n" << m << endl;

	for (int count = 1; count <= m.rows * m.cols; count++, p++)
	{
		cout << int(*p) << "   ";				// 注意：用cout输出uchar数据输出的是ASCII码，有些ASCII码是隐藏的不对窗口显示，所以需要转换为int类型再输出。
	}
	cout << endl;


	// at()返回矩阵元素的引用。
	cout << "at<_Tp>(row,col)[channel]返回矩阵元素的引用：" << endl;				//注意第一个通道的序号是0
	cout << "(int)MU.at<uchar>(0,1) = " << (int)MU.at<uchar>(0, 1) << endl;
	cout << "MF.at<float>(2,0) = " << MF.at<float>(2, 0) << endl;
	cout << "MFF.at<Vec3f>(2,2) = " << MFF.at<Vec3f>(2, 2) << endl;
	cout << "MFF.at<Vec3f>(2,2)[0]" << MFF.at<Vec3f>(2, 2)[0] << endl;

	// begin(), end()返回元素的迭代器
	cout << "begin(), end()返回元素的迭代器" << endl;
	Mat m1;
	MatIterator_<int> t1, tt1;						// 元素类型必须是已知的，迭代器类型要和元素类型对应。
	MatConstIterator_<float> ct2, ctt2;



	int arr1[] = { 1,2,3,4,5,6,7,8,9 };
	float arr2[] = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9 };
	m1 = Mat(3, 3, CV_32SC1, arr1);
	const Mat m2 = Mat(3, 3, CV_32FC1, arr2);
	t1 = m1.begin<int>();
	tt1 = m1.end<int>();
	ct2 = m2.begin<float>();
	ctt2 = m2.end<float>();


	cout << "从首元素开始用迭代器正向遍历元素：" << endl;
	for (; t1 != m1.end<int>(); t1++)
	{
		cout << *t1 << "  ";
	}
	cout << endl;

	cout << "从尾元素开始用迭代器反向遍历元素：" << endl;
	for (ctt2--; ctt2 != m2.begin<float>()--; ctt2--)
	{
		cout << *ctt2 << "  ";
	}
	cout << endl;

	int a, b, c, d;
	a = 1;
	b = 1;
	c = 1;
	d = 1;
	a = b++;		// a先赋值，之后b再自增；
	c = ++d;		// d先自增，之后c再赋值。
	cout << a << "  " << b << endl;
	cout << c << "  " << d << endl;

}

//test6：其他不知道如何分类的成员方法：
static void test6(void)
{
	cout << "test8：其他不知道如何分类的成员方法：" << endl << endl;

	// Mat::convertTo()更改矩阵数据类型。
	cout << "Mat::convertTo()更改矩阵数据类型。" << endl;
	Mat M81 = Mat(2, 3, CV_64FC2, Scalar(2.33, 9.11));
	Mat_<int> M82 = Mat_<int>::ones(2, 3);
	cout << "M81 = \n" << M81 << endl;
	cout << "M82 = \n" << M82 << endl;
	Mat M811;
	Mat_<double> M821;
	M81.convertTo(M811, CV_8UC2);
	M82.convertTo(M821, CV_64FC1);
	cout << "M811 = \n" << M811 << endl;
	cout << "M821 = \n" << M821 << endl;
	cout << "typeid(M821(1,1)).name() = " << typeid(M821(1, 1)).name() << endl;
	cout << endl;

	// release()
	cout << "void cv::Mat:: release()" << endl;
	Mat m, m1;
	cout << "声明矩阵后：" << endl;
	cout << "m = \n" << m << endl;
	m = Mat::ones(3, 4, CV_64FC1);
	cout << "定义矩阵后：" << endl;
	cout << "m = \n" << m << endl;
	m.release();
	cout << "release矩阵后：" << endl;
	cout << "m = \n" << m << endl;
	cout << endl;

	// create()
	cout << "void create(int rows, int cols, int type)" << endl;
	cout << "声明矩阵后：" << endl;
	cout << "m = \n" << m << endl;
	m.create(2, 3, CV_64FC1);
	cout << "矩阵create之后：" << endl;
	cout << "m = \n" << m << endl;
	cout << endl;


	// clone()
	cout << "Mat cv::Mat::clone() const" << endl;
	double* p = nullptr;
	m = Mat::zeros(3, 4, CV_64FC1);
	m1 = m.clone();
	cout << "m = \n" << m << endl;
	cout << "m1 = \n" << m1 << endl;
	p = m.ptr<double>(1, 2);
	*p = 1.23;
	cout << "*p = 1.23;" << endl;
	cout << "m = \n" << m << endl;
	cout << "m1 = \n" << m1 << endl;

}

//test7: 矩阵的格式化输出：
static void test7(void)
{
	cout << "test1: the output format of matrix: " << endl;
	Mat I = Mat::eye(5, 5, CV_32FC3);									//eye()并非Mat类的构造函数，是成员函数，返回一个矩阵。

	cout << "矩阵的默认输出格式：" << endl;
	cout << "I = \n" << " " << I << endl << endl;
	cout << "矩阵的MATLAB风格的输出格式：" << endl;
	cout << "I = \n" << format(I, Formatter::FMT_MATLAB) << ";" << endl;
	cout << endl;

	cout << endl;
}