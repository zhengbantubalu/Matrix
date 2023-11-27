#include "./include/EasyCalc.h"
#include "../include/MatOper.h"
#include "../include/MatUtil.h"
#include "../include/MatIO.h"
#include "../include/MatStruct.h"
#include "../include/MatConst.h"
#include <stdio.h>
#include <stdbool.h>

#define START 0
#define INPUT 1
#define SELECT 2
#define FREE 3
#define END 4

#define RANK 1
#define DETER 2
#define ECHE 3
#define REDECHE 4
#define TRANS 5
#define ADJO 6
#define INVER 7
#define ADD 8
#define SUB 9
#define SCAMUL 10
#define MULTI 11
#define CLEAR 12

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

void easyCalc(void)
{
    int state = START;
    int choice = 0;
    char ch;
    Mat matrix, matemp, matOut;
    int numRows = 0, numCols = 0;
    int rank = 0;
    double det = 0, multer = 0;
    printf("简易矩阵计算器\n\n");
    while (state != END)
    {
        switch (state)
        {
        case START:
            printf("请输入选项:\n1.输入矩阵    2.测试用例    3.退出程序\n\n");
            choice = 0;
            scanf("%d", &choice);
            clear();
            putchar('\n');
            switch (choice)
            {
            case 1:
                state = INPUT;
                break;
            case 2:
                printf("例1:\n4 4\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n\n");
                printf("例2:\n4 5\n1 1 1 1 1\n3 2 1 1 -3\n0 1 3 2 5\n5 4 3 3 -1\n\n");
                printf("例3:\n3 3 3 -3 4 2 -3 4 0 -1 1\n\n");
                printf("例4:\n4 4 4 1 2 4 1 2 0 2 10 5 2 0 0 1 1 7\n\n");
                break;
            case 3:
                state = END;
                break;
            default:
                printf("选项不存在\n");
                pause();
            }
            break;
        case INPUT:
            printf("请输入矩阵A\n[行数] [列数] [矩阵] (无需换行)\n");
            printf("输入任何非数字以中断输入\n\n");
            ungetc(ch = getchar(), stdin);
            if (scanf("%d%d", &numRows, &numCols) != 2)
            {
                printf("\n输入中断\n");
                clear();
                pause();
                state = START;
                break;
            }
            matInit(&matrix, numRows, numCols);
            switch (matInput(matrix))
            {
            case SUCCESS:
                putchar('\n');
                state = SELECT;
                break;
            case BREAK:
                printf("\n输入中断\n");
                pause();
                state = FREE;
                break;
            }
            clear();
            break;
        case SELECT:
            printf("请输入选项:\n1. 求矩阵的秩       2. 求矩阵的行列式   3. 求行阶梯形矩阵\n");
            printf("4. 求行最简形矩阵   5. 求转置矩阵       6. 求伴随矩阵\n");
            printf("7. 求逆矩阵         8. 矩阵加法         9. 矩阵减法\n");
            printf("10.矩阵数乘         11.矩阵乘法         12.清除矩阵\n\n");
            choice = 0;
            scanf("%d", &choice);
            clear();
            putchar('\n');
            switch (choice)
            {
            case RANK:
                matRank(matrix, false, &rank);
                printf("rank(A) = %d\n", rank);
                pause();
                break;
            case DETER:
                switch (matDeter(matrix, &det))
                {
                case SUCCESS:
                    printf("det(A) = ");
                    prtDouble(det, PRECISION, 0, false);
                    putchar('\n');
                    break;
                case ERROR:
                    printf("只有方阵可以求行列式\n");
                }
                pause();
                break;
            case ECHE:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                matEche(matrix, matOut, NULL);
                printf("A的行阶梯形矩阵:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            case REDECHE:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                matRedEche(matrix, matOut, false);
                printf("A的行最简形矩阵:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            case TRANS:
                matInit(&matOut, matrix.numCols, matrix.numRows);
                matTrans(matrix, matOut);
                printf("A的转置矩阵:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            case ADJO:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                switch (matAdjo(matrix, matOut))
                {
                case SUCCESS:
                    printf("A的伴随矩阵:\n");
                    matOutput(matOut, PRECISION, WIDTH);
                    break;
                case ERROR:
                    printf("只有方阵可以求伴随矩阵\n");
                    break;
                }
                matFree(&matOut);
                pause();
                break;
            case INVER:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                switch (matInver(matrix, matOut))
                {
                case SUCCESS:
                    printf("A的逆矩阵:\n");
                    matOutput(matOut, PRECISION, WIDTH);
                    break;
                case SINGULAR:
                    printf("矩阵不可逆\n");
                    break;
                case ERROR:
                    printf("只有方阵可以求逆矩阵\n");
                    break;
                }
                matFree(&matOut);
                pause();
                break;
            case ADD:
                matInit(&matemp, matrix.numRows, matrix.numCols);
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("请输入 %d行 %d列 的矩阵B (无需输入行列数)\n", numRows, numCols);
                printf("输入任何非数字以中断输入\n\n");
                switch (matInput(matemp))
                {
                case SUCCESS:
                    matData(matrix, matemp, matOut);
                    printf("\nA + B =\n");
                    matOutput(matOut, PRECISION, WIDTH);
                    break;
                case BREAK:
                    printf("\n输入中断\n");
                    break;
                }
                clear();
                matFree(&matemp);
                matFree(&matOut);
                pause();
                break;
            case SUB:
                matInit(&matemp, matrix.numRows, matrix.numCols);
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("请输入 %d行 %d列 的矩阵B (无需输入行列数)\n", numRows, numCols);
                printf("输入任何非数字以中断输入\n\n");
                switch (matInput(matemp))
                {
                case SUCCESS:
                    clear();
                    printf("\n请输入选项:\n1.A - B    2.B - A\n\n");
                    choice = 0;
                    scanf("%d", &choice);
                    clear();
                    putchar('\n');
                    switch (choice)
                    {
                    case 1:
                        matSub(matrix, matemp, matOut);
                        printf("A - B =\n");
                        matOutput(matOut, PRECISION, WIDTH);
                        break;
                    case 2:
                        matSub(matemp, matrix, matOut);
                        printf("B - A =\n");
                        matOutput(matOut, PRECISION, WIDTH);
                        break;
                    default:
                        printf("选项不存在\n");
                    }
                    break;
                case BREAK:
                    clear();
                    printf("\n输入中断\n");
                    break;
                }
                matFree(&matemp);
                matFree(&matOut);
                pause();
                break;
            case SCAMUL:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("请输入数乘倍数:\n\n");
                if (scanf("%lf", &multer) == 1)
                {
                    matScaMul(matrix, matOut, multer);
                    printf("\nA * ");
                    prtDouble(multer, PRECISION, 0, false);
                    printf(" =\n");
                    matOutput(matOut, PRECISION, WIDTH);
                }
                else
                {
                    printf("\n输入不是数字\n");
                }
                clear();
                matFree(&matOut);
                pause();
                break;
            case MULTI:
                printf("请输入选项:\n1.A * B    2.B * A\n\n");
                scanf("%d", &choice);
                clear();
                putchar('\n');
                switch (choice)
                {
                case 1:
                    printf("请输入矩阵B\n[行数] [列数] [矩阵] (无需换行)\n");
                    printf("矩阵B的行数须为%d\n", matrix.numCols);
                    printf("输入任何非数字以中断输入\n\n");
                    ungetc(ch = getchar(), stdin);
                    if (scanf("%d%d", &numRows, &numCols) != 2)
                    {
                        printf("\n输入中断\n");
                        clear();
                        break;
                    }
                    if (numRows != matrix.numCols)
                    {
                        printf("\n矩阵B的行数不符合要求\n");
                        clear();
                        break;
                    }
                    else
                    {
                        matInit(&matemp, numRows, numCols);
                        matInit(&matOut, matrix.numRows, matemp.numCols);
                        switch (matInput(matemp))
                        {
                        case SUCCESS:
                            matMulti(matrix, matemp, matOut);
                            printf("\nA * B =\n");
                            matOutput(matOut, PRECISION, WIDTH);
                            break;
                        case BREAK:
                            printf("\n输入中断\n");
                            break;
                        }
                        clear();
                        matFree(&matemp);
                        matFree(&matOut);
                        break;
                    }
                    break;
                case 2:
                    printf("请输入矩阵B\n[行数] [列数] [矩阵] (无需换行)\n");
                    printf("矩阵B的列数须为%d\n", matrix.numRows);
                    printf("输入任何非数字以中断输入\n\n");
                    ungetc(ch = getchar(), stdin);
                    if (scanf("%d%d", &numRows, &numCols) != 2)
                    {
                        printf("\n输入中断\n");
                        clear();
                        break;
                    }
                    if (numCols != matrix.numRows)
                    {
                        printf("\n矩阵B的列数不符合要求\n");
                        clear();
                        break;
                    }
                    else
                    {
                        matInit(&matemp, numRows, numCols);
                        matInit(&matOut, matemp.numRows, matrix.numCols);
                        switch (matInput(matemp))
                        {
                        case SUCCESS:
                            matMulti(matemp, matrix, matOut);
                            printf("\nB * A =\n");
                            matOutput(matOut, PRECISION, WIDTH);
                            break;
                        case BREAK:
                            printf("\n输入中断\n");
                            break;
                        }
                        clear();
                        matFree(&matemp);
                        matFree(&matOut);
                        break;
                    }
                    break;
                default:
                    printf("选项不存在\n");
                }
                pause();
                break;
            case CLEAR:
                state = FREE;
                break;
            default:
                printf("选项不存在\n");
                pause();
            }
            break;
        case FREE:
            matFree(&matrix);
            state = START;
            break;
        }
    }
}