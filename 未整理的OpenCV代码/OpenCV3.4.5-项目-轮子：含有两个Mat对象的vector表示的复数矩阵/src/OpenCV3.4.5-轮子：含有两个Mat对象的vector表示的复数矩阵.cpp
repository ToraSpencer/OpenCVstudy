#include "cMat.h"
using namespace std;
using namespace cv;

//test1():
void test1()
{
	Mat_<double> m,m1,m2;

	m = Mat_<double>::zeros(3,4);
	m1 = m.clone();
	m2 = m.clone();
	cout << "m = \n" << m << endl;
	cout << "m1 = \n" << m1 << endl;
	cout << "m2 = \n" << m2 << endl;
	cout << endl;

	cv::randu(m,0,2);
	cout << "m = \n" << m << endl;
	cout << endl;

	cv::min(m,1);
	cout << "m = \n" << m << endl;
	cout << endl;

	cv::randu(m1,0,2);
	cv::randu(m2,0,2);
	cout << "m1 = \n" << m1 << endl;
	cout << "m2 = \n" << m2 << endl;

	Mat_<double> temp = min(m1,m2);
	cout << "temp = \n" << temp << endl;
	cout << endl;
}

//test2():
void test2()
{
	Mat_<double> m = (Mat_<double>(3,3)<<1,2,3,4,5,6,7,8,9);


	Mat_<double> temp1 = cv::max(m,0,8);
	cout << "cv::max(m,0,6) = \n" << temp1 << endl << endl;

	temp1 = cv::max(m,1,7);
	cout << "cv::max(m,1,5) = \n" << temp1 << endl << endl;

	temp1 = cv::min(m,0,2);
	cout << "cv::max(m,1,5) = \n" << temp1 << endl << endl;

	temp1 = cv::min(m,1,5);
	cout << "cv::max(m,1,5) = \n" << temp1 << endl << endl;

}

//
void test3()
{
	Mat_<double> m1 = (Mat_<double>(2,3)<< 1,1,2,1,3,1);
	double temp = cv::normInf(m1);
	cout << temp << endl;

	int a = 11;
	std::printf("%d",a);
	std::printf("11\n");
}

int main()
{
	//test1();
	//test2();
	test3();



	return 0;
}
