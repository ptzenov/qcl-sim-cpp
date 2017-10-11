#ifndef _MATRIX_UTILS_HPP_
#define _MATRIX_UTILS_HPP_

#ifdef _TEST_

#include "matrix.hpp"
#include "../common/utils.hpp"

#else

#include <matrix/matrix.hpp>
#include <common/utils.hpp>

#endif

#include <random>


template<typename AMTX, typename BMTX>
class MatrixMult
{
public:

        using ElementType = decltype(typename AMTX::ElementType {} * typename BMTX::ElementType {});

        explicit MatrixMult(AMTX const & a,BMTX const &b,bool element_wise = false) :_a(a), _b(b), _ew(element_wise)
        {
		if (_ew){
			assert(_a.get_dimI() == _b.get_dimI()); 
			assert(_a.get_dimJ() == _b.get_dimJ()); 
		}
		else{
			assert(_a.get_dimJ() == _b.get_dimI());
		}
		_dimI = _a.get_dimI();
                _dimJ = _b.get_dimJ();
        }

        ElementType operator()(size_t i, size_t j) const
        {
                if(_ew)
                        return _a(i,j)*_b(i,j);

                ElementType res {} ;
                for(size_t k = 0; k<_b.get_dimI(); k++)
                        res += _a(i,k)*_b(k,j); // can vectorize! store everything inside cache!
                return res;
        }

        // overload the cast operator!
        operator Matrix<ElementType>()
        {
                Matrix<ElementType> m(_dimI,_dimJ);
                m = *this;
                return m;
        }

        size_t get_dimI() const
        {
                return _dimI;
        }
        size_t get_dimJ() const
        {
                return _dimJ;
        }
private:
        size_t _dimI;
        size_t _dimJ;
        bool _ew;
        AMTX const & _a;
        BMTX const & _b;
};

template<typename T1, typename T2>
MatrixMult<Matrix<T1>, Matrix<T2>> operator*(Matrix<T1> const &A, Matrix<T2> const &B)
{
        return MatrixMult<Matrix<T1>, Matrix<T2>> (A,B);
}

template<typename T1, typename T2>
MatrixMult<Matrix<T1>,Matrix<T2> > mMult(Matrix<T1> const & A, Matrix<T2> const& B)
{
        return MatrixMult<Matrix<T1>, Matrix<T2> > (A,B,true);
}




// summation
template<typename AMTX, typename BMTX>
class MatrixSumDiff
{
public:

        using ElementType = decltype(typename AMTX::ElementType {} + typename BMTX::ElementType {});

        explicit MatrixSumDiff(AMTX const & a,BMTX const &b,bool positive) :_a(a), _b(b)
        {
                assert(_a.get_dimI() == _b.get_dimI());
                assert(_a.get_dimJ() == _b.get_dimJ());
                _dimI = _a.get_dimI();
                _dimJ = _b.get_dimJ();
                if(positive)
                        _sign = 1;
                else
                        _sign = -1;

        }

        ElementType operator()(size_t i, size_t j) const
        {
                return _a(i,j)+_sign*_b(i,j);
        }

        // A = A+(A-A):
        // A-A -> MatrixSumDiff<AMTX,BMTX>
        // implicit cast -> Matrix<ElementType>() -> should occur here!
        //

        operator Matrix<ElementType>() const
        {
                Matrix<ElementType> m(_dimI,_dimJ);
                m = *this; // do the evaluation !
                return m; // return m -> must by copy assignable !
        }

        size_t get_dimI() const
        {
                return _dimI;
        }

        size_t get_dimJ() const
        {
                return _dimJ;
        }

private:
        size_t _dimI;
        size_t _dimJ;
        ElementType _sign;
        AMTX const & _a;
        BMTX const & _b;
};

// sum
template<typename T1, typename T2>
MatrixSumDiff<Matrix<T1>, Matrix<T2> > operator+(Matrix<T1> const &A, Matrix<T2> const &B)
{
        return MatrixSumDiff<Matrix<T1>, Matrix<T2> >(A,B,true);
}



