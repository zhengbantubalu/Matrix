#include "MatHead.h"

/**
 * @brief   �������� �C ����ӷ�
 * @param   matSource1  Դ����1��ַ
 * @param   matSource2  Դ����2��ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    ������matSource1�����matSource2�ĺ͸�ֵ������matTarget����������ͬ��
 */
void matAdd(double **matSource1, double **matSource2, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[i][j] = matSource1[i][j] + matSource2[i][j];
        }
    }
}

/**
 * @brief   �������� �C �������
 * @param   matMinu     ���������ַ
 * @param   matSub      �������ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    ������matMinu������matSub�Ĳֵ������matTarget����������ͬ��
 */
void matSub(double **matMinu, double **matSub, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[i][j] = matMinu[i][j] - matSub[i][j];
        }
    }
}

/**
 * @brief   �������� �C ��������
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @param   multiplier  ���˱���
 * @note    ������matSource��multiplier����ֵ������matTarget����������ͬ��
 */
void matScaMul(double **matSource, double **matTarget, int numRows, int numCols, double multiplier)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[i][j] = matSource[i][j] * multiplier;
        }
    }
}

/**
 * @brief   �������� �C ����˷�
 * @param   matLeft     ������ַ
 * @param   matRight    �Ҿ����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRowsL    ���������
 * @param   numColsL    ���������
 * @param   numColsR    �Ҿ�������
 * @note    ������matLeft�����matRight�Ļ���ֵ������matTarget��matLeft���������matSouRight������
 *          matTarget���������matLeft������matTarget���������matRight����
 */
void matMul(double **matLeft, double **matRight, double **matTarget,
            int numRowsL, int numColsL, int numColsR)
{
    int i = 0, j = 0, k = 0;
    double tempS = 0;
    for (i = 0; i < numRowsL; i++)
    {
        for (j = 0; j < numColsR; j++)
        {
            for (k = 0, tempS = 0; k < numColsL; k++)
            {
                tempS += matLeft[i][k] * matRight[k][j];
            }
            matTarget[i][j] = tempS;
        }
    }
}

/**
 * @brief   �������� �C ��ת�þ���
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     Դ��������
 * @param   numCols     Դ��������
 * @note    ������matSource��ת�ø�ֵ������matTarget��
 *          matSource���������matTarget������matSource���������matTarget����
 */
void matTrans(double **matSource, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[j][i] = matSource[i][j];
        }
    }
}

/**
 * @brief   �������� �C �������
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @return  SUCCESS �C �������ɹ�
 * @return  SINGULAR �C ���󲻿���
 * @note    ������matSource�������ֵ������matTarget�����������������
 */
int matInverse(double **matSource, double **matTarget, int numRows)
{
    int i = 0, j = 0;
    double **matOper = NULL;
    matOper = matInit(numRows, 2 * numRows);
    matLoCopy(matSource, matOper, 0, numRows - 1, 0, numRows - 1, 0, numRows - 1, 0, numRows - 1);
    matLoAssignE(matOper, 0, numRows - 1, numRows, 2 * numRows - 1);
    if (fabs(matEchelon(matOper, matOper, numRows, 2 * numRows)) < ZEROTHRES)
    {
        return SINGULAR;
    }
    matRedEche(matOper, matOper, numRows, 2 * numRows, true);
    matLoCopy(matOper, matTarget, 0, numRows - 1, 0, numRows - 1, numRows, 2 * numRows - 1, 0, numRows - 1);
    matFree(matOper, numRows);
    matOper = NULL;
    return SUCCESS;
}

/**
 * @brief   �������� �C ��������
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @note    ������matSource�İ������ֵ������matTarget�����������������
 */
void matAdj(double **matSource, double **matTarget, int numRows)
{
    int i = 0, j = 0;
    if (matInverse(matSource, matTarget, numRows) == SUCCESS)
    {
        matScaMul(matTarget, matTarget, numRows, numRows, matDet(matSource, numRows));
    }
    else
    {
        for (i = 0; i < numRows; i++)
        {
            for (j = 0; j < numRows; j++)
            {
                matTarget[i][j] = matAlgMin(matSource, numRows, j, i);
            }
        }
    }
}

/**
 * @brief   �������� �C ���н����ξ���
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @return  ���Դ����Ϊ�����򷵻�ֵΪ����ʽ
 * @note    ������matSource���н����θ�ֵ������matTarget����������Ϊͬ�ͷ���
 */
double matEchelon(double **matSource, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0, tempI = 0, echelon = 0;
    double det = 1;
    bool nonZero = false;
    matEnCopy(matSource, matTarget, numRows, numCols);
    while (i < numRows && i + echelon < numCols)
    {
        nonZero = true;
        if (fabs(matTarget[i][i + echelon]) <= ZEROTHRES)
        {
            nonZero = false;
            for (tempI = i + 1; tempI < numRows && !nonZero; tempI++)
            {
                if (fabs(matTarget[tempI][i + echelon]) > ZEROTHRES)
                {
                    matRowSwap(matTarget, numRows, numCols, i, tempI, true);
                    nonZero = true;
                }
            }
            if (!nonZero)
            {
                det = 0;
                echelon++;
            }
        }
        if (nonZero)
        {
            det *= matTarget[i][i + echelon];
            matRowScaMul(matTarget, numRows, numCols, i, 1 / matTarget[i][i + echelon], true);
            for (j = i + 1; j < numRows; j++)
            {
                matRowAdd(matTarget, numRows, numCols, i, j, -matTarget[j][i + echelon], true);
            }
            i++;
        }
    }
    return det;
}

