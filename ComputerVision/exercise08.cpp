#include <stdio.h>
#include <math.h>
int main()
{
	//temp = 112,99    148,116
	//search = 102,79	216,133
	FILE *fp, *fp2; 
	unsigned char image[256][256], image2[256][256];
	long int min = 1000000000;
	int x_position, y_position;

	fp = fopen("woman1.raw","rb");//읽기용파일 열기
	fp2 = fopen("result.raw","wb");//쓰기용파일 열기

	fread(image,1,256*256,fp); //영상파일읽기

	int temp_histo[256];

	//비교할것 a 히스토생성
	for(int i=99; i<116; i++)
		for(int j=112; j<148; j++)
			for(int k=0; k<256; k++)
				if(image[i][j]==k)
				{
					temp_histo[k]++;
					break;
				}

	long int distance;

	for(int search_y = 79; search_y<133; search_y++)  //17
		for(int search_x = 166; search_x<216; search_x++)  //36
		{
			int comp_histo[256] = {0};
			distance = 0;
			for(int a1=0; a1<17; a1++)
				for(int a2=0; a2<36; a2++)
				{
					for(int k=0; k<256; k++)
						if(image[search_y+a1][search_x+a2]==k)
						{
							comp_histo[k]++;
						}
				}

			for(int c=0; c<256; c++)
				distance += (temp_histo[c]-comp_histo[c])*(temp_histo[c]-comp_histo[c]);

			if(distance<min)
			{
				min = distance;
				x_position = search_x;
				y_position = search_y;
			}
		}
		

	for(int i=0; i<256; i++)
		for(int j=0; j<256; j++)
			image2[i][j]=image[i][j];

	for(int i=y_position; i<y_position+17; i++)
	{
		for(int j=x_position; j<x_position+36; j++)
		{
			image2[i][j]=0;
		}
	}

	for(int i=99; i<116; i++)
		for(int j=112; j<148; j++)
			image2[i][j]=255;
	fwrite(image2, 1,256*256, fp2);
	

}
