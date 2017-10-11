#ifndef _MATRIX_
#define _MATRIX_

//#include <common/utils.hpp>

#include <memory>
#include <algorithm>

#include <assert.h>

#include <stdlib.h>
/***************************************************************
 * Usual 2D matrix of size dimI x dimJ
 ***************************************************************/

template<typename _Tp>
class Matrix
{
public:
        using ElementType = _Tp;
        Matrix() = delete; // disable the default constructor
        // ctor
        Matrix(size_t dim_i, size_t dim_j) 
		: _dimI(dim_i), _dimJ(dim_j),
                  _bytes(dim_i*dim_j*sizeof(_Tp)),
                _data( new _Tp[dim_i*dim_j] {})
        {
                _size = _dimI*_dimJ;
                _i0 = 0;
                _i1 = _dimI;
                _j0 = 0;
                _j1 = _dimJ;
        }

        Matrix(size_t dim_i, size_t dim_j, _Tp const & val): Matrix(dim_i,dim_j)
        {
                std::fill(_data.get(),_data.get()+_size, val);
        }
        Matrix(Matrix<_Tp> const & arg): Matrix(arg.get_dimI(),arg.get_dimJ())
        {
                for(size_t i = 0; i < _dimI; i++)
                        std::copy_n(~arg+arg._j0 + (i+arg._i0)*arg._dimJ,
                                    arg.get_dimJ(), ~(*this) + i*_dimJ);

        }
        // copy assignment operator
        Matrix<_Tp>& operator=(Matrix<_Tp> const & arg)
        {
                assert(arg.get_dimI() == get_dimI());
                assert(arg.get_dimJ() == get_dimJ());

                for(size_t i = _i0; i < _i1; i++)
                        std::copy_n(~arg+arg._j0 + (i+arg._i0)*arg._dimJ,
                                    arg.get_dimJ(), ~(*this) +_j0 + i*_dimJ);
                return *this;
        }
        // move ctor
        Matrix(Matrix<_Tp>&& arg): Matrix(arg.get_dimI(),arg.get_dimJ())
	{ 
		for(size_t i = _i0; i < _i1; i++)
		{	
			_Tp* first1 = ~arg+arg._j0 + (i+arg._i0)*arg._dimJ;
			_Tp* first2 = ~(*this)+_j0 + i*_dimJ;
			std::swap_ranges(first1, first1+arg.get_dimJ(), first2);
		}
	}

        // move assignment o
        Matrix& operator=(Matrix<_Tp>&& arg)
        {
                assert(arg.get_dimI() == get_dimI());
                assert(arg.get_dimJ() == get_dimJ());
                for(size_t i = _i0; i < _i1; i++)
		{	
			_Tp* first1 = ~arg+arg._j0 + (i+arg._i0)*arg._dimJ;
			_Tp* first2 = ~(*this) +_j0 + i*_dimJ;
			std::swap_ranges(first1, first1+arg.get_dimJ(), first2);
		}

		return *this;
        }

        template <typename E>
        Matrix(E const & expr)
                : Matrix(expr.get_dimI(),expr.get_dimJ())
        {
                for(size_t i=_i0; i<_i1; i++)
                        for(size_t j=_j0; j<_j1; j++)
                                _data[j+i*_dimJ] = expr(i,j);
        }
        // expression copy assignment operator;
        template<typename E>
        Matrix& operator=(E const& expr)
        {
                for(size_t i=_i0; i<_i1; i++)
                        for(size_t j=_j0; j<_j1; j++)
                                _data[j+i*_dimJ] = expr(i,j);

                return *this;
        }
        //	destructor
        virtual ~Matrix()
        {
                ;
        }
        _Tp& operator()(size_t i, size_t j)
        {
                assert(i+_i0 < _i1 && j+_j0 < _j1 );
                return _data[j+_j0+(i+_i0)*_dimJ];
        }

        _Tp const & operator()(size_t i, size_t j) const
        {
                assert(i+_i0 < _i1 && j+_j0 < _j1 );
                return _data[j+_j0+(i+_i0)*_dimJ];
        }

        size_t get_dimI() const
        {
                return _i1-_i0;
        }
        size_t get_dimJ() const
        {
                return _j1-_j0;
        }
        size_t get_size() const
        {
                return _size;
        }
        size_t getBytes() const
        {
                return _bytes;
        }

        void set_index_frame(size_t i0,size_t i1, size_t j0, size_t j1)
        {
                assert(i0 <i1 && j0 < j1 && i0 >= 0 && i1 <= _dimI
                       && j0 >=0 && j1 <= _dimJ);
                _i0 = i0;
                _i1 = i1;
                _j0 = j0;
                _j1 = j1;
        }

        void reset_index_frame()
        {
                _i0 = 0;
                _i1 = _dimI;
                _j0 = 0;
                _j1 = _dimJ;
        }

        _Tp* const get_data() const
        {
                return _data.get();
        }

        bool isSquare() const
        {
                return _dimI == _dimJ;
        }

private:
        size_t _dimI;
        size_t _i0,_i1;

        size_t _dimJ;
        size_t _j0,_j1;

        size_t _size;
        size_t _bytes;
        std::unique_ptr<_Tp []> _data;
        // "address of a matrix"
        _Tp* const operator~() const
        {
                return _data.get();
        }



};

#endif


