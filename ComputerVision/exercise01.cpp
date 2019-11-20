#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
CvCapture* capture = cvCaptureFromCAM(0);
Mat frame, gray;
    frame = cvQueryFrame(capture);
cvtColor(frame, gray, CV_BGR2GRAY);
Mat gray2 = Mat::zeros(gray.size(), CV_8UC1);

while(capture) {
    frame = cvQueryFrame(capture);
cvtColor(frame, gray, CV_BGR2GRAY);//이부분은 주변의 점 평균을 해와서 좀 흐릿해 지게 만드는
for(int j = 1; j<gray.rows-1; j++)
	for(int i = 1; i < gray.cols-1; i++)
	{
		gray2.at<unsigned char>(j,i)=//(j,i)주변 8개 점의 평균   
		(
		gray.at<unsigned char>(j-1, i-1)+
		gray.at<unsigned char>(j, i-1)+
		gray.at<unsigned char>(j+1, i-1)+
		gray.at<unsigned char>(j-1, i)+
		gray.at<unsigned char>(j, i)+
		gray.at<unsigned char>(j+1, i)+
		gray.at<unsigned char>(j-1, i+1)+
		gray.at<unsigned char>(j, i+1)+
		gray.at<unsigned char>(j+1, i+1)
		)/9.0;
	}
equalizeHist(gray, gray2);
    imshow("Color", frame);
imshow("Gray", gray);
imshow("Gray2", gray2);

if(cvWaitKey(33) == 27)break;
} // while의끝
waitKey(0);
cvReleaseCapture(&capture);
cvDestroyWindow("Color");
return 0;
}