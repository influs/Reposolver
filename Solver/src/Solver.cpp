//============================================================================
// Name        : Solver.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<math.h>
#include<fstream>
#include"matrix.h"
#define n 10
using namespace std;
double f(double,double);

double f(double x,double y)
{
	return x*x+y*y;
}
int main(void)
{

	int i,j;
	double h1;
	matrix a(n,n),b(n,n),c(n,n);
	matrix U[n],F[n],alfa[n],betta[n];
	fstream fout("2.xls", ios::out);
    fout.precision(2);
	h1 = 1./(n-1.);

	for(i=0;i<n;i++)
		{
			U[i].SetSize(n,1);
			F[i].SetSize(n,1);
			alfa[i].SetSize(n,n);
			betta[i].SetSize(n,1);
		}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if (i==j)
			{	a(i,j)=1./(h1*h1);
				c(i,j)=1./(h1*h1);
			}
			else
			{	a(i,j)=0;
				c(i,j)=0;
			}
		}



	for(i=1;i<n-1;i++)
		for(j=1;j<n-1;j++)
		{
			if (i==j)
			{
				b(i,j)=-4./(h1*h1);
			}

			else if(fabs(i-j)==1)
			{
				b(i,j)=1./(h1*h1);
			}
			else
			{
				b(i,j)=0;
			}
		}

b(0,0)=-4./(h1*h1);
b(n-1,n-1)=-4./(h1*h1);
b(1,0)=1./(h1*h1);
b(0,1)=1./(h1*h1);
b(n-1,n-2)=1./(h1*h1);
b(n-2,n-1)=1./(h1*h1);


for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			fout<<b(i,j)<<" ";
		fout<<endl;
	}
//border conditions
//left,right
for(j=1;j<n;++j)
{
    U[0](j,0) = f(0.,(j)*h1);
    U[n-1](j,0) = f(1.,(j)*h1);
}
//up,down
for(i=1;i<n;++i)
{
	U[i](0,0) = f((i)*h1,0.);
	U[i](n-1,0) = f((i)*h1,1.);
}
cout<<U[0]<<endl;
cout.precision(2);
for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{

		cout<<U[i](j,0)<<"\t";
		}

		cout<<endl;
	}

//vektor F[n]

	for(i=0;i<n;i++)
	{
		F[i](0,0)= 4. - U[i](0,0)/h1/h1;
		F[i](n-1,0)= 4. - U[i](n-1,0)/h1/h1;
		//init F internal

		for(j=1;j<n-1;++j)
		{
		    F[i](j,0) = 4.;
		}


	}

fout<<endl;
fout<<endl;
fout<<endl;

	for (j=0;j<n;j++)
		{
			alfa[1].Null();
			betta[1](j,0)=U[0](j,0);
		}

	for(i=1;i<n-1;i++)
		{
			for(j=1;j<n-1;j++)
			{
			alfa[i+1]=!(a*alfa[i]+b)*(-c);
			betta[i+1]=!(a*alfa[i]+b)*(F[i]-a*betta[i]);
			}
		}

	for(i=n-2;i>=0;i--)
	{
			U[i]=alfa[i+1]*U[i+1]+betta[i+1];

	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		fout<<U[i](j,0)<<" ";
		}

		fout<<endl;
	}

	fout.close();
	return(0);
}
