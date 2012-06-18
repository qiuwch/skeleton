#ifndef __MATRIX_IO_H__
#define __MATRIX_IO_H__

#include "simpleMatrix.h"

template<class T>
inline std::ostream& operator << (std::ostream &os, const matrix_t<T>& a)
{
    std::cout << a.height_ << " " << a.width_ << std::endl;
	for (int row = 0; row < a.height_; row++)
	{
		for (int col = 0; col < a.width_; col++)
		{
            // std::cout << row << " " << col << std::endl;
			os << a[row][col] << " ";
		}
        os << std::endl;
	}
	return os;
}

template<class T>
inline std::istream& operator >> (std::istream &is, const matrix_t<T>& a)
{
	for (int row = 0; row < a.height; row++)
	{
		for (int col = 0; col < a.width; col++)
		{
			is >> a[row][col];
		}
	}
	return is;
}
#endif
