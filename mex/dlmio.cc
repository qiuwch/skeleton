#include <vector>
#include <sstream>
#include "stdlib.h"
#include "dlmio.h"
// #include <boost/lexical_cast.hpp>

using namespace std;

vector<vector<char> > load(string filename, char sepchar);
vector<vector<double> > matrixchar2double(vector<vector<char> > charmat, char sepchar);
matrix_t<double> vecmat2matrix(vector<vector<double> > vecmat);


matrix_t<double> dlmread(string filename, char sepchar)
{
    vector<vector<char> > mat1 = load(filename, sepchar);
    vector<vector<double> > mat2 = matrixchar2double(mat1, sepchar);
    matrix_t<double> mat3 = vecmat2matrix(mat2);
    if (DEBUG) cout << "Descturct 2" << endl;
    return mat3;
}

bool isSepChar(char c, char sepchar)
{
    if (c == sepchar || c == ' ' || c == '\n')
        return true;
    return false;
}

bool str2double(string str, double& v)
{
    // v = 0;
    // v = boost::lexical_cast<double>(str);
    v = atof(str.c_str());
    if (v == 0 && str != "0")
    {
        fprintf(stderr, "String %s can not be parsed\n", str.c_str());
        return false;
    }
    return true;
}

matrix_t<double> vecmat2matrix(vector<vector<double> > vecmat)
{
    int nrow = 0, ncol = 0;
    nrow = vecmat.size();
    if (nrow > 0)
        ncol = vecmat[0].size();

    matrix_t<double> mat(nrow, ncol);

    vector<vector<double> >::iterator iter1;
    vector<double>::iterator iter2;

    int row = 0, col = 0;
    for (iter1 = vecmat.begin(); iter1 < vecmat.end(); iter1++)
    {
        col = 0;
        for (iter2 = (*iter1).begin(); iter2 < (*iter1).end(); iter2++)
        {
            mat[row][col++] = *iter2;
        }
        if (col != ncol)
        {
            fprintf(stderr, "Column number of row %d:%d can not match first column %d\n", row, col, ncol);
            return matrix_t<double>(0,0);
        }
        row++;
    }

    if (DEBUG) cout << "Destruct 1" << endl;
    return mat;
}

vector<vector<double> > matrixchar2double(vector<vector<char> > charmat, char sepchar)
{
    vector<vector<double> > doublemat;
    vector<vector<char> >::iterator iter1;
    for (iter1 = charmat.begin(); iter1 < charmat.end(); iter1++)
    {
        vector<double> doubleline;
        
        vector<char>::iterator iter2, iter1end = (*iter1).end();
        iter2 = (*iter1).begin();

        while (iter2 != iter1end)
        {
            double v = 0;
            string str = "";
            char c = *iter2;

            while (iter2 != iter1end && !isSepChar(c, sepchar))
            {
                str = str + c;
                iter2++;
                c = *iter2;
            }
            
            if (str2double(str, v))
            {
                doubleline.push_back(v);
            }
            else
            {
                fprintf(stderr, "Some string in char matrix can not be parsed.\n");
                return vector<vector<double> >();
            }

            while (iter2 != iter1end && isSepChar(*iter2, sepchar))
            {
                iter2++;
                c = *iter2;
            }
        }
        doublemat.push_back(doubleline);
    }
    if (DEBUG) cout << "Size of double vector matrix:" << doublemat.size() << endl;
    return doublemat;
}

vector<vector<char> > load(string filename, char sepchar)
{
    // string filename = "testmat.txt";
    ifstream f;
    f.open(filename.c_str(), ios::in | ios::out);
    // f.unsetf(ios_base::skipws);
    f >> noskipws;

    if (!f.is_open())
    {
        fprintf(stderr, "Can not open file.\n");
        return vector<vector<char> >();
    }

    vector<vector<char> > data;
    string line;

    while(!std::getline(f, line, '\n').eof())
    {
        istringstream reader(line);
        reader.unsetf(ios_base::skipws);
        // reader >> noskipws;

        vector<char> lineData;
        
        // string::const_iterator i = line.begin();

        while (!reader.eof())
        {
            char val;
            reader >> val;
            
            if (reader.fail())
                break;

            lineData.push_back(val);
            // cout << val;
        }

        data.push_back(lineData);
    }
    if (DEBUG) cout << "Size of char vector matrix:" << data.size() << endl;
    return data;
}














