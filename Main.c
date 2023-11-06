#include "MatHead.h"

#define START 0
#define MATINPUT 1
#define SELECT 2
#define MATFREE 3
#define END 4

int main(void)
{
    int state = START;
    int choice = 0;
    int numRows = 0, numCols = 0;
    char ch;
    double **matrix = NULL, **matOut = NULL;
    while (state != END)
    {
        switch (state)
        {
        case START:
            printf("请输入选项:\n1.输入矩阵    2.退出程序\n\n");
            choice = 0;
            scanf("%d", &choice);
            fflush(stdin);
            switch (choice)
            {
            case 1:
                state = MATINPUT;
                break;
            case 2:
                state = END;
                break;
            }
            putchar('\n');
            break;
        case MATINPUT:
            printf("请输入[行数] [列数] [矩阵](无需换行)\n");
            printf("输入任何非数字以中断输入\n\n");
            printf("例1:\n4 4\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n\n");
            printf("例2:\n4 5\n1 1 1 1 1\n3 2 1 1 -3\n0 1 3 2 5\n5 4 3 3 -1\n\n");
            printf("例3:\n3 3 3 -3 4 2 -3 4 0 -1 1\n\n");
            printf("例4:\n4 4 4 1 2 4 1 2 0 2 10 5 2 0 0 1 1 7\n\n");
            ungetc(ch = getchar(), stdin);
            if (scanf("%d%d", &numRows, &numCols) != 2)
            {
                printf("\n输入中断\n\n");
                fflush(stdin);
                system("pause");
                putchar('\n');
                state = START;
                break;
            }
            matrix = matInit(numRows, numCols);
            switch (matEnIn(matrix, numRows, numCols))
            {
            case SUCCESS:
                state = SELECT;
                putchar('\n');
                break;
            case BREAK:
                printf("\n输入中断\n\n");
                fflush(stdin);
                system("pause");
                putchar('\n');
                state = MATFREE;
                break;
            }
            break;
        case SELECT:
            printf("请输入选项:\n1.矩阵标准测试    2.求矩阵的秩      3.求矩阵的行列式\n");
            printf("4.求行阶梯形矩阵  5.求行最简形矩阵  6.求转置矩阵\n");
            printf("7.求伴随矩阵      8.求逆矩阵        9.清除矩阵\n\n");
            choice = 0;
            scanf("%d", &choice);
            putchar('\n');
            fflush(stdin);
            switch (choice)
            {
            case 1:
                matStdTest(matrix, numRows, numCols);
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 2:
                printf("rank=%d\n\n", matRank(matrix, numRows, numCols, false));
                system("pause");
                putchar('\n');
                break;
            case 3:
                if (numRows != numCols)
                {
                    printf("只有方阵可以求行列式\n\n");
                }
                else
                {
                    printf("det=%.3lf\n\n", matDet(matrix, numRows));
                }
                system("pause");
                putchar('\n');
                break;
            case 4:
                matOut = matInit(numRows, numCols);
                matEchelon(matrix, matOut, numRows, numCols);
                matEnOut(matOut, numRows, numCols);
                matFree(matOut, numRows);
                matOut = NULL;
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 5:
                matOut = matInit(numRows, numCols);
                matRedEche(matrix, matOut, numRows, numCols, false);
                matEnOut(matOut, numRows, numCols);
                matFree(matOut, numRows);
                matOut = NULL;
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 6:
                matOut = matInit(numCols, numRows);
                matTrans(matrix, matOut, numRows, numCols);
                matEnOut(matOut, numCols, numRows);
                matFree(matOut, numCols);
                matOut = NULL;
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 7:
                if (numRows != numCols)
                {
                    printf("只有方阵可以求伴随矩阵\n");
                }
                else
                {
                    matOut = matInit(numRows, numRows);
                    matAdj(matrix, matOut, numRows);
                    matEnOut(matOut, numRows, numRows);
                    matFree(matOut, numRows);
                    matOut = NULL;
                }
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 8:
                if (numRows != numCols)
                {
                    printf("只有方阵可以求逆矩阵\n");
                }
                else
                {
                    matOut = matInit(numRows, numRows);
                    switch (matInverse(matrix, matOut, numRows))
                    {
                    case SUCCESS:
                        matEnOut(matOut, numRows, numRows);
                        break;
                    case SINGULAR:
                        printf("矩阵不可逆\n");
                        break;
                    }
                    matFree(matOut, numRows);
                    matOut = NULL;
                }
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 9:
                state = MATFREE;
                break;
            }
            break;
        case MATFREE:
            matFree(matrix, numRows);
            matrix = NULL;
            state = START;
            break;
        }
    }
    printf("程序结束\n\n");
    system("pause");
    return 0;
}