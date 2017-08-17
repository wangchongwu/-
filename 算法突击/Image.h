//for 8-bit image ,band=1
#pragma once
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>  
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class LimVar
{
public:
	LimVar::LimVar(float k1, float k2):low(k1),high(k2) {};
	double  low;
	double  high;
};

class Image
{
public:
	Image(cv::Mat);
	~Image();
	void showInWindow();//显示

	////////////////////////////---------接口-----///////////////////////////////////
	Image imadjust(LimVar input, LimVar output, float gamma);//灰度拉伸
	LimVar stretchlim(double k1, double k2);//百分比拉伸上下限
	Image getHistImage();	//获得直方图图像
	Image equalizeHist();//直方图均衡化
	Image logTrans();//对数变换
public:
	cv::Mat mat_im;
	std::string matPath;

private:
	vector<int> hist;//直方图
	void getHist();//求直方图
	bool hasHist;//
};

