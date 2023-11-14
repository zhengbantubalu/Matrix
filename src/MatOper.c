#include "..\include\MatOper.h"
#include "..\include\MatEleTrans.h"
#include "..\include\MatUtil.h"
#include "..\include\MatConst.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief   矩阵运算 – 矩阵加法
 * @param   source1     源矩阵1
 * @param   source2     源矩阵2
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source1与矩阵source2的和赋值给矩阵target，三矩阵须同型
 */
int matAdd(Mat source1, Mat source2, Mat target)
{
    int i = 0, j = 0;
    if (matSameDim(source1, source2) && matSameDim(source1, target))
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.address[i][j] = source1.address[i][j] + source2.address[i][j];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵运算 – 矩阵减法
 * @param   sourceM     被减矩阵
 * @param   sourceS     减矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵sourceM减矩阵sourceS的差赋值给矩阵target，三矩阵须同型
 */
int matSub(Mat sourceM, Mat sourceS, Mat target)
{
    int i = 0, j = 0;
    if (matSameDim(sourceM, sourceS) && matSameDim(sourceM, target))
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.address[i][j] = sourceM.address[i][j] - sourceS.address[i][j];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵运算 – 矩阵数乘
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @param   multer  数乘倍数
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source数乘multer的积赋值给矩阵target，两矩阵须同型
 */
int matScaMul(Mat source, Mat target, double multer)
{
    int i = 0, j = 0;
    if (matSameDim(source, target))
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.address[i][j] = source.address[i][j] * multer;
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵运算 – 矩阵乘法
 * @param   sourceL     左矩阵
 * @param   sourceR     右矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵sourceL与矩阵sourceR的积赋值给矩阵target，sourceL的列数须等于sourceR的行数，
 *          sourceL的行数须等于target的行数，sourceR的列数须等于target的列数
 */
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
                    tempS += sourceL.address[i][k] * sourceR.address[k][j];
                }
                target.address[i][j] = tempS;
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵运算 – 求转置矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的转置矩阵赋值给矩阵target，source的行数须等于target的列数，source的列数须等于target的行数
 */
int matTrans(Mat source, Mat target)
{
    int i = 0, j = 0;
    if (source.numRows == target.numCols && source.numCols == target.numRows)
    {
        for (i = 0; i < target.numRows; i++)
        {
            for (j = 0; j < target.numCols; j++)
            {
                target.address[i][j] = source.address[j][i];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵运算 – 求逆矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  SINGULAR – 矩阵不可逆
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的逆矩阵赋值给矩阵target，两矩阵须为同型方阵
 */
int matInver(Mat source, Mat target)
{
    int i = 0, j = 0;
    double det = 100;
    Mat matemp;
    if (source.numRows == source.numCols && matSameDim(source, target))
    {
        matInit(&matemp, source.numRows, 2 * source.numCols);
        matCpLocal(source.address, matemp.address,
                   0, source.numRows - 1, 0, source.numCols - 1,
                   0, matemp.numRows - 1, 0, source.numCols - 1);
        matSetELocal(matemp.address, 0, matemp.numRows - 1, matemp.numRows, matemp.numCols - 1);
        matEche(matemp, matemp, &det);
        if (fabs(det) < ZEROTHRES)
        {
            return SINGULAR;
        }
        matRedEche(matemp, matemp, true);
        matCpLocal(matemp.address, target.address,
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

/**
 * @brief   矩阵运算 – 求伴随矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的伴随矩阵赋值给矩阵target，两矩阵须为同型方阵
 */
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
                    target.address[i][j] = cofactor;
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

/**
 * @brief   矩阵运算 – 求行阶梯形矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @param   deterPtr    行列式地址，若不需要请传入NULL
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的行阶梯形矩阵赋值给矩阵target，将矩阵source的行列式赋值给*deterPtr，两矩阵须同型
 */
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
            if (fabs(target.address[i][i + echelon]) <= ZEROTHRES)
            {
                nonZero = false;
                for (tempI = i + 1; tempI < target.numRows && !nonZero; tempI++)
                {
                    if (fabs(target.address[tempI][i + echelon]) > ZEROTHRES)
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
                (deterPtr != NULL) ? *deterPtr *= target.address[i][i + echelon] : 0;
                matEleScaMul(target, i, 1 / target.address[i][i + echelon], true);
                for (j = i + 1; j < target.numRows; j++)
                {
                    matEleAdd(target, i, j, -target.address[j][i + echelon], true);
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

/**
 * @brief   矩阵运算 – 求行最简形矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @param   isEche      source是否为行阶梯形矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的行最简形矩阵赋值给矩阵target，两矩阵须同型
 */
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
                if (fabs(target.address[i][j]) > ZEROTHRES)
                {
                    if (fabs(target.address[i][j] - 1) > ZEROTHRES)
                    {
                        matEleScaMul(target, i, 1 / target.address[i][j], true);
                    }
                    for (k = i - 1; k >= 0; k--)
                    {
                        matEleAdd(target, i, k, -target.address[k][j], true);
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

/**
 * @brief   矩阵运算 – 求矩阵的秩
 * @param   matrix      矩阵
 * @param   isEche      matrix是否为行阶梯形矩阵
 * @param   rankPtr     秩地址
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 指针为空
 * @note    求矩阵matrix的秩，并赋值给*rankPtr
 */
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
                if (fabs(matemp.address[i][j]) > ZEROTHRES)
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

/**
 * @brief   矩阵运算 – 求矩阵的行列式
 * @param   matrix      矩阵
 * @param   deterPtr    行列式地址
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求，或指针为空
 * @note    求矩阵matrix的行列式，并赋值给*deterPtr，矩阵须为方阵
 */
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

/**
 * @brief   矩阵运算 – 求元素的余子式
 * @param   matrix      矩阵
 * @param   indexRow    元素行索引
 * @param   indexCol    元素列索引
 * @param   minorPtr    余子式地址
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求，或指针为空
 * @note    求矩阵matrix第indexRow行第indexCol列元素的余子式，并赋值给*minorPtr，矩阵须为方阵
 */
int matMinor(Mat matrix, int indexRow, int indexCol, double *minorPtr)
{
    Mat matemp;
    if (matrix.numRows == matrix.numCols && minorPtr != NULL)
    {
        matInit(&matemp, matrix.numRows - 1, matrix.numRows - 1);
        matCpLocal(matrix.address, matemp.address,
                   0, indexRow - 1, 0, indexRow - 1, 0, indexCol - 1, 0, indexCol - 1);
        matCpLocal(matrix.address, matemp.address,
                   indexRow + 1, matrix.numRows - 1, indexRow, matrix.numRows - 2,
                   0, indexCol - 1, 0, indexCol - 1);
        matCpLocal(matrix.address, matemp.address,
                   0, indexRow - 1, 0, indexRow - 1,
                   indexCol + 1, matrix.numRows - 1, indexCol, matrix.numRows - 2);
        matCpLocal(matrix.address, matemp.address,
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

/**
 * @brief   矩阵运算 – 求元素的代数余子式
 * @param   matrix      矩阵
 * @param   indexRow    元素行索引
 * @param   indexCol    元素列索引
 * @param   cofacPtr    代数余子式地址
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求，或指针为空
 * @note    求矩阵matrix第indexRow行第indexCol列元素的代数余子式，并赋值给*cofacPtr，矩阵须为方阵
 */
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