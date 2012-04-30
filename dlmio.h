#ifndef __DLEMIO_H__
#define __DLEMIO_H__

#include <iostream>
#include <fstream>
#include "simpleMatrix.h"
#include "matrixio.h"

using namespace std;

extern bool DEBUG;

/* dlmread, dlmwrite support, inspired by octave code */
matrix_t<double> dlmread(string filename, char sepchar);

template<class T>
inline bool dlmwrite(string filename, matrix_t<T>& mat, char sepchar)
{
    ofstream f;
    f.open(filename.c_str());
    
    if (!f.is_open())
    {
        fprintf(stderr, "Can not open file %s for dlmwrite\n", filename.c_str());
        return false;
    }
    
    for (int row = 0; row < mat.height; row++)
    {
        for (int col = 0; col < mat.width; col++)
        {
            f << mat[row][col];
            if (col != mat.width - 1) f << sepchar;
        }
        f << endl;
    }
    return true;
}

#endif