/*
template<typename T1>
Matrix<T1> operator+(Matrix<T1> const &A, Matrix<T1> const &B)
{
	Matrix<T1> res = A;
	for(int i = 0; i<res.get_dimI(); i++)
		for(int j = 0; j<res.get_dimJ(); j++)
			res(i,j) = A(i,j) + B(i,j);
       return res;
}
*/




//difference
template<typename T1, typename T2>
MatrixSumDiff<Matrix<T1>, Matrix<T2>> operator-(Matrix<T1> const &A, Matrix<T2> const &B)
{
        return MatrixSumDiff<Matrix<T1>, Matrix<T2> > (A,B,false);
}

// scaling
template<typename AMTX, typename NUM>
class MatrixScale
{
public:

        using ElementType = decltype(typename AMTX::ElementType {} * NUM {});

        explicit MatrixScale(AMTX const & a,NUM const & num) :_a(a), _num(num)
        {

                _dimI = a.get_dimI();
                _dimJ = a.get_dimJ();

        }

        ElementType operator()(size_t i, size_t j) const
        {
                return _num*_a(i,j);
        }
        operator Matrix<ElementType>()
        {
                Matrix<ElementType> m(_dimI,_dimJ);
                m = *this;
                return m;

        }
        size_t get_dimI() const
        {
                return _dimI;
        }
        size_t get_dimJ() const
        {
                return _dimJ;
        }
private:

        size_t _dimI;
        size_t _dimJ;
        AMTX const & _a;
        NUM const & _num;
};

template<typename T1, typename T2>
MatrixScale<Matrix<T1>,T2> operator*(Matrix<T1> const &A, T2 const &num)
{
        return MatrixScale<Matrix<T1>, T2> (A,num);
}


template<typename T1, typename T2>
MatrixScale<Matrix<T1>,T2> operator*(T2 const &num, Matrix<T1> const & A)
{
        return MatrixScale<Matrix<T1>, T2> (A,num);
}

template<typename _Tp>
std::ostream& operator<<(std::ostream& os, Matrix<_Tp> const & obj)
{
        for (size_t i =0; i < obj.get_dimI(); i++)
        {
                for (size_t j = 0; j < obj.get_dimJ(); j++)
                        os << "" << obj(i,j)  <<" ";  //_data[j+i*_dimJ];
                os << std::endl;
        }
        return os;
}
template<typename _Tp>
std::ostream& operator<<(std::ostream& os, Matrix<_Tp>&& obj)
{
        std::cout << obj;
}





// some more matrix utility stuff !!!
template<typename _Tp>
Matrix<_Tp> eye(size_t M)
{
        Matrix<_Tp> res(M, M, 0);
        for(size_t i=0; i<M; i++)
                res(i,i) = 1;
        return res; // return value optimizaiton??
}

template<typename _Tp>
Matrix<_Tp> realVal(const Matrix<_Tp>& m)
{
        Matrix<_Tp> res(m);
        for (size_t i = 0; i < res.get_dimI(); i++)
                for (size_t j = 0; j < res.get_dimJ(); j++)
                        res(i, j) = REAL(res(i,j));
        return res;
}


template<typename _Tp>
Matrix<_Tp> imagVal(const Matrix<_Tp>& m)
{
        Matrix<_Tp> res(m);
        for (size_t i = 0; i < res.get_dimI(); i++)
                for (size_t j = 0; j < res.get_dimJ(); j++)
                        res(i, j) = IMAG(res(i,j));

        return res;
}


template<typename _Tp>
Matrix<_Tp> conjVal(const Matrix<_Tp>& m)
{
        Matrix<_Tp> res = m;
        for (size_t i = 0; i < res.get_dimI(); i++)
                for (size_t j = 0; j < res.get_dimJ(); j++)
                        res(i, j) = REAL(res(i,j)) - _i*IMAG(res(i,j));
        return res;
}

template<typename _Tp>
Matrix<_Tp> randInit(size_t M,size_t N,int a,int b)
{

        Matrix<_Tp> res(M, N);

        std::random_device rd;
        std::mt19937 mt(rd()); //  32-bit Mersenne Twister by Matsumoto and Nishimura, 1998
        std::uniform_int_distribution<int> dist(a,b);

        for (size_t i = 0; i < M; i++)
                for (size_t j = 0; j < N; j++)
                        res(i, j) = dist(mt);

        return res;
}




#endif
