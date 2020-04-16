//Originally From Bo Zhu, Edited by Ben Newhall
#include <chrono>

#include <iostream>

using namespace std;


void test()
{
	
	int size=2090000;
	int a[size];
	int sum=0;
	for(int i = 0; i<size;i+=4){
		a[i]=1;
		a[i+1]=23;
		a[i+2]=934;
		a[i+3]=-67;
	}
	auto start=chrono::system_clock::now();

	// //stupid way
	// for(int i=0; i<a.size();i++){
	// 	sum+=a[i];
	// }

	//brute-force way
	// for(int i=0;i<size;i++){
	// 	sum+=a[i];
	// }

	// //try loop unrolling?
	// int s1=0,s2=0;
	// for(int i=0;i<size;i+=2){
	// 	s1+=a[i];
	// 	s2+=a[i+1];
	// }
	// sum=s1+s2;

	// ////further unrolling?
	// int s1=0,s2=0,s3=0,s4=0;
	// for(int i=0;i<size;i+=4){
	// 	s1+=a[i];
	// 	s2+=a[i+1];
	// 	s3+=a[i+2];
	// 	s4+=a[i+3];
	// }
	// sum=s1+s2+s3+s4;

	//EVEN FURTHER??
	// int s1=0,s2=0,s3=0,s4=0,s5=0,s6=0,s7=0,s8=0,s9=0,s10=0;
	// for(int i=0;i<size;i+=10){
	// 	s1+=a[i];
	// 	s2+=a[i+1];
	// 	s3+=a[i+2];
	// 	s4+=a[i+3];
	// 	s5+=a[i+4];
	// 	s6+=a[i+5];
	// 	s8+=a[i+6];
	// 	s9+=a[i+7];
	// 	s10+=a[i+8];
	// }
	// sum=s1+s2+s3+s4+s5+s6+s7+s8+s9+s10;

	//Loop unrolling approaches a limit of how much benefit it can give around 10ish unrolls. The program is memory bound, and we have to find ways to access memory less frequently
	//This solution is adapted from A person in the HPC class
	// long s1 = 0; 
	// long s2 = 0;
	// long s3 = 0;
	// long s4=0;

    // const long* l= (long*)(&a[0]);
	// int i = 0;
	// for(;i<size-8;i+=8){
	// 	s1+=l[(i >> 1)];
	// 	s2+=l[(i >> 1)+1];
	// 	s3+=l[(i >> 1)+2];
	// 	s4+=l[(i >> 1)+3];
	// }
	// for(;i<size;++i){
	// 	s1+= a[i];
	// }
	// sum = (int) (s1 & 0xFFFFFFFFL) + (s1 >> 32) +
	// (s2 & 0xFFFFFFFFL) + (s2 >> 32) +
	// (s3 & 0xFFFFFFFFL) + (s3 >> 32) +
	// (s4 & 0xFFFFFFFFL) + (s4 >> 32);

//NOW ITS MY TURN

	// long s1 = 0; 
	// long s2 = 0;
	// long s3 = 0;
	// long s4=0;

	// struct superlong{
	// 	long x;
	// 	long y;
	// 	long z;
	// 	long w;
	// };

    // const superlong* l= (superlong*)(&a[0]);

	// int i = 0;

	// for(;i<size-32;i+=32){
	// 	s1+=l[(i >> 4)].x +l[(i >> 4)].y +l[(i >> 4)].z +l[(i >> 4)].w;
	// 	s2+=l[(i >> 4)+1].x +l[(i >> 4)+1].y +l[(i >> 4)+1].z +l[(i >> 4)+1].w;
	// 	s3+=l[(i >> 4)+2].x +l[(i >> 4)+2].y +l[(i >> 4)+2].z +l[(i >> 4)+2].w;
	// 	s4+=l[(i >> 4)+3].x +l[(i >> 4)+3].y +l[(i >> 4)+4].z +l[(i >> 4)+4].w;
	// }
	// for(;i<size;++i){
	// 	s1+= a[i];
	// }
	// sum = (int) (s1 & 0xFFFFFFFFL) + (s1 >> 32) +
	// (s2 & 0xFFFFFFFFL) + (s2 >> 32) +
	// (s3 & 0xFFFFFFFFL) + (s3 >> 32) +
	// (s4 & 0xFFFFFFFFL) + (s4 >> 32);

//ok.... that was a little better, not perfect however
//I want perfect.

	long s1 = 0; 
	long s2 = 0;
	long s3 = 0;
	long s4=0;
	long s5 = 0; 
	long s6 = 0;
	long s7 = 0;
	long s8=0;
	long s9 = 0; 
	long s10 = 0;
	struct superlong{
		long x;
		long y;
		long z;
		long w;
	};

    const superlong* l= (superlong*)(&a[0]);

	int i = 0;

	for(;i<size-80;i+=80){
		s1+=l[(i >> 4)].x +l[(i >> 4)].y +l[(i >> 4)].z +l[(i >> 4)].w;
		s2+=l[(i >> 4)+1].x +l[(i >> 4)+1].y +l[(i >> 4)+1].z +l[(i >> 4)+1].w;
		s3+=l[(i >> 4)+2].x +l[(i >> 4)+2].y +l[(i >> 4)+2].z +l[(i >> 4)+2].w;
		s4+=l[(i >> 4)+3].x +l[(i >> 4)+3].y +l[(i >> 4)+3].z +l[(i >> 4)+3].w;
		s5+=l[(i >> 4)+4].x +l[(i >> 4)+4].y +l[(i >> 4)+4].z +l[(i >> 4)+4].w;
		s6+=l[(i >> 4)+5].x +l[(i >> 4)+5].y +l[(i >> 4)+5].z +l[(i >> 4)+5].w;
		s7+=l[(i >> 4)+6].x +l[(i >> 4)+6].y +l[(i >> 4)+6].z +l[(i >> 4)+6].w;
		s8+=l[(i >> 4)+7].x +l[(i >> 4)+7].y +l[(i >> 4)+7].z +l[(i >> 4)+7].w;
		s9+=l[(i >> 4)+8].x +l[(i >> 4)+8].y +l[(i >> 4)+8].z +l[(i >> 4)+8].w;
		s10+=l[(i >> 4)+9].x +l[(i >> 4)+9].y +l[(i >> 4)+9].z +l[(i >> 4)+9].w;

	}
	for(;i<size;++i){
		s1+= a[i];
	}
	sum = (int) (s1 & 0xFFFFFFFFL) + (s1 >> 32) +
	(s2 & 0xFFFFFFFFL) + (s2 >> 32) +
	(s3 & 0xFFFFFFFFL) + (s3 >> 32) +
	(s4 & 0xFFFFFFFFL) + (s4 >> 32) +
	(s5 & 0xFFFFFFFFL) + (s5 >> 32) +
	(s6 & 0xFFFFFFFFL) + (s6 >> 32) +
	(s7 & 0xFFFFFFFFL) + (s7 >> 32) +
	(s8 & 0xFFFFFFFFL) + (s8 >> 32) +
	(s9 & 0xFFFFFFFFL) + (s9 >> 32) +
	(s10 & 0xFFFFFFFFL) + (s10 >> 32);

//possibly went too far with this last one.

	auto end=chrono::system_clock::now();
	chrono::duration<double> t=end-start;
	cout<<"result: "<<sum<<endl;
	cout<<"run time: "<<t.count()*1000.<<" ms."<<endl;	
}


int main()
{
		test();
}

