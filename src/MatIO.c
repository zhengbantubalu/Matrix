#include "..\include\MatIO.h"
#include "..\include\MatConst.h"
#include <stdio.h>
#include <math.h>

/**
 * @brief   ���󹤾� �C ��������
 * @param   matrix      ����
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    �������matrix
 */
int matInput(Mat matrix)
{
    return matInLocal(matrix.address, 0, matrix.numRows - 1, 0, matrix.numCols - 1);
}

/**
 * @brief   ���󹤾� �C ����ֲ�����
 * @param   matAdd      �����ַ
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    ��������ָ����Χ
 */
int matInLocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    char ch;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            ungetc(ch = getchar(), stdin);
            if ((ch < '0' || ch > '9') && ch != ' ' && ch != '\n' && ch != '\t')
            {
                return BREAK;
            }
            scanf("%lf", &matAdd[i][j]);
        }
    }
    return SUCCESS;
}

/**
 * @brief   ���󹤾� �C �������
 * @param   matrix      ����
 * @note    �������matrix
 */
void matOutput(Mat matrix)
{
    matOutLocal(matrix.address, 0, matrix.numRows - 1, 0, matrix.numCols - 1);
}

/**
 * @brief   ���󹤾� �C ����ֲ����
 * @param   matAdd      ����
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @note    ��������ָ����Χ
 */
void matOutLocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            if (fabs(matAdd[i][j] - (int)matAdd[i][j]) < ZEROTHRES ||
                fabs(matAdd[i][j] - (int)matAdd[i][j] + 1) < ZEROTHRES ||
                fabs(matAdd[i][j] - (int)matAdd[i][j] - 1) < ZEROTHRES)
            {
                if (fabs(matAdd[i][j]) < 0.001)
                {
                    printf("%6d ", 0);
                }
                else
                {
                    printf("%6.0lf ", matAdd[i][j]);
                }
            }
            else
            {
                printf("%6.3lf ", matAdd[i][j]);
            }
        }
        putchar('\n');
    }
}