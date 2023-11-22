#include "..\include\MatUtil.h"
#include "..\include\MatConst.h"
#include <stdlib.h>

/**
 * @brief   ���󹤾� �C �����ʼ��
 * @param   matPtr      ����ṹ���ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    �������Ĵ洢�ռ䣬����ֵΪ�����
 */
void matInit(Mat *matPtr, int numRows, int numCols)
{
    int i = 0, j = 0;
    (*matPtr).address = (double **)malloc(sizeof(double *) * numRows);
    (*matPtr).numRows = numRows;
    (*matPtr).numCols = numCols;
    for (i = 0; i < numRows; i++)
    {
        (*matPtr).address[i] = (double *)malloc(sizeof(double) * numCols);
        for (j = 0; j < numCols; j++)
        {
            (*matPtr).address[i][j] = 0;
        }
    }
}

/**
 * @brief   ���󹤾� �C ����洢�ռ��ͷ�
 * @param   matPtr      ����ṹ���ַ
 * @note    �ͷž���Ĵ洢�ռ�
 */
void matFree(Mat *matPtr)
{
    int i = 0;
    for (i = 0; i < (*matPtr).numRows; i++)
    {
        free((*matPtr).address[i]);
        (*matPtr).address[i] = NULL;
    }
    free((*matPtr).address);
    (*matPtr).address = NULL;
    (*matPtr).numRows = 0;
    (*matPtr).numCols = 0;
}

/**
 * @brief   ���󹤾� �C ��ֵΪ��λ����
 * @param   matrix      ����
 * @param   numRows     ��������
 * @return  SUCCESS �C ��ֵ�ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������matrix��ֵΪ��λ���󣬾�����Ϊ����
 */
int matSetE(Mat matrix)
{
    if (matrix.numRows = matrix.numCols)
    {
        matSetELocal(matrix.address, 0, matrix.numRows - 1, 0, matrix.numRows - 1);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   ���󹤾� �C �ֲ���ֵΪ��λ����
 * @param   matAdd      �����ַ
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @return  SUCCESS �C ��ֵ�ɹ�
 * @return  ERROR �C ��Χ�����������
 * @note    �������ָ����Χ��ֵΪ��λ���󣬷�Χ�����������
 */
void matSetELocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            matAdd[i][j] = (i - rowStart) == (j - colStart) ? 1 : 0;
        }
    }
}

/**
 * @brief   ���󹤾� �C ������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ���Ƴɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source���Ƶ�����target��Դ������Ŀ�������ͬ��
 */
int matCopy(Mat source, Mat target)
{
    if (source.address == target.address)
    {
        return SUCCESS;
    }
    else if (matSameDim(source, target))
    {
        matCpLocal(source.address, target.address,
                   0, source.numRows - 1, 0, source.numRows - 1,
                   0, source.numCols - 1, 0, source.numCols - 1);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   ���󹤾� �C ����ֲ�����
 * @param   srcAdd      Դ�����ַ
 * @param   tgtAdd      Ŀ������ַ
 * @param   rowSrcSt    Դ������ʼ��
 * @param   rowSrcEd    Դ������ֹ��
 * @param   rowTarSt    Ŀ�������ʼ��
 * @param   rowTarEd    Ŀ�������ֹ��
 * @param   colSrcSt    Դ������ʼ��
 * @param   colSrcEd    Դ������ֹ��
 * @param   colTarSt    Ŀ�������ʼ��
 * @param   colTarEd    Ŀ�������ֹ��
 * @return  SUCCESS �C ���Ƴɹ�
 * @return  ERROR �C ָ����Χ�����������
 * @note    ��Դ�����ָ����Χ���Ƶ�Ŀ������ָ����Χ��������ָ����Χ�������������
 */
int matCpLocal(double **srcAdd, double **tgtAdd,
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
                tgtAdd[i + rowTgtSt][j + colTarSt] = srcAdd[i + rowSrcSt][j + colSrcSt];
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
 * @brief   ���󹤾� �C ����ͬ���ж�
 * @param   matrix1     ����1
 * @param   matrix2     ����2
 * @return  ture �C ͬ��
 * @return  false �C ��ͬ��
 * @note    �жϾ���matrix1�����matrix2�Ƿ�ͬ�ͣ����Ƿ�����������������
 */
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

/**
 * @brief   ���󹤾� �C ��������ж�
 * @param   matrix1     ����1
 * @param   matrix2     ����2
 * @return  ture �C ���
 * @return  false �C �����
 * @note    �жϾ���matrix1�����matrix2�Ƿ���ȣ���������ͬ��
 */
bool matEqual(Mat matrix1, Mat matrix2)
{
    if (matrix1.address == matrix2.address)
    {
        return true;
    }
    else if (matSameDim(matrix1, matrix2))
    {
        return matEqLocal(matrix1.address, matrix2.address,
                          0, matrix1.numRows - 1, 0, matrix1.numRows - 1,
                          0, matrix1.numCols - 1, 0, matrix1.numCols - 1);
    }
    else
    {
        return false;
    }
}

/**
 * @brief   ���󹤾� �C ����ֲ�����ж�
 * @param   matAdd1     ����1��ַ
 * @param   matAdd2     ����2��ַ
 * @param   rowSt1      ����1��ʼ��
 * @param   rowEd1      ����1��ֹ��
 * @param   rowSt2      ����2��ʼ��
 * @param   rowEd2      ����2��ֹ��
 * @param   colSt1      ����1��ʼ��
 * @param   colEd1      ����1��ֹ��
 * @param   colSt2      ����2��ʼ��
 * @param   colEd2      ����2��ֹ��
 * @return  true �C ���
 * @return  false �C �����
 * @note    �жϾ���matrix1�����matrix2ָ����Χ�Ƿ���ȣ�������Χ�����������
 */
bool matEqLocal(double **matAdd1, double **matAdd2,
                int rowSt1, int rowEd1, int rowSt2, int rowEd2,
                int colSt1, int colEd1, int colSt2, int colEd2)
{
    int i = 0, j = 0;
    for (i = 0; i <= rowEd1 - rowSt1; i++)
    {
        for (j = 0; j <= colEd1 - colSt1; j++)
        {
            if ((matAdd1[i + rowSt1][j + colSt1] - matAdd2[i + rowSt2][j + colSt2]) > ZEROTHRES)
            {
                return false;
            }
        }
    }
    return true;
}