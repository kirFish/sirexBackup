#include <iostream>
#include <cassert>
#include <cmath>
#include <functional>

using namespace std;

constexpr uint n = 7;

struct Vec2 {
	double x,y;
	constexpr Vec2(double x,double y): x(x),y(x){
		return;
	}
};

constexpr static Vec2 DataArr[n]={Vec2(0.7,0.49),Vec2(0.8,0.64),Vec2(0.9,0.81),Vec2(1,1),Vec2(1.1,1.21),Vec2(1.2,1.44),Vec2(1.3,1.69)};

[[gnu::pure]]
double li(int i,double x){
	double mulU=1;
	double mulD=1;
	for (int j=0;j<n;++j){
		if (i != j){
			mulU*= (x-DataArr[j].x);
			mulD*= (DataArr[i].x-DataArr[j].x);
		}
	};
	return mulU/mulD;
}
[[gnu::pure]]
double Lag(double x){
	double sum=0;
	for (int i=0;i<n;++i){
		sum+=DataArr[i].y * li(i,x);
	}
	return sum;
}

[[gnu::pure]]
double diff_n_of_f_in_p(function<double(double)> f,double x,uint n=1,const uint ezn=6){
	const double eps = 10 ^ -ezn;
	auto df = [&f,eps](double x){
		const double left_apr = (f(x) - f(x-eps))/eps;
		const double right_apr = (f(x+eps)-f(x))/eps;
		const double ret = (left_apr+right_apr)/2;
		//cout<<"#DBG In "<<x<<" "<<n<<"'s diff of func is: "<<ret<<"\n";
		return ret;
	};
	switch (n){
		case 0:
			return f(x);
		case 1:
			return df(x);
		default:
			return diff_n_of_f_in_p(df,x,n-1,ezn);
	};
};

int main(){
	for (uint i = 0;i<n;++i)
		cout<<"Diff in point "<<DataArr[i].x<<": "<<diff_n_of_f_in_p(Lag,DataArr[i].x,1,6)<<"\n";
}

