#define __DEBUG__
#include "../dlmio.h"
#include "../matrixio.h"

bool DEBUG = false;
static int test();

int main()
{
    return test();
}

static int test()
{
    matrix_t<double> mat1(0,0);
    cout << "Read test 1" << endl;
    string filename1 = "testmat.txt";
    mat1 = dlmread(filename1, ' ');
    cout << mat1;

    cout << "Read/Write test 1" << endl;
    filename1 = "testmat_comma.txt";
    dlmwrite(filename1, mat1, ',');
    mat1 = dlmread(filename1, ',');
    cout << mat1;

    cout << "Read/Write test 2" << endl;
    filename1 = "testmat_space.txt";
    dlmwrite(filename1, mat1, ' ');
    mat1 = dlmread(filename1, ' ');
    cout << mat1;
    
    cout << "Read test 2" << endl;
    string filename2 = "G.txt";
    matrix_t<double> mat2 = dlmread(filename2, ',');

    /*
    vector<vector<char> >::iterator iter1;
    vector<char>::iterator iter2;
    for (iter1 = mat1.begin(); iter1 < mat1.end(); iter1++)
    {
        for (iter2 = (*iter1).begin(); iter2 < (*iter1).end(); iter2++)
        {
            cout << *iter2 << ' ';
        }
        cout << endl;
    }
    */

    /*
    vector<vector<double> >::iterator iter1;
    vector<double>::iterator iter2;

    for (iter1 = mat2.begin(); iter1 < mat2.end(); iter1++)
    {
        for (iter2 = (*iter1).begin(); iter2 < (*iter1).end(); iter2++)
        {
            cout << *iter2 << ' ';
        }
        cout << endl;
    }
    */
    return 0;
}

