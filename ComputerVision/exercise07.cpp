#include <stdio.h>
#include <math.h>
int main()
{
	FILE *fp, *fp2; 
	unsigned char image[256][256], image2[256][256];
	float f_x[256][256]={0.0,}, f_y[256][256]={0.0,};
	float th = 15000.0;

	fp = fopen("girl.raw","rb");//읽기용파일 열기
	fp2 = fopen("result.raw","wb");//쓰기용파일 열기

	fread(image,1,256*256,fp); //영상파일읽기

	for(int i=0; i<256; i++)
		for(int j=0; j<256; j++)
			image2[i][j] = image[i][j];


	//영상처리
	for(int i=1; i<256-1; i++)
		for(int j=1; j<256-1; j++)
		{
			f_x[i][j] = image[i][j]-image[i][j-1]; //미분 d_x
			f_y[i][j] = image[i][j]-image[i-1][j]; // d_y
		}

	for(int i=1; i<256-1; i++)
		for(int j=1; j<256-1; j++)
		{
			float d_x_square_sum=0, d_y_square_sum=0, d_x_d_y_sum=0, eigen_sum=0, eigen_mul=0, c;

			for(int k1=-1; k1<=1; k1++)
				for(int k2=-1; k2<=1; k2++)
				{
					d_x_square_sum += f_x[i+k1][j+k2]*f_x[i+k1][j+k2]; //마스크 내의 d_x*d_x 값들의 합
					d_y_square_sum += f_y[i+k1][j+k2]*f_y[i+k1][j+k2]; // 마스크 내의 d_y*d_y 값들의 합
					d_x_d_y_sum += f_x[i+k1][j+k2]*f_y[i+k1][j+k2];
				}
			eigen_sum = d_x_square_sum + d_y_square_sum;
			eigen_mul = d_x_square_sum * d_y_square_sum - d_x_d_y_sum * d_x_d_y_sum;

			c = eigen_mul - 0.05 * eigen_sum * eigen_sum;

			if(c > th)
				for(int n1=-1; n1<2; n1++)
					for(int n2=-1; n2<2; n2++)
						image2[i+n1][j+n2] = 255;
		}

	
	fwrite(image2,1,256*256,fp2); //영상파일쓰기


}
