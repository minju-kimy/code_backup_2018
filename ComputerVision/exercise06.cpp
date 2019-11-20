#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
	Mat gray;
	Mat img = imread("C:\\Users\\Administrator\\Downloads\\test.png");
	cvtColor(img, gray, CV_BGR2GRAY);//(어느영상을 불러와, 어디에다 저장해, 어떻게 바꿔) cvtColor가 함수인듯?
	//Mat gray2 = Mat::zeros(gray.size(), CV_8UC1);//gray.size하면 그대로 가져와 같은 크기 만듬
	Mat gray_blur = Mat::zeros(gray.rows, gray.cols, CV_8UC1);

	blur( gray, gray_blur, Size( 3, 3 ) ); //원래 영상, 나중영상, 크기카우시안 커널  >> opencv코드이고 가우시안필터?

	
	Mat gray2 = Mat::zeros(gray.rows/2, gray.cols/2, CV_8UC1);
	Mat gray3 = Mat::zeros(gray.rows/2, gray.cols/2, CV_8UC1);
	Mat gray4 = Mat::zeros(gray.rows/3, gray.cols/3, CV_8UC1);

	for(int j=0; j<gray2.rows; j++)
		for(int i=0; i<gray2.cols; i++)
			gray2.at<unsigned char>(j,i) = gray_blur.at<unsigned char>(2*j, 2*i); //가우시안(블러 적용 후) 1/2로 줄임 1/4

	for(int j=0; j<gray3.rows; j++)
		for(int i=0; i<gray3.cols; i++)
			gray3.at<unsigned char>(j,i) = gray.at<unsigned char>(2*j, 2*i); //그냥 1/2로 줄임 정확히는 1/4

	for(int j=0; j<gray4.rows; j++)
		for(int i=0; i<gray4.cols; i++)
			gray4.at<unsigned char>(j,i) = gray_blur.at<unsigned char>(3*j, 3*i); //블러 넣은 후 사진크기 1/3 으로 줄인거 정확히는 1/9배 줄인거

	imshow("gray", gray);
	imshow("gray_blur", gray_blur);
	imshow("gray2", gray2);
	imshow("gray3", gray3);
	imshow("gray4", gray4);

	waitKey(0);
	return 0;
}