/**
 * @file    EasyCalc.c
 * @brief   示例 – 简易矩阵计算器
 */

#include "./include/EasyCalc.h"
#include "../include/MatOper.h"   //调用了其中几乎所有函数
#include "../include/MatUtil.h"   //初始化矩阵、释放矩阵存储空间
#include "../include/MatIO.h"     //矩阵输入、矩阵输出、浮点数输出
#include "../include/MatStruct.h" //矩阵结构体
#include "../include/MatConst.h"  //浮点数输出参数、函数返回状态码
#include <stdio.h>                //scanf,printf,getchar,putchar
#include <stdbool.h>              //bool,ture,false

#define START 0  // 开始
#define INPUT 1  // 输入矩阵
#define SELECT 2 // 选择操作
#define FREE 3   // 释放空间
#define END 4    // 结束

#define RANK 1    // 求矩阵的秩
#define DETER 2   // 求矩阵的行列式
#define ECHE 3    // 求行阶梯形矩阵
#define REDECHE 4 // 求行最简形矩阵
#define TRANS 5   // 求转置矩阵
#define ADJO 6    // 求伴随矩阵
#define INVER 7   // 求逆矩阵
#define ADD 8     // 矩阵加法
#define SUB 9     // 矩阵减法
#define SCAMUL 10 // 矩阵数乘
#define MULTI 11  // 矩阵乘法
#define CLEAR 12  // 清除矩阵

// 清空输入缓冲区至'\n'
void static clear(void)
{
    while (getchar() != '\n')
        ;
}

// 暂停
void static pause(void)
{
    ungetc('0', stdin);
    printf("\n按回车键继续...");
    getchar();
    clear();
    putchar('\n');
}

