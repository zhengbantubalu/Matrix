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
            if ((ch < '0' || ch > '9') && ch != ' ' && ch != '-' && ch != '\n' && ch != '\t')
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
            prtDouble(matData[i][j], PRECISION, WIDTH);
            putchar(' ');
        }
        putchar('\n');
    }
}

void prtDouble(double value, int precision, int width)
{
    char format[20];
    if (fabs(value - (int)value) < ZEROTHRES ||
        fabs(value - (int)value + 1) < ZEROTHRES ||
        fabs(value - (int)value - 1) < ZEROTHRES)
    {
        sprintf(format, "%%%d.0lf", width);
    }
    else
    {
        sprintf(format, "%%%d.%dlf", width, precision);
    }
    printf(format, fabs(value));
}