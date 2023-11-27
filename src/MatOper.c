#include "../include/MatOper.h"
#include "../include/MatEleTrans.h"
#include "../include/MatUtil.h"
#include "../include/MatConst.h"
#include <stdlib.h>
#include <math.h>

int matData(Mat source1, Mat source2, Mat target)
{
    int i = 0, j = 0;
    if (matSameDim(source1, source2) && matSameDim(source1, target))
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.data[i][j] = source1.data[i][j] + source2.data[i][j];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matSub(Mat sourceM, Mat sourceS, Mat target)
{
    int i = 0, j = 0;
    if (matSameDim(sourceM, sourceS) && matSameDim(sourceM, target))
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.data[i][j] = sourceM.data[i][j] - sourceS.data[i][j];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matScaMul(Mat source, Mat target, double multer)
{
    int i = 0, j = 0;
    if (matSameDim(source, target))
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.data[i][j] = source.data[i][j] * multer;
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matMulti(Mat sourceL, Mat sourceR, Mat target)
{
    int i = 0, j = 0, k = 0;
    double tempS = 0;
    if (sourceL.numCols == sourceR.numRows &&
        sourceL.numRows == target.numRows && sourceR.numCols == target.numCols)
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                for (k = 0, tempS = 0; k < sourceL.numCols; k++)
                {
                    tempS += sourceL.data[i][k] * sourceR.data[k][j];
                }
                target.data[i][j] = tempS;
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matTrans(Mat source, Mat target)
{
    int i = 0, j = 0;
    if (source.numRows == target.numCols && source.numCols == target.numRows)
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.data[i][j] = source.data[j][i];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matInver(Mat source, Mat target)
{
    int i = 0, j = 0;
    double det = 100;
    Mat matemp;
    if (source.numRows == source.numCols && matSameDim(source, target))
    {
        matInit(&matemp, source.numRows, 2 * source.numCols);
        matCpLocal(source.data, matemp.data,
                   0, source.numRows - 1, 0, source.numCols - 1,
                   0, matemp.numRows - 1, 0, source.numCols - 1);
        matSetELocal(matemp.data, 0, matemp.numRows - 1, matemp.numRows, matemp.numCols - 1);
        matEche(matemp, matemp, &det);
        if (fabs(det) < ZEROTHRES)
        {
            return SINGULAR;
        }
        matRedEche(matemp, matemp, true);
        matCpLocal(matemp.data, target.data,
                   0, matemp.numRows - 1, 0, target.numRows - 1,
                   matemp.numRows, matemp.numCols - 1, 0, target.numCols - 1);
        matFree(&matemp);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matAdjo(Mat source, Mat target)
{
    int i = 0, j = 0;
    double det = 0, cofactor = 0;
    if (source.numRows == source.numCols && matSameDim(source, target))
    {
        if (matInver(source, target) == SUCCESS)
        {
            matDeter(source, &det);
            matScaMul(target, target, det);
        }
        else
        {
            for (i = 0; i < target.numRows; i++)
            {
                for (j = 0; j < target.numRows; j++)
                {
                    matCofac(source, j, i, &cofactor);
                    target.data[i][j] = cofactor;
                }
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matEche(Mat source, Mat target, double *deterPtr)
{
    int i = 0, j = 0, tempI = 0, echelon = 0;
    bool nonZero = false;
    if (matSameDim(source, target))
    {
        (deterPtr != NULL) ? *deterPtr = 1 : 0;
        matCopy(source, target);
        while (i < target.numRows && i + echelon < target.numCols)
        {
            nonZero = true;
            if (fabs(target.data[i][i + echelon]) <= ZEROTHRES)
            {
                nonZero = false;
                for (tempI = i + 1; tempI < target.numRows && !nonZero; tempI++)
                {
                    if (fabs(target.data[tempI][i + echelon]) > ZEROTHRES)
                    {
                        matEleSwap(target, i, tempI, true);
                        nonZero = true;
                    }
                }
                if (!nonZero)
                {
                    (deterPtr != NULL) ? *deterPtr = 0 : 0;
                    echelon++;
                }
            }
            if (nonZero)
            {
                (deterPtr != NULL) ? *deterPtr *= target.data[i][i + echelon] : 0;
                matEleScaMul(target, i, 1 / target.data[i][i + echelon], true);
                for (j = i + 1; j < target.numRows; j++)
                {
                    matEleAdd(target, i, j, -target.data[j][i + echelon], true);
                }
                i++;
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matRedEche(Mat source, Mat target, bool isEche)
{
    int i = 0, j = 0, k = 0;
    if (matSameDim(source, target))
    {
        bool operated = false;
        if (isEche)
        {
            matCopy(source, target);
        }
        else
        {
            matEche(source, target, NULL);
        }
        for (i = target.numRows - 1; i >= 0; i--)
        {
            for (j = 0, operated = false; j < target.numCols && !operated; j++)
            {
                if (fabs(target.data[i][j]) > ZEROTHRES)
                {
                    if (fabs(target.data[i][j] - 1) > ZEROTHRES)
                    {
                        matEleScaMul(target, i, 1 / target.data[i][j], true);
                    }
                    for (k = i - 1; k >= 0; k--)
                    {
                        matEleAdd(target, i, k, -target.data[k][j], true);
                    }
                    operated = true;
                }
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matRank(Mat matrix, bool isEche, int *rankPtr)
{
    int i = 0, j = 0;
    bool hasNonZero = false;
    Mat matemp;
    if (rankPtr != NULL)
    {
        *rankPtr = matrix.numRows;
        matInit(&matemp, matrix.numRows, matrix.numCols);
        if (isEche)
        {
            matCopy(matrix, matemp);
        }
        else
        {
            matEche(matrix, matemp, NULL);
        }
        for (i = matemp.numRows - 1; i >= 0 && !hasNonZero; i--)
        {
            for (j = 0; j < matemp.numCols && !hasNonZero; j++)
            {
                if (fabs(matemp.data[i][j]) > ZEROTHRES)
                {
                    hasNonZero = true;
                }
            }
            if (!hasNonZero)
            {
                (*rankPtr)--;
            }
        }
        matFree(&matemp);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matDeter(Mat matrix, double *deterPtr)
{
    Mat matemp;
    if (matrix.numRows == matrix.numCols && deterPtr != NULL)
    {
        matInit(&matemp, matrix.numRows, matrix.numCols);
        matEche(matrix, matemp, deterPtr);
        matFree(&matemp);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matMinor(Mat matrix, int indexRow, int indexCol, double *minorPtr)
{
    Mat matemp;
    if (matrix.numRows == matrix.numCols && minorPtr != NULL)
    {
        matInit(&matemp, matrix.numRows - 1, matrix.numRows - 1);
        matCpLocal(matrix.data, matemp.data,
                   0, indexRow - 1, 0, indexRow - 1, 0, indexCol - 1, 0, indexCol - 1);
        matCpLocal(matrix.data, matemp.data,
                   indexRow + 1, matrix.numRows - 1, indexRow, matrix.numRows - 2,
                   0, indexCol - 1, 0, indexCol - 1);
        matCpLocal(matrix.data, matemp.data,
                   0, indexRow - 1, 0, indexRow - 1,
                   indexCol + 1, matrix.numRows - 1, indexCol, matrix.numRows - 2);
        matCpLocal(matrix.data, matemp.data,
                   indexRow + 1, matrix.numRows - 1, indexRow, matrix.numRows - 2,
                   indexCol + 1, matrix.numRows - 1, indexCol, matrix.numRows - 2);
        matDeter(matemp, minorPtr);
        matFree(&matemp);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int matCofac(Mat matrix, int indexRow, int indexCol, double *cofacPtr)
{
    if (matrix.numRows == matrix.numCols && cofacPtr != NULL)
    {
        matMinor(matrix, indexRow, indexCol, cofacPtr);
        if ((indexRow + indexCol) % 2 != 0)
        {
            *cofacPtr = -*cofacPtr;
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}