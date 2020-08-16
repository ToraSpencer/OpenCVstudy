#include <opencv2/opencv.hpp>
 

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace cv;
 
#define eps 1e-10					//����ǳ�С��һ����epsilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// OpenCV�������͡���Mat�ࡢ�Լ���ص�MatSize�ࡢ
/*
**
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
void set_fun_dataType_Mat(void);
void start_dataType_Mat(void);


static void test0(void);



/***************************************************************************
***************************************************************************/
// extern����
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// ��������
void set_fun_dataType_Mat(void)
{
	pfun[0] = test0;

}


void start_dataType_Mat(void)
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
		cout << "0. test0: Mat��ĳ��ù��캯��  " << endl;


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


// test0: Mat��ĳ��ù��캯��
static void test0(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: Mat��ĳ��ù��캯��" << endl << endl;

	// �޲ι��죺
	cout << "\tMat() �޲ι��캯������Ŀվ���" << endl;
	Mat emptyMatrix = Mat();
	cout << "\ta = \n" << " " << emptyMatrix << endl << endl;

	// Mat(int rows, int cols, type)��
	cout << "\tMat(int rows, int cols, type) ����Ԫ�س�ʼֵȫΪ0�ľ���" << endl;
	Mat M1(3, 4, CV_8UC1);
	cout << "\tM1 = \n" << format(M1, Formatter::FMT_MATLAB) << endl << endl;


	// ����Size�����죺
	cout << "\tMat(sz,type) ����Size����涨�ĳߴ����������" << endl;
	Size sz = Size(5, 6);
	Mat M2 = Mat(sz, CV_8UC1);
	cout << "\tM2 = \n" << format(M2, Formatter::FMT_MATLAB) << endl << endl;


	// ����Scalar�����죺
	cout << "\t����Scalar�������ͨ��ͼ��ľ���:" << endl;
	Mat fourChanelMatrix = Mat(3, 3, CV_32FC4, Scalar(1, 2, 3, 4));
	cout << "\tfourChanelMatrix = \n" << format(fourChanelMatrix, Formatter::FMT_MATLAB) << endl << endl;


	// ����һάarray���죺
	cout << "\t��ȡһάarray���ݹ������" << endl;
	double a[] = { 1,2,3,4,5,6,7,8,9 };
	Mat M_array(3, 3, CV_64FC1, a);
	cout << "\tM_array = \n" << M_array << endl;


	// �����άarray���죺
	cout << "\t�����άarray���죺" << endl;
	double aa[2][3] = { {1,2,3},{4,5,6} };
	Mat M_array2(2, 3, CV_64FC1, aa);
	cout << "\tM_array2 = \n" << M_array2 << endl << endl;


	// ����vector�����죺
	cout << "\t����vector����������������" << endl;
	vector<double> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	Mat M_vector(v);
	cout << "\tM_vector = \n" << M_vector << endl << endl;


	cout << endl << endl;
}


