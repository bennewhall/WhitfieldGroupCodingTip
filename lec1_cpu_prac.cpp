#ifndef __CPU_PRACTICE_h__
#define __CPU_PRACTICE_h__
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

void Test_Branch()
{
	vector<int> a1(1024*1024);
	int s=a1.size();
	for(int i=0;i<s;i++){
		a1[i]=rand()%100;
	}
	//sort(a1.begin(),a1.end());	////difference between sorted and unsorted

	auto start=chrono::system_clock::now();

	int sum=0;
	for(int i=0;i<s;i++){
		if(a1[i]>50){
			sum+=a1[i];
		}
	}

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;
}

void Test_2D_Array_Sum()
{
	const int s=1024;
	int** a=new int*[s];
	for(int i=0;i<s;i++){
		a[i]=new int[s];
		for(int j=0;j<s;j++){
			a[i][j]=rand()%10;
		}
	}

	auto start=chrono::system_clock::now();

	int sum=0;
	for(int i=0;i<s;i++){
		for(int j=0;j<s;j++){
			sum+=a[i][j];	////difference between ij and ji?
		}
	}

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;

	for(int i=0;i<s;i++){
		delete [] a[i];
	}
	delete [] a;
}

double add(const double& a,const double& b){return a+b;}

void Test_Vector_Add()
{
	vector<double> a1(1024*1024,1.);
	vector<double> a2(1024*1024,2.);

	auto start=chrono::system_clock::now();

	//brute-force way
	//for(int i=0;i<a1.size();i++){
	//	a2[i]=add(a2[i],a1[i]);
	//}

	////improved by reducing function calls
	int size=(int)a1.size();
	for(int i=0;i<size;i++){
		a2[i]+=a1[i];
	}

	//////multicore
	//int size=(int)a1.size();
	//#pragma omp parallel for
	//for(int i=0;i<size;i++){
	//	a2[i]+=a1[i];
	//}

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;
}

void Test_Sum_From_Memory()
{
	vector<int> a(100000,1);
	int sum=0;
	int size=a.size();
	auto start=chrono::system_clock::now();

	//brute-force way
	for(int i=0;i<size;i++){
		sum+=a[i];
	}

	////try loop unrolling?
	//int s1=0,s2=0;
	//for(int i=0;i<size;i+=2){
	//	s1+=a[i];
	//	s2+=a[i+1];
	//}
	//sum=s1+s2;

	//////further unrolling?
	//int s1=0,s2=0,s3=0,s4=0;
	//for(int i=0;i<size;i+=4){
	//	s1+=a[i];
	//	s2+=a[i+1];
	//	s3+=a[i+2];
	//	s4+=a[i+3];
	//}
	//sum=s1+s2+s3+s4;

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;	
}

void Test_Sum()
{
	int size=100000;
	int sum=0;

	auto start=chrono::system_clock::now();

	//////brute-force way
	for(int i=0;i<size;i++){
		sum+=i;
	}

	//////loop unrolling
	//for(int i=0;i<size;i+=2){
	//	sum+=i;
	//	sum+=(i+1);
	//}

	//////better loop unrolling
	//for(int i=0;i<size;i+=2){
	//	sum+=(i+i+1);
	//}

	//////instruction level parallelization
	//int s1=0,s2=0;
	//for(int i=0;i<size;i+=2){
	//	s1+=i;
	//	s2+=(i+1);
	//}
	//sum=s1+s2;

	//////further ILP
	//int s1=0,s2=0,s3=0,s4=0;
	//for(int i=0;i<size;i+=4){
	//	s1+=i;
	//	s2+=(i+1);
	//	s3+=(i+2);
	//	s4+=(i+3);
	//}
	//sum=s1+s2+s3+s4;

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;	
	std::cout<<sum<<endl;
}

void Test_Multiplication_And_Division()
{
	int size=1024*1024;
	vector<double> a(size,1.);
	double x=12345.;
	double one_over_x=1./x;
	double y=1.;

	auto start=chrono::system_clock::now();

	for(int i=0;i<size;i++){
		y=y/x;		////replace /x with *one_over_x to observe the difference
	}

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;
}

int main()
{
	for(int k=0;k<100;k++){
		//Test_Multiplication_And_Division();
		Test_Sum();
		//Test_Sum_From_Memory();
		//Test_Vector_Add();
		//Test_2D_Array_Sum();
		//Test_Branch();
	}

}

#endif
