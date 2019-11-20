#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
	Mat gray;
	Mat img = imread("C:\\Users\\Administrator\\Downloads\\test.png");
	cvtColor(img, gray, CV_BGR2GRAY);//(어느영상을 불러와, 어디에다 저장해, 어떻게 바꿔) cvtColor가 함수인듯?
	//Mat gray2 = Mat::zeros(gray.size(), CV_8UC1);//gray.size하면 그대로 가져와 같은 크기 만듬
	
	Mat gray2 = Mat::zeros(gray.rows*2, gray.cols*2, CV_8UC1);
	

	for(int j=0; j<gray2.rows; j+=2)
		for(int i=0; i<gray2.cols; i+=2)
		{
			gray2.at<unsigned char>(j,i) = gray.at<unsigned char>(j/2, i/2); 
			gray2.at<unsigned char>(j+1,i) = gray.at<unsigned char>(j/2, i/2); 
			gray2.at<unsigned char>(j,i+1) = gray.at<unsigned char>(j/2, i/2); 
			gray2.at<unsigned char>(j+1,i+1) = gray.at<unsigned char>(j/2, i/2); 
		}


	imshow("gray", gray);
	imshow("gray2", gray2);


	waitKey(0);
	return 0;
}