//test1:������������ľ����Mat���Ա����
static void test1(void)
{
	cout << "test3��������������ľ���" << endl;

	//Mat::zeros()
	Mat zerosM = Mat::zeros(3, 4, CV_8UC1);
	cout << "����ȫ�����" << endl;
	cout << "zerosM = \n" << format(zerosM, Formatter::FMT_MATLAB) << endl;


	//Mat::oens()
	Mat onesM = Mat::ones(3, 4, CV_8UC1);
	cout << "����ȫһ����" << endl;
	cout << "onesM = \n" << format(onesM, Formatter::FMT_MATLAB) << endl;


	//Mat::eye()
	cout << "���ɵ�λ����" << endl;
	Mat eyeM = Mat::eye(4, 4, CV_8UC1);
	cout << "eyeM = \n" << format(eyeM, Formatter::FMT_MATLAB) << endl;


	//
	cout << "���ɵ���άά���ܴ����ά����" << endl;
	Mat multipleChanelM(3, 4, CV_32FC(5));			//ͨ������������άά������4ʱ������Ҫд�������ڡ�
	cout << "multipleChanelM = \n" << format(multipleChanelM, Formatter::FMT_MATLAB) << "\nͨ�������ΪCV_CN_MAX = 512" << endl;
	cout << endl;


	//cv::randu()
	cout << "���ɾ��ȷֲ���������󡪡�randu(dst,low,high)" << endl;
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

//test2��Mat���public��Ա���ݡ�
static void test2(void)
{
	cout << "test4�������������ԣ�Mat��ĳ�Ա����" << endl << endl;

	Mat MU(3, 4, CV_8UC1);
	Mat MF(3, 4, CV_32FC1);
	Mat MFF(3, 4, CV_32FC3);

	cout << "�����ά��ΪMU.dims = " << MU.dims << endl << endl;

	cout << "���������ΪMU.rows = " << MU.rows << endl;
	cout << "���������ΪMU.cols = " << MU.cols << endl;
	cout << "����ĳߴ�ΪMU.size = " << MU.size << endl << endl;

	cout << endl << endl;
}

//test3����ȡ�������Եķ�����
static void test3(void)
{
	cout << "test5����ȡ�������Եķ�����" << endl;

	Mat MU(3, 4, CV_8UC1);
	Mat MF(3, 4, CV_32FC1);
	Mat MFF(3, 4, CV_32FC3);

	cout << "���ؾ���ͨ������MFF.channels() = " << MFF.channels() << endl << endl;

	cout << "elemSize1()������һ������Ԫ��һ��ͨ��������ռ���ֽ�����" << endl;
	cout << "MU.elemSize1() = " << MU.elemSize1() << "		//uchar����һ��Ԫ��һ��ͨ������ռ1��byte��λ��Ϊ8λ��" << endl;
	cout << "MFF.elemSize1() = " << MFF.elemSize1() << "		//32float����һ��Ԫ��һ��ͨ������ռ4byte��λ��Ϊ32λ��" << endl;
	cout << endl;

	cout << "elemSize()������һ������Ԫ����ռ���ֽ�����" << endl;
	cout << "MU.elemSize() = " << MU.elemSize() << endl;
	cout << "MFF.elemSize() = " << MFF.elemSize() << endl;
	cout << endl;

	cout << "����һ����ʾ����Ԫ�����͵���������MU.depth() = " << MU.depth() << endl;
	cout << "����б�uchar(8U) = 0, short(8S) = 1, unsigned(16U) = 2, short int(16S) = 3, int(32S) = 4, float(32F) = 5, double(64F) = 6 " << endl;
	cout << "����һ����ʾ����Ԫ�����ͺ�ͨ������������, MFF.type() = " << MFF.type() << endl;
	cout << "M.type() = 8*(M.channels()-1)+M.depth()" << endl;
	cout << endl;

	cout << endl;
}

//test4���������㡢����cv������
static void test4(void)
{
	cout << "test6���������㡢���ú�����" << endl;
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

	cout << "ʵ���������ˣ�" << endl;
	cout << "3.0*Ma = \n" << 3.0 * Ma << endl;
	cout << endl;

	cout << "�������ʵ����" << endl;
	cout << "Ma/8 = \n" << Ma / 8 << endl;
	cout << endl;

	cout << "����˷���" << endl;
	cout << "Ma*Mb = \n" << Ma * Mb << endl;
	cout << endl;

	cout << "����Ԫ����ˣ�" << endl;
	cout << "Ma.mul(Mb) = \n" << Ma.mul(Mb) << endl;
	cout << endl;

	cout << "�����ڻ������������������ڻ�����" << endl;
	cout << "Ma.dot(Mb) = " << Ma.dot(Mb) << endl;
	cout << endl;

	cout << "void exp(��������������)��" << endl;
	exp(Ma, temp);
	cout << "exp(Ma,temp); temp = \n" << temp << endl;
	cout << endl;


	//reshape()����������
	cout << "Mat reshape(int cn,int rows = 0) :" << endl;
	//��һ�����������κ��ͨ������ȡ0�Ļ�ͨ�������ı䡣
	//�ڶ��������κ��������ȡ0�Ļ���ʾ���ı䡣
	Mat Ma31 = Ma3.reshape(0, 4);
	cout << "Ma3 = \n" << Ma3 << endl;
	cout << "Ma31 = Ma3.reshape(1,4); Ma31 =  \n" << Ma31 << endl;
	cout << "Ma31.channels() = " << Ma31.channels() << endl;
	cout << endl;


	//�������Ͳ�����
	//vconcat(src1,src2,dst)
	//vconcat(vector<Mat> v, dst)
	cout << "�������Ͳ�����vconcat(),hconcat()" << endl;
	Mat_<double> Mc;
	vconcat(Ma, Mb, Mc);
	cout << "vconcat(Ma,Mb,Mc); Mc = \n" << Mc << endl;
	vector<Mat> v;
	v.push_back(Ma);
	v.push_back(Mb);
	vconcat(v, Mc); 										// @suppress("Invalid arguments")
	cout << "vconcat(v,Mc); Mc = \n" << Mc << endl;


	//ʹ��Range()��ȡ�����һ���֡�
	cout << "Range()��ȡ�����һ���֣�" << endl;
	Mat M61 = Ma(Range(0, 1), Range::all());				//��ȡ����ĵ�0�е���1�У���������1�У���
	cout << "Mat M61 = Ma(Range(0,1),Range::all()); M61 = \n" << M61 << endl;


	//minMaxIdx()��ȡ�������ֵ��Сֵ������������
	cout << "minMaxIdx()��ȡ�������ֵ��Сֵ������������" << endl;
	double minVal;
	double maxVal;
	int minIdx[2];
	int maxIdx[2];
	minMaxIdx(Ma, &minVal, &maxVal, minIdx, maxIdx);
	cout << minVal << endl;
	cout << maxVal << endl;
	cout << minIdx[0] << ", " << minIdx[1] << endl;
	cout << maxIdx[0] << ", " << maxIdx[1] << endl;


	//repeat()�������ž���
	//void repeat(InputArray src, int ny, int nx, OutputArray dst)
	//Mat repeat(const Mat& src, int ny, int nx)
	cout << "repeat()�������ž���" << endl;
	Mat_<double> Mrepeat1;
	repeat(Ma, 2, 1, Mrepeat1);
	cout << "Mrepeat1 = \n" << Mrepeat1 << endl;
	Mat_<double> Mrepeat2 = repeat(Ma, 1, 2);
	cout << "Mrepeat = \n" << Mrepeat2 << endl;
	cout << endl;


	//mean()���ֵ
	//Scalar mean(InputArray src, InputArray mask = noArray())
	cout << "mean()���ֵ��" << endl;
	Mat_<Vec4d> M(4, 4, Scalar(1, 2, 3, 4));
	Scalar S_mean = mean(M);
	cout << "S_mean = " << S_mean << endl;
	cout << endl;

	//sum()���������Ԫ�غ�
	//Scalar sum(InputArray src)
	cout << "sum()���������Ԫ�غ�" << endl;
	cout << "M = \n" << M << endl;
	Scalar S_sum = sum(M);
	cout << "S_sum = " << S_sum << endl;
	cout << "Ma = \n" << Ma << endl;
	double Ma_sum = sum(M)(0);
	cout << "Ma_sum = sum(M)(0) = " << Ma_sum << endl;
	cout << endl;

	//reduce()������/����͡����ֵ�������ֵ������Сֵ
	//void reduce(InputArray src, OutputArray dst, int dim, nt rtype, int dtype = -1 )
	//		int dim��0Ϊ�����������1Ϊ�����������
	//		rtype: CV_REDUCE_SUM = 0; CV_REDUCE_AVG = 1; CV_REDUCE_MAX = 2; CV_REDUCE_MIN = 3;
	cout << "reduce()������/����͡����ֵ�������ֵ������Сֵ" << endl;
	Mat_<Vec4d> Msum;
	reduce(M, Msum, 0, 0);
	cout << "Msum = \n" << Msum << endl;
	Mat_<Vec4d> Mavg;
	reduce(M, Mavg, 1, 1);
	cout << "Mavg = \n" << Mavg << endl;


	//transpose()����ת��
	//void transpose(InputArray src, OutputArray dst)
	cout << "transpose()����ת��" << endl;
	cout << "Ma = \n" << Ma << endl;
	transpose(Ma, Ma);
	cout << "transpose(Ma,Ma); Ma = \n" << Ma << endl;
	cout << endl;




	cout << endl;
}

//test5������Ԫ�صķ��ʡ�����ȡԪ�ص�ָ�롢���á�������
static void test5(void)
{
	cout << "test7������Ԫ�صķ��ʡ�����ȡԪ�ص�ָ�롢���á���������" << endl << endl;
	Mat MU(3, 4, CV_8UC1);
	Mat MF(3, 4, CV_32FC1);
	Mat MFF(3, 4, CV_32FC3);

	// ptr()���ؾ���Ԫ�ص�ָ�롣
	cout << "ʹ��.ptr<_Tp>()��ȡ����Ԫ��ָ�룺" << endl;		//ptr()�����أ�ptr(row)����ĳ�е���ָ�룻 ptr(row,col)����ĳ��ĳ�е�Ԫ�ء�
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
	cout << "ע�⣺��cout���uchar�����������ASCII�룬��ЩASCII�������صĲ��Դ�����ʾ��������Ҫת��Ϊint�����������" << endl;
	cout << endl;

	// ʹ��ָ����������е�Ԫ�أ�
	cout << "ʹ��ָ����������е�Ԫ�أ�" << endl;
	Mat m;
	uchar* p = nullptr;
	uchar arr[] = { 1,2,3,4,5,6,7,8,9 };

	m = Mat(3, 3, CV_8SC1, arr);
	p = m.ptr<uchar>(0, 0);

	cout << "m = \n" << m << endl;

	for (int count = 1; count <= m.rows * m.cols; count++, p++)
	{
		cout << int(*p) << "   ";				// ע�⣺��cout���uchar�����������ASCII�룬��ЩASCII�������صĲ��Դ�����ʾ��������Ҫת��Ϊint�����������
	}
	cout << endl;


	// at()���ؾ���Ԫ�ص����á�
	cout << "at<_Tp>(row,col)[channel]���ؾ���Ԫ�ص����ã�" << endl;				//ע���һ��ͨ���������0
	cout << "(int)MU.at<uchar>(0,1) = " << (int)MU.at<uchar>(0, 1) << endl;
	cout << "MF.at<float>(2,0) = " << MF.at<float>(2, 0) << endl;
	cout << "MFF.at<Vec3f>(2,2) = " << MFF.at<Vec3f>(2, 2) << endl;
	cout << "MFF.at<Vec3f>(2,2)[0]" << MFF.at<Vec3f>(2, 2)[0] << endl;

	// begin(), end()����Ԫ�صĵ�����
	cout << "begin(), end()����Ԫ�صĵ�����" << endl;
	Mat m1;
	MatIterator_<int> t1, tt1;						// Ԫ�����ͱ�������֪�ģ�����������Ҫ��Ԫ�����Ͷ�Ӧ��
	MatConstIterator_<float> ct2, ctt2;



	int arr1[] = { 1,2,3,4,5,6,7,8,9 };
	float arr2[] = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9 };
	m1 = Mat(3, 3, CV_32SC1, arr1);
	const Mat m2 = Mat(3, 3, CV_32FC1, arr2);
	t1 = m1.begin<int>();
	tt1 = m1.end<int>();
	ct2 = m2.begin<float>();
	ctt2 = m2.end<float>();


	cout << "����Ԫ�ؿ�ʼ�õ������������Ԫ�أ�" << endl;
	for (; t1 != m1.end<int>(); t1++)
	{
		cout << *t1 << "  ";
	}
	cout << endl;

	cout << "��βԪ�ؿ�ʼ�õ������������Ԫ�أ�" << endl;
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
	a = b++;		// a�ȸ�ֵ��֮��b��������
	c = ++d;		// d��������֮��c�ٸ�ֵ��
	cout << a << "  " << b << endl;
	cout << c << "  " << d << endl;

}

