/**
 * @file    MatStdTest.c
 * @brief   测试 – 矩阵运算标准测试
 */

#include "./include/MatStdTest.h"
#include "../include/MatOper.h"
#include "../include/MatUtil.h"
#include "../include/MatIO.h"
#include "../include/MatStruct.h"
#include "../include/MatConst.h"
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
    printf("\n行阶梯形矩阵:\n");
    matOutput(matOut, PRECISION, WIDTH);
    matRedEche(matOut, matOut, true);
    printf("\n行最简形矩阵:\n");
    matOutput(matOut, PRECISION, WIDTH);
    matInit(&matTra, matrix.numCols, matrix.numRows);
    matTrans(matrix, matTra);
    printf("\n转置矩阵:\n");
    matOutput(matTra, PRECISION, WIDTH);
    if (matrix.numRows == matrix.numCols)
    {
        matAdd(matrix, matTra, matOut);
        printf("\n原矩阵加转置矩阵:\n");
        matOutput(matOut, PRECISION, WIDTH);
        matSub(matrix, matTra, matOut);
        printf("\n原矩阵减转置矩阵:\n");
        matOutput(matOut, PRECISION, WIDTH);
        matAdjo(matrix, matOut);
        printf("\n伴随矩阵:\n");
        matOutput(matOut, PRECISION, WIDTH);
        matInit(&matMul, matrix.numRows, matrix.numCols);
        matMulti(matrix, matOut, matMul);
        printf("\n原矩阵乘伴随矩阵:\n");
        matOutput(matMul, PRECISION, WIDTH);
        matFree(&matMul);
        switch (matInver(matrix, matOut))
        {
        case SUCCESS:
            printf("\n逆矩阵:\n");
            matOutput(matOut, PRECISION, WIDTH);
            matInver(matOut, matOut);
            printf("\n逆矩阵的逆矩阵:\n");
            matOutput(matOut, PRECISION, WIDTH);
            printf("逆的逆与原矩阵相等: ");
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
            printf("\n矩阵不可逆\n");
            break;
        }
    }
    matFree(&matOut);
    matFree(&matTra);
}