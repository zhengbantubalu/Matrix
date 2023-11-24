#include ".\include\MaxInd.h"
#include "..\include\MatOper.h"
#include "..\include\MatUtil.h"
#include "..\include\MatIO.h"
#include "..\include\MatStruct.h"
#include "..\include\MatConst.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void maxInd(void)
{
    int i = 0, j = 0, k = 0;
    Mat matrix;
    int numRows = 0, numCols = 0, rank = 0;
    int *pivot = NULL;
    bool isFirst = false;
    printf("极大线性无关组计算器\n\n");
    printf("向量维数: ");
    while (scanf("%d", &numRows) != 1)
    {
        fflush(stdin);
        printf("向量维数: ");
    }
    fflush(stdin);
    printf("向量个数: ");
    while (scanf("%d", &numCols) != 1)
    {
        fflush(stdin);
        printf("向量个数: ");
    }
    fflush(stdin);
    matInit(&matrix, numRows, numCols);
    pivot = (int *)malloc(sizeof(int) * (numRows < numCols ? numRows : numCols));
    for (i = 0; i < numCols; i++)
    {
        printf("a%d: ", i + 1);
        while (matInLocal(matrix.data, 0, numRows - 1, i, i) == BREAK)
        {
            printf("a%d: ", i + 1);
            fflush(stdin);
        }
        fflush(stdin);
    }
    matRedEche(matrix, matrix, false);
    for (rank = 0, i = 0; rank < numRows && i < numCols; i++)
    {
        if (fabs(matrix.data[rank][i]) > ZEROTHRES)
        {
            pivot[rank] = i;
            rank++;
        }
    }
    printf("\n极大线性无关组:");
    for (i = 0; i < rank; i++)
    {
        printf(" a%d", pivot[i] + 1);
    }
    putchar('\n');
    for (i = 0, j = 0; i < numCols; i++)
    {
        if (pivot[j] != i)
        {
            printf("a%d = ", i + 1);
            isFirst = true;
            for (k = 0; k < rank; k++)
            {
                if (fabs(matrix.data[k][i]) > ZEROTHRES)
                {
                    if (isFirst)
                    {
                        isFirst = false;
                        if (matrix.data[k][i] < 0)
                        {
                            printf("- ");
                        }
                    }
                    else if (matrix.data[k][i] > 0)
                    {
                        printf(" + ");
                    }
                    else
                    {
                        printf(" - ");
                    }
                    if (fabs(fabs(matrix.data[k][i]) - 1) > ZEROTHRES)
                    {
                        prtDouble(matrix.data[k][i], PRECISION, 0, true);
                        putchar(' ');
                    }
                    printf("a%d", pivot[k] + 1);
                }
            }
            putchar('\n');
        }
        else
        {
            j++;
        }
    }
    putchar('\n');
    system("pause");
    matFree(&matrix);
}