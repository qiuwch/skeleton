/*!
  @file simpleMatrix.h
  @brief Matrix operation definition
  all functions in this header file is defined as "inline" for performance consideration
*/

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "math.h"
#include "assert.h"
#include "string.h" // include it to use memset
#include <iostream>
#include "stdio.h"

// Wrap code for windows compatibility
#ifdef _WIN32

inline int round(float v)
{
	return floor(v+1);
}
#include <limits>
#define INFINITY numeric_limits<float>::infinity()
#define isfinite _finite
#define _USE_MATH_DEFINES
#endif

/*
  0 <= xl, xr <= width-1
  0 <= yt, yb <= height-1
*/

class region_t
{
public:
	region_t() {}
	region_t(int xl, int xr, int yt, int yb)
	{
		this->xl = xl;
		this->xr = xr;
		this->yt = yt;
		this->yb = yb;
	}
	int width() const { return xr-xl; }
	int height() const { return yb-yt; }
	int xl, xr, yt, yb;
};

template<class T>
class matrix_t
{
public:
	matrix_t(int rows, int cols, T *p = 0)
	{
		this->width_ = cols;
		this->height_ = rows;
		this->len_ = cols * rows;
		this->p_ = new T[len_];
		memset(this->p_, 0, sizeof(T) * len_); // Important!
		if (p != 0)
		{
			for (int i = 0; i<len_; i++) this->p_[i] = p[i];
		}
	}

	// copy constructor
    matrix_t(const matrix_t<T>& source)
    {
        this->width_ = source.width_;
        this->height_ = source.height_;
        this->len_ = source.len_;
        this->p_ = new T[source.len_];
        memset(this->p_, 0, sizeof(T) * len_);
        // use memcpy
        for (int i = 0; i < this->len_; i++)
            this->p_[i] = source.p_[i];
    }

	~matrix_t()
	{
		std::cout << "destruct." << std::endl;
        // this->p_ = NULL; 
// This is very important, I don't know why
// Can not pass test case without this
        // std::cout << "Destruct." << std::endl;
		delete []p_;
		this->p_ = NULL;
	}
    
    inline matrix_t<T>& operator=(const matrix_t<T> source)
    {
        this->width_ = source.width_;
        this->height_ = source.height_;
        this->len_ = source.len_;
        delete[] this->p_;
        this->p_ = new T[len_];
        for (int i = 0; i < this->len_; i++)
            this->p_[i] = source.p_[i];
        return *this;
    }

	inline T* operator[](int index) const
	{
        if (index < 0 || index >= this->height_)
        {
            fprintf(stderr, "Row index out of bound, index %d, rows %d\n", index, this->height_);
            return NULL;
        }
		return p_ + index*width_;
	}
	
	inline void min(T *val, int *x, int *y)
	{
		T min = INFINITY;
		T* pmin;
		T* pp = this->p_;
		while(pp < this->p_+len_)
		{
			if (min > *pp) 
			{
				min = *pp;
				pmin = pp;
			}
			pp++;
		}
		*val = min;
		*y = (pmin - p_) / width_;
		*x = (pmin - p_) % width_;
	}

	inline void max(T *val, int *x, int *y)
	{
		T max = -INFINITY;
		T* pmax;
		T* pp = this->p_;
		while(pp < this->p_+len_)
		{
			if (max < *pp) 
			{
				max = *pp;
				pmax = pp;
			}
			pp++;
		}
		*val = *pmax;
		*y = (pmax - p_) / width_;
		*x = (pmax - p_) % width_;
	}
	T *p_;
	int width_;
	int height_;
	int len_;

};


template<class T>
inline void divide_s(matrix_t<T> *m, const float f, const region_t *r=0)
{
	if (r == 0)
	{
		T *p = m->p_;
		int i = 0;
		while (i < m->len_)
		{
			p[i++] /= f;
		}
	}
	else
	{
		for (int i = r->yt; i <= r->yb; i++)
		{
			for (int j = r->xl; j <= r->xr; j++)
			{
				(*m)[i][j] /= f;
			}
		}
	}
}

template<class T>
inline void multiply_s(matrix_t<T> *m, const float f, const region_t *r=0)
{
	if (r == 0)
	{
		T *p = m->p_;
		int i = 0;
		while (i < m->len_)
		{
			p[i++] *= f;
		}
	}
	else
	{
		for (int i = r->yt; i <= r->yb; i++)
		{
			for (int j = r->xl; j <= r->xr; j++)
			{
				(*m)[i][j] *= f;
			}
		}
	}
}

template<class T>
inline void add_s(matrix_t<T> *m, const T f, const region_t *r=0)
{
	if (r == 0)
	{
		T *p = m->p_;
		int i = 0;
		while (i < m->len_)
		{
			p[i++] += f;
		}
	}
	else
	{
		for (int i = r->yt; i <= r->yb; i++)
		{
			for (int j = r->xl; j <= r->xr; j++)
			{
				(*m)[i][j] += f;
			}
		}
	}
}

template<class T1, class T2>
inline void add_m(matrix_t<T1> *m1, const matrix_t<T2> *m2, const region_t *r1=0, const region_t *r2=0)
{
	if (r1 == 0 && r2 == 0)
	{
		T1 *p1 = m1->p_;
		T2 *p2 = m2->p_;

		while (p1 < m1->p_ + m1->len_)
		{
			*p1++ += *p2++;
		}
	}
	else
	{
		assert(r1->width() == r2->width());
		assert(r1->height() == r2->height());
		int width = r1->width();
		int height = r1->height();
		
		for (int i = 0; i<height; i++)
		{
			for (int j = 0; j<width; j++)
			{
				(*m1)[r1->yt+i][r1->xl+j] += (*m2)[r2->yt+i][r2->xl+j];
			}
		}
	}
}

template<class T1, class T2>
inline void matrix_copy(matrix_t<T1> *m1, const matrix_t<T2> *m2, const region_t *r1 = 0, const region_t *r2 = 0)
{
	if (r1 == 0 && r2 == 0)
	{
		assert(m1->width_ == m2->width_);
		assert(m1->height_ == m2->height_);
		
		T1 *p1 = m1->p_;
		T2 *p2 = m2->p_;
		while (p1 < m1->p_ + m1->len_)
		{
			*p1++ = *p2++;
		}
	}
	else
	{
		assert(false);
	}
}

template<class T>
inline void matrix_set(matrix_t<T> *m, T v, const region_t *r=0)
{
	if (r == 0)
	{
		T *p = m->p_;
		while (p < m->p_ + m->len_)
		{
			*p++ = v;
		}
	}
	else
	{
		int width = r->width();
		int height = r->height();
		
		for (int i = 0; i<height; i++)
		{
			for (int j = 0; j<width; j++)
			{
				(*m)[r->yt+i][r->xl+j] = v;
			}
		}
		
	}
}

template<class T>
inline bool operator ==(const matrix_t<T>& a, const matrix_t<T>& b)
{
	if (a.width_ != b.width_ || a.height_ != b.height_)
		return false;
	for (int row = 0; row < a.height_; row++)
		for (int col = 0; col < a.width_; col++)
		{
			if (abs(a[row][col] - b[row][col]) > 0.0001) return false;
		}
	return true;
}


#endif
