#include "..\include\MatEleTrans.h"
#include <stdlib.h>

/**
 * @brief   ������ȱ任 �C �Ի��任
 * @param   matrix      ����
 * @param   index1      Ŀ��1������
 * @param   index2      Ŀ��2������
 * @param   isRow       Ϊ�����б任��Ϊ�����б任
 * @note    ������matrix�ĵ�index1�����index2�жԻ�(�б任ͬ��)
 */
void matEleSwap(Mat matrix, int index1, int index2, bool isRow)
{
    int i = 0;
    double *tempArr = NULL;
    if (isRow)
    {
        tempArr = (double *)malloc(sizeof(double) * matrix.numCols);
        for (i = 0; i < matrix.numCols; i++)
        {
            tempArr[i] = matrix.address[index1][i];
            matrix.address[index1][i] = matrix.address[index2][i];
            matrix.address[index2][i] = tempArr[i];
        }
    }
    else
    {
        tempArr = (double *)malloc(sizeof(double) * matrix.numRows);
        for (i = 0; i < matrix.numRows; i++)
        {
            tempArr[i] = matrix.address[i][index1];
            matrix.address[i][index1] = matrix.address[i][index2];
            matrix.address[i][index2] = tempArr[i];
        }
    }
    free(tempArr);
    tempArr = NULL;
}

/**
 * @brief   ������ȱ任 �C ���˱任
 * @param   matrix      ����
 * @param   index       Ŀ��������
 * @param   multer      ���˱���
 * @param   isRow       Ϊ�����б任��Ϊ�����б任
 * @note    ������matrix��index�г���multer(�б任ͬ��)
 */
void matEleScaMul(Mat matrix, int index, double multer, bool isRow)
{
    int i = 0;
    if (isRow)
    {
        for (i = 0; i < matrix.numCols; i++)
        {
            matrix.address[index][i] *= multer;
        }
    }
    else
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            matrix.address[i][index] *= multer;
        }
    }
}

/**
 * @brief   ������ȱ任 �C ���ӱ任
 * @param   matrix      ����
 * @param   indexS      Դ������
 * @param   indexT      Ŀ��������
 * @param   multer      ���˱���
 * @param   isRow       Ϊ�����б任��Ϊ�����б任
 * @note    ������matrix��indexS�е�multer���ӵ���indexT����(�б任ͬ��)
 */
void matEleAdd(Mat matrix, int indexS, int indexT, double multer, bool isRow)
{
    int i = 0;
    if (isRow)
    {
        for (i = 0; i < matrix.numCols; i++)
        {
            matrix.address[indexT][i] += matrix.address[indexS][i] * multer;
        }
    }
    else
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            matrix.address[i][indexT] += matrix.address[i][indexS] * multer;
        }
    }
}