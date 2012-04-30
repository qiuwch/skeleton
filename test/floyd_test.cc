#include "../floyd.h"
#include "../dlmio.h"

int main()
{
    matrix_t<double> G = dlmread("G.txt", ',');
    matrix_t<double> minDist(0,0);
    matrix_t<int> mid(0,0);
    floyd(G, minDist, mid);
    
    dlmwrite("minDist.txt", minDist, ',');
    dlmwrite("mid.txt", mid, ',');

    matrix_t<vector<int> > path(0,0);
    genPath(mid, path);

    for (int i = 0; i<500; i++)
    {
        cout << path[0][i];
    }
    return 0;
}
