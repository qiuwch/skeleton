#include "matrix.h"
#include "matrixio.h"
#include "dlmio.h"
#include <vector>

using namespace std;

bool DEBUG = false;

struct path_t
{
    path_t *leftPath;
    path_t *rightPath;
    int mid; // node id
    int start;
    int end;
};

void addSegment(const path_t* segment, vector<int>& vpath)
{
    if (segment->leftPath->mid != 0) 
    {
        addSegment(segment->leftPath, vpath);
    }
    if (segment->mid != 0) vpath.push_back(segment->mid);
    if (segment->rightPath->mid != 0)
    {
        addSegment(segment->rightPath, vpath);
    }
}

vector<int> translate(const path_t &path)
{
    vector<int> vpath;
    vpath.push_back(path.start);
    addSegment(&path, vpath);
    vpath.push_back(path.end);
    return vpath;
}

ostream& operator << (ostream &os, const path_t& p)
{
    vector<int> v = translate(p);

    vector<int>::iterator iter;
    os << "Path: ";
    for (iter = v.begin(); iter < v.end(); iter++)
    {
        os << *iter << " ";
    }
    return os;
}


bool floyd(matrix_t<double>& G, matrix_t<double>& minDist, matrix_t<int>& mid);
bool genPath(matrix_t<int>& mid, matrix_t<path_t>& outPath);

int main()
{
    matrix_t<double> G = dlmread("test/G.txt", ',');
    matrix_t<double> minDist(0,0);
    matrix_t<int> mid(0,0);
    floyd(G, minDist, mid);
    
    dlmwrite("test/minDist.txt", minDist, ',');
    dlmwrite("test/mid.txt", mid, ',');

    matrix_t<path_t> path(0,0);
    genPath(mid, path);

    for (int i = 0; i<500; i++)
    {
        cout << path[0][i] << endl;
    }
    // cout << path[1][10] << endl;

    return 0;
}

path_t* minPath(matrix_t<int>& mid, matrix_t<path_t>& path, matrix_t<bool>& flag, int i, int j)
{
    if (flag[i][j])
    {
        return &path[i][j];
    }

    path_t p;
    int midNode = mid[i][j];
    if (midNode == 0)
    {
        p.leftPath = &path[i][i];
        p.rightPath = &path[j][j];
        p.mid = 0;
        p.start = i;
        p.end = j;
    }
    else
    {
        p.leftPath = minPath(mid, path, flag, i, midNode);
        p.rightPath = minPath(mid, path, flag, midNode, j);
        p.mid = midNode;
        p.start = p.leftPath->start;
        p.end = p.rightPath->end;
    }
    path[i][j] = p;
    flag[i][j] = true;
    return &path[i][j];
}

bool genPath(matrix_t<int>& mid, matrix_t<path_t>& outPath)
{
    int i = 0, j = 0, n = 0;
    n = mid.height;

    matrix_t<bool> flag(n, n);
    matrix_t<path_t> path(n, n);

    for (i = 0; i < n; i++)
    {
        path_t p;
        p.start = i;
        p.end = i;
        p.mid = 0;
        p.leftPath = &path[i][i];
        p.rightPath = &path[i][i];
        path[i][i] = p;
        flag[i][i] = true;
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            minPath(mid, path, flag, i, j);
        }
    outPath = path;
    return true;
}

bool floyd(matrix_t<double>& G, matrix_t<double>& outMinDist, matrix_t<int>& outMid)
{
    cout << "Begin" << endl;
    int nrow = 0, ncol = 0;
    nrow = G.height;
    ncol = G.width;

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
                    mid[i][j] = k;
                }
            }
    outMinDist = minDist;
    outMid = mid;

    return true;
}
