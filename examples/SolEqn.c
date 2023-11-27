#include "./include/SolEqn.h"
#include "../include/MatOper.h"
#include "../include/MatUtil.h"
#include "../include/MatIO.h"
#include "../include/MatStruct.h"
#include "../include/MatConst.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void static clear(void)
{
    while (getchar() != '\n')
        ;
}

void static pause(void)
{
    ungetc('\n', stdin);
    printf("\n按回车键继续...");
    getchar();
    clear();
    putchar('\n');
}

void solEqn(void)
{
    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0;
    Mat matrix;
    int numRows = 0, numCols = 0, rankCof = 0, rankAug = 0;
    int *pivot = NULL;
    bool isHomo = false;
    printf("求解线性方程组\n\n");
    printf("未知数个数: ");
    while (scanf("%d", &numCols) != 1)
    {
        clear();
        printf("未知数个数: ");
    }
    clear();
    printf("方程个数: ");
    while (scanf("%d", &numRows) != 1)
    {
        clear();
        printf("方程个数: ");
    }
    clear();
    numCols++;
    matInit(&matrix, numRows, numCols);
    pivot = (int *)malloc(sizeof(int) * (numRows < numCols ? numRows : numCols));
    printf("请输入增广矩阵:\n");
    if (matInput(matrix) == SUCCESS)
    {
        putchar('\n');
        for (i = 0, isHomo = true; i < numRows && isHomo == true; i++)
        {
            if (fabs(matrix.data[i][numCols - 1]) > ZEROTHRES)
            {
                isHomo = false;
            }
        }
        matRedEche(matrix, matrix, false);
        for (rankCof = 0, i = 0; rankCof < numRows && i < numCols - 1; i++)
        {
            if (fabs(matrix.data[rankCof][i]) > ZEROTHRES)
            {
                pivot[rankCof] = i;
                rankCof++;
            }
        }
        if (isHomo && rankCof == numCols - 1)
        {
            printf("通解:\nξ = 0\n");
            matFree(&matrix);
            clear();
            pause();
            return;
        }
        if (!isHomo)
        {
            matRank(matrix, true, &rankAug);
            if (rankCof < rankAug)
            {
                printf("方程组无解\n");
                matFree(&matrix);
                clear();
                pause();
                return;
            }
            else
            {
                printf("特解:\nη* = ( ");
                j = 0;
                if (pivot[0] == 0)
                {
                    prtDouble(matrix.data[0][numCols - 1], PRECISION, WIDTH, false);
                    putchar(' ');
                    j++;
                }
                else
                {
                    prtDouble(0, 0, WIDTH, false);
                    putchar(' ');
                }
                for (i = 1; i < numCols - 1; i++)
                {
                    if (j < rankCof && pivot[j] == i)
                    {
                        printf(", ");
                        prtDouble(matrix.data[j][numCols - 1], PRECISION, WIDTH, false);
                        putchar(' ');
                        j++;
                    }
                    else
                    {
                        printf(", ");
                        prtDouble(0, 0, WIDTH, false);
                        putchar(' ');
                    }
                }
                printf(")T\n导出组的");
            }
        }
        printf("基础解系:\n");
        for (i = pivot[0], j = 0, m = 1; i < numCols - 1; i++)
        {
            if (j == rankCof || pivot[j] != i)
            {
                printf("ξ%d = ( ", m);
                l = 0;
                if (pivot[0] == 0)
                {
                    prtDouble(-matrix.data[0][i], PRECISION, WIDTH, false);
                    putchar(' ');
                    l++;
                }
                else
                {
                    prtDouble(0, 0, WIDTH, false);
                    putchar(' ');
                }
                for (k = 1; k < numCols - 1; k++)
                {
                    if (l < rankCof && pivot[l] == k && k != i)
                    {
                        printf(", ");
                        prtDouble(-matrix.data[l][i], PRECISION, WIDTH, false);
                        putchar(' ');
                        l++;
                    }
                    else if (k == i)
                    {
                        printf(", ");
                        prtDouble(1, 0, WIDTH, false);
                        putchar(' ');
                    }
                    else
                    {
                        printf(", ");
                        prtDouble(0, 0, WIDTH, false);
                        putchar(' ');
                    }
                }
                printf(")T\n");
                m++;
            }
            else
            {
                j++;
            }
        }
        if (!isHomo)
        {
            printf("通解:\nη = η* + k1ξ1");
        }
        else
        {
            printf("通解:\nξ = k1ξ1");
        }
        for (i = 2; i < m; i++)
        {
            printf(" + k%dξ%d", i, i);
        }
        putchar('\n');
    }
    else
    {
        printf("\n输入中断\n");
    }
    matFree(&matrix);
    clear();
    pause();
}