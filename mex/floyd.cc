#include "floyd.h"

using namespace std;

bool DEBUG = false;

void addSegment(int i, int j, vector<int>& vecpath, const matrix_t<int>& mid)
{
    int k = mid[i][j] - 1; 
// vertex id stored in mid start from 1
    if (k != -1)
    {
        addSegment(i, k, vecpath, mid);
        vecpath.push_back(k+1);
        addSegment(k, j, vecpath, mid);
    }
    else
    {
        return;
    }
}

bool genPath(matrix_t<int>& mid, matrix_t<double>& dist, matrix_t<vector<int> >& outPath)
{
    int i = 0, j = 0, n = 0;
    n = mid.height_;

    matrix_t<vector<int> > path(n, n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            vector<int> vecpath;
            vecpath.push_back(i+1);
            addSegment(i, j, vecpath, mid);
            vecpath.push_back(j+1);

// BUG fix: if the distance between start node and end node is inf
// there should be no path
			if (vecpath.size() == 2 && dist[i][j] == INFINITY)
				continue;
            path[i][j] = vecpath;
        }
    }

    outPath = path;
    return true;
}

bool floyd(matrix_t<double>& G, matrix_t<double>& outMinDist, matrix_t<int>& outMid)
{
    int nrow = 0, ncol = 0;
    nrow = G.height_;
    ncol = G.width_;

    if (nrow != ncol)
    {
        fprintf(stderr, "Distance matrix should be square.\n");
        return false;
    }

    int i = 0, j = 0, k = 0, n = nrow;
    double midDist = 0;
    matrix_t<double> minDist = G;
    matrix_t<int> mid(nrow, ncol);

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) 
// Can be optimize to only calculate half of the matrix
            {
                midDist = minDist[i][k] + minDist[k][j];
                if (midDist < minDist[i][j])
                {
                    // cout << "Update" << endl;
                    minDist[i][j] = midDist;
                    mid[i][j] = k + 1;
                }
            }
    outMinDist = minDist;
    outMid = mid;

    return true;
}
