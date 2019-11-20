#include <stdio.h>
#include <math.h>
int main()
{
	FILE *fp, *fp2; 
	unsigned char image[256][256], image2[256][256];
	float f_x[256][256]={0.0,}, f_y[256][256]={0.0,};

	fp = fopen("girl.raw","rb");//읽기용파일 열기
	fp2 = fopen("result.raw","wb");//쓰기용파일 열기

	fread(image,1,256*256,fp); //영상파일읽기

	
	//영상처리
	for(int i=0; i<256-1; i++)
		for(int j=0; j<256-1; j++)
		{
			f_x[i][j] = image[i][j+1]-image[i][j]; //미분
			f_y[i][j] = image[i+1][j]-image[i][j];

			f_x[i][j] = image[i][j+1]-image[i][j-1]; //중간에 노이즈가 있을 수도 있어서 조금 더 넓은 범위를 보겠다? 인듯?? 정확도는 좀 떨어지는..?
			//
			f_y[i][j] = image[i+1][j]-image[i-1][j];
		}

	for(int i=1; i<256-1; i++)
		for(int j=1; j<256-1; j++)
			image2[i][j]=sqrt(f_x[i][j]*f_x[i][j]+f_y[i][j]*f_y[i][j]);
 
	fwrite(image2,1,256*256,fp2); //영상파일쓰기


}