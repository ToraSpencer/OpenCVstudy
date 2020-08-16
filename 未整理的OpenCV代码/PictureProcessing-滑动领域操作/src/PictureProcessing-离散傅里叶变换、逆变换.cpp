#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include "cMat.h"

using namespace std;
using namespace cv;


/* 一维连续傅里叶变换：
 * 			F(u) = $f(t)*exp(-1j*2*pi*t*u)dt;
 * 一维离散傅里叶变换DCT:
 * 			频谱序列序数为j的元素：F(j) = SIGMA(f(i)*exp(-1j*2*pi*i*j/N))， 对f整个序列遍历累加。
 * 			j从0开始。
 * 			f是空域的离散时间信号序列，F是变换到频域的序列，两者长度相同。
 *
 *
 *
 */


//DCT的底层实现：
cMat DCT(cMat f)
{
	cMat factor =
	cMat F = f.clone();
	for(int k = 0; k<=,k++);


}

test1()
{

}