/**
 * @brief   �������� �C ��������ξ���
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @param   isEche      matSource�Ƿ�Ϊ�н����ξ���
 * @note    ������matSource��������θ�ֵ������matTarget����������ͬ��
 */
void matRedEche(double **matSource, double **matTarget, int numRows, int numCols, bool isEche)
{
    int i = 0, j = 0, k = 0;
    bool operated = false;
    if (isEche)
    {
        matEnCopy(matSource, matTarget, numRows, numCols);
    }
    else
    {
        matEchelon(matSource, matTarget, numRows, numCols);
    }
    for (i = numRows - 1; i >= 0; i--)
    {
        for (j = 0, operated = false; j < numCols && !operated; j++)
        {
            if (fabs(matTarget[i][j]) > ZEROTHRES)
            {
                if (fabs(matTarget[i][j] - 1) > ZEROTHRES)
                {
                    matRowScaMul(matTarget, numRows, numCols, i, 1 / matTarget[i][j], true);
                }
                for (k = i - 1; k >= 0; k--)
                {
                    matRowAdd(matTarget, numRows, numCols, i, k, -matTarget[k][j], true);
                }
                operated = true;
            }
        }
    }
}

/**
 * @brief   �������� �C ��������
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @param   isEche      matSource�Ƿ�Ϊ�н����ξ���
 * @return  �������
 * @note    �����matrix����
 */
int matRank(double **matrix, int numRows, int numCols, bool isEche)
{
    int rank = numRows, i = 0, j = 0;
    bool hasNonZero = false;
    double **matOper = NULL;
    if (isEche)
    {
        for (i = numRows - 1; i >= 0 && !hasNonZero; i--)
        {
            for (j = 0; j < numCols && !hasNonZero; j++)
            {
                if (fabs(matrix[i][j]) > ZEROTHRES)
                {
                    hasNonZero = true;
                }
            }
            if (!hasNonZero)
            {
                rank--;
            }
        }
    }
    else
    {
        matOper = matInit(numRows, numCols);
        matEchelon(matrix, matOper, numRows, numCols);
        for (i = numRows - 1; i >= 0 && !hasNonZero; i--)
        {
            for (j = 0; j < numCols && !hasNonZero; j++)
            {
                if (fabs(matOper[i][j]) > ZEROTHRES)
                {
                    hasNonZero = true;
                }
            }
            if (!hasNonZero)
            {
                rank--;
            }
        }
        matFree(matOper, numRows);
        matOper = NULL;
    }
    return rank;
}

/**
 * @brief   �������� �C ����������ʽ
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @return  ���������ʽ
 * @note    �����matrix������ʽ��������Ϊ����
 */
double matDet(double **matrix, int numRows)
{
    double det = 0;
    double **matOper = matInit(numRows, numRows);
    det = matEchelon(matrix, matOper, numRows, numRows);
    matFree(matOper, numRows);
    matOper = NULL;
    return det;
}

/**
 * @brief   �������� �C ��Ԫ�ص�����ʽ
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   indexRow    Ԫ��������
 * @param   indexCol    Ԫ��������
 * @return  �����ӦԪ�ص�����ʽ
 * @note    �����matrix��indexRow�е�indexCol�е�����ʽ��������Ϊ����
 */
double matMinor(double **matrix, int numRows, int indexRow, int indexCol)
{
    double minor = 0;
    double **matOper = matInit(numRows - 1, numRows - 1);
    matLoCopy(matrix, matOper, 0, indexRow - 1, 0, indexRow - 1, 0, indexCol - 1, 0, indexCol - 1);
    matLoCopy(matrix, matOper, indexRow + 1, numRows - 1, indexRow, numRows - 2,
              0, indexCol - 1, 0, indexCol - 1);
    matLoCopy(matrix, matOper, 0, indexRow - 1, 0, indexRow - 1,
              indexCol + 1, numRows - 1, indexCol, numRows - 2);
    matLoCopy(matrix, matOper, indexRow + 1, numRows - 1, indexRow, numRows - 2,
              indexCol + 1, numRows - 1, indexCol, numRows - 2);
    minor = matDet(matOper, numRows - 1);
    matFree(matOper, numRows - 1);
    matOper = NULL;
    return minor;
}

/**
 * @brief   �������� �C ��Ԫ�صĴ�������ʽ
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   indexRow    Ԫ��������
 * @param   indexCol    Ԫ��������
 * @return  �����ӦԪ�صĴ�������ʽ
 * @note    �����matrix��indexRow�е�indexCol�еĴ�������ʽ��������Ϊ����
 */
double matAlgMin(double **matrix, int numRows, int indexRow, int indexCol)
{
    double algMin = 0;
    algMin = matMinor(matrix, numRows, indexRow, indexCol);
    if ((indexRow + indexCol) % 2 == 0)
    {
        return algMin;
    }
    else
    {
        return -algMin;
    }
}