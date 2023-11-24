#include ".\include\MatStdTest.h"
#include "..\include\MatOper.h"
#include "..\include\MatUtil.h"
#include "..\include\MatIO.h"
#include "..\include\MatStruct.h"
#include "..\include\MatConst.h"
#include <stdio.h>
#include <stdbool.h>

void matStdTest(Mat matrix)
{
    Mat matOut, matTra, matMul;
    int rank = 0;
    double det = 0;
    matInit(&matOut, matrix.numRows, matrix.numCols);
    matEche(matrix, matOut, NULL);
    matRank(matOut, true, &rank);
    printf("rank = %d\n", rank);
    if (matrix.numRows == matrix.numCols)
    {
        matDeter(matrix, &det);
        printf("\ndet = ");
        prtDouble(det, PRECISION, 0, false);
        putchar('\n');
    }
    printf("\n�н����ξ���:\n");
    matOutput(matOut, PRECISION, WIDTH);
    matRedEche(matOut, matOut, true);
    printf("\n������ξ���:\n");
    matOutput(matOut, PRECISION, WIDTH);
    matInit(&matTra, matrix.numCols, matrix.numRows);
    matTrans(matrix, matTra);
    printf("\nת�þ���:\n");
    matOutput(matTra, PRECISION, WIDTH);
    if (matrix.numRows == matrix.numCols)
    {
        matData(matrix, matTra, matOut);
        printf("\nԭ�����ת�þ���:\n");
        matOutput(matOut, PRECISION, WIDTH);
        matSub(matrix, matTra, matOut);
        printf("\nԭ�����ת�þ���:\n");
        matOutput(matOut, PRECISION, WIDTH);
        matAdjo(matrix, matOut);
        printf("\n�������:\n");
        matOutput(matOut, PRECISION, WIDTH);
        matInit(&matMul, matrix.numRows, matrix.numCols);
        matMulti(matrix, matOut, matMul);
        printf("\nԭ����˰������:\n");
        matOutput(matMul, PRECISION, WIDTH);
        matFree(&matMul);
        switch (matInver(matrix, matOut))
        {
        case SUCCESS:
            printf("\n�����:\n");
            matOutput(matOut, PRECISION, WIDTH);
            matInver(matOut, matOut);
            printf("\n�����������:\n");
            matOutput(matOut, PRECISION, WIDTH);
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