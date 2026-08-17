#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

int main(int argc, char** argv) {
	INPUT:int k;
	cout << "Input nth prime: ";
	cin >> k;
	int l, m=3, n, o;
	int*p=new int[k]; p[0]=2, p[1]=m;
	auto start_time = std::chrono::system_clock::now();
	
	for(n=2;m+=2,n<k;p[n]=m,n++,l=1)
		for(o=3;o*o<=m;(m%o==0?m+=2,l=1:l++),o=p[l]);
	
	std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - start_time;
	cout << "Time elapsed " << std::fixed << setprecision(3) << elapsed_time.count() << " seconds" << std::endl;
	cout << std::to_string(k) << ". prime is: " << std::to_string(p[k-1]) << std::endl << std::endl;
	delete[] p;
	goto INPUT;
}
