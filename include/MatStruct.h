#ifndef _MATSTRUCT_H_
#define _MATSTRUCT_H_

struct mat
{
    double **address;
    int numRows;
    int numCols;
};
typedef struct mat Mat;

#endif