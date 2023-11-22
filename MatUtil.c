#include "MatHead.h"

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
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    �������matrix
 */
int matEnIn(double **matrix, int numRows, int numCols)
{
    return matLoIn(matrix, 0, numRows - 1, 0, numCols - 1);
}

/**
 * @brief   ���󹤾� �C ����ֲ�����
 * @param   matrix      �����ַ
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    �������matrix��ָ����Χ
 */
int matLoIn(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
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
            scanf("%lf", &matrix[i][j]);
        }
    }
    return SUCCESS;
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
 * @return  ERROR �C ��Χ�����������
 * @note    ������matSource��ָ����Χ���Ƶ�����matTarget��ָ����Χ��������Χ�����������
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
 * @brief   ���󹤾� �C ������������ж�
 * @param   matrix1     ����1��ַ
 * @param   matrix2     ����2��ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @return  EQUAL �C ���������
 * @return  UNEQUAL �C ���������
 * @note    �жϾ���matrix1�����matrix2�Ƿ���ȣ������������������
 */
int matEnEqual(double **matrix1, double **matrix2, int numRows, int numCols)
{
    return matLoEqual(matrix1, matrix2, 0, numRows - 1, 0, numRows - 1, 0, numCols - 1, 0, numCols - 1);
}

/**
 * @brief   ���󹤾� �C ����ֲ�����ж�
 * @param   matrix1     ����1��ַ
 * @param   matrix2     ����2��ַ
 * @param   rowStart1   ����1��ʼ��
 * @param   rowEnd1     ����1��ֹ��
 * @param   rowStart2   ����2��ʼ��
 * @param   rowEnd2     ����2��ֹ��
 * @param   colStart1   ����1��ʼ��
 * @param   colEnd1     ����1��ֹ��
 * @param   colStart2   ����2��ʼ��
 * @param   colEnd2     ����2��ֹ��
 * @return  EQUAL �C ������Χ���
 * @return  UNEQUAL �C ������Χ�����
 * @return  ERROR �C ��Χ�����������
 * @note    �жϾ���matrix1�����matrix2ָ����Χ�Ƿ���ȣ�������Χ�����������
 */
int matLoEqual(double **matrix1, double **matrix2,
               int rowStart1, int rowEnd1, int rowStart2, int rowEnd2,
               int colStart1, int colEnd1, int colStart2, int colEnd2)
{
    int i = 0, j = 0;
    if (rowEnd1 - rowStart1 != rowEnd2 - rowStart2 ||
        colEnd1 - colStart1 != colEnd2 - colStart2)
    {
        return ERROR;
    }
    for (i = 0; i <= rowEnd1 - rowStart1; i++)
    {
        for (j = 0; j <= colEnd1 - colStart1; j++)
        {
            if ((matrix1[i + rowStart1][j + colStart1] - matrix2[i + rowStart2][j + colStart2]) > ZEROTHRES)
            {
                return UNEQUAL;
            }
        }
    }
    return EQUAL;
}

/**
 * @brief   ���󹤾� �C ���帳ֵΪ��λ����
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @note    ������matrix��ֵΪ��λ���󣬾��������������
 */
void matEnAssignE(double **matrix, int numRows)
{
    matLoAssignE(matrix, 0, numRows - 1, 0, numRows - 1);
}

/**
 * @brief   ���󹤾� �C �ֲ���ֵΪ��λ����
 * @param   matrix      �����ַ
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @return  SUCCESS �C ��ֵ�ɹ�
 * @return  ERROR �C ��Χ�����������
 * @note    ������matrix��ָ����Χ��ֵΪ��λ���󣬷�Χ�����������
 */
int matLoAssignE(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    if (rowEnd - rowStart != colEnd - colStart)
    {
        return ERROR;
    }
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            matrix[i][j] = (i - rowStart) == (j - colStart) ? 1 : 0;
        }
    }
    return SUCCESS;
}