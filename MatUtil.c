#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MatUtil.h"

/**
 * @brief   ���󹤾� �C �����ʼ��
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @return  �����ַ
 * @note    �������Ĵ洢�ռ䣬����ֵΪ�����
 */
double **matInit(int numRows, int numCols)
{
    int i = 0, j = 0;
    double **matrix = (double **)malloc(sizeof(double *) * numRows);
    for (i = 0; i < numRows; i++)
    {
        matrix[i] = (double *)malloc(sizeof(double) * numCols);
        for (j = 0; j < numCols; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

/**
 * @brief   ���󹤾� �C ����洢�ռ��ͷ�
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @note    �ͷž���matrix�Ĵ洢�ռ�
 */
void matFree(double **matrix, int numRows)
{
    int i = 0;
    for (i = 0; i < numRows; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
}

/**
 * @brief   ���󹤾� �C ������������
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    �������matrix
 */
void matEnIn(double **matrix, int numRows, int numCols)
{
    matLoIn(matrix, 0, numRows - 1, 0, numCols - 1);
}

/**
 * @brief   ���󹤾� �C ����ֲ�����
 * @param   matrix      �����ַ
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @note    �������matrix��ָ����Χ
 */
void matLoIn(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

/**
 * @brief   ���󹤾� �C �����������
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    �������matrix
 */
void matEnOut(double **matrix, int numRows, int numCols)
{
    matLoOut(matrix, 0, numRows - 1, 0, numCols - 1);
}

/**
 * @brief   ���󹤾� �C ����ֲ����
 * @param   matrix      �����ַ
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @note    �������matrix��ָ����Χ
 */
void matLoOut(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            if (fabs(matrix[i][j] - (int)matrix[i][j]) < ZEROTHRES ||
                fabs(matrix[i][j] - (int)matrix[i][j] + 1) < ZEROTHRES ||
                fabs(matrix[i][j] - (int)matrix[i][j] - 1) < ZEROTHRES)
            {
                if (fabs(matrix[i][j]) < 0.001)
                {
                    printf("%6d ", 0);
                }
                else
                {
                    printf("%6.0lf ", matrix[i][j]);
                }
            }
            else
            {
                printf("%6.3lf ", matrix[i][j]);
            }
        }
        putchar('\n');
    }
}

/**
 * @brief   ���󹤾� �C �������帴��
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    ������matSource���Ƶ�����matTarget��Դ������Ŀ����������������
 */
void matEnCopy(double **matSource, double **matTarget, int numRows, int numCols)
{
    if (matSource != matTarget)
    {
        matLoCopy(matSource, matTarget, 0, numRows - 1, 0, numRows - 1, 0, numCols - 1, 0, numCols - 1);
    }
}

/**
 * @brief   ���󹤾� �C ����ֲ�����
 * @param   matSource   Դ�����ַ
 * @param   matTarget   Ŀ������ַ
 * @param   rowSouStart Դ������ʼ��
 * @param   rowSouEnd   Դ������ֹ��
 * @param   rowTarStart Ŀ�������ʼ��
 * @param   rowTarEnd   Ŀ�������ֹ��
 * @param   colSouStart Դ������ʼ��
 * @param   colSouEnd   Դ������ֹ��
 * @param   colTarStart Ŀ�������ʼ��
 * @param   colTarEnd   Ŀ�������ֹ��
 * @return  SUCCESS �C ���Ƴɹ�
 * @return  ERROR �C ��������ƥ��
 * @note    ������matSource��ָ����Χ���Ƶ�����matTarget��ָ����Χ
 */
int matLoCopy(double **matSource, double **matTarget,
              int rowSouStart, int rowSouEnd, int rowTarStart, int rowTarEnd,
              int colSouStart, int colSouEnd, int colTarStart, int colTarEnd)
{
    int i = 0, j = 0;
    if (rowSouEnd - rowSouStart != rowTarEnd - rowTarStart ||
        colSouEnd - colSouStart != colTarEnd - colTarStart)
    {
        return ERROR;
    }
    for (i = 0; i <= rowSouEnd - rowSouStart; i++)
    {
        for (j = 0; j <= colSouEnd - colSouStart; j++)
        {
            matTarget[i + rowTarStart][j + colTarStart] = matSource[i + rowSouStart][j + colSouStart];
        }
    }
    return SUCCESS;
}

/**
 * @brief   ���󹤾� �C ��ֵΪ��λ����
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @note    ������matrix��ֵΪ��λ���󣬾��������������
 */
void matAssignE(double **matrix, int numRows)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numRows; j++)
        {
            matrix[i][j] = i == j ? 1 : 0;
        }
    }
}