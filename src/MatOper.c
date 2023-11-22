#include "..\include\MatOper.h"
#include "..\include\MatEleTrans.h"
#include "..\include\MatUtil.h"
#include "..\include\MatConst.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief   �������� �C ����ӷ�
 * @param   source1     Դ����1
 * @param   source2     Դ����2
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source1�����source2�ĺ͸�ֵ������target����������ͬ��
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
 * @brief   �������� �C �������
 * @param   sourceM     ��������
 * @param   sourceS     ������
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������sourceM������sourceS�Ĳֵ������target����������ͬ��
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
 * @brief   �������� �C ��������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @param   multer  ���˱���
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source����multer�Ļ���ֵ������target����������ͬ��
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
 * @brief   �������� �C ����˷�
 * @param   sourceL     �����
 * @param   sourceR     �Ҿ���
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������sourceL�����sourceR�Ļ���ֵ������target��sourceL�����������sourceR��������
 *          sourceL�����������target��������sourceR�����������target������
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
 * @brief   �������� �C ��ת�þ���
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source��ת�þ���ֵ������target��source�����������target��������source�����������target������
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
 * @brief   �������� �C �������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  SINGULAR �C ���󲻿���
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source�������ֵ������target����������Ϊͬ�ͷ���
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
 * @brief   �������� �C ��������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source�İ������ֵ������target����������Ϊͬ�ͷ���
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
 * @brief   �������� �C ���н����ξ���
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @param   deterPtr    ����ʽ��ַ��������Ҫ�봫��NULL
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source���н����ξ���ֵ������target��������source������ʽ��ֵ��*deterPtr����������ͬ��
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
 * @brief   �������� �C ��������ξ���
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @param   isEche      source�Ƿ�Ϊ�н����ξ���
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source��������ξ���ֵ������target����������ͬ��
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
 * @brief   �������� �C ��������
 * @param   matrix      ����
 * @param   isEche      matrix�Ƿ�Ϊ�н����ξ���
 * @param   rankPtr     �ȵ�ַ
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ָ��Ϊ��
 * @note    �����matrix���ȣ�����ֵ��*rankPtr
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
 * @brief   �������� �C ����������ʽ
 * @param   matrix      ����
 * @param   deterPtr    ����ʽ��ַ
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ�󣬻�ָ��Ϊ��
 * @note    �����matrix������ʽ������ֵ��*deterPtr��������Ϊ����
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
 * @brief   �������� �C ��Ԫ�ص�����ʽ
 * @param   matrix      ����
 * @param   indexRow    Ԫ��������
 * @param   indexCol    Ԫ��������
 * @param   minorPtr    ����ʽ��ַ
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ�󣬻�ָ��Ϊ��
 * @note    �����matrix��indexRow�е�indexCol��Ԫ�ص�����ʽ������ֵ��*minorPtr��������Ϊ����
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
 * @brief   �������� �C ��Ԫ�صĴ�������ʽ
 * @param   matrix      ����
 * @param   indexRow    Ԫ��������
 * @param   indexCol    Ԫ��������
 * @param   cofacPtr    ��������ʽ��ַ
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ�󣬻�ָ��Ϊ��
 * @note    �����matrix��indexRow�е�indexCol��Ԫ�صĴ�������ʽ������ֵ��*cofacPtr��������Ϊ����
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