#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <thread>


using namespace std;

void gauss (int n,double **a,double *b,double *x){
int i,j,k;
int o,p;
double fator , sum;
for(k=0;k<=n-2;k++)
	{
		for(i=k+1;i<=n-1;i++)
		{
			fator=a[i][k]/a[k][k];

			for(j=k+1;j<=n-1;j++)
			{
				a[i][j]=a[i][j]-(fator*a[k][j]);
			}
			b[i]=b[i]-(fator*b[k]);

			a[i][k]=0.0f;
		}

		for(o=0;o<=n-1;o++)
		{
			printf("|");

			for(p=0;p<=n-1;p++)
			{
				printf (" %+g ",a[o][p]);
			}
			printf(" %g| \n",b[o]);
		}
		printf("\n");
	}

	x[n-1]=b[n-1]/a[n-1][n-1];

	for(i=n-1;i>=0;i--)
	{
		sum=0.0f;
		for(j=i+1;j<=n-1;j++)
		{
			sum=sum+a[i][j]*x[j];
		}
		x[i]=(b[i]-sum)/a[i][i];
	}

	for(i=0;i<=n-1;i++)
	{
		printf("x(%i) = %+g \n",i,x[i]);
	}
	//return EXIT_SUCCESS;


}


int main (int argc , char *argv[])
{	
	double **a, *b, *x;
	int i,j,n;

	a=(double **) malloc((n+1)*sizeof(double *));
	b=(double *) malloc((n+1)*sizeof(double));
	x=(double *) malloc((n+1)*sizeof(double));
	 for(i=0;i < n+1;i++)
	 {
	  a[i]=(double *)malloc((n+1)*sizeof(double));
	 }

	printf("Tamanho da matriz NxN");
	scanf("%d",&n);

	printf("\n Defina a matriz A[%dx%d]\n",n,n);

	for(i=0; i<= n-1; i++)
	{
		for(j=0; j<=n-1; j++)
		{
			printf("\n a[%d,%d]=  ",i+1,j+1);
			scanf("%lf",&a[i][j]);
		}
	}
	 
	printf("\n Defina o vetor B(%d)\n",n);
	 
	for(i=0; i<=n-1; i++)
	{
	   printf("\n b[%d]=  ",i+1);
	   scanf("%lf",&b[i]);
	}


	thread t1(gauss,n,a,b,x);
	thread t2(gauss,n,a,b,x);
	t1.join();
	t2.join();
	
}