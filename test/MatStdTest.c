#include ".\include\MatStdTest.h"
#include "..\include\MatOper.h"
#include "..\include\MatUtil.h"
#include "..\include\MatIO.h"
#include "..\include\MatConst.h"
#include <stdio.h>

/**
 * @brief   ���� �C ���������׼����
 * @param   matrix      ����
 */
void matStdTest(Mat matrix)
{
    Mat matOut, matTra, matMul;
    int rank = 0;
    double det = 0;
    matInit(&matOut, matrix.numRows, matrix.numCols);
    matEche(matrix, matOut, NULL);
    matRank(matOut, true, &rank);
    printf("rank=%d\n", rank);
    if (matrix.numRows == matrix.numCols)
    {
        matDeter(matrix, &det);
        printf("\ndet=%.3lf\n", det);
    }
    printf("\n�н����ξ���:\n");
    matOutput(matOut);
    matRedEche(matOut, matOut, true);
    printf("\n������ξ���:\n");
    matOutput(matOut);
    matInit(&matTra, matrix.numCols, matrix.numRows);
    matTrans(matrix, matTra);
    printf("\nת�þ���:\n");
    matOutput(matTra);
    if (matrix.numRows == matrix.numCols)
    {
        matAdd(matrix, matTra, matOut);
        printf("\nԭ�����ת�þ���:\n");
        matOutput(matOut);
        matSub(matrix, matTra, matOut);
        printf("\nԭ�����ת�þ���:\n");
        matOutput(matOut);
        matAdjo(matrix, matOut);
        printf("\n�������:\n");
        matOutput(matOut);
        matInit(&matMul, matrix.numRows, matrix.numCols);
        matMulti(matrix, matOut, matMul);
        printf("\nԭ����˰������:\n");
        matOutput(matMul);
        matFree(&matMul);
        switch (matInver(matrix, matOut))
        {
        case SUCCESS:
            printf("\n�����:\n");
            matOutput(matOut);
            matInver(matOut, matOut);
            printf("\n�����������:\n");
            matOutput(matOut);
            printf("�������ԭ�������: ");
            if (matEqual(matrix, matOut))
            {
                printf("TRUE\n");
            }
            else
            {
                printf("FALSE\n");
            }
            break;
        case SINGULAR:
            printf("\n���󲻿���\n");
            break;
        }
    }
    matFree(&matOut);
    matFree(&matTra);
}