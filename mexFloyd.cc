#include "mex.h"
#include "floyd.h"
#include "simpleMatrix.h"
#include "stdint.h"

void log(FILE *fid, const char *message)
{
    mexPrintf(message);
    fprintf(fid, message);
    mexEvalString("drawnow;");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, 
  const mxArray *prhs[])
{
    FILE *fid;
    fid = fopen("log.txt", "w+");

    if (nrhs != 1)
    {
        mexPrintf("Wrong number of input parameters, 1 need, %d specified\n", nrhs);
        return;
    }

    if (nlhs != 2)
    {
        mexPrintf("Wrong number of output parameters, 2 needed, %d specified\n", nlhs);
        return;
    }
    
    const mxArray *mxG = prhs[0];
    int m = 0, n = 0;
    m = mxGetM(mxG);
    n = mxGetN(mxG);

    if (m != n)
    {
        mexPrintf("Wrong input matrix G, m:%d and n:%d can not match\n", m, n);
        return;
    }

    mxArray *mxdist = mxCreateDoubleMatrix(m, n, mxREAL);
    // mxArray *mxCreateDoubleMatrix(mwSize m, mwSize n, mxComplexity ComplexFlag);
    mxArray *mxpath = mxCreateCellMatrix(m, n);
    // mxArray *mxCreateCellMatrix(mwSize m, mwSize n);

    plhs[0] = mxdist;
    plhs[1] = mxpath;

    log(fid, "Read data from matlab.\n");
    double *pointer = mxGetPr(mxG);    
    matrix_t<double> G(n, n, pointer);

    matrix_t<int> mid(0, 0);
    matrix_t<double> dist(0, 0);
    matrix_t<vector<int> > path(0, 0);

    log(fid, "Floyd algorithm begin.\n");
    floyd(G, dist, mid);
    log(fid, "Generate path from result.\n");
    genPath(mid, path);

    log(fid, "Calulation done, convert to matlab data structure.\n");

    int i = 0, j = 0, k = 0;
    
    // void mxSetPr(mxArray *pm, double *pr);
    // mxSetPr(mxdist, dist.p);  // This is wrong.
    double *mxdistPointer = mxGetPr(mxdist);
    for (i = 0; i < dist.len; i++)
        mxdistPointer[i] = dist.p[i];

    log(fid, "Convert distance matrix done.\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            // Node index range is from 0 to 65535
            vector<int> vecpath = path[i][j];
            size_t l = vecpath.size();
            mxArray *pathArray = mxCreateNumericMatrix(1, l, mxUINT16_CLASS, mxREAL);
            uint16_t *pathPointer = (uint16_t*)mxGetData(pathArray);

            for (k = 0; k < vecpath.size(); k++)
            {
                pathPointer[k] = vecpath[k]; // convert to matlab index, start from 1
            }
            // void mxSetData(mxArray *pm, void *pr); // 32bits and 64bits support should be considered
            // mxSetData(pathPointer, &vecpath[0]);  // this assignment is wrong. 

            // void mxSetCell(mxArray *pm, mwIndex index, mxArray *value);
            // mxArray *mxCreateNumericMatrix(mwSize m, mwSize n, mxClassID classid, mxComplexity ComplexFlag);
            // mwIndex mxCalcSingleSubscript(const mxArray *pm, mwSize nsubs, mwIndex *subs);

            // int subs[2] = {i, j};
            // mwIndex idx = mxCalcSingleSubscript(pathArray, 2, subs);
            mwIndex idx = j * n + i; // column first
            mxSetCell(mxpath,  idx, pathArray);

        }
    }
    log(fid, "Convert path matrix done.\n");
    fclose(fid);
}
