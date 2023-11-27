#include "../include/MatEleTrans.h"
#include <stdlib.h>

void matEleSwap(Mat matrix, int index1, int index2, bool isRow)
{
    int i = 0;
    double *tempArr = NULL;
    if (isRow)
    {
        tempArr = (double *)malloc(sizeof(double) * matrix.numCols);
        for (i = 0; i < matrix.numCols; i++)
        {
            tempArr[i] = matrix.data[index1][i];
            matrix.data[index1][i] = matrix.data[index2][i];
            matrix.data[index2][i] = tempArr[i];
        }
    }
    else
    {
        tempArr = (double *)malloc(sizeof(double) * matrix.numRows);
        for (i = 0; i < matrix.numRows; i++)
        {
            tempArr[i] = matrix.data[i][index1];
            matrix.data[i][index1] = matrix.data[i][index2];
            matrix.data[i][index2] = tempArr[i];
        }
    }
    free(tempArr);
    tempArr = NULL;
}

void matEleScaMul(Mat matrix, int index, double multer, bool isRow)
{
    int i = 0;
    if (isRow)
    {
        for (i = 0; i < matrix.numCols; i++)
        {
            matrix.data[index][i] *= multer;
        }
    }
    else
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            matrix.data[i][index] *= multer;
        }
    }
}

void matEleAdd(Mat matrix, int indexS, int indexT, double multer, bool isRow)
{
    int i = 0;
    if (isRow)
    {
        for (i = 0; i < matrix.numCols; i++)
        {
            matrix.data[indexT][i] += matrix.data[indexS][i] * multer;
        }
    }
    else
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            matrix.data[i][indexT] += matrix.data[i][indexS] * multer;
        }
    }
}