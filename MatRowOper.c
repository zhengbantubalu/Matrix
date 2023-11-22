#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief   ������ȱ任 �C �Ի��任
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @param   index1      Ŀ��1������
 * @param   index2      Ŀ��2������
 * @param   isRowOper   Ϊ���ʾ�б任��Ϊ�ٱ�ʾ�б任
 * @note    ������matrix��index1�����index2�жԻ�(�б任ͬ��)
 */
void matRowSwap(double **matrix, int numRows, int numCols, int index1, int index2, bool isRowOper)
{
    int i = 0;
    double *tempArr = NULL;
    if (isRowOper)
    {
        tempArr = (double *)malloc(sizeof(double) * numCols);
        for (i = 0; i < numCols; i++)
        {
            tempArr[i] = matrix[index1][i];
            matrix[index1][i] = matrix[index2][i];
            matrix[index2][i] = tempArr[i];
        }
    }
    else
    {
        tempArr = (double *)malloc(sizeof(double) * numRows);
        for (i = 0; i < numRows; i++)
        {
            tempArr[i] = matrix[i][index1];
            matrix[i][index1] = matrix[i][index2];
            matrix[i][index2] = tempArr[i];
        }
    }
    free(tempArr);
    tempArr = NULL;
}

/**
 * @brief   ������ȱ任 �C ���˱任
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @param   index       Ŀ��������
 * @param   multiplier  ���˱���
 * @param   isRowOper   Ϊ���ʾ�б任��Ϊ�ٱ�ʾ�б任
 * @note    ������matrix��index�г���multiplier(�б任ͬ��)
 */
void matRowScaMul(double **matrix, int numRows, int numCols, int index, double multiplier, bool isRowOper)
{
    int i = 0;
    if (isRowOper)
    {
        for (i = 0; i < numCols; i++)
        {
            matrix[index][i] *= multiplier;
        }
    }
    else
    {
        for (i = 0; i < numRows; i++)
        {
            matrix[i][index] *= multiplier;
        }
    }
}

/**
 * @brief   ������ȱ任 �C ���ӱ任
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @param   indexSource Դ������
 * @param   indexTarget Ŀ��������
 * @param   multiplier  ���˱���
 * @param   isRowOper   Ϊ���ʾ�б任��Ϊ�ٱ�ʾ�б任
 * @note    ������matrix��indexSource�е�multiplier���ӵ���indexTarget����(�б任ͬ��)
 */
void matRowAdd(double **matrix, int numRows, int numCols,
               int indexSource, int indexTarget, double multiplier, bool isRowOper)
{
    int i = 0;
    if (isRowOper)
    {
        for (i = 0; i < numCols; i++)
        {
            matrix[indexTarget][i] += matrix[indexSource][i] * multiplier;
        }
    }
    else
    {
        for (i = 0; i < numRows; i++)
        {
            matrix[i][indexTarget] += matrix[i][indexSource] * multiplier;
        }
    }
}