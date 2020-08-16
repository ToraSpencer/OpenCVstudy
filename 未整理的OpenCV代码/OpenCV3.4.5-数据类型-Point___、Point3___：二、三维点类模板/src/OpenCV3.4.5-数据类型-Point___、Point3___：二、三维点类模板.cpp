#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

//二维平面点类：Point2i, Point2f, Point2d;
void test1()
{
	cout << "二维平面点类：Point2i, Point2f, Point2d;" << endl << endl;

	cout << "Point2i, Point_<int>, Point三种命名是等价的。" << endl;
	cout << "Point2f, Point_<float>两种命名是等价的。" << endl;
	cout << "Point2d, Point_<double>两种命名是等价的。" << endl;
	cout << "以上三个二维平面点类都是类模板Point_< _Tp >的实现。" << endl;
	cout << endl;


	cout << "二维平面点对象的构造函数：" << endl;
	Point2d A(1,2);
	cout << "Point2d A(1,2); A = " << A << endl;
	cout << endl;

	cout << "二维平面类的成员数据：" << endl;
	cout << "点的x坐标：A.x = " << A.x << endl;
	cout << "点的y坐标：A.y = " << A.y << endl;
	cout << endl;

	cout << "点对象放入vector容器构造点列向量：" << endl;
	vector<Point2d> v(10);
	for(size_t i = 0; i<v.size();i++)
	{v[i] = Point2d(3*(double)i,-(double)i);}
	cout << "v = \n" << v << endl;
	cout << endl;


	cout << endl << endl;
}

//三维空间点类：Point3i, Point3f, Point3d;
void test2()
{
	cout << "三维空间点类：Point3i, Point3f, Point3d;" << endl << endl;

	cout << "Point3i, Point3_<int>两种命名是等价的。" << endl;
	cout << "Point3f, Point3_<float>两种命名是等价的。" << endl;
	cout << "Point3d, Point3_<double>两种命名是等价的。" << endl;
	cout << "以上三个三维空间点类都是类模板Point3_< _Tp >的实现。" << endl;
	cout << endl;













	cout << endl;
}


int main(int argc, char** argv)
{
	test1();

    return 0;
}
