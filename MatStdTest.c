#include "MatHead.h"

/**
 * @brief   �����׼����
 * @param   matrix      �����ַ
 * @param   numRows     ��������
 * @param   numCols     ��������
 */
void matStdTest(double **matrix, int numRows, int numCols)
{
    double **matrixOut = NULL, **matrixMul = NULL, **matrixTrans = NULL;
    matrixOut = matInit(numRows, numCols);
    matEchelon(matrix, matrixOut, numRows, numCols);
    printf("rank=%d\n", matRank(matrixOut, numRows, numCols, true));
    if (numRows == numCols)
    {
        printf("\ndet=%.3lf\n", matDet(matrix, numRows));
    }
    printf("\n�н����ξ���:\n");
    matEnOut(matrixOut, numRows, numCols);
    matRedEche(matrixOut, matrixOut, numRows, numCols, true);
    printf("\n������ξ���:\n");
    matEnOut(matrixOut, numRows, numCols);
    matrixTrans = matInit(numCols, numRows);
    matTrans(matrix, matrixTrans, numRows, numCols);
    printf("\nת�þ���:\n");
    matEnOut(matrixTrans, numCols, numRows);
    if (numRows == numCols)
    {
        matAdd(matrix, matrixTrans, matrixOut, numRows, numRows);
        printf("\nԭ������ת�þ������:\n");
        matEnOut(matrixOut, numRows, numRows);
        matSub(matrixTrans, matrix, matrixOut, numRows, numRows);
        printf("\nת�þ����ԭ����:\n");
        matEnOut(matrixOut, numRows, numRows);
        matAdj(matrix, matrixOut, numRows);
        printf("\n�������:\n");
        matEnOut(matrixOut, numRows, numRows);
        matrixMul = matInit(numRows, numRows);
        matMul(matrix, matrixOut, matrixMul, numRows, numRows, numRows);
        printf("\nԭ���������������:\n");
        matEnOut(matrixMul, numRows, numRows);
        matFree(matrixMul, numRows);
        matrixMul = NULL;
        switch (matInverse(matrix, matrixOut, numRows))
        {
        case SUCCESS:
            printf("\n�����:\n");
            matEnOut(matrixOut, numRows, numRows);
            matInverse(matrixOut, matrixOut, numRows);
            printf("\n�����������:\n");
            matEnOut(matrixOut, numRows, numRows);
            printf("�������ԭ�������: ");
            switch (matEnEqual(matrix, matrixOut, numRows, numRows))
            {
            case EQUAL:
                printf("TRUE\n");
                break;
            case UNEQUAL:
                printf("FALSE\n");
                break;
            }
            break;
        case SINGULAR:
            printf("\n���󲻿���\n");
            break;
        }
    }
    matFree(matrixOut, numRows);
    matFree(matrixTrans, numCols);
    matrixOut = NULL;
    matrixTrans = NULL;
}