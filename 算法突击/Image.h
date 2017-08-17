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
	void showInWindow();//��ʾ

	////////////////////////////---------�ӿ�-----///////////////////////////////////
	Image imadjust(LimVar input, LimVar output, float gamma);//�Ҷ�����
	LimVar stretchlim(double k1, double k2);//�ٷֱ�����������
	Image getHistImage();	//���ֱ��ͼͼ��
	Image equalizeHist();//ֱ��ͼ���⻯
	Image logTrans();//�����任
public:
	cv::Mat mat_im;
	std::string matPath;

private:
	vector<int> hist;//ֱ��ͼ
	void getHist();//��ֱ��ͼ
	bool hasHist;//
};

