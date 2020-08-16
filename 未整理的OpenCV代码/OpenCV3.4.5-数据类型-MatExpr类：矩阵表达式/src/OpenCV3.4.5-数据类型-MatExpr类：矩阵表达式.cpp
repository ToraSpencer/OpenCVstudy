/*
public成员数据
	Mat 	a
	double 	alpha
	Mat 	b
	double 	beta
	Mat 	c
	int 	flags
	const MatOp * 	op
	Scalar 	s



构造函数
MatExpr ()

MatExpr (const Mat &m)

MatExpr (const MatOp *_op, int _flags, const Mat &_a=Mat(), const Mat &_b=Mat(), const Mat &_c=Mat(), double _alpha=1, double _beta=1, const Scalar &_s=Scalar())



public成员方法
	MatExpr 	col (int x) const

	Mat 	cross (const Mat &m) const

	MatExpr 	diag (int d=0) const

	double 	dot (const Mat &m) const

	MatExpr 	inv (int method=DECOMP_LU) const

	MatExpr 	mul (const MatExpr &e, double scale=1) const

	MatExpr 	mul (const Mat &m, double scale=1) const

 	operator Mat () const

	template<typename _Tp >
 		operator Mat_< _Tp > () const

	MatExpr 	operator() (const Range &rowRange, const Range &colRange) const

	MatExpr 	operator() (const Rect &roi) const

	MatExpr 	row (int y) const

	Size 	size () const

	MatExpr 	t () const

	int 	type () const





返回矩阵表达式的cv函数
MatExpr 	operator+ (const Mat &a, const Mat &b)

MatExpr 	operator+ (const Mat &a, const Scalar &s)

MatExpr 	operator+ (const Scalar &s, const Mat &a)

MatExpr 	operator+ (const MatExpr &e, const Mat &m)

MatExpr 	operator+ (const Mat &m, const MatExpr &e)

MatExpr 	operator+ (const MatExpr &e, const Scalar &s)

MatExpr 	operator+ (const Scalar &s, const MatExpr &e)

MatExpr 	operator+ (const MatExpr &e1, const MatExpr &e2)

MatExpr 	operator- (const Mat &a, const Mat &b)

MatExpr 	operator- (const Mat &a, const Scalar &s)

MatExpr 	operator- (const Scalar &s, const Mat &a)

MatExpr 	operator- (const MatExpr &e, const Mat &m)

MatExpr 	operator- (const Mat &m, const MatExpr &e)

MatExpr 	operator- (const MatExpr &e, const Scalar &s)

MatExpr 	operator- (const Scalar &s, const MatExpr &e)

MatExpr 	operator- (const MatExpr &e1, const MatExpr &e2)

MatExpr 	operator- (const Mat &m)

MatExpr 	operator- (const MatExpr &e)

MatExpr 	operator* (const Mat &a, const Mat &b)

MatExpr 	operator* (const Mat &a, double s)

MatExpr 	operator* (double s, const Mat &a)

MatExpr 	operator* (const MatExpr &e, const Mat &m)

MatExpr 	operator* (const Mat &m, const MatExpr &e)

MatExpr 	operator* (const MatExpr &e, double s)

MatExpr 	operator* (double s, const MatExpr &e)

MatExpr 	operator* (const MatExpr &e1, const MatExpr &e2)

MatExpr 	operator/ (const Mat &a, const Mat &b)

MatExpr 	operator/ (const Mat &a, double s)

MatExpr 	operator/ (double s, const Mat &a)

MatExpr 	operator/ (const MatExpr &e, const Mat &m)

MatExpr 	operator/ (const Mat &m, const MatExpr &e)

MatExpr 	operator/ (const MatExpr &e, double s)

MatExpr 	operator/ (double s, const MatExpr &e)

MatExpr 	operator/ (const MatExpr &e1, const MatExpr &e2)

MatExpr 	operator< (const Mat &a, const Mat &b)

MatExpr 	operator< (const Mat &a, double s)

MatExpr 	operator< (double s, const Mat &a)

MatExpr 	operator<= (const Mat &a, const Mat &b)

MatExpr 	operator<= (const Mat &a, double s)

MatExpr 	operator<= (double s, const Mat &a)

MatExpr 	operator== (const Mat &a, const Mat &b)

MatExpr 	operator== (const Mat &a, double s)

MatExpr 	operator== (double s, const Mat &a)

MatExpr 	operator!= (const Mat &a, const Mat &b)

MatExpr 	operator!= (const Mat &a, double s)

MatExpr 	operator!= (double s, const Mat &a)

MatExpr 	operator>= (const Mat &a, const Mat &b)

MatExpr 	operator>= (const Mat &a, double s)

MatExpr 	operator>= (double s, const Mat &a)

MatExpr 	operator> (const Mat &a, const Mat &b)

MatExpr 	operator> (const Mat &a, double s)

MatExpr 	operator> (double s, const Mat &a)

MatExpr 	operator & (const Mat &a, const Mat &b)

MatExpr 	operator & (const Mat &a, const Scalar &s)

MatExpr 	operator & (const Scalar &s, const Mat &a)

MatExpr 	operator| (const Mat &a, const Mat &b)

MatExpr 	operator| (const Mat &a, const Scalar &s)

MatExpr 	operator| (const Scalar &s, const Mat &a)

MatExpr 	operator^ (const Mat &a, const Mat &b)

MatExpr 	operator^ (const Mat &a, const Scalar &s)

MatExpr 	operator^ (const Scalar &s, const Mat &a)

MatExpr 	operator~ (const Mat &m)

MatExpr 	min (const Mat &a, const Mat &b)

MatExpr 	min (const Mat &a, double s)

MatExpr 	min (double s, const Mat &a)

MatExpr 	max (const Mat &a, const Mat &b)

MatExpr 	max (const Mat &a, double s)

MatExpr 	max (double s, const Mat &a)

MatExpr 	abs (const Mat &m)

MatExpr 	abs (const MatExpr &e)





 */



#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


// 含有比较运算符的矩阵表达式：
void test1()
{
	Mat_<double> m1 = (Mat_<double>(3,3)<< 1,2,3,4,5,6,7,8,9);
	Mat_<int> m2 = (Mat_<int>(3,3)<< 1,2,3,4,5,6,7,8,9);
	Mat m;

	m = m1>3;					// m是8S单通道矩阵，即矩阵元素为uchar，满足表达式的元素为255，不满足的为0.


	cout << (m1>=5) << endl;
	cout << m << endl;
	cout << m1.depth() << endl;
	cout << m.depth() << endl;
	cout << m.channels() << endl;
	cout << "m.type() = " << m.type() << endl;

	// 使用convertTo()将比较运算符得到的uchar矩阵转化为double矩阵：
	m.convertTo(m,CV_64FC1);
	cout << "convertTo转换之后m的深度为："<< m.depth() << endl;
	cout << "m = " << m << endl;
	m = m/255;
	cout << "m/255之后，m = \n" << m << endl;



}

// max() min()
void test2()
{
	Mat a,b;



}



int main()
{
	test1();


	return 0;

}
