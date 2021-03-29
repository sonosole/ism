#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ( (x)<(0)?(-x):(x) )

void ism(float xr,float yr,float zr,  /* 房间尺寸 */
		 float xs,float ys,float zs,  /* 声源坐标 */
		 float xm,float ym,float zm,  /* 听者坐标 */
		 int I, int J, int K,         /* 镜像总数 */
		 float a,                     /* 反射系数 */
		 float f                      /* 采样频率 */
		)
{
	float *x = (float *)malloc( sizeof(float)*((I<<1)+1) );
	float *y = (float *)malloc( sizeof(float)*((J<<1)+1) );
	float *z = (float *)malloc( sizeof(float)*((K<<1)+1) );

	int length = ((I<<1)+1)*((J<<1)+1)*((K<<1)+1);
	float *h = (float *)malloc( sizeof(float)*length );

	for(int i = -I; i <= I; i++)
	{
		if(i%2)
			x[i+I] = -xs + (i+1)*xr - xm;
		else
			x[i+I] =  xs +     i*xr - xm;
	}

	for(int j = -J; j <= J; j++)
	{
		if(j%2)
			y[j+J] = -ys + (j+1)*yr - ym;
		else
			y[j+J] =  ys +     j*yr - ym;
	}

	for(int k = -K; k <= K; k++)
	{
		if(k%2)
			z[k+K] = -zs + (k+1)*zr - zm;
		else
			z[k+K] =  zs +     k*zr - zm;
	}
	
	for(int i = -I; i <= I; i++){
		for(int j = -J; j <= J; j++){
			for(int k = -K; k <= K; k++){
				float d = sqrt( x[i+I]*x[i+I] + y[j+J]*y[j+J] + z[k+K]*z[k+K] );
				float t = d / 344;
				int n = (int)(f*t);
				if( h[n] )
					h[n] += pow( a, ABS(i) + ABS(j) + ABS(k) ) / d;
				else
					h[n] = pow( a, ABS(i) + ABS(j) + ABS(k) ) / d;
			}
		}
	}

	for(int i = 0; i < length; i++){
		printf("%.4f\n",h[i]);
	}
	free(h);
	h==NULL;
}

int main(){
	ism(3.5,4.2,2.5, 1.1,2.5,1.7, 2,3,1, 12,12,12, -0.8, 16000.0);
	return 0;
}