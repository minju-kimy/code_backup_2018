#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
    Mat img = imread("C:/Users/Public/Pictures/Sample Pictures/1.jpg");//컬러이미지를 넣음
	Mat gray, dst_norm, dst_norm_scaled;
	int thresh = 100;

	cvtColor(img, gray, CV_BGR2GRAY); // rgb컬러로 된것을 그레이로 바꾸는 open cv함수 넣을 이미지, 바뀐 이미지를 넣을곳, 뭘로 바꿀지
	Mat dst = Mat::zeros(gray.size(), CV_32FC1);//이거의 크기는 그레이의 크기와 같은?? 행렬이 하나 만들어짐. 32비트 f타입을 가지는
	cornerHarris( gray, dst, 2, 3, 0.03, BORDER_DEFAULT); //3바이3 공간에서 2는 블럭사이즈 0.03은..?
	//해리스코너에 대한 값이 dst에 들어가있음 

	normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );// 값이 작아서 노멀라이즈 해줌 
  convertScaleAbs( dst_norm, dst_norm_scaled );//앞에것 절대값을 뒤에다 넣음

  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )//dst_norm의 모든 행과 열에 대해서
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh )
              {
               circle(img, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
              }
          }
     }
	imshow("Color", img);
	waitKey(0);
	return 0;
}