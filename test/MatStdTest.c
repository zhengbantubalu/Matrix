#include ".\include\MatStdTest.h"
#include "..\include\MatOper.h"
#include "..\include\MatUtil.h"
#include "..\include\MatIO.h"
#include "..\include\MatConst.h"
#include <stdio.h>

/**
 * @brief   ²âÊÔ ¨C ¾ØÕóÔËËã±ê×¼²âÊÔ
 * @param   matrix      ¾ØÕó
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
    printf("\nĞĞ½×ÌİĞÎ¾ØÕó:\n");
    matOutput(matOut);
    matRedEche(matOut, matOut, true);
    printf("\nĞĞ×î¼òĞÎ¾ØÕó:\n");
    matOutput(matOut);
    matInit(&matTra, matrix.numCols, matrix.numRows);
    matTrans(matrix, matTra);
    printf("\n×ªÖÃ¾ØÕó:\n");
    matOutput(matTra);
    if (matrix.numRows == matrix.numCols)
    {
        matAdd(matrix, matTra, matOut);
        printf("\nÔ­¾ØÕó¼Ó×ªÖÃ¾ØÕó:\n");
        matOutput(matOut);
        matSub(matrix, matTra, matOut);
        printf("\nÔ­¾ØÕó¼õ×ªÖÃ¾ØÕó:\n");
        matOutput(matOut);
        matAdjo(matrix, matOut);
        printf("\n°éËæ¾ØÕó:\n");
        matOutput(matOut);
        matInit(&matMul, matrix.numRows, matrix.numCols);
        matMulti(matrix, matOut, matMul);
        printf("\nÔ­¾ØÕó³Ë°éËæ¾ØÕó:\n");
        matOutput(matMul);
        matFree(&matMul);
        switch (matInver(matrix, matOut))
        {
        case SUCCESS:
            printf("\nÄæ¾ØÕó:\n");
            matOutput(matOut);
            matInver(matOut, matOut);
            printf("\nÄæ¾ØÕóµÄÄæ¾ØÕó:\n");
            matOutput(matOut);
            printf("ÄæµÄÄæÓëÔ­¾ØÕóÏàµÈ: ");
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
            printf("\n¾ØÕó²»¿ÉÄæ\n");
            break;
        }
    }
    matFree(&matOut);
    matFree(&matTra);
}