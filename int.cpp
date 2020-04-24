#include <iostream>
#include <string>
#include <cmath>
//#include "gtest.h"

using namespace std;



constexpr int koefs[6][6] = {
 { 19    , 75     , 50     , 0      ,  0      , 0      }, //n=6
 { 41    , 216    , 27     , 272    ,  0      , 0      }, //n=7
 { 751   , 3577   , 1323   , 2989   ,  0      , 0      }, //n=8
 { 989   , 5888   , -928   , 10496  , -4540   , 0      }, //n=9
 { 2857  , 15741  ,  1080  , 19344  ,  5778   , 0      }, //n=10
 { 16067 , 106300 , -48525 , 272400 , -260550 , 427368 }, //n=11
 };
constexpr int hs[6] = { 288 , 840 , 17280 , 28350 , 89600 , 598752 };


double func(double x){
    return x*x*sin(x)/cos(x)/cos(x);
}


constexpr double Rectangle( double a, double b, int n, double(*func)(double) ) {
	const double h = (b - a)/n;

	double res = (func(a) + func(b))/2;

	for (int i = 1;i < n; i++) {
		res = res + func(a+i*h);
	}

	res = res * h;

	return res;
}
constexpr double Kotes( double a, double b, int n, double(*func)(double) ) {
	const double h = (b - a) / n;
	double res = func(a) + func(b);


	for (int i = 2; i < n-1; i+=2) {
		res += 2*func(a+i*h);
	}
	for (int i = 1; i < n; i+=2) {
		res += 4*func(a+i*h);
	}
	res = res * h / 3;
	return res;
}

constexpr double ClosedType( double a, double b, int n, double(*func)(double) ) {
	double res = 0;
    int N = ceil(n/2);
    double h = (b-a)/(n-1);
	for (int i = 0; i < N; i+=1) {
		res = res+koefs[n-6][i]*(func(a+i*h)+func(b-i*h));
	}
        res += koefs[n-6][N]*(func(a+N*h));

        res =res*h*(n-1);
        res =res/hs[n-6];
    return res;

}

constexpr double ChooseYourMethod( double a, double b, int n, double(*func)(double) ,double (*Name)(double,double,int,double(*func)(double))){
return Name(a, b, n,func);
}

int main(){
cout<<"Rectangle method = "                             <<ChooseYourMethod(0.0,1.0,200,func,Rectangle)<<endl;
cout<<"Kotes formula = "                                <<ChooseYourMethod(0.0,1.0,200,func,Kotes)<<endl;
cout<<"Closed quadrature formula with 6 points = "      <<ChooseYourMethod(0.0,1.0,6,func,ClosedType)<<endl;
cout<<"Closed quadrature formula with with 11 points = "<<ChooseYourMethod(0.0,1.0,11,func,ClosedType)<<endl;
}


