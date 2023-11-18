#include "..\include\MatIO.h"
#include "..\include\MatConst.h"
#include <stdio.h>
#include <math.h>

int matInput(Mat matrix)
{
    return matInLocal(matrix.data, 0, matrix.numRows - 1, 0, matrix.numCols - 1);
}

int matInLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    char ch;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            ungetc(ch = getchar(), stdin);
            if ((ch < '0' || ch > '9') && ch != ' ' && ch != '\n' && ch != '\t')
            {
                return BREAK;
            }
            scanf("%lf", &matData[i][j]);
        }
    }
    return SUCCESS;
}

void matOutput(Mat matrix)
{
    matOutLocal(matrix.data, 0, matrix.numRows - 1, 0, matrix.numCols - 1);
}

void matOutLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            if (fabs(matData[i][j] - (int)matData[i][j]) < ZEROTHRES ||
                fabs(matData[i][j] - (int)matData[i][j] + 1) < ZEROTHRES ||
                fabs(matData[i][j] - (int)matData[i][j] - 1) < ZEROTHRES)
            {
                if (fabs(matData[i][j]) < 0.001)
                {
                    printf("%6d ", 0);
                }
                else
                {
                    printf("%6.0lf ", matData[i][j]);
                }
            }
            else
            {
                printf("%6.3lf ", matData[i][j]);
            }
        }
        putchar('\n');
    }
}