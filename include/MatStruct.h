#ifndef _MATSTRUCT_H_
#define _MATSTRUCT_H_

/**
 * @brief   ����ṹ��
 * @note    data �C ָ��������ݵ�ָ��
 * @note    numRows �C ��������
 * @note    numCols �C ��������
 */
typedef struct mat
{
    double **data;
    int numRows;
    int numCols;
} Mat;

#endif