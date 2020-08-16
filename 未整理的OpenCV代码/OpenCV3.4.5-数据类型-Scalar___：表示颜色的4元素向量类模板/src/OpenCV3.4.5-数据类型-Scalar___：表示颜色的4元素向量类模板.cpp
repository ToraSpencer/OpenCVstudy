#include "cv.h"
#include "highgui.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


//Scalar类的本质是Scalar_类模板的实例化：Scalar_<double>
//一般通过Scalar对象来对多通道图像矩阵进行初始化，四个double数值为每个通道的元素初始值。


//test1():构造Scalar对象
void test1()
{
	cout << "test1():构造Scalar对象:" << endl;
	Scalar s1 = Scalar(1,2,3,4);
	Scalar s2(1,2);
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;


	cout << endl << endl;
}

//test2():利用Scalar对象来构造多通道图像矩阵：
void test2()
{
	cout << "test2():利用Scalar对象来构造多通道图像矩阵：" << endl;
	Mat M1 = Mat(300,300,CV_8UC1,Scalar(0));
	imshow("black grey-scale map",M1);
	waitKey(0);

	Mat M2(300,300,CV_8UC1,Scalar(255));
	imshow("white grey-scale map",M2);
	waitKey(0);

	Mat M3(300,300,CV_8UC3,Scalar(100,0,0));
	imshow("blue RGB map",M3);
	waitKey(0);

	Mat M3_1(300,300,CV_32FC3,Scalar(255,0,0));
	imshow("blue RGB map, type CV_64FC3",M3_1);			//32位浮点数和8位unsigned取值范围不同，所有同样数值对应的实际的色阶是不同的。
	waitKey(0);

	Mat M4(300,300,CV_8UC3,Scalar(100,0,50));			//Scalar前三个数值对应的颜色分别为BGR
	imshow("purple RGB map",M4);
	waitKey(0);




	cout << endl << endl;

}

//test3()：Scalar_<_Tp>类模板的成员方法
void test3()
{
	cout << "test3()：Scalar_<_Tp>类模板的成员方法：" << endl << endl;

	//Scalar_<_T> static all(v0)
	cout << "Static成员方法：Scalar_<_Tp> all(v0)：返回元素值全为v0的Scalar_<_Tp>对象：" << endl;
	Scalar_<double> S31 = Scalar_<double>::all(3.2);
	cout << "Scalar_<double>::all(3.2) = " << S31 << endl;



	cout << endl;
}

//test4():Scalar_<_Tp>类模板的成员数据
void test4()
{
	cout << "test4():Scalar_<_Tp>类模板的成员数据" << endl << endl;

	cout << "使用（下标）来访问成员数据：" << endl;
	Scalar_<double> s1 = Scalar(1,2,3,4);
	cout << "s1(0) = " << s1(0) << endl;
	cout << "typeid(s1(0)).name() = " << typeid(s1(0)).name() << endl;


}


int main(int argc, char** argv)
{
	//test1();
	//test2();
	//test3();
	test4();

	cout << "end of program." << endl;
	getchar();

    return 0;
}
