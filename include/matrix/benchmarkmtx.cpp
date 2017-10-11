#include <iostream>

#define _TEST_
#include "matrixutils.hpp"
#include <chrono>


int main(){
	
	int N = 10;
	size_t repetitions = 3; 
	size_t steps = 100000; 

	double complexity = N*N*N; 
	Matrix<double> A(N,N,1); 
	Matrix<double> B(N,N,2); 
	
	Matrix<double> C(N,N,0); 


	for(size_t rep = 0U; rep < repetitions; rep++)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> start,end; 
		start = std::chrono::high_resolution_clock::now(); 
		for(size_t step = 0U; step < steps; step++)
			C = A*B;
		
		end = std::chrono::high_resolution_clock::now(); 
		std::chrono::duration<double> elapsedTime = end-start;
		if (C(0,0) != 2.0*N) {std::cerr << "\n BAD MULTIPLICATION \n";}
		double seconds(elapsedTime.count()); 
		double Mflops = (complexity*steps)/(seconds*1E6); // 
		std::cout << " RUN " << rep+1 <<":" << seconds << "s (" << Mflops << " Mflops)" << std::endl; 	
	} 

}
