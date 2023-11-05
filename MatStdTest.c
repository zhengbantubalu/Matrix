#include "MatHead.h"

/**
 * @brief   矩阵标准测试
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 */
void matStdTest(double **matrix, int numRows, int numCols)
{
    double **matrixOut = NULL, **matrixMul = NULL, **matrixTrans = NULL;
    matrixOut = matInit(numRows, numCols);
    matEchelon(matrix, matrixOut, numRows, numCols);
    printf("\nrank=%d\n", matRank(matrixOut, numRows, numCols, true));
    if (numRows == numCols)
    {
        printf("\ndet=%.3lf\n", matDet(matrix, numRows));
    }
    printf("\n行阶梯形矩阵:\n");
    matEnOut(matrixOut, numRows, numCols);
    matRedEche(matrixOut, matrixOut, numRows, numCols, true);
    printf("\n行最简形矩阵:\n");
    matEnOut(matrixOut, numRows, numCols);
    matrixTrans = matInit(numCols, numRows);
    matTrans(matrix, matrixTrans, numRows, numCols);
    printf("\n转置矩阵:\n");
    matEnOut(matrixTrans, numCols, numRows);
    if (numRows == numCols)
    {
        matAdd(matrix, matrixTrans, matrixOut, numRows, numRows);
        printf("\n原矩阵与转置矩阵相加:\n");
        matEnOut(matrixOut, numRows, numRows);
        matSub(matrixTrans, matrix, matrixOut, numRows, numRows);
        printf("\n转置矩阵减原矩阵:\n");
        matEnOut(matrixOut, numRows, numRows);
        matAdj(matrix, matrixOut, numRows);
        printf("\n伴随矩阵:\n");
        matEnOut(matrixOut, numRows, numRows);
        matrixMul = matInit(numRows, numRows);
        matMul(matrix, matrixOut, matrixMul, numRows, numRows, numRows);
        printf("\n原矩阵与伴随矩阵相乘:\n");
        matEnOut(matrixMul, numRows, numRows);
        matFree(matrixMul, numRows);
        matrixMul = NULL;
        switch (matInverse(matrix, matrixOut, numRows))
        {
        case SUCCESS:
            printf("\n逆矩阵:\n");
            matEnOut(matrixOut, numRows, numRows);
            matInverse(matrixOut, matrixOut, numRows);
            printf("\n逆矩阵的逆矩阵:\n");
            matEnOut(matrixOut, numRows, numRows);
            printf("逆的逆与原矩阵相等: ");
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
            printf("\n矩阵不可逆\n");
            break;
        }
    }
    matFree(matrixOut, numRows);
    matFree(matrixTrans, numCols);
    matrixOut = NULL;
    matrixTrans = NULL;
    putchar('\n');
}