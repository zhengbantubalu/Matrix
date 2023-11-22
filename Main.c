#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MatOper.h"
#include "MatUtil.h"

int main(void)
{
    int numRows = 0, numCols = 0;
    double **matrixIn = NULL, **matrixOut = NULL, **matrixMul = NULL, **matrixTrans = NULL;
    printf("������[����] [����] [����](���軻��)\n\n��1:\n4 4\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n\n");
    printf("��2:\n4 5\n1 1 1 1 1\n3 2 1 1 -3\n0 1 3 2 5\n5 4 3 3 -1\n\n��3:\n3 3 3 -3 4 2 -3 4 0 -1 1\n\n");
    printf("��4:\n4 4 4 1 2 4 1 2 0 2 10 5 2 0 0 1 1 7\n\n");
    scanf("%d%d", &numRows, &numCols);
    matrixIn = matInit(numRows, numCols);
    matrixOut = matInit(numRows, numCols);
    matEnIn(matrixIn, numRows, numCols);
    matEchelon(matrixIn, matrixOut, numRows, numCols);
    printf("\nrank=%d\n", matRank(matrixOut, numRows, numCols, true));
    if (numRows == numCols)
    {
        printf("\ndet=%.3lf\n", matDet(matrixIn, numRows));
    }
    printf("\n�н����ξ���:\n");
    matEnOut(matrixOut, numRows, numCols);
    matRedEche(matrixOut, matrixOut, numRows, numCols, true);
    printf("\n������ξ���:\n");
    matEnOut(matrixOut, numRows, numCols);
    matrixTrans = matInit(numCols, numRows);
    matTrans(matrixIn, matrixTrans, numRows, numCols);
    printf("\nת�þ���:\n");
    matEnOut(matrixTrans, numCols, numRows);
    if (numRows == numCols)
    {
        matAdd(matrixIn, matrixTrans, matrixOut, numRows, numRows);
        printf("\nԭ������ת�þ������:\n");
        matEnOut(matrixOut, numRows, numRows);
        matSub(matrixTrans, matrixIn, matrixOut, numRows, numRows);
        printf("\nת�þ����ԭ����:\n");
        matEnOut(matrixOut, numRows, numRows);
        matAdj(matrixIn, matrixOut, numRows);
        printf("\n�������:\n");
        matEnOut(matrixOut, numRows, numRows);
        matrixMul = matInit(numRows, numRows);
        matMul(matrixIn, matrixOut, matrixMul, numRows, numRows, numRows);
        printf("\nԭ���������������:\n");
        matEnOut(matrixMul, numRows, numRows);
        matFree(matrixMul, numRows);
        matrixMul = NULL;
        switch (matInverse(matrixIn, matrixOut, numRows))
        {
        case SUCCESS:
            printf("\n�����:\n");
            matEnOut(matrixOut, numRows, numRows);
            matInverse(matrixOut, matrixOut, numRows);
            printf("\n�����������:\n");
            matEnOut(matrixOut, numRows, numRows);
            printf("�������ԭ�������: ");
            switch (matEnEqual(matrixIn, matrixOut, numRows, numRows))
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
    matFree(matrixIn, numRows);
    matFree(matrixOut, numRows);
    matFree(matrixTrans, numCols);
    matrixIn = NULL;
    matrixOut = NULL;
    matrixTrans = NULL;
    putchar('\n');
    system("pause");
    return 0;
}