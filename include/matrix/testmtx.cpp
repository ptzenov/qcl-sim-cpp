#include <iostream>



#define _TEST_
#include "matrixutils.hpp"


int main(){

	Matrix<double> A(5,5,0);
	A(2,2) = 1.;
	std::cout<<"\n A:= \n" << A; 
	A.set_index_frame(1,4,1,4);
	// in the new index frame! 
	A(0,0) = 1.; 
	A(1,1) = 1.; 
	A(2,2) = 1.; 
		
	Matrix<double>B(3,3,2); 
	Matrix<double>C(3,3,3); 
	Matrix<double> D = A + static_cast< Matrix<double> >(B+C); // copy assignment -> D should be 3x3 

	C = A*B; 
	std::cout<<"\n A:= \n" << A; 
	std::cout<<"\n B:= \n" << B; 
	std::cout<<"\n C:= \n" << C; 
	std::cout<<"\n D:= \n" << D; 
	A.reset_index_frame();
	std::cout<<"\n A:= \n" << A; 
	A = static_cast<Matrix<double>>(A+A)-A; 
	std::cout << "\n (A+A)-A = \n" << A;
// matrix vector multiplication test! 
	Matrix<double> a(1,5,1);
	Matrix<double> a2(1,5,1);

	Matrix<double> b(5,1,2);
	Matrix<double> b2(5,1,2);
       	Matrix<double> c = a*b;
       	Matrix<double> d = b*a;
	Matrix<double> e = a+a2;
       	Matrix<double> f = a-a2;
       	Matrix<double> g = b+b2;
       	Matrix<double> h = b-b2;


	std::cout << "\n a = \n"<< a; 
	std::cout << "\n b = \n"<< b;
	std::cout << "\n c = a*b \n"<< c;
	std::cout << "\n d = b*a \n"<< d;
	std::cout << "\n e = a+a2 \n"<< e;
	std::cout << "\n f = a-a2 \n"<< f;
	std::cout << "\n e = b+b2 \n"<< g;
	std::cout << "\n g = b-b2 \n"<< h;

	a(0,3) = 0; 
	a.set_index_frame(0,1,3,4); 
	std::cout << "\n a[0,0,3,4] = \n " <<  a; 
	









}

