#include "GIsystem.h"
#include "GI_linear_reconstructor.h"
#include "GPSR_BB_reconstructor.h"

using namespace std;
using namespace cv;


void test1()
{
	Mat_<double> obj = imread("/Users/wuhan/Downloads/GI_letters.bmp",0);
	GIsystem s = GIsystem(obj);
	Mat_<double> A = s.getA();
	Mat_<double> y = s.getY();
	int MD = s.getMD();
	int ND = s.getND();

	GI_linear_reconstructor giR = GI_linear_reconstructor(MD,ND);
	Mat_<double> image = giR.GIreconstruct(A,y);
	imshow("image", image);
	waitKey(0);

}


// GI线性重构算法，文件的读取和写入。
void test2()
{
	Mat_<double> obj = imread("/Users/wuhan/Downloads/GI_letters.bmp",0);
	GIsystem s = GIsystem(obj);
	Mat_<double> A = s.getA();
	Mat_<double> y = s.getY();
	int MD = s.getMD();
	int ND = s.getND();
	s.saveA();
	s.saveY();


	ifstream fileA("/Users/wuhan/Downloads/A",ios::binary);
	ifstream fileY("/Users/wuhan/Downloads/y",ios::binary);

	Mat_<double> tA;
	Mat_<double> ty;
	fileA.read((char*)(&tA),sizeof(Mat_<double>));
	fileA.close();
	fileY.read((char*)(&ty),sizeof(Mat_<double>));
	fileY.close();
	GI_linear_reconstructor giR = GI_linear_reconstructor(MD,ND);
	giR.GIreconstruct(tA,ty);
	giR.saveImage();
	cout << "finished" << endl;
	waitKey(0);

}

// GPSR_BB算法
void test3()
{
	Mat_<double> obj = imread("/Users/wuhan/Downloads/GI_letters.bmp",0);
	GIsystem s = GIsystem(obj);
	Mat_<double> A = s.getA();
	Mat_<double> y = s.getY();
	int MD = s.getMD();
	int ND = s.getND();

	double sparse_number = 0.0003;
	Mat_<double> temp = cv::abs(transpose(A)*y);
	double maxVal, minVal;
	cv::minMaxIdx(temp,&minVal, &maxVal);
	double tau = sparse_number*maxVal;
	GPSR_BB_reconstructor GPSR = GPSR_BB_reconstructor(MD,ND,tau);

	Mat_<double> image = GPSR.GPSR_BB_reconstruct(A,y);

	imshow("image",image);
	waitKey(0);



}

int main()
{
	//test1();
	//test2();
	test3();


	return 0;
}