void easyCalc(void)
{
    int state = START; // 状态
    int choice = 0;    // 选项
    Mat matrix,        // 矩阵(A)
        matemp,        // 临时矩阵(B)
        matOut;        // 待输出矩阵
    int numRows = 0,   // 矩阵行数
        numCols = 0;   // 矩阵列数
    int rank = 0;      // 矩阵的秩
    double det = 0,    // 矩阵的行列式
        multer = 0;    // 数乘倍数
    printf("简易矩阵计算器\n\n");
    // 程序主体运行逻辑使用状态机模型
    while (state != END)
    {
        switch (state)
        {
        // 开始
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
        // 输入矩阵
        case INPUT:
            printf("请输入矩阵A\n[行数] [列数] [矩阵] (无需换行)\n");
            printf("输入任何非数字以中断输入\n\n");
            if (scanf("%d%d", &numRows, &numCols) != 2)
            {
                printf("\n输入中断\n");
                clear();
                pause();
                state = START;
                break;
            }
            matInit(&matrix, numRows, numCols); // 初始化矩阵
            // 输入矩阵，并根据返回状态码执行相应操作
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
        // 选择操作
        case SELECT:
            printf("请输入选项:\n1. 求矩阵的秩       2. 求矩阵的行列式   3. 求行阶梯形矩阵\n");
            printf("4. 求行最简形矩阵   5. 求转置矩阵       6. 求伴随矩阵\n");
            printf("7. 求逆矩阵         8. 矩阵加法         9. 矩阵减法\n");
            printf("10.矩阵数乘         11.矩阵乘法         12.清除矩阵\n\n");
            choice = 0;
            scanf("%d", &choice);
            clear();
            putchar('\n');
            // 根据选项执行相应操作
            switch (choice)
            {
            // 求矩阵的秩
            case RANK:
                // 求矩阵matrix的秩
                matRank(matrix, false, &rank);
                printf("rank(A) = %d\n", rank);
                pause();
                break;
            // 求矩阵的行列式
            case DETER:
                // 求矩阵matrix的行列式，并根据返回状态码执行相应操作
                switch (matDeter(matrix, &det))
                {
                case SUCCESS:
                    printf("det(A) = ");
                    // 为统一浮点数输出精度，调用浮点数输出函数，传入MatConst.h中的PRECISION
                    prtDouble(det, PRECISION, 0, false);
                    putchar('\n');
                    break;
                case ERROR:
                    printf("只有方阵可以求行列式\n");
                }
                pause();
                break;
            // 求行阶梯形矩阵
            case ECHE:
                // 因为不能更改矩阵matrix原本的值，所以初始化一个同型矩阵matOut用于存储和输出计算结果
                matInit(&matOut, matrix.numRows, matrix.numCols);
                // 求矩阵matrix的行阶梯形
                matEche(matrix, matOut, NULL);
                printf("A的行阶梯形矩阵:\n");
                // 输出矩阵matOut，可以传入MatConst.h中的参数PRECISION和WIDTH，也可以自定义
                matOutput(matOut, PRECISION, WIDTH);
                // 在matOut使用完毕后及时释放存储空间
                matFree(&matOut);
                pause();
                break;
            // 求行最简形矩阵
            case REDECHE:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                // 求矩阵matrix的行最简形
                matRedEche(matrix, matOut, false);
                printf("A的行最简形矩阵:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            // 求转置矩阵
            case TRANS:
                matInit(&matOut, matrix.numCols, matrix.numRows);
                // 求矩阵matrix的转置矩阵
                matTrans(matrix, matOut);
                printf("A的转置矩阵:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            // 求伴随矩阵
            case ADJO:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                // 求矩阵matrix的伴随矩阵，并根据返回状态码执行相应操作
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
            // 求逆矩阵
            case INVER:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                // 求矩阵matrix的逆矩阵，并根据返回状态码执行相应操作
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
            // 矩阵加法
            case ADD:
                // 初始化同型临时矩阵matemp用于存储矩阵B
                matInit(&matemp, matrix.numRows, matrix.numCols);
                // 初始化同型矩阵matOut用于存储和输出计算结果
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("请输入 %d行 %d列 的矩阵B (无需输入行列数)\n", numRows, numCols);
                printf("输入任何非数字以中断输入\n\n");
                switch (matInput(matemp))
                {
                case SUCCESS:
                    // 将矩阵matrix加矩阵matemp，结果赋给matOut
                    matAdd(matrix, matemp, matOut);
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
            // 矩阵减法
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
                    // A - B
                    case 1:
                        // 将矩阵matrix减矩阵matemp，结果赋给matOut
                        matSub(matrix, matemp, matOut);
                        printf("A - B =\n");
                        matOutput(matOut, PRECISION, WIDTH);
                        break;
                    // B - A
                    case 2:
                        // 将矩阵matemp减矩阵matrix，结果赋给matOut
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
            // 矩阵数乘
            case SCAMUL:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("请输入数乘倍数:\n\n");
                if (scanf("%lf", &multer) == 1)
                {
                    // 将矩阵matrix数乘multer，结果赋给matOut
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
            // 矩阵乘法
            case MULTI:
                printf("请输入选项:\n1.A * B    2.B * A\n\n");
                scanf("%d", &choice);
                clear();
                putchar('\n');
                switch (choice)
                {
                // A * B
                case 1:
                    printf("请输入矩阵B\n[行数] [列数] [矩阵] (无需换行)\n");
                    printf("矩阵B的行数须为%d\n", matrix.numCols);
                    printf("输入任何非数字以中断输入\n\n");
                    // 此处复用numRows和numCols用于存储被乘矩阵matemp的行列数
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
                        // 使用刚刚获取的输入初始化被乘矩阵matemp
                        matInit(&matemp, numRows, numCols);
                        // matrix左乘matemp，结果矩阵matOut的行数是matrix的行数，列数是matemp的列数
                        matInit(&matOut, matrix.numRows, matemp.numCols);
                        switch (matInput(matemp))
                        {
                        case SUCCESS:
                            // 将矩阵matrix左乘矩阵matemp，结果赋给matOut
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
                // B * A
                case 2:
                    printf("请输入矩阵B\n[行数] [列数] [矩阵] (无需换行)\n");
                    printf("矩阵B的列数须为%d\n", matrix.numRows);
                    printf("输入任何非数字以中断输入\n\n");
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
                            // 将矩阵matrix右乘矩阵matemp，结果赋给matOut
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
            // 清除矩阵
            case CLEAR:
                state = FREE;
                break;
            default:
                printf("选项不存在\n");
                pause();
            }
            break;
        // 释放空间
        case FREE:
            matFree(&matrix);
            state = START;
            break;
        }
    }
}