#include "../include/MatUtil.h"
#include "../include/MatConst.h"
#include <stdlib.h>

void matInit(Mat *matPtr, int numRows, int numCols)
{
    int i = 0, j = 0;
    (*matPtr).data = (double **)malloc(sizeof(double *) * numRows);
    (*matPtr).numRows = numRows;
    (*matPtr).numCols = numCols;
    for (i = 0; i < numRows; i++)
    {
        (*matPtr).data[i] = (double *)malloc(sizeof(double) * numCols);
        for (j = 0; j < numCols; j++)
        {
            (*matPtr).data[i][j] = 0;
        }
    }
}

void matFree(Mat *matPtr)
{
    int i = 0;
    for (i = 0; i < (*matPtr).numRows; i++)
    {
        free((*matPtr).data[i]);
        (*matPtr).data[i] = NULL;
    }
    free((*matPtr).data);
    (*matPtr).data = NULL;
    (*matPtr).numRows = 0;
    (*matPtr).numCols = 0;
}

int matSetE(Mat matrix)
{
    if (matrix.numRows = matrix.numCols)
    {
        matSetELocal(matrix.data, 0, matrix.numRows - 1, 0, matrix.numRows - 1);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

void matSetELocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            matData[i][j] = (i - rowStart) == (j - colStart) ? 1 : 0;
        }
    }
}

int matSetArr(Mat matrix, double *arr, int sizeofArr)
{
    int i = 0, j = 0;
    if (matrix.numRows * matrix.numCols == sizeofArr / sizeof(double))
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            for (j = 0; j < matrix.numCols; j++)
            {
                matrix.data[i][j] = arr[i * matrix.numCols + j];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matCopy(Mat source, Mat target)
{
    if (source.data == target.data)
    {
        return SUCCESS;
    }
    else if (matSameDim(source, target))
    {
        matCpLocal(source.data, target.data,
                   0, source.numRows - 1, 0, source.numRows - 1,
                   0, source.numCols - 1, 0, source.numCols - 1);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matCpLocal(double **srcData, double **tgtData,
               int rowSrcSt, int rowSrcEd, int rowTgtSt, int rowTgtEd,
               int colSrcSt, int colSrcEd, int colTarSt, int colTarEd)
{
    int i = 0, j = 0;
    if (rowSrcEd - rowSrcSt == rowTgtEd - rowTgtSt && colSrcEd - colSrcSt == colTarEd - colTarSt)
    {
        for (i = 0; i <= rowSrcEd - rowSrcSt; i++)
        {
            for (j = 0; j <= colSrcEd - colSrcSt; j++)
            {
                tgtData[i + rowTgtSt][j + colTarSt] = srcData[i + rowSrcSt][j + colSrcSt];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

bool matSameDim(Mat matrix1, Mat matrix2)
{
    if (matrix1.numRows == matrix2.numRows && matrix1.numCols == matrix2.numCols)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool matEqual(Mat matrix1, Mat matrix2)
{
    if (matrix1.data == matrix2.data)
    {
        return true;
    }
    else if (matSameDim(matrix1, matrix2))
    {
        return matEqLocal(matrix1.data, matrix2.data,
                          0, matrix1.numRows - 1, 0, matrix1.numRows - 1,
                          0, matrix1.numCols - 1, 0, matrix1.numCols - 1);
    }
    else
    {
        return false;
    }
}

bool matEqLocal(double **matData1, double **matData2,
                int rowSt1, int rowEd1, int rowSt2, int rowEd2,
                int colSt1, int colEd1, int colSt2, int colEd2)
{
    int i = 0, j = 0;
    for (i = 0; i <= rowEd1 - rowSt1; i++)
    {
        for (j = 0; j <= colEd1 - colSt1; j++)
        {
            if ((matData1[i + rowSt1][j + colSt1] - matData2[i + rowSt2][j + colSt2]) > ZEROTHRES)
            {
                return false;
            }
        }
    }
    return true;
}