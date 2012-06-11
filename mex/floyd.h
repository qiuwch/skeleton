#ifndef __FLOYD_H__
#define __FLOYD_H__

#include "simpleMatrix.h"
#include <vector>

using namespace std;

bool floyd(matrix_t<double>& G, matrix_t<double>& minDist, matrix_t<int>& mid);
bool genPath(matrix_t<int>& mid, matrix_t<double>& dist, matrix_t<vector<int> >& outPath);

inline ostream& operator<<(ostream& os, const vector<int>& path)
{
    vector<int>::const_iterator iter;
    for (iter = path.begin(); iter < path.end(); iter++)
    {
        os << *iter << " ";
    }
    os << endl;
    return os;
}

#endif

