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
		this->width = cols;
		this->height = rows;
		this->len = cols * rows;
		this->p = new T[len];
		memset(this->p, 0, sizeof(T) * len); // Important!
		if (p != 0)
		{
			for (int i = 0; i<len; i++) this->p[i] = p[i];
		}
	}

    matrix_t(const matrix_t& from)
    {
        this->width = from.width;
        this->height = from.height;
        this->len = from.len;
        this->p = new T[from.len];
        memset(this->p, 0, sizeof(T) * len);
        for (int i = 0; i < this->len; i++)
            this->p[i] = from.p[i];
    }

	~matrix_t()
	{
        this->p = NULL; 
// This is very important, I don't know why
// Can not pass test case without this
        // std::cout << "Destruct." << std::endl;
		delete []p;
	}
    
	inline T* operator[](int index) const
	{
        if (index < 0 || index >= this->height)
        {
            fprintf(stderr, "Row index out of bound, index %d, rows %d\n", index, this->height);
            return NULL;
        }
		return p + index*width;
	}
	
	inline void min(T *val, int *x, int *y)
	{
		T min = INFINITY;
		T* pmin;
		T* pp = this->p;
		while(pp < this->p+len)
		{
			if (min > *pp) 
			{
				min = *pp;
				pmin = pp;
			}
			pp++;
		}
		*val = min;
		*y = (pmin - p) / width;
		*x = (pmin - p) % width;
	}

	inline void max(T *val, int *x, int *y)
	{
		T max = -INFINITY;
		T* pmax;
		T* pp = this->p;
		while(pp < this->p+len)
		{
			if (max < *pp) 
			{
				max = *pp;
				pmax = pp;
			}
			pp++;
		}
		*val = *pmax;
		*y = (pmax - p) / width;
		*x = (pmax - p) % width;
	}
	T *p;
	int width;
	int height;
	int len;

};


template<class T>
inline void divide_s(matrix_t<T> *m, const float f, const region_t *r=0)
{
	if (r == 0)
	{
		T *p = m->p;
		int i = 0;
		while (i < m->len)
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
		T *p = m->p;
		int i = 0;
		while (i < m->len)
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
		T *p = m->p;
		int i = 0;
		while (i < m->len)
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
		T1 *p1 = m1->p;
		T2 *p2 = m2->p;

		while (p1 < m1->p + m1->len)
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
		assert(m1->width == m2->width);
		assert(m1->height == m2->height);
		
		T1 *p1 = m1->p;
		T2 *p2 = m2->p;
		while (p1 < m1->p + m1->len)
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
		T *p = m->p;
		while (p < m->p + m->len)
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
	if (a.width != b.width || a.height != b.height)
		return false;
	for (int row = 0; row < a.height; row++)
		for (int col = 0; col < a.width; col++)
		{
			if (abs(a[row][col] - b[row][col]) > 0.0001) return false;
		}
	return true;
}


#endif