//test6��������֪����η���ĳ�Ա������
static void test6(void)
{
	cout << "test8��������֪����η���ĳ�Ա������" << endl << endl;

	// Mat::convertTo()���ľ����������͡�
	cout << "Mat::convertTo()���ľ����������͡�" << endl;
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
	cout << "���������" << endl;
	cout << "m = \n" << m << endl;
	m = Mat::ones(3, 4, CV_64FC1);
	cout << "��������" << endl;
	cout << "m = \n" << m << endl;
	m.release();
	cout << "release�����" << endl;
	cout << "m = \n" << m << endl;
	cout << endl;

	// create()
	cout << "void create(int rows, int cols, int type)" << endl;
	cout << "���������" << endl;
	cout << "m = \n" << m << endl;
	m.create(2, 3, CV_64FC1);
	cout << "����create֮��" << endl;
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

//test7: ����ĸ�ʽ�������
static void test7(void)
{
	cout << "test1: the output format of matrix: " << endl;
	Mat I = Mat::eye(5, 5, CV_32FC3);									//eye()����Mat��Ĺ��캯�����ǳ�Ա����������һ������

	cout << "�����Ĭ�������ʽ��" << endl;
	cout << "I = \n" << " " << I << endl << endl;
	cout << "�����MATLAB���������ʽ��" << endl;
	cout << "I = \n" << format(I, Formatter::FMT_MATLAB) << ";" << endl;
	cout << endl;

	cout << endl;
